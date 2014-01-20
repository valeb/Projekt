;************************************************************************************************
;*      AW32-LCD_Steuerung  Version 1.0                                                         *
;*                                                                                              *
;*      Revision vom 11. Januar 2013                                                            *
;*                                                                                              *
;*      Name Valentin Bernard                                                                   *
;*      Klasse: 4AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Ausgaberoutine für 32-Byte LCD-Display, mit BCD-Word Ausgabe                            *
;*                                                                                              *
;*      Init:                                                                                   *
;*      jsr     Init_LCD                ; [LCD_Disp_8Bit.inc] Initialisiert das LCD             *
;*                                                                                              *
;*      Variablen:                                                                              *
;*      LCD_Pointer     ds      2T              ; Pointer auf die aktuelle LCD-Routine          *
;*      LCD_Counter     ds      1T                                                              *
;*      LCD_Oben        ds      16T             ; LCD erste Zeile, 16 Zeichen lang              *
;*      LCD_Unten       ds      16T             ; LCD zweite Zeile, 16 Zeichen lang             *
;*      DelayCounter    ds      1T              ; Grässlich - Delay für LCD...                  *
;*      CopyCounter     ds      1T                                                              *
;*      SourcePointer   ds      2T              ; Pointer für Copy-Routinen                     *
;*      DestPointer     ds      2T              ; Ebenfalls für die Copy-Routinen               *
;*      TextLenght      ds      1T                                                              *
;*      WordZahl        ds      2T                                                              *
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr     Update_LCD              ; [LCD_Disp_8Bit.inc] Beschreibt das LCD                *
;*                                                                                              *
;*      ASM:                                                                                    *
;*      INCLUDE 'LCD_Disp_8Bit_BCDWord.inc'                                                          *
;*                                                                                              *
;************************************************************************************************


;************************************************************************************************
;*                                                                                              *
;*      Initialisierung des LCD-Displays auf 8 Bit                                              *
;*                                                                                              *
;************************************************************************************************

LCD_E_BIT       EQU     0                       ; Definitionen, auf welchem Port die
LCD_E_PORT      EQU     PORTG                   ; Bits "E" und "RS" des LCD hängen
LCD_RS_BIT      EQU     1
LCD_RS_PORT     EQU     PORTG


LCD_DATA_PORT   EQU     PORTA                   ; Auf welchem Port hängt das LCD (Datanbus)?

DELTIME         EQU     20T                                        



;************************************************************************************************
;*                                                                                              *
;*      Init_LCD: Initialisiert Pointer und Variablen für das LCD                               *
;*                                                                                              *
;************************************************************************************************

Init_LCD

                lda     #0T                     ; Counter auf Null setzen
                sta     LCD_Counter
                ldhx    #LCD_Wait_Start         ; LCD-Schrittkette beginnt mit diesem Schritt
                sthx    LCD_Pointer
                rts


;************************************************************************************************
;*                                                                                              *
;*      Update_LCD: Wird vom Main_Loop aufgerufen, kümmert sich um das Beschreiben des LCD      *
;*      Führt praktisch nur nacheinander die verschienden Schritte der Schrittkette aus         *
;*                                                                                              *
;************************************************************************************************
                
Update_LCD                
                ldhx    LCD_Pointer
                jsr     0,X
                rts

;************************************************************************************************
;*                                                                                              *
;*      LCD_Wait_Start: Wartet am Anfang 50 msec, damit sich das LCD intern initialisieren      *
;*      kann.                                                                                   *
;*                                                                                              *
;************************************************************************************************


LCD_Wait_Start
                lda     LCD_Counter
                inca
                sta     LCD_Counter
                cmpa    #10T                     ; Warte 10 x 5msec R.T. = 50 msec
                bne     Exit_LCD_Wait
                ldhx    #LCD_Initializing
                sthx    LCD_Pointer

Exit_LCD_Wait
                rts

;************************************************************************************************
;*                                                                                              *
;*      LCD_Initialisierung: Initialisiert hardwaremäßig das LCD laut Datenblatt                *
;*                                                                                              *
;************************************************************************************************


