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
CMAKE_SOURCE_DIR = /home/zy/project/WebServer_mine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zy/project/WebServer_mine/build

# Include any dependencies generated for this target.
include src/base/CMakeFiles/webserver_base.dir/depend.make

# Include the progress variables for this target.
include src/base/CMakeFiles/webserver_base.dir/progress.make

# Include the compile flags for this target's objects.
include src/base/CMakeFiles/webserver_base.dir/flags.make

src/base/CMakeFiles/webserver_base.dir/AsyncLogging.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/AsyncLogging.cpp.o: ../src/base/AsyncLogging.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/base/CMakeFiles/webserver_base.dir/AsyncLogging.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/AsyncLogging.cpp.o -c /home/zy/project/WebServer_mine/src/base/AsyncLogging.cpp

src/base/CMakeFiles/webserver_base.dir/AsyncLogging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/AsyncLogging.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/AsyncLogging.cpp > CMakeFiles/webserver_base.dir/AsyncLogging.cpp.i

src/base/CMakeFiles/webserver_base.dir/AsyncLogging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/AsyncLogging.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/AsyncLogging.cpp -o CMakeFiles/webserver_base.dir/AsyncLogging.cpp.s

src/base/CMakeFiles/webserver_base.dir/CountDownLatch.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/CountDownLatch.cpp.o: ../src/base/CountDownLatch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/base/CMakeFiles/webserver_base.dir/CountDownLatch.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/CountDownLatch.cpp.o -c /home/zy/project/WebServer_mine/src/base/CountDownLatch.cpp

src/base/CMakeFiles/webserver_base.dir/CountDownLatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/CountDownLatch.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/CountDownLatch.cpp > CMakeFiles/webserver_base.dir/CountDownLatch.cpp.i

src/base/CMakeFiles/webserver_base.dir/CountDownLatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/CountDownLatch.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/CountDownLatch.cpp -o CMakeFiles/webserver_base.dir/CountDownLatch.cpp.s

src/base/CMakeFiles/webserver_base.dir/FileUtil.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/FileUtil.cpp.o: ../src/base/FileUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/base/CMakeFiles/webserver_base.dir/FileUtil.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/FileUtil.cpp.o -c /home/zy/project/WebServer_mine/src/base/FileUtil.cpp

src/base/CMakeFiles/webserver_base.dir/FileUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/FileUtil.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/FileUtil.cpp > CMakeFiles/webserver_base.dir/FileUtil.cpp.i

src/base/CMakeFiles/webserver_base.dir/FileUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/FileUtil.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/FileUtil.cpp -o CMakeFiles/webserver_base.dir/FileUtil.cpp.s

src/base/CMakeFiles/webserver_base.dir/LogFile.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/LogFile.cpp.o: ../src/base/LogFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/base/CMakeFiles/webserver_base.dir/LogFile.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/LogFile.cpp.o -c /home/zy/project/WebServer_mine/src/base/LogFile.cpp

src/base/CMakeFiles/webserver_base.dir/LogFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/LogFile.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/LogFile.cpp > CMakeFiles/webserver_base.dir/LogFile.cpp.i

src/base/CMakeFiles/webserver_base.dir/LogFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/LogFile.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/LogFile.cpp -o CMakeFiles/webserver_base.dir/LogFile.cpp.s

src/base/CMakeFiles/webserver_base.dir/Logging.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/Logging.cpp.o: ../src/base/Logging.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/base/CMakeFiles/webserver_base.dir/Logging.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/Logging.cpp.o -c /home/zy/project/WebServer_mine/src/base/Logging.cpp

src/base/CMakeFiles/webserver_base.dir/Logging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/Logging.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/Logging.cpp > CMakeFiles/webserver_base.dir/Logging.cpp.i

src/base/CMakeFiles/webserver_base.dir/Logging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/Logging.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/Logging.cpp -o CMakeFiles/webserver_base.dir/Logging.cpp.s

src/base/CMakeFiles/webserver_base.dir/LogStream.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/LogStream.cpp.o: ../src/base/LogStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/base/CMakeFiles/webserver_base.dir/LogStream.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/LogStream.cpp.o -c /home/zy/project/WebServer_mine/src/base/LogStream.cpp

src/base/CMakeFiles/webserver_base.dir/LogStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/LogStream.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/LogStream.cpp > CMakeFiles/webserver_base.dir/LogStream.cpp.i

src/base/CMakeFiles/webserver_base.dir/LogStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/LogStream.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/LogStream.cpp -o CMakeFiles/webserver_base.dir/LogStream.cpp.s

