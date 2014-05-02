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
    lda     #$80
    sta     Daten
    jsr     Write_RFID
    
    lda     #TPrescalerReg
    sta     Adresse
    lda     #$A9
    sta     Daten
    jsr     Write_RFID
    
    lda     #TReloadRegL
    sta     Adresse
    lda     #$E8
    sta     Daten
    jsr     Write_RFID
 
    lda     #TReloadRegH
    sta     Adresse
    lda     #$03
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
    ORA     #$03
    sta     Daten
    jsr     Write_RFID

    rts        

Check_RFID

;bool MFRC522::PICC_IsNewCardPresent() {
;byte bufferATQA[2];
;byte bufferSize = sizeof(bufferATQA);
;byte result = PICC_RequestA(bufferATQA, &bufferSize);
;return (result == STATUS_OK || result == STATUS_COLLISION);
;} // End PICC_IsNewCardPresent() 


;byte MFRC522::PICC_RequestA(byte *bufferATQA,	///< The buffer to store the ATQA (Answer to request) in
;byte *bufferSize	///< Buffer size, at least two bytes. Also number of bytes returned if STATUS_OK.
;) {
;return PICC_REQA_or_WUPA(PICC_CMD_REQA, bufferATQA, bufferSize);
;} // End PICC_RequestA()


;byte MFRC522::PICC_REQA_or_WUPA(	byte command, ///< The command to send - PICC_CMD_REQA or PICC_CMD_WUPA
;byte *bufferATQA,	///< The buffer to store the ATQA (Answer to request) in
;byte *bufferSize	///< Buffer size, at least two bytes. Also number of bytes returned if STATUS_OK.
;) {
;byte validBits;
;byte status;
;
;if (bufferATQA == NULL || *bufferSize < 2) {	// The ATQA response is 2 bytes long.
;return STATUS_NO_ROOM;
;}
;PCD_ClearRegisterBitMask(CollReg, 0x80);	// ValuesAfterColl=1 => Bits received after collision are cleared.
;validBits = 7;	// For REQA and WUPA we need the short frame format - transmit only 7 bits of the last (and only) byte. TxLastBits = BitFramingReg[2..0]
;status = PCD_TransceiveData(&command, 1, bufferATQA, bufferSize, &validBits);
;if (status != STATUS_OK) {
;return status;
;}
;if (*bufferSize != 2 || validBits != 0) {	// ATQA must be exactly 16 bits.
;return STATUS_ERROR;
;}
;return STATUS_OK;
;} // End PICC_REQA_or_WUPA()


;byte MFRC522::PCD_TransceiveData(	byte *sendData,	///< Pointer to the data to transfer to the FIFO.
;byte sendLen,	///< Number of bytes to transfer to the FIFO.
;byte *backData,	///< NULL or pointer to buffer if data should be read back after executing the command.
;byte *backLen,	///< In: Max number of bytes to write to *backData. Out: The number of bytes returned.
;byte *validBits,	///< In/Out: The number of valid bits in the last byte. 0 for 8 valid bits. Default NULL.
;byte rxAlign,	///< In: Defines the bit position in backData[0] for the first bit received. Default 0.
;bool checkCRC	///< In: True => The last two bytes of the response is assumed to be a CRC_A that must be validated.
;) {
;byte waitIRq = 0x30;	// RxIRq and IdleIRq
;return PCD_CommunicateWithPICC(PCD_Transceive, waitIRq, sendData, sendLen, backData, backLen, validBits, rxAlign, checkCRC);
;} // End PCD_TransceiveData()


;byte MFRC522::PCD_CommunicateWithPICC(	byte command,	///< The command to execute. One of the PCD_Command enums.
;byte waitIRq,	///< The bits in the ComIrqReg register that signals successful completion of the command.
;byte *sendData,	///< Pointer to the data to transfer to the FIFO.
;byte sendLen,	///< Number of bytes to transfer to the FIFO.
;byte *backData,	///< NULL or pointer to buffer if data should be read back after executing the command.
;byte *backLen,	///< In: Max number of bytes to write to *backData. Out: The number of bytes returned.
;byte *validBits,	///< In/Out: The number of valid bits in the last byte. 0 for 8 valid bits.
;byte rxAlign,	///< In: Defines the bit position in backData[0] for the first bit received. Default 0.
;bool checkCRC	///< In: True => The last two bytes of the response is assumed to be a CRC_A that must be validated.
;) {
;byte n, _validBits;
;unsigned int i;
;
;// Prepare values for BitFramingReg
;byte txLastBits = validBits ? *validBits : 0;
;byte bitFraming	= (rxAlign << 4) + txLastBits;	// RxAlign = BitFramingReg[6..4]. TxLastBits = BitFramingReg[2..0]

;PCD_WriteRegister(CommandReg, PCD_Idle);	// Stop any active command.
;PCD_WriteRegister(ComIrqReg, 0x7F);	// Clear all seven interrupt request bits
;PCD_SetRegisterBitMask(FIFOLevelReg, 0x80);	// FlushBuffer = 1, FIFO initialization
;PCD_WriteRegister(FIFODataReg, sendLen, sendData);	// Write sendData to the FIFO
;PCD_WriteRegister(BitFramingReg, bitFraming);	// Bit adjustments
;PCD_WriteRegister(CommandReg, command);	// Execute the command
;if (command == PCD_Transceive) {
;PCD_SetRegisterBitMask(BitFramingReg, 0x80);	// StartSend=1, transmission of data starts
;}

;// Wait for the command to complete.
;// In PCD_Init() we set the TAuto flag in TModeReg. This means the timer automatically starts when the PCD stops transmitting.
;// Each iteration of the do-while-loop takes 17.86?s.
;i = 2000;
;while (1) {
;n = PCD_ReadRegister(ComIrqReg);	// ComIrqReg[7..0] bits are: Set1 TxIRq RxIRq IdleIRq HiAlertIRq LoAlertIRq ErrIRq TimerIRq
;if (n & waitIRq) {	// One of the interrupts that signal success has been set.
;break;
;}
;if (n & 0x01) {	// Timer interrupt - nothing received in 25ms
;return STATUS_TIMEOUT;
;}
;if (--i == 0) {	// The emergency break. If all other condions fail we will eventually terminate on this one after 35.7ms. Communication with the MFRC522 might be down.
;return STATUS_TIMEOUT;
;}
;}

;// Stop now if any errors except collisions were detected.
;byte errorRegValue = PCD_ReadRegister(ErrorReg); // ErrorReg[7..0] bits are: WrErr TempErr reserved BufferOvfl CollErr CRCErr ParityErr ProtocolErr
;if (errorRegValue & 0x13) {	// BufferOvfl ParityErr ProtocolErr
;return STATUS_ERROR;
;}	
;
;// If the caller wants data back, get it from the MFRC522.
;if (backData && backLen) {
;n = PCD_ReadRegister(FIFOLevelReg);	// Number of bytes in the FIFO
;if (n > *backLen) {
;return STATUS_NO_ROOM;
;}
;*backLen = n;	// Number of bytes returned
;PCD_ReadRegister(FIFODataReg, n, backData, rxAlign);	// Get received data from FIFO
;_validBits = PCD_ReadRegister(ControlReg) & 0x07;	// RxLastBits[2:0] indicates the number of valid bits in the last received byte. If this value is 000b, the whole byte is valid.
;if (validBits) {
;*validBits = _validBits;
;}
;}
;
;// Tell about collisions
;if (errorRegValue & 0x08) { // CollErr
;return STATUS_COLLISION;
;}

;// Perform CRC_A validation if requested.
;if (backData && backLen && checkCRC) {
;// In this case a MIFARE Classic NAK is not OK.
;if (*backLen == 1 && _validBits == 4) {
;return STATUS_MIFARE_NACK;
;}
;// We need at least the CRC_A value and all 8 bits of the last byte must be received.
;if (*backLen < 2 || _validBits != 0) {
;return STATUS_CRC_WRONG;
;}
;// Verify CRC_A - do our own calculation and store the control in controlBuffer.
;byte controlBuffer[2];
;n = PCD_CalculateCRC(&backData[0], *backLen - 2, &controlBuffer[0]);
;if (n != STATUS_OK) {
;return n;
;}
;if ((backData[*backLen - 2] != controlBuffer[0]) || (backData[*backLen - 1] != controlBuffer[1])) {
;return STATUS_CRC_WRONG;
;}
;}

;return STATUS_OK;
;} // End PCD_CommunicateWithPICC(


    lda     CollReg
    sta     Adresse
    jsr     Read_RFID
    lda     Daten
    ORA     #$80

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

