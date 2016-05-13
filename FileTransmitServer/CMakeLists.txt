cmake_minimum_required(VERSION 3.2)
project(FileTransmitServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES main.cpp server/Server.cpp server/Server.h tools/log/Log.cpp tools/log/Log.h server/RequestQueue.cpp server/RequestQueue.h tools/threads/waitObjects/mutex/Mutex.cpp tools/threads/waitObjects/mutex/Mutex.h server/Worker.cpp server/Worker.h tools/threads/Thread.cpp tools/threads/Thread.h tools/threads/waitObjects/conditionalVariable/Signal.cpp tools/threads/waitObjects/conditionalVariable/Signal.h server/AcceptorThread.cpp server/AcceptorThread.h server/FileReceiveWorker.cpp server/FileReceiveWorker.h)
add_executable(FileTransmitServer ${SOURCE_FILES})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(FileTransmitServer Threads::Threads)