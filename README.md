# Mini-Filament-Factory

-A DIY Machine to produce 1.75mm filament from plastic pellets

3D printing is cheap nowadays, with the average 1kg PLA spool costing $10-20. But, can we make it even cheaper? The answer is yes, and that is what this project aims to achieve. This is a machine that can take in cheap plastic pellets, with PLA pellets costing $2-3 per kg, and output usable 3D printer filament.  

# Project Goals
1. Filament should be acceptable by a 3D Printer, and it should print well
2. Should be easy to build and run
3. Filament should be cheap to make
4. Handles multiple types of plastic
5. Resistant to jamming and other mechanical flaws

# How Does This Work?

To make 3D printer filament from plastic pellets, it first needs to be melted and extruded. This is the first phase. A Nema 17 stepper motor in the back drives a planetary gearbox with a 1:10 ratio. So, for every 10 rotations of the stepper motor, the output of the gearbox rotates once. Under ideal conditions, this increases the torque by 10 fold and decreases the speed by the same ratio, but in real life, friction and backlash, especially in 3D printed gears, causes energy losses which reduces the efficiency (power in vs power out). The output shaft of the gearbox then drives an auger 25mm in diameter and 430mm long (Although, the AliExpress listing doesn't tell us how long the twisty bit is, which means we can't buy a pipe of exact size). The auger rotates inside of a steel pipe which is also 25mm in inner diameter with some slight clearance. I considered using Aluminum for the pipe since it was cheaper, but the auger is made of HSS (High Speed Steel) which is much, much harder than Aluminum, so it will erode the Aluminum pipe and increase the gap between the auger and the pipe wall, which will create a gap for the molten plastic to flow back, which would be catastrophic. Steel also has a lot lower heat conductivity than aluminum, which might seem worse (since you need to heat up plastic), but it is better, since we don't want the heat from the end creeping up to the back where the hopper for plastic pellets is (it would make the plastic pellets stick early). Heat creep is also why there are fans between the end and the start of the pipe, to stop heat coming to the back of the pipe. The rotating auger pushes the pellets forward to the end of the pipe, where two 150W band heaters act as a hot end. The plastic exits through a nozzle (which is just a hole) that is ~1.75mm in diameter. The plastic then air cools, with fans assisting the process. The filament doesn't come out with the diameter we need due to various factors such as die swell (molten plastic expands as it comes out of the hole), so we need to do some quality control. The cooled filament strand goes into a diameter sensor. The filament passes through two roller bearings, one on the top and the other on the bottom. The one on the bottom is fixed, but the top one moves up and down with the filament diameter. The top bearing moves a lever arm, which amplifies the error by 7x. For example, if the filament is .1mm thicker than needed, the top bearing moves up .1mm, which moves the lever arm, which amplifies the distance, moving the neodymium magnet at the bottom by .7mm. The hall effect sensor picks up the motion of the magnet, and the arduino does some calculations to figure out the current filament diameter. After the filament passes through the diameter sensor, it goes to the final stage, which is a puller. The puller also has two rollers, but only one is a bearing. The top one is a bearing that can be moved up or down by turning a small gear, which turns a larger gear with a 1:5 ratio, which turns a nut, which interfaces with a bolt at the top, moving it up or down. The bolt has a thread of 13 TPI (threads per inches), so for every 13 turns, the nut & bearing will move an inch. Spinning the small gear 5 times will turn the big gear 1 time. Spinning the big gear 1 time will move the nut by 1/13 inches, so spinning the small gear 1 time will move the nut by (1/13)/5 or 1/65 inches. The bottom roller is attached to a Nema 17 Pancake, which has just enough torque to pull the strand. The arduino controls the speed at which it pulls using the feedback from the diameter sensor. Faster pulling will thin out the filament, while slower pulling will thicken it. This process will ensure that we get accurate 1.75mm filament that can be accepted by a 3D printer.

# Electrical Systems


# CAD Images

<img width="822" height="315" alt="image" src="https://github.com/user-attachments/assets/096066fa-ba86-4049-9503-1f263109dbfe" />
<img width="173" height="480" alt="image" src="https://github.com/user-attachments/assets/68efaecc-c182-4a69-97db-1ae08f57696e" />
<img width="788" height="481" alt="image" src="https://github.com/user-attachments/assets/a66111e9-ab58-42f5-95d5-aa2a7d0ab6ea" />
<img width="788" height="481" alt="image" src="https://github.com/user-attachments/assets/686b8050-8732-42a3-958b-1a5f36a9a2eb" />


# Building Instructions
-README, Firmware, guide continuation after assembly

