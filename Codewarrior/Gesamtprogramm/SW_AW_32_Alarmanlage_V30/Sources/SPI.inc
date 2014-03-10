;************************************************************************************************
;*      AW32-RFID-Programm  Version 1.0                                                        	*
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       			                  *    
;*      Synchrone serielle Schnittstelle                       			                            *
;*                                                                                              *
;*      Include:                                                                         	      *
;*      INCLUDE 'SPI.inc'                                                   										*
;*                                                                                              *
;*      Init:                                                                       		        *
;*      jsr     Init_SPI 		                                                                    *
;*                                                                                              *
;************************************************************************************************


Init_SPI
    mov   #%01010100,SPI1C1   ; SPI Aktiviert als Master
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
;           |||||||______  SPI Stop in Wait mode
;           ||||||_______  nc
;           |||||________  Bidirectional, Output enable
;           ||||_________  Mode-Fault enable
;           |||__________  nc
;           ||___________  nc
;           |____________  nc
 
 

    mov   #%01110100,SPI1BR     ; Stellt den SPI_Clock ein
;           ||||||||
;           ||||||||_____  )
;           |||||||______  > Timer Scaler 2..256 (32)
;           ||||||_______  )
;           |||||________  nc
;           ||||_________  )
;           |||__________  > Timer Prescaler 1..8 (8)
;           ||___________  )
;           |____________  nc

    rts
    
SPI_Clock

    pshh
    
    lda   #%01110111    
    sta   SPI1BR
    
    pulh 
    
    rti   
    