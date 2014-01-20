;************************************************************************************************
;*      AW32-Bewegungsmelder  Version 1.0                                                       *
;*                                                                                              *
;*      Revision vom 10. Januar 2014                                                            *
;*                                                                                              *
;*      Name: Valentin Beranrd                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Auslesen des Bewegungsmelders                                                           *
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      Bewegung_Flag    ds  1T                                                                 *
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr     Blinklicht                                                                      *
;*                                                                                              *
;*      In Init kopieren:                                                                       *
;*      jsr   Init_Blinklicht                                                                   *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'Bewegungsmelder.inc'        ; Routine für das Blicklicht                       *
;************************************************************************************************

BEWEGUNG_PIN     EQU     4
BEWEGUNG_PORT    EQU     PORTF

Bewegungsmelder

        brclr     BEWEGUNG_PIN,BEWEGUNG_PORT,Ende_Bewegung
        
        bset      0,Bewegung_Flag
        
Ende_Bewegung
        
        clr       Bewegung_Flag
        rts   