OpenALPR MinGW  Version
========
This repository was forked from original openalpr repository for make sure compiling it on Windows. It's containing tesseract and leptonica dependencies in its own. 

## Result ##
![Windows 10](http://s15.postimg.org/7hwkwfp2x/result.png)

## Usage ##
> **Video Tutorial:** https://www.youtube.com/watch?v=YYvxUef3l3E

1- Download and install latest CMake

    http://www.cmake.org/files/v3.3/cmake-3.3.0-win32-x86.exe

2- Download and extract OpenCv. (I tested on OpenCv 2.4.10)

    http://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.10/opencv-2.4.10.exe/download
    
3- Get latest MinGW and install. (I tested on MinGW 5.1.0 (gcc 5.1.0))

    http://sourceforge.net/projects/mingw-w64/files/latest/download
    
4- Add mingw bin folder to Path Variable on the System Environment Variables.

5- Configure OpenCV/sources folder with CMake without any changes (use MinGW Makefiles), thereafter generate it.

6- Install 7zip, just in case. (Not important, you can ignore this step)

    http://www.7-zip.org/download.html
    
7- Go to your OpenCv CMake generated folder and open command prompt here, thereafter type mingw32-make and hit enter. Then wait until compilation is complete.

8- Clone this repository and configure ./src folder with CMake (use MinGW Makefiles), it will be asked for OpenCv folder, thereafter enter your OpenCv CMake generated folder, finally generate it.

9- Go to this repo's CMake generated foder and open command prompt here, thereafter type mingw32-make and hit enter. Then wait until compilation is complete. No longer you have finished OpenALPR with MinGW. (was builded alpr.exe)

10- Just copy alpr.exe to test_it_here folder and run above command:
alpr.exe --config alpr.conf test-image.jpg

openalpr
========

OpenALPR is an open source *Automatic License Plate Recognition* library written in C++ with bindings in C#, Java, and Python.  The library analyzes images and video streams to identify license plates.  The output is the text representation of any license plate characters.

Check out a live online demo here: http://www.openalpr.com/demo-image.html

User Guide
-----------


OpenALPR includes a command line utility.  Simply typing "alpr [image file path]" is enough to get started recognizing license plate images.

For example, the following output is created by analyzing this image:
![Plate Image](http://www.openalpr.com/images/demoscreenshots/plate3.png "Input image")



```
user@linux:~/openalpr$ alpr ./samplecar.png

plate0: top 10 results -- Processing Time = 58.1879ms.
    - PE3R2X     confidence: 88.9371
    - PE32X      confidence: 78.1385
    - PE3R2      confidence: 77.5444
    - PE3R2Y     confidence: 76.1448
    - P63R2X     confidence: 72.9016
    - FE3R2X     confidence: 72.1147
    - PE32       confidence: 66.7458
    - PE32Y      confidence: 65.3462
    - P632X      confidence: 62.1031
    - P63R2      confidence: 61.5089

```

Detailed command line usage:

```
user@linux:~/openalpr$ alpr --help

USAGE: 

   alpr  [-c <country_code>] [--config <config_file>] [-n <topN>] [--seek
         <integer_ms>] [-p <pattern code>] [--clock] [-d] [-j] [--]
         [--version] [-h] <image_file_path>


Where: 

   -c <country_code>,  --country <country_code>
     Country code to identify (either us for USA or eu for Europe). 
     Default=us

   --config <config_file>
     Path to the openalpr.conf file

   -n <topN>,  --topn <topN>
     Max number of possible plate numbers to return.  Default=10

   --seek <integer_ms>
     Seek to the specied millisecond in a video file. Default=0

   -p <pattern code>,  --pattern <pattern code>
     Attempt to match the plate number against a plate pattern (e.g., md
     for Maryland, ca for California)

   --clock
     Measure/print the total time to process image and all plates. 
     Default=off

   -d,  --detect_region
     Attempt to detect the region of the plate image.  [Experimental] 
     Default=off

   -j,  --json
     Output recognition results in JSON format.  Default=off

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.

   <image_file_path>
     Image containing license plates


   OpenAlpr Command Line Utility

```


Binaries
----------

Pre-compiled Windows binaries can be downloaded on the [releases page] (https://github.com/openalpr/openalpr/releases)

Install OpenALPR on Ubuntu 14.04 x64 with the following commands:

    wget -O - http://deb.openalpr.com/openalpr.gpg.key | sudo apt-key add -
    echo "deb http://deb.openalpr.com/master/ openalpr main" | sudo tee /etc/apt/sources.list.d/openalpr.list
    sudo apt-get update
    sudo apt-get install openalpr openalpr-daemon openalpr-utils libopenalpr-dev

Integrating the Library
-----------------------

OpenALPR is written in C++ and has bindings in C#, Python, and Java.  Please see this guide for examples showing how to run OpenALPR in your application: https://github.com/openalpr/openalpr/wiki/Integrating-OpenALPR

Compiling
-----------

[![Build Status](https://travis-ci.org/openalpr/openalpr.svg?branch=master)](https://travis-ci.org/openalpr/openalpr)

OpenALPR compiles and runs on Linux, Mac OSX and Windows.

OpenALPR requires the following additional libraries:

    - Tesseract OCR v3.0.3 (https://code.google.com/p/tesseract-ocr/)
    - OpenCV v2.4.8+ (http://opencv.org/)

After cloning this GitHub repository, you should download and extract Tesseract and OpenCV source code into their own directories.  Compile both libraries.

Please follow these detailed compilation guides for your respective operating system:

* [Windows] (https://github.com/openalpr/openalpr/wiki/Compilation-instructions-(Windows))
* [Ubuntu Linux] (https://github.com/openalpr/openalpr/wiki/Compilation-instructions-(Ubuntu-Linux))
* [OS X] (https://github.com/openalpr/openalpr/wiki/Compilation-instructions-(OS-X))
* [Android] (https://github.com/sujaybhowmick/OpenAlprDroidApp)
* [iOS] (https://github.com/twelve17/openalpr-ios)

If all went well, there should be an executable named *alpr* along with *libopenalpr-static.a* and *libopenalpr.so* that can be linked into your project.

Docker
------

``` shell
# Build docker image
docker build -t openalpr https://github.com/openalpr/openalpr.git
# Download test image
wget http://plates.openalpr.com/h786poj.jpg
# Run alpr on image
docker run -it --rm -v $(pwd):/data:ro openalpr -c eu h786poj.jpg
```

Questions
---------
Please post questions or comments to the Google group list: https://groups.google.com/forum/#!forum/openalpr


Contributions
-------------
Improvements to the OpenALPR library are always welcome.  Please review the [OpenALPR design description](https://github.com/openalpr/openalpr/wiki/OpenALPR-Design) and get started.

Code contributions are not the only way to help out.  Do you have a large library of license plate images?  If so, please upload your data to the anonymous FTP located at upload.openalpr.com.  Do you have time to "tag" plate images in an input image or help in other ways?  Please let everyone know by posting a note in the forum.


License
-------

Affero GPLv3
http://www.gnu.org/licenses/agpl-3.0.html
