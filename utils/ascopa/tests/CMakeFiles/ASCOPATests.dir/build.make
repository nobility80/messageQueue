# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daimler/workspace/messageQueue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daimler/workspace/messageQueue

# Include any dependencies generated for this target.
include utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/depend.make

# Include the progress variables for this target.
include utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/progress.make

# Include the compile flags for this target's objects.
include utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/flags.make

utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/main.cpp.o: utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/flags.make
utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/main.cpp.o: utils/ascopa/tests/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daimler/workspace/messageQueue/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/main.cpp.o"
	cd /home/daimler/workspace/messageQueue/utils/ascopa/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ASCOPATests.dir/main.cpp.o -c /home/daimler/workspace/messageQueue/utils/ascopa/tests/main.cpp

utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ASCOPATests.dir/main.cpp.i"
	cd /home/daimler/workspace/messageQueue/utils/ascopa/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daimler/workspace/messageQueue/utils/ascopa/tests/main.cpp > CMakeFiles/ASCOPATests.dir/main.cpp.i

utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ASCOPATests.dir/main.cpp.s"
	cd /home/daimler/workspace/messageQueue/utils/ascopa/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daimler/workspace/messageQueue/utils/ascopa/tests/main.cpp -o CMakeFiles/ASCOPATests.dir/main.cpp.s

utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.o: utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/flags.make
utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.o: utils/ascopa/tests/ascopaunittests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daimler/workspace/messageQueue/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.o"
	cd /home/daimler/workspace/messageQueue/utils/ascopa/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.o -c /home/daimler/workspace/messageQueue/utils/ascopa/tests/ascopaunittests.cpp

utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.i"
	cd /home/daimler/workspace/messageQueue/utils/ascopa/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daimler/workspace/messageQueue/utils/ascopa/tests/ascopaunittests.cpp > CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.i

utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.s"
	cd /home/daimler/workspace/messageQueue/utils/ascopa/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daimler/workspace/messageQueue/utils/ascopa/tests/ascopaunittests.cpp -o CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.s

# Object files for target ASCOPATests
ASCOPATests_OBJECTS = \
"CMakeFiles/ASCOPATests.dir/main.cpp.o" \
"CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.o"

# External object files for target ASCOPATests
ASCOPATests_EXTERNAL_OBJECTS =

utils/ascopa/tests/ASCOPATests: utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/main.cpp.o
utils/ascopa/tests/ASCOPATests: utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/ascopaunittests.cpp.o
utils/ascopa/tests/ASCOPATests: utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/build.make
utils/ascopa/tests/ASCOPATests: utils/ascopa/libascopa.a
utils/ascopa/tests/ASCOPATests: utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daimler/workspace/messageQueue/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ASCOPATests"
	cd /home/daimler/workspace/messageQueue/utils/ascopa/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ASCOPATests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/build: utils/ascopa/tests/ASCOPATests

.PHONY : utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/build

utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/clean:
	cd /home/daimler/workspace/messageQueue/utils/ascopa/tests && $(CMAKE_COMMAND) -P CMakeFiles/ASCOPATests.dir/cmake_clean.cmake
.PHONY : utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/clean

utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/depend:
	cd /home/daimler/workspace/messageQueue && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daimler/workspace/messageQueue /home/daimler/workspace/messageQueue/utils/ascopa/tests /home/daimler/workspace/messageQueue /home/daimler/workspace/messageQueue/utils/ascopa/tests /home/daimler/workspace/messageQueue/utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/ascopa/tests/CMakeFiles/ASCOPATests.dir/depend

