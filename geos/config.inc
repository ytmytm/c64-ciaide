
; This is the only configuration file
; you should edit only this one

!set machine		= 128			; 64 for C64, 128 for C128

; Kind of memory expansion (only for C64) 0 - true, !=0 false
!set useRamCart	= 1
!set usePlus60K	= 0

; This is only for RamCart
RC_firstFreeBlock  = 1		; 0-241, space to swap disk driver on RamCart


; you shouldn't need to change it
myDrvType	= $81

; don't change below unless you know what you are doing
!set HDD_MAXBLK_FREE	= 254*256-256		;total number of free blocks
!set HDD_DIR_TRACK	= 18			;to be compatible with artificial 1541
!set HDD_DIR_DATA	= 1			;first sector with file data
!set HDD_DIR_BORDER	= $df			;border directory sector
!set HDD_DIR_BAM1ST	= $e0			;first sector of BAM-data (SNF requires lastBAM+1=0)
