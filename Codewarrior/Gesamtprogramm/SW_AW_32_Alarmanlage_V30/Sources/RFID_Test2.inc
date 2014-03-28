Check_RFID

    lda     #CommandReg
    sta     Adresse
    lda     #%10101010
    sta     Daten
    jsr     Write_RFID
    
    lda     #CommandReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    

    rts




;***** Sende Daten *******************************************************************************    

Write_RFID

    brclr   5,SPI1S,Ende_RW

    
    lda     Adresse
    lsla
    AND     #%01111110    
    sta     SPI1D

    bclr    3,PORTE
    
S1Delay 
    brclr   7,SPI1S,S1Delay
    
    lda     SPI1D
    
    lda     Daten

    sta     SPI1D

S2Delay 
    brclr   7,SPI1S,S2Delay
    
    lda     SPI1D
    
    bset    3,PORTE
    
Ende_RW    
        
    rts
  
;***** Empfange Daten ****************************************************************************  
    
Read_RFID

    brclr   5,SPI1S,Ende_RW    
        
    lda     Adresse
    lsla
    AND     #%01111110
    ORA     #%10000000 

    sta     SPI1D
    
    bclr    3,PORTE
    
S3Delay
    brclr    7,SPI1S,S3Delay
    
    lda     SPI1D
    
    lda     #$00

    sta     SPI1D
    
S4Delay
    brclr    7,SPI1S,S4Delay
    
    lda     SPI1D

    sta     Daten    
    bset    3,PORTE     
        
    rts    

