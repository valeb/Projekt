;************************************************************************************************
;*      AW32-RFID-Programm  Version 1.0                                                        	*
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       			                  *    
;*      Auslesen des RFID-Tags über synchrone serielle Schnittstelle                       			*
;*                                                                                              *
;*                                                                                              *
;*      Variabeln:                                                                  		        *
;*      RFID_Flag     ds    2T                                             											*
;*      TempVar       ds    1T                                                                  *
;*                                                                                              *
;*      Include:                                                                         	      *
;*      INCLUDE RFID.inc                                                   											*
;*                                                                                              *
;*      Eingang:                                                                 	            	*
;*      jsr   Check_RFID											                                                  *
;*                                                                                              *
;*      Init:                                                                       		        *
;*      jsr     Init_SPI 		                                                                    *
;*      jsr     Init_RFID                                                                       *
;*                                                                                              *
;************************************************************************************************


Init_SPI
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
;           |||||||______  SPI Stop in Wait mode
;           ||||||_______  nc
;           |||||________  Bidirectional, Output enable
;           ||||_________  Mode-Fault enable
;           |||__________  nc
;           ||___________  nc
;           |____________  nc
 
 

    mov   #%01110111,SPI1BR     ; Stellt den SPI_Clock ein
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
    
SPI_Clock

    pshh
    
    lda   #%01110111    
    sta   SPI1BR
    
    pulh 
    
    rti   
    
    
Init_RFID

    ;   Antenne aktivieren
    lda     #TxControlReg
    lsla
    AND     #%1111110
    ORA     #%1000000 
    
    sta     SPI1D
     
S1Delay

    brclr    7,SPI1S,S1Delay
    
    lda     SPI1D
   
    ORA     #%0000011
    
    sta     TempVar
    
    lda     #TxControlReg
    lsla
    AND     #%0111110
    
    sta     SPI1D
    
S2Delay

    brclr   7,SPI1S,S2Delay
    
    lda     TempVar
    sta     SPI1D
    
S3Delay

    brclr   7,SPI1S,S3Delay
    
    bclr    6,SPI1C1    
         
    rts
        

Check_RFID

    ;   MFRC5522_Request
    ;   Status = Ok ?
    ;   Ausgeben Karte entdeckt
      
      
    rts
