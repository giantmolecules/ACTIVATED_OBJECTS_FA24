/* ----------------------------------------------------------------------
"Simple" Protomatter library example sketch (once you get past all
the various pin configurations at the top, and all the comments).
Shows basic use of Adafruit_Protomatter library with different devices.

This example is written for a 64x32 matrix but can be adapted to others.

Once the RGB matrix is initialized, most functions of the Adafruit_GFX
library are available for drawing -- code from other projects that use
LCDs or OLEDs can be easily adapted, or may be insightful for reference.
GFX library is documented here:
https://learn.adafruit.com/adafruit-gfx-graphics-library
------------------------------------------------------------------------- */

#include <Adafruit_Protomatter.h>

const uint16_t bitmap[] = {
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x20c1, 0xfb23, 0xf282, 0x89e2, 0x3101, 0x0820, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x28c1, 0x1060, 0x0000, 0x0000, 0x5161, 0xfb03, 0x9222, 0x9a02, 0xba22, 0xf2a2, 0xe282, 0xfa62,
0xfa42, 0xfa42, 0xfa62, 0xfa42, 0xc222, 0xba22, 0xb202, 0xba02, 0xfa62, 0x51a2, 0x8a42, 0xfaa2, 0xe262, 0xf242, 0xf242, 0xf242,
0xf242, 0xf242, 0xe242, 0xb202, 0xaa02, 0xd222, 0xe282, 0xf262, 0xba22, 0xaa02, 0xfa22, 0x71c2, 0x5181, 0xfa62, 0xfa62, 0x1060,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3101, 0xfac3, 0xba02, 0xe262, 0xfac3, 0x8202, 0x20a0, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0840, 0x71e2, 0x61c2, 0x4141, 0x20c1, 0x61a2, 0xe242, 0xca22, 0xe242, 0xd222, 0xb202, 0xb202, 0xb222,
0xaa22, 0x9202, 0x7a22, 0x7a02, 0x9a02, 0xa202, 0xb222, 0xba22, 0x9202, 0x3101, 0x8202, 0xfa42, 0xc222, 0xaa02, 0xb202, 0xb202,
0xb222, 0xb222, 0xaa02, 0xaa02, 0xaa02, 0xaa02, 0xb222, 0xba22, 0xaa02, 0xb202, 0xf222, 0x79c2, 0x79c2, 0xe222, 0xfa82, 0x3101,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x30e1, 0xfac3, 0xaa02, 0xaa02, 0xb202, 0xfa82, 0xfac3, 0x4161, 0x0840, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x5161, 0xfb43, 0xfaa2, 0xfa82, 0xda22, 0xaa02, 0xb202, 0xaa02, 0xb202, 0xb202, 0xfa22, 0x79c2,
0x5981, 0x4941, 0x0000, 0x1880, 0x69a2, 0x69a2, 0xc222, 0xfa82, 0x4961, 0x3101, 0x5981, 0x59a2, 0xb222, 0xba22, 0xb202, 0xaa02,
0xba22, 0xe222, 0xf222, 0xe242, 0xc222, 0xb202, 0xaa02, 0xaa02, 0xaa02, 0xaa02, 0xaa02, 0xaa02, 0xba22, 0xfa82, 0xfac3, 0x20a0,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x18a0, 0xfaa3, 0xca02, 0xb202, 0xaa02, 0xb202, 0xd222, 0xfae3, 0x8202, 0x1880,
0x28c1, 0x28e1, 0x28e1, 0x28c1, 0x61a2, 0xd242, 0xaa02, 0xba02, 0xb202, 0xaa02, 0xb202, 0xb202, 0xb202, 0xb202, 0xc222, 0x89e2,
0x89e2, 0x9a22, 0x20a0, 0x4141, 0xfa82, 0x9a02, 0xb222, 0xd242, 0x4961, 0x61a2, 0xa222, 0x4961, 0x69a2, 0xf242, 0xb202, 0xba22,
0xaa02, 0x79e2, 0x71c2, 0xaa22, 0xfaa3, 0xfaa2, 0xfa82, 0xfa82, 0xfa82, 0xfa82, 0xfa82, 0xfaa2, 0xfac3, 0xb2a3, 0x3101, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x9a02, 0xfa82, 0xaa02, 0xca22, 0x71c2, 0x9202, 0xc202, 0xfa82, 0xfa82,
0xfa62, 0xfa82, 0xfaa2, 0xfaa3, 0xfa42, 0xaa02, 0xb202, 0xaa02, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xaa02, 0xda22,
0xfa42, 0xfa62, 0xfa82, 0x59a2, 0xaa42, 0xf222, 0xaa02, 0xa1e2, 0xb222, 0xaa22, 0xfa42, 0xa222, 0x5982, 0xda22, 0xb202, 0xfa42,
0x79e2, 0x5161, 0x61a1, 0x5161, 0x3921, 0x59a2, 0x69e2, 0x7a22, 0x7a02, 0x7a22, 0x7a02, 0x61e2, 0x4961, 0x1880, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x20a0, 0xfaa2, 0xba22, 0xfa42, 0x5181, 0x61a2, 0xfa42, 0xaa02, 0xf242,
0xfa42, 0xda22, 0xd222, 0xd222, 0xb222, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xaa02,
0xaa02, 0xaa02, 0xfa82, 0x3921, 0x4961, 0xfb83, 0xfac3, 0xfac3, 0xfa62, 0xba02, 0xfa22, 0x59a2, 0x4961, 0xfa62, 0xaa02, 0xfa42,
0x69c2, 0x69a2, 0xfb03, 0x59a2, 0x0000, 0x0000, 0x0820, 0x0840, 0x0840, 0x0840, 0x0840, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2080, 0x30e1, 0x89e2, 0xca22, 0xd222, 0x81e2, 0x61a2, 0xf242, 0xfa22, 0xaa02,
0xaa02, 0xaa02, 0xaa02, 0xaa02, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202,
0xb202, 0xb202, 0xda42, 0x81e2, 0x1880, 0x3961, 0x59c2, 0x59a2, 0xfa62, 0xfac3, 0xfb23, 0x5181, 0x5181, 0xfa42, 0xba02, 0xb222,
0x59a2, 0xda22, 0x9a42, 0x20a0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x30c1, 0x6202, 0xb282, 0xf262, 0xa202, 0xb202, 0xaa02, 0xd222, 0xaa22, 0x71c2, 0x8a02, 0xe222,
0xaa02, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202,
0xb202, 0xb202, 0xb202, 0xfac3, 0x28e1, 0x0000, 0x0000, 0x0000, 0x20a0, 0x61c2, 0x51a2, 0x3921, 0xaa02, 0xd222, 0xf242, 0x59a2,
0x5161, 0xfb83, 0x59a2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x3921, 0xfae3, 0xfa82, 0xfa62, 0xfa62, 0xc222, 0xaa02, 0xda42, 0xfa42, 0xfa42, 0x89e2, 0x69a2, 0xaa02,
0xd222, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202,
0xb202, 0xb202, 0xaa02, 0xfa82, 0x59a2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4941, 0xfa82, 0xaa02, 0xfa62, 0x51a2,
0x9242, 0xfaa2, 0x1880, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x1080, 0xfac3, 0xfa62, 0xba02, 0x99e2, 0x9202, 0xda22, 0xb202, 0x61a2, 0x69a2, 0xa222, 0xe242, 0x5981, 0x5981,
0xf242, 0xc222, 0xaa02, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202,
0xb202, 0xb202, 0xb202, 0xfa62, 0x69a2, 0x0020, 0x59a2, 0x79c2, 0x5981, 0x5161, 0x61a2, 0xba42, 0xb222, 0xca22, 0xc222, 0x3921,
0x30e1, 0x1040, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x28e1, 0xfaa2, 0xa202, 0xf242, 0x6981, 0x4121, 0xaa42, 0xfa42, 0x59a2, 0x4121, 0x28c0, 0x28e1, 0x69c2, 0x81e2,
0x69c2, 0x69c2, 0xda22, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202,
0xb202, 0xb202, 0xb202, 0xfa42, 0x79e2, 0x0000, 0x61c2, 0xfb03, 0xfa62, 0xfa62, 0xfa62, 0xca22, 0xb202, 0xfac3, 0x61a2, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x20c1, 0x9a22, 0x81e2, 0xfa62, 0x71a2, 0x2060, 0x4961, 0xc262, 0xf242, 0x79e2, 0x4121, 0x3921, 0xfa62, 0xfa42,
0x89e2, 0x89e2, 0xba22, 0xaa02, 0xb202, 0xaa02, 0xba22, 0xba22, 0xaa02, 0xb202, 0xb202, 0xb202, 0xb202, 0xaa02, 0xaa02, 0xb202,
0xaa02, 0xb202, 0xb202, 0xfa82, 0x69c2, 0x0000, 0x28e1, 0xfb23, 0xfa82, 0xfa62, 0xfa62, 0xfa62, 0xfaa2, 0xa2a3, 0x1880, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0820, 0x51a2, 0xfa82, 0xfa62, 0xb222, 0x4141, 0x3921, 0x61a2, 0x9a02, 0x61a1, 0x81e1, 0xaa21, 0x91c1, 0x91c1,
0xa9e1, 0xba01, 0xca02, 0xba22, 0xaa02, 0xaa02, 0xb222, 0xfa42, 0xda22, 0xb202, 0xaa02, 0xaa02, 0xba22, 0xda22, 0xf242, 0xf222,
0xca22, 0xb202, 0xaa02, 0xfae3, 0x4141, 0x0000, 0x0000, 0x4121, 0x69a2, 0x71c2, 0x71c2, 0x71c2, 0x4961, 0x1880, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0820, 0x4141, 0x9a42, 0xfaa3, 0x59a2, 0x5181, 0x8222, 0x69a1, 0x5961, 0x51a2, 0x6244, 0x5a65, 0x6265,
0x7285, 0x59c2, 0x79a1, 0xfa01, 0xba22, 0xda22, 0x71c2, 0x5181, 0x9a22, 0xfa42, 0xc222, 0xe242, 0xd222, 0xa202, 0x9202, 0x79c2,
0xb222, 0xd222, 0xfa62, 0xfaa3, 0x1060, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5161, 0x7202, 0x4961, 0x69a2, 0xd262, 0x4961, 0x5265, 0x7428, 0xd7e9, 0xce48, 0xbe28,
0xbe48, 0x8468, 0x6ae6, 0x9202, 0xfa22, 0xfa42, 0xaa02, 0x30e1, 0x5161, 0x9202, 0xfaa2, 0xb222, 0x61a2, 0x69a2, 0x4141, 0x5161,
0x71c2, 0x8a02, 0x9a82, 0x3901, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x30e1, 0x9222, 0x69a2, 0x81e2, 0xfa42, 0x5141, 0x4aa6, 0xffec, 0xffeb, 0xff08, 0x93c7, 0x93c8,
0xbc88, 0xde28, 0x9528, 0x52a6, 0x59a1, 0x99e1, 0x69a1, 0x89c1, 0x8a02, 0x4141, 0x3921, 0x4141, 0x61a2, 0xaa42, 0x5181, 0x71c2,
0x9a02, 0x71c2, 0x5141, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x20c1, 0x9a22, 0xfa01, 0xa9c1, 0x89a1, 0x4a25, 0xffec, 0xbe89, 0x52a6, 0x5b2d, 0x8e3f, 0x979f,
0xffff, 0xff12, 0x49e5, 0x51e6, 0x49a4, 0x5a04, 0x4a65, 0x6203, 0x99e1, 0x3901, 0x0000, 0x3941, 0xfa82, 0xfac3, 0x61c2, 0x6181,
0xfa42, 0x8a02, 0x9262, 0x0820, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x1060, 0x1860, 0x51c3, 0x8243, 0x91c1, 0x93e7, 0xf7eb, 0x4a04, 0x5141, 0x61c4, 0x7aa7, 0x72e8,
0x39c6, 0x6392, 0x6bd5, 0x5228, 0x9aeb, 0x62a7, 0xffe9, 0x84aa, 0x51e3, 0x6181, 0x51a2, 0x51a2, 0xfb23, 0xfa62, 0x71e2, 0xe2e3,
0xd242, 0xda22, 0x9242, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0820, 0x28a0, 0x18c1, 0x7429, 0xf78a, 0x51e3, 0x83e7, 0x62c6, 0x6160, 0xf201, 0xda01, 0xa9c0, 0xa1c1,
0x5120, 0x4962, 0x8b6a, 0x3a08, 0x4b10, 0x7c0f, 0x9427, 0xffea, 0x6b87, 0x8202, 0xfac2, 0x20a0, 0x20a0, 0x1880, 0x28e1, 0x59e2,
0x20c1, 0x20a0, 0x1040, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x1880, 0x9a62, 0x8a83, 0x8469, 0xb549, 0x94e9, 0x52e7, 0x5161, 0xfa21, 0xca22, 0xca22, 0xd222, 0xd201,
0xfa22, 0xaa01, 0x91c1, 0x3901, 0x3942, 0x6b91, 0x52c9, 0xcce7, 0xcf8a, 0x5204, 0x1860, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x1060, 0xfa82, 0xba22, 0x7a84, 0x52a6, 0x5328, 0x39a3, 0x7981, 0xfa42, 0xaa02, 0xaa02, 0xaa02, 0xaa02,
0xba22, 0xfa42, 0x81c1, 0x69a1, 0xa221, 0xba02, 0x3963, 0x6b26, 0xffeb, 0x5224, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x30e1, 0x30e1, 0x3901, 0x51c2, 0x3122, 0x3921, 0xf262, 0xb202, 0xb202, 0xb202, 0xb202, 0xb202,
0xaa02, 0xfa42, 0x69c2, 0x69c2, 0xfa42, 0xfa21, 0x4981, 0x73a8, 0xd6c9, 0xe2a3, 0x5181, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0840, 0x1060, 0x20a0, 0xfa62, 0x89c1, 0x61a1, 0xfa42, 0xb202, 0xb202, 0xb202, 0xb202, 0xaa02,
0xba22, 0xd242, 0x4961, 0x79e2, 0xf222, 0xb1c1, 0x59e3, 0xa6ca, 0x9305, 0xb9e1, 0x3921, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3921, 0x8222, 0xca82, 0x61c2, 0x69c2, 0xfa42, 0xaa02, 0xb202, 0xb202, 0xaa02, 0xb202,
0xfa62, 0x59a2, 0x5181, 0xfa42, 0xfa22, 0x81c1, 0x72e6, 0x84a8, 0x9243, 0x5161, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3101, 0xfb03, 0x79c2, 0x4121, 0x5181, 0xfa62, 0xb202, 0xaa02, 0xaa02, 0xca22, 0xfa62,
0x79e2, 0x4141, 0x9202, 0xfa42, 0xfa22, 0x51a2, 0x7408, 0xf588, 0xffe9, 0x5266, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1060, 0xfaa2, 0x79c2, 0x69c2, 0x4961, 0x81c2, 0xfa42, 0xfa42, 0xfa82, 0xf242, 0x71c2,
0x4141, 0x8202, 0xfa42, 0xfa42, 0x71a1, 0x61e3, 0x9c47, 0xfec9, 0xff89, 0x31a4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1060, 0xfaa3, 0x6181, 0x71e2, 0xc262, 0x6181, 0x79e2, 0x8202, 0x71e2, 0x69a2, 0x5981,
0x9222, 0xfa82, 0xfa82, 0xa202, 0x28e1, 0x5981, 0x4982, 0x2123, 0x2122, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8a22, 0x9222, 0x4141, 0xfaa3, 0xc242, 0x69c2, 0x69a2, 0x28c1, 0x4941, 0xfa42,
0xd242, 0x79c2, 0x71e2, 0x3921, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x20a0, 0xfbe3, 0x3921, 0x4121, 0xe262, 0x9a22, 0xe242, 0x30e1, 0x61a2, 0xfa42,
0x69a2, 0x81c2, 0x30e1, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3941, 0x9a42, 0x18a0, 0x5181, 0x61a2, 0x4141, 0x5121, 0x6181, 0xaa42,
0xb262, 0xfac3, 0x3101, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3101, 0x3101, 0x1060, 0x1060, 0x0820, 0xb1c1, 0x7181, 0x20a1,
0x7a02, 0xfaa3, 0x28e1, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0840, 0x0000, 0x0000, 0x0000, 0x1040, 0x9181, 0x30c0,
0x20c1, 0x3921, 0x0840, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
0x0000
};


