;************************************************************************************************
;*                                                                                              *
;*      Hier werden den Registern und Befehlen des MC522 Namen zugewiesen                       *
;*                                                                                              *
;************************************************************************************************

;MF522 command bits
PCD_IDLE              	EQU        $00               ;NO action; cancel current commands
PCD_AUTHENT          	  EQU        $0E               ;verify password key
PCD_RECEIVE           	EQU        $08               ;receive data
PCD_TRANSMIT          	EQU        $04               ;send data
PCD_TRANSCEIVE          EQU        $0C               ;send and receive data
PCD_RESETPHASE          EQU        $0F               ;reset
PCD_CALCCRC           	EQU        $03               ;CRC check and caculation

;Mifare_One card command bits
PICC_REQIDL           	EQU        $26               ;Search the cards that not into sleep mode in the antenna area 
PICC_REQALL           	EQU        $52               ;Search all the cards in the antenna area
PICC_ANTICOLL         	EQU        $93               ;prevent conflict
PICC_SElECTTAG          EQU        $93               ;select card
PICC_AUTHENT1A          EQU        $60               ;verify A password key
PICC_AUTHENT1B          EQU        $61               ;verify B password key
PICC_READ             	EQU        $30               ;read 
PICC_WRITE            	EQU        $A0               ;write
PICC_DECREMENT      	  EQU        $C0               ;deduct value
PICC_INCREMENT      	  EQU        $C1               ;charge up value
PICC_RESTORE          	EQU        $C2               ;Restore data into buffer
PICC_TRANSFER        	  EQU        $B0               ;Save data into buffer
PICC_HALT             	EQU        $50               ;sleep mode


;THe mistake code that return when communicate with MF522
MI_OK                 	EQU        $0
MI_NOTAGERR           	EQU	       $1
MI_ERR                	EQU	       $2


;------------------MFRC522 register ---------------
;Page 0:Command and Status
Reserved00            	EQU        $00    
CommandReg            	EQU        $01    
CommIEnReg            	EQU        $02    
DivlEnReg             	EQU        $03    
CommIrqReg            	EQU        $04    
DivIrqReg             	EQU        $05
ErrorReg              	EQU        $06    
Status1Reg            	EQU        $07    
Status2Reg            	EQU        $08    
FIFODataReg           	EQU        $09
FIFOLevelReg          	EQU        $0A
WaterLevelReg         	EQU        $0B
ControlReg            	EQU        $0C
BitFramingReg         	EQU        $0D
CollReg               	EQU        $0E
Reserved01            	EQU        $0F
;Page 1:Command     
Reserved10            	EQU        $10
ModeReg               	EQU        $11
TxModeReg             	EQU        $12
RxModeReg             	EQU        $13
TxControlReg          	EQU        $14
TxAutoReg             	EQU        $15
TxSelReg              	EQU        $16
RxSelReg              	EQU        $17
RxThresholdReg        	EQU        $18
DemodReg              	EQU        $19
Reserved11            	EQU        $1A
Reserved12            	EQU        $1B
MifareReg             	EQU        $1C
Reserved13            	EQU        $1D
Reserved14            	EQU        $1E
SerialSpeedReg        	EQU        $1F
;Page 2:CFG    
Reserved20            	EQU        $20  
CRCResultRegM         	EQU        $21
CRCResultRegL         	EQU        $22
Reserved21            	EQU        $23
ModWidthReg           	EQU        $24
Reserved22            	EQU        $25
RFCfgReg              	EQU        $26
GsNReg                	EQU        $27
CWGsPReg	          	  EQU        $28
ModGsPReg             	EQU        $29
TModeReg              	EQU        $2A
TPrescalerReg         	EQU        $2B
TReloadRegH           	EQU        $2C
TReloadRegL           	EQU        $2D
TCounterValueRegH     	EQU        $2E
TCounterValueRegL     	EQU        $2F
;Page 3:TestRegister     
Reserved30            	EQU        $30
TestSel1Reg           	EQU        $31
TestSel2Reg           	EQU        $32
TestPinEnReg          	EQU        $33
TestPinValueReg       	EQU        $34
TestBusReg            	EQU        $35
AutoTestReg           	EQU        $36
VersionReg            	EQU        $37
AnalogTestReg         	EQU        $38
TestDAC1Reg           	EQU        $39  
TestDAC2Reg           	EQU        $3A   
TestADCReg            	EQU        $3B   
Reserved31            	EQU        $3C   
Reserved32            	EQU        $3D   
Reserved33            	EQU        $3E   
Reserved34		          EQU        $3F