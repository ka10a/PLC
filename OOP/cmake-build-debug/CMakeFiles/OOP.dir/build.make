# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/imroggen/clion-2020.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/imroggen/clion-2020.2.4/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/imroggen/CLionProjects/PLC/OOP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/imroggen/CLionProjects/PLC/OOP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OOP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OOP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OOP.dir/flags.make

CMakeFiles/OOP.dir/main.cpp.o: CMakeFiles/OOP.dir/flags.make
CMakeFiles/OOP.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/imroggen/CLionProjects/PLC/OOP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OOP.dir/main.cpp.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OOP.dir/main.cpp.o -c /home/imroggen/CLionProjects/PLC/OOP/main.cpp

CMakeFiles/OOP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OOP.dir/main.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/imroggen/CLionProjects/PLC/OOP/main.cpp > CMakeFiles/OOP.dir/main.cpp.i

CMakeFiles/OOP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OOP.dir/main.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/imroggen/CLionProjects/PLC/OOP/main.cpp -o CMakeFiles/OOP.dir/main.cpp.s

# Object files for target OOP
OOP_OBJECTS = \
"CMakeFiles/OOP.dir/main.cpp.o"

# External object files for target OOP
OOP_EXTERNAL_OBJECTS =

OOP: CMakeFiles/OOP.dir/main.cpp.o
OOP: CMakeFiles/OOP.dir/build.make
OOP: CMakeFiles/OOP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/imroggen/CLionProjects/PLC/OOP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OOP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OOP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OOP.dir/build: OOP

.PHONY : CMakeFiles/OOP.dir/build

CMakeFiles/OOP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OOP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OOP.dir/clean

CMakeFiles/OOP.dir/depend:
	cd /home/imroggen/CLionProjects/PLC/OOP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/imroggen/CLionProjects/PLC/OOP /home/imroggen/CLionProjects/PLC/OOP /home/imroggen/CLionProjects/PLC/OOP/cmake-build-debug /home/imroggen/CLionProjects/PLC/OOP/cmake-build-debug /home/imroggen/CLionProjects/PLC/OOP/cmake-build-debug/CMakeFiles/OOP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OOP.dir/depend
