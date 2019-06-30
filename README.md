![VIVOE-LITE](images/Vivoe-lite-banner.png)
![Travis](https://travis-ci.com/ross-newman/vivoe-lite.svg?token=3WE3zHMAGTzwqxs2yiqd&branch=master)
[![License](https://img.shields.io/badge/licence-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/2927/badge)](https://bestpractices.coreinfrastructure.org/projects/2927)
[![codecov](https://codecov.io/gh/ross-newman/vivoe-lite/branch/master/graph/badge.svg)](https://codecov.io/gh/ross-newman/vivoe-lite)
![Version](https://img.shields.io/badge/version-0.1.266-red.svg)
# Dependancies
This VIVOE (Vetronics Infrastructure for Video Over Ethernet) environment is currently tested on Ubuntu 18.04 LTS. Please ensure you have the following packages installed prior to building the application:
```
sudo apt install libcairo2-dev libxt-dev libsdl2-dev doxygen libxml2-dev ncurses-dev libxext-dev libswscale-dev libprotobuf-
```
# HMI
The project includes an refferance implementation of the GVA Human Machin Interface (HMI). This is meant as a tool for testing different video cameras and streaming protocols and does not implement a lot of the functionality defined in the GVA Land Data Model (LDM). Its primerially used to demonstrate various video streaming pipelines and control mechanisms for real time video processing and experiment with HMI options.

![GVA HMI](images/GVA-HMI-Cairo.png)

> NOTE: Not all labels are currently implemented, project in heavy development! See [DEVELOPER.md](docs/DEVELOPER.md) for issues and features.

Video can be streamed to an optional video processing unit (GPU/TPU for AI/ML and hemeshperical video processing) before being recieved by the HMI processor for video overlays and personalisation for gunner/commaner and driver displays. Multicast vdeo streams should be recieved by all consumers in realtime (networking not shown). There may be one or more users and displays on any given manned vehicle.

![GVA Dataflow](images/GVA-DataFlow.PNG)

Touch screen inputs and bezel key inputs are sent back to the HMI to update the overlays in the RTP stream. The display can be 'dumb' with HMI / Video processing being done on a seperate LRU. RTP streams being recieved by the display have the overlays already rendered in the video stream.

### HMI Controls

To build the HMI clone the code and run cmake. Automated builds are handled by travis-ci.

The following keys can be used to interact with the display:
* \+ Rotate PPI clockwise
* \- Rotate PPI anti-clockwise
* \> Rotate Sight anti-clockwise
* < Rotate Sight anti-clockwise
* [1-8] Function SA,WPN...
* ESC Quit
* A Alarms
* K Keyboard
  * CAPS-LOCK toggle upper case
  * NUM-LOCK toggle special chars

## DDS
Support for FastRTPS is being tested currently and provides RTPS communication as prescribed by the GVA standards. Messages are derived from IDL that is _not_ part of the LDM. There are two DDS protocols on Github that look like good candidates opensource projects implementing GVA.
* https://github.com/eProsima/Fast-RTPS
* https://github.com/ADLINK-IST/opensplice

I will be testing FastRTPS as this is the default choice for [ROS2](https://index.ros.org/doc/ros2/).

## GPS source
Application supports locally connected NMEA (USB virtual serial) GPS source. The only tested device is currently the [GlobalSat BU-353-S4 USB](https://www.amazon.co.uk/GlobalSat-BU-353-S4-Receiver-SiRF-Black/dp/B008200LHW/ref=sr_1_1?keywords=GlobalSat+BU-353-S4+USB&qid=1560375523&s=electronics&sr=1-1) available from Amazon and Robotshop. This outputs [NMEA](https://en.wikipedia.org/wiki/NMEA_0183) formatted strings as shown below. These are read, converted and displayed on the display in the status bar if present. This is done by the same thread that updates the clock on the HMI. If no device is present then a dummy location is used which will place you in London at a famous landmark.
```
newmanr@dell-lnx:~/git/vivoe-lite$ cat /dev/ttyUSB0 | hexdump -C
00000000  24 47 50 47 47 41 2c 32  32 31 34 32 38 2e 30 30  |$GPGGA,221428.00|
00000010  30 2c 35 32 31 32 2e 38  35 37 36 2c 4e 2c 30 30  |0,5212.8576,N,00|
00000020  30 35 33 2e 33 39 30 37  2c 57 2c 31 2c 30 36 2c  |053.3907,W,1,06,|
00000030  31 2e 34 2c 31 31 37 2e  33 2c 4d 2c 34 37 2e 33  |1.4,117.3,M,47.3|
00000040  2c 4d 2c 2c 30 30 30 30  2a 34 35 0a 0a 24 47 50  |,M,,0000*45..$GP|
00000050  47 53 41 2c 41 2c 33 2c  30 36 2c 32 33 2c 30 32  |GSA,A,3,06,23,02|
00000060  2c 30 33 2c 31 39 2c 31  37 2c 2c 2c 2c 2c 2c 2c  |,03,19,17,,,,,,,|
00000070  32 2e 34 2c 31 2e 34 2c  32 2e 30 2a 33 42 0a 0a  |2.4,1.4,2.0*3B..|
00000080  24 47 50 52 4d 43 2c 32  32 31 34 32 38 2e 30 30  |$GPRMC,221428.00|
00000090  30 2c 41 2c 35 32 31 32  2e 38 35 37 36 2c 4e 2c  |0,A,5212.8576,N,|
000000a0  30 30 30 35 33 2e 33 39  30 37 2c 57 2c 30 2e 35  |00053.3907,W,0.5|
000000b0  31 2c 39 34 2e 33 36 2c  31 32 30 36 31 39 2c 2c  |1,94.36,120619,,|
000000c0  2c 41 2a 34 31 0a 0a 24  47 50 47 47 41 2c 32 32  |,A*41..$GPGGA,22|
000000d0  31 34 32 39 2e 30 30 30  2c 35 32 31 32 2e 38 35  |1429.000,5212.85|
000000e0  37 37 2c 4e 2c 30 30 30  35 33 2e 33 39 31 35 2c  |77,N,00053.3915,|
000000f0  57 2c 31 2c 30 36 2c 31  2e 34 2c 31 31 37 2e 35  |W,1,06,1.4,117.5|
00000100  2c 4d 2c 34 37 2e 33 2c  4d 2c 2c 30 30 30 30 2a  |,M,47.3,M,,0000*|
00000110  34 30 0a 0a 24 47 50 47  53 41 2c 41 2c 33 2c 30  |40..$GPGSA,A,3,0|
00000120  36 2c 32 33 2c 30 32 2c  30 33 2c 31 39 2c 31 37  |6,23,02,03,19,17|
00000130  2c 2c 2c 2c 2c 2c 2c 32  2e 34 2c 31 2e 34 2c 32  |,,,,,,,2.4,1.4,2|
00000140  2e 30 2a 33 42 0a 0a 24  47 50 52 4d 43 2c 32 32  |.0*3B..$GPRMC,22|
```
Internally [libnema](https://github.com/ross-newman/nmealib) is used aquire [NMEA](https://en.wikipedia.org/wiki/NMEA_0183) messages from the GPS source. Once aquired conversion from decimal long/lat to degrees minutes seconds is required for the internal representation. Conversions to many other formats are possible using [libGeographic](https://geographiclib.sourceforge.io), currently the only conversion implemented is [MGRS](https://en.wikipedia.org/wiki/Military_Grid_Reference_System).

# Offline Maps
If a valid GPS source is present then an offline map will be available rendered by [libosmscout](https://wiki.openstreetmap.org/wiki/Libosmscout). This feature is currently being developed. OpenStreetMap database is required plus some additional processing prior to use. An regularly updated collection of global maps can be downloaded from [Geofabrik](https://download.geofabrik.de/). Entire world comes in at 77Gb before processing.

You can render maps using servers provided by [Google Colaboratory](https://colab.research.google.com/notebooks/welcome.ipynb) using my [juypter notebook](https://gist.github.com/ross-newman/8634f69e98ac2aded46552e7b0768dbb) for processing the data and depositing the results on to a Google Drive account. 

Tutorial [documentation for libosmscout](http://libosmscout.sourceforge.net/tutorials/importing/) contains a full description on how to prepare the maps database.
# Screensho
See [screenshots](images/README.md) in the images directory. 

# Development
See developer guidelines in [DEVELOPER.md](docs/DEVELOPER.md) which also contains the list of currently known issues.

# Config
See configuration setup in [CONFIG.md](docs/CONFIG.md)

# AI and ML Pipelines
See configuration setup in [PIPELINE.md](docs/PIPELINE.md)

## DEF STAN 00-83 - Vetronics Infrastructure for Video Over Ethernet (VIVOE)
For the video streaming element of the sample HMI the RTP raw video streams conform to Defence Standard 00-83 Vetronics Infrastructure
for Video Over Ethernet Part 1: Standards and Protocols, Issue 2. Specifically Appendix B2 YCbCr 4:2:2 Encoded Uncompressed Video.

Defence Standard 00-083 is currently split into the parts below.

*  Vetronics Infrastructure for Video Over Ethernet Part: 0 : Guidance 
*  **Vetronics Infrastructure for Video Over Ethernet Part: 1 : Standards and Protocols**
*  Vetronics Infrastructure for Video Over Ethernet Part: 2 : Extensions for Audio and Acoustic Data 

This standard is also mandated in the NATO version of GVA (NGVA). 

## STANAG 4754 - NATO Generic Vehicle Architecture (NGVA)
NGVA is a NATO Standardisation Agreement (STANAG 4754) based on open standards to design and integrate multiple electronic sub-systems onto military vehicles which are controllable from a multifunction crew display and control unit. 

## STANAG 4697 - Platform Extended Video Standard (PLEVID)
AIM The aim of this NATO standardization agreement (STANAG) is to respond to the following interoperability requirements. Adopts DEF STAN 00-083 and allows for GigE.

# Rendering
The HMI uses Cairo for rendering the GUI components.

![GVA HMI](images/GVA_HMI.png)

**GVA HMI Example layout**

# Links
* https://www.vetronics.org/
* https://en.wikipedia.org/wiki/Generic_Vehicle_Architecture
* https://www.cairographics.org/
* https://wiki.openstreetmap.org/wiki/Libosmscout
* https://download.geofabrik.de/
* https://geographiclib.sourceforge.io/
* https://index.ros.org/doc/ros2/
