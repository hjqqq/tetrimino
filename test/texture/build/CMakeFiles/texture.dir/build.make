# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/build

# Include any dependencies generated for this target.
include CMakeFiles/texture.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/texture.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/texture.dir/flags.make

CMakeFiles/texture.dir/main.cpp.o: CMakeFiles/texture.dir/flags.make
CMakeFiles/texture.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/texture.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/texture.dir/main.cpp.o -c /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/main.cpp

CMakeFiles/texture.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/texture.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/main.cpp > CMakeFiles/texture.dir/main.cpp.i

CMakeFiles/texture.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/texture.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/main.cpp -o CMakeFiles/texture.dir/main.cpp.s

CMakeFiles/texture.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/texture.dir/main.cpp.o.requires

CMakeFiles/texture.dir/main.cpp.o.provides: CMakeFiles/texture.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/texture.dir/build.make CMakeFiles/texture.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/texture.dir/main.cpp.o.provides

CMakeFiles/texture.dir/main.cpp.o.provides.build: CMakeFiles/texture.dir/main.cpp.o

# Object files for target texture
texture_OBJECTS = \
"CMakeFiles/texture.dir/main.cpp.o"

# External object files for target texture
texture_EXTERNAL_OBJECTS =

texture: CMakeFiles/texture.dir/main.cpp.o
texture: /usr/lib/libSDLmain.a
texture: /usr/lib/libSDL.so
texture: /usr/lib/libSDL_image.so
texture: CMakeFiles/texture.dir/build.make
texture: CMakeFiles/texture.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable texture"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/texture.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/texture.dir/build: texture
.PHONY : CMakeFiles/texture.dir/build

CMakeFiles/texture.dir/requires: CMakeFiles/texture.dir/main.cpp.o.requires
.PHONY : CMakeFiles/texture.dir/requires

CMakeFiles/texture.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/texture.dir/cmake_clean.cmake
.PHONY : CMakeFiles/texture.dir/clean

CMakeFiles/texture.dir/depend:
	cd /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/build /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/build /home/tom/study/SDL/TetriminoProject/tetrimino/test/texture/build/CMakeFiles/texture.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/texture.dir/depend

