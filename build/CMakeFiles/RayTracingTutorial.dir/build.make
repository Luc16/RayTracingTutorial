# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luc/CLionProjects/RayTracingTutorial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luc/CLionProjects/RayTracingTutorial/build

# Include any dependencies generated for this target.
include CMakeFiles/RayTracingTutorial.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RayTracingTutorial.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RayTracingTutorial.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RayTracingTutorial.dir/flags.make

CMakeFiles/RayTracingTutorial.dir/main.cpp.o: CMakeFiles/RayTracingTutorial.dir/flags.make
CMakeFiles/RayTracingTutorial.dir/main.cpp.o: ../main.cpp
CMakeFiles/RayTracingTutorial.dir/main.cpp.o: CMakeFiles/RayTracingTutorial.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luc/CLionProjects/RayTracingTutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RayTracingTutorial.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RayTracingTutorial.dir/main.cpp.o -MF CMakeFiles/RayTracingTutorial.dir/main.cpp.o.d -o CMakeFiles/RayTracingTutorial.dir/main.cpp.o -c /home/luc/CLionProjects/RayTracingTutorial/main.cpp

CMakeFiles/RayTracingTutorial.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RayTracingTutorial.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luc/CLionProjects/RayTracingTutorial/main.cpp > CMakeFiles/RayTracingTutorial.dir/main.cpp.i

CMakeFiles/RayTracingTutorial.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RayTracingTutorial.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luc/CLionProjects/RayTracingTutorial/main.cpp -o CMakeFiles/RayTracingTutorial.dir/main.cpp.s

# Object files for target RayTracingTutorial
RayTracingTutorial_OBJECTS = \
"CMakeFiles/RayTracingTutorial.dir/main.cpp.o"

# External object files for target RayTracingTutorial
RayTracingTutorial_EXTERNAL_OBJECTS =

RayTracingTutorial: CMakeFiles/RayTracingTutorial.dir/main.cpp.o
RayTracingTutorial: CMakeFiles/RayTracingTutorial.dir/build.make
RayTracingTutorial: CMakeFiles/RayTracingTutorial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luc/CLionProjects/RayTracingTutorial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RayTracingTutorial"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RayTracingTutorial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RayTracingTutorial.dir/build: RayTracingTutorial
.PHONY : CMakeFiles/RayTracingTutorial.dir/build

CMakeFiles/RayTracingTutorial.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RayTracingTutorial.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RayTracingTutorial.dir/clean

CMakeFiles/RayTracingTutorial.dir/depend:
	cd /home/luc/CLionProjects/RayTracingTutorial/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luc/CLionProjects/RayTracingTutorial /home/luc/CLionProjects/RayTracingTutorial /home/luc/CLionProjects/RayTracingTutorial/build /home/luc/CLionProjects/RayTracingTutorial/build /home/luc/CLionProjects/RayTracingTutorial/build/CMakeFiles/RayTracingTutorial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RayTracingTutorial.dir/depend

