# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.21.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.21.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/giraffe/CLionProjects/zombies/libraries/assimpMac

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/giraffe/CLionProjects/zombies/libraries/assimpMac

# Include any dependencies generated for this target.
include contrib/irrXML/CMakeFiles/IrrXML.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include contrib/irrXML/CMakeFiles/IrrXML.dir/compiler_depend.make

# Include the progress variables for this target.
include contrib/irrXML/CMakeFiles/IrrXML.dir/progress.make

# Include the compile flags for this target's objects.
include contrib/irrXML/CMakeFiles/IrrXML.dir/flags.make

contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o: contrib/irrXML/CMakeFiles/IrrXML.dir/flags.make
contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o: contrib/irrXML/irrXML.cpp
contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o: contrib/irrXML/CMakeFiles/IrrXML.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o"
	cd /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o -MF CMakeFiles/IrrXML.dir/irrXML.cpp.o.d -o CMakeFiles/IrrXML.dir/irrXML.cpp.o -c /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML/irrXML.cpp

contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IrrXML.dir/irrXML.cpp.i"
	cd /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML/irrXML.cpp > CMakeFiles/IrrXML.dir/irrXML.cpp.i

contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IrrXML.dir/irrXML.cpp.s"
	cd /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML/irrXML.cpp -o CMakeFiles/IrrXML.dir/irrXML.cpp.s

# Object files for target IrrXML
IrrXML_OBJECTS = \
"CMakeFiles/IrrXML.dir/irrXML.cpp.o"

# External object files for target IrrXML
IrrXML_EXTERNAL_OBJECTS =

lib/libIrrXML.dylib: contrib/irrXML/CMakeFiles/IrrXML.dir/irrXML.cpp.o
lib/libIrrXML.dylib: contrib/irrXML/CMakeFiles/IrrXML.dir/build.make
lib/libIrrXML.dylib: contrib/irrXML/CMakeFiles/IrrXML.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/giraffe/CLionProjects/zombies/libraries/assimpMac/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../lib/libIrrXML.dylib"
	cd /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IrrXML.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
contrib/irrXML/CMakeFiles/IrrXML.dir/build: lib/libIrrXML.dylib
.PHONY : contrib/irrXML/CMakeFiles/IrrXML.dir/build

contrib/irrXML/CMakeFiles/IrrXML.dir/clean:
	cd /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML && $(CMAKE_COMMAND) -P CMakeFiles/IrrXML.dir/cmake_clean.cmake
.PHONY : contrib/irrXML/CMakeFiles/IrrXML.dir/clean

contrib/irrXML/CMakeFiles/IrrXML.dir/depend:
	cd /Users/giraffe/CLionProjects/zombies/libraries/assimpMac && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/giraffe/CLionProjects/zombies/libraries/assimpMac /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML /Users/giraffe/CLionProjects/zombies/libraries/assimpMac /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML /Users/giraffe/CLionProjects/zombies/libraries/assimpMac/contrib/irrXML/CMakeFiles/IrrXML.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : contrib/irrXML/CMakeFiles/IrrXML.dir/depend

