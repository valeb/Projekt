;************************************************************************************************
;*                                                                                              *
;*      Hier kommen meine Variablen rein... Zuerst die Zeropage                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     Z_RAM_START            


TimerFlag       ds      1T
RealTimeCounter ds      1T




;************************************************************************************************
;*                                                                                              *
;*      Und hier die sog. "Extend RAM", also der gro�e Speicher                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     E_RAM_START
                
