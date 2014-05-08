;************************************************************************************************
;*                                                                                              *
;*      AW32-Timerinterrupt  Version 1.0                                                        * 
;*                                                                                              *
;*      Revision vom 24.01.2014                                                                 * 
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  * 
;*      Klasse: 5AEL                                                                            * 
;*      Version: 1.0                                                                            * 
;*                                                                                              *
;*      Timer für die Alarmausgabe. Frequenz veränderbar über T_Low und T_High.                 *
;*                                                                                              *
;*      In Init kopieren:                                                                       * 
;*      jsr     Init_Alarmtimer                                                                 * 
;*                                                                                              *
;*      In ASM kopieren:                                                                        *
;*      INCLUDE 'Timerinterrupt_V10.inc'                                                        * 
;*                                                                                              *
;************************************************************************************************

Init_RFIDTimer
 
  mov   #%00000000,TPM1SC     ; Timer 1CH2 STOP


  mov   #$00,TPM1C4VH         ; Setzt einen Output Compare nach $78 Clicks
  mov   #$57,TPM1C4VL         ; das sind bei dem gegebenen Clock ca. 25ms
                           

  mov   #%01010000,TPM1C4SC   ; Timer 1 Channel 5 Gesetzt für Output Compare $50
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


;***********************************************************************************************************
;*   ALARMTON INTERRUPRT: Toggelt PB0                                                                      *
;***********************************************************************************************************

Timer_Over

    pshh
    
    lda     TPM1C4SC
    mov     #%01010000,TPM1C4SC   ;Flag löschen
  
    lda     TPM1C4VL              ; Nächster Interrupt in weiteren $57 Clicks
    add     #$14                  ; Also wieder $57 x 203,451 nsec
    sta     TPM1C5VL	

    lda     TPM1C5VH
    add     #$01		 
    sta     TPM1C5VH
    
    lda     RFID_Flag
    cmp     #$01
    bne     Ende_Timer
    
    ldhx    Counter
    aix     #1T
    sthx    Counter
    cphx    #1000T
    bhs     Timer_Off2
     
    lda     #CommIrqReg
    sta     Adresse
    ;jsr     Read_RFID
    lda     Daten
    sta     Status
    
    brset   5,Status,Timer_Off1        ;Check Rx_IRQ
    brset   4,Status,Timer_Off1        ;Check Idle_IRQ 
    ;brset   0,Status,Timer_Off2        ;Check Timer_IRQ
    
    bra     Ende_Timer
    
Timer_Off1
      
    lda     #$02
    sta     RFID_Flag    
    bra     Ende_Timer

Timer_Off2
    
    lda     #0T
    sta     Counter  
    lda     #$04
    sta     RFID_Flag
    bra     Ende_Timer
    
Ende_Timer

    pulh

    rti