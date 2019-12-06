cmake_minimum_required(VERSION 2.8)

project(OVM)


#set(CMAKE_BUILD_TYPE "Debug | Release")

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libs)


include_directories(../)

link_directories()

set(SOURCE_FILE_CORE
	OVMCore/Geometry/OVMVector.h
	OVMCore/IO/IOManager.h
	OVMCore/IO/IOManager.cpp
	OVMCore/IO/MeshIO.h
	OVMCore/IO/Options.h
	OVMCore/Mesh/AttributeKernelT.h
	OVMCore/Mesh/Attributes.h
	OVMCore/Mesh/BaseHandle.h
	OVMCore/Mesh/BaseMesh.h
	OVMCore/Mesh/BaseKernel.h
	OVMCore/Mesh/CirculatorsT.h
	OVMCore/Mesh/Handles.h
	OVMCore/Mesh/Status.h
	OVMCore/Mesh/THKernel.h
	OVMCore/Mesh/THKernel.cpp
	OVMCore/Mesh/THMesh_ArrayKernelT.h
	OVMCore/Mesh/THMeshItems.h
	OVMCore/Mesh/THMeshT.h
	OVMCore/Mesh/THMeshT.cpp
	OVMCore/Mesh/TopologyItems.h
	OVMCore/Mesh/TopologyItems.cpp
	OVMCore/Mesh/TopologyKernel.h
	OVMCore/Mesh/TopologyKernel.cpp
	OVMCore/Mesh/Traits.h
	OVMCore/system/compiler.h
	OVMCore/system/config.h
	OVMCore/Util/BaseProperty.h
	OVMCore/Util/BaseProperty.cpp
	OVMCore/Util/PropertyContainer.h
	OVMCore/Util/PropertyHandle.h
	OVMCore/Util/PropertyT.h
	OVMCore/Util/vector_traits.h 
	)
set(SOURCE_FILE_TOOLS
	OVMTools/Math/OVMMath.h
	OVMTools/Math/OVMMath.cpp
	OVMTools/Util/DualGraph.h
	OVMTools/Util/DualGraph.cpp
	OVMTools/Util/QualityEvaluation.h
	OVMTools/Util/QualityEvaluation.cpp
	OVMTools/Util/SmootherT.h
	OVMTools/Util/SmootherT.cpp
	)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(OVMCore STATIC ${SOURCE_FILE_CORE})
add_library(OVMTools STATIC ${SOURCE_FILE_TOOLS})