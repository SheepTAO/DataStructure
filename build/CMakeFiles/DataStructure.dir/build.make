# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/archtao/Works/Cpp/DataStructure

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/archtao/Works/Cpp/DataStructure/build

# Include any dependencies generated for this target.
include CMakeFiles/DataStructure.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DataStructure.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DataStructure.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DataStructure.dir/flags.make

CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o: CMakeFiles/DataStructure.dir/flags.make
CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o: ../chapter5/BinaryTree.cpp
CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o: CMakeFiles/DataStructure.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/archtao/Works/Cpp/DataStructure/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o -MF CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o.d -o CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o -c /home/archtao/Works/Cpp/DataStructure/chapter5/BinaryTree.cpp

CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/archtao/Works/Cpp/DataStructure/chapter5/BinaryTree.cpp > CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.i

CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/archtao/Works/Cpp/DataStructure/chapter5/BinaryTree.cpp -o CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.s

# Object files for target DataStructure
DataStructure_OBJECTS = \
"CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o"

# External object files for target DataStructure
DataStructure_EXTERNAL_OBJECTS =

DataStructure: CMakeFiles/DataStructure.dir/chapter5/BinaryTree.cpp.o
DataStructure: CMakeFiles/DataStructure.dir/build.make
DataStructure: CMakeFiles/DataStructure.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/archtao/Works/Cpp/DataStructure/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DataStructure"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DataStructure.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DataStructure.dir/build: DataStructure
.PHONY : CMakeFiles/DataStructure.dir/build

CMakeFiles/DataStructure.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DataStructure.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DataStructure.dir/clean

CMakeFiles/DataStructure.dir/depend:
	cd /home/archtao/Works/Cpp/DataStructure/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/archtao/Works/Cpp/DataStructure /home/archtao/Works/Cpp/DataStructure /home/archtao/Works/Cpp/DataStructure/build /home/archtao/Works/Cpp/DataStructure/build /home/archtao/Works/Cpp/DataStructure/build/CMakeFiles/DataStructure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DataStructure.dir/depend