LCD_Initializing
                lda     #$03
                jsr     Write_LCD_Instruction
                jsr     Delay

                lda     #$03
                jsr     Write_LCD_Instruction
                jsr     Delay


                lda     #$03
                jsr     Write_LCD_Instruction
                jsr     Delay
                                                ;                   x  x  x  DL N  F  x  x

                lda     #%00111000              ; $28 Function Set: 0  0  1  1  1  0  0  0
                jsr     Write_LCD_Instruction   ; DL: 0=4-Bit-Interface  1=8-Bit-Interface
                jsr     Delay


                lda     #%00001100              ; $0C  Display On/Off
                jsr     Write_LCD_Instruction
                jsr     Delay

                                                ;                  x  x  x  x  x  x  ID S
                lda     #%00000110              ; $06  Entry Mode: 0  0  0  0  0  1  1  0
                jsr     Write_LCD_Instruction   ; ID : 0=Adress decrement 1=Adress Increment
                jsr     Delay

                ldhx    #LCD_Cursor_Home
                sthx    LCD_Pointer

                rts

;************************************************************************************************
;*                                                                                              *
;*      LCD_Cursor_Home: Setzt den Cursor (nicht sichtbar) in die "Home"-Position               *
;*                                                                                              *
;************************************************************************************************

LCD_Cursor_Home
                lda     #$80                    ; Cursor Home
                jsr     Write_LCD_Instruction   ; ID : 0=Adress decrement 1=Adress Increment

                ldhx    #LCD_Write_Zeile1
                sthx    LCD_Pointer
                
                clra
                sta     LCD_Counter
                rts

;************************************************************************************************
;*                                                                                              *
;*      LCD_Write_Zeile1: Schreibt die erste Zeile auf das Display                              *
;*                                                                                              *
;************************************************************************************************

LCD_Write_Zeile1

                ldhx    #LCD_Oben-1
Next_Zeile1
                aix     #1T
                lda     0,X
                jsr     Write_Lcd_Data
                jsr     Delay2
                lda     LCD_Counter
                inca
                sta     LCD_Counter
                cmpa    #16T
                bne     Next_Zeile1

                ldhx    #LCD_Goto_Zeile2
                sthx    LCD_Pointer
                
                clra
                sta     LCD_Counter

                rts


;************************************************************************************************
;*                                                                                              *
;*      LCD_Goto_Zeile2: Setzt den Cursor an den Anfang der zweiten Zeile                       *
;*                                                                                              *
;************************************************************************************************

LCD_Goto_Zeile2
                lda     #$C0                    ; Cursor zweite Zeile
                jsr     Write_LCD_Instruction   ; ID : 0=Adress decrement 1=Adress Increment

                ldhx    #LCD_Write_Zeile2
                sthx    LCD_Pointer
                clra
                sta     LCD_Counter
                rts

;************************************************************************************************
;*                                                                                              *
;*      LCD_Write_Zeile2: Schreibt die zweite Zeile auf das Display                             *
;*                                                                                              *
;************************************************************************************************

LCD_Write_Zeile2
                ldhx    #LCD_Unten-1
Next_Zeile2
                aix     #1T
                lda     0,X
                jsr     Write_Lcd_Data  
                jsr     Delay2
                lda     LCD_Counter
                inca
                sta     LCD_Counter
                cmpa    #16T
                bne     Next_Zeile2

                ldhx    #LCD_Cursor_Home
                sthx    LCD_Pointer
                clra
                sta     LCD_Counter

                rts



;************************************************************************************************
;*                                                                                              *
;*      LCD_Instruction: Schreibt eine "Instruction" (Befehl) auf das LCD                       *
;*                                                                                              *
;************************************************************************************************


Write_LCD_Instruction
                bclr    LCD_RS_BIT,LCD_RS_PORT            ; RS = 0
                nop
                nop
                sta     LCD_DATA_PORT
                nop
                nop
                nop
                nop
                bset    LCD_E_BIT,LCD_E_PORT             ; Clock auf "E"
                nop
                nop
                nop
                nop
                nop
                nop
                bclr    LCD_E_BIT,LCD_E_PORT
                rts

Write_Lcd_Data
                bset    LCD_RS_BIT,LCD_RS_PORT            ; RS = 1
                nop
                nop
                nop
                nop
                sta     LCD_DATA_PORT
                nop
                nop
                nop
                nop
                nop
                nop
                bset    LCD_E_BIT,LCD_E_PORT             ; Clock auf "E"
                nop
                nop
                bclr    LCD_E_BIT,LCD_E_PORT
                rts




