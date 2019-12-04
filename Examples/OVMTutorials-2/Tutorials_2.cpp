/*---------------------------------------------------------------------------------------------------------------------
* This tutorial is written by Chuhua Xian                                                                             *
* Email: chuhuaxian@gmail.com                                                                                         *
* $Date: 2012-08-05. $                                                                                                *
* This tutorial shows:                                                                                                *
* 1) How to add and remove properties                                                                                 *
* 2) How to set and get the value of a property                                                                       *
*--------------------------------------------------------------------------------------------------------------------*/ 

#include <iostream>
#include <vector>

#include <OVM/OVMCore/IO/MeshIO.h>
#include <OVM/OVMCore/Mesh/THMesh_ArrayKernelT.h>

typedef OVM::THMesh_ArrayKernelT<> Mesh;

int main()
{
	std::string file_name;
	std::string output_file;
	std::cout << "Please enter an input file name: ";
	std::cin >> file_name;
	std::cout << "Please enter an output file name: ";
	std::cin >> output_file;

	Mesh mesh;
	if (!OVM::IO::read_mesh(mesh, file_name))
	{
		std::cerr << "Cannot open the file!" << std::endl;
		return 1;
	}

	//--- define a vertex property and add to the vertices of the mesh ---//
	OVM::VPropHandleT<Mesh::Point> v_property;

	//--- check if the property has been added to the mesh ---//
	if (!mesh.get_property_handle(v_property, "v_property"))
	{
		mesh.add_property(v_property, "v_property");
	}

	int valence;

	for (Mesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++ v_it)
	{
		valence = 0;
		//--- access the property and set the value ---//
		mesh.property(v_property, mesh.handle(*v_it)) = Mesh::Point(0, 0, 0);
		for (Mesh::VertexVertexIter vv_it = mesh.vertex_vertex_iter(v_it); vv_it; ++ vv_it)
		{			
			mesh.property(v_property, mesh.handle(*v_it)) += mesh.point(vv_it.handle());
			++ valence;
		}

		mesh.property(v_property, mesh.handle(*v_it)) /= valence;
	}

	for (Mesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++ v_it)
	{
		if (!mesh.is_boundary(v_it))
		{
			mesh.set_point(v_it, mesh.property(v_property, mesh.handle(*v_it)));
		}
	}

	//--- remove the property ---//
	mesh.remove_property(v_property);

	if (!OVM::IO::write_mesh(mesh, output_file))
	{
		std::cerr << "Error: cannot write mesh to " << output_file << std::endl;
		return 1;
	}

	

	return 0;
}