src/base/CMakeFiles/webserver_base.dir/Thread.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/Thread.cpp.o: ../src/base/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/base/CMakeFiles/webserver_base.dir/Thread.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/Thread.cpp.o -c /home/zy/project/WebServer_mine/src/base/Thread.cpp

src/base/CMakeFiles/webserver_base.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/Thread.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/Thread.cpp > CMakeFiles/webserver_base.dir/Thread.cpp.i

src/base/CMakeFiles/webserver_base.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/Thread.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/Thread.cpp -o CMakeFiles/webserver_base.dir/Thread.cpp.s

src/base/CMakeFiles/webserver_base.dir/CurrentThread.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/CurrentThread.cpp.o: ../src/base/CurrentThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/base/CMakeFiles/webserver_base.dir/CurrentThread.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/CurrentThread.cpp.o -c /home/zy/project/WebServer_mine/src/base/CurrentThread.cpp

src/base/CMakeFiles/webserver_base.dir/CurrentThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/CurrentThread.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/CurrentThread.cpp > CMakeFiles/webserver_base.dir/CurrentThread.cpp.i

src/base/CMakeFiles/webserver_base.dir/CurrentThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/CurrentThread.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/CurrentThread.cpp -o CMakeFiles/webserver_base.dir/CurrentThread.cpp.s

src/base/CMakeFiles/webserver_base.dir/Timestamp.cpp.o: src/base/CMakeFiles/webserver_base.dir/flags.make
src/base/CMakeFiles/webserver_base.dir/Timestamp.cpp.o: ../src/base/Timestamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/base/CMakeFiles/webserver_base.dir/Timestamp.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_base.dir/Timestamp.cpp.o -c /home/zy/project/WebServer_mine/src/base/Timestamp.cpp

src/base/CMakeFiles/webserver_base.dir/Timestamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_base.dir/Timestamp.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/base/Timestamp.cpp > CMakeFiles/webserver_base.dir/Timestamp.cpp.i

src/base/CMakeFiles/webserver_base.dir/Timestamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_base.dir/Timestamp.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/base/Timestamp.cpp -o CMakeFiles/webserver_base.dir/Timestamp.cpp.s

# Object files for target webserver_base
webserver_base_OBJECTS = \
"CMakeFiles/webserver_base.dir/AsyncLogging.cpp.o" \
"CMakeFiles/webserver_base.dir/CountDownLatch.cpp.o" \
"CMakeFiles/webserver_base.dir/FileUtil.cpp.o" \
"CMakeFiles/webserver_base.dir/LogFile.cpp.o" \
"CMakeFiles/webserver_base.dir/Logging.cpp.o" \
"CMakeFiles/webserver_base.dir/LogStream.cpp.o" \
"CMakeFiles/webserver_base.dir/Thread.cpp.o" \
"CMakeFiles/webserver_base.dir/CurrentThread.cpp.o" \
"CMakeFiles/webserver_base.dir/Timestamp.cpp.o"

# External object files for target webserver_base
webserver_base_EXTERNAL_OBJECTS =

lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/AsyncLogging.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/CountDownLatch.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/FileUtil.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/LogFile.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/Logging.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/LogStream.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/Thread.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/CurrentThread.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/Timestamp.cpp.o
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/build.make
lib/libwebserver_base.a: src/base/CMakeFiles/webserver_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library ../../lib/libwebserver_base.a"
	cd /home/zy/project/WebServer_mine/build/src/base && $(CMAKE_COMMAND) -P CMakeFiles/webserver_base.dir/cmake_clean_target.cmake
	cd /home/zy/project/WebServer_mine/build/src/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webserver_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/base/CMakeFiles/webserver_base.dir/build: lib/libwebserver_base.a

.PHONY : src/base/CMakeFiles/webserver_base.dir/build

src/base/CMakeFiles/webserver_base.dir/clean:
	cd /home/zy/project/WebServer_mine/build/src/base && $(CMAKE_COMMAND) -P CMakeFiles/webserver_base.dir/cmake_clean.cmake
.PHONY : src/base/CMakeFiles/webserver_base.dir/clean

src/base/CMakeFiles/webserver_base.dir/depend:
	cd /home/zy/project/WebServer_mine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zy/project/WebServer_mine /home/zy/project/WebServer_mine/src/base /home/zy/project/WebServer_mine/build /home/zy/project/WebServer_mine/build/src/base /home/zy/project/WebServer_mine/build/src/base/CMakeFiles/webserver_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/base/CMakeFiles/webserver_base.dir/depend

