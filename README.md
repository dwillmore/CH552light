# CH552light

These are a few programs I wrote as a gift for my neighbor's kids.  They enjoyed the lights I had out over the holidays one year and were sad when we took them in, so I made them a replacement that they could have for their own.
The hardware is very simple--just a CH552 demo board with a small strand of WS2812B LEDs attached.  The effect is a walk around the HSV circle to give a sort of rainbow effect.  The colors dim over the course of a half hour allowing the kids to fall asleep.  At which point it stays off until power cycled/reset.
There are a few variants which might be useful if only to show different ways to drive WS2812B LEDs.

This project relies on the Arduino support library https://github.com/DeqingSun/ch55xduino by Deqing Sun which makes this possible on cheap hardware.  If I had it to do over again, I'd write it in raw C using cnlohr's https://github.com/cnlohr/ch32v003fun as those chips are cheaper, better, and not using Arduino is always a plus.

Additionally, I have included the OpenSCAD source and a rendered .STL for the aluminum channel stock and the end case which held the CH552 board.  The board is the WeAct Studio CH552 core board https://github.com/WeActStudio/WeActStudio.CH552CoreBoard  The aluminum channel stock was just some stuff I picked up on Aliexpress that's meant to take 10mm LED strips.  The kind I used was the corner style in black anodized with a white diffuser.  It does a good job diffusing the 60/m pitch WS2812B LED strips.
