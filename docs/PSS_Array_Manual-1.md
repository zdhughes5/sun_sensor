## **PINHOLE SUN SENSOR ARRAY MANUAL** 

**June 2024** 

**==> picture [195 x 368] intentionally omitted <==**

**----- Start of picture text -----**<br>
© 2024 StarSpec Technologies Inc. [2»] All rights reserved.<br>**----- End of picture text -----**<br>


**1 Preface** 

**Thank you for working with StarSpec Technologies! We appreciate your partnership!** 

This manual outlines the functionality and purpose of the Pinhole Sun Sensor Array (PSS Array). 

The PSS Array is developed for Louisiana State University for use on the Antarctic Demonstrator for the Advanced Particle Physics Telescope (ADAPT) Long Duration Balloon (LDB) project. 

_**Figure 1:** ADAPT Mission Patch_ 

StarSpec has strong heritage and demonstrated success in high fidelity pointing stability, control and reconstruction for balloon-borne instrumentation at high- and mid-latitudes (LDB and SPB). 

This includes full-sky pointing reconstruction expertise for large, highly constrained astrophysics balloonborne payloads, including SuperBIT, EXCITE, Spider 1/2, BLAST, BOOMERanG, etc. Also, StarSpec has degree, arcminute, arcsecond, and sub-arcsecond reconstruction, feedback, and control capabilities. 

_**Figure 2:** Spider 2—Antarctica 2022/23 LDB Campaign_ 

_**Figure 3:** SuperBIT—Wanaka 2023 SPB Campaign_ 

i 

© 2024 StarSpec Technologies Inc. All rights reserved. 

## **Read this manual before use** 

This manual can provide answers and guidance for use of the PSS Array. Other questions can be directed to StarSpec Technologies. 

## **1.1 Handling & Storage** 

The PSS Array is self housed and mechanically self contained for balloon-borne operations. Thus, there are specific handling and storage considerations that must be followed. 

## **1.1.1 Pinhole Care** 

Caution should be taken when handling the PSS array as to not damage any of the 6 pinhole sub-assemblies. This concerns the pinhole geometry primarily, the user must ensure that the assembly is stored and operated in an environment that will optimize performance. This includes: 

- Storage and Operation in a Humidity free Environment. 

- Caution to possible debris entering pinhole. 

## **1.1.2 Housing Care** 

The housing encompasses all the Pinhole sub-assemblies and the electronics stack. For nominal operations, it is crucial that the housing configuration is maintained. Thus: 

- Do not tighten / remove any screws or plugs. 

- Take care that no objects are inserted into housing apertures. 

- Aperture stickers are only to be removed before flight. 

## **1.1.3 General Cautions** 

- Do not use the product in a wet or humid environment. 

- Do not attempt to disassemble or alter the equipment unless advised by StarSpec Technologies. 

• Ensure rigid mounting to interfaces using the four mounting holes. 

ii © 2024 StarSpec Technologies Inc. All rights reserved. 

|**CONTENTS**|**CONTENTS**|||
|---|---|---|---|
|**1**|**Preface**||**i**|
||1.1<br>Handling & Storage|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|ii|
||1.1.1<br>Pinhole Care|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|ii|
||1.1.2<br>Housing Care|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|ii|
||1.1.3<br>General Cautions<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .||ii|
|**List of Acronyms**|||**1**|
|**List of Figures**|||**2**|
|**List of Tables**|||**2**|
|**2**|**Theory of Operation**||**3**|
|**3**|**High Level Mechanical**||**4**|
|**4**|**Performance**||**5**|
||4.1<br>Specifcations . . . .|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|5|
|**5**|**Components**||**5**|
||5.1<br>GPS Input-Required|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|5|
||5.2<br>Tilt Sensor<br>. . . . .|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|6|
|**6**|**Pinouts & Settings**||**6**|
|**7**|**Commanding & Telemetry Data Formats**||**7**|
||7.1<br>Commands . . . . .|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|7|
||7.1.1<br>Command Details<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .||7|
||7.1.2<br>Command Descriptions . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .||7|
||7.2<br>Telemetry . . . . . .|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|12|
||7.2.1<br>Telemetry Details . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .||12|
||7.2.2<br>Telemetry Descriptions<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .||12|
|**8**|**Sample Programs & API**||**16**|
||8.1<br>Connecting for the First Time . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .||16|
||8.2<br>Parsing the Byte Stream . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .||17|
||8.3<br>Sending Commands|. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|21|
|**9**|**Calibration**||**23**|
||9.1<br>Stage 1 Calibration -|Individual PSS Linearization<br>. . . . . . . . . . . . . . . . . . . . . . . .|23|
||9.2<br>Stage 2 Calibration -|Az/El Correlation . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|23|



iii 

© 2024 StarSpec Technologies Inc. All rights reserved. 

## **List of Acronyms** 

**ADC** Analog-Digital Converter 

**ADAPT** Antarctic Demonstrator for the Advanced Particle-Astrophysics Telescope 

**ASCII** American Standard Code for Information Interchange 

**Az** Azimuth 

**BLAST** Balloon-borne Large APerture Submillimeter Telescope 

**BOOMERanG** Balloon Observations Of Millimetric Extragalactic Radiation and Geophysics 

**El** Elevation 

**EXCITE** Exoplanet Climate Infrared TElescope 

**FDC** Full-Duplex Communication 

- **FSW** Flight Software 

**GGA** Global Positioning System Fix Data (latitude, longitude, altitude) 

**GNSS** Global Navigation Satellite System 

**GPS** Global Positioning System 

**LDB** Long Duration Balloon 

**MCC** Mission Control Center 

**NMEA** National Marine Electronics Association 

**PSD** Position Sensitive Device 

**PSS** Pinhole Sun Sensor 

**RMC** Recommended Minimum Specific GNSS Data (year, month, day, hours, minutes, seconds) 

- **RPi** Raspberry Pi 

**SCC** Single Chip Computer 

**SPB** Super Pressure Balloon 

**SuperBIT** Super-pressure Balloon-borne Imaging Telescope 

**UDP** User Datagram Protocol 

1 

© 2024 StarSpec Technologies Inc. All rights reserved. 

## **List of Figures** 

|1|ADAPT Mission Patch . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|i|
|---|---|---|
|2|Spider 2—Antarctica 2022/23 LDB Campaign . . . . . . . . . . . . . . . . . . . . . . . . . . .|i|
|3|SuperBIT—Wanaka 2023 SPB Campaign . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|i|
|4|Azmuith & Elevation in the Balloon Gondala Context . . . . . . . . . . . . . . . . . . . . . . .|3|
|5|Top Level Assembly of PSS Array . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|4|
|6|SCL3300-D01 Tilt Sensor . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|6|
|7|Serial Connection<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|6|
|8|Power Connection<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|7|
|9|PSS 41 Heat Map<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|23|



## **List of Tables** 

