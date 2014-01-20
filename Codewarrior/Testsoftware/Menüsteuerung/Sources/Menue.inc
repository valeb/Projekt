;************************************************************************************************
;*      AW32-Base-Programm  Version 1.0                                                         *
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
;*      In Init kopieren:                                                                       *
;*      jsr   Init_Menue                                                                        *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'Menue.inc'             ; Routine für das Menü                                  *
;************************************************************************************************

LED_PORT      EQU     PORTD
TASTER_PORT   EQU     PORTF

ZEIT_START    EQU     500T



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

;*************************************** STARTTEXTE **********************************************

StartText
 
         ;************************
          
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
          beq     ZU_M1
          
          rts


;************************************************************************************************

ZU_StartText2
          ;Die Adresse des nächsten Schrittes wird auf Pointer gespeichert
          ldhx    #StartText2
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          rts
          
;************************************************************************************************  

ZU_M1			
          ldhx    #Menue1
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TasteA_Flag       ;Verhindert dass ein tastendruck öfters verwendet wird
          bset    CHECKED, TasteB_Flag
          
                    
          rts
          
;************************************************************************************************

ZU_M2
          ldhx    #Menue2
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TasteA_Flag
          bset    CHECKED, TasteB_Flag
          
          lda     #0T
          sta     Zurueck
          
          rts
          
;************************************************************************************************

ZU_M3
          ldhx    #Menue3
          sthx    Pointer_Schritte
          
          ldhx    #0T
          sthx    Schritte_Counter
          
          bset    CHECKED, TasteA_Flag
          bset    CHECKED, TasteB_Flag
          
          lda     #0T
          sta     Zurueck          

          rts
          
;************************************************************************************************



Menue1    ;Hauptmenü
          
          ;jsr     Musterlauf            ;Musterlauflicht-Programm  
          
          ;Ausgabe Text

          ldhx    #Text_Ausgabe3
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght
     
          jsr     CopyText
          
          ;Zu Zeiteinstellung 
          lda     TasteA_Flag
          cmpa    #%00000001        
          beq     ZU_M2
          
          ;Zu Zeitausgabe
          lda     TasteB_Flag
          cmpa    #%00000001        
          beq     ZU_M3
                    
          rts
                    
;************************************************************************************************
Zu_ZU_M1

      bra   ZU_M1
      rts
;************************************************************************************************

Menue2    ;Zeitenstellung    
          
          ;jsr     Zeiteinstellung       ;Verändern der Zeit
          
          ;Ausgabe Text
          
          ldhx    #Text_Ausgabe5
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght
          
          jsr     CopyText

          ;Ausgabe Zahl

          ldhx    #LCD_Unten
          sthx    DestPointer 
          lda     #100T
     
          jsr     DezimalBCD
                   
          ;Austrittsbedingungen 
          
          lda     TasteA_Flag
          cmpa    #%00000001        
          beq     Zu_ZU_M1
          
          rts
          
;************************************************************************************************

Menue3    ;Zeitausgabe
          
          ;jsr     Musterlauf            ;Musterlauflicht-Programm    
          
          ;Ausgabe Text
          
          ldhx    #Text_Ausgabe4
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght
          
          jsr     CopyText

          ;Ausgabe Zahl

          ldhx    #LCD_Unten
          sthx    DestPointer 
          lda     #100T
     
          jsr     DezimalBCD
                   
          ;Austrittsbedingungen 
          
          lda     TasteB_Flag
          cmpa    #%00000001        
          beq     Zu_ZU_M1
          
          ldhx    Zurueck
          aix     #1T
          cphx    #1000T
          beq     Zu_ZU_M1               
          
          
          rts          
          
          
         
;************************************* Texte für Schritte ***************************************

                 

     

Text_Start1
                  ;----------------
          dc.b    'Valentin Bernard'
          dc.b    '      5AEL      '
          
Text_Start2
                  ;----------------
          dc.b    ' Maturaproljekt '
          dc.b    '  Alarmanlage   '

Text_Ausgabe3
                  ;----------------
          dc.b    '   HAUPTMENUE   '
          dc.b    '                '
          
Text_Ausgabe4
                  ;----------------
          dc.b    'Zeit:           '
          dc.b    '                '
          
Text_Ausgabe5
                  ;----------------
          dc.b    'Zeiteinstellung:'
          dc.b    '                '          
