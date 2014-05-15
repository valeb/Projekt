;************************************************************************************************
;*      AW32-Alarmanlage Endversion                                                             *
;*                                                                                              *
;*      Revision vom 13. Dezember 2013                                                          *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5ael                                                                            *
;*      Version: 1.0                                                                            *
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
                INCLUDE 'MFRC522regs.inc'    
                
                INCLUDE 'Variablen.inc'




;************************************************************************************************
;*                                                                                              *
;*      Main_Loop: Die Hauptschleife                                                            *
;*      Sie wird exakt alle 10msec einmal durchlaufen!                                          *
;*                                                                                              *
;************************************************************************************************


                ORG    ROM_START


Main_Loop
                sta     SRS                     ; Watchdog zurücksetzen
                
                lda     TimerFlag               ; TimerFlag = 0 --> Realtime noch nicht um
                beq     Main_Loop               ; TimerFlag <>0 --> Realtime (5 msec) ist um!
                clr     TimerFlag           
                
                ; Eigene Routinen
                
                jsr     Tastenroutine 
                jsr     Menue
                jsr     Update_LCD                              
                             
                bra     Main_Loop




;************************************************************************************************
;*                                                                                              *
;*      Es folgen die verschiedensten Includes für die                                          *
;*      SubRoutinen                                                                             *
;*                                                                                              *
;************************************************************************************************

                INCLUDE 'Menue.inc'             ; Routine für das Menü 
                INCLUDE 'LCD_Disp_8bit.inc'     ; Routine für das LCD Display
                INCLUDE 'Tastenroutine.inc'     ; Routine für die Abfrage der Taster
                INCLUDE 'Timerinterrupt_V20.inc'; Timerinterrupt für die Tonausgabe
                INCLUDE 'Alarmton_LUT.inc'      ; Tonausgabe
                INCLUDE 'Blinklichter.inc'      ; Routine für das Blicklicht
                INCLUDE 'Bewegungsmelder.inc'   ; Bewegungsmelder auslesen
                INCLUDE 'Passwort.inc'          ; Routine zur Passworteingabe
                INCLUDE 'SPI.inc'               ; SPI Initialisierung
                INCLUDE 'RFID.inc'              ; RFID-Tag Erkennung
                INCLUDE 'Ausgabe.inc'          ; Alle Ausgaben
                

                INCLUDE 'Init.inc'              ; Hier startet der µC / Initialisierungen
                INCLUDE 'Realtime_T1CH0.inc'    ; Alles für die Timer (Realtime)
                INCLUDE 'Dummy_Isr.inc'         ; Für fehlgeschlagene (unerwünschte) Interrupts
                INCLUDE 'Vectors.inc'           ; Vektoren usw.
