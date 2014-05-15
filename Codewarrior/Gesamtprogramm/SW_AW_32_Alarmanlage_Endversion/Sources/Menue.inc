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

ZEIT_START    EQU     100T


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
          jsr     A_StartText
        
          
          ;Austrittsbedingung         Zeitverzögerung 5 sec,
          ldhx    Schritte_Counter
          aix     #1T
          sthx    Schritte_Counter
          add     #50T          
          cphx    #ZEIT_START
          beq     ZU_StartText2
          
          rts
          
          
ZU_StartText2
          
          ldhx    #StartText2
          sthx    Pointer_Schritte
          
          jsr     Init_RFID
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          rts                         

StartText2
 
          ;Ausgabe_Text
          jsr     A_StartText2  
        
          
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
          jsr     A_Inaktiv
          
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
          jsr     Check_RFID
          jsr     Bewegungsmelder
                   
          jsr     Blink_Rot
          
          ;Ausgabe: "Alarm Aktiv"
          jsr     A_Aktiv        
          
          ;Austrittsbedingungen 
          lda     PW_Flag
          cmpa    #%00000001
          beq     ZU_Inaktiv
           
          lda     Bewegung_Flag
          cmpa    #%10011111        
          beq     ZU_Alarm
          
          lda     RFID_Flag
          cmpa    #$FF
          beq     ZU_Inaktiv
          
          lda     TZUR_Flag
          cmpa    #%00000001
          beq     ZU_Alarm
          
          rts        
          
;********| Sprünge |*****************************************************************************

;Die Adresse des nächsten Schrittes wird in den Pointer geladen

ZU_Alarm
          ldhx    #Alarm
          sthx    Pointer_Schritte
          
          jsr     Init_Alarmton
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TZUR_Flag       ;Verhindert dass ein Tastendruck öfters verwendet wird
                    
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

          ;Ausgabe: "Neues Passwort"
          jsr     A_Change
          
          jsr     Change_PW
          jsr     Blink_Gruen
          
          lda     PW_Flag
          cmpa    #%00100000
          beq     ZU_Inaktiv
 
          rts                
                   
;********| Ausgelöst |***************************************************************************

Alarm    
          bset    6,PORTD
          bset    0,Alarm_Flag
                    
          jsr     Alarmton
          jsr     Check_PW
          jsr     Check_RFID   
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
          cphx    #30000T
          beq     ZU_Aktiv 
          
      
          
          lda     RFID_Flag
          cmpa    #$FF
          beq     ZU_Inaktiv
          
          lda     PW_Flag
          cmpa    #%00000001
          beq     ZU_Inaktiv
            
   
          ;Ausgabe Text "Alarm"
          jsr     A_Alarm
          rts                 
          
;************************************************************************************************

