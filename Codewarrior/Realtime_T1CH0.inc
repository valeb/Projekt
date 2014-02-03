;************************************************************************************************
;*                                                                                              *
;*      Init_Realtime: Initialisiert den RealTime auf Timer2, CH0                                  *
;*                                                                                              *
;*      BusClock: Bei 19,6608 MHz-Quarz ist der Busclock                                        *
;*      1/19,6608MHz x 4 = 50,863 nsec x 4 = 203,451 nsec                                       *
;*      Bei $6000 Zyklen (Dezimal: 24576 Zyklen) á 203,451 nsec = 5 msec                        *
;*                                                                                              *
;************************************************************************************************

Init_Realtime

   mov   #%00000000,TPM1SC     ; Timer 1CH2 STOP


   mov   #$20,TPM1C0VH         ; Setzt einen Output Compare nach $6000 Clicks
   mov   #$00,TPM1C0VL         ; das sind bei dem gegebenen Clock GENAU 1,66666 msec
                           

   mov   #%01010000,TPM1C0SC   ; Timer 1 Channel 5 Gesetzt für Output Compare $50
 ;         ||||||||
 ;         ||||||||_____  not used
 ;         |||||||______  not used
 ;         ||||||_______  ELS1A Edge Level Select Bits for Channel 1
 ;         |||||________  ELS1B [B:A]=[0:1]=Toggle Output con Compare  [0:0]=Software compare only
 ;         ||||_________  MS1A Mode select for Timer 1  [B:A]=[0:1] = Output compare
 ;         |||__________  MS1B
 ;         ||___________  CH1IE 0=Interr. disable  1=Interrupt enable
 ;         |____________  CH1F  0=No input capt. or Outp.Comp on Pin  1=Input capt. or Outp.Comp on Pin 
 

   mov   #%00001000,TPM1SC     ; Startet den Timer 1CH2
 ;         ||||||||
 ;         ||||||||_____  PS0  Prescaler : 0:0:0=Clock/1    0:0:1=Clock/2    0:1:0=Clock/4
 ;         |||||||______  PS1              0:1:1=Clock/8    1:0:0=Clock/16   1:0:1=Clock/32
 ;         ||||||_______  PS2              1:1:0=Clock/64   1:1:1=Clock/128
 ;         |||||________  CLKS [A] --> [B:A]  0:0 = TPM OFF  0:1 = Bus rate Clock (BUSCLK)
 ;         ||||_________  CLKS [B] CLK Source 1:0 = Fixed system Clock (XCLX) 1:1 Ex. Source (TPMxCLK)
 ;         |||__________  CPWMS Normal Op (0) or Center alligned PWM (1)
 ;         ||___________  TOIE Timer Interrupt Enable
 ;         |____________  TOV - Timer Overflow, Read only

   rts



;************************************************************************************************
;*                                                                                              *
;*      Realtime: Diese Interrupt-Routine wird alle 1,666 msec aufgerufen                       *
;*                                                                                              *
;************************************************************************************************


Realtime
      pshh
      
      lda     TPM1C0SC
      mov     #%01010000,TPM1C0SC   ;Flag löschen
  
      lda     TPM1C0VL              ; Nächster Interrupt in weiteren $6000 Clicks
      add     #$00                  ; Also wieder $20 x 203,451 nsec = 1,666 msec GENAU
      sta     TPM1C0VL	

      lda     TPM1C0VH
      adc     #$20
      sta     TPM1C0VH 
                
      lda      RealTimeCounter
      inca
      sta      RealTimeCounter           ; 6 x 1,6666ms = 10 msec genau
      cmpa     #6T
      bne      Exit_Realtime
      clra
      sta      RealTimeCounter
             
      lda      #1T
      sta      TimerFlag


Exit_Realtime       
       pulh

       rti