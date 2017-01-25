# AquaStation
Project of a connected station to monitor the temperature and the pH of the water of an aquarium.

## Main hardware

* ESP-12 Wifi module
* DS18B20 waterproof temperature probe
* Analog pH meter kit : http://www.dfrobot.com/index.php?route=product/product&product_id=1025#.VxtGopOLRo7

## Software
* Embedded software : C++ code Based on a home made scheduller (using timer)
* Back end :
  * External SQL database on a server to periodicatly store pH and temperature values
  * PHP scripts to store and read data from the database
* Frontend : multi-plateform application to get data on the server and adjust the settings of the station


## Tools
* Arduino IDE (Embedded software on ESP-12)
* Eagle (PCB routing)
* [Ionic](http://ionicframework.com/) (Application)