|1|Performance Specifcations for PSS Array . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|5|
|---|---|---|
|2|Operational & Interface Specifcations . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|5|
|3|Serial Connection Pinout<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|6|
|4|Power Connection Pinout<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|7|
|5|Command Data Types . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|7|
|6|Confgure ADC 0 fltering<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|8|
|7|Confgure ADC 1 fltering<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|8|
|8|Confgure ADC 2 fltering<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|8|
|9|Confgure ADC 3 fltering<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|8|
|10|Confgure ADC 4 fltering<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|8|
|11|Confgure ADC 5 fltering<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|8|
|12|gps: Connect the GPS . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|9|
|13|Set the PSS 0 Threshold parameters for AzEl data . . . . . . . . . . . . . . . . . . . . . . . .|9|
|14|Set the PSS 1 Threshold parameters for AzEl data . . . . . . . . . . . . . . . . . . . . . . . .|9|
|15|Set the PSS 2 Threshold parameters for AzEl data . . . . . . . . . . . . . . . . . . . . . . . .|9|
|16|Set the PSS 3 Threshold parameters for AzEl data . . . . . . . . . . . . . . . . . . . . . . . .|9|
|17|Set the PSS 4 Threshold parameters for AzEl data . . . . . . . . . . . . . . . . . . . . . . . .|10|
|18|Set the PSS 5 Threshold parameters for AzEl data . . . . . . . . . . . . . . . . . . . . . . . .|10|
|19|Set the command IP:port for the PSS array. . . . . . . . . . . . . . . . . . . . . . . . . . . . .|10|
|20|Set the Az offset by asserting the current Az of the PSS array . . . . . . . . . . . . . . . . . .|10|
|21|Set the Az offset for the PSS array. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|10|
|22|Set the telemetry IP:port for the PSS array.<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . .|10|
|23|Command the calibration table to a given angle (only available when calibration table is con-||
||nected)<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|11|
|24|Command the calibration table to stop motion and active control, yielding manual motion||
||(only available when calibration table is connected) . . . . . . . . . . . . . . . . . . . . . . . .|11|
|25|Command the calibration table to set the current position to the desired value (only available||
||when calibration table is connected)<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|11|
|26|Command the calibration table to cycle a trapezoidal position profle from start to end for a||
||given number of cycles (only available when calibration table is connected)<br>. . . . . . . . . .|11|
|27|Command the calibration table to have a given maximum speed for all moves - this command||
||does not issue a move, but this speed is used for all goto or cycle commands (only available||
||when calibration table is connected)<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|11|
|28|Miscellaneous / debugging commands (no parameters)<br>. . . . . . . . . . . . . . . . . . . . .|12|
|29|Telemetry Data Types<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|12|
|30|Telemetry Items – total frame size of 833 Bytes . . . . . . . . . . . . . . . . . . . . . . . . . .|16|



2 

© 2024 StarSpec Technologies Inc. All rights reserved. 

## **2 Theory of Operation** 

The PSS Array provides a 240 degree azimuth (Az) Sun position tracker with onboard computational resources for operating stand-alone software. Additionally, the device presents elevation position determination for a local Sun elevation angle of 25 ± 10 degrees, consistent with Antarctic LDB flight in the austral summer. 

_**Figure 4:** Azmuith & Elevation in the Balloon Gondala Context_ 

The independent flight software records and determines time stamped Az/El coordinates. For determining these coordinates, inputs are required by the FSW: RS232 GPS, tip and tilt angles from the horizontal, and time of day. The tip and tilt angles are read from an internal tilt sensor on the custom daughter board mounted to the Raspberry Pi.The PSS uses modularized packaging of the above elements for robust operations in the stratosphere. 

The FSW comprises of a commanding interface for controlling, calibrating, tuning, and regular operations of the PSS. 

The design incorporates pinhole analog sensors, a split array mechanical design, Ethernet interface, and data synchronization via payload. 

The Pinhole Sun Sensor provides the Az/El Sun orientation information relative to the sensor orientation. The Sun is imaged through a series of pinholes onto 2-dimensional position sensitive detectors (PSD) whose outputs are used to calculate the x and y position of the image. The x and y positions are then used to get information about the module’s relative orientation. 

The PSS Array takes the GPS readings along with the x and y coordinates, and translates them to the Array’s orientation information: Azimuth and Elevation. 

3 

© 2024 StarSpec Technologies Inc. All rights reserved. 

## **3 High Level Mechanical** 

Top level assembly of the PSS Array can be seen below. 

_**Figure 5:** Top Level Assembly of PSS Array_ 

4 

© 2024 StarSpec Technologies Inc. All rights reserved. 

## **4 Performance** 

## **4.1 Specifications** 

_**Table 1:** Performance Specifications for PSS Array_ 

|**Performance Specifcations**|**Min.**|**Nom.**|**Max.**|**Units**|
|---|---|---|---|---|
|Nominal Angular Resolution|1.10|5.00|–|arcminute|
|Relative Solar Azimuth Range|–|240|270|degrees|
|Solar Elevation Range|15|25|35|degrees|
|Az / El Determination Rate|–|5|20|Hz|
|Leveling precision|0.05|0.1|–|degree|
|Leveling offset|0.0|0.3|5.0|degree|



_**Table 2:** Operational & Interface Specifications_ 

|**Operational Specifcations**|**Min.**|**Nom.**|**Max.**|**Units**|
|---|---|---|---|---|
|Supply voltage range|18|48|70|Volt|
|Peak Power|–|3.6|7.2|Watt|
|Temperature Range|0|25|85|Celsius|
|Required Input GPS Precision|–|–|5|arcminute|
|Required Input GPS Rate|1|–|–|Hz|
|Required Mounting Precision|–|–|0.1|degrees|



## **5 Components** 

## **5.1 GPS Input-Required** 

A GPS with the following parameters is required: Expected Baud Rate : 9600 bps Expected Message Format: GGA and RMC NMEA sentences. Expected Communication Interface: RS232 

## **Required standard NMEA sentences (1 Hz recommended):** 

GGA: Global Positioning System Fix Data (latitude, longitude, altitude) RMC: GNSS Timing Data (year, month, day, hours, minutes, seconds) 

5 

© 2024 StarSpec Technologies Inc. All rights reserved. 

A resource for the NMEA standard can be found online ( `https://receiverhelp.trimble.com/alloy-gnss/ en-us/NMEA-0183messages_MessageOverview.html` ) or is available upon request. 

## **5.2 Tilt Sensor** 

The tilt sensor is a SCL3300-D01 3-axis inclinometer which measures tip and tilt angles so that the FSW can determine the position of the PSS with respect to the sun. Inclination ranges are limited in Mode 4 to maximum ±10°. 

_**Figure 6:** SCL3300-D01 Tilt Sensor_ 

More details on the SCL3300-D01 can be found online ( `https://www.digikey.ca/en/products/detail/ murata-electronics/SCL3300-D01-1/9950616` ) or available upon request. 

**6 Pinouts & Settings** 

_**Figure 7:** Serial Connection_ 

|**GPS RS232 Signal**<br>**Input DB9-Female**|**J2 Pin**<br>**Number**|
|---|---|
|**Ground**|**Pin 1**|
|**N.C**|**Pin 2**|
|**RxD**|**Pin 3**|
|**TxD**|**Pin 4**|
|**N.C.**|**Pin 5**|
|**RESERVED**|**Pin 6**|
|**RESERVED**|**Pin 7**|
|**RESERVED**|**Pin 8**|
|**RESERVED**|**Pin 9**|



_**Table 3:** Serial Connection Pinout_ 

6 

© 2024 StarSpec Technologies Inc. All rights reserved. 

_**Figure 8:** Power Connection_ 

|**Battery/Gondola**<br>**Power Input**<br>**DB9-Male**|**J3 Pin**<br>**Number**|
|---|---|
|**-Batt**|**Pin 1**|
|**N.C.**|**Pin 2**|
|**N.C.**|**Pin 3**|
|**N.C.**|**Pin 4**|
|**+Batt**|**Pin 5**|
|**-Batt**|**Pin 6**|
|**N.C.**|**Pin 7**|
|**N.C.**|**Pin 8**|
|**+Batt**|**Pin 9**|
|**Additional Ports**||
|**Ethernet**||



_**Table 4:** Power Connection Pinout_ 

## **7 Commanding & Telemetry Data Formats** 

