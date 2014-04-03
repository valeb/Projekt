;************************************************************************************************
;*                                                                                              *
;*      Main_Init: Hier beginnt der Controller mit der Arbeit                                   *
;*                                                                                              *
;************************************************************************************************


Main_Init
                ldhx    #E_RAM_END              ; Setze meinen Stackpointer ganz an das Ende der Extended RAM
                txs
                
                jsr     Clear_Zero_Ram          ; [.] Löscht die ZEROPAGE-RAM
                jsr     Clear_Extended_Ram      ; [.] Löscht die EXTENDED-RAM
                
                lda     #0T                     ; Alle Ports vorsichtshalber mal auf Null setzen
                sta     PORTA
                sta     PORTD
                sta     PORTE

                mov     #%11111111,PTADD        ; Data Direction für PORTA
                mov     #%00000001,PTBDD        ; Data Direction für PORTB                
                mov     #%00000000,PTCDD        ; DDR für Port C: 
                mov     #%11000000,PTDDD        ; DDR für PORT D: 
                mov     #%00000000,PTEDD        ; DDR für PORT E: 
                mov     #%00000000,PTFDD        ; DDR für PORT F: 
                mov     #%00000011,PTGDD        ; DDR für PORT G: 

                jsr     Init_MCU                ; [.] Controller Clock usw.       
                jsr     Init_Realtime           ; [Timer.inc] Realtime + PWM-Kanäle
                
;**************| Eigene Inits |******************************************************************              
                
                jsr     Init_Menue
                
                jsr     Init_Alarmton
                jsr     Init_Alarmtimer
                jsr     Change_PW
                
                jsr     Init_LCD                ; [LCD_Disp_8Bit.inc] Initialisiert das LCD
                
                
                cli                             ; Interrupts freigeben

                jmp     Main_Loop

                


;************************************************************************************************
;*                                                                                              *
;*      Initialisierung verschiedener Register der MCU                                          *
;*                                                                                              *
;************************************************************************************************

Init_MCU
                lda     #%01111100
                ;         ||||||||
                ;         ||||||||_____  Fix 0
                ;         |||||||______  Loss of Clock detection enabled (0)
                ;         ||||||_______  Enabel Osc in OFF-Mode (1)
                ;         |||||________  Clock Mode 1:1 = FLL enabled, external Reference
                ;         ||||_________  Clock Mode 
                ;         |||__________  External reference 0=External Clock  1=Ext.Crystal
                ;         ||___________  Freq.Range 0=Low Frequency  1=High Frequency
                ;         |____________  High Gain Osc Select 0=Low Power 1=High Gain
                
                sta     ICGC1      
                
                lda     #0T
                sta     SMCLK
                sta     ICGFLTU
                sta     ICGS2
                sta     ICGS1
                lda     #$01
                sta     ICGC2
                lda     #$0C
                sta     ICGFLTL

                rts
                
                
;************************************************************************************************
;*                                                                                              *
;*      Routinen zum Löschen der gesamten RAM (Zero+Extended)                                   *
;*                                                                                              *
;************************************************************************************************




Clear_Zero_Ram
                lda     #0T
                ldhx    #Z_RAM_START
Next_Clear_Zero
                sta     0,X
                aix     #1T
                cphx    #Z_RAM_END
                bne     Next_Clear_Zero
                rts
                
Clear_Extended_Ram                
                lda     #0T
                ldhx    #E_RAM_START
Next_Clear_Extended
                sta     0,X
                aix     #1T
                cphx    #E_RAM_END-4T
                bne     Next_Clear_Extended   ; Den Stack lasse ich leben...
                rts
                
                