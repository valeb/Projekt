;************************************************************************************************
;*      AW32-Serial-Routine  Version 1.0                                             	        *
;*                                                                                              *
;*      Revision vom 11. Januar 2013                                                            *
;*                                                                                              *
;*      Name Valentin Bernard                                                                   *
;*      Klasse: 4AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Routine zum senden und empfangen über die serielle Schnittstelle                        *
;*                                                                                              *
;*      Variablen:                                                                              *
;*      SCI_RX_Pointer  ds      2T              ; Pointer auf die aktuelle RX-Routine           *
;*      RX_Byte         ds      1T              ; Diese Variable beinhaltet das empfangene Byte *
;*      TX_Byte         ds      1T              ; Byte, das rausgesendet wird                   *
;*                                                                                              *
;*      TX_Buffer       ds      30T             ; Sehe mal 30 Bytes für den Buffer vor          *
;*      TX_Pointer      ds      2T              ; Pointer innerhalb des Buffers                 *
;*      TX_Lenght       ds      1T              ; Länge des zu sendenden Streams                *
;*                                                                                              *
;*      Init:                                                                                   *
;*      jsr     Init_Serial                                                                     *
;*                                                                                              *
;*      Vektoren:                                                                               *
;*      DC.W    SCI_TX_ISR      ; $FFD4+$FFD5   Vector SCI2_TX					*
;*	DC.W    SCI_RX_ISR      ; $FFD6+$FFD7   Vector SCI2_RX                                  *
;*                                                                                              *
;*      Init:              	                                                                *
;*      jsr     Init_Serial                                                                     *
;*												*
;*      Eingang:                                                                                *
;*      jsr     Go_Send_ADC                                                                     *
;*                                                                                              *
;************************************************************************************************


;****************************************************************
;*                                                              *
;*      Init_Serial: Initialisiert die Serielle auf             *
;*      SCI2                                                    *
;*                                                              *
;****************************************************************



Init_Serial
        mov     #%00000000,SCI2C2       ; SCI2C2: TIE=0,TCIE=0,RIE=0,ILIE=0,TE=0,RE=0,RWU=0,SBK=0
        
        lda     SCI2S1                  ; Sicherheitshalber einfach nur auslesen...
        lda     SCI2D                   ; Data Register auch einmal auslesen

        mov     #%00000000,SCI2BDH        
        mov     #%00010000,SCI2BDL      ; müssten 19.200 BAUD sein
                
        mov     #%00000100,SCI2C1       ; SCI2C1: LOOPS=0,SCISWAI=0,RSRC=0,M=0,WAKE=0,ILT=1,PE=0,PT=0 
                
        mov     #%00101100,SCI2C2       ; SCI2C2: TIE=0,TCIE=0,RIE=1,ILIE=0,TE=1,RE=1,RWU=0,SBK=0 
        
        mov     #%00000000,SCI2C3       ; SCI2C3: 

        mov     #%00000000,SCI2S2       ; SCI2S2: BRK13=0,RAF=0
        
        rts


;****************************************************************
;*                                                              *
;*      SCI_RX_ISR: Hier springt das Interrupt her, wenn ein    *
;*      Byte empfangen wird                                     *
;*                                                              *
;****************************************************************

SCI_RX_ISR
        pshh
        lda     SCI2S1          ; Flag durch auslesen löschen, sonst kann danach nix mehr empfangen werden
        lda     SCI2D           ; Empfangenes Byte einlesen
        sta     RX_Byte         ; und einfach in die Variable "RX_Byte" speichern
        sta     PORTD
        pulh
        rti
        
;****************************************************************
;*                                                              *
;*      Decode_Serial: Schaut, was für ein Befehl über die      *
;*      Serielle reingekommen ist und verhält sich              *
;*      dementsprechend                                         *
;*                                                              *
;****************************************************************
        

Decode_Serial
        lda     RX_Byte
        cmpa    #'1'            ; Sendet ADCs 1 bis 4
        beq     Go_Send_ADC1
        cmpa    #'2'           
        beq     Go_Send_ADC2
        cmpa    #'3'            
        beq     Go_Send_ADC3
        cmpa    #'4'            
        beq     Go_Send_ADC4

        rts
                   

Go_Send_ADC1
        beq     Send_ADC1
        rts
Go_Send_ADC2
        beq     Send_ADC2
        rts
Go_Send_ADC3
        beq     Send_ADC3
        rts                
Go_Send_ADC4
        beq     Send_ADC4
        rts                                          
             
Send_ADC1
        lda     #0T
        sta     RX_Byte
        bset    1,Taster_F0
        
        lda     #'A'
        sta     TX_Buffer+0T
        lda     Analog_PB0
        sta     TX_Buffer+1T
        
        bra     Sende
        
Send_ADC2
        lda     #0T
        sta     RX_Byte
        bset    1,Taster_F0
        
        lda     #'A'
        sta     TX_Buffer+0T
        lda     Analog_PB0
        sta     TX_Buffer+1T
        
        bra     Sende
                
Send_ADC3
        lda     #0T
        sta     RX_Byte
        bset    1,Taster_F0
        
        lda     #'A'
        sta     TX_Buffer+0T
        lda     Analog_PB0
        sta     TX_Buffer+1T
        
        bra     Sende

Send_ADC4
        lda     #0T
        sta     RX_Byte
        bset    1,Taster_F0
        
        lda     #'A'
        sta     TX_Buffer+0T
        lda     Analog_PB0
        sta     TX_Buffer+1T
        
        bra     Sende        
        
Sende        
                        
        lda     #1T                     ; "1" weil das erste Byte automatisch rausgeht!
        sta     TX_Lenght               ; 1 Byte im Interrupt zu senden!
        ldhx    #TX_Buffer
        sthx    TX_Pointer
        
        mov     #%01101100,SCI2C2       ; SCI2C2: TIE=0,TCIE=1,RIE=1,ILIE=0,TE=1,RE=1,RWU=0,SBK=0 
        lda     SCI2S1
        lda     TX_Buffer
        sta     SCI2D
        rts

;****************************************************************
;*                                                              *
;*      SCI_TX_ISR: Interrupt-Service-Routine für SCI-TX        *
;*                                                              *
;****************************************************************
        
SCI_TX_ISR      
        pshh
        lda     SCI2S1  
        ldhx    TX_Pointer
        lda     0,X
        sta     SCI2D
        aix     #1T
        sthx    TX_Pointer
        lda     TX_Lenght
        deca
        sta     TX_Lenght
        cmpa    #-1T
        bne     Ende_TX_ISR

                                        ; Schalte das TCIE aus (=0), Transmit Complete Interrupt
        mov     #%00101100,SCI2C2       ; SCI2C2: TIE=0,TCIE=0,RIE=1,ILIE=0,TE=1,RE=1,RWU=0,SBK=0 
Ende_TX_ISR
        pulh
        rti