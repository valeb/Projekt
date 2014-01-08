;************************************************************************************************
;*                                                                                              *
;*      Hier kommen meine Variablen rein... Zuerst die Zeropage                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     Z_RAM_START            


TimerFlag       ds      1T
RealTimeCounter ds      1T

Ton_Timer       ds      1T
Ton_Select      ds      1T
Ton_Pointer     ds      2T
Frequenz        ds      2T


;************************************************************************************************
;*                                                                                              *
;*      Und hier die sog. "Extend RAM", also der groﬂe Speicher                                 *
;*                                                                                              *
;************************************************************************************************

                ORG     E_RAM_START
                
PWM_Kanal_1     ds      2T   
;PWM_Kanal_2     ds      2T
;PWM_Kanal_3     ds      2T
;PWM_Kanal_4     ds      2T

       