Delay           ldhx    #$500
next_x          aix     #-1
                cphx    #0
                bne     next_x
                rts


Delay2
                lda     DelayCounter
                inca
                sta     DelayCounter
                cmpa    #DELTIME
                bne     Delay2
                clra
                sta     DelayCounter
                rts

;************************************************************************************************
;*                                                                                              *
;*      Utility: Kopiert einen "TextLenght"-langen Text von einer Position (SourcePointer)      *
;*      in eine andere (DestPointer) um.                                                        *
;*                                                                                              *
;************************************************************************************************

CopyText
        clra
        sta     CopyCounter
NextCopyText
        ldhx    SourcePointer
        lda     0,X
        aix     #1
        sthx    SourcePointer
        ldhx    DestPointer
        sta     0,X
        aix     #1T
        sthx    DestPointer
        lda     CopyCounter
        inca
        sta     CopyCounter
        cmpa    TextLenght                  ; Lenght = Anzahl der Zeichen, die zu kopieren sind
        bne     NextCopyText
 rts

;************************************************************************************************
;*                                                                                              *
;*      Dezimal-BCD: Wandelt eine Dezimalzahl in eine BCD-Zahl um und schreibt sie              *
;*      in die Position "DestPointer", "DestPointer+1" und "DestPointer+2"                      *
;*      Die zu wandelnde Zahl steht im Register A                                               *
;*                                                                                              *
;************************************************************************************************


DezimalBCD
        clrh                            ; da 8 Bit-Division: H = 0, A hat ja schon den Wert, X
        ldx     #10T                    ; noch mit 10 laden
        div
        psha                           ; Ergebnis in A, Rest in H
        pshh                           ; Rette das Ergebnis auf den Stack
        pula
        add     #$30                   ; "0" dazuzählen
        ldhx    DestPointer
        sta     2,X
        pula
        clrh
        ldx     #10T
        div
        psha
        pshh
        pula
        add     #$30
        ldhx    DestPointer
        sta     1,X
        pula
        clrh
        ldx     #10T
        div
        pshh
        pula
        cmpa    #0T
        beq     BCD_NoZero              ; Kill leading Zero...
        add     #$30
        ldhx    DestPointer
        sta     0,X
        rts
BCD_NoZero
        lda     #' '
        ldhx    DestPointer
        sta     0,X
        lda     1,X
        cmpa    #'0'
        bne     Exit_DBCD               ; Kill second Zero if first even zero
        lda     #' '
        sta     1,X
Exit_DBCD        
        rts
        
       
DezimalBCDWord

        sthx    WordZahl
        txa
        ldx     #10T
        div
        psha                           ; Ergebnis in A, Rest in H
        pshh                           ; Rette das Ergebnis auf den Stack
        pula
        ldhx    DestPointer
        sta     4,X
        ldhx    WordZahl
        txa
        ldx     #100T
        div
        psha                           ; Ergebnis in A, Rest in H
        pshh                           ; Rette das Ergebnis auf den Stack
        pula
        ldhx    DestPointer
        sta     3,X
        pula
        jsr     DezimalBCD
                
        rts     


;************************************************************************************************
;*                                                                                              *
;*  Dezimal-BCD: Wandelt eine Dezimalzahl in eine BCD-Zahl um und schreibt sie                  *
;*  in die Position "DestPointer", "DestPointer+1" und "DestPointer+2"                          *
;*  Die zu wandelnde Zahl steht im Register A                                                   *
;*                                                                                              *
;************************************************************************************************

DezimalBCD_Druck
        clrh                           ; da 8 Bit-Division: H = 0, A hat ja schon den Wert, X
        ldx     #10T                   ; noch mit 10 laden
        div
        psha                           ; Ergebnis in A, Rest in H
        pshh                           ; Rette das Ergebnis auf den Stack
        pula
        add     #48T                    ; "0" dazuzählen
        ldhx    DestPointer
        sta     2,X
        pula
        ldx     #10T
        div
        pshh
        pula
        add     #48T
        ldhx    DestPointer
        sta     0,X
        lda     #'.'                    ; Punkt setzen
        sta     1,X
        rts





