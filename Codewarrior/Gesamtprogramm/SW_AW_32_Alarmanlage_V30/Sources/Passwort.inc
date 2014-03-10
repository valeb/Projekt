;************************************************************************************************
;*      AW32-Passwort  Version 1.0                                                              *
;*                                                                                              *
;*      Revision vom 10. Januar 2014                                                            *
;*                                                                                              *
;*      Name: Valentin Beranrd                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Passworteingabe auf Richtigkeit �berpr�fen                                              *
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      PW_Flag     ds    1T                                                                    *
;*      PW_Counter  ds    1T                                                                    *
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr     Check_PW                                                                        *
;*                                                                                              *
;*      In Init kopieren:                                                                       *
;*      jsr   Init_Passwort                                                                     *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'Passwort.inc'        ; Routine zur Passworteingabe                             *
;*                                                                                              *      
;************************************************************************************************

; OK --> PD1
; ZUR --> PD0
; VOR --> PD2
; 1 --> PD3 
; 2 --> PD4 
; 3 --> PF6 
; 4 --> PF5 
; 5 --> PF7 
; 6 --> PF4
; 7 --> PF3
; 8 --> PF2
; 9 --> PF1
; 0 --> PF0

Check_PW

      lda     #%00000001  
      cmpa    TOK_Flag
      bne     PW_Weiter
      
      bset    0,TOK_Flag
      bset    7,PW_Flag

PW_Weiter
      
      brclr   7,PW_Flag,PW_Ende
      
            
      
PW_Ende

      rts
        
Passwort

  dc.w    1
  dc.w    2
  dc.w    3
  dc.w    4
  dc.w    5
  
EndePW  
  

            
                  