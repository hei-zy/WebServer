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
include src/net/CMakeFiles/webserver_net.dir/depend.make

# Include the progress variables for this target.
include src/net/CMakeFiles/webserver_net.dir/progress.make

# Include the compile flags for this target's objects.
include src/net/CMakeFiles/webserver_net.dir/flags.make

src/net/CMakeFiles/webserver_net.dir/Acceptor.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/Acceptor.cpp.o: ../src/net/Acceptor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/net/CMakeFiles/webserver_net.dir/Acceptor.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/Acceptor.cpp.o -c /home/zy/project/WebServer_mine/src/net/Acceptor.cpp

src/net/CMakeFiles/webserver_net.dir/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/Acceptor.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/Acceptor.cpp > CMakeFiles/webserver_net.dir/Acceptor.cpp.i

src/net/CMakeFiles/webserver_net.dir/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/Acceptor.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/Acceptor.cpp -o CMakeFiles/webserver_net.dir/Acceptor.cpp.s

src/net/CMakeFiles/webserver_net.dir/Buffer.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/Buffer.cpp.o: ../src/net/Buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/net/CMakeFiles/webserver_net.dir/Buffer.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/Buffer.cpp.o -c /home/zy/project/WebServer_mine/src/net/Buffer.cpp

src/net/CMakeFiles/webserver_net.dir/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/Buffer.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/Buffer.cpp > CMakeFiles/webserver_net.dir/Buffer.cpp.i

src/net/CMakeFiles/webserver_net.dir/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/Buffer.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/Buffer.cpp -o CMakeFiles/webserver_net.dir/Buffer.cpp.s

src/net/CMakeFiles/webserver_net.dir/Channel.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/Channel.cpp.o: ../src/net/Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/net/CMakeFiles/webserver_net.dir/Channel.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/Channel.cpp.o -c /home/zy/project/WebServer_mine/src/net/Channel.cpp

src/net/CMakeFiles/webserver_net.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/Channel.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/Channel.cpp > CMakeFiles/webserver_net.dir/Channel.cpp.i

src/net/CMakeFiles/webserver_net.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/Channel.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/Channel.cpp -o CMakeFiles/webserver_net.dir/Channel.cpp.s

src/net/CMakeFiles/webserver_net.dir/EventLoop.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/EventLoop.cpp.o: ../src/net/EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/net/CMakeFiles/webserver_net.dir/EventLoop.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/EventLoop.cpp.o -c /home/zy/project/WebServer_mine/src/net/EventLoop.cpp

src/net/CMakeFiles/webserver_net.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/EventLoop.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/EventLoop.cpp > CMakeFiles/webserver_net.dir/EventLoop.cpp.i

src/net/CMakeFiles/webserver_net.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/EventLoop.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/EventLoop.cpp -o CMakeFiles/webserver_net.dir/EventLoop.cpp.s

src/net/CMakeFiles/webserver_net.dir/EventLoopThread.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/EventLoopThread.cpp.o: ../src/net/EventLoopThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/net/CMakeFiles/webserver_net.dir/EventLoopThread.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/EventLoopThread.cpp.o -c /home/zy/project/WebServer_mine/src/net/EventLoopThread.cpp

src/net/CMakeFiles/webserver_net.dir/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/EventLoopThread.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/EventLoopThread.cpp > CMakeFiles/webserver_net.dir/EventLoopThread.cpp.i

src/net/CMakeFiles/webserver_net.dir/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/EventLoopThread.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/EventLoopThread.cpp -o CMakeFiles/webserver_net.dir/EventLoopThread.cpp.s

src/net/CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.o: ../src/net/EventLoopThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/net/CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.o -c /home/zy/project/WebServer_mine/src/net/EventLoopThreadPool.cpp

src/net/CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/EventLoopThreadPool.cpp > CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.i

src/net/CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/EventLoopThreadPool.cpp -o CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.s

src/net/CMakeFiles/webserver_net.dir/InetAddress.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/InetAddress.cpp.o: ../src/net/InetAddress.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/net/CMakeFiles/webserver_net.dir/InetAddress.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/InetAddress.cpp.o -c /home/zy/project/WebServer_mine/src/net/InetAddress.cpp

