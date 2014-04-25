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
;*                                                                                              *
;*      Variablen                                                                               *
;*      Alarm_Timer      ds     2T                                                              *
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
          ldhx  #Inaktiv		            ;Speichere Adresse des ersten Schrittes in Pointer
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
          
          jsr     Change_PW
              
          ;Ausgabe: "Alarm Inaktiv"
          ldhx    #Text_Inaktiv
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght
          jsr     CopyText
          
          ;Aktieviertung 
          lda     TOK_Flag
          cmpa    #%00000001        
          beq     ZU_Aktiv
          
          ;Passwort ändern
          lda     TVOR_Flag
          cmpa    #%00000001
          beq     ZU_Change
                    
          rts             
                                          
;********| Aktiviert |***************************************************************************

Aktiv      
          
          jsr     Check_PW
          ;jsr     Check-RFID
          jsr     Bewegungsmelder
                   
          jsr     Blink_Rot
          
          ;Ausgabe: "Alarm Aktiv"
          ldhx    #Text_Aktiv
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText          
          
          ;Austrittsbedingungen 
          
          ;lda     RFID-Flag

          lda     PW_Flag
          cmpa    #%00000001
          beq     ZU_Inaktiv
           
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
          
          bset    CHECKED, TOK_Flag       ;Verhindert dass ein Tastendruck öfters verwendet wird
          
          rts 
         

ZU_Aktiv
          clr     Alarm_Flag
          bclr    0,PORTB
          clr     Bewegung_Flag
                    
          ldhx    #Aktiv
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TOK_Flag
          
          ;lda     #0T
          ;sta     Zurueck
          
          rts
                                        
ZU_Inaktiv
          clr     Alarm_Flag
          bclr    0,PORTB
          clr     Bewegung_Flag
			
          ldhx    #Inaktiv
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TOK_Flag
          clr     PW_Flag
          bset    CHECKED, TZUR_Flag
                    
          rts
           
ZU_Change
          bset    CHECKED, TVOR_Flag
          
          ldhx    #Change
          sthx    Pointer_Schritte         
          
          rts
                                    
;********| Passwort ändern |*********************************************************************

Change
  
          
          jsr     Change_PW
          jsr     Blink_Gruen
          
          ;Ausgabe: "Neues Passwort"
          ldhx    #Text_Change
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #19T
          sta     TextLenght
          jsr     CopyText
            
          lda     TZUR_Flag
          cmpa    #%00000001
          beq     ZU_Inaktiv
           
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
          ;Austrittsbedingungen 
          ldhx    Alarm_Timer
          incx
          sthx    Alarm_Timer
          cphx    #40000T
          beq     ZU_Aktiv         
          
          ;lda     RFID_Flag
          ;lda     PW_Flag
          
          lda     PW_Flag
          cmpa    #%00000001
          beq     ZU_Inaktiv
          
          
          jsr     Alarmton
          jsr     Check_PW
          ;jsr     Check-RFID  
   
          ;Ausgabe Text 
          ldhx    #Text_Alarm
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText    

          rts                 
          
                   
;*******|Texte für Schritte |*******************************************************************    

Text_Alarm
                  ;----------------
          dc.b    '    Alarm!!     '
          
Text_Start1
                  ;----------------
          dc.b    'Valentin Bernard'
          dc.b    '      5AEL      '
          
Text_Start2
                  ;----------------
          dc.b    ' Maturaprojekt  '
          dc.b    ' Alarmanlage    '

Text_Inaktiv
                  ;----------------
          dc.b    ' Alarm Inaktiv  '
          dc.b    '                '
Text_Change
                  ;----------------
          dc.b    ' Neues Passwort '
          dc.b    'PW:'
Text_Aktiv
                  ;----------------
          dc.b    ' Alarm Aktiv    '
