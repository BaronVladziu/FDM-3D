# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/baronvladziu/Downloads/CLion-2018.2.2/clion-2018.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/baronvladziu/Downloads/CLion-2018.2.2/clion-2018.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/baronvladziu/Projects/Vulkan/FDM-3D/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/vulkan-fdm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vulkan-fdm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vulkan-fdm.dir/flags.make

CMakeFiles/vulkan-fdm.dir/main.cpp.o: CMakeFiles/vulkan-fdm.dir/flags.make
CMakeFiles/vulkan-fdm.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vulkan-fdm.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vulkan-fdm.dir/main.cpp.o -c /home/baronvladziu/Projects/Vulkan/FDM-3D/src/main.cpp

CMakeFiles/vulkan-fdm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vulkan-fdm.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/baronvladziu/Projects/Vulkan/FDM-3D/src/main.cpp > CMakeFiles/vulkan-fdm.dir/main.cpp.i

CMakeFiles/vulkan-fdm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vulkan-fdm.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/baronvladziu/Projects/Vulkan/FDM-3D/src/main.cpp -o CMakeFiles/vulkan-fdm.dir/main.cpp.s

CMakeFiles/vulkan-fdm.dir/App.cpp.o: CMakeFiles/vulkan-fdm.dir/flags.make
CMakeFiles/vulkan-fdm.dir/App.cpp.o: ../App.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/vulkan-fdm.dir/App.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vulkan-fdm.dir/App.cpp.o -c /home/baronvladziu/Projects/Vulkan/FDM-3D/src/App.cpp

CMakeFiles/vulkan-fdm.dir/App.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vulkan-fdm.dir/App.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/baronvladziu/Projects/Vulkan/FDM-3D/src/App.cpp > CMakeFiles/vulkan-fdm.dir/App.cpp.i

CMakeFiles/vulkan-fdm.dir/App.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vulkan-fdm.dir/App.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/baronvladziu/Projects/Vulkan/FDM-3D/src/App.cpp -o CMakeFiles/vulkan-fdm.dir/App.cpp.s

CMakeFiles/vulkan-fdm.dir/Renderer.cpp.o: CMakeFiles/vulkan-fdm.dir/flags.make
CMakeFiles/vulkan-fdm.dir/Renderer.cpp.o: ../Renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/vulkan-fdm.dir/Renderer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vulkan-fdm.dir/Renderer.cpp.o -c /home/baronvladziu/Projects/Vulkan/FDM-3D/src/Renderer.cpp

CMakeFiles/vulkan-fdm.dir/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vulkan-fdm.dir/Renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/baronvladziu/Projects/Vulkan/FDM-3D/src/Renderer.cpp > CMakeFiles/vulkan-fdm.dir/Renderer.cpp.i

CMakeFiles/vulkan-fdm.dir/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vulkan-fdm.dir/Renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/baronvladziu/Projects/Vulkan/FDM-3D/src/Renderer.cpp -o CMakeFiles/vulkan-fdm.dir/Renderer.cpp.s

CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.o: CMakeFiles/vulkan-fdm.dir/flags.make
CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.o: ../RenderVertex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.o -c /home/baronvladziu/Projects/Vulkan/FDM-3D/src/RenderVertex.cpp

CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/baronvladziu/Projects/Vulkan/FDM-3D/src/RenderVertex.cpp > CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.i

CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/baronvladziu/Projects/Vulkan/FDM-3D/src/RenderVertex.cpp -o CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.s

CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.o: CMakeFiles/vulkan-fdm.dir/flags.make
CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.o: ../RenderTriangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.o -c /home/baronvladziu/Projects/Vulkan/FDM-3D/src/RenderTriangle.cpp

CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/baronvladziu/Projects/Vulkan/FDM-3D/src/RenderTriangle.cpp > CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.i

CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/baronvladziu/Projects/Vulkan/FDM-3D/src/RenderTriangle.cpp -o CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.s

CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.o: CMakeFiles/vulkan-fdm.dir/flags.make
CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.o: ../MapLoader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.o -c /home/baronvladziu/Projects/Vulkan/FDM-3D/src/MapLoader.cpp

CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/baronvladziu/Projects/Vulkan/FDM-3D/src/MapLoader.cpp > CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.i

CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/baronvladziu/Projects/Vulkan/FDM-3D/src/MapLoader.cpp -o CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.s

CMakeFiles/vulkan-fdm.dir/Map.cpp.o: CMakeFiles/vulkan-fdm.dir/flags.make
CMakeFiles/vulkan-fdm.dir/Map.cpp.o: ../Map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/vulkan-fdm.dir/Map.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vulkan-fdm.dir/Map.cpp.o -c /home/baronvladziu/Projects/Vulkan/FDM-3D/src/Map.cpp

CMakeFiles/vulkan-fdm.dir/Map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vulkan-fdm.dir/Map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/baronvladziu/Projects/Vulkan/FDM-3D/src/Map.cpp > CMakeFiles/vulkan-fdm.dir/Map.cpp.i

CMakeFiles/vulkan-fdm.dir/Map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vulkan-fdm.dir/Map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/baronvladziu/Projects/Vulkan/FDM-3D/src/Map.cpp -o CMakeFiles/vulkan-fdm.dir/Map.cpp.s

# Object files for target vulkan-fdm
vulkan__fdm_OBJECTS = \
"CMakeFiles/vulkan-fdm.dir/main.cpp.o" \
"CMakeFiles/vulkan-fdm.dir/App.cpp.o" \
"CMakeFiles/vulkan-fdm.dir/Renderer.cpp.o" \
"CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.o" \
"CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.o" \
"CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.o" \
"CMakeFiles/vulkan-fdm.dir/Map.cpp.o"

# External object files for target vulkan-fdm
vulkan__fdm_EXTERNAL_OBJECTS =

vulkan-fdm: CMakeFiles/vulkan-fdm.dir/main.cpp.o
vulkan-fdm: CMakeFiles/vulkan-fdm.dir/App.cpp.o
vulkan-fdm: CMakeFiles/vulkan-fdm.dir/Renderer.cpp.o
vulkan-fdm: CMakeFiles/vulkan-fdm.dir/RenderVertex.cpp.o
vulkan-fdm: CMakeFiles/vulkan-fdm.dir/RenderTriangle.cpp.o
vulkan-fdm: CMakeFiles/vulkan-fdm.dir/MapLoader.cpp.o
vulkan-fdm: CMakeFiles/vulkan-fdm.dir/Map.cpp.o
vulkan-fdm: CMakeFiles/vulkan-fdm.dir/build.make
vulkan-fdm: /usr/local/lib/libglfw3.a
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libXrandr.so
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libXcursor.so
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libXinerama.so
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libXi.so
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libSM.so
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libICE.so
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libX11.so
vulkan-fdm: /usr/lib/x86_64-linux-gnu/libXext.so
vulkan-fdm: ../../vulkan/x86_64/lib/libvulkan.so
vulkan-fdm: CMakeFiles/vulkan-fdm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable vulkan-fdm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vulkan-fdm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vulkan-fdm.dir/build: vulkan-fdm

.PHONY : CMakeFiles/vulkan-fdm.dir/build

CMakeFiles/vulkan-fdm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vulkan-fdm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vulkan-fdm.dir/clean

CMakeFiles/vulkan-fdm.dir/depend:
	cd /home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/baronvladziu/Projects/Vulkan/FDM-3D/src /home/baronvladziu/Projects/Vulkan/FDM-3D/src /home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug /home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug /home/baronvladziu/Projects/Vulkan/FDM-3D/src/cmake-build-debug/CMakeFiles/vulkan-fdm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vulkan-fdm.dir/depend

