# Arduino-Switch-Breaker
this is an improved design based on flehrad's break-in machine: https://github.com/flehrad/Switch-breaker
unlike the original design this one is using a NEMA 17 stepper motor controlled by a Polulu A4988 driver
and an arduino pro micro.

The code itself is using the StepperDriver library by laurb9: https://github.com/laurb9/StepperDriver

# a little more about changes from the original design:
The center pole has been enlarged to 8mm for a 150mm lead screw.
The cams now have holes for M5 screws so they will be
held together by groups of two with a SHF8 lead screw fastener.
The motor plate has mounting holes for a bearing to hold the lead screw so it will rotate freely as possible
the center pole is bigger by 1mm than the other parts,
allowing the lead screw to float there not touching the plastic.
for mouting the beraings an extra small 90 degree part has been added

all parts were printed in petg. other materials could produce different results

https://raw.githubusercontent.com/kapyuval/Arduino-Switch-Breaker/dev/circuit-diagram.jpg

# 3D Printed parts

 * 2 x Motor Holder
 * 4 x Cam
 * 8 x Switch Rack
 * 4 x 90 Degree Adapter

# BOM

* 4x20mm M5
* 4x10mm M5
* 4x30mm M5
* 4xM5 nuts

* 1x8mm to 4mm stepper motor adapter (or get other adapter that fits your motor shaft)
* 1x150mm lead screw with 8mm diameter, 2mm pitch, 4mm lead 
* 2xSHF8 8mm lead screw fasteners
* 2xKP08 Shaft holder bearing
* 1xNEMA 17 motor (any bipolar motor will work)
* 32xDSA keycaps

* 12V dc power supply
* Polulu A4988 stepper motor driver
* arduino pro micro
* (optional) breadboard

* a set with a shaft, two bearing and an 8mm to 8mm adapter (if it fits your motor shaft)
recommended even of you don't use the adapter beacause shipping would be more expensive if 
you buy the bearings separately when purchased seperately
https://www.amazon.com/gp/product/B097JBT1TF/
18.69$

* a single 150mm lead screw
https://www.amazon.com/Screw-Pitch-Length-Copper-Printer/dp/B08GS7TY4J
7.99$

* 2 pcs KP08 bearing shaft holder
https://www.amazon.com/PAZIKO-Diameter-Bearing-Mounted-Support/dp/B08NK8JCJ1
8.99$

* 2 pcs SHF8 fastener
https://www.amazon.com/Aluminum-Holder-Linear-Support-Bearing/dp/B01G0ENHFE
4.29$

* M5 screw assortment.
i got this one, it's always good to have some extras
https://www.amazon.com/gp/product/B07WZHN2XS
12.99$

* Stepper motor
The specific one i used was jut one i had laying around. this model: 42SHD0217-24B
get a bipolar 4 wires motor. it's really important to invest in a good quality motor
https://www.amazon.com/DROK-2-Phrase-Universal-Electric-Engraving/dp/B06XSYP24P
17.59$

* arduino pro micro
aliexpress probably has those for cheaper
https://www.amazon.com/ATmega32U4-Replace-ATmega328-Leonardo-Interface/dp/B086JK79JJ
7.23$

* Polulu A4988 driver
https://www.amazon.com/Printer-Accessory-Reprap-Stepper-Heatsink/dp/B0868F8LDD
3.42$

* 12v power supply with a 2 wire adapter
https://www.amazon.com/dp/B01AZLA9XQ
6.99$

* dupont wire for connecting stuff
https://www.amazon.com/QQQ-Breadboard-Multicolored-Arduino-Raspberry/dp/B0925KFP3F
5.28$

* (Optional) breadboard for prototyping (or if you don't want to commit the pro micro)
you could also solder or connect directly 
https://www.amazon.com/dp/B07FYBBVYR
6.58$
breadboard/wires bundle
https://www.amazon.com/DaFuRui-Breadboard-400-Point-Multiple-Preformed/dp/B07KGQHJW8
13.99$

*(Optional - if you already have ones) DSA keycaps (x37). use a set you don't care destroying. 
those are prbably the cheapest on amazon with more than 32 keycaps
https://www.amazon.com/YMDK-Keycap-Switches-Mechanical-Keyboard/dp/B079GPVBQ2
13.5$


Total
* everything with wires only (no keycaps)
76.48$
* everything with breadboard (no keycaps)
85.19$

* DSA keycaps are another 13.99$
