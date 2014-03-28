;************************************************************************************************
;*      AW32-Passwort  Version 1.0                                                              *
;*                                                                                              *
;*      Revision vom 10. Januar 2014                                                            *
;*                                                                                              *
;*      Name: Valentin Beranrd                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Passworteingabe auf Richtigkeit überprüfen                                              *
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      PW_Flag     ds    1T                                                                    *
;*      PW_Counter  ds    1T                                                                    *
;*      Compare     ds    1T                                                                    *    
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


Check_PW

      lda     #%00000001  
      cmpa    TOK_Flag
      bne     PW_Weiter
      
      bset    1,TOK_Flag
      
      brclr   7,PW_Flag,StartPW
      
      brset   6,PW_Flag,Fehler
      brclr   6,PW_Flag,Richtig
      
StartPW      
      bset    7,PW_Flag
      
      ;compare Eingabelänge, richtigkeit

PW_Weiter
      
      brclr   7,PW_Flag,PW_Ende
      
      ldhx    #Passwort
      txa
      add     TValue
      tax
      lda     0,X
      
      cmpa    TValue
      beq     Richtig1
            
      bset    6, PW_Flag      ; Fehler
       
Richtig1

      lda     PW_Counter
      inca
      sta     PW_Counter
      cmpa    #4
      blo     Richtig2
      
      bset    6, PW_Flag      ; Fehler
      
Richtig2      
      
       
      
PW_Ende

      rts
      
Fehler

      lda   #0T
      sta   PW_Counter
      clr   PW_Flag
      ; Print Falsche Eingabe
      
      rts
      
Richtig

      lda   #0T
      sta   PW_Counter
      clr   PW_Flag
      bset  0,PW_Flag
      ; Print Richtige Eingabea
      
      
      rts
                 
        
Passwort

  dc.w    1
  dc.w    2
  dc.w    3
  dc.w    4
  dc.w    5
  
EndePW  
  

            
                  