# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\angeliton\Desktop\openalpr-mingw-master\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\angeliton\Desktop\openalpr-mingw-master\src-build

# Include any dependencies generated for this target.
include CMakeFiles/alpr.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/alpr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/alpr.dir/flags.make

CMakeFiles/alpr.dir/main.cpp.obj: CMakeFiles/alpr.dir/flags.make
CMakeFiles/alpr.dir/main.cpp.obj: CMakeFiles/alpr.dir/includes_CXX.rsp
CMakeFiles/alpr.dir/main.cpp.obj: C:/Users/angeliton/Desktop/openalpr-mingw-master/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\angeliton\Desktop\openalpr-mingw-master\src-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/alpr.dir/main.cpp.obj"
	C:\mingw\mingw32\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\alpr.dir\main.cpp.obj -c C:\Users\angeliton\Desktop\openalpr-mingw-master\src\main.cpp

CMakeFiles/alpr.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/alpr.dir/main.cpp.i"
	C:\mingw\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\angeliton\Desktop\openalpr-mingw-master\src\main.cpp > CMakeFiles\alpr.dir\main.cpp.i

CMakeFiles/alpr.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/alpr.dir/main.cpp.s"
	C:\mingw\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\angeliton\Desktop\openalpr-mingw-master\src\main.cpp -o CMakeFiles\alpr.dir\main.cpp.s

CMakeFiles/alpr.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/alpr.dir/main.cpp.obj.requires

CMakeFiles/alpr.dir/main.cpp.obj.provides: CMakeFiles/alpr.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\alpr.dir\build.make CMakeFiles/alpr.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/alpr.dir/main.cpp.obj.provides

CMakeFiles/alpr.dir/main.cpp.obj.provides.build: CMakeFiles/alpr.dir/main.cpp.obj


# Object files for target alpr
alpr_OBJECTS = \
"CMakeFiles/alpr.dir/main.cpp.obj"

# External object files for target alpr
alpr_EXTERNAL_OBJECTS =

alpr.exe: CMakeFiles/alpr.dir/main.cpp.obj
alpr.exe: CMakeFiles/alpr.dir/build.make
alpr.exe: openalpr/libopenalpr-static.a
alpr.exe: openalpr/support/libsupport.a
alpr.exe: video/libvideo.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_videostab2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_ts2410.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_superres2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_stitching2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_contrib2410.dll.a
alpr.exe: C:/Users/angeliton/Desktop/openalpr-mingw-master/src/../deps/lib/libtesseract305.a
alpr.exe: C:/Users/angeliton/Desktop/openalpr-mingw-master/src/../deps/lib/libtesseract305.a
alpr.exe: openalpr/support/libsupport.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_nonfree2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_ocl2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_gpu2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_photo2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_objdetect2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_legacy2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_video2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_ml2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_calib3d2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_features2d2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_highgui2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_imgproc2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_flann2410.dll.a
alpr.exe: C:/opencv/sources-build/lib/libopencv_core2410.dll.a
alpr.exe: CMakeFiles/alpr.dir/linklibs.rsp
alpr.exe: CMakeFiles/alpr.dir/objects1.rsp
alpr.exe: CMakeFiles/alpr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\angeliton\Desktop\openalpr-mingw-master\src-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable alpr.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\alpr.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/alpr.dir/build: alpr.exe

.PHONY : CMakeFiles/alpr.dir/build

CMakeFiles/alpr.dir/requires: CMakeFiles/alpr.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/alpr.dir/requires

CMakeFiles/alpr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\alpr.dir\cmake_clean.cmake
.PHONY : CMakeFiles/alpr.dir/clean

CMakeFiles/alpr.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\angeliton\Desktop\openalpr-mingw-master\src C:\Users\angeliton\Desktop\openalpr-mingw-master\src C:\Users\angeliton\Desktop\openalpr-mingw-master\src-build C:\Users\angeliton\Desktop\openalpr-mingw-master\src-build C:\Users\angeliton\Desktop\openalpr-mingw-master\src-build\CMakeFiles\alpr.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/alpr.dir/depend
