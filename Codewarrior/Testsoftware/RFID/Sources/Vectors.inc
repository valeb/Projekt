;************************************************************************************************
;*                                                                                              *
;*                 Interrupt Vectoren                                                           *
;*                                                                                              *
;************************************************************************************************

                ORG   VECTOR_START


                DC.W    Dummy_ISR1      ; $FFCC+$FFCD   Vector RTI
                DC.W    Dummy_ISR2      ; $FFCE+$FFCF   Vector IIC1
                DC.W    Dummy_ISR3      ; $FFD0+$FFD1   Vector ADC1
                DC.W    Dummy_ISR4      ; $FFD2+$FFD3   Vector KEYBOARD
                DC.W    Dummy_ISR5      ; $FFD4+$FFD5   Vector SCI2_TX
                DC.W    Dummy_ISR6      ; $FFD6+$FFD7   Vector SCI2_RX
                DC.W    Dummy_ISR7      ; $FFD8+$FFD9   Vector SCI2_ERR
                DC.W    Dummy_ISR8      ; $FFDA+$FFDB   Vector SCI1_TX
                DC.W    Dummy_ISR9      ; $FFDC+$FFDC   Vector SCI1_RX
                DC.W    Dummy_ISR10     ; $FFDE+$FFDF   Vector SCI1_ERR
                DC.W    SPI_Clock       ; $FFE0+$FFE1   Vector SPI1
                DC.W    Dummy_ISR12     ; $FFE2+$FFE3   Vector TPM2OVF                
                DC.W    Dummy_ISR13     ; $FFE4+$FFE5   Vector TMP2CH1                
                DC.W    Dummy_ISR14     ; $FFE6+$FFE7   Vector TPM2CH0                
                DC.W    Dummy_ISR15     ; $FFE8+$FFE9   Vector TPM1OVF                
                DC.W    Dummy_ISR16     ; $FFEA+$FFEB   Vector TPM1CH5
                DC.W    Dummy_ISR17     ; $FFEC+$FFED   Vector TPM1CH4
                DC.W    Dummy_ISR18     ; $FFEE+$FFEF   Vector TPM1CH3
                DC.W    Dummy_ISR19     ; $FFF0+$FFF1   Vector TPM1CH2
                DC.W    Dummy_ISR20     ; $FFF2+$FFF3   Vector TPM1CH1
                DC.W    Realtime        ; $FFF4+$FFF5   Vector TPM1CH0
                DC.W    Dummy_ISR21     ; $FFF6+$FFF7   Vector ICG
                DC.W    Dummy_ISR21     ; $FFF8+$FFF9   Vector LVD
                DC.W    Dummy_ISR21     ; $FFFA+$FFFB   Vector_IRQ
                DC.W    Dummy_ISR21     ; $FFFC+$FFFD   Vector SWI
                DC.W    Main_Init       ; $FFFE+$FFFF   Vector RESET
                

