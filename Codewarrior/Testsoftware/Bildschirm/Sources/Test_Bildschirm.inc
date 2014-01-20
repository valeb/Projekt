;************************************************************************************************
;*      AW32-Test_Bildschirm  Version 1.0                                                      	*
;*                                                                                              *
;*      Revision vom 13. 12. 2013                                                               *
;*                                                                                              *
;*      Name: Valentin Bernard                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                       		                    *
;*                                                                       		                    *
;*                                                                                              *
;*                                                                                              *
;************************************************************************************************


Test
        ldhx    #Text
        sthx    SourcePointer
        ldhx    #LCD_Oben
        sthx    DestPointer
        lda     #16T
        sta     TextLenght
     
        jsr     CopyText
       
        rts
        
        
        
Text
          ;---------------;
    dc.b  'test TEst TEST '        