Commands are transmitted to the PSS array as UDP packets over port X within the flight network. 

## **7.1 Commands** 

Commands for the PSS are in a simple ASCII format. Numerical parameters are space-separated following the ASCII command (e.g. “adc ~~0 f~~ ilter 20” to set the ADC filter boxcar size to 20). String or character parameters are also space-separated, but must be quoted (e.g. “gps ~~c~~ onnect 115200 ”/dev/ttyS0”” to set the GPS baud rate to 115.2 kbaud and the device path to /dev/ttyS0). 

## **7.1.1 Command Details** 

|**Type**|**Description**|
|---|---|
|i<br>l<br>f<br>d<br>s|16 bit signed integer<br>32 bit unnormalized integer<br>16 bit normalized floating point<br>32 bit normalized floating point<br>7-bit character string|



_**Table 5:** Command Data Types_ 

7 

© 2024 StarSpec Technologies Inc. All rights reserved. 

## **7.1.2 Command Descriptions** 

Commands are specified in tables below. 

||||||
|---|---|---|---|---|
|**Command: adc**<br>~~**0**~~<br>~~**f**~~**lter**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|boxcar<br>~~s~~ize<br>~~a~~dc<br>~~0~~|i|(1,1000)|0|Boxcar size:|



_**Table 6:** Configure ADC 0 filtering_ 

||||||
|---|---|---|---|---|
|**Command: adc**<br>~~**1**~~<br>~~**f**~~**lter**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|boxcar<br>~~s~~ize<br>~~a~~dc<br>~~1~~|i|(1,1000)|0|Boxcar size:|



_**Table 7:** Configure ADC 1 filtering_ 

||||||
|---|---|---|---|---|
|**Command: adc**<br>~~**2**~~<br>~~**f**~~**lter**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|boxcar<br>~~s~~ize<br>~~a~~dc<br>~~2~~|i|(1,1000)|0|Boxcar size:|



_**Table 8:** Configure ADC 2 filtering_ 

||||||
|---|---|---|---|---|
|**Command: adc**<br>~~**3**~~<br>~~**f**~~**lter**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|boxcar<br>~~s~~ize<br>~~a~~dc<br>~~3~~|i|(1,1000)|0|Boxcar size:|



_**Table 9:** Configure ADC 3 filtering_ 

||||||
|---|---|---|---|---|
|**Command: adc**<br>~~**4**~~<br>~~**f**~~**lter**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|boxcar<br>~~s~~ize<br>~~a~~dc<br>~~4~~|i|(1,1000)|0|Boxcar size:|



_**Table 10:** Configure ADC 4 filtering_ 

||||||
|---|---|---|---|---|
|**Command: adc**<br>~~**5**~~<br>~~**f**~~**lter**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|boxcar<br>~~s~~ize<br>~~a~~dc<br>~~5~~|i|(1,1000)|0|Boxcar size:|



_**Table 11:** Configure ADC 5 filtering_ 

8 

© 2024 StarSpec Technologies Inc. All rights reserved. 

||||||
|---|---|---|---|---|
|**Command: gps**<br>~~**c**~~**onnect**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|baud<br>~~g~~ps|l|(0,115200)|115200|gps: Baud rate (bps) for GPS|



_**Table 12:** gps: Connect the GPS_ 

||||||
|---|---|---|---|---|
|**Command: pss**<br>~~**0**~~<br>~~**t**~~**hreshold**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|thresh<br>~~p~~ss<br>~~0~~<br>radius<br>~~p~~ss<br>~~0~~|d<br>d|(0,10)<br>(0,20)|0.4<br>2.15|pss: Per channel threshold [V]<br>pss: Per PSS sensor radius threshold [mm]|



_**Table 13:** Set the PSS 0 Threshold parameters for AzEl data_ 

||||||
|---|---|---|---|---|
|**Command: pss**<br>~~**1**~~<br>~~**t**~~**hreshold**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|thresh<br>~~p~~ss<br>~~1~~<br>radius<br>~~p~~ss<br>~~1~~|d<br>d|(0,10)<br>(0,20)|0.4<br>2.15|pss: Per channel threshold [V]<br>pss: Per PSS sensor radius threshold [mm]|



_**Table 14:** Set the PSS 1 Threshold parameters for AzEl data_ 

## **Command: pss** ~~**2 t**~~ **hreshold** 

|**Command: pss**<br>~~**2**~~<br>~~**t**~~**hreshold**|**Command: pss**<br>~~**2**~~<br>~~**t**~~**hreshold**|**Command: pss**<br>~~**2**~~<br>~~**t**~~**hreshold**|**Command: pss**<br>~~**2**~~<br>~~**t**~~**hreshold**|**Command: pss**<br>~~**2**~~<br>~~**t**~~**hreshold**|
|---|---|---|---|---|
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|thresh<br>~~p~~ss<br>~~2~~<br>radius<br>~~p~~ss<br>~~2~~|d<br>d|(0,10)<br>(0,20)|0.4<br>2.15|pss: Per channel threshold [V]<br>pss: Per PSS sensor radius threshold [mm]|



_**Table 15:** Set the PSS 2 Threshold parameters for AzEl data_ 

||||||
|---|---|---|---|---|
|**Command: pss**<br>~~**3**~~<br>~~**t**~~**hreshold**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|thresh<br>~~p~~ss<br>~~3~~<br>radius<br>~~p~~ss<br>~~3~~|d<br>d|(0,10)<br>(0,20)|0.4<br>2.15|pss: Per channel threshold [V]<br>pss: Per PSS sensor radius threshold [mm]|



_**Table 16:** Set the PSS 3 Threshold parameters for AzEl data_ 

9 

© 2024 StarSpec Technologies Inc. All rights reserved. 

||||||
|---|---|---|---|---|
|**Command: pss**<br>~~**4**~~<br>~~**t**~~**hreshold**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|thresh<br>~~p~~ss<br>~~4~~<br>radius<br>~~p~~ss<br>~~4~~|d<br>d|(0,10)<br>(0,20)|0.4<br>2.15|pss: Per channel threshold [V]<br>pss: Per PSS sensor radius threshold [mm]|



_**Table 17:** Set the PSS 4 Threshold parameters for AzEl data_ 

||||||
|---|---|---|---|---|
|**Command: pss**<br>~~**5**~~<br>~~**t**~~**hreshold**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|thresh<br>~~p~~ss<br>~~5~~<br>radius<br>~~p~~ss<br>~~5~~|d<br>d|(0,10)<br>(0,20)|0.4<br>2.15|pss: Per channel threshold [V]<br>pss: Per PSS sensor radius threshold [mm]|



_**Table 18:** Set the PSS 5 Threshold parameters for AzEl data_ 

||||||
|---|---|---|---|---|
|**Command: set**<br>~~**c**~~**md**<br>~~**a**~~**ddress**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|override<br>~~c~~md|s|(”0.0.0.0:12000”,<br>”255.255.255.255:60000”)|10.0.0.2:54345|Set the IP:port on which to receive<br>commands|



_**Table 19:** Set the command IP:port for the PSS array._ 

||||||
|---|---|---|---|---|
|**Command: set**<br>~~**c**~~**urrent**<br>~~**a**~~**z**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|current<br>~~a~~z|d|(-360,360)|0|Current Az (deg):|



_**Table 20:** Set the Az offset by asserting the current Az of the PSS array_ 

