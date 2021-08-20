# Arduino-Switch-Breaker
this is an improved design based on flehrad's break-in machine: https://github.com/flehrad/Switch-breaker
unlike the original design this one is using a NEMA 17 stepper motor controlled by a Polulu A4988 driver
and an arduino pro micro.

The code itef is using the StepperDriver library by laurb9: https://github.com/laurb9/StepperDriver

# a little more about changes from the original design:
The center pole has been enlarged to 8mm for a 150mm lead screw.
The cams now have holes for M5 screws so they will be
held together by groups of two with a SHF8 lead screw fastener.
The motor plate has mounting holes for a bearing to hold the lead screw so it will rotate freely as possible
the center pole is bigger by 1mm than the other parts,
allowing the lead screw to float there not touching the plastic.
for mouting the beraings an extra small 90 degree part has been added

all parts were printed in petg. other materials could produce different results

https://github.com/kapyuval/Arduino-Switch-Breaker/blob/dev/circuit-diagram.jpg?raw=true
