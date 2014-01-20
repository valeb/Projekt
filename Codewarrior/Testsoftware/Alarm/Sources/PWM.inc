;****************************************************************
;*                                                              *
;*      Init_PWM: Initialisiert die PWM auf den Kanälen:        *
;*                                                              *
;*      PF0 (TPM1C2V): Kanal 1                                  *
;*      PF1 (TPM1C3V): Kanal 2                                  *
;*      PF2 (TPM1C4V): Kanal 3                                  *
;*      PF3 (TPM1C5V): Kanal 4                                  *
;*                                                              *
;*      PWM läuft auf dem selben Timer wie der Realtime,        *
;*      hat also eine Grundfrequenz von 19,6608 MHZ             *
;*      (4,9152 MHz x 4, über FLL)                              *
;*      1/fclk = 50,863 nsec x 4 = 203,451 nsec Busclock        *
;*      Ein Aufruf alle 64 Busclocks = einmal alle 13,021 µsec  *
;*                                                              *
;****************************************************************


Init_PWM

       mov   #%00000000,TPM1SC     ; Timer 1 - Stopped.
     ;         ||||||||
     ;         ||||||||_____  PS0  Prescaler : 0:0:0=Clock/1    0:0:1=Clock/2    0:1:0=Clock/4
     ;         |||||||______  PS1              0:1:1=Clock/8    1:0:0=Clock/16   1:0:1=Clock/32
     ;         ||||||_______  PS2              1:1:0=Clock/64   1:1:1=Clock/128
     ;         |||||________  CLKS [A] --> [B:A]  0:0 = TPM OFF  0:1 = Bus rate Clock (BUSCLK)
     ;         ||||_________  CLKS [B] CLK Source 1:0 = Fixed system Clock (XCLX) 1:1 Ex. Source (TPMxCLK)
     ;         |||__________  CPWMS Normal Op (0) or Center alligned PWM (1)
     ;         ||___________  TOIE Timer Interrupt Enable
     ;         |____________  TOV - Timer Overflow, Read only


       mov   #%10101000,TPM1C2SC   ; Timer 1 Channel 0 Gesetzt für Output Compare $54
       ;mov   #%10101000,TPM1C3SC   ; Timer 1 Channel 0 Gesetzt für Output Compare $54
       ;mov   #%10101000,TPM1C4SC   ; Timer 1 Channel 0 Gesetzt für Output Compare $54
       ;mov   #%10101000,TPM1C5SC   ; Timer 1 Channel 0 Gesetzt für Output Compare $54
     ;         ||||||||
     ;         ||||||||_____  not used
     ;         |||||||______  not used
     ;         ||||||_______  ELS1A Edge Level Select Bits for Channel 1
     ;         |||||________  ELS1B [B:A]=[1:0]=Edge-alligned PWM
     ;         ||||_________  MS1A Mode select for Timer 1  [B:A]=[1:0] = Edge-allined PWM
     ;         |||__________  MS1B
     ;         ||___________  CH1IE 0=Interr. disable  1=Interrupt enable
     ;         |____________  CH1F  0=No input capt. or Outp.Comp on Pin  1=Input capt. or Outp.Comp on Pin 
       
       
       ldhx    Frequenz          ; 1000 x 203,451 nsec = 203,451 µsec  Periode PWM = 1000 Clocks!
       sthx    TPM1MODH        ; 1/X = 4,9152 kHz


       mov   #%00001000,TPM1SC     ; Startet den Timer
     ;         ||||||||
     ;         ||||||||_____  PS0  Prescaler : 0:0:0=Clock/1    0:0:1=Clock/2    0:1:0=Clock/4
     ;         |||||||______  PS1              0:1:1=Clock/8    1:0:0=Clock/16   1:0:1=Clock/32
     ;         ||||||_______  PS2              1:1:0=Clock/64   1:1:1=Clock/128
     ;         |||||________  CLKS [A] --> [B:A]  0:0 = TPM OFF  0:1 = Bus rate Clock (BUSCLK)
     ;         ||||_________  CLKS [B] CLK Source 1:0 = Fixed system Clock (XCLX) 1:1 Ex. Source (TPMxCLK)
     ;         |||__________  CPWMS Normal Op (0) or Center alligned PWM (1)
     ;         ||___________  TOIE Timer Overflow Interrupt Enable (1) or disable (0)
     ;         |____________  TOV - Timer Overflow, Read only



     ; 1000T ist volle Periode (100% Duty), 500T folglich die Hälfte (50%) usw...
        
        ldhx    #500T
        sthx    TPM1C2V         ; Kanal 1: Initialisiert mit 500T (50%)
        
        ;ldhx    #500T
        ;sthx    TPM1C3V         ; Kanal 2: Initialisiert mit 500T (50%)
        
        ;ldhx    #750T           
        ;sthx    TPM1C4V         ; Kanal 3: Initialisiert mit 750T (75%)
                                 
        ;ldhx    #1000T           
        ;sthx    TPM1C5V         ; Kanal 4: Initialisiert mit 1000T (100%)
        
        rts
        
;****************************************************************
;*                                                              *
;*      Set_PWM: teilt die jeweiligen PWM´s den einzelnen       *
;*      Kanälen zu.                                             *
;*                                                              *
;****************************************************************
        
Set_PWM
	   
	   ldhx		PWM_Kanal_1
      sthx     TPM1C2V
        
	   ;ldhx		PWM_Kanal_2
     ; sthx     TPM1C3V

	   ;ldhx		PWM_Kanal_3
     ; sthx     TPM1C4V

	   ;ldhx		PWM_Kanal_4
     ; sthx     TPM1C5V
       
       rts
       
       

   
        