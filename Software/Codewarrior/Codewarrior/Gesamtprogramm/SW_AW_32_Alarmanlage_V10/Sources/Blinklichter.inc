;************************************************************************************************
;*      AW32-Base-Programm  Version 1.0                                                         *
;*                                                                                              *
;*      Revision vom 10. Januar 2014                                                            *
;*                                                                                              *
;*      Name: Valentin Beranrd                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Blinklicht, Variable Dauer                                                              *
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      Blink_Counter    ds  1T                                                                 *
;*                                                                                              *
;*      In Hauptloop kopieren:                                                                  *
;*      jsr     Blinklicht                                                                      *
;*                                                                                              *
;*      In Init kopieren:                                                                       *
;*      jsr   Init_Blinklicht                                                                   *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'Blinklichter.inc'        ; Routine f�r das Blicklicht                          *
;************************************************************************************************

VERZOEGERUNG    EQU   50T
BLINK_ROT       EQU   0
BLINK_GRUEN     EQU   1
BLINK_PORT      EQU   PORTD

;************************************************************************************************
;*                           Initialisierungen f�r das Blinklicht                               *
;************************************************************************************************

Init_Blinklicht
                lda   #10T
                sta   Blink_Counter
                rts


;************************************************************************************************
;*                          Programm f�r das rote Blinklicht                                    *
;************************************************************************************************

Blink_Rot

          bclr  BLINK_GRUEN,BLINK_PORT
        
          lda   Blink_Counter               	; Verz�gerung 100 x 10ms = 1s
          inca
          sta   Blink_Counter
          cmpa  #VERZOEGERUNG                         
          bne   Ende_Rot
          
          lda   #0T
          sta   Blink_Counter
          brset BLINK_ROT,BLINK_PORT,Rot_aus

Rot_ein
          bset  BLINK_ROT,BLINK_PORT
          rts
   
Rot_aus
          bclr  BLINK_ROT,BLINK_PORT
          rts

Ende_Rot
          rts
          
                    
;************************************************************************************************
;*                          Programm f�r das gruene Blinklicht                                  *
;************************************************************************************************

Blink_Gruen

          bclr  BLINK_ROT,BLINK_PORT

          lda   Blink_Counter               	; Verz�gerung 100 x 10ms = 1s
          inca
          sta   Blink_Counter
          cmpa  #VERZOEGERUNG                         
          bne   Ende_Gruen
          
          lda   #0T
          sta   Blink_Counter
          brset BLINK_GRUEN,BLINK_PORT,Gruen_aus

Gruen_ein
          bset  BLINK_GRUEN,BLINK_PORT
          rts
   
Gruen_aus
          bclr  BLINK_GRUEN,BLINK_PORT
          rts

Ende_Gruen
          rts