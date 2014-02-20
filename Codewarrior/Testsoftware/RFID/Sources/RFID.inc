;************************************************************************************************
;*      AW32-RFID-Programm  Version 1.0                                                        	*
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       			                  *    
;*      Auslesen des RFID-Tags über serielle Schnittstelle                                			*
;*                                                                                              *
;*                                                                                              *
;*      Variabeln:                                                                  		        *
;*      RFID_Tag    ds    2T                                               											*
;*                                                                                              *
;*      Include:                                                                         	      *
;*      INCLUDE RFID.inc                                                   											*
;*                                                                                              *
;*      Eingang:                                                                 	            	*
;*      jsr   Check_RFID											                                                  *
;*                                                                                              *
;*      Init:                                                                       		        *
;*      jsr   Init_RFID 		  	                                                                *
;*                                                                                              *
;************************************************************************************************


Init_RFID
    mov   #%11110100,SPI1C1   ; SPI Aktiviert als Master
;           ||||||||
;           ||||||||_____  Shifter directiom.  0 = 7..0
;           |||||||______  SS Output enable = 0
;           ||||||_______  Clock Pahse, 0 = Middle o. Cycle
;           |||||________  Clock Polarity 0 = Active High
;           ||||_________  MSTR, 1 = Master
;           |||__________  Transmit Interrupt enable
;           ||___________  SPI enable
;           |____________  Interrupt enable

    mov   #%00000000,SPI1C2   
;           ||||||||
;           ||||||||_____  Bidirectional enable
;           |||||||______  SPI Srtop in Wait mode
;           ||||||_______  nc
;           |||||________  Bidirictional, Output enable
;           ||||_________  Mode-Fault enable
;           |||__________  nc
;           ||___________  nc
;           |____________  nc
 
 

    mov   #%01110111,SPI1BR     ; Startet den Timer 1CH2
;           ||||||||
;           ||||||||_____  )
;           |||||||______  > Timer Scaler 2..256 (256)
;           ||||||_______  )
;           |||||________  nc
;           ||||_________  )
;           |||__________  > Timer Prescaler 1..8 (8)
;           ||___________  )
;           |____________  nc

    rts

Check_RFID

      
      
      
      rts
