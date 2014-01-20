;************************************************************************************************
;*      AW32-Base-Programm  Version 1.0                                                         *
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name:                                                                                   *
;*      Klasse:                                                                                 *
;*      Version:                                                                                *
;*                                                                                              *
;*      Blinklicht, 1 Pin, Variable Dauer                                                       *
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
;*      INCLUDE 'Blinklicht.inc'        ; Routine für das Blicklicht                            *
;************************************************************************************************

VERZOEGERUNG    EQU   100T
BLINK_PIN       EQU   0
BLINK_PORT      EQU   PORTD

;************************************************************************************************
;*                           Initialisierungen für das Blinklicht                               *
;************************************************************************************************

Init_Blinklicht
                lda   #10T
                sta   Blink_Counter
                rts


;************************************************************************************************
;*                               Programm für das BLinklicht                                    *
;************************************************************************************************

Blinklicht
          lda   Blink_Counter               	; Verzögerung 100 x 10ms = 1s
          inca
          sta   Blink_Counter
          cmpa  #VERZOEGERUNG                         
          bne   Ende_Blinklicht
          
          clr   Blink_Counter
          brset BLINK_PIN,BLINK_PORT,Led_aus

Led_ein
          bset  BLINK_PIN,BLINK_PORT
          rts
   
Led_aus
          bclr  BLINK_PIN,BLINK_PORT
          rts

Ende_Blinklicht
          rts