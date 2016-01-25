
; IDE interface registers (interface by Chris Ward)
; 19.07.2000
; by Maciej 'YTM/Elysium' Witkowiak

IDE_BASE		=	$d700

IDE_DataL		=	IDE_BASE
IDE_Error		=	IDE_BASE+1
IDE_SectorCount		=	IDE_BASE+2
IDE_Sector		=	IDE_BASE+3
IDE_CylinderL		=	IDE_BASE+4
IDE_CylinderH		=	IDE_BASE+5
IDE_Head		=	IDE_BASE+6
IDE_Command		=	IDE_BASE+7
IDE_Status		=	IDE_BASE+7
IDE_SecondaryStatus	=	IDE_BASE+14
IDE_ActiveCommand	=	IDE_BASE+15

; not sure yet
IDE_DataH		=	IDE_BASE+8