src/net/CMakeFiles/webserver_net.dir/InetAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/InetAddress.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/InetAddress.cpp > CMakeFiles/webserver_net.dir/InetAddress.cpp.i

src/net/CMakeFiles/webserver_net.dir/InetAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/InetAddress.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/InetAddress.cpp -o CMakeFiles/webserver_net.dir/InetAddress.cpp.s

src/net/CMakeFiles/webserver_net.dir/Poller.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/Poller.cpp.o: ../src/net/Poller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/net/CMakeFiles/webserver_net.dir/Poller.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/Poller.cpp.o -c /home/zy/project/WebServer_mine/src/net/Poller.cpp

src/net/CMakeFiles/webserver_net.dir/Poller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/Poller.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/Poller.cpp > CMakeFiles/webserver_net.dir/Poller.cpp.i

src/net/CMakeFiles/webserver_net.dir/Poller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/Poller.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/Poller.cpp -o CMakeFiles/webserver_net.dir/Poller.cpp.s

src/net/CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.o: ../src/net/poller/DefaultPoller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/net/CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.o -c /home/zy/project/WebServer_mine/src/net/poller/DefaultPoller.cpp

src/net/CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/poller/DefaultPoller.cpp > CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.i

src/net/CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/poller/DefaultPoller.cpp -o CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.s

src/net/CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.o: ../src/net/poller/EPollPoller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/net/CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.o -c /home/zy/project/WebServer_mine/src/net/poller/EPollPoller.cpp

src/net/CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/poller/EPollPoller.cpp > CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.i

src/net/CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/poller/EPollPoller.cpp -o CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.s

src/net/CMakeFiles/webserver_net.dir/Socket.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/Socket.cpp.o: ../src/net/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/net/CMakeFiles/webserver_net.dir/Socket.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/Socket.cpp.o -c /home/zy/project/WebServer_mine/src/net/Socket.cpp

src/net/CMakeFiles/webserver_net.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/Socket.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/Socket.cpp > CMakeFiles/webserver_net.dir/Socket.cpp.i

src/net/CMakeFiles/webserver_net.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/Socket.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/Socket.cpp -o CMakeFiles/webserver_net.dir/Socket.cpp.s

src/net/CMakeFiles/webserver_net.dir/TcpConnection.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/TcpConnection.cpp.o: ../src/net/TcpConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/net/CMakeFiles/webserver_net.dir/TcpConnection.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/TcpConnection.cpp.o -c /home/zy/project/WebServer_mine/src/net/TcpConnection.cpp

src/net/CMakeFiles/webserver_net.dir/TcpConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/TcpConnection.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/TcpConnection.cpp > CMakeFiles/webserver_net.dir/TcpConnection.cpp.i

src/net/CMakeFiles/webserver_net.dir/TcpConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/TcpConnection.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/TcpConnection.cpp -o CMakeFiles/webserver_net.dir/TcpConnection.cpp.s

src/net/CMakeFiles/webserver_net.dir/TcpServer.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/TcpServer.cpp.o: ../src/net/TcpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object src/net/CMakeFiles/webserver_net.dir/TcpServer.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/TcpServer.cpp.o -c /home/zy/project/WebServer_mine/src/net/TcpServer.cpp

src/net/CMakeFiles/webserver_net.dir/TcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/TcpServer.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/TcpServer.cpp > CMakeFiles/webserver_net.dir/TcpServer.cpp.i

src/net/CMakeFiles/webserver_net.dir/TcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/TcpServer.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/TcpServer.cpp -o CMakeFiles/webserver_net.dir/TcpServer.cpp.s

src/net/CMakeFiles/webserver_net.dir/Timer.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/Timer.cpp.o: ../src/net/Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object src/net/CMakeFiles/webserver_net.dir/Timer.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/Timer.cpp.o -c /home/zy/project/WebServer_mine/src/net/Timer.cpp

src/net/CMakeFiles/webserver_net.dir/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/Timer.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/Timer.cpp > CMakeFiles/webserver_net.dir/Timer.cpp.i

