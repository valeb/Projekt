;************************************************************************************************
;*                                                                                              *
;*      Hier kommen meine Variablen rein... Zuerst die Zeropage                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     Z_RAM_START            


TimerFlag       ds      1T
RealTimeCounter ds      1T

RFID_Flag       ds      1T

Daten           ds      1T 
Status          ds      1T


;************************************************************************************************
;*                                                                                              *
;*      Und hier die sog. "Extend RAM", also der groﬂe Speicher                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     E_RAM_START
                
                
Counter         ds      2T                                                              
Adresse         ds      1T                                                              
                 

Initial         ds      1T