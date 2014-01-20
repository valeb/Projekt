;************************************************************************************************
;*                                                                                              *
;*      Init_Realtime: Initialisiert den RealTime auf Timer2, CH0                                  *
;*                                                                                              *
;*      BusClock: Bei 19,6608 MHz-Quarz ist der Busclock                                        *
;*      1/19,6608MHz x 4 = 50,863 nsec x 4 = 203,451 nsec                                       *
;*      Bei $6000 Zyklen (Dezimal: 24576 Zyklen) á 203,451 nsec = 5 msec                        *
;*                                                                                              *
;************************************************************************************************



Init_Realtime
        lda       #%011110101             ; Dividiert durch 8192 x 203,451... nsec = 1,6666 msec
        sta       SRTISC        

        rts
       

;************************************************************************************************
;*                                                                                              *
;*      Realtime: Diese Interrupt-Routine wird alle 1,666 msec aufgerufen                       *
;*                                                                                              *
;************************************************************************************************


Realtime
       pshh
       lda      #%011110101              ; Acknowledge
       sta      SRTISC                 
       
       lda      RealTimeCounter
       inca
       sta      RealTimeCounter           ; 6 x 1,6666ms = 10 msec genau
       cmpa     #6T
       bne      Exit_Realtime
       clra
       sta      RealTimeCounter

       
       lda      #1T
       sta      TimerFlag


Exit_Realtime       
       pulh

       rti