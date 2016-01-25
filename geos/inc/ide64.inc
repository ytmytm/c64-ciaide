
; IDE64 interface registers
; 23.07.2002
; by Maciej 'YTM/Elysium' Witkowiak

;used IDE commands

IDE_READ	= $20
IDE_WRITE	= $30
IDE_SPINDOWN	= $e0
IDE_SPINUP	= $e1
IDE_SETSPINDOWNNOW	= $e2
IDE_SETSPINDOWN	= $e3
IDE_IDENTIFY	= $ec

;IDE register numbers
;	read: ldx IDE_Data: lda IDE64_IDEBase,x: lda IDE64_IDEDataL
;	write:ldx IDE_Data: sta IDE64_IDEDataL: sta IDE64_IDEBase,x

IDE_Data	= 0
IDE_Error	= 1
IDE_SectorCount	= 2
IDE_Sector	= 3
IDE_CylinderL	= 4
IDE_CylinderH	= 5
IDE_Head	= 6
IDE_Command	= 7
IDE_Status	= 7
IDE_Control	= 14

IDE64_IDEBase	= $de20
IDE64_IDEDataL	= $de30
IDE64_IDEDataH	= $de31
