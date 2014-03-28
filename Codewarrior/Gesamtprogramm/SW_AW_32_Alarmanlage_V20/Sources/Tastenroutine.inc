;************************************************************************************************
;*      TASTENROUTINE_V20                                                                       *
;*                                                                                              *
;*      Revision vom 14. januar 2013                                                            *
;*                                                                                              *
;*      Name:         Valentin Bernrad                                                          *
;*      Klasse:       4AEL                                                                      *
;*      Version:      2.0                                                                       *
;*                                                                                              *
;*      Tastenroutine mit mehreren Tasten und Entprellzeit                                      *
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      T0_Flag       ds      1T                                                                *
;*      T0_Counter    ds      1T                                                                *
;*      T1_Flag       ds      1T                                                                *
;*      T1_Counter    ds      1T                                                                *
;*      T2_Flag       ds      1T                                                                *
;*      T2_Counter    ds      1T                                                                *
;*      T3_Flag       ds      1T                                                                *
;*      T4_Counter    ds      1T                                                                *
;*      T4_Flag       ds      1T                                                                *
;*      T4_Counter    ds      1T                                                                *
;*      T5_Flag       ds      1T                                                                *
;*      T5_Counter    ds      1T                                                                *
;*      T6_Flag       ds      1T                                                                *
;*      T6_Counter    ds      1T                                                                *
;*      T7_Flag       ds      1T                                                                *
;*      T7_Counter    ds      1T                                                                *
;*      T8_Flag       ds      1T                                                                *
;*      T8_Counter    ds      1T                                                                *
;*      T9_Flag       ds      1T                                                                *
;*      T9_Counter    ds      1T                                                                *
;*      TOK_Flag      ds      1T                                                                *
;*      TOK_Counter   ds      1T                                                                *
;*      TUP_Flag      ds      1T                                                                *
;*      TUP_Counter   ds      1T                                                                *
;*      TVOR_Flag     ds      1T                                                                * 
;*      TZUR_Counter  ds      1T                                                                *
;*      TValue        ds      1T                                                                *
;*                                                                                              *    
;*      In Hauptloop kopieren:                                                                  *
;*      jsr     Tastenroutine                                                                   *
;*                                                                                              *                                                                 *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'Tastenroutine.inc'     ; Routine für die Abfrage der Taster                    *
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


ENTPRELLZEIT  EQU     5

PRESSED       EQU     0
CHECKED       EQU     1

;************************************************************************************************
;*                               Programm für die Tasterroutine                                 *
;************************************************************************************************

Tastenroutine 

        lda    #$FF
        sta    TValue   

;Taste 0       
        
        brset  0, PORTF, SetzeT0            ; frage ab ob Taster gedrückt wurde
        
        lda    #0T   
        sta    T0_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T0_Counter      
        bra    T0Ende 
SetzeT0  
        lda    T0_Counter
        inca
        sta    T0_Counter
        cmpa   #ENTPRELLZEIT
        bne    T0Ende
        bset   PRESSED, T0_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$00
        sta    TValue         
        
T0Ende
                        
;Taste 9        
        
        brset  1, PORTF, SetzeT9
        
        lda    #0T   
        sta    T9_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T9_Counter      
        bra    T9Ende 
SetzeT9  
        lda    T9_Counter
        inca
        sta    T9_Counter
        cmpa   #ENTPRELLZEIT
        bne    T9Ende
        bset   PRESSED, T9_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$09
        sta    TValue 
T9Ende
        

        
;Taste 8        
        
        brset  2, PORTF, SetzeT8
        
        lda    #0T   
        sta    T8_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T8_Counter      
        bra    T8Ende 
SetzeT8  
        lda    T8_Counter
        inca
        sta    T8_Counter
        cmpa   #ENTPRELLZEIT
        bne    T8Ende
        bset   PRESSED, T8_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$08
        sta    TValue         
T8Ende
        


;Taste 7        
        
        brset  3, PORTF, SetzeT7
        
        lda    #0T   
        sta    T7_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T7_Counter      
        bra    T7Ende 
