# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\deonj\Documents\CIS 350\Proj1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\deonj\Documents\CIS 350\Proj1\cmake-build-default"

# Include any dependencies generated for this target.
include CMakeFiles/Proj1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Proj1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Proj1.dir/flags.make

CMakeFiles/Proj1.dir/main.cpp.obj: CMakeFiles/Proj1.dir/flags.make
CMakeFiles/Proj1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\deonj\Documents\CIS 350\Proj1\cmake-build-default\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Proj1.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Proj1.dir\main.cpp.obj -c "C:\Users\deonj\Documents\CIS 350\Proj1\main.cpp"

CMakeFiles/Proj1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proj1.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\deonj\Documents\CIS 350\Proj1\main.cpp" > CMakeFiles\Proj1.dir\main.cpp.i

CMakeFiles/Proj1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proj1.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\deonj\Documents\CIS 350\Proj1\main.cpp" -o CMakeFiles\Proj1.dir\main.cpp.s

CMakeFiles/Proj1.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/Proj1.dir/main.cpp.obj.requires

CMakeFiles/Proj1.dir/main.cpp.obj.provides: CMakeFiles/Proj1.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\Proj1.dir\build.make CMakeFiles/Proj1.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/Proj1.dir/main.cpp.obj.provides

CMakeFiles/Proj1.dir/main.cpp.obj.provides.build: CMakeFiles/Proj1.dir/main.cpp.obj


# Object files for target Proj1
Proj1_OBJECTS = \
"CMakeFiles/Proj1.dir/main.cpp.obj"

# External object files for target Proj1
Proj1_EXTERNAL_OBJECTS =

Proj1.exe: CMakeFiles/Proj1.dir/main.cpp.obj
Proj1.exe: CMakeFiles/Proj1.dir/build.make
Proj1.exe: CMakeFiles/Proj1.dir/linklibs.rsp
Proj1.exe: CMakeFiles/Proj1.dir/objects1.rsp
Proj1.exe: CMakeFiles/Proj1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\deonj\Documents\CIS 350\Proj1\cmake-build-default\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Proj1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Proj1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Proj1.dir/build: Proj1.exe

.PHONY : CMakeFiles/Proj1.dir/build

CMakeFiles/Proj1.dir/requires: CMakeFiles/Proj1.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/Proj1.dir/requires

CMakeFiles/Proj1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Proj1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Proj1.dir/clean

CMakeFiles/Proj1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\deonj\Documents\CIS 350\Proj1" "C:\Users\deonj\Documents\CIS 350\Proj1" "C:\Users\deonj\Documents\CIS 350\Proj1\cmake-build-default" "C:\Users\deonj\Documents\CIS 350\Proj1\cmake-build-default" "C:\Users\deonj\Documents\CIS 350\Proj1\cmake-build-default\CMakeFiles\Proj1.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Proj1.dir/depend
