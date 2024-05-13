<center>
<h1>Plymouth University Module Support Board</h1>
<h2>An Mbed library to provide high level access to the features of the Module Support Board</h2>
<div>Including :-   </div>
<div>SD Card</div>
<div>LED Matrix</div>
<div>Latched LED Bar</div>
<div>Latched Seven Segment Display</div>
<div>ADCs and DACs</div>
<div>Inertial Measurememtn Unit- </div>
<div>Environmental Sensor</div>
<div>Switches</div>
<div>Buzzer</div>
<div>LCD</div>
</center>

This repository contains the library files only.
The demo code which exercises and tests all the peripherals can be found at
<a href>https://github.com/PlymouthUniversityEEER/UOP_MSB_Test</a>

In order to use the SD Card and I2C, they need to be enabled in mbed_app.json.
This library contains an mbed_app.json file which can be copied into your project directory.
NB. Ensure that it is placed in the root of the project directory.

#Usage 

To set up the library for use with your particular Nucleo board and modulke support board, you should set the correct values in the file "MSB_Config.h"
This file sets up the prerequisites to link your board version and module support board version.
There are currently two defines which you may need to edit.
These are "MSB_VER" and "USE_SD_CARD". The MSB_VER define requires a numerical value of your module support board to be passed to it.
Current versions available are 2 and 4 (most peoiple will have V4).
"USE_SD_CARD" just need to be defined if you wish to use the SD card. If not, this line should be commented out.

```
#define MSB_VER 4
//#define MSB_VER 2

// If you do not wish to use the SD Card, comment this line out
#define USE_SD_CARD
```

Besides these two configuration steps, you should not need to do anything else with the "MSB_Config.h" file/


To use the library in your project you must include the "uop_msb.h" header file where you wish to use it. (eg main.cpp)
This file includes the header files required by the rest of the library, along with predefined and instantiated objects for you to use.
bny default the library creates all of the objects. If you do not wish for a a particular object to be instantiated, you can comment it out in this file.
```
    // Precreated library objects for you to use
    AnalogIn pot(AN_POT_PIN);
    AnalogIn ldr (AN_LDR_PIN);
    AnalogIn signal_in (BNC_AN_PIN);
    AnalogIn mic (MIC_AN_PIN);
    AnalogOut dac_out_1 (DAC1_AN_PIN);
    AnalogOut dac_out_2 (DAC2_AN_PIN);
    LatchedLED latchedLEDs(LEDMODE::STRIP);     
    Buttons buttons;
    // LCD_16X2_DISPLAY disp; <- LCD will not be instantiated as it is commented out
    EnvSensor env (ENV_MOSI,ENV_MISO,ENV_SCLK,ENV_CS);
    Buzzer buzz;
    DIPSwitches dipSwitches (DIP0_PIN,DIP1_PIN,DIP2_PIN,DIP3_PIN);
    MotionSensor motion (MEMS_SDA,MEMS_SCL,MEMS_FREQ);
    Matrix matrix (MATRIX_MOSI,MATRIX_MISO,MATRIX_SCLK,MATRIX_CS,MATRIX_OE);
    TrafficLights traffic(TRAF_RED1_PIN,TRAF_YEL1_PIN,TRAF_GRN1_PIN,TRAF_RED2_PIN,TRAF_YEL2_PIN,TRAF_GRN2_PIN,TRAF_WHITE_PIN);
```

# How to use the library objects

##AnalogIn and AnalogOut

The AnalogIn and AnalogOut objects are just basic Mbed objects. 
More info can be found <a href="https://os.mbed.com/docs/mbed-os/v6.16/apis/i-o-apis.html">here </a>  and <a href="https://os.mbed.com/docs/mbed-os/v6.16/apis/analogout.html">here.</a>


## SD Card

The SDCard classputs a wrapper around Mbed's SDBlockDevice class.
It contains methods for writing to a file, printing data contained within a file and copying the contents of a file to an array.
The user can select whther or not they wish debug messages to be displayed during read/write attempts.
This is done my passing "true" as the final argument to the function calls.

```
    // Create test string 
    char test_string[] = "This is the Plymouth University EEER Module Support Board Test\n";
    // Write the string to a file
    sd.write_file("msb_test.txt", test_string,true);
    // print the contents of the file we've just written to
    sd.print_file("msb_test.txt",true);
    // Copy the contents back into another array
    char array_to_copy_to[256];
    sd.copy_file("msb_test.txt", array_to_copy_to,sizeof(array_to_copy_to),true);
    // Print the new array
    printf("%s\n",array_to_copy_to);
```




