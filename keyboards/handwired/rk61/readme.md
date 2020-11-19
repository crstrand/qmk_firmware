# rk61

![RK61](https://i.imgur.com/Q27Ttnf.jpg)  

The RK61 is 61-key ANSI 60% keyboard. This firmware version is meant to revive a keyboard with a destroyed processor (don't ask).<br>
![](https://i.imgur.com/jN021Uu.png) HFD48KP500 actually Sonix SN32F268 (Or, at least, pin compatible)<br>
I removed the processor and the micro USB connector and replaced both with an Arduino Pro Micro and handwired it to the rows and columns.

Here is the row/column layout of the PCB
![Row_Column](https://i.imgur.com/ILBRluu.jpg)

Schematic for one column LED and 4 switches
![Partial Schematic](https://i.imgur.com/kl1XOTi.png)

This is the finished wiring
![RK61_Pro_Micro_wiring](https://i.imgur.com/3Ook5fh.jpg)
I reinforced the microUSB connector on the Pro Micro with some epoxy.<br>The Pro Micro has Kapton tape on the back and is held in place with hot-melt glue.<br>
The microUSB connector will sit about 4mm lower in the case, so modification of the hole in the case is required to make room for the microUSB cable's connector.<br>
I also removed the bluetooth module, the battery connector, the destroyed LiPo charging chip, and a destroyed capacitor.

* Keyboard Maintainer: [crstrand](https://github.com/crstrand)
* Hardware Supported: RK61 with Arduino Pro Micro controller

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/rk61 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
