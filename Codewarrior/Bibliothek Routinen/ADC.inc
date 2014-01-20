;************************************************************************************************
;*      AW32-ADC-Routine  Version 1.0                                                           *
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 4ael                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Ein analoger Eingang, erweiterbar                                                       *
;*                                                                                              *
;*      Variablen:                                                                              *
;*      Pointer_ADC     ds    2T        ;Pointer für den Wandler                                *
;*      Analog_PB0      ds    1T        ;Variable für den Analogwert                            *
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr       Check_ADC                                                                     *
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
;*      ADC_Kanal_PB0: Liest den Kanal PB0 aus (er wurde vorher schon gestartet) und            *
;*      schreibt den Wert in die Variable "Analog_PB0"                                          *
;*                                                                                              *
;************************************************************************************************

ADC_Kanal_PB0
        
        lda     ADC1RL                  ; ADC-Register einlesen
        sta     Analog_PB0              ; in die Variable "Analog_PB0" abspeichern

        mov     #%0000000,ADC1SC1      ; Hier wird der nächste Kanaln ausgewählt 
        
        ;ldhx    #ADC_Kanal_PB1         ;Sringe auf anderen Kanal (optional)
        ;sthx    Pointer_ADC
        rts

