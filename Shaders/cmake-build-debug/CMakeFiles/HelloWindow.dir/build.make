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
CMAKE_COMMAND = /home/guoxiaofei/clion-2018.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/guoxiaofei/clion-2018.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HelloWindow.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HelloWindow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HelloWindow.dir/flags.make

CMakeFiles/HelloWindow.dir/main.cpp.o: CMakeFiles/HelloWindow.dir/flags.make
CMakeFiles/HelloWindow.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HelloWindow.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HelloWindow.dir/main.cpp.o -c /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/main.cpp

CMakeFiles/HelloWindow.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloWindow.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/main.cpp > CMakeFiles/HelloWindow.dir/main.cpp.i

CMakeFiles/HelloWindow.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloWindow.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/main.cpp -o CMakeFiles/HelloWindow.dir/main.cpp.s

CMakeFiles/HelloWindow.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/HelloWindow.dir/main.cpp.o.requires

CMakeFiles/HelloWindow.dir/main.cpp.o.provides: CMakeFiles/HelloWindow.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/HelloWindow.dir/build.make CMakeFiles/HelloWindow.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/HelloWindow.dir/main.cpp.o.provides

CMakeFiles/HelloWindow.dir/main.cpp.o.provides.build: CMakeFiles/HelloWindow.dir/main.cpp.o


CMakeFiles/HelloWindow.dir/glad.c.o: CMakeFiles/HelloWindow.dir/flags.make
CMakeFiles/HelloWindow.dir/glad.c.o: ../glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/HelloWindow.dir/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HelloWindow.dir/glad.c.o   -c /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/glad.c

CMakeFiles/HelloWindow.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HelloWindow.dir/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/glad.c > CMakeFiles/HelloWindow.dir/glad.c.i

CMakeFiles/HelloWindow.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HelloWindow.dir/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/glad.c -o CMakeFiles/HelloWindow.dir/glad.c.s

CMakeFiles/HelloWindow.dir/glad.c.o.requires:

.PHONY : CMakeFiles/HelloWindow.dir/glad.c.o.requires

CMakeFiles/HelloWindow.dir/glad.c.o.provides: CMakeFiles/HelloWindow.dir/glad.c.o.requires
	$(MAKE) -f CMakeFiles/HelloWindow.dir/build.make CMakeFiles/HelloWindow.dir/glad.c.o.provides.build
.PHONY : CMakeFiles/HelloWindow.dir/glad.c.o.provides

CMakeFiles/HelloWindow.dir/glad.c.o.provides.build: CMakeFiles/HelloWindow.dir/glad.c.o


CMakeFiles/HelloWindow.dir/shader.cpp.o: CMakeFiles/HelloWindow.dir/flags.make
CMakeFiles/HelloWindow.dir/shader.cpp.o: ../shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/HelloWindow.dir/shader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HelloWindow.dir/shader.cpp.o -c /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/shader.cpp

CMakeFiles/HelloWindow.dir/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloWindow.dir/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/shader.cpp > CMakeFiles/HelloWindow.dir/shader.cpp.i

CMakeFiles/HelloWindow.dir/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloWindow.dir/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/shader.cpp -o CMakeFiles/HelloWindow.dir/shader.cpp.s

CMakeFiles/HelloWindow.dir/shader.cpp.o.requires:

.PHONY : CMakeFiles/HelloWindow.dir/shader.cpp.o.requires

CMakeFiles/HelloWindow.dir/shader.cpp.o.provides: CMakeFiles/HelloWindow.dir/shader.cpp.o.requires
	$(MAKE) -f CMakeFiles/HelloWindow.dir/build.make CMakeFiles/HelloWindow.dir/shader.cpp.o.provides.build
.PHONY : CMakeFiles/HelloWindow.dir/shader.cpp.o.provides

CMakeFiles/HelloWindow.dir/shader.cpp.o.provides.build: CMakeFiles/HelloWindow.dir/shader.cpp.o


# Object files for target HelloWindow
HelloWindow_OBJECTS = \
"CMakeFiles/HelloWindow.dir/main.cpp.o" \
"CMakeFiles/HelloWindow.dir/glad.c.o" \
"CMakeFiles/HelloWindow.dir/shader.cpp.o"

# External object files for target HelloWindow
HelloWindow_EXTERNAL_OBJECTS =

HelloWindow: CMakeFiles/HelloWindow.dir/main.cpp.o
HelloWindow: CMakeFiles/HelloWindow.dir/glad.c.o
HelloWindow: CMakeFiles/HelloWindow.dir/shader.cpp.o
HelloWindow: CMakeFiles/HelloWindow.dir/build.make
HelloWindow: /usr/lib/x86_64-linux-gnu/libGL.so
HelloWindow: /usr/lib/x86_64-linux-gnu/libGLU.so
HelloWindow: /usr/lib/x86_64-linux-gnu/libglut.so
HelloWindow: /usr/lib/x86_64-linux-gnu/libXmu.so
HelloWindow: /usr/lib/x86_64-linux-gnu/libXi.so
HelloWindow: CMakeFiles/HelloWindow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable HelloWindow"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HelloWindow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HelloWindow.dir/build: HelloWindow

.PHONY : CMakeFiles/HelloWindow.dir/build

CMakeFiles/HelloWindow.dir/requires: CMakeFiles/HelloWindow.dir/main.cpp.o.requires
CMakeFiles/HelloWindow.dir/requires: CMakeFiles/HelloWindow.dir/glad.c.o.requires
CMakeFiles/HelloWindow.dir/requires: CMakeFiles/HelloWindow.dir/shader.cpp.o.requires

.PHONY : CMakeFiles/HelloWindow.dir/requires

CMakeFiles/HelloWindow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HelloWindow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HelloWindow.dir/clean

CMakeFiles/HelloWindow.dir/depend:
	cd /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug /home/guoxiaofei/CLionProjects/learnOpenGL/Shaders/cmake-build-debug/CMakeFiles/HelloWindow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HelloWindow.dir/depend

