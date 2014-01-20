;************************************************************************************************
;*                                                                                              *
;*      AW32-Timerinterrupt  Version 1.0                                                             * 
;*                                                                                              *
;*      Revision vom 30.Dezember 2013                                                           * 
;*                                                                                              *
;*      Name: Lukas Graif                                                                       * 
;*      Klasse: 5AEL                                                                            * 
;*      Version: 1.0                                                                            * 
;*                                                                                              *
;*      RPM_Timer 1.0                                                                           * 
;*      Timer für die RPM Routine.                                                              * 
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      ;RPM_Timer                                                                              * 
;*      RPM_TimerStart ds       1T                                                              * 
;*                                                                                              *
;*      In Hauptloop kopieren:                                                                  *
;*                                                                                              *
;*      In Init kopieren:                                                                       * 
;*      jsr     Init_RPM_Timer                                                                  * 
;*                                                                                              *
;*      In ASM kopieren:                                                                        *
;*      INCLUDE 'RPM_Timer_V10.inc'                                                             * 
;*                                                                                              *
;************************************************************************************************


Init_RPM_Timer


   lda   #0T
   sta   RPM_TimerStart 

   mov   #%00000000,TPM1SC     ; Timer 1CH2 STOP


   mov   #$60,TPM1C5VH         ; Setzt einen Output Compare nach $6000 Clicks
   mov   #$00,TPM1C5VL         ; das sind bei dem gegebenen Clock GENAU 5 msec
                           

   mov   #%01010000,TPM1C5SC   ; Timer 1 Channel 0 Gesetzt für Output Compare $50
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




T2_Over

    pshh
    	
	  mov   #$60,TPM1C5VH
    
    brclr 0,RPM_TimerStart,RPM_NoTimer  
  
    ldhx   RPMCounter              
    aix    #1T
    sthx   RPMCounter 

RPM_NoTimer
   
  pulh


  rti