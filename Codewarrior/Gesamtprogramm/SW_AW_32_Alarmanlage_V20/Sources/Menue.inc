;************************************************************************************************
;*      MENÜSTRUKTUR                                                                            *
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name:   Valentin Bernard                                                                *
;*      Klasse:   4AEL                                                                          *
;*      Version:   1.0                                                                          *
;*                                                                                              *
;*      Programmiert auf einem Target mit 4,9152 MHz                                            *
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      Pointer_Schritte ds     2T                                                              *
;*      Zurueck          ds     2T                                                              *
;*      Schritte_Counter ds     2T                                                              *
;*                                                                                              *
;*      In Hauptloop kopieren:                                                                  *
;*      jsr     Menue                                                                           *
;*
;*      Variablen
;*      Alarm_Timer      ds     2T
;*                                                                                              *
;*      In Init kopieren:                                                                       *
;*      jsr   Init_Menue                                                                        *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'Menue.inc'             ; Routine für das Menü                                  *
;************************************************************************************************

LED_PORT      EQU     PORTD
TASTER_PORT   EQU     PORTF

ZEIT_START    EQU     200T



;************************************************************************************************
;*                           Initialisierung des Menüs                                          *
;************************************************************************************************

Init_Menue
          ldhx  #StartText		            ;Speichere Adresse des ersten Schrittes in Pointer
          sthx  Pointer_Schritte
          rts

;************************************************************************************************
;*                               Programm für das Menü                                          *
;************************************************************************************************

Menue

          ldhx    Pointer_Schritte        ; lade Adresse des aktuellen Schrittes in HX                      
          jsr     0,x                     ; springe zu dieser Adresse 
          
          rts       

;********| STARTTEXTE |**************************************************************************

StartText
          
          ;Ausgabe_Text          
          ldhx    #Text_Start1
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght     
          jsr     CopyText
        
          
          ;Austrittsbedingung         Zeitverzögerung 5 sec,
          ldhx    Schritte_Counter
          aix     #1T
          sthx    Schritte_Counter
          
          cphx    #ZEIT_START
          beq     ZU_StartText2
          
          rts
          
          
ZU_StartText2
          
          ldhx    #StartText2
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          rts
                   
          

StartText2
 
          ;Ausgabe_Text
          ldhx    #Text_Start2
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght     
          jsr     CopyText
        
          
          ;Austrittsbedingung         Zeitverzögerung 5 sec,
          ldhx    Schritte_Counter
          aix     #1T
          sthx    Schritte_Counter
          
          cphx    #ZEIT_START
          beq     ZU_Inaktiv
          
          rts


          
;********| Deaktiviert |************************************************************************                                                                        

Inaktiv
          
          ;jsr     Check-RFID
          jsr     Blink_Gruen
              
          ;Ausgabe: "Alarm Inaktiv"
          ldhx    #Text_Inaktiv
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght
          jsr     CopyText
          
          ;Aktieviertung 
          lda     TasteA_Flag
          cmpa    #%00000001        
          beq     ZU_Aktiv
                    
          rts
          
                                          
;********| Aktiviert |***************************************************************************

Aktiv      
          
          ;jsr     Passwort
          ;jsr     Check-RFID
          jsr     Bewegungsmelder
                   
          jsr     Blink_Rot
          
          ;Ausgabe: "Alarm Aktiv"
          ldhx    #Text_Aktiv
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght          
          jsr     CopyText          
          
          ;Austrittsbedingungen 
          
          lda     TasteA_Flag
          cmpa    #%00000001        
          beq     ZU_Inaktiv
          
          
          ;lda     RFID-Flag
          
          ;lda     PW_Flag
           
          lda     Bewegung_Flag
          cmpa    #%10011111        
          beq     ZU_Alarm
          
          rts
          
;********| Sprünge |*****************************************************************************

;Die Adresse des nächsten Schrittes wird in den Pointer geladen
         
ZU_Alarm
          ldhx    #Alarm
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TasteA_Flag       ;Verhindert dass ein Tastendruck öfters verwendet wird
          bset    CHECKED, TasteB_Flag
          
          lda     #0T
          sta     Zurueck
          
          rts
          
ZU_Aktiv
          clr     Alarm_Flag
                    
          ldhx    #Aktiv
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TasteA_Flag
          bset    CHECKED, TasteB_Flag
          
          lda     #0T
          sta     Zurueck
          
          rts
                    
ZU_Inaktiv
          clr     Alarm_Flag
			
          ldhx    #Inaktiv
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TasteA_Flag
          bset    CHECKED, TasteB_Flag
          
                    
          rts                 
          
;********| Ausgelöst |***************************************************************************

Alarm    
          bset    0,Alarm_Flag
          bset    6,PORTD
           
          jsr     Bewegungsmelder
          
          lda     Bewegung_Flag
          cmpa    #%00000000
          bne     No_Reset
          
          ldhx    #0T
          sthx    Alarm_Timer
          
No_Reset          
          
          jsr     Alarmton
          ;jsr     Passwort
          ;jsr     Check-RFID  
   
          ;Ausgabe Text 
          ldhx    #Text_Alarm
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght          
          jsr     CopyText        
          
          
          ;Austrittsbedingungen          
          
          ;lda     RFID_Flag
          ;lda     PW_Flag
          
          lda     TasteA_Flag
          cmpa    #%00000001        
          beq     ZU_Inaktiv
          
          ldhx    Alarm_Timer
          incx
          sthx    Alarm_Timer
          cphx    #40000T
          beq     ZU_Aktiv

          rts          
          
                   
;*******|Texte für Schritte |*******************************************************************    

Text_Start1
                  ;----------------
          dc.b    'Valentin Bernard'
          dc.b    '      5AEL      '
          
Text_Start2
                  ;----------------
          dc.b    ' Maturaproljekt '
          dc.b    '  Alarmanlage   '

Text_Inaktiv
                  ;----------------
          dc.b    ' Alarm Inaktiv  '
          dc.b    '                '
          
Text_Aktiv
                  ;----------------
          dc.b    ' Alarm Aktiv    '
          dc.b    '                '
          
Text_Alarm
                  ;----------------
          dc.b    '    Alarm!!     '
          dc.b    '                '
