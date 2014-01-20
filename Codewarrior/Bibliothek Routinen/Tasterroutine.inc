;************************************************************************************************
;*      AW32-Tasterroutine-Programm  Version 1.0                                                *
;*                                                                                              *
;*      Revision vom 11. Januar 2013                                                            *
;*                                                                                              *
;*      Name Valentin Bernard                                                                   *
;*      Klasse: 4AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Tasterdruck wird erkannt und in Variable gespeichert. Beim Loslassen wird die Variable  *
;*      gelöscht. Prellzeit verhindert Tasterprellen. Erweiterbar.                              *
;*                                                                                              *
;*      Variablen:                                                                              *
;*      Taster_F0       ds     1T                                                               *
;*      Counter_F0      ds     1T                                                               *
;*      Taser_F1        ds     1T                                                               *
;*      Counter_F1      ds     1T                                                               *
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr   Tasterroutine                                                                     *
;*                                                                                              *
;************************************************************************************************

PRELLZEIT   EQU   10T
PRESSED     EQU   0T
CHECKED     EQU   1T

Tasterroutine   

        brset   0,PORTF,F0_Gedrueckt           ; springe wenn Taster gedrückt    

F0_Nicht_Gedrueckt      
        lda     #0T                            ; Reset wenn Taster nicht gedrückt
        sta     Taster_F0
        sta     Counter_F0
        jmp     F0_Ende

F0_Gedrueckt   
        lda     Counter_F0		       ; Taster mis mindestens PRELLZEIT gedrückt sein		
        cmpa    #PRELLZEIT                
        beq     F0_Setzen
        inca
        sta     Counter_F0
        jmp     F0_Ende

F0_Setzen           
        bset    PRESSED,Taster_F0              ; Setze PRESSED-Pin nach der PRELLZEIT
        jmp     F0_Ende

F0_Ende  
        
        brset   1,PORTF,F1_Gedrueckt           ; Beleiebig erweiterbar

F1_Nicht_Gedrueckt      
        lda     #0T
        sta     Taster_F1
        sta     Counter_F1
        jmp     F1_Ende

F1_Gedrueckt   
        lda     Counter_F1
        cmpa    #10T                
        beq     F1_Setzen
        inca
        sta     Counter_F1
        jmp     F1_Ende

F1_Setzen           
        bset    PRESSED,Taster_F1
        jmp     F1_Ende

F1_Ende
        rts
                
        
                