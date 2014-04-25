;************************************************************************************************
;*                                                                                              *
;*      Hier kommen meine Variablen rein... Zuerst die Zeropage                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     Z_RAM_START            


TimerFlag         ds      1T
RealTimeCounter   ds      1T

Bewegung_Flag     ds      1T
Bewegung_Counter  ds      2T

RFID_Flag         ds      1T
PW_Flag           ds      1T
Alarm_Flag        ds      1T

T0_Flag           ds      1T                                                                
T1_Flag           ds      1T                                                                
T2_Flag           ds      1T                                                                
T3_Flag           ds      1T                                                                 
T4_Flag           ds      1T                                                                
T5_Flag           ds      1T                                                                
T6_Flag           ds      1T                                                                 
T7_Flag           ds      1T                                                                
T8_Flag           ds      1T                                                                
T9_Flag           ds      1T                                                                
TOK_Flag          ds      1T                                                                
TVOR_Flag         ds      1T                                                                 
TZUR_Flag         ds      1T     
                  

;************************************************************************************************
;*                                                                                              *
;*      Und hier die sog. "Extend RAM", also der große Speicher                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     E_RAM_START

Blink_Counter     ds      1T
PW_Counter        ds      1T

TValue            ds      1T

Alarm_Timer       ds      2T
Ton_Timer         ds      1T                                                           
Ton_Select        ds      1T                                                             
T_High            ds      1T                                                              
T_Low             ds      1T                                                              
Pointer_LOW       ds      2T                                                              
Pointer_HIGH      ds      2T                                                              
                
Pointer_Schritte  ds      2T                                                           
Schritte_Counter  ds      2T                            

LCD_Pointer       ds      2T              ; Pointer auf die aktuelle LCD-Routine          
LCD_Counter       ds      1T                                                             
LCD_Oben          ds      16T             ; LCD erste Zeile, 16 Zeichen lang              
LCD_Unten         ds      16T             ; LCD zweite Zeile, 16 Zeichen lang             
DelayCounter      ds      1T              ; Grässlich - Delay für LCD...                  
CopyCounter       ds      1T                                                             
SourcePointer     ds      2T              ; Pointer für Copy-Routinen                     
DestPointer       ds      2T              ; Ebenfalls für die Copy-Routinen              
TextLenght        ds      1T                                                   

   
T0_Counter        ds      1T                                                                 
T1_Counter        ds      1T                                                                
T2_Counter        ds      1T                                                                 
T3_Counter        ds      1T                                                                 
T4_Counter        ds      1T                                                                  
T5_Counter        ds      1T                                                                
T6_Counter        ds      1T                                                                
T7_Counter        ds      1T                                                                 
T8_Counter        ds      1T                                                                 
T9_Counter        ds      1T                                                                 
TOK_Counter       ds      1T                                                                 
TVOR_Counter      ds      1T                                                              
TZUR_Counter      ds      1T  


PW_1              ds      1T
PW_2              ds      1T 
PW_3              ds      1T 
PW_4              ds      1T 
PW_5              ds      1T 
PW_6              ds      1T 
PW_7              ds      1T
PW_8              ds      1T 
PW_9              ds      1T 
PW_10             ds      1T                                                                          