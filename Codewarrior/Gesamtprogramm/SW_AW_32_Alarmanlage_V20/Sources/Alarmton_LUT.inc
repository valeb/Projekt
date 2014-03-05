;************************************************************************************************
;*      AW32-Alarm-Programm  Version 1.0                                                      	*
;*                                                                                              *
;*      Revision vom 21. Februar 2014                                                           *
;*                                                                                              *
;*      Name: Adler Philip                                                                      *
;*      Urheber: Bernard Valentin                                                               *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       	                  		*
;*      Ein Alarmotn wird als Rechteckimpuls augegeben. Es wird zwischen 2 Tönen hin und        *
;*      her gewechselt.                                                                        	*
;*                                                                                              *
;*                                                                                              *
;*      Variabeln:                                                                          		*
;*      Ton_Timer       ds      1T                                                              *
;*      Ton_Select      ds      1T                                                              * 
;*      T_High          ds      1T                                                              *
;*      T_Low           ds      1T                                                              *
;*      Pointer_LOW     ds      2T                                                              *
;*      Pointer_HIGH    ds      2T                                                              *
;*                                                                                              *
;*      Include:                                                                              	*
;*      INCLUDE 'Alarmton.inc'                                            	                		*
;*                                                                                              *
;*      In Init kopieren:                                                                       * 
;*      jsr     Init_Alarmton                                                                   * 
;*                                                                                              *
;*      Eingang:                                                                             	 	*
;*      jsr   Alarmton                                                     	                		*
;*                                                                                              *
;*                                                                                              *
;************************************************************************************************

TONDAUER       EQU     20T

Init_Alarmton           
      ldhx    #LUT_HIGH
      sthx    Pointer_HIGH
                
      ldhx    #LUT_LOW
      sthx    Pointer_LOW
   
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
            
      ldhx    Pointer_HIGH
      lda     0,X        
      sta     T_High
      
      ldhx    Pointer_LOW
      lda     0,X        
      sta     T_Low
          
      ldhx  Pointer_HIGH
      aix   #1T
      sthx  Pointer_HIGH
          
      cphx  #LUT_HIGH_Ende
      beq   LUT_HIGH_Reset
      
Pointer_LOW_INC      
      
      ldhx  Pointer_LOW
      aix   #1T
      sthx  Pointer_LOW
          
      cphx  #LUT_LOW_Ende
      beq   LUT_LOW_Reset
                
      rts     

LUT_HIGH_Reset
          ldhx  #LUT_HIGH
          sthx  Pointer_HIGH
          bra   Pointer_LOW_INC
                        
LUT_LOW_Reset
          ldhx  #LUT_LOW
          sthx  Pointer_LOW
          rts    
  
;************************************************************************************************  
;************************************************************************************************
;*                                           Tabellen                                           *
;************************************************************************************************ 
;************************************************************************************************ 
      
      
;************************************************************************************************
;*                                           LUT_HIGH                                           *
;************************************************************************************************      
      
LUT_HIGH
      
      dc.b       T_C4
      dc.b       T_Cc4
      dc.b       T_D4
      dc.b       T_Dd4
      dc.b       T_E4
      dc.b       T_F4
      dc.b       T_Ff4
      dc.b       T_G4
      dc.b       T_Gg4
      dc.b       T_A4
      dc.b       T_Aa4
      dc.b       T_H4  
      dc.b       T_C5
      dc.b       T_Cc5
      dc.b       T_D5
      dc.b       T_Dd5
      dc.b       T_E5
      dc.b       T_Dd5
      dc.b       T_D5
      dc.b       T_Cc5  
      dc.b       T_C5
      dc.b       T_H4
      dc.b       T_Aa4
      dc.b       T_A4
      dc.b       T_Gg4
      dc.b       T_G4
      dc.b       T_Ff4
      dc.b       T_F4
      dc.b       T_E4
      dc.b       T_Dd4
      dc.b       T_D4
      dc.b       T_Cc4        

LUT_HIGH_Ende

;************************************************************************************************
;*                                           LUT_LOW                                            *
;************************************************************************************************

LUT_LOW      
     
      dc.b       T_C4_L
      dc.b       T_Cc4_L
      dc.b       T_D4_L
      dc.b       T_Dd4_L
      dc.b       T_E4_L
      dc.b       T_F4_L
      dc.b       T_Ff4_L
      dc.b       T_G4_L
      dc.b       T_Gg4_L
      dc.b       T_A4_L
      dc.b       T_Aa4_L
      dc.b       T_H4_L
      dc.b       T_C5_L
      dc.b       T_Cc5_L
      dc.b       T_D5_L
      dc.b       T_Dd5_L
      dc.b       T_E5_L
      dc.b       T_Dd5_L
      dc.b       T_D5_L
      dc.b       T_Cc5_L  
      dc.b       T_C5_L
      dc.b       T_H4_L        
      dc.b       T_Aa4_L
      dc.b       T_A4_L
      dc.b       T_Gg4_L
      dc.b       T_G4_L
      dc.b       T_Ff4_L
      dc.b       T_F4_L
      dc.b       T_E4_L
      dc.b       T_Dd4_L
      dc.b       T_D4_L
      dc.b       T_Cc4_L 
          
LUT_LOW_Ende

;************************************************************************************************
;*                                     Konstanten High                                          *
;************************************************************************************************

T_Pause         EQU     $FF         
T_E5            EQU     $0E
T_Dd5           EQU     $0F
T_D5            EQU     $10
T_Cc5           EQU     $11
T_C5            EQU     $12
T_H4            EQU     $13
T_Aa4           EQU     $14
T_A4            EQU     $15
T_Gg4           EQU     $17
T_G4            EQU     $18
T_Ff4           EQU     $19
T_F4            EQU     $1B
T_E4            EQU     $1D
T_Dd4           EQU     $1E
T_D4            EQU     $20
T_Cc4           EQU     $22
T_C4            EQU     $24  

;************************************************************************************************
;*                                     Konstanten Low                                           *
;************************************************************************************************

T_Pause_L       EQU     $FF       
T_E5_L          EQU     $8F
T_Dd5_L         EQU     $6D
T_D5_L          EQU     $58
T_Cc5_L         EQU     $51
T_C5_L          EQU     $58
T_H4_L          EQU     $70
T_Aa4_L         EQU     $97
T_A4_L          EQU     $D1
T_Gg4_L         EQU     $1D
T_G4_L          EQU     $7D
T_Ff4_L         EQU     $F2
T_F4_L          EQU     $7D
T_E4_L          EQU     $1F
T_Dd4_L         EQU     $DB
T_D4_L          EQU     $B0
T_Cc4_L         EQU     $A2
T_C4_L          EQU     $B1