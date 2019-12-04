#Author: Chuhua Xian
#Created: 2019.11.04


CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(OVMTutorials)

set (directories 
  OVMTutorials_0
  OVMTutorials_1
  OVMTutorials_2
  OVMTutorials_3
  OVMTutorials_4
)

INCLUDE_DIRECTORIES(../../)

ADD_EXECUTABLE(Toturials_0 Tutorials_0.cpp)
ADD_EXECUTABLE(Toturials_1 Tutorials_1.cpp)
ADD_EXECUTABLE(Toturials_2 Tutorials_2.cpp)
ADD_EXECUTABLE(Toturials_3 Tutorials_3.cpp)
ADD_EXECUTABLE(Toturials_4 Tutorials_4.cpp)


