;************************************************************************************************
;*      AW32-Alarm-Programm  Version 1.0                                                      	*
;*                                                                                              *
;*      Revision vom 16. Dezember 2013                                                          *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       			                  *
;*      Ein Alarmotn wird als Rechteckimpuls augegeben. Es wird zwischen 2 Tönen hin und        *
;*      her gewechselt.                                                                    			*
;*                                                                                              *
;*                                                                                              *
;*      Variabeln:                                                                  		        *
;*      Ton_Timer       ds      1T                                                              *
;*      Ton_Select      ds      1T                                                              * 
;*      T_High          ds      1T                                                              *
;*      T_Low           ds      1T                                                              *
;*                                                                                              *
;*      Include:                                                                              	*
;*      INCLUDE 'Alarmton.inc'                                            											*
;*                                                                                              *
;*      Eingang:                                                                 	 	            *
;*      jsr   Alarmton                                                     											*
;*                                                                                              *
;*                                                                                              *
;************************************************************************************************

TONDAUER       EQU     30T

Init_Alarmton

      lda   #$07
      sta   T_High
      lda   #$47        
      sta   T_Low
  
      lda   #1T
      sta   Ton_Select    
  
      rts

Alarmton

      lda     Ton_Timer
      cmpa    #TONDAUER
      beq     Ton_Steps
      
      lda     Ton_Timer
      inca
      sta     Ton_Timer

      rts

Ton_Steps           
               
      lda     #0T
      sta     Ton_Timer
            

      lda     Ton_Select
      cmpa    #0T             ;Ton-Nummer
      beq     Ton_0
      cmpa    #1T
      beq     Ton_1

      rts     
                                            
Ton_0            
  
      lda  #$07
      sta  T_High 
      lda  #$47        
      sta  T_Low 

      lda     #1T
      sta     Ton_Select
      rts

                        
Ton_1
  
      lda  #$05
      sta  T_High 
      lda  #$74        
      sta  T_Low

      lda     #0T
      sta     Ton_Select
      rts
     
     
     
     
     
     
            
     