|**Command: set**<br>~~**o**~~**ffset**<br>~~**a**~~**z**<br>**Parameter**<br>**Type**<br>**(Min,Max)**<br>**Default**<br>**Description**<br>offset<br>~~a~~z<br>d<br>(-360,360)<br>0<br>Az offset (deg):|**Command: set**<br>~~**o**~~**ffset**<br>~~**a**~~**z**<br>**Parameter**<br>**Type**<br>**(Min,Max)**<br>**Default**<br>**Description**<br>offset<br>~~a~~z<br>d<br>(-360,360)<br>0<br>Az offset (deg):|**Command: set**<br>~~**o**~~**ffset**<br>~~**a**~~**z**<br>**Parameter**<br>**Type**<br>**(Min,Max)**<br>**Default**<br>**Description**<br>offset<br>~~a~~z<br>d<br>(-360,360)<br>0<br>Az offset (deg):|**Command: set**<br>~~**o**~~**ffset**<br>~~**a**~~**z**<br>**Parameter**<br>**Type**<br>**(Min,Max)**<br>**Default**<br>**Description**<br>offset<br>~~a~~z<br>d<br>(-360,360)<br>0<br>Az offset (deg):|**Command: set**<br>~~**o**~~**ffset**<br>~~**a**~~**z**<br>**Parameter**<br>**Type**<br>**(Min,Max)**<br>**Default**<br>**Description**<br>offset<br>~~a~~z<br>d<br>(-360,360)<br>0<br>Az offset (deg):|
|---|---|---|---|---|
||**Type**|**(Min,Max)**|**Default**|**Description**|
||d|(-360,360)|0|Az offset (deg):|



_**Table 21:** Set the Az offset for the PSS array._ 

||||||
|---|---|---|---|---|
|**Command: set**<br>~~**t**~~**lm**<br>~~**a**~~**ddress**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|override<br>~~t~~lm|s|(”0.0.0.0:12000”,<br>”255.255.255.255:60000”)|10.0.0.1:53335|Set the IP:port on which to receive<br>telemetrydata|



_**Table 22:** Set the telemetry IP:port for the PSS array._ 

10 

© 2024 StarSpec Technologies Inc. All rights reserved. 

||||||
|---|---|---|---|---|
|**Command: table**<br>~~**g**~~**oto**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|cmd<br>~~p~~osition<br>~~t~~able|d|(-360,360)|0|Commanded table position (deg):|



_**Table 23:** Command the calibration table to a given angle (only available when calibration table is connected)_ 

||||||
|---|---|---|---|---|
|**Command: table**<br>~~**s**~~**top**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|–|–|–|–|–|



_**Table 24:** Command the calibration table to stop motion and active control, yielding manual motion (only available when calibration table is connected)_ 

||||||
|---|---|---|---|---|
|**Command: table**<br>~~**s**~~**et**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|set<br>~~p~~osition<br>~~t~~able|d|(-360,360)|0|Current table position (deg):|



_**Table 25:** Command the calibration table to set the current position to the desired value (only available when calibration table is connected)_ 

||||||
|---|---|---|---|---|
|**Command: table**<br>~~**c**~~**ycle**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|cycle<br>~~s~~tart<br>~~t~~able|d|(-360,360)|0|Starting position for table cycle (deg):|
|cycle<br>~~e~~nd<br>~~t~~able|d|(-360,360)|0|Ending position for table cycle (deg):|
|cycles<br>~~l~~eft<br>~~t~~able|d|(-360,360)|0|Number of cycles to execute (negative for infnite):|



_**Table 26:** Command the calibration table to cycle a trapezoidal position profile from start to end for a given number of cycles (only available when calibration table is connected)_ 

||||||
|---|---|---|---|---|
|**Command: table**<br>~~**s**~~**et**<br>~~**s**~~**peed**|||||
|**Parameter**|**Type**|**(Min,Max)**|**Default**|**Description**|
|cmd<br>~~s~~peed<br>~~t~~able|d|(0,90)|0|Table speed (deg):|



_**Table 27:** Command the calibration table to have a given maximum speed for all moves - this command does not issue a move, but this speed is used for all goto or cycle commands (only available when calibration table is connected)_ 

11 © 2024 StarSpec Technologies Inc. All rights reserved. 

|**Command**|**Description**|
|---|---|
|adc<br>~~0~~<br>~~f~~orce<br>~~r~~eset|Force a reset of the ADC|
|adc<br>~~1~~<br>~~f~~orce<br>~~r~~eset|Force a reset of the ADC|
|adc<br>~~2~~<br>~~f~~orce<br>~~r~~eset|Force a reset of the ADC|
|adc<br>~~3~~<br>~~f~~orce<br>~~r~~eset|Force a reset of the ADC|
|adc<br>~~4~~<br>~~f~~orce<br>~~r~~eset|Force a reset of the ADC|
|adc<br>~~5~~<br>~~f~~orce<br>~~r~~eset|Force a reset of the ADC|
|gps<br>~~d~~isconnect|Disconnect the GPS|
|reset<br>~~f~~actory<br>~~d~~efaults|Reset all the settings to factory defaults|
|restart|Restart the main PSS program|



_**Table 28:** Miscellaneous / debugging commands (no parameters)_ 

## **7.2 Telemetry** 

The data type used for Telemetry items is Binary. The telemetry packets are continuously transmitted over port 54345 via UDP to the FDC. The contents of the packets themselves are outlined in Section 7.2.2, alongside the allocated bytes, types, and names. 

## **7.2.1 Telemetry Details** 

Below is a type list for the following sections describing telemetry. Min and max values are specified for some floating point types for informational purposes only. 

|**Type**|**Description**|
|---|---|
|s<br>u<br>c<br>i<br>d<br>f|16 bit signed integer<br>16 bit unsigned integer<br>8 bit character / unsigned integer<br>32 bit signed integer<br>64 bit foating point<br>32 bit foat|



_**Table 29:** Telemetry Data Types_ 

## **7.2.2 Telemetry Descriptions** 

In the table below the contents of the telemetry packet is outlined. Each entry has its own name, type, minimum and maximum value (if applicable), samples-per-frame (spf), size, description, and units. It is notable that the byte transmission uses little endian system. 

**Note:** All * ~~t~~ able items are only valid when connected to a calibration table and are empty otherwise. 

12 

© 2024 StarSpec Technologies Inc. All rights reserved. 

