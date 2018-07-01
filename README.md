# Pool Graph

https://poolgraph.com/

An IoT device for monitoring a swimming pool.

![Image 1](https://raw.githubusercontent.com/monospacesoftware/poolgraph/master/collateral/poolgraph-v1-1.jpg)
![Image 2](https://raw.githubusercontent.com/monospacesoftware/poolgraph/master/collateral/poolgraph-v1-2.jpg)
![Image 3](https://raw.githubusercontent.com/monospacesoftware/poolgraph/master/collateral/poolgraph-v1-3.jpg)
![Image 4](https://raw.githubusercontent.com/monospacesoftware/poolgraph/master/collateral/poolgraph-v1-4.jpg)

## Features

* Monitor water temperature, filter pressure, air temperature and humidity.
* Online dashboard shows current and historical data.
* Can send txt/email alerts regarding high pressure, the pump running at night, and when to turn on or off a solar heater.

## Components

* [Particle Photon](https://www.particle.io/products/hardware/photon-wifi) - Wifi enabled microcontroller and IoT cloud platform
* [Losant](https://www.losant.com/) - IoT dashboard and workflow engine 

## Required Materials

* [Particle Photon](https://amzn.to/2ymgYTO) - $20 

Amazon sells them for the same price as the Particle website plus quick Prime shipping!

* [DS18B20 Waterproof Digital Temperature Sensor](https://amzn.to/2MyeRiw) - $10 - $15

You'll need a 4.7K ohm resistor for the DS18B20, this one includes it.

* [DHT22 Digital Temperature And Humidity Sensor](https://amzn.to/2LYMOrr) - $7 - $10

Some DHT22 sensor like this one come conveniently mounted on a little circuit board that includes a resistor and a capacitor. Otherwise you'll need another 4.7k-10k ohm resistor.

* [1/4" Pressure Sensor](https://amzn.to/2My9IqY) - $15 - $20

You'll need to check your filter but 1/4" seems to be standard.  This one has a range up to 1.2 MPa which is far higher than a pool filter would ever go, but it does the job.   
 
* [Solderable Prototype Board](https://amzn.to/2JXHyqS) - $5 - $10

There's a lot of variety here, but I've found the Busboards that match a solderless breadboard to be much easier to work with than the green/silver boards with individual holes.

* [Large Outlet Cover](https://amzn.to/2M1SZeG) - $8 - $10

You need a water resistant place to mount the Photon. These deep outlet covers work pretty well, but you may already have space somewhere in your pool's electronics. 

## Optional Materials

* [Connectors](https://amzn.to/2t4KmJb) or [Connectors](https://amzn.to/2LZCP5n) - $5 - $10

The temp sensors and pressure sensor are all 3 pin. You need a way to connect the sensors to the circuit board.  These little polarized connectors work pretty well but you may want to pickup a [crimping tool](https://amzn.to/2thaqzU) also. Otherwise there's always [screw terminals](https://amzn.to/2LZCP5n)

* [Some wire](https://amzn.to/2MAhNLR)

* [Resistors](https://amzn.to/2K2pBr9) - $1 - 10

The temp sensors require a resistor, some come with it, others don't.  Pickup a little [variety pack](https://amzn.to/2MwsKOh), they're great to have for IoT prototyping

* [U.FL Antenna](https://amzn.to/2ygUmnK) - $8 - $10

The Photon's wifi range isn't great. Adding an antenna really helps pickup a wifi signal out at your pool.

* [Small Micro USB Cable](https://amzn.to/2tbenXV) - $4

* [USB wall charger](https://amzn.to/2MArhXm) $5 - $10

## Notes

* The Photon's Micro USB port is fragile. Be careful not to twist or bend it too much or the circuit board connections can break.  Alternatively, power the Photon from your custom circut board with a voltage regular, etc. 

## Circuit Diagram

![Image 5](https://raw.githubusercontent.com/monospacesoftware/poolgraph/master/collateral/poolgraph2_bb.png)

## Particle Setup

TODO

## Losant Setup

TODO
