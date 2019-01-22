
# Overview
An Arduino powered pulse width modulation (PWM) light controller, for making lights flash with music (or any dynamic sound source) in real time. Amplitude driven, no FFT magic here.
Turn any boring old party into a fantastic light show! You’ll be the talk of the neighborhood! Tested on LEDs and 12" cold cathode lamps, the latter of which produce a very interesting effect when hacked to work at less than 100% power. This is a highly technical solution, based primarily on gut feelings, guestimates, and hand waving. Enjoy!

Note on optimization: This code is written in a strongly object oriented fashion to prioritize readability and extensibility over performance. The same operation could be realized with fewer function calls and a smaller memory footprint.

# Secret Formula
Powering lights with an Arduino, even making them flash, is trivial. Adjusting brightness in real time, responsively, to music of varying tempo and volume, is not! Two main problems had to be solved.

### Amplitude correction
Music has non-uniform volume at various timescales - seconds, tens of seconds, minutes. And if you don’t take this into account, you’ll likely end up with lights that stay solidly on during loud parts and solidly off during quiet parts – not very exciting! Not to mention, without some form of automatic adjustment, the system wouldn't work without manually presetting a bias<sup>1</sup> to compensate for volume differences in different settings.

To ensure a wide dynamic brightness range, we constantly normalize input volume according to a decaying volume envelope. To illustrate, assume microphone input varies in the range [0, 100]. Suppose that, during quiet parts of a song, only values between 0 and 25 might be measured. Without a correction, the light will never exceed 25% brightness until the song gets louder. So we instantiate a variable _currentMax = 0, and on every loop, we perform the following test:

```c++
if(micVal > _currentMax)
    _currentMax = micVal;
```
Now that we have a value for the current maximum song volume (25), we can linearly map micVal to the range [0, _currentMax]. The result is a fuller dynamic brightness range, as the quiet part of the song now outputs brightness from 0-100%, instead of just 0-25% without the correction. Now, what happens when we get to the next, louder part of the music, and most of the sound measured falls in the range of [50, 90]?


An astute reader may observe that there is no correction for the lower volume bound. Seems to work better without one.

### Output Brightness Correction
A naïve implementation (ask me how I know), adjusting pulse width linearly with mic voltage, causes lights to appear only to flash on and off, with very little range in between. I speculate that the human eye perceives light intensity logarithmically, much in the same way that human hearing is best measured on the logarithmic decibel scale. The solution: map the linear microphone voltage input to an inverse logarithmic function to linearize perception of LED brightness. Here's the relevent code from math_.cpp:

```c++
float correction(float rawValue)
{
    return exp(.055452*rawValue) - 1;
}
```
This function actually serves two purposes. In addition to the non-linear correction, it maps an input range of [0, 100] to [0, 255]. I chose [0,100] as the input range to make adjustments more intuitive to reason about, and the analogWrite function takes a single byte as imput to control pulse width from 0 to 255. The result works quite well with the parameters in the code!



# Hardware
![](docs/hardware.png)
![](docs/pro_schematic.png)
* Arduino Uno: This part isn’t terribly important, this code should work just fine with any Arduino variant/clone
* Amplified Microphone Board: My advice is to get a board with instructions. Mine was random chineseium and I had to figure it out by trial and error mostly. Your mic sensitivity will probably affect light response, so you may need to tweak your variables.
* Power Transistor: I used a TIP122 NPN darlington transistor. Probably overkill at 65 watt capacity, but cheap and available.
* 12V power both the Arduino and the lights. I made my own nifty splitter so that I could use a single power supply. You can get 12v power supplies for cheap on amazon, along with connectors.


# Disclaimer
I am a lowly geophysicist, not an electrical engineer. If my spherical cow burns up whatever you're powering with it or explodes in your face, please don't sue me. Use at your own risk. Probably not safe for controlling medical devices or any kind.

# Licensing
I haven't found a particular license that fits my requirements. Until I do, this software is released more or less as open source for NON COMMERCIAL USE ONLY. If you want to sell it, I’d like a cut.

# Footnotes
1. One potential solution is a good Automatic Gain Control(AGC) microphone, however the mic I used had AGC and didn't perform well without the discussed algorithmic adjustments. AGC is not without its own paramaters which have limited or no adjustability with most cheap mics on the market.