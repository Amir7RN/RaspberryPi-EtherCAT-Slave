# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/IMU/FINALCODE/ONEIMU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/IMU/FINALCODE/ONEIMU/build

# Include any dependencies generated for this target.
include applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/depend.make

# Include the progress variables for this target.
include applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/progress.make

# Include the compile flags for this target's objects.
include applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/flags.make

applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.o: applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/flags.make
applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.o: ../applications/raspberry_lan9252demo/getSensorData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/IMU/FINALCODE/ONEIMU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.o"
	cd /home/IMU/FINALCODE/ONEIMU/build/applications/raspberry_lan9252demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.o -c /home/IMU/FINALCODE/ONEIMU/applications/raspberry_lan9252demo/getSensorData.cpp

applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.i"
	cd /home/IMU/FINALCODE/ONEIMU/build/applications/raspberry_lan9252demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/IMU/FINALCODE/ONEIMU/applications/raspberry_lan9252demo/getSensorData.cpp > CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.i

applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.s"
	cd /home/IMU/FINALCODE/ONEIMU/build/applications/raspberry_lan9252demo && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/IMU/FINALCODE/ONEIMU/applications/raspberry_lan9252demo/getSensorData.cpp -o CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.s

# Object files for target getSensorData_lib
getSensorData_lib_OBJECTS = \
"CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.o"

# External object files for target getSensorData_lib
getSensorData_lib_EXTERNAL_OBJECTS =

applications/raspberry_lan9252demo/libgetSensorData_lib.a: applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/getSensorData.cpp.o
applications/raspberry_lan9252demo/libgetSensorData_lib.a: applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/build.make
applications/raspberry_lan9252demo/libgetSensorData_lib.a: applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/IMU/FINALCODE/ONEIMU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgetSensorData_lib.a"
	cd /home/IMU/FINALCODE/ONEIMU/build/applications/raspberry_lan9252demo && $(CMAKE_COMMAND) -P CMakeFiles/getSensorData_lib.dir/cmake_clean_target.cmake
	cd /home/IMU/FINALCODE/ONEIMU/build/applications/raspberry_lan9252demo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/getSensorData_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/build: applications/raspberry_lan9252demo/libgetSensorData_lib.a

.PHONY : applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/build

applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/clean:
	cd /home/IMU/FINALCODE/ONEIMU/build/applications/raspberry_lan9252demo && $(CMAKE_COMMAND) -P CMakeFiles/getSensorData_lib.dir/cmake_clean.cmake
.PHONY : applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/clean

applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/depend:
	cd /home/IMU/FINALCODE/ONEIMU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/IMU/FINALCODE/ONEIMU /home/IMU/FINALCODE/ONEIMU/applications/raspberry_lan9252demo /home/IMU/FINALCODE/ONEIMU/build /home/IMU/FINALCODE/ONEIMU/build/applications/raspberry_lan9252demo /home/IMU/FINALCODE/ONEIMU/build/applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : applications/raspberry_lan9252demo/CMakeFiles/getSensorData_lib.dir/depend

