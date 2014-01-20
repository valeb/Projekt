;************************************************************************************************
;*                                                                                              *
;*      Maturaprojekt                                                                           *
;*                                                                                              *
;*                                                                                              *
;*      Name: Max Messavilla                                                                    *
;*      Klasse: 5AEL                                                                            *
;*                                                                                              *
;*      TETRIS                                                                                  *
;*                                                                                              *
;************************************************************************************************

SONG_FREQUENZ       EQU     20T

Init_Tetris_Song

       ldhx   #Init_Ton
       sthx   Ton_Pointer
       rts

Tetris_Song

       lda    Song_Timer
       cmpa   #SONG_FREQUENZ
       beq    Song_Steps

       lda    Song_Timer
       inca
       sta    Song_Timer

       rts


Song_Steps           
               
       lda    #0T
       sta    Song_Timer
       
       lda    Song_Step
       inca
       sta    Song_Step
 
       ldhx   Ton_Pointer
       aix    #1T
       sthx   Ton_Pointer

       lda    Song_Step
       cmpa   #53T            ;max. Step Anzahl
       blo    Frequenz_Select
       
       lda    #0T           ;Frequenz Reset
       sta    Song_Step

       ldhx   #Init_Ton 
       sthx   Ton_Pointer
       rts

       
Frequenz_Select       

       ldhx    Ton_Pointer                 ;D7  2350    A6  1760    E6  1320
       lda     0,x                         ;C7  2090    G6  1570    D6  1174      
                                           ;A#6 1860    F6  1390
Ton_D7      
       cmpa    #1T 
       bne     Ton_C7       
       ldhx    #8392T
       sthx    Frequenz
       bra     Frequenz_Outout
                        
Ton_C7
       cmpa    #2T 
       bne     Ton_Ais6       
       ldhx    #9418T
       sthx    Frequenz
       bra     Frequenz_Outout

Ton_Ais6
       cmpa    #3T 
       bne     Ton_A6       
       ldhx    #10571T
       sthx    Frequenz
       bra     Frequenz_Outout

Ton_A6
       cmpa    #4T 
       bne     Ton_G6       
       ldhx    #11195T
       sthx    Frequenz
       bra     Frequenz_Outout

Ton_G6
       cmpa    #5T 
       bne     Ton_F6      
       ldhx    #12566T
       sthx    Frequenz
       bra     Frequenz_Outout

Ton_F6
       cmpa    #6T 
       bne     Ton_E6      
       ldhx    #14114T
       sthx    Frequenz
       bra     Frequenz_Outout

Ton_E6
       cmpa    #7T 
       bne     Ton_D6      
       ldhx    #14972T
       sthx    Frequenz
       bra     Frequenz_Outout

Ton_D6

       cmpa    #8T
       ldhx    #16755T
       sthx    Frequenz
       bra     Frequenz_Outout

       ldhx    #1T
       sthx    Frequenz

                        
Frequenz_Outout
	
       jsr     Init_PWM

       rts


Init_Ton       
       dc.b   4T          ;A6    BLOCK 1
       dc.b   4T          ;A6
       dc.b   7T          ;E6
       dc.b   6T          ;F6
       dc.b   5T          ;G6
       dc.b   5T          ;G6
       dc.b   6T          ;F6
       dc.b   7T          ;E6
       dc.b   8T          ;D6    BLOCK 2
       dc.b   8T          ;D6
       dc.b   8T          ;D6
       dc.b   6T          ;F6
       dc.b   4T          ;A6
       dc.b   4T          ;A6
       dc.b   5T          ;G6
       dc.b   6T          ;F6
       dc.b   7T          ;E6    BLOCK 3
       dc.b   7T          ;E6
       dc.b   7T          ;E6
       dc.b   6T          ;F6
       dc.b   5T          ;G6
       dc.b   5T          ;G6
       dc.b   4T          ;A6
       dc.b   4T          ;A6
       dc.b   6T          ;F6    BLOCK 4
       dc.b   6T          ;F6
       dc.b   8T          ;D6
       dc.b   8T          ;D6
       dc.b   8T          ;D6
       dc.b   8T          ;D6
       dc.b   5T          ;G6    BLOCK 5
       dc.b   5T          ;G6
       dc.b   5T          ;G6
       dc.b   3T          ;A#6
       dc.b   1T          ;D7
       dc.b   1T          ;D7
       dc.b   2T          ;C7
       dc.b   3T          ;A#6
       dc.b   4T          ;A6    BLOCK 6
       dc.b   4T          ;A6
       dc.b   4T          ;A6
       dc.b   6T          ;F6
       dc.b   4T          ;A6
       dc.b   4T          ;A6
       dc.b   5T          ;G6          
       dc.b   6T          ;F6
       dc.b   7T          ;E6    BLOCK 7
       dc.b   7T          ;E6
       dc.b   7T          ;E6
       dc.b   6T          ;F6
       dc.b   6T          ;G6
       dc.b   6T          ;G6
          
        
        
        
        
        
        
        
        
        
        
        
        
        