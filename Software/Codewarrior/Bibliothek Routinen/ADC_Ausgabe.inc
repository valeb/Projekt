;************************************************************************************************
;*      AW32-ADC-Routine  Version 2.0                                                           *
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 4ael                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Alle 4 analogen Eingänge, mit Ausgabe                                                   *
;*                                                                                              *
;*      Variablen:                                                                              *
;*      Pointer_ADC     ds    2T        ;Pointer für den Wandler                                *
;*      Analog_PB0      ds    1T        ;Variable für den Analogwert                            *
;*      Analog_PB1      ds    1T        ;Variable für den Analogwert                            *
;*      Analog_PB2      ds    1T        ;Variable für den Analogwert                            *
;*      Analog_PB3      ds    1T        ;Variable für den Analogwert                            *
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr       Check-ADC                                                                     *
;*                                                                                              *
;*      ASM:                                                                                    *
;*      INCLUDE 'ADC.inc'                                                                       *
;*                                                                                              *
;*      Programmiert auf einem Target mit 4,9152 MHz                                            *
;*      Interner Busclock mit FLL auf 19,6608 MHz hinaufgetaktet                                *
;*      Realtime zu exakt 10 msec                                                               *
;*                                                                                              *
;************************************************************************************************

Init_ADC

        ldhx    #ADC_Kanal_PB0
        sthx    Pointer_ADC             ; Pointer auf PB0 setzen
        
        mov     #%10010000,ADC1CFG      ; Wandlergeschwindigkeit, 8 Bit Mode etc.
        mov     #%00000000,ADC1SC2      ; Keine Compare-Funktion, Software-Trigger
        mov     #%11111111,APCTL1       ; Pins rein Analog
        mov     #%00000000,ADC1SC1      ; PB0 soll gewandelt werden

        rts
                
;************************************************************************************************
;*                                                                                              *
;*      Check_ADC: Diese Routine wird vom Main-Loop                                             *
;*      angesprungen --> Im Prinzip wird hier nur zum aktuellen Kanal weitergeleitet            *
;*                                                                                              *
;************************************************************************************************

Check_ADC
        ldhx    Pointer_ADC
        jsr     0,X
        rts
        
;************************************************************************************************
;*                                                                                              *
;*      ADC_Kanal_PB0 - ADC_Kanal_PB3: Liest den Kanal aus (er wurde vorher schon gestartet)    *
;*      und schreibt den Wert in die Variable "Analog_PB(0-3)"                                      *
;*                                                                                              *
;************************************************************************************************

ADC_Kanal_PB0
        
        lda     ADC1RL                  ; ADC-Register einlesen
        sta     Analog_PB0              ; in die Variable "Analog_PB0" abspeichern

        mov     #%00000001,ADC1SC1      ; Hier wird der nächste Kanaln ausgewählt 
        
        jsr     Ausgabe1                ;Springe zur Ausgabe
        
        ldhx    #ADC_Kanal_PB1          ;Sringe auf anderen Kanal (optional)
        sthx    Pointer_ADC
        rts
        
ADC_Kanal_PB1
        
        lda     ADC1RL                  ; ADC-Register einlesen
        sta     Analog_PB1              ; in die Variable "Analog_PB1" abspeichern

        mov     #%00000010,ADC1SC1      ; Hier wird der nächste Kanaln ausgewählt 
        
        jsr     Ausgabe2                ;Springe zur Ausgabe
        
        ldhx    #ADC_Kanal_PB2          ;Sringe auf anderen Kanal (optional)
        sthx    Pointer_ADC
        rts

ADC_Kanal_PB2
        
        lda     ADC1RL                  ; ADC-Register einlesen
        sta     Analog_PB2              ; in die Variable "Analog_PB2" abspeichern

        mov     #%00000011,ADC1SC1      ; Hier wird der nächste Kanaln ausgewählt 
        
        jsr     Ausgabe3                ;Springe zur Ausgabe
        
        ldhx    #ADC_Kanal_PB3          ;Sringe auf anderen Kanal (optional)
        sthx    Pointer_ADC
        rts

ADC_Kanal_PB3
        
        lda     ADC1RL                  ; ADC-Register einlesen
        sta     Analog_PB3              ; in die Variable "Analog_PB3" abspeichern

        mov     #%00000000,ADC1SC1      ; Hier wird der nächste Kanaln ausgewählt 
        
        jsr     Ausgabe4                ;Springe zur Ausgabe
        
        ldhx    #ADC_Kanal_PB0          ;Sringe auf anderen Kanal (optional)
        sthx    Pointer_ADC
        rts                
                                
Ausgabe1
       
       ;Ausgabe_Text (auch in Init möglich)

       ldhx    #Text
       sthx    SourcePointer
       ldhx    #LCD_Oben
       sthx    DestPointer
       lda     #16T
       sta     TextLenght
     
       jsr     CopyText
       
       
       
       ldhx     #LCD_Unten
       sthx     DestPointer                         
       lda      Analog_PB0
       
       jsr      DezimalBCD
       
       rts 
       
Ausgabe2
       
       ldhx     #LCD_Unten+4
       sthx     DestPointer                         
       lda      Analog_PB1
       
       jsr      DezimalBCD
       
       rts 
      
Ausgabe3
       
       ldhx     #LCD_Unten+8
       sthx     DestPointer                         
       lda      Analog_PB2
       
       jsr      DezimalBCD
       
       rts 
       
Ausgabe4
       
       ldhx     #LCD_Unten+12
       sthx     DestPointer                         
       lda      Analog_PB3
       
       jsr      DezimalBCD
       
       rts 
       
Text
                ;----------------;
      dc.b      'PT1 PT2 PT3 PT4 '                               
        