SetzeT7  
        lda    T7_Counter
        inca
        sta    T7_Counter
        cmpa   #ENTPRELLZEIT
        bne    T7Ende
        bset   PRESSED, T7_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$07
        sta    TValue         
T7Ende
        


;Taste 6        
        
        brset  4, PORTF, SetzeT6
        
        lda    #0T   
        sta    T6_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T6_Counter      
        bra    T6Ende 
SetzeT6  
        lda    T6_Counter
        inca
        sta    T6_Counter
        cmpa   #ENTPRELLZEIT
        bne    T0Ende
        bset   PRESSED, T6_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$06
        sta    TValue         
T6Ende
        


;Taste 5        
        
        brset  7, PORTF, SetzeT5
        
        lda    #0T   
        sta    T5_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T5_Counter      
        bra    T5Ende 
SetzeT5  
        lda    T5_Counter
        inca
        sta    T5_Counter
        cmpa   #ENTPRELLZEIT
        bne    T5Ende
        bset   PRESSED, T5_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$05
        sta    TValue         
T5Ende
        


;Taste 4        
        
        brset  5, PORTF, SetzeT4
        
        lda    #0T   
        sta    T4_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T4_Counter      
        bra    T4Ende 
SetzeT4  
        lda    T4_Counter
        inca
        sta    T4_Counter
        cmpa   #ENTPRELLZEIT
        bne    T4Ende
        bset   PRESSED, T4_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$04
        sta    TValue         
T4Ende
        


;Taste 3        
        
        brset  6, PORTF, SetzeT3
        
        lda    #0T   
        sta    T3_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T3_Counter      
        bra    T3Ende 
SetzeT3  
        lda    T3_Counter
        inca
        sta    T3_Counter
        cmpa   #ENTPRELLZEIT
        bne    T3Ende
        bset   PRESSED, T3_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$03
        sta    TValue         
T3Ende
        


;Taste 2        
        
        brset  4, PORTD, SetzeT2
        
        lda    #0T   
        sta    T2_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T2_Counter      
        bra    T2Ende 
SetzeT2  
        lda    T2_Counter
        inca
        sta    T2_Counter
        cmpa   #ENTPRELLZEIT
        bne    T2Ende
        bset   PRESSED, T2_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$02
        sta    TValue         
T2Ende
        

;Taste 1        
        
        brset  3, PORTD, SetzeT1
        
        lda    #0T   
        sta    T1_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    T1_Counter      
        bra    T1Ende 
SetzeT1  
        lda    T1_Counter
        inca
        sta    T1_Counter
        cmpa   #ENTPRELLZEIT
        bne    T1Ende
        bset   PRESSED, T1_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$01
        sta    TValue        
T1Ende
        

;Taste VOR        
        
        brset  2, PORTD, SetzeTVOR
        
        lda    #0T   
        sta    TVOR_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    TVOR_Counter      
        bra    TVOREnde 
SetzeTVOR 
        lda    TVOR_Counter
        inca
        sta    TVOR_Counter
        cmpa   #ENTPRELLZEIT
        bne    TVOREnde
        bset   PRESSED, TVOR_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$0A
        sta    TValue         
TVOREnde
        


;Taste OK        
        
        brset  1, PORTD, SetzeTOK
        
        lda    #0T   
        sta    TOK_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    TOK_Counter      
        bra    TOKEnde 
SetzeTOK  
        lda    TOK_Counter
        inca
        sta    TOK_Counter
        cmpa   #ENTPRELLZEIT
        bne    TOKEnde
        bset   PRESSED, TOK_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$0B
        sta    TValue         
TOKEnde
        


;Taste ZUR        
        
        brset  0, PORTD, SetzeTZUR
        
        lda    #0T   
        sta    TZUR_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    TZUR_Counter      
        bra    TZUREnde 
SetzeTZUR  
        lda    TZUR_Counter
        inca
        sta    TZUR_Counter
        cmpa   #ENTPRELLZEIT
        bne    TZUREnde
        bset   PRESSED, TZUR_Flag             ; wenn gedrückt, setze PRESSED-Bit
        lda    #$0C
        sta    TValue         
TZUREnde
        rts

        
        

        
     