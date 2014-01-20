;************************************************************************************************
;*                                                                                              *
;* DUMMY_ISR                                                                                    *
;* Wenn ein falscher Interrupt reinkommt...	                		                                *
;*                                                                                              *
;************************************************************************************************

Dummy_ISR
         nop            ; Im Prinzip nix tun und sofort wieder raus aus dem Interrupt
         rti
         
         