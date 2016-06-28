# AquaStation
Project of a connected station to monitor the temperature and the pH of the water of an aquarium.

## Main hardware

* ESP-12 Wifi module
* DS18B20 waterproof temperature probe
* Analog pH meter kit : http://www.dfrobot.com/index.php?route=product/product&product_id=1025#.VxtGopOLRo7

## Software
* Embedded software : C++ code Based on a home made scheduller (using timer)
* External database on a server to periodicatly store pH and temperature values
* PHP scripts to store and read data from the database
* Mobile application : multi-plateform application developped with [Apache Cordova](https://cordova.apache.org/) and [Ionic](http://ionicframework.com/) to get data on the server and adjust the settings of the station
