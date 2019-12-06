CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(OVMTutorials)


INCLUDE_DIRECTORIES(../../)

link_directories()


ADD_EXECUTABLE(OVMTutorials_0 OVMTutorials-0/Tutorials_0.cpp)
ADD_EXECUTABLE(OVMTutorials_1 OVMTutorials-1/Tutorials_1.cpp)
ADD_EXECUTABLE(OVMTutorials_2 OVMTutorials-2/Tutorials_2.cpp)
ADD_EXECUTABLE(OVMTutorials_3 OVMTutorials-3/Tutorials_3.cpp)
ADD_EXECUTABLE(OVMTutorials_4 OVMTutorials-4/Tutorials_4.cpp)

if (WIN32)
	target_link_libraries(OVMTutorials_0 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.lib)
	target_link_libraries(OVMTutorials_1 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.lib)
	target_link_libraries(OVMTutorials_2 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.lib)
	target_link_libraries(OVMTutorials_3 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.lib)
	target_link_libraries(OVMTutorials_4 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.lib)
elseif (UNIX)
	target_link_libraries(OVMTutorials_0 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.a)
	target_link_libraries(OVMTutorials_1 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.a)
	target_link_libraries(OVMTutorials_2 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.a)
	target_link_libraries(OVMTutorials_3 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.a)
	target_link_libraries(OVMTutorials_4 ${CMAKE_CURRENT_SOURCE_DIR}/../libs/OVMCore.a)
endif()

