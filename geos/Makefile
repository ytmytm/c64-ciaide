
all:	hddtool hddswitch

hddswitch: config.inc hddswitch.tas hddswitchcvt.head
	acme -vv hddswitch.tas
	acme -vv hddswitchcvt.head
	mv hddswitch*.cvt compiled/

hddtool: config.inc hddtool.tas hddtoolcvt.head idehdd-chs.bin idehdd-lba.bin setdevice128.tas setdevice64.tas swapdrv128hdd.tas swapdrv64hdd.tas
	acme -vv hddtool.tas
	acme -vv hddtoolcvt.head
	mv hddtool*.cvt compiled/

idehdd-chs.bin: config.inc hddtool.tas idechs.tas
	acme -vv idechs.tas

idehdd-lba.bin: config.inc hddtool.tas idelba.tas
	acme -vv idelba.tas

love:
	@echo "Not war, eh?"

.PHONY: clean

clean:
	-rm idehdd-chs.bin idehdd-lba.bin hddtool.{128,64} compiled/hddtool*.cvt
	-rm hddswitch.{128,64} compiled/hddswitch*.cvt
