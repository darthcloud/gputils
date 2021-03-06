;  This file is used to test gpdasm with the 12 bit enhanced instruction set.

	list p=16f527

	include p16f527.inc

	CONFIG	FOSC=INTRC_IO		; 0x004
	CONFIG	WDTE=ON			; 0x008
	CONFIG	CP=ON			; 0x000
	CONFIG	MCLRE=OFF		; 0x000
	CONFIG	IOSCFS=8MHz		; 0x040
	CONFIG	CPSW=ON			; 0x000
	CONFIG	BOREN=ON		; 0x100
	CONFIG	DRTEN=OFF		; 0x000
					;-------
					; 0x14C
insn macro file
	ADDWF	file, F
	ANDLW	0xff
	ANDWF	file, F
	BCF	file, 7
	BSF	file, 7
	BTFSC	file, F
	BTFSS	file, F
	CALL	0xff
	CLRF	file
	CLRW
	CLRWDT
	COMF	file, F
	DECF	file, F
	DECFSZ	file, F
	GOTO	0x100
	INCF	file, F
	INCFSZ	file, F
	IORLW	0xff
	IORWF	file, F
	MOVF	file, F
	MOVLB	7
	MOVLW	0xff
	MOVWF	file
	NOP
	OPTION
	RETFIE
	RETLW	0
	RETURN
	RLF	file, F
	RRF	file, F
	SLEEP
	SUBWF	file, F
	SWAPF	file, F
	TRIS	6
	XORLW	0xff
	XORWF	file, F
    endm

	org	0
	insn	0

	org	0x80
	insn	.10

	org	0x100
	insn	.20

	org	0x200
	insn	.25
    end