/* ----------------------------------------------------------------------
The RGB matrix must be wired to VERY SPECIFIC pins, different for each
microcontroller board. This first section sets that up for a number of
supported boards. Notes have been moved to the bottom of the code.
------------------------------------------------------------------------- */

uint8_t rgbPins[] = { 6, 5, 9, 11, 10, 12 };
uint8_t addrPins[] = { A5, A4, A3, A2 };
uint8_t clockPin = 13;  // Must be on same port as rgbPins
uint8_t latchPin = RX;
uint8_t oePin = TX;

Adafruit_Protomatter matrix(
  64,                         // Width of matrix (or matrix chain) in pixels
  4,                          // Bit depth, 1-6
  1, rgbPins,                 // # of matrix chains, array of 6 RGB pins for each
  4, addrPins,                // # of address pins (height is inferred), array of pins
  clockPin, latchPin, oePin,  // Other matrix control pins
  false);                     // No double-buffering here (see "doublebuffer" example)

// SETUP - RUNS ONCE AT PROGRAM START --------------------------------------

void setup(void) {
  Serial.begin(115200);

  // Initialize matrix...
  ProtomatterStatus status = matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if (status != PROTOMATTER_OK) {
    // DO NOT CONTINUE if matrix setup encountered an error.
    for (;;)
      ;
  }
  matrix.drawRGBBitmap(0,0,bitmap,64,32);
  matrix.show();  // Copy data to matrix buffers
}

// LOOP - RUNS REPEATEDLY AFTER SETUP --------------------------------------

void loop(void) {
  // Since there's nothing more to be drawn, this loop() function just
  // shows the approximate refresh rate of the matrix at current settings.
  Serial.print("Refresh FPS = ~");
  Serial.println(matrix.getFrameCount());
  delay(1000);
}
