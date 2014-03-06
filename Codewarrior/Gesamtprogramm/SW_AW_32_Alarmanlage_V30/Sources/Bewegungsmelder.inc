;************************************************************************************************
;*      AW32-Bewegungsmelder  Version 1.0                                                       *
;*                                                                                              *
;*      Revision vom 10. Januar 2014                                                            *
;*                                                                                              *
;*      Name: Valentin Beranrd                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Auslesen des Bewegungsmelders. Nach 4 Aufeinanderfolgenden High-Pegeln mit nicht        *
;*      mehr als einer Minute Zeit dazwischen wird der Alarm ausgesößt. Erst die 1-minütige     *
;*      Abwesenheit von High-Pegeln resetiert das Bewegungs-Flag wieder, und der Alarm-         *
;*      Countdown kann beginnen.                                                                *
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      Bewegung_Flag    ds   1T                                                                *
;*      Bewegung_Counter ds   2T                                                                *
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr     Bewegungsmelder                                                                 *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'Bewegungsmelder.inc'        ; Routine für das Blicklicht                       *
;*                                                                                              *  
;************************************************************************************************

BEWEGUNG_PIN      EQU     1
BEWEGUNG_PORT     EQU     PORTB
RESET_ZEIT        EQU     6000T

Bewegungsmelder

        brset     BEWEGUNG_PIN,BEWEGUNG_PORT,Setzen
        
        bclr       7,Bewegung_Flag
        
        ldhx      Bewegung_Counter
        incx
        sthx      Bewegung_Counter
        cphx      #RESET_ZEIT
        blo       Ende_Bewegung
        
        clr       Bewegung_Flag
        clr       Bewegung_Counter
               
	      bra	      Ende_Bewegung		

Setzen
        brset     7,Bewegung_Flag,Ende_Bewegung
        bset      7,Bewegung_Flag
            
        brset     0,Bewegung_Flag,Flag_1
        bset      0,Bewegung_Flag
        bra       Ende_Bewegung
Flag_1        
        ;brset     1,Bewegung_Flag,Flag_2
        bset      1,Bewegung_Flag
        ;bra       Ende_Bewegung
;Flag_2        
        ;brset     2,Bewegung_Flag,Flag_3
        bset      2,Bewegung_Flag
        ;bra       Ende_Bewegung
;Flag_3        
        ;brset     3,Bewegung_Flag,Flag_4
        bset      3,Bewegung_Flag
        ;bra       Ende_Bewegung
;Flag_4            
        bset      4,Bewegung_Flag
        bra       Ende_Bewegung  
        
Ende_Bewegung
        
        rts   