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
;*      TasteA_Flag     ds      1T                                                              *
;*      TasteA_Counter  ds      1T                                                              *
;*      TasteB_Flag     ds      1T                                                              *
;*      TasteB_Counter  ds      1T                                                              *
;*      TasteC_Flag     ds      1T                                                              *
;*      TasteC_Counter  ds      1T                                                              *
;*                                                                                              *
;*      In Hauptloop kopieren:                                                                  *
;*      jsr     Tastenroutine                                                                   *
;*                                                                                              *                                                                 *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'tasterroutine.inc'     ; Routine für die Abfrage der Taster                    *
;*                                                                                              *
;************************************************************************************************

ENTPRELLZEIT  EQU     5

TASTERPORT    EQU     PORTF

PRESSED       EQU     0
CHECKED       EQU     1

;************************************************************************************************
;*                               Programm für die Tasterroutine                                 *
;************************************************************************************************

Tastenroutine 

;Taste A       
        
        brset  0, TASTERPORT, SetzeA            ; frage ab ob Taster gedrückt wurde
        
        lda    #0T   
        sta    TasteA_Flag                      ; wenn nicht gedrückt, lösche ganzes Byte
        sta    TasteA_Counter      
        bra    TasteAEnde 
SetzeA  
        lda    TasteA_Counter
        inca
        sta    TasteA_Counter
        cmpa   #ENTPRELLZEIT
        bne    TasteAEnde
        bset   PRESSED, TasteA_Flag             ; wenn gedrückt, setze PRESSED-Bit
        
TasteAEnde
        ; rts                           
        
;Taste B        
        
        brset  1, TASTERPORT, SetzeB
        
        lda    #0T   
        sta    TasteB_Flag
        sta    TasteB_Counter      
        bra    TasteBEnde 
SetzeB
        lda    TasteB_Counter
        inca
        sta    TasteB_Counter
        cmpa   #ENTPRELLZEIT
        bne    TasteBEnde
        bset   PRESSED, TasteB_Flag
        
TasteBEnde
        ;rts
        
;Taste C        
        
        brset  2, TASTERPORT, SetzeC
        
        lda    #0T   
        sta    TasteC_Flag
        sta    TasteC_Counter      
        bra    TasteCEnde 
SetzeC
        lda    TasteC_Counter
        inca
        sta    TasteC_Counter
        cmpa   #ENTPRELLZEIT
        bne    TasteCEnde
        bset   PRESSED, TasteC_Flag
        
TasteCEnde
        rts        
        

        
        

        
     