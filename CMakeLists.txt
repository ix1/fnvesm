cmake_minimum_required(VERSION 2.6)
project(fnvesm)

add_executable(fnvesm main.cpp)

install(TARGETS fnvesm RUNTIME DESTINATION bin)
