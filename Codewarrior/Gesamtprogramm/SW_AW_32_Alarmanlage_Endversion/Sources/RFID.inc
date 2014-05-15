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

    ;Reset Durchführen
    lda     #CommandReg
    sta     Adresse
    lda     #PCD_RESETPHASE
    sta     Daten
    jsr     Write_RFID  
    
    lda     #TModeReg
    sta     Adresse
    lda     #$8D
    sta     Daten
    jsr     Write_RFID
    lda     #TModeReg
    sta     Adresse
    jsr     Read_RFID 
    
    lda     #TPrescalerReg
    sta     Adresse
    lda     #$3E
    sta     Daten
    jsr     Write_RFID
    
    lda     #TReloadRegL
    sta     Adresse
    lda     #30T
    sta     Daten
    jsr     Write_RFID
 
    lda     #TReloadRegH
    sta     Adresse
    lda     #$0
    sta     Daten
    jsr     Write_RFID

    lda     #TxAutoReg
    sta     Adresse
    lda     #$40
    sta     Daten
    jsr     Write_RFID

    lda     #ModeReg
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
    
    lda     #TxControlReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    

    rts        

Check_RFID

    ;   MFRC5522_Request
    
    lda     Counter
    cmpa    #0T
    beq     No_Transfer
    jmp     Transfer

No_Transfer    
    
    lda     #BitFramingReg
    sta     Adresse
    lda     #$07
    sta     Daten
    jsr     Write_RFID
    
    ; MFRC5522_ToCard
     
    lda     #CommIEnReg           ;Interrupts erlauben
    sta     Adresse               
    lda     #$77
    ORA     #$80
    sta     Daten
    jsr     Write_RFID
    
    lda     #CommIrqReg           ;Alle Interrupt-Bits löschen
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    AND     #%01111111
    sta     Daten
    jsr     Write_RFID
    
    lda     #FIFOLevelReg         ;Buffer Initialisieren
    sta     Adresse               ;Flush-Buffer Pin
    jsr     Read_RFID
    lda     Daten
    ORA     #$80
    sta     Daten
    jsr     Write_RFID
       
    lda     #CommandReg           ;Derzeitiges Kommando Unterbrecehn
    sta     Adresse
    lda     #PCD_IDLE
    sta     Daten
    jsr     Write_RFID
    
    lda     #FIFODataReg          ;Daten in Buffer schreiben
    sta     Adresse               
    lda     #PICC_REQALL          ;Nach allen Tags suchen
    sta     Daten
    jsr     Write_RFID
    
    lda     #CommandReg           ;FIFO-Buffer hinaussenden 
    sta     Adresse
    lda     #PCD_TRANSCEIVE       ;Senden-und-Empfangen Befehl
    sta     Daten
    jsr     Write_RFID
    
    lda     #BitFramingReg        ;StartSend_Bit auf 1 setzen
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    ORA     #$80
    sta     Daten
    jsr     Write_RFID
    
Transfer

        
    lda     #CommIrqReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    sta     Status
    
    lda     Status        ;Check Timer_IRQ
    AND     #$01
    cmpa    #$01
    beq     Ende_Transfer
    
    lda     Status        ;Check Idle_IRQ 
    AND     #$10
    cmpa    #$10
    beq     Ende_Transfer
    
    lda     Status        ;Check Rx_IRQ
    AND     #$20
    cmpa    #$20
    beq     Ende_Transfer
    
    lda     Counter
    inca
    sta     Counter    
    cmpa    #3T
    bls     Ende_RFID



Ende_Transfer
    lda     #BitFramingReg        ;StartSend_Bit auf 0 setzen
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    AND     #%01111111
    sta     Daten
    jsr     Write_RFID 
    
    lda     Counter               
    cmpa    #4T
    beq     Ende_RFID
    lda     #0T
    sta     Counter        

    lda     #ErrorReg              ;Check 4 versch. Error-Flags
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    AND     #$1B
    cmpa    #$1B
    beq     Ende_RFID
    cmpa    #$10
    beq     Ende_RFID
    cmpa    #$0B
    beq     Ende_RFID
    cmpa    #$08
    beq     Ende_RFID
    cmpa    #$03
    beq     Ende_RFID
    cmpa    #$02
    beq     Ende_RFID
    cmpa    #$01
    beq     Ende_RFID
    
    lda     Status                ;Check Timer_IRQ
    AND     #$01                        
    cmpa    #$01
    beq     Ende_RFID
    
    ;an dieser Stelle sollte ein Tag vorhanen sein
    
    lda     #$FF
    sta     RFID_Flag

      
Ende_RFID
   
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
  
