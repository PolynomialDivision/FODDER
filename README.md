# FODDER
Fine Dust Daemon

This project is a try to help ["luftdaten.info"](http://luftdaten.info/) get more sensor data.
The daemon will always send the data in certain time steps to the luftdaten.info API.

!["WDR4300 and SDS011"](https://github.com/PolynomialDivision/FODDER/blob/master/docs/img/WDR4300_SDS011.jpg)

## Fine Dust Script

!["Fine Dust Script on LEDE"](https://github.com/PolynomialDivision/FODDER/blob/master/docs/img/fine_dust_lede.png)

### Requirements

    opkg install kmod-usb-serial-ch341 coreutils-stty coreutils-od bc

### Using

	cd bash_script

	sh finedust.sh