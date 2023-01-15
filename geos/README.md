
# COPYRIGHT

Source code of GEOS driver for a IDE interface (CIAIDE or IDE64), installer
and tools is covered by GNU GPL license.

Specifically it means that you are free to modify it to other flavours of IDE
interfaces for Commodore or even other 8-bit 6502 computers but you MUST
provide source code of your changed version.


# REQUIREMENTS/COMPATIBILITY

For compiling the stuff, you need ACME, a free cross-assembler version 0.97 or later.
http://sourceforge.net/projects/acme-crossass/

You need an IDE interface, it can be CIA-IDE as described in my articles elsewhere.
By default this source code expects that it can be found at $DC20 I/O page. You
can change this by editing proper lines in `inc/ide3.inc` file.
You may also use IDE64 interface, but BE SURE TO READ IMPORTANT NOTE BELOW.

This source code uses 8-bit interface only.
Drive: any IDE disk drive larger than 32MB will be good. I have tested my code
with both types of disk - un/supporing LBA, with sizes ranging from 40MB to 2.5GB.
You should check your disk parameters. Installer tries autoconfiguration, but
it may fail. Wrong parameters mean wrong estimation of disk size and possible
loss of data. Cylinder/Head/Sector numbers are needed also for LBA-capable drives
just to measure their size.
Currently only MASTER device is adressed on IDE cable.

Supported platforms: GEOS 2.0 64/128 and...

```
C64/128 with REU
    - no problems.

C128 without REU and up to 2 different types of drives (e.g. 1571+1541 or 2*1571+1541)
    - no problems.

C64 without REU
    - memory expansion is required, currently supported are:
	+60K
	RamCart 64/128K
	IDE64 internal RAM
```


# CONFIGURATION

Edit `config.inc` and put correct machine value there (64 or 128).

Set there also correct type of IDE interface (IDE64 or CIAIDE).
Check out additional config options which are depended on these two values.

In `inc/ide3.inc` you can set base address for CIA#3.


# IMPORTANT NOTE FOR IDE64 OWNERS!!! BLAME YOURSELF IF YOU DIDN'T READ IT!!!

Filesystem used by this software is totally incompatible with native IDE64
one, so:
- you can't access IDE64 data from GEOS and vice-versa
- on a one disk you can use either IDE64 or filesystem provided by this driver,
  not both
- by doing disk initialization with hddtool on IDE64 native disk with data -
  everything will be erased.
I didn't try, but it should be possible to use two disks - master as GEOS
drive (this driver probes only master) and slave as IDE64 device.
Warning! The driver uses part IDE64 internal RAM as swap space for exchanging
disk drivers. You may lose your IDE64 BIOS settings (floppy speeder etc.).
After power-on IDE64 ROM might hang while identifying hard disk. If it happens -
press RUN/STOP+RESTORE.


# COMPILING

Do: `make` and correct .cvt files will be built and saved in compiled/ directory

Do: `make clean` to remove all built files



# INSTALLATION

Now you can transfer the resulting files to Commodore world and unConvert it
with Convert v2.5 or GeoConvert98.
Or you may use c1541 and geoswrite command to put unconverted file
on a disk image and write that disk image at once.

After unconverting copy auto-exec to your bootdisk and place it so
it would be between Configure and InstallDriveD auto-execs. If you are
not using InstallDriveD just place my installer right after Configure in
the disk directory.

If you don't have REU but you do use two different kinds of disk drives
(like me: 1571+2*1541) you will need my patched version of DeskTop 128 to be
able to get to drive C. It can be found at
ftp://ftp.elysium.pl/tools/geos_software/updates/

HDDTool is for configuring HDD and driver installer, it is an Auto-Exec
HDDSwitch is for changing virtual partitions, it is a DeskAccessory



# USAGE

hddtool.{64|128} will help you to configure your HDD partitions and will install
HDD driver if necessary (it will be necessary on boot :).
Information about disk structure is saved in the very first sector of hard disk.
Read source code for more. Anyway, IDE HDD driver will not be installed if:
- there is no IDE interface
- there is no disk hooked to IDE interface (master)
- disk is not configured
Therefore you must run hddtool for the first time from DeskTop to configure
your disk. Some menu items will not be available unless disk is configured.
The default partition is the partition that will be always set active whenever
hddtool is executed. The first partition has number '0', the last partition is
'65535'. Maxpartition in 'hdd info' option will show you how many partitions
you have. E.g. '5 partitions, 1 default' means that you have 5 partitions total,
the last one has number 4 and the second one is active.

hddswitch is a DeskAcessory for changing virtual disks. On C64 it can't be used
from HDD - store it on disk in another drive and run from there. It is not
possible to execute hddswitch from HDD on C64 because it would crash the
system.



# PARAMETERS

Disk driver in its current state takes the first sector to store configuration
variables. The rest of the disk is divided into partition-like virtual disks
(called 'partition' over this document) that you can change while running GEOS.
Each partition has exactly 65024 sectors and 64768 are available for data so
there is 16192KB of free space. There are 65536 partitions available for total
amount of 1012GB (physically it would be 2024GB because of 8bit interface).
This is more than any ATA-3 IDE disk will ever have. Standard limits the size
to 128GB.

Note that you can't use disk smaller than 32MB to hold one 16MB partition
with 8bit interface.

Transfer rate is... acceptable (erm, I don't know the speed :). It works
somewhat better on C128 in 2MHz mode, it seems that much time is spent on
calculating sector data, however my disk uses CHS only and LBA to CHS
calculations seem to be long (32 bit arithmetic is involved). If your disk
supports LBA this is not an issue because driver internally uses only LBA.
Anyway it doesn't seem to be much slower than RAM disk without DMA at 2MHz
(e.g. geoRAM) and it is way faster than 1541/71.


# DISK STRUCTURE

Tracks are numbered from 1 to 255. Sectors are numbered from 0 to 255.
Disk driver contains current partition size (now always $0000FF00) and
offset from start of disk to start of current partition. Within partition
layout is as below:

```
sector offset
$00000000	track 1, sector 0
$000000FF	track 1, sector 255
$00000100	track 2, sector 0
...
$00001100	track 18, sector 0
...
$0000FEFF	track 254, sector 255
```

Directory occupies whole track 18. (18,0) is the usual directory header, as in
1541. It contains link to (18,1) where file descriptions are stored.
Sector (18,223) contains GEOS border directory and the following 32 sectors
(18,224)-(18,255) contain BAM bitmap. BAM Sectors do not store link in first
two bytes - all 256 bytes are used for allocation map. Sector (18,224) has
map for tracks 1-9.
The rest of directory - file descriptions is identical to classic 1541 scheme.
There are 222 sectors for file descriptions so a partition may contain up to
4368 files.

Maciej 'YTM/Elysium' Witkowiak <ytm@elysium.pl>