|**Name**|**Type**|**(min/max)**|**Spf**|**Start Byte**|**Bytes**|**Description**|**Units**|
|---|---|---|---|---|---|---|---|
|**v**<br>~~**x**~~**1**<br>~~**p**~~**ss**<br>~~**0**~~|d|(0.0, 50.0)|1|0|8|Voltage|V|
|**v**<br>~~**x**~~**2**<br>~~**p**~~**ss**<br>~~**0**~~|d|(0.0, 50.0)|1|8|8|Voltage|V|
|**v**<br>~~**y**~~**1**<br>~~**p**~~**ss**<br>~~**0**~~|d|(0.0, 50.0)|1|16|8|Voltage|V|
|**v**<br>~~**y**~~**2**<br>~~**p**~~**ss**<br>~~**0**~~|d|(0.0, 50.0)|1|24|8|Voltage|V|
|**v**<br>**sum**<br>**pss**<br>~~**0**~~|d|(0.0, 50.0)|1|32|8|Voltage|V|
|**thresh**<br>**pss**<br>~~**0**~~|d|(0.0, 10.0)|1|40|8|–|–|
|**radius**<br>~~**p**~~**ss**<br>**0**|d|(0.0, 20.0)|1|48|8|–|–|
|**good**<br>~~**p**~~**ss**<br>~~**0**~~|c|–|1|56|1|–|–|
|**x**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**0**~~|d|–|1|57|8|–|–|
|**y**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**0**~~|d|–|1|65|8|–|–|
|**x**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**0**~~|d|–|1|73|8|–|–|
|**y**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**0**~~|d|–|1|81|8|–|–|
|**az**<br>~~**p**~~**ss**<br>~~**0**~~|d|(0.0, 360.0)|1|89|8|Angle|deg|
|**el**<br>~~**p**~~**ss**<br>~~**0**~~|d|(0.0, 360.0)|1|97|8|Angle|deg|
|**valid**<br>~~**p**~~**ss**<br>~~**0**~~|c|–|1|105|1|–|–|
|**v**<br>~~**x**~~**1**<br>~~**p**~~**ss**<br>~~**1**~~|d|(0.0, 50.0)|1|106|8|Voltage|V|
|**v**<br>~~**x**~~**2**<br>~~**p**~~**ss**<br>~~**1**~~|d|(0.0, 50.0)|1|114|8|Voltage|V|
|**v**<br>~~**y**~~**1**<br>~~**p**~~**ss**<br>~~**1**~~|d|(0.0, 50.0)|1|122|8|Voltage|V|
|**v**<br>~~**y**~~**2**<br>~~**p**~~**ss**<br>~~**1**~~|d|(0.0, 50.0)|1|130|8|Voltage|V|
|**v**<br>**sum**<br>**pss**<br>~~**1**~~|d|(0.0, 50.0)|1|138|8|Voltage|V|
|**thresh**<br>**pss**<br>~~**1**~~|d|(0.0, 10.0)|1|146|8|–|–|
|**radius**<br>~~**p**~~**ss**<br>**1**|d|(0.0, 20.0)|1|154|8|–|–|
|**good**<br>~~**p**~~**ss**<br>~~**1**~~|c|–|1|162|1|–|–|
|**x**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**1**~~|d|–|1|163|8|–|–|
|**y**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**1**~~|d|–|1|171|8|–|–|
|**x**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**1**~~|d|–|1|179|8|–|–|
|**y**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**1**~~|d|–|1|187|8|–|–|
|**az**<br>~~**p**~~**ss**<br>~~**1**~~|d|(0.0, 360.0)|1|195|8|Angle|deg|
|**el**<br>~~**p**~~**ss**<br>~~**1**~~|d|(0.0, 360.0)|1|203|8|Angle|deg|
|**valid**<br>~~**p**~~**ss**<br>~~**1**~~|c|–|1|211|1|–|–|
|**v**<br>~~**x**~~**1**<br>~~**p**~~**ss**<br>~~**2**~~|d|(0.0, 50.0)|1|212|8|Voltage|V|
|**v**<br>~~**x**~~**2**<br>~~**p**~~**ss**<br>~~**2**~~|d|(0.0, 50.0)|1|220|8|Voltage|V|



13 © 2024 StarSpec Technologies Inc. All rights reserved. 

|**v**<br>~~**y**~~**1**<br>~~**p**~~**ss**<br>~~**2**~~|d|(0.0, 50.0)|1|228|8|Voltage|V|
|---|---|---|---|---|---|---|---|
|**v**<br>~~**y**~~**2**<br>~~**p**~~**ss**<br>~~**2**~~|d|(0.0, 50.0)|1|236|8|Voltage|V|
|**v**<br>**sum**<br>**pss**<br>~~**2**~~|d|(0.0, 50.0)|1|244|8|Voltage|V|
|**thresh**<br>**pss**<br>~~**2**~~|d|(0.0, 10.0)|1|252|8|–|–|
|**radius**<br>~~**p**~~**ss**<br>**2**|d|(0.0, 20.0)|1|260|8|–|–|
|**good**<br>~~**p**~~**ss**<br>~~**2**~~|c|–|1|268|1|–|–|
|**x**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**2**~~|d|–|1|269|8|–|–|
|**y**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**2**~~|d|–|1|277|8|–|–|
|**x**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**2**~~|d|–|1|285|8|–|–|
|**y**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**2**~~|d|–|1|293|8|–|–|
|**az**<br>~~**p**~~**ss**<br>~~**2**~~|d|(0.0, 360.0)|1|301|8|Angle|deg|
|**el**<br>~~**p**~~**ss**<br>~~**2**~~|d|(0.0, 360.0)|1|309|8|Angle|deg|
|**valid**<br>~~**p**~~**ss**<br>~~**2**~~|c|–|1|317|1|–|–|
|**v**<br>~~**x**~~**1**<br>~~**p**~~**ss**<br>~~**3**~~|d|(0.0, 50.0)|1|318|8|Voltage|V|
|**v**<br>~~**x**~~**2**<br>~~**p**~~**ss**<br>~~**3**~~|d|(0.0, 50.0)|1|326|8|Voltage|V|
|**v**<br>~~**y**~~**1**<br>~~**p**~~**ss**<br>~~**3**~~|d|(0.0, 50.0)|1|334|8|Voltage|V|
|**v**<br>~~**y**~~**2**<br>~~**p**~~**ss**<br>~~**3**~~|d|(0.0, 50.0)|1|342|8|Voltage|V|
|**v**<br>**sum**<br>**pss**<br>~~**3**~~|d|(0.0, 50.0)|1|350|8|Voltage|V|
|**thresh**<br>**pss**<br>~~**3**~~|d|(0.0, 10.0)|1|358|8|–|–|
|**radius**<br>~~**p**~~**ss**<br>**3**|d|(0.0, 20.0)|1|366|8|–|–|
|**good**<br>~~**p**~~**ss**<br>~~**3**~~|c|–|1|374|1|–|–|
|**x**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**3**~~|d|–|1|375|8|–|–|
|**y**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**3**~~|d|–|1|383|8|–|–|
|**x**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**3**~~|d|–|1|391|8|–|–|
|**y**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**3**~~|d|–|1|399|8|–|–|
|**az**<br>~~**p**~~**ss**<br>~~**3**~~|d|(0.0, 360.0)|1|407|8|Angle|deg|
|**el**<br>~~**p**~~**ss**<br>~~**3**~~|d|(0.0, 360.0)|1|415|8|Angle|deg|
|**valid**<br>~~**p**~~**ss**<br>~~**3**~~|c|–|1|423|1|–|–|
|**v**<br>~~**x**~~**1**<br>~~**p**~~**ss**<br>~~**4**~~|d|(0.0, 50.0)|1|424|8|Voltage|V|
|**v**<br>~~**x**~~**2**<br>~~**p**~~**ss**<br>~~**4**~~|d|(0.0, 50.0)|1|432|8|Voltage|V|
|**v**<br>~~**y**~~**1**<br>~~**p**~~**ss**<br>~~**4**~~|d|(0.0, 50.0)|1|440|8|Voltage|V|
|**v**<br>~~**y**~~**2**<br>~~**p**~~**ss**<br>~~**4**~~|d|(0.0, 50.0)|1|448|8|Voltage|V|



14 © 2024 StarSpec Technologies Inc. All rights reserved. 

|**v**<br>**sum**<br>**pss**<br>~~**4**~~|d|(0.0, 50.0)|1|456|8|Voltage|V|
|---|---|---|---|---|---|---|---|
|**thresh**<br>**pss**<br>~~**4**~~|d|(0.0, 10.0)|1|464|8|–|–|
|**radius**<br>~~**p**~~**ss**<br>**4**|d|(0.0, 20.0)|1|472|8|–|–|
|**good**<br>~~**p**~~**ss**<br>~~**4**~~|c|–|1|480|1|–|–|
|**x**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**4**~~|d|–|1|481|8|–|–|
|**y**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**4**~~|d|–|1|489|8|–|–|
|**x**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**4**~~|d|–|1|497|8|–|–|
|**y**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**4**~~|d|–|1|505|8|–|–|
|**az**<br>~~**p**~~**ss**<br>~~**4**~~|d|(0.0, 360.0)|1|513|8|Angle|deg|
|**el**<br>~~**p**~~**ss**<br>~~**4**~~|d|(0.0, 360.0)|1|521|8|Angle|deg|
|**valid**<br>~~**p**~~**ss**<br>~~**4**~~|c|–|1|529|1|–|–|
|**v**<br>~~**x**~~**1**<br>~~**p**~~**ss**<br>~~**5**~~|d|(0.0, 50.0)|1|530|8|Voltage|V|
|**v**<br>~~**x**~~**2**<br>~~**p**~~**ss**<br>~~**5**~~|d|(0.0, 50.0)|1|538|8|Voltage|V|
|**v**<br>~~**y**~~**1**<br>~~**p**~~**ss**<br>~~**5**~~|d|(0.0, 50.0)|1|546|8|Voltage|V|
|**v**<br>~~**y**~~**2**<br>~~**p**~~**ss**<br>~~**5**~~|d|(0.0, 50.0)|1|554|8|Voltage|V|
|**v**<br>**sum**<br>**pss**<br>~~**5**~~|d|(0.0, 50.0)|1|562|8|Voltage|V|
|**thresh**<br>**pss**<br>~~**5**~~|d|(0.0, 10.0)|1|570|8|–|–|
|**radius**<br>~~**p**~~**ss**<br>**5**|d|(0.0, 20.0)|1|578|8|–|–|
|**good**<br>~~**p**~~**ss**<br>~~**5**~~|c|–|1|586|1|–|–|
|**x**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**5**~~|d|–|1|587|8|–|–|
|**y**<br>~~**r**~~**aw**<br>~~**p**~~**ss**<br>~~**5**~~|d|–|1|595|8|–|–|
|**x**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**5**~~|d|–|1|603|8|–|–|
|**y**<br>~~**c**~~**orr**<br>~~**p**~~**ss**<br>~~**5**~~|d|–|1|611|8|–|–|
|**az**<br>~~**p**~~**ss**<br>~~**5**~~|d|(0.0, 360.0)|1|619|8|Angle|deg|
|**el**<br>~~**p**~~**ss**<br>~~**5**~~|d|(0.0, 360.0)|1|627|8|Angle|deg|
|**valid**<br>~~**p**~~**ss**<br>~~**5**~~|c|–|1|635|1|–|–|
|**boxcar**<br>~~**s**~~**ize**<br>~~**a**~~**dc**<br>~~**0**~~|u|(1.0, 1000.0)|1|636|2|–|–|
|**boxcar**<br>~~**s**~~**ize**<br>~~**a**~~**dc**<br>~~**1**~~|u|(1.0, 1000.0)|1|638|2|–|–|
|**boxcar**<br>~~**s**~~**ize**<br>~~**a**~~**dc**<br>~~**2**~~|u|(1.0, 1000.0)|1|640|2|–|–|
|**boxcar**<br>~~**s**~~**ize**<br>~~**a**~~**dc**<br>~~**3**~~|u|(1.0, 1000.0)|1|642|2|–|–|
|**boxcar**<br>~~**s**~~**ize**<br>~~**a**~~**dc**<br>~~**4**~~|u|(1.0, 1000.0)|1|644|2|–|–|
|**boxcar**<br>~~**s**~~**ize**<br>~~**a**~~**dc**<br>~~**5**~~|u|(1.0, 1000.0)|1|646|2|–|–|



15 © 2024 StarSpec Technologies Inc. All rights reserved. 

|**current**<br>~~**a**~~**z**|d|(-360.0, 360.0)|1|648|8|–|–|
|---|---|---|---|---|---|---|---|
|**offset**<br>~~**a**~~**z**|d|(-360.0, 360.0)|1|656|8|–|–|
|**best**<br>~~**a**~~**z**|d|(0.0, 360.0)|1|664|8|Angle|deg|
|**best**<br>~~**e**~~**l**|d|(0.0, 360.0)|1|672|8|Angle|deg|
|**timestamp**<br>**gps**|d|–|1|680|8|Time|s|
|**lat**<br>~~**g**~~**ps**|d|–|1|688|8|–|–|
|**lon**<br>~~**g**~~**ps**|d|–|1|694|8|–|–|
|**alt**<br>~~**g**~~**ps**|d|–|1|704|8|–|–|
|**baud**<br>~~**g**~~**ps**|i|(0.0, 115200.0)|1|712|4|–|–|
|**ra**<br>**sun**<br>**gps**|d|–|1|716|8|–|–|
|**dec**<br>**sun**<br>**gps**|d|–|1|724|8|–|–|
|**az**<br>~~**s**~~**un**<br>~~**g**~~**ps**|d|–|1|732|8|–|–|
|**el**<br>~~**s**~~**un**<br>~~**g**~~**ps**|d|–|1|740|8|–|–|
|**ha**<br>~~**s**~~**un**<br>~~**g**~~**ps**|d|–|1|748|8|–|–|
|**array**<br>~~**t**~~**ip**|d|–|1|756|8|–|–|
|**array**<br>~~**t**~~**ilt**|d|–|1|764|8|–|–|
|**pos**<br>~~**t**~~**able**|d|–|1|772|8|Angle|deg|
|**last**<br>~~**t**~~**ime**<br>~~**t**~~**able**|d|–|1|780|8|Time|s|
|**at**<br>~~**t**~~**arget**<br>**table**|c|–|1|788|1|–|–|
|**cmd**<br>~~**p**~~**osition**<br>~~**t**~~**able**|d|(-360.0, 360.0)|1|789|8|Angle|deg|
|**cmd**<br>~~**s**~~**peed**<br>~~**t**~~**able**|d|–|(0.0, 90.0)|797|8|Speed|deg/s|
|**set**<br>~~**p**~~**os**<br>~~**t**~~**able**|d|(-360.0, 360.0)|1|805|8|Angle|deg|
|**cycle**<br>~~**s**~~**tart**<br>~~**t**~~**able**|d|(-360.0, 360.0)|1|813|8|Angle|deg|
|**cycle**<br>~~**e**~~**nd**<br>~~**t**~~**able**|d|(-360.0, 360.0)|1|821|8|Angle|deg|
|**cycles**<br>**left**<br>~~**t**~~**able**|i|–|1|829|4|–|cycles|



_**Table 30:** Telemetry Items – total frame size of 833 Bytes_ 

## **8 Sample Programs & API** 

## **8.1 Connecting for the First Time** 

As mentioned in Section 7.2, Telemetry is transmitted continuously over port 54345 via UDP to the FDC. This port is configurable after the first connection, but must be used for initial setup purposes. 

16 

© 2024 StarSpec Technologies Inc. All rights reserved. 

Below, a sample of a simple connection program in **Rust** is outlined: Send address (default for commands): Address of the RPi: 10.0.0.2:54345 Receive address (default for telemetry): IP of the laptop: 10.0.0.1:53335 

1 `//When calling the function:` 2 **`let`** `port = 53335;` 3 **`let`** `socket = commands::connect(port.to_string()).unwrap();` 4 5 `//Command to establish the connection` 6 **`pub fn`** `connect(port: String) -> Result<UdpSocket, Box<` **`dyn`** `Error>> {` 7 `//creating socket` 8 **`let`** `socket = UdpSocket::bind(format!("0.0.0.0:{}", port))` 9 `.expect("Couldn’t␣bind␣to␣address");` 10 11 `//return the socket` 12 `Ok(socket)` 13 `}` 

Another sample in **C** is below: 

1 i n t connect socket ( ) _{_ 2 i n t sockfd ; 3 s t r u c t sockaddr in server addr ; 4 5 / / Creating socket 6 sockfd = socket ( AF INET , SOC ~~K D~~ GRAM, 0) ; 7 i f ( sockfd _<_ 0) _{_ 8 perror ( ” Couldn ’ t create socket ” ) ; 9 e x i t ( EXIT FAILURE ) ; 10 _}_ 11 12 / / Binding the socket to an address 13 memset(& server addr , 0 , sizeof ( server addr ) ) ; 14 server addr . s i n f a m i l y = AF INET ; 15 server addr . sin addr . s addr = INADDR ~~A~~ NY; 16 server addr . s i n p o r t = htons (LOCAL ~~P~~ ORT) ; 17 18 i f ( bind ( sockfd , ( const s t r u c t sockaddr *[)&server] addr , sizeof ( server addr ) ) _<_ 0) _{_ 19 perror ( ” Couldn ’ t bind to address ” ) ; 20 e x i t ( EXIT FAILURE ) ; 21 _}_ 22 23 return sockfd ; 24 _}_ 

## **8.2 Parsing the Byte Stream** 

The byte stream is transmitted via the little endian system. This means it stores the least significant byte at the smallest address. Most data items are type f64 and 8 bytes, so this is important to consider for parsing the telemetry packets correctly. 

A sample in **Rust** is outlined below: 

```
//InMain--------------------------------------------------------------------------
```

1 2 **`fn`** `main() {` 3 `//send address` 4 **`let`** `addr_send = "10.0.0.2";` 5 6 `//recieve address` 7 **`let`** `addr_rec = "0.0.0.0:54345";` 8 

17 

© 2024 StarSpec Technologies Inc. All rights reserved. 

9 `//connect` 10 **`let`** `port = "53335";` 11 12 `println!("Connecting␣to␣the␣device");` 13 **`let`** `socket = commands::connect(port.to_string()).unwrap();` 14 15 `println!("afer␣connect");` 16 `//get a buffer to recieve the datagram --> 772 bytes via the manual` 17 **`let mut`** `buf = [0; 772];` 18 19 `//reading continuously and exporting to .csv` 20 **`loop`** `{` 21 `//recieve the data` 22 **`match`** `socket.recv_from(&` **`mut`** `buf) {` 23 `//match the result` 24 `Ok((recieved,_)) => {` 25 `//check if the data is the correct size` 26 **`if`** `(recieved != 772){` 27 `//error handling` 28 `eprintln!("Insufficient␣data␣recieved");` 29 `}` **`else`** `{` 30 `println!("Data␣recieved");` 31 `//read the data` 32 `commands::read(&` **`mut`** `buf);` 33 `}` 34 `}` 35 `//error handling` 36 `Err(e) => eprintln!("Error:␣{:?}", e),` 37 `}` 38 39 `}` 40 `}` 41 42 `//Interpreting the byte stream-------------------------------------------------------` 43 **`pub fn`** `read(arr: &` **`mut`** `[u8]){` 44 `//process the array into the telemetry values based on the size array` 45 **`let mut`** `vec: Vec<f64> = Vec::new();` 46 **`let mut`** `arr_vec = arr.to_vec();` 47 **`let mut`** `used = Vec::new();` 48 `//for loop for each pss` 49 **`for`** `x` **`in`** `0..6 {` 50 `//for loop for each telemetry value` 51 `// println!("x {}",x);` 52 **`for`** `i` **`in`** `0..13{` 53 `//get sizes value` 54 **`let`** `size = SIZES[i];` 55 56 `//process that amount of bytes, reconstruct back into an integer` 57 **`let mut`** `val: f64 = 0.0;` 58 59 **`if`** `(size == 8){` 60 `//get the 8 bytes` 61 `val = f64::from_le_bytes([arr_vec[0], arr_vec[1], arr_vec[2],` 62 `arr_vec[3], arr_vec[4], arr_vec[5], arr_vec[6], arr_vec[7]]);` 

18 

© 2024 StarSpec Technologies Inc. All rights reserved. 

63 64 `//remove the used bytes` 65 **`let`** `temp = arr_vec.split_off(8);` 66 67 `used.push(arr_vec);` 68 69 `arr_vec = temp;` 70 

71 `}` **`else if`** `size == 1{` 72 `//get the 1 byte` 

73 `val = arr_vec[0]` **`as`** `f64;` 

74 

75 `//remove the used bytes` 76 **`let`** `temp = arr_vec.split_off(1);` 77 78 `used.push(arr_vec);` 79 80 `arr_vec = temp;` 

81 82 `}` 

83 84 `//append to the vector` 85 `vec.push(val);` 

86 87 `}` 88 `}` 

89 

90 `//now process the remaining data, independant of each PSS` 91 `//boxcars --> 2 bytes each` 

92 **`for`** `i` **`in`** `0..6{` 

93 `//process that amount of bytes, reconstruct back into an integer` 94 **`let`** `val;` 

95 

- 96 `//process and reconstruct` 

97 `val = u16::from_le_bytes([arr_vec[0], arr_vec[1]])` **`as`** `f64;` 

98 

99 `//push used values` 100 **`let`** `temp = arr_vec.split_off(2);` 101 102 `used.push(arr_vec);` 103 104 `arr_vec = temp;` 

105 106 `//append to the vector` 107 `vec.push(val);` 108 `}` 

109 

- 110 `//print size of arr vec` 

- 111 `// println!("size of arr_vec {}", arr_vec.len());` 

112 

113 `//remaining values are 8 bytes except baud gps` 114 **`for`** `i` **`in`** `0..16{` 115 `//if i = 7, baud gps is 4 bytes to proccess` 116 **`let`** `val;` 

19 

© 2024 StarSpec Technologies Inc. All rights reserved. 

117 118 **`if`** `i == 8{` 119 `//process 4 bytes` 120 `val = f32::from_le_bytes([arr_vec[0], arr_vec[1],` 121 `arr_vec[2], arr_vec[3]])` **`as`** `f64;` 122 123 `//push used values` 124 **`let`** `temp = arr_vec.split_off(4);` 125 126 `used.push(arr_vec);` 

127 128 `arr_vec = temp;` 129 130 `//append to the vector` 131 `vec.push(val);` 132 `}` **`else`** `{` 133 `//process 8 bytes` 134 `val = f64::from_le_bytes([arr_vec[0], arr_vec[1], arr_vec[2],` 135 `arr_vec[3], arr_vec[4], arr_vec[5], arr_vec[6], arr_vec[7]]);` 136 137 `//push used values` 138 **`let`** `temp = arr_vec.split_off(8);` 139 `used.push(arr_vec);` 140 141 `arr_vec = temp;` 

142 143 `//append to the vector` 144 `vec.push(val);` 145 `}` 146 `}` 

147 

148 `//write each line to csv` 149 `append_csv(vec, "telemetry.csv");` 

150 151 `}` 

## Another sample in **C** is below: 

1 / / Constant size array f o r each set of PSS telemetry 2 i n t SIZES [13] = _{_ 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 1 _}_ ; 3 4 / / Function to read and i n t e r p r e t the byte stream 5 void read telemetry ( unsigned char * arr , i n t a r r l e n ) _{_ 6 double vec [35] = _{_ 0 _}_ ; / / Adjust size according to t o t a l expected telemetry values 7 i n t o f f s e t = 0; 8 i n t idx = 0; 9 10 / / Process PSS telemetry 11 f o r ( i n t x = 0; x _<_ 6; ++x ) _{_ 12 f o r ( i n t i = 0; i _<_ 13; ++ i ) _{_ 13 i n t size = SIZES [ i ] ; 14 double val = 0.0; 15 16 i f ( size == 8) _{_ 17 memcpy(& val , arr + offset , sizeof ( double ) ) ; 18 o f f s e t += 8; 19 _}_ else i f ( size == 1) _{_ 20 val = arr [ o f f s e t ] ; 21 o f f s e t += 1; 22 _}_ 

20 

© 2024 StarSpec Technologies Inc. All rights reserved. 

23 24 vec [ idx ++] = val ; 25 _}_ 26 _}_ 27 28 / / Process boxcar telemetry 29 f o r ( i n t i = 0; i _<_ 6; ++ i ) _{_ 30 u i n t 1 6 t val ; 31 memcpy(& val , arr + offset , sizeof ( u i n t 1 6 t ) ) ; 32 vec [ idx ++] = val ; 33 o f f s e t += 2; 34 _}_ 35 36 / / Process remaining data 37 f o r ( i n t i = 0; i _<_ 16; ++ i ) _{_ 38 double val = 0.0; 39 40 i f ( i == 8) _{_ / / GPS baud rate 41 f l o a t v a l f l o a t ; 42 memcpy(& v a l f l o a t , arr + offset , sizeof ( f l o a t ) ) ; 43 val = v a l f l o a t ; 44 o f f s e t += 4; 45 _}_ else _{_ 46 memcpy(& val , arr + offset , sizeof ( double ) ) ; 47 o f f s e t += 8; 48 _}_ 49 50 vec [ idx ++] = val ; 51 _}_ 52 53 / / Append to CSV 54 append csv ( vec , idx , ” telemetry . csv ” ) ; 55 _}_ 

## **8.3 Sending Commands** 

Sending commands is relatively simple, as they are ASCII based. If there are input parameters, they are to be space-separated, as follows: 

## **adc** ~~**0 f**~~ **ilter 20** 

String or character parameters are also space-separated, but must be quoted, as follows: 

## **gps connect 9600** 

Sample functions that send these commands are outlined below in **Rust** : 

1 `//set offset az` 2 **`pub fn`** `set_offset_az(az:f32, socket: &UdpSocket, addr: &str, port: &str){` 3 **`let`** `message = format!("set_offset_az␣{}", az);` 4 **`let`** `m = message.as_bytes();` 5 6 `socket.send_to(&m,format!("{}:{}",addr,port)).expect("Couldn’t␣send␣data");` 7 `}` 8 9 `//connect gps` 10 **`pub fn`** `connect_gps(baud: i32, dev: &str, socket: &UdpSocket, addr: &str, port: &str){` 11 **`let`** `message = format!("gps_connect␣{}␣’{}’", baud, dev);` 12 **`let`** `m = message.as_bytes();` 13 14 `socket.send_to(&m,format!("{}:{}",addr,port)).expect("Couldn’t␣send␣data");` 

21 

© 2024 StarSpec Technologies Inc. All rights reserved. 

15 `}` 16 17 `//disconnect gps` 18 **`pub fn`** `disconnect_gps(socket: &UdpSocket, addr: &str, port: &str){` 19 **`let`** `message = format!("gps_disconnect");` 20 **`let`** `m = message.as_bytes();` 21 22 `socket.send_to(&m,format!("{}:{}",addr,port)).expect("Couldn’t␣send␣data");` 23 `}` 24 25 `//force reset of adc X` 26 **`pub fn`** `force_reset_adc(x:i16, socket: &UdpSocket, addr: &str, port: &str){` 27 **`let`** `message = format!("adc_{}_force_reset", x);` 28 **`let`** `m = message.as_bytes();` 29 30 `socket.send_to(&m,format!("{}:{}",addr,port)).expect("Couldn’t␣send␣data");` 31 `}` 

## Another sample in **C** is below: 

1 #code here 

2 / / Function to connect GPS 3 void connect gps ( i n t baud , const char *dev , i n t sockfd ) _{_ 4 char message [ 2 5 6 ] ; 5 s t r u c t sockaddr in server addr ; 6 7 s p r i n t f (message , ” gps connect %d ’%s ’ ” , baud , dev ) ; 8 9 memset(& server addr , 0 , sizeof ( server addr ) ) ; 10 server addr . s i n f a m i l y = AF INET ; 11 server addr . s i n p o r t = htons (PORT) ; 12 server addr . sin addr . s addr = inet addr ( ” 10.0.0.2 ” ) ; 13 14 sendto ( sockfd , message , s t r l e n ( message ) , MSG ~~C~~ ONFIRM, ( const s t r u c t sockaddr *[)&server] addr , sizeof ( server addr ) ) ; 15 _}_ 16 17 / / Function to disconnect GPS 18 void disconnect gps ( i n t sockfd ) _{_ 19 char message[256] = ” gps disconnect ” ; 20 s t r u c t sockaddr in server addr ; 21 22 memset(& server addr , 0 , sizeof ( server addr ) ) ; 23 server addr . s i n f a m i l y = AF INET ; 24 server addr . s i n p o r t = htons (PORT) ; 25 server addr . sin addr . s addr = inet addr ( ” 10.0.0.2 ” ) ; 26 27 sendto ( sockfd , message , s t r l e n ( message ) , MSG ~~C~~ ONFIRM, ( const s t r u c t sockaddr *[)&server] addr , sizeof ( server addr ) ) ; 28 _}_ 29 

30 / / Function to force reset of ADC 31 void force reset adc ( i n t x , i n t sockfd ) _{_ 32 char message [ 2 5 6 ] ; 33 s t r u c t sockaddr in server addr ; 34 35 s p r i n t f (message , ” adc ~~%~~ d force reset ” , x ) ; 36 37 memset(& server addr , 0 , sizeof ( server addr ) ) ; 38 server addr . s i n f a m i l y = AF INET ; 39 server addr . s i n p o r t = htons (PORT) ; 40 server addr . sin addr . s addr = inet addr ( ” 10.0.0.2 ” ) ; 41 42 MSG ~~C~~ 

sendto ( sockfd , message , s t r l e n ( message ) , MSG ~~C~~ ONFIRM, ( const s t r u c t sockaddr *[)&server] addr , sizeof ( server addr ) ) ; 

22 

© 2024 StarSpec Technologies Inc. All rights reserved. 

43 _}_ 

## **9 Calibration** 

## **9.1 Stage 1 Calibration - Individual PSS Linearization** 

In the first stage of calibration, the accuracy of each individual PSD sensor was evaluated at the sub micron level. To achieve this, a laser is pointed at the PSD to imitate a point source of light which can be expected from a pinhole. Then, the entire sensor surface area was mapped, and was then linearized based on position and generated heat maps (Figure 9). Thus, from this scanning, each sensor surface was able to be calibrated using the custom FSW to adjust for any inherent discontinuities or nonuniformities present. This allows for each PSS’ sensing surface response to be symmetrical and consistent to any sun position. 

_**Figure 9:** PSS 41 Heat Map_ 

## **9.2 Stage 2 Calibration - Az/El Correlation** 

In the second stage of calibration, the position sensor assembly is evaluated, specifically with respect to each other. This is an on-sky calibration and requires a cloud free sky to conduct the process. The sensors are now fully integrated into the housing and are rotated as the sun is within the elevation range, allowing the mapping of relative position to each other with a known sun position. As before, each sensor can be calibrated for discontinuities or nonuniformities, ensuring a sound overall scanning surface. 

## **Through stage 1 and 2 calibration the PSS achieves a 5 arcminute resolution and accuracy.** 

23 

© 2024 StarSpec Technologies Inc. All rights reserved. 

