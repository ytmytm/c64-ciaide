
; This is the only configuration file
; you should edit only this one

!set machine		= 128			; 64 for C64, 128 for C128

; Kind of IDE interface. 0 - IDE64, !=0 - CIA#3 @ $d300
!set useIDE64	= 1

; If using CIA-style interface: 0 - faster, 1 - slower but sure, use
;                              if you experienced data corruption - this may help
!set extraCareful = 0

; Kind of memory expansion (only matter for C64 without IDE64) 0 - true, !=0 false
!set useRamCart	= 1
!set usePlus60K	= 0

; This is only for RamCart
RC_firstFreeBlock  = 1		; 0-241, space to swap disk driver on RamCart (needs 14 blocks)

; This is only for IDE64
IDE64_SWAPRAM_BASE = $1000	; space for disk driver swapper - $1000-$7200 (need $0e00 length)
				; can't overwrite $2000

; you shouldn't need to change it - GEOS drive type (RAM_DRIVE|DRV_1541)
myDrvType	= $81

; don't change below unless you really know what you are doing
!set HDD_MAXBLK_FREE	= 254*256-256		;total number of free blocks
!set HDD_DIR_TRACK	= 18			;to be compatible with artificial 1541
!set HDD_DIR_DATA	= 1			;first sector with file data
!set HDD_DIR_BORDER	= $df			;border directory sector
!set HDD_DIR_BAM1ST	= $e0			;first sector of BAM-data (SetNextFree requires lastBAM+1=0)
