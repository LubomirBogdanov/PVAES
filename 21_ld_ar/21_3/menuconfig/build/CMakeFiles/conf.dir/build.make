# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /home/lbogdanov/programs/xilinx/Vitis/2022.2/tps/lnx64/cmake-3.3.2/bin/cmake

# The command to remove a file.
RM = /home/lbogdanov/programs/xilinx/Vitis/2022.2/tps/lnx64/cmake-3.3.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/build

# Include any dependencies generated for this target.
include CMakeFiles/conf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/conf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/conf.dir/flags.make

CMakeFiles/conf.dir/conf.c.o: CMakeFiles/conf.dir/flags.make
CMakeFiles/conf.dir/conf.c.o: ../conf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/conf.dir/conf.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/conf.dir/conf.c.o   -c /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/conf.c

CMakeFiles/conf.dir/conf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/conf.dir/conf.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/conf.c > CMakeFiles/conf.dir/conf.c.i

CMakeFiles/conf.dir/conf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/conf.dir/conf.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/conf.c -o CMakeFiles/conf.dir/conf.c.s

CMakeFiles/conf.dir/conf.c.o.requires:

.PHONY : CMakeFiles/conf.dir/conf.c.o.requires

CMakeFiles/conf.dir/conf.c.o.provides: CMakeFiles/conf.dir/conf.c.o.requires
	$(MAKE) -f CMakeFiles/conf.dir/build.make CMakeFiles/conf.dir/conf.c.o.provides.build
.PHONY : CMakeFiles/conf.dir/conf.c.o.provides

CMakeFiles/conf.dir/conf.c.o.provides.build: CMakeFiles/conf.dir/conf.c.o


# Object files for target conf
conf_OBJECTS = \
"CMakeFiles/conf.dir/conf.c.o"

# External object files for target conf
conf_EXTERNAL_OBJECTS =

conf: CMakeFiles/conf.dir/conf.c.o
conf: CMakeFiles/conf.dir/build.make
conf: /usr/lib/x86_64-linux-gnu/libncurses.so
conf: /usr/lib/x86_64-linux-gnu/libform.so
conf: libzconf.a
conf: CMakeFiles/conf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable conf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/conf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/conf.dir/build: conf

.PHONY : CMakeFiles/conf.dir/build

CMakeFiles/conf.dir/requires: CMakeFiles/conf.dir/conf.c.o.requires

.PHONY : CMakeFiles/conf.dir/requires

CMakeFiles/conf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/conf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/conf.dir/clean

CMakeFiles/conf.dir/depend:
	cd /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/build /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/build /home/lbogdanov/workspaces/xilinx_workspace/18_08/menuconfig/build/CMakeFiles/conf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/conf.dir/depend

