;************************************************************************************************
;*      AW32-Passwort  Version 1.0                                                              *
;*                                                                                              *
;*      Revision vom 10. Januar 2014                                                            *
;*                                                                                              *
;*      Name: Valentin Beranrd                                                                  *
;*      Klasse: 5AEL                                                                            *
;*      Version: 1.0                                                                            *
;*                                                                                              *
;*      Passworteingabe auf Richtigkeit überprüfen                                              *
;*                                                                                              *
;*      Variabeln:                                                                              *
;*      PW_Flag     ds    1T                                                                    *
;*                                                                                              *
;*      Eingang:                                                                                *
;*      jsr     Check_PW                                                                        *
;*                                                                                              *
;*      In Init kopieren:                                                                       *
;*      jsr   Init_Blinklicht                                                                   *
;*                                                                                              *
;*      In ASM kopieren                                                                         *
;*      INCLUDE 'Passwort.inc'        ; Routine zur Passworteingabe                             *
;************************************************************************************************


Check_PW

        rts