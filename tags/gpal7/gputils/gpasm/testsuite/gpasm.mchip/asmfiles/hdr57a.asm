; HDR57A.ASM

; This file tests header file usage for the specified processor.

	LIST	P=16CR57A
	INCLUDE	"p16c5x.inc"

 	DATA	_CP_ON,	0X0FF7		; This changes per device
	DATA	_CP_OFF, 0X0FFF
	DATA	_WDT_ON, 0X0FFF
	DATA	_WDT_OFF, 0X0FFB
	DATA	_LP_OSC, 0X0FFC
	DATA	_XT_OSC, 0X0FFD
	DATA	_HS_OSC, 0X0FFE
	DATA	_RC_OSC, 0X0FFF

	DATA	PORTC, 7		; Register Files	
	DATA	PORTB, 6
	DATA	PORTA, 5
	DATA	FSR, 4	
	DATA	STATUS, 3
	DATA	PCL, 2
	DATA	TMR0, 1
	DATA	INDF, 0

	DATA	PA2, 7			; Status Register
	DATA	PA1, 6
	DATA	PA0, 5
	DATA	NOT_TO, 4
	DATA	NOT_PD, 3
	DATA	Z, 2
	DATA	DC, 1
	DATA	C, 0

	DATA 	T0CS, 5			; Option Register
	DATA	T0SE, 4
	DATA	PSA, 3
	DATA	PS2, 2
	DATA	PS1, 1
	DATA	PS0, 0

	END