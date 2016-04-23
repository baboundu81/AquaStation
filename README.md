# AquaStation
Project of a connected station to monitor the temperature and the pH of the water of an aquarium.

## Main hardware
* Arduino pro mini (8 MHz, 3.3V) : https://www.arduino.cc/en/Main/arduinoBoardProMini
* ESP-12 Wifi module
* DS18B20 waterproof temperature probe
* Analog pH meter kit : http://www.dfrobot.com/index.php?route=product/product&product_id=1025#.VxtGopOLRo7

## Software
* Embedded software : C++ code Based on FreeRTOS (no necessary but I wanted to learn how to use it)
* External database to periodicatly store pH and temperature values
* Mobile application : multi-plateform application developped with Apache Cordova to get data and notify user if threshold have been reached
