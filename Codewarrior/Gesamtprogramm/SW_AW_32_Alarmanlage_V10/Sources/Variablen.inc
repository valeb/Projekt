;************************************************************************************************
;*                                                                                              *
;*      Hier kommen meine Variablen rein... Zuerst die Zeropage                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     Z_RAM_START            


TimerFlag         ds      1T
RealTimeCounter   ds      1T

TasteA_Flag       ds      1T                                                            
TasteA_Counter    ds      1T                                                             
TasteB_Flag       ds      1T                                                              
TasteB_Counter    ds      1T                                                              
TasteC_Flag       ds      1T                                                              
TasteC_Counter    ds      1T

Bewegung_Flag     ds      1T
RFID_Flag         ds      1T
PW_Flag           ds      1T

T_High            ds      1T                                                             
T_Low             ds      1T
                  

;************************************************************************************************
;*                                                                                              *
;*      Und hier die sog. "Extend RAM", also der gro�e Speicher                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     E_RAM_START

Blink_Counter     ds      1T

Alarm_Timer       ds      2T
                
Pointer_Schritte  ds      2T                                                             
Zurueck           ds      2T                                                            
Schritte_Counter  ds      2T 

Ton_Timer         ds      1T                                                             
Ton_Select        ds      1T                                                               
Ton_Pointer       ds      2T                                                              
Frequenz          ds      2T 
PWM_Kanal_1       ds      2T                                                             

LCD_Pointer       ds      2T              ; Pointer auf die aktuelle LCD-Routine          
LCD_Counter       ds      1T                                                             
LCD_Oben          ds      16T             ; LCD erste Zeile, 16 Zeichen lang              
LCD_Unten         ds      16T             ; LCD zweite Zeile, 16 Zeichen lang             
DelayCounter      ds      1T              ; Gr�sslich - Delay f�r LCD...                  
CopyCounter       ds      1T                                                             
SourcePointer     ds      2T              ; Pointer f�r Copy-Routinen                     
DestPointer       ds      2T              ; Ebenfalls f�r die Copy-Routinen              
TextLenght        ds      1T                                                              