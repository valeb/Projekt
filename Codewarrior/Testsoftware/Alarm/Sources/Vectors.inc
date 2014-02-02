;************************************************************************************************
;*                                                                                              *
;*                 Interrupt Vectoren                                                           *
;*                                                                                              *
;************************************************************************************************

                ORG   VECTOR_START


                DC.W    Realtime        ; $FFCC+$FFCD   Vector RTI
                DC.W    Dummy_ISR       ; $FFCE+$FFCF   Vector IIC1
                DC.W    Dummy_ISR       ; $FFD0+$FFD1   Vector ADC1
                DC.W    Dummy_ISR       ; $FFD2+$FFD3   Vector KEYBOARD
                DC.W    Dummy_ISR       ; $FFD4+$FFD5   Vector SCI2_TX
                DC.W    Dummy_ISR       ; $FFD6+$FFD7   Vector SCI2_RX
                DC.W    Dummy_ISR       ; $FFD8+$FFD9   Vector SCI2_ERR
                DC.W    Dummy_ISR       ; $FFDA+$FFDB   Vector SCI1_TX
                DC.W    Dummy_ISR       ; $FFDC+$FFDC   Vector SCI1_RX
                DC.W    Dummy_ISR       ; $FFDE+$FFDF   Vector SCI1_ERR
                DC.W    Dummy_ISR       ; $FFE0+$FFE1   Vector SPI1
                DC.W    Dummy_ISR       ; $FFE2+$FFE3   Vector TPM2OVF                
                DC.W    Dummy_ISR       ; $FFE4+$FFE5   Vector TMP2CH1                
                DC.W    Dummy_ISR       ; $FFE6+$FFE7   Vector TPM2CH0                
                DC.W    Dummy_ISR       ; $FFE8+$FFE9   Vector TPM1OVF                
                DC.W    Timer_Over      ; $FFEA+$FFEB   Vector TPM1CH5
                DC.W    Dummy_ISR       ; $FFEC+$FFED   Vector TPM1CH4
                DC.W    Dummy_ISR       ; $FFEE+$FFEF   Vector TPM1CH3
                DC.W    Dummy_ISR       ; $FFF0+$FFF1   Vector TPM1CH2
                DC.W    Dummy_ISR       ; $FFF2+$FFF3   Vector TPM1CH1
                DC.W    Dummy_ISR       ; $FFF4+$FFF5   Vector TPM1CH0
                DC.W    Dummy_ISR       ; $FFF6+$FFF7   Vector ICG
                DC.W    Dummy_ISR       ; $FFF8+$FFF9   Vector LVD
                DC.W    Dummy_ISR       ; $FFFA+$FFFB   Vector_IRQ
                DC.W    Dummy_ISR       ; $FFFC+$FFFD   Vector SWI
                DC.W    Main_Init       ; $FFFE+$FFFF   Vector RESET
                

