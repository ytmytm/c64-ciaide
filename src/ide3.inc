
; IDE interface registers (CIA#3 interface by Maciej Witkowiak)
; 05.08.2001
; by Maciej 'YTM/Elysium' Witkowiak

cia3base	= $d300
cia3pa		= cia3base	; control port bits, straight connection, no inverters
cia3pb		= cia3base+1	; lower 8 bits data port
cia3ddra	= cia3base+2	; data direction of port A, always output ($ff)
cia3ddrb	= cia3base+3	; data direction of port B, input/output

; upper 16 bit definitions
upperdata	= cia1base	; upper 8 bits data port
upperddr	= cia1base+2	; data direction for upper 8 bits port, input/output

; remaining 12 registers of CIA#3 are unused by IDE interface

;PA connection bits
;+--7---+--6---+--5---+--4---+--3---+--2---+--1---+--0---+
;|  A0  |  A1  |  A2  | /WR  | /RD  | /CS1 | /CS0 | N.C. |
;+------+------+------+------+------+------+------+------+

IDE_rdmask   = %11110111	; mask for activating /rd
IDE_wrmask   = %11101111	; mask for activating /wr

;used IDE commands

IDE_READ	= $20
IDE_WRITE	= $30
IDE_SPINDOWN	= $e0
IDE_SPINUP	= $e1
IDE_SETSPINDOWNNOW	= $e2
IDE_SETSPINDOWN	= $e3
IDE_IDENTIFY	= $ec

;IDE register numbers

IDE_Data	= 0
IDE_Error	= 1
IDE_SectorCount	= 2
IDE_Sector	= 3
IDE_CylinderL	= 4
IDE_CylinderH	= 5
IDE_Head	= 6
IDE_Command	= 7
IDE_Status	= 7
IDE_Status2	= 8		; ATA3 specs say that this is obsolete
IDE_Active	= 9
IDE_Control	= 9

; index this table with register number to get register
; addresses, /rw and /wr lines are
; inactive here
	    !macro IDE_RegisterTable	{
	    !byte %00011100 ;data
	    !byte %10011100 ;error
            !byte %01011100 ;sec. count
            !byte %11011100 ;sector
            !byte %00111100 ;cyll
            !byte %10111100 ;cylh
            !byte %01111100 ;head
            !byte %11111100 ;command/status
            !byte %01111010 ;status2
            !byte %11111010 ;active
	    }
