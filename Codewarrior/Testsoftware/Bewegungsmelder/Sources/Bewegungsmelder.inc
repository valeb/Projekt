;************************************************************************************************
;*      AW32- Bewegungsmelder-Programm  Version 1.0                                            	*
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       			                  *
;*      Bewegungsmelder an Port D1, Blinklicht                                                  *
;*                                                                                              *
;*                                                                                              *
;*      Variabeln:                                                                  		*
;*      											*
;*      											*
;*                                                                                              *
;*      Include:                                                                         	*
;*      											*
;*                                                                                              *
;*      Eingang:                                                                 	 	*
;*      											*
;*                                                                                              *
;*      Init:                                                                       		*
;*      			                                                                *
;*                                                                                              *
;************************************************************************************************


Bewegungsmelder

    brset   1,PORTB,Setzen
    bclr    6,PORTD
    bra     Ende
Setzen
            
    bset    6,PORTD
    bra     Ende
      
Ende
      rts      