;************************************************************************************************
;*      AW32-Schrittkette-Programm  Version 1.0                                             	*
;*                                                                                              *
;*      Revision vom 11. Januar 2013                                                            *
;*                                                                                              *
;*      Name Valentin Bernard                                                                   *
;*      Klasse: 4AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Schrittkette mit 3 Schritte, Vor/Zurueck mit Tasterdruck				*
;*	(Tasterroutine nit 2 Tastern nötig)   							*
;*                                                                                              *
;*      Variablen:                                                                              *
;*      Pointer_Schritte    ds     2T                                                           *
;*                                                                                              *
;*      Init:                                                                                   *
;*      jsr   Init_Auswahl                                                                      *  
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr   Auswahl                                                                           *
;*                                                                                              *
;************************************************************************************************



Init_Auswahl  

          ldhx    #S1
          sthx    Pointer_Schritte			; Pointer auf Schritt 1 setzen
          rts

Auswahl
          ldhx    Pointer_Schritte
          jsr     0,x					; Zu Pointer-Adresse springen
          rts
          
S1        
          jsr     Schritt1				; Springe in Schritt 1

          lda     Taster_F0				; Tastervariablen auswerten, T0 vor, T1 zurueck	
          cmpa    #%00000001				
          beq     ZU_S2
          lda     Taster_F1
          cmpa    #%00000001
          beq     ZU_S3      
          rts
          
S2
          jsr     Schritt2				; Springe in Schritt 2

          lda     Taster_F0 				; Tastervariablen auswerten, T0 vor, T1 zurueck
          cmpa    #%00000001
          beq     ZU_S3
          lda     Taster_F1
          cmpa    #%00000001
          beq     ZU_S1
          rts
          
S3
          jsr     Schritt3				; Springe in Schritt 3

          lda     Taster_F0 				; Tastervariablen auswerten, T0 vor, T1 zurueck
          cmpa    #%00000001
          beq     ZU_S1
          lda     Taster_F1
          cmpa    #%00000001
          beq     ZU_S2
          rts
          
ZU_S2
          bset    CHECKED,Taster_F0			; Taster als Verwendet markieren	
          bset    CHECKED,Taster_F1
          ldhx    #S2    				; Schritt in Pointer speichern 	
          sthx    Pointer_Schritte
          rts

ZU_S3
          bset    CHECKED,Taster_F0			; Taster als Verwendet markieren	
          bset    CHECKED,Taster_F1
          ldhx    #S3    				; Schritt in Pointer speichern 	   
          sthx    Pointer_Schritte
          rts
          
ZU_S1
          bset    CHECKED,Taster_F0			; Taster als Verwendet markieren	
          bset    CHECKED,Taster_F1
          ldhx    #S1    				; Schritt in Pointer speichern 	    
          sthx    Pointer_Schritte
          rts





        