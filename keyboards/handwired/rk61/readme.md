# rk61

![RK61](http://www.rkgaming.com/res/2020/03-13/14/f8b7ace16549082f6c97fc77aa9ecfca.jpg)  

The RK61 is 61-key ANSI 60% keyboard. This firmware version is meant to revive a keyboard with a destroyed processor (don't ask).  I removed the processor and the micro USB connector and replaced both with an Arduino Pro Micro and handwired it to the rows and columns.

* Keyboard Maintainer: [crstrand](https://github.com/crstrand)
* Hardware Supported: RK61 with Arduino Pro Micro controller

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/rk61 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
