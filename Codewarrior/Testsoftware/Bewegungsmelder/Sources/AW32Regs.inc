PTAD:               equ    $00000000                                    
PORTA:              equ    $00000000                                ;*** PTAD - Port A Data Register; 0x00000000 ***
PTADD:              equ    $00000001                                ;*** PTADD - Data Direction Register A; 0x00000001 ***
PTBD:               equ    $00000002                                ;*** PTBD - Port B Data Register; 0x00000002 ***
PORTB:              equ    $00000002
PTBDD:              equ    $00000003                                ;*** PTBDD - Data Direction Register B; 0x00000003 ***
PTCD:               equ    $00000004                                ;*** PTCD - Port C Data Register; 0x00000004 ***
PORTC               equ    $00000004
PTCDD:              equ    $00000005                                ;*** PTCDD - Data Direction Register C; 0x00000005 ***
PTDD:               equ    $00000006                                ;*** PTDD - Port D Data Register; 0x00000006 ***
PORTD:              equ    $00000006
PTDDD:              equ    $00000007                                ;*** PTDDD - Data Direction Register D; 0x00000007 ***
PTED:               equ    $00000008        
PORTE:              equ    $00000008                                ;*** PTED - Port E Data Register; 0x00000008 ***
PTEDD:              equ    $00000009                                ;*** PTEDD - Data Direction Register E; 0x00000009 ***
PTFD:               equ    $0000000A                                ;*** PTFD - Port F Data Register; 0x0000000A ***
PORTF:              equ    $0000000A                                ;*** PTFD - Port F Data Register; 0x0000000A ***
PTFDD:              equ    $0000000B                                ;*** PTFDD - Data Direction Register F; 0x0000000B ***
PTGD:               equ    $0000000C                                ;*** PTGD - Port G Data Register; 0x0000000C ***
PORTG:              equ    $0000000C                                ;*** PTFD - Port F Data Register; 0x0000000A ***
PTGDD:              equ    $0000000D                                ;*** PTGDD - Data Direction Register G; 0x0000000D ***
ADC1SC1:            equ    $00000010                                ;*** ADC1SC1 - Status and Control Register; 0x00000010 ***
ADC1SC2:            equ    $00000011                                ;*** ADC1SC2 - Status and Control Register 2; 0x00000011 ***
ADC1R:              equ    $00000012                                ;*** ADC1R - ADC10 Result Data Right Justified; 0x00000012 ***
ADC1RH:             equ    $00000012                                ;*** ADC1RH - ADC10 Result Data Right Justified High; 0x00000012 ***
ADC1RL:             equ    $00000013                                ;*** ADC1RL - ADC10 Result Data Right Justified Low; 0x00000013 ***
ADC1CV:             equ    $00000014                                ;*** ADC1CV - Compare Value Register; 0x00000014 ***
ADC1CVH:            equ    $00000014                                ;*** ADC1CVH - Compare Value Register High; 0x00000014 ***
ADC1CVL:            equ    $00000015                                ;*** ADC1CVL - Compare Value Register Low; 0x00000015 ***
ADC1CFG:            equ    $00000016                                ;*** ADC1CFG - Configuration Register; 0x00000016 ***
APCTL1:             equ    $00000017                                ;*** APCTL1 - ADC10 Pin Control 1 Register; 0x00000017 ***
APCTL2:             equ    $00000018                                ;*** APCTL2 - ADC10 Pin Control 2 Register; 0x00000018 ***
APCTL3:             equ    $00000019                                ;*** APCTL3 - ADC10 Pin Control 3 Register; 0x00000019 ***
IRQSC:              equ    $0000001C                                ;*** IRQSC - Interrupt Request Status and Control Register; 0x0000001C ***
KBISC:              equ    $0000001E                                ;*** KBISC - KBI1 Status and Control; 0x0000001E ***
KBIPE:              equ    $0000001F                                ;*** KBIPE - KBI1 Pin Enable Register; 0x0000001F ***
TPM1SC:             equ    $00000020                                ;*** TPM1SC - TPM 1 Status and Control Register; 0x00000020 ***
TPM1CNT:            equ    $00000021                                ;*** TPM1CNT - TPM 1 Counter Register; 0x00000021 ***
TPM1CNTH:           equ    $00000021                                ;*** TPM1CNTH - TPM 1 Counter Register High; 0x00000021 ***
TPM1CNTL:           equ    $00000022                                ;*** TPM1CNTL - TPM 1 Counter Register Low; 0x00000022 ***
TPM1MOD:            equ    $00000023                                ;*** TPM1MOD - TPM 1 Timer Counter Modulo Register; 0x00000023 ***
TPM1MODH:           equ    $00000023                                ;*** TPM1MODH - TPM 1 Timer Counter Modulo Register High; 0x00000023 ***
TPM1MODL:           equ    $00000024                                ;*** TPM1MODL - TPM 1 Timer Counter Modulo Register Low; 0x00000024 ***
TPM1C0SC:           equ    $00000025                                ;*** TPM1C0SC - TPM 1 Timer Channel 0 Status and Control Register; 0x00000025 ***
TPM1C0V:            equ    $00000026                                ;*** TPM1C0V - TPM 1 Timer Channel 0 Value Register; 0x00000026 ***
TPM1C0VH:           equ    $00000026                                ;*** TPM1C0VH - TPM 1 Timer Channel 0 Value Register High; 0x00000026 ***
TPM1C0VL:           equ    $00000027                                ;*** TPM1C0VL - TPM 1 Timer Channel 0 Value Register Low; 0x00000027 ***
TPM1C1SC:           equ    $00000028                                ;*** TPM1C1SC - TPM 1 Timer Channel 1 Status and Control Register; 0x00000028 ***
TPM1C1V:            equ    $00000029                                ;*** TPM1C1V - TPM 1 Timer Channel 1 Value Register; 0x00000029 ***
TPM1C1VH:           equ    $00000029                                ;*** TPM1C1VH - TPM 1 Timer Channel 1 Value Register High; 0x00000029 ***
TPM1C1VL:           equ    $0000002A                                ;*** TPM1C1VL - TPM 1 Timer Channel 1 Value Register Low; 0x0000002A ***
TPM1C2SC:           equ    $0000002B                                ;*** TPM1C2SC - TPM 1 Timer Channel 2 Status and Control Register; 0x0000002B ***
TPM1C2V:            equ    $0000002C                                ;*** TPM1C2V - TPM 1 Timer Channel 2 Value Register; 0x0000002C ***
TPM1C2VH:           equ    $0000002C                                ;*** TPM1C2VH - TPM 1 Timer Channel 2 Value Register High; 0x0000002C ***
TPM1C2VL:           equ    $0000002D                                ;*** TPM1C2VL - TPM 1 Timer Channel 2 Value Register Low; 0x0000002D ***
TPM1C3SC:           equ    $0000002E                                ;*** TPM1C3SC - TPM 1 Timer Channel 3 Status and Control Register; 0x0000002E ***
TPM1C3V:            equ    $0000002F                                ;*** TPM1C3V - TPM 1 Timer Channel 3 Value Register; 0x0000002F ***
TPM1C3VH:           equ    $0000002F                                ;*** TPM1C3VH - TPM 1 Timer Channel 3 Value Register High; 0x0000002F ***
TPM1C3VL:           equ    $00000030                                ;*** TPM1C3VL - TPM 1 Timer Channel 3 Value Register Low; 0x00000030 ***
TPM1C4SC:           equ    $00000031                                ;*** TPM1C4SC - TPM 1 Timer Channel 4 Status and Control Register; 0x00000031 ***
TPM1C4V:            equ    $00000032                                ;*** TPM1C4V - TPM 1 Timer Channel 4 Value Register; 0x00000032 ***
TPM1C4VH:           equ    $00000032                                ;*** TPM1C4VH - TPM 1 Timer Channel 4 Value Register High; 0x00000032 ***
TPM1C4VL:           equ    $00000033                                ;*** TPM1C4VL - TPM 1 Timer Channel 4 Value Register Low; 0x00000033 ***
TPM1C5SC:           equ    $00000034                                ;*** TPM1C5SC - TPM 1 Timer Channel 5 Status and Control Register; 0x00000034 ***
TPM1C5V:            equ    $00000035                                ;*** TPM1C5V - TPM 1 Timer Channel 5 Value Register; 0x00000035 ***
TPM1C5VH:           equ    $00000035                                ;*** TPM1C5VH - TPM 1 Timer Channel 5 Value Register High; 0x00000035 ***
TPM1C5VL:           equ    $00000036                                ;*** TPM1C5VL - TPM 1 Timer Channel 5 Value Register Low; 0x00000036 ***
SCI1BD:             equ    $00000038                                ;*** SCI1BD - SCI1 Baud Rate Register; 0x00000038 ***
SCI1BDH:            equ    $00000038                                ;*** SCI1BDH - SCI1 Baud Rate Register High; 0x00000038 ***
SCI1BDL:            equ    $00000039                                ;*** SCI1BDL - SCI1 Baud Rate Register Low; 0x00000039 ***
SCI1C1:             equ    $0000003A                                ;*** SCI1C1 - SCI1 Control Register 1; 0x0000003A ***
SCI1C2:             equ    $0000003B                                ;*** SCI1C2 - SCI1 Control Register 2; 0x0000003B ***
SCI1S1:             equ    $0000003C                                ;*** SCI1S1 - SCI1 Status Register 1; 0x0000003C ***
SCI1S2:             equ    $0000003D                                ;*** SCI1S2 - SCI1 Status Register 2; 0x0000003D ***
SCI1D:              equ    $0000003F                                ;*** SCI1D - SCI1 Data Register; 0x0000003F ***
SCI2BD:             equ    $00000040                                ;*** SCI2BD - SCI2 Baud Rate Register; 0x00000040 ***
SCI2BDH:            equ    $00000040                                ;*** SCI2BDH - SCI2 Baud Rate Register High; 0x00000040 ***
SCI2BDL:            equ    $00000041                                ;*** SCI2BDL - SCI2 Baud Rate Register Low; 0x00000041 ***
SCI2C1:             equ    $00000042                                ;*** SCI2C1 - SCI1 Control Register 1; 0x00000042 ***
SCI2C2:             equ    $00000043                                ;*** SCI2C2 - SCI2 Control Register 2; 0x00000043 ***
SCI2S1:             equ    $00000044                                ;*** SCI2S1 - SCI2 Status Register 1; 0x00000044 ***
SCI2S2:             equ    $00000045                                ;*** SCI2S2 - SCI2 Status Register 2; 0x00000045 ***
SCI2C3:             equ    $00000046                                ;*** SCI2C3 - SCI2 Control Register 3; 0x00000046 ***
SCI2D:              equ    $00000047                                ;*** SCI2D - SCI2 Data Register; 0x00000047 ***
ICGC1:              equ    $00000048                                ;*** ICGC1 - ICG Control Register 1; 0x00000048 ***
ICGC2:              equ    $00000049                                ;*** ICGC2 - ICG Control Register 2; 0x00000049 ***
ICGS1:              equ    $0000004A                                ;*** ICGS1 - ICG Status Register 1; 0x0000004A ***
ICGS2:              equ    $0000004B                                ;*** ICGS2 - ICG Status Register 2; 0x0000004B ***
ICGFLT:             equ    $0000004C                                ;*** ICGFLT - ICG Upper Filter; 0x0000004C ***
ICGFLTU:            equ    $0000004C                                ;*** ICGFLTU - ICG Upper Filter Register; 0x0000004C ***
ICGFLTL:            equ    $0000004D                                ;*** ICGFLTL - ICG Lower Filter Register; 0x0000004D ***
ICGTRM:             equ    $0000004E                                ;*** ICGTRM - ICG Trim Register; 0x0000004E ***
SPI1C1:             equ    $00000050                                ;*** SPI1C1 - SPI1 Control Register 1; 0x00000050 ***
SPI1C2:             equ    $00000051                                ;*** SPI1C2 - SPI1 Control Register 2; 0x00000051 ***
SPI1BR:             equ    $00000052                                ;*** SPI1BR - SPI1 Baud Rate Register; 0x00000052 ***
SPI1S:              equ    $00000053                                ;*** SPI1S - SPI1 Status Register; 0x00000053 ***
IIC1A:              equ    $00000058                                ;*** IIC1A - IIC1 Address Register; 0x00000058 ***
IIC1F:              equ    $00000059                                ;*** IIC1F - IIC1 Frequency Divider Register; 0x00000059 ***
IIC1C:              equ    $0000005A                                ;*** IIC1C - IIC1 Control Register; 0x0000005A ***
IIC1S:              equ    $0000005B                                ;*** IIC1S - IIC1 Status Register; 0x0000005B ***
IIC1D:              equ    $0000005C                                ;*** IIC1D - IIC1 Data I/O Register; 0x0000005C ***
TPM2SC:             equ    $00000060                                ;*** TPM2SC - TPM 2 Status and Control Register; 0x00000060 ***
TPM2CNT:            equ    $00000061                                ;*** TPM2CNT - TPM 2 Counter Register; 0x00000061 ***
TPM2CNTH:           equ    $00000061                                ;*** TPM2CNTH - TPM 2 Counter Register High; 0x00000061 ***
TPM2CNTL:           equ    $00000062                                ;*** TPM2CNTL - TPM 2 Counter Register Low; 0x00000062 ***
TPM2MOD:            equ    $00000063                                ;*** TPM2MOD - TPM 2 Timer Counter Modulo Register; 0x00000063 ***
TPM2MODH:           equ    $00000063                                ;*** TPM2MODH - TPM 2 Timer Counter Modulo Register High; 0x00000063 ***
TPM2MODL:           equ    $00000064                                ;*** TPM2MODL - TPM 2 Timer Counter Modulo Register Low; 0x00000064 ***
TPM2C0SC:           equ    $00000065                                ;*** TPM2C0SC - TPM 2 Timer Channel 0 Status and Control Register; 0x00000065 ***
TPM2C0V:            equ    $00000066                                ;*** TPM2C0V - TPM 2 Timer Channel 0 Value Register; 0x00000066 ***
TPM2C0VH:           equ    $00000066                                ;*** TPM2C0VH - TPM 2 Timer Channel 0 Value Register High; 0x00000066 ***
TPM2C0VL:           equ    $00000067                                ;*** TPM2C0VL - TPM 2 Timer Channel 0 Value Register Low; 0x00000067 ***
TPM2C1SC:           equ    $00000068                                ;*** TPM2C1SC - TPM 2 Timer Channel 1 Status and Control Register; 0x00000068 ***
TPM2C1V:            equ    $00000069                                ;*** TPM2C1V - TPM 2 Timer Channel 1 Value Register; 0x00000069 ***
TPM2C1VH:           equ    $00000069                                ;*** TPM2C1VH - TPM 2 Timer Channel 1 Value Register High; 0x00000069 ***
TPM2C1VL:           equ    $0000006A                                ;*** TPM2C1VL - TPM 2 Timer Channel 1 Value Register Low; 0x0000006A ***
SRS:                equ    $00001800                                ;*** SRS - System Reset Status; 0x00001800 ***
SBDFR:              equ    $00001801                                ;*** SBDFR - System Background Debug Force Reset Register; 0x00001801 ***
mSBDFR_BDFR:        equ    %00000001
SOPT:               equ    $00001802                                ;*** SOPT - System Options Register; 0x00001802 ***
SMCLK:              equ    $00001803                                ;*** SMCLK - System MCLK Control Register; 0x00001803 ***
SDID:               equ    $00001806                                ;*** SDID - System Integration Module Part ID Register; 0x00001806 ***
SDIDH:              equ    $00001806                                ;*** SDIDH - System Integration Module Part ID Register High; 0x00001806 ***
SDIDL:              equ    $00001807                                ;*** SDIDL - System Integration Module Part ID Register Low; 0x00001807 ***
SRTISC:             equ    $00001808                                ;*** SRTISC - System RTI Status and Control Register; 0x00001808 ***
SPMSC1:             equ    $00001809                                ;*** SPMSC1 - PM Status and Control 1 Register; 0x00001809 ***
SPMSC2:             equ    $0000180A                                ;*** SPMSC2 - PM Status and Control 2 Register; 0x0000180A ***
DBGCAH:             equ    $00001810                                ;*** DBGCAH - Debug Comparator A High Register; 0x00001810 ***
DBGCAL:             equ    $00001811                                ;*** DBGCAL - Debug Comparator A Low Register; 0x00001811 ***
DBGCBH:             equ    $00001812                                ;*** DBGCBH - Debug Comparator B High Register; 0x00001812 ***
DBGCBL:             equ    $00001813                                ;*** DBGCBL - Debug Comparator B Low Register; 0x00001813 ***
DBGFH:              equ    $00001814                                ;*** DBGFH - Debug FIFO High Register; 0x00001814 ***
DBGFL:              equ    $00001815                                ;*** DBGFL - Debug FIFO Low Register; 0x00001815 ***
DBGC:               equ    $00001816                                ;*** DBGC - Debug Control Register; 0x00001816 ***
DBGT:               equ    $00001817                                ;*** DBGT - Debug Trigger Register; 0x00001817 ***
DBGS:               equ    $00001818                                ;*** DBGS - Debug Status Register; 0x00001818 ***
FCDIV:              equ    $00001820                                ;*** FCDIV - FLASH Clock Divider Register; 0x00001820 ***
FOPT:               equ    $00001821                                ;*** FOPT - FLASH Options Register; 0x00001821 ***
FCNFG:              equ    $00001823                                ;*** FCNFG - FLASH Configuration Register; 0x00001823 ***
FPROT:              equ    $00001824                                ;*** FPROT - FLASH Protection Register; 0x00001824 ***
FSTAT:              equ    $00001825                                ;*** FSTAT - FLASH Status Register; 0x00001825 ***
FCMD:               equ    $00001826                                ;*** FCMD - FLASH Command Register; 0x00001826 ***
PTAPE:              equ    $00001840                                ;*** PTAPE - Pullup Enable for Port A; 0x00001840 ***
PTASE:              equ    $00001841                                ;*** PTASE - Slew Rate Control Enable for Port A; 0x00001841 ***
PTADS:              equ    $00001842                                ;*** PTADS - Output Drive Strength Selection for Port A; 0x00001842 ***
PTBPE:              equ    $00001844                                ;*** PTBPE - Pullup Enable for Port B; 0x00001844 ***
PTBSE:              equ    $00001845                                ;*** PTBSE - Slew Rate Control Enable for Port B; 0x00001845 ***
PTBDS:              equ    $00001846                                ;*** PTBDS - Output Drive Strength Selection for Port B; 0x00001846 ***
PTCPE:              equ    $00001848                                ;*** PTCPE - Pullup Enable for Port C; 0x00001848 ***
PTCSE:              equ    $00001849                                ;*** PTCSE - Slew Rate Control Enable for Port C; 0x00001849 ***
PTCDS:              equ    $0000184A                                ;*** PTCDS - Output Drive Strength Selection for Port C; 0x0000184A ***
PTDPE:              equ    $0000184C                                ;*** PTDPE - Pullup Enable for Port D; 0x0000184C ***
PTDSE:              equ    $0000184D                                ;*** PTDSE - Slew Rate Control Enable for Port D; 0x0000184D ***
PTDDS:              equ    $0000184E                                ;*** PTDDS - Output Drive Strength Selection for Port D; 0x0000184E ***
PTEPE:              equ    $00001850                                ;*** PTEPE - Pullup Enable for Port E; 0x00001850 ***
PTESE:              equ    $00001851                                ;*** PTESE - Slew Rate Control Enable for Port E; 0x00001851 ***
PTEDS:              equ    $00001852                                ;*** PTEDS - Output Drive Strength Selection for Port E; 0x00001852 ***
PTFPE:              equ    $00001854                                ;*** PTFPE - Pullup Enable for Port F; 0x00001854 ***
PTFSE:              equ    $00001855                                ;*** PTFSE - Slew Rate Control Enable for Port F; 0x00001855 ***
PTFDS:              equ    $00001856                                ;*** PTFDS - Output Drive Strength Selection for Port F; 0x00001856 ***
PTGPE:              equ    $00001858                                ;*** PTGPE - Pullup Enable for Port G; 0x00001858 ***
PTGSE:              equ    $00001859                                ;*** PTGSE - Slew Rate Control Enable for Port G; 0x00001859 ***
PTGDS:              equ    $0000185A                                ;*** PTGDS - Output Drive Strength Selection for Port G; 0x0000185A ***
NVBACKKEY0:         equ    $0000FFB0                                ;*** NVBACKKEY0 - Backdoor Comparison Key 0; 0x0000FFB0 ***
NVBACKKEY1:         equ    $0000FFB1                                ;*** NVBACKKEY1 - Backdoor Comparison Key 1; 0x0000FFB1 ***
NVBACKKEY2:         equ    $0000FFB2                                ;*** NVBACKKEY2 - Backdoor Comparison Key 2; 0x0000FFB2 ***
NVBACKKEY3:         equ    $0000FFB3                                ;*** NVBACKKEY3 - Backdoor Comparison Key 3; 0x0000FFB3 ***
NVBACKKEY4:         equ    $0000FFB4                                ;*** NVBACKKEY4 - Backdoor Comparison Key 4; 0x0000FFB4 ***
NVBACKKEY5:         equ    $0000FFB5                                ;*** NVBACKKEY5 - Backdoor Comparison Key 5; 0x0000FFB5 ***
NVBACKKEY6:         equ    $0000FFB6                                ;*** NVBACKKEY6 - Backdoor Comparison Key 6; 0x0000FFB6 ***
NVBACKKEY7:         equ    $0000FFB7                                ;*** NVBACKKEY7 - Backdoor Comparison Key 7; 0x0000FFB7 ***
NVPROT:             equ    $0000FFBD                                ;*** NVPROT - Nonvolatile FLASH Protection Register; 0x0000FFBD ***
NVOPT:              equ    $0000FFBF                                ;*** NVOPT - Nonvolatile FLASH Options Register; 0x0000FFBF ***

