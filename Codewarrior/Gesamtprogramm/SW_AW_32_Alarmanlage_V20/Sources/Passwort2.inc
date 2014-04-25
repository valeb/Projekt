;************************************************************************************************
;*      AW32-Passwort  Version 2.0                                                              *
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

Init_PW

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


Check_PW
          ; Anfang oder Ende?
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
          bne     Falsch
          
          lda     #0T
          sta     PW_Counter    

          brset   6,PW_Flag,Falsch
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
          
Falsch

          lda     #0T
          sta     PW_Counter
          sta     PW_Flag
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
          sta   PW_Flag
          bset  0,PW_Flag
      
          rts          

PW_Weiter

          brclr   7,PW_Flag,PW_Nichts
          
          ; Tastendruck erkennen
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
      
          bset    CHECKED,T1_Flag
          bset    CHECKED,T2_Flag
          bset    CHECKED,T3_Flag
          bset    CHECKED,T4_Flag
          bset    CHECKED,T5_Flag
          bset    CHECKED,T6_Flag
          bset    CHECKED,T7_Flag
          bset    CHECKED,T8_Flag
          bset    CHECKED,T9_Flag
          bset    CHECKED,T0_Flag
      
          jsr     Ausgabe_Stern
          
          ldhx    #PW_1
          txa
          add     PW_Counter
          tax
          lda     0,X
                
          cmpa    TValue
          beq     ZeichenOK
            
          bset    6, PW_Flag      ; Fehler
       
ZeichenOK

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

          ; untere Zeile löschen 
          ldhx    #Text_Nichts
          sthx    SourcePointer
          ldhx    #LCD_Unten
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText
          
          lda     #0T
          sta     PW_Counter
          sta     PW_Flag
                  
PW_rts      
      
          rts          


Change_PW

          ; Ende der Eingabe?
          lda     #%00000001
          cmpa    TOK_Flag
          bne     Change_Weiter
          cmpa    TZUR_Flag
          bne     Change_Weiter
          
          ; Bei 0 Zeichen: Kein Ende
          lda     PW_Counter
          cmpa    #0T
          beq     Change_Weiter
          
          bset    CHECKED,TOK_Flag
          bset    0,TZUR_Flag
          
FF_Loop
          ; Restliche Variablen mit $FF auffüllen
          lda     PW_Counter
          inca
          sta     PW_Counter
          cmpa    #10T
          beq     Ende_FF
          
          ldhx    #PW_1
          txa
          add     PW_Counter
          tax          
          lda     #$FF
          sta     0,X
          
          bra     FF_Loop         
          
Ende_FF          
          lda     #0T
          sta     PW_Counter  
          rts            
          
          
          
Change_Weiter
         
          ; Tastendruck erkennen 
          lda     #%00000001
          cmpa    T1_Flag
          beq     Change_Druck
          cmpa    T2_Flag
          beq     Change_Druck
          cmpa    T3_Flag
          beq     Change_Druck
          cmpa    T4_Flag
          beq     Change_Druck
          cmpa    T5_Flag
          beq     Change_Druck
          cmpa    T6_Flag
          beq     Change_Druck
          cmpa    T7_Flag
          beq     Change_Druck
          cmpa    T8_Flag
          beq     Change_Druck
          cmpa    T9_Flag
          beq     Change_Druck
          cmpa    T0_Flag
          beq     Change_Druck

          bra     PW_rts
          
Change_Druck

          bset    CHECKED,T1_Flag
          bset    CHECKED,T2_Flag
          bset    CHECKED,T3_Flag
          bset    CHECKED,T4_Flag
          bset    CHECKED,T5_Flag
          bset    CHECKED,T6_Flag
          bset    CHECKED,T7_Flag
          bset    CHECKED,T8_Flag
          bset    CHECKED,T9_Flag
          bset    CHECKED,T0_Flag
          
          jsr     Ausgabe_Stern
          
          ldhx    #PW_1
          txa
          add     PW_Counter
          tax          
          lda     TValue
          sta     0,X
          
          lda     PW_Counter
          inca
          sta     PW_Counter

          rts 
          
          
Ausgabe_Stern 
          
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
            
                  