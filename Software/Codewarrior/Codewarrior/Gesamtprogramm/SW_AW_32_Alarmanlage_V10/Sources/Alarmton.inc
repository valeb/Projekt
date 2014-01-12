;************************************************************************************************
;*      ALARMTON-AUSGABE                                                                      	*
;*                                                                                              *
;*      Revision vom 16. Dezember 2013                                                          *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       			                  *
;*      Ein Alarmotn wird als Rechteckimpuls augegeben.                                         *                         		
;*                                                                                              *
;*                                                                                              *
;*      Variabeln:                                                                  		        *
;*      Ton_Timer       ds      1T                                                              *
;*      Ton_Select      ds      1T                                                              * 
;*      Ton_Pointer     ds      2T                                                              *
;*      Frequenz        ds      2T                                                              *
;*                                                                                              *
;*      Eingang:                                                                 	 	            *
;*      jsr   Alarmton                                                     											*
;*                                                                                              *                                                                                            
;*      Include:                                                                              	*
;*      INCLUDE 'Alarmton.inc'                                            											*
;*                                                                                              *
;************************************************************************************************

TONDAUER       EQU     100T


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
      cmpa    #0T             ;Ton-Anzahl
      beq     Ton_0
      cmpa    #1T
      beq     Ton_1
      
      rts     
                                            
Ton_0            
      ldhx    #1396T          ;A7 3520Hz
      sthx    Frequenz
      jsr     Init_PWM
      lda     #1T
      sta     Ton_Select
      
      rts
                        
Ton_1                           
      ldhx    #2352T          ;C7 2093Hz       
      sthx    Frequenz
      jsr     Init_PWM
      lda     #0T
      sta     Ton_Select
      
      rts
     
     
            
     