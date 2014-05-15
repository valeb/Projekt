;Alle für das Programm benötigten Textausgaben als Subroutinen

A_StartText

          ldhx    #Text_Start1
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght     
          jsr     CopyText
          
          rts
          
A_StartText2          
          
          ldhx    #Text_Start2
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght     
          jsr     CopyText
          
          rts

A_Inaktiv

          ldhx    #Text_Inaktiv
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #32T
          sta     TextLenght
          jsr     CopyText

          rts
          
A_Aktiv             
          
          ldhx    #Text_Aktiv
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText  
          
          rts
          
A_Change
          
          ldhx    #Text_Change
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #19T
          sta     TextLenght
          jsr     CopyText          
          
          rts
          
A_Alarm
          
          ldhx    #Text_Alarm
          sthx    SourcePointer
          ldhx    #LCD_Oben
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText    

          rts 
          
A_PW          
          ldhx    #Text_PW
          sthx    SourcePointer
          ldhx    #LCD_Unten
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText
          
          rts
          
A_PWFalsch

          ldhx    #Text_Fehler
          sthx    SourcePointer
          ldhx    #LCD_Unten
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText 
          
          rts
          
A_Nichts  
  
          ldhx    #Text_Nichts
          sthx    SourcePointer
          ldhx    #LCD_Unten
          sthx    DestPointer
          lda     #16T
          sta     TextLenght          
          jsr     CopyText  
              
          rts 
          
                             
;*******|Texte ******************************************************************************

Text_Alarm
                  ;----------------
          dc.b    '    Alarm!!     '         
Text_Start1
                  ;----------------
          dc.b    'Valentin Bernard'
          dc.b    '      5AEL      '          
Text_Start2
                  ;----------------
          dc.b    ' Maturaprojekt  '
          dc.b    ' Alarmanlage    '
Text_Inaktiv
                  ;----------------
          dc.b    ' Alarm Inaktiv  '
          dc.b    '                '
Text_Change
                  ;----------------
          dc.b    ' Neues Passwort '
          dc.b    'PW:'
Text_Aktiv
                  ;----------------
          dc.b    ' Alarm Aktiv    '           
Text_PW 
                  ;----------------
          dc.b    'PW:             '
Text_Nichts
                  ;----------------
          dc.b    '                '           
Text_Fehler
                  ;----------------
          dc.b    'FALSCHE EINGABE '
            
                            
          
                
          
         