Check_RFID

    lda     #TestBusReg
    sta     Adresse
    lda     #%11111111
    sta     Daten
    jsr     Write_RFID
    
    lda     #TestBusReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten

 rts




;***** Sende Daten *******************************************************************************    

Write_RFID

    lda     Adresse
    lsla
    AND     #%01111110    
    sta     SPI1D
    
S1Delay 
    brclr   7,SPI1S,S1Delay
    
    lda     Daten
    sta     SPI1D

S2Delay 
    brclr   7,SPI1S,S2Delay    
        
    rts
  
;***** Empfange Daten ****************************************************************************  
    
Read_RFID

    lda     Adresse
    lsla
    AND     #%11111110
    ORA     #%10000000    
    sta     SPI1D
    
S3Delay
    brclr    7,SPI1S,S3Delay
    
    lda     #$00
    sta     SPI1D
    
S4Delay
    brclr    7,SPI1S,S4Delay    
    
    sta     Daten 
        
    rts    