src/net/CMakeFiles/webserver_net.dir/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/Timer.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/Timer.cpp -o CMakeFiles/webserver_net.dir/Timer.cpp.s

src/net/CMakeFiles/webserver_net.dir/TimerQueue.cpp.o: src/net/CMakeFiles/webserver_net.dir/flags.make
src/net/CMakeFiles/webserver_net.dir/TimerQueue.cpp.o: ../src/net/TimerQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object src/net/CMakeFiles/webserver_net.dir/TimerQueue.cpp.o"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver_net.dir/TimerQueue.cpp.o -c /home/zy/project/WebServer_mine/src/net/TimerQueue.cpp

src/net/CMakeFiles/webserver_net.dir/TimerQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver_net.dir/TimerQueue.cpp.i"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zy/project/WebServer_mine/src/net/TimerQueue.cpp > CMakeFiles/webserver_net.dir/TimerQueue.cpp.i

src/net/CMakeFiles/webserver_net.dir/TimerQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver_net.dir/TimerQueue.cpp.s"
	cd /home/zy/project/WebServer_mine/build/src/net && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zy/project/WebServer_mine/src/net/TimerQueue.cpp -o CMakeFiles/webserver_net.dir/TimerQueue.cpp.s

# Object files for target webserver_net
webserver_net_OBJECTS = \
"CMakeFiles/webserver_net.dir/Acceptor.cpp.o" \
"CMakeFiles/webserver_net.dir/Buffer.cpp.o" \
"CMakeFiles/webserver_net.dir/Channel.cpp.o" \
"CMakeFiles/webserver_net.dir/EventLoop.cpp.o" \
"CMakeFiles/webserver_net.dir/EventLoopThread.cpp.o" \
"CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.o" \
"CMakeFiles/webserver_net.dir/InetAddress.cpp.o" \
"CMakeFiles/webserver_net.dir/Poller.cpp.o" \
"CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.o" \
"CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.o" \
"CMakeFiles/webserver_net.dir/Socket.cpp.o" \
"CMakeFiles/webserver_net.dir/TcpConnection.cpp.o" \
"CMakeFiles/webserver_net.dir/TcpServer.cpp.o" \
"CMakeFiles/webserver_net.dir/Timer.cpp.o" \
"CMakeFiles/webserver_net.dir/TimerQueue.cpp.o"

# External object files for target webserver_net
webserver_net_EXTERNAL_OBJECTS =

lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/Acceptor.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/Buffer.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/Channel.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/EventLoop.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/EventLoopThread.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/EventLoopThreadPool.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/InetAddress.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/Poller.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/poller/DefaultPoller.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/poller/EPollPoller.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/Socket.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/TcpConnection.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/TcpServer.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/Timer.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/TimerQueue.cpp.o
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/build.make
lib/libwebserver_net.a: src/net/CMakeFiles/webserver_net.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zy/project/WebServer_mine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX static library ../../lib/libwebserver_net.a"
	cd /home/zy/project/WebServer_mine/build/src/net && $(CMAKE_COMMAND) -P CMakeFiles/webserver_net.dir/cmake_clean_target.cmake
	cd /home/zy/project/WebServer_mine/build/src/net && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webserver_net.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/net/CMakeFiles/webserver_net.dir/build: lib/libwebserver_net.a

.PHONY : src/net/CMakeFiles/webserver_net.dir/build

src/net/CMakeFiles/webserver_net.dir/clean:
	cd /home/zy/project/WebServer_mine/build/src/net && $(CMAKE_COMMAND) -P CMakeFiles/webserver_net.dir/cmake_clean.cmake
.PHONY : src/net/CMakeFiles/webserver_net.dir/clean

src/net/CMakeFiles/webserver_net.dir/depend:
	cd /home/zy/project/WebServer_mine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zy/project/WebServer_mine /home/zy/project/WebServer_mine/src/net /home/zy/project/WebServer_mine/build /home/zy/project/WebServer_mine/build/src/net /home/zy/project/WebServer_mine/build/src/net/CMakeFiles/webserver_net.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/net/CMakeFiles/webserver_net.dir/depend

