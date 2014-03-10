;************************************************************************************************
;*      AW32-RFID-Programm  Version 1.0                                                        	*
;*                                                                                              *
;*      Revision vom 21. Oktober 2011                                                           *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       			                  *    
;*      Auslesen des RFID-Tags �ber synchrone serielle Schnittstelle                       			*
;*                                                                                              *
;*                                                                                              *
;*      Variabeln:                                                                  		        *
;*    ??RFID_Tag        ds    2T                                           											*
;*      Counter         ds    1T                                                                *
;*      Adresse         ds    1T                                                                *
;*      Daten           ds    1T                                                                *          
;*                                                                                              *
;*      Include:                                                                         	      *
;*      INCLUDE RFID.inc                                                   											*
;*                                                                                              *
;*      Eingang:                                                                 	            	*
;*      jsr   Check_RFID											                                                  *
;*                                                                                              *
;*      Init:                                                                       		        *
;*      jsr     Init_RFID                                                                       *
;*                                                                                              *
;************************************************************************************************


Init_RFID


  ;//Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
  ;Write_MFRC522(TModeReg, 0x8D);		//Tauto=1; f(Timer) = 6.78MHz/TPreScaler
  ;Write_MFRC522(TPrescalerReg, 0x3E);	//TModeReg[3..0] + TPrescalerReg
  ;Write_MFRC522(TReloadRegL, 30);           
  ;Write_MFRC522(TReloadRegH, 0);

  ;Write_MFRC522(TxAutoReg, 0x40);		//100%ASK
  ;Write_MFRC522(ModeReg, 0x3D);		//CRC initilizate value 0x6363	???

    lda     TModeReg
    sta     Adresse
    lda     #$8D
    sta     Daten
    jsr     Write_RFID
    
    lda     TPrescalerReg
    sta     Adresse
    lda     #$3E
    sta     Daten
    jsr     Write_RFID
    
    lda     TReloadRegL
    sta     Adresse
    lda     #30T
    sta     Daten
    jsr     Write_RFID
 
    lda     TReloadRegH
    sta     Adresse
    lda     #$0
    sta     Daten
    jsr     Write_RFID

    lda     TxAutoReg
    sta     Adresse
    lda     #$40
    sta     Daten
    jsr     Write_RFID

    lda     ModeReg
    sta     Adresse
    lda     #$3D
    sta     Daten
    jsr     Write_RFID
      
    ; Antenne aktivieren
    lda     #TxControlReg
    sta     Adresse
    jsr     Read_RFID 
    lda     Daten   
    ORA     #%0000011
    sta     Daten
    jsr     Write_RFID

    rts
        

Check_RFID

    ;   MFRC5522_Request
    
    lda     Counter
    cmpa    #0T
    bne     Waiting
    
    lda     #BitFramingReg
    sta     Adresse
    lda     #$07
    sta     Daten
    jsr     Write_RFID
    
    lda     #CommIEnReg
    sta     Adresse
    lda     #$77
    ORA     #$80
    sta     Daten
    jsr     Write_RFID
    
    lda     #CommIrqReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    AND     #%01111111
    sta     Daten
    jsr     Write_RFID
    
    lda     #FIFOLevelReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    ORA     #$80
    sta     Daten
    jsr     Write_RFID
       
    lda     #CommandReg
    sta     Adresse
    lda     #PCD_IDLE
    sta     Daten
    jsr     Write_RFID
    
    lda     #FIFODataReg
    sta     Adresse
    lda     #PICC_REQALL
    sta     Daten
    jsr     Write_RFID
    
    lda     #CommandReg
    sta     Adresse
    lda     #PCD_TRANSCEIVE
    sta     Daten
    jsr     Write_RFID
    
    lda     #BitFramingReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    ORA     #$80
    sta     Daten
    jsr     Write_RFID
    
Waiting

    lda     Counter
    inca
    sta     Counter
    cmpa    #3T
    blo     Ende_RFID
    
    lda     #0T
    sta     Counter
    
    lda     BitFramingReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    sta     Counter
    
    lda     #BitFramingReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    AND     #%01111111
    sta     Daten
    jsr     Write_RFID
    
    lda     ErrorReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    cmpa    #$1B
    beq     Ende_RFID
    
    lda     Counter
    AND     #$77
    AND     #$01
    cmpa    #1T
    beq     Ende_RFID
    
    ;an dieser Stelle Sollte ein Tag vorhanen sein?
    
    lda     #$FF
    sta     RFID_Flag

      
Ende_RFID
   
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
    
    lda     SPI1D
    sta     Daten 
        
    rts    
