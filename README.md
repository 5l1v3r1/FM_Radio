# FM_Radio
Creating a FM radio decoder in C
## Objective
Using the RTL-SDR Blog v3, I have obtained a couple of FM Radio captures. These captures
are in the `/captures` folder. My goal is to write a C program to decode these captures and output an audio file that can be played on my computer.
## Comments
- 24 SEP: Finished the working GRC model. At first I was attempting to write the code from scratch in C (bad idea) then decided to move to Python to prototype it. This was a better idea, but the execution was still flawed because there are multiple points a bug could introduce itself from my poor implementation of a low pass filter, digital PLL, or .wav file output. Therefore, I finally created a working model in GRC. Studying that further could lead me to improve my own Python code and then C code.
