# License Plate Detector in Windows for Parkings
## Introduction
This repository was forked from the original openalpr repository and, using the repository from [omergoktas](https://github.com/omergoktas/openalpr-mingw), compiled in Windows making use of CMake, OpenCV 2.4.10 and MinGW 5.1.0. Besides this repository contains tesseract and leptonica dependencies in *deps* folder.

## Project description
OpenALPR is an open source Automatic License Plate Recognition library written in C++ with bindings in C#, Java, Node.js, Go, and Python. The library analyzes images and video streams to identify license plates. The output is the text representation of any license plate characters.

This program contains a modified version of [OpenALPR](https://github.com/openalpr/openalpr), including the socket functionality to adapt it to car parkings. The main program is a server that open a socket in a port specified by argument (or 1234 by default) and start listening for a client. When a client is connected and it sends the key message ('Z'), the main program takes a photo, analyze it and returns the license plate if found to the socket.

## Compiling
You can try the program using the executable in the *test-it-here* folder. However, for them who want to compile it themselves, you can follow the videotutorial that kindly made omergoktas.
> **Video Tutorial:** https://www.youtube.com/watch?v=YYvxUef3l3E

**Note: It is IMPORTANT to use the versions specified below. Any version different may cause problems.**
1- Download and install latest CMake
    [http://www.cmake.org/files/v3.3/cmake-3.3.0-win32-x86.exe](http://www.cmake.org/files/v3.3/cmake-3.3.0-win32-x86.exe)

2- Download and extract OpenCv. (Tested on OpenCv 2.4.10)
    [http://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.10/opencv-2.4.10.exe/download](http://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.10/opencv-2.4.10.exe/download)

3- Get latest MinGW and install. (I tested on MinGW 5.1.0 (gcc 5.1.0))
    [http://sourceforge.net/projects/mingw-w64/files/latest/download](http://sourceforge.net/projects/mingw-w64/files/latest/download)

4- Add *mingw bin folder* to Path Variable on the System Environment Variables. (Detailed in the *videotutorial*)

5- Configure OpenCV/sources folder with CMake without any changes (use MinGW Makefiles), thereafter generate it in another folder called sources-build, for example.

6- Go to your OpenCv CMake generated folder and open command prompt here, thereafter type mingw32-make and hit enter. Then wait until compilation is complete.

7- Clone this repository and configure ./src folder with CMake (use MinGW Makefiles), it will be asked for OpenCv folder, thereafter enter your OpenCv CMake generated folder, finally generate it.

8- Go to this repo's CMake generated foder and open command prompt here, thereafter type mingw32-make and hit enter. Then wait until compilation is complete. No longer you have finished OpenALPR with MinGW. (was builded alpr.exe)

## Usage
As I said in the description of the project, this program uses a socket to receive signals, take a picture with a usb or ip camera and return the license plate that is more accurate. By default the values are:
- With USB camera. (If your computer has one it would be that one)
- Listening to port 1234 at localhost.
- Using the config file in config/openalpr.conf
- Using Europe as country and the pattern of Spain.

However, if you want to change those default values, here is a more detailed explanation:

### Detailed command line usage

```
user@windows:~/openalpr$ alpr.exe --help

USAGE:

   alpr [--camera <camera>] [-a <address>] [-p <port>] [-c                                                                      <country_code>] [--config <config_file>] [--debug] [-j] [--]                                                            [--version] [-h]


Where:

   --camera <camera>                                                                                                         
   Default video camera by usb = 0 (If you have a native camera and you want an usb camera, this value must be 1)  

   -a <address>,  --address <address>                                                                                        
   Address to the ip camera

   -p <port>,  --port <port>
   Port to open server.  Default = 1234

   --config <config_file>                                                                                                    
   Path to the openalpr.conf file

   -j,  --json                                                                                                               
   Output recognition results in JSON format.  Default=off

   --,  --ignore_rest                                                                                                        
   Ignores the rest of the labeled arguments following this flag.

   --version                                                                                                                 
   Displays version information and exits.

   -h,  --help                                                                                                               
   Displays usage information and exits.

   OpenAlpr Command Line Utility
```

### Example of use
To use it I recommend to test it with the netcat version for windows, it is very easy to send messages to a socket using this utility. More information: [NetCat for Windows](https://joncraton.org/blog/46/netcat-for-windows/)

*Note: Something that could help you in order to debug is that a picture is taken every time the program receives the signal.*

First I start opening the alpr.exe in the test-it-here folder and it will appear:
```
PORT 1234 added!
```
If there wasn't any errors and the port was free. After that I open the netcat for windows using:
```
nc.exe localhost 1234
```
Our alpr.exe program will detect that a client is connected, now, let give it a run!
```
PORT 1234 added!
Client connected

Message received: Z
TAKING PICTURE...
Total Time to process image: 93.645ms.
Message sent: NO_LEGIBLE

Message received: Z
TAKING PICTURE...
Total Time to process image: 142.236ms.

plate0: 10 results
- H5O26BBD   confidence: 92.1501     pattern_match: 0
- H5026BBD   confidence: 90.1177     pattern_match: 1
- H5Q26BBD   confidence: 87.6579     pattern_match: 0
- H5D26BBD   confidence: 87.6517     pattern_match: 0
- H5G26BBD   confidence: 85.4804     pattern_match: 0
- HSO26BBD   confidence: 84.3767     pattern_match: 0
- H5O26BB0   confidence: 84.2214     pattern_match: 0
- H5O2SBBD   confidence: 83.7692     pattern_match: 0
- H5O26B8D   confidence: 83.763      pattern_match: 0
- H5O2GBBD   confidence: 83.5287     pattern_match: 0

Message sent: H5026BBD
```
What we receive is:
```
NO_LEGIBLE                                                                                 
H5026BBD
```

# Contributions
Improvements to the OpenALPR library are always welcome.  Please review the [OpenALPR design description](https://github.com/openalpr/openalpr/wiki/OpenALPR-Design) and get started.

# License
[Affero GPLv3](http://www.gnu.org/licenses/agpl-3.0.html)
