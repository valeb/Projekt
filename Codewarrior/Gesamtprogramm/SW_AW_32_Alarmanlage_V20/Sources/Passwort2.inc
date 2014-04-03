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


PW_LAENGE     EQU     5T


Check_PW

          lda     #%00000001
          cmpa    TOK_Flag
          bne     PW_Weiter
      
          bset    1,TOK_Flag

          brclr   7,PW_Flag,StartPW
         
          ldhx    #PW_1
          txa
          add     PW_Counter
          add     #1T
          tax
          lda     0,X
          cmpa    #$FF
          bne     Fehler 
          
          lda     #0T
          sta     PW_Counter    

          brset   6,PW_Flag,Fehler
          brclr   6,PW_Flag,Richtig

StartPW      
          bset    7,PW_Flag
          lda     #0T
          sta     PW_Counter
          ; Text Passwort Eingeben 
          ldhx    #Text_PW
          sthx    SourcePointer
          ldhx    #LCD_Unten
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText
          
          rts 
          
Fehler

          lda     #0T
          sta     PW_Counter
          clr     PW_Flag
          bset    1,PW_Flag
          
          ; Print Falsche Eingabe
          ldhx    #Text_Fehler
          sthx    SourcePointer
          ldhx    #LCD_Unten
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText 
          
      
          rts
      
Richtig

          lda   #0T
          sta   PW_Counter
          clr   PW_Flag
          bset  0,PW_Flag
      
          rts          

PW_Weiter

          brclr   7,PW_Flag,PW_Nichts
          
          lda     #%00000001
          cmpa    T1_Flag
          beq     PW_Druck
          cmpa    T2_Flag
          beq     PW_Druck
          cmpa    T3_Flag
          beq     PW_Druck
          cmpa    T4_Flag
          beq     PW_Druck
          cmpa    T5_Flag
          beq     PW_Druck
          cmpa    T6_Flag
          beq     PW_Druck
          cmpa    T7_Flag
          beq     PW_Druck
          cmpa    T8_Flag
          beq     PW_Druck
          cmpa    T9_Flag
          beq     PW_Druck
          cmpa    T0_Flag
          beq     PW_Druck

          bra     PW_rts
          
PW_Druck          
      
          bset    1,T1_Flag
          bset    1,T2_Flag
          bset    1,T3_Flag
          bset    1,T4_Flag
          bset    1,T5_Flag
          bset    1,T6_Flag
          bset    1,T7_Flag
          bset    1,T8_Flag
          bset    1,T9_Flag
          bset    1,T0_Flag
      
          ; * Ausgeben
          ldhx    #Text_Stern
          sthx    SourcePointer
          ldhx    #LCD_Unten+4
          txa
          add     PW_Counter
          tax
          sthx    DestPointer
          lda     #1T
          sta     TextLenght          
          jsr     CopyText
          
          ldhx    #PW_1
          txa
          add     PW_Counter
          tax
          lda     0,X
                
          cmpa    TValue
          beq     Richtig1
            
          bset    6, PW_Flag      ; Fehler
       
Richtig1

          lda     PW_Counter
          inca
          sta     PW_Counter
          
          rts       
      
PW_Nichts

          brclr   1,PW_Flag,PW_Del
          
          lda     PW_Counter
          inca
          sta     PW_Counter
          cmpa    #50T
          bne     PW_rts         
          
PW_Del

          ; untere Zeile l�schen 
          ldhx    #Text_Nichts
          sthx    SourcePointer
          ldhx    #LCD_Unten
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText         
PW_rts      
      
          rts          
        
Passwort

      dc.b    1
      dc.b    2
      dc.b    3
      dc.b    4
      dc.b    5
  
EndePW


Change_PW

          lda     #1T
          sta     PW_1
          lda     #2T
          sta     PW_2
          lda     #3T
          sta     PW_3
          lda     #4T
          sta     PW_4
          lda     #5T
          sta     PW_5
          lda     #$FF
          sta     PW_6
          lda     #$FF
          sta     PW_7
          lda     #$FF
          sta     PW_8
          lda     #$FF
          sta     PW_9
          lda     #$FF
          sta     PW_10
          
          rts                     

  
  
Text_PW 
              ;----------------
      dc.b    'PW:             '
      
Text_Stern
      
      dc.b    '*'
      
Text_Nichts
              ;----------------
      dc.b    '                '      
      
Text_Fehler
              ;----------------
      dc.b    'FALSCHE EINGABE '
            
                  