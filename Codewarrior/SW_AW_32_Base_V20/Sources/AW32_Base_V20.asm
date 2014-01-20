;************************************************************************************************
;*      AW32-    -Programm  Version 2.0                                                         *
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 4ael                                                                            *
;*      Version: -.-                                                                            *
;*                                                                                              *
;*      Programmiert auf einem Target mit 4,9152 MHz                                            *
;*      Interner Busclock mit FLL auf 19,6608 MHz hinaufgetaktet                                *
;*      Realtime zu exakt 10 msec                                                               *
;*                                                                                              *
;************************************************************************************************


		XDEF Main_Loop
                ABSENTRY Main_Init

;************************************************************************************************
;*      Speicherdefinitionen                                                                    *
;*                                                                                              *
;************************************************************************************************


ROM_START       EQU     $00008000
ROM_END         EQU     $0000FFAF
Z_RAM_START     EQU     $00000070
Z_RAM_END       EQU     $000000FF
E_RAM_START     EQU     $00000100
E_RAM_END       EQU     $0000086F
VECTOR_START    EQU     $0000FFCC


                INCLUDE 'AW32regs.inc'          ; Register    
                INCLUDE 'Variablen.inc'
                INCLUDE 'Equates.inc'




;************************************************************************************************
;*                                                                                              *
;*      Main_Loop: Die Hauptschleife                                                            *
;*      Sie wird exakt alle 5msec einmal durchlaufen!                                           *
;*                                                                                              *
;************************************************************************************************


                ORG    ROM_START


Main_Loop
                sta     SRS                     ; Watchdog zurücksetzen
                
                lda     TimerFlag               ; TimerFlag = 0 --> Realtime noch nicht um
                beq     Main_Loop               ; TimerFlag <>0 --> Realtime (5 msec) ist um!
                clr     TimerFlag          
                
                
                ; Hier kommen deine Routinen hinein
                
                             
                bra     Main_Loop




;************************************************************************************************
;*                                                                                              *
;*      Es folgen die verschiedensten Includes für die                                          *
;*      SubRoutinen                                                                             *
;*                                                                                              *
;************************************************************************************************


                INCLUDE 'Init.inc'              ; Hier startet der µC / Initialisierungen
                INCLUDE 'Timer.inc'             ; Alles für die Timer (Realtime)
                INCLUDE 'Dummy_Isr.inc'         ; Für fehlgeschlagene (unerwünschte) Interrupts
                INCLUDE 'Vectors.inc'           ; Vektoren usw.
