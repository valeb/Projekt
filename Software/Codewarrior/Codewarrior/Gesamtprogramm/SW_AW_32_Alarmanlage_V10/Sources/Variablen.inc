;************************************************************************************************
;*                                                                                              *
;*      Hier kommen meine Variablen rein... Zuerst die Zeropage                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     Z_RAM_START            


TimerFlag       ds      1T
RealTimeCounter ds      1T

TasteA_Flag     ds      1T                                                            
TasteA_Counter  ds      1T                                                             
TasteB_Flag     ds      1T                                                              
TasteB_Counter  ds      1T                                                              
TasteC_Flag     ds      1T                                                              
TasteC_Counter  ds      1T 



;************************************************************************************************
;*                                                                                              *
;*      Und hier die sog. "Extend RAM", also der große Speicher                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     E_RAM_START

Blink_Counter    ds  1T
                
Pointer_Schritte ds     2T                                                             
Zurueck          ds     2T                                                            
Schritte_Counter ds     2T                                                              


LCD_Pointer     ds      2T              ; Pointer auf die aktuelle LCD-Routine          
LCD_Counter     ds      1T                                                             
LCD_Oben        ds      16T             ; LCD erste Zeile, 16 Zeichen lang              
LCD_Unten       ds      16T             ; LCD zweite Zeile, 16 Zeichen lang             
DelayCounter    ds      1T              ; Grässlich - Delay für LCD...                  
CopyCounter     ds      1T                                                             
SourcePointer   ds      2T              ; Pointer für Copy-Routinen                     
DestPointer     ds      2T              ; Ebenfalls für die Copy-Routinen              
TextLenght      ds      1T                                                              