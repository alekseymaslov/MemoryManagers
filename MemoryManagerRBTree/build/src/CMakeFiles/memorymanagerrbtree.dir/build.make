# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/alex/projects/MemoryManagerRBTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/projects/MemoryManagerRBTree/build

# Include any dependencies generated for this target.
include src/CMakeFiles/memorymanagerrbtree.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/memorymanagerrbtree.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/memorymanagerrbtree.dir/flags.make

src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o: src/CMakeFiles/memorymanagerrbtree.dir/flags.make
src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/projects/MemoryManagerRBTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o"
	cd /home/alex/projects/MemoryManagerRBTree/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/memorymanagerrbtree.dir/main.cpp.o -c /home/alex/projects/MemoryManagerRBTree/src/main.cpp

src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/memorymanagerrbtree.dir/main.cpp.i"
	cd /home/alex/projects/MemoryManagerRBTree/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/projects/MemoryManagerRBTree/src/main.cpp > CMakeFiles/memorymanagerrbtree.dir/main.cpp.i

src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/memorymanagerrbtree.dir/main.cpp.s"
	cd /home/alex/projects/MemoryManagerRBTree/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/projects/MemoryManagerRBTree/src/main.cpp -o CMakeFiles/memorymanagerrbtree.dir/main.cpp.s

src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o.requires

src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o.provides: src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/memorymanagerrbtree.dir/build.make src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o.provides

src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o.provides.build: src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o


# Object files for target memorymanagerrbtree
memorymanagerrbtree_OBJECTS = \
"CMakeFiles/memorymanagerrbtree.dir/main.cpp.o"

# External object files for target memorymanagerrbtree
memorymanagerrbtree_EXTERNAL_OBJECTS =

bin/memorymanagerrbtree: src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o
bin/memorymanagerrbtree: src/CMakeFiles/memorymanagerrbtree.dir/build.make
bin/memorymanagerrbtree: src/CMakeFiles/memorymanagerrbtree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/projects/MemoryManagerRBTree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/memorymanagerrbtree"
	cd /home/alex/projects/MemoryManagerRBTree/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/memorymanagerrbtree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/memorymanagerrbtree.dir/build: bin/memorymanagerrbtree

.PHONY : src/CMakeFiles/memorymanagerrbtree.dir/build

src/CMakeFiles/memorymanagerrbtree.dir/requires: src/CMakeFiles/memorymanagerrbtree.dir/main.cpp.o.requires

.PHONY : src/CMakeFiles/memorymanagerrbtree.dir/requires

src/CMakeFiles/memorymanagerrbtree.dir/clean:
	cd /home/alex/projects/MemoryManagerRBTree/build/src && $(CMAKE_COMMAND) -P CMakeFiles/memorymanagerrbtree.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/memorymanagerrbtree.dir/clean

src/CMakeFiles/memorymanagerrbtree.dir/depend:
	cd /home/alex/projects/MemoryManagerRBTree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/projects/MemoryManagerRBTree /home/alex/projects/MemoryManagerRBTree/src /home/alex/projects/MemoryManagerRBTree/build /home/alex/projects/MemoryManagerRBTree/build/src /home/alex/projects/MemoryManagerRBTree/build/src/CMakeFiles/memorymanagerrbtree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/memorymanagerrbtree.dir/depend

