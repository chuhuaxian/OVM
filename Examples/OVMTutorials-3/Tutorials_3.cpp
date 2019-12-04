/*---------------------------------------------------------------------------------------------------------------------
* This tutorial is written by Chuhua Xian                                                                             *
* Email: chuhuaxian@gmail.com                                                                                         *
* $Date: 2012-08-05. $                                                                                                *
* This tutorial shows:                                                                                                *
* 1) How to change the data types of a mesh                                                                           *
*--------------------------------------------------------------------------------------------------------------------*/ 
#include <iostream>
#include <string>

#include <OVM/OVMCore/IO/MeshIO.h>
#include <OVM/OVMCore/Mesh/THMesh_ArrayKernelT.h>


typedef struct MyTrait : public OVM::DefaultTraits
{
	//--- let point and normal be a vector of doubles ---//
	typedef OVM::Vec3d Point;
	typedef OVM::Vec3d Normal;

} MyTrait;

typedef OVM::THMesh_ArrayKernelT<MyTrait> Mesh;

int main()
{
	std::string file_name;
	std::cout << "Please enter a file name:";
	std::cin >> file_name;
	
	Mesh mesh;

	if (!OVM::IO::read_mesh(mesh, file_name))
	{
		std::cout << "Cannot open the file: " << file_name << std::endl;
		return 1;
	}

	if (typeid(OVM::vector_traits<MyTrait::Point>::value_type) != typeid(double))
	{
		std::cout << "Error! Data type is wrong!" << std::endl;
		return 1;
	}

	if (typeid(OVM::vector_traits<MyTrait::Normal>::value_type) != typeid(double))
	{
		std::cout << "Error! Data type is wrong!" << std::endl;
		return 1;
	}


	return 0;
}