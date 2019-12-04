/*---------------------------------------------------------------------------------------------------------------------
* This tutorial is written by Chuhua Xian                                                                             *
* Email: chuhuaxian@gmail.com                                                                                         *
* $Date: 2012-08-05. $                                                                                                *
* This tutorial shows:                                                                                                *
* 1) How to declare your volumetric mesh type                                                                         *
* 2) How to add vertices and build a tetrahedral mesh and hexahedral mesh                                             *
* 3) How to write a mesh using the IO operations.                                                                     *
*--------------------------------------------------------------------------------------------------------------------*/ 
#include <iostream>
#include <vector>

#include <OVM/OVMCore/Mesh/Traits.h>
#include <OVM/OVMCore/IO/MeshIO.h>
#include <OVM/OVMCore/Mesh/THMesh_ArrayKernelT.h>

typedef OVM::THMesh_ArrayKernelT<> Mesh;

int main()
{

	//--- build a tetrahedral mesh ---//
	Mesh tet_mesh; 
	tet_mesh.set_mesh_type(OVM::THKernel::TETRAHEDRON);


	Mesh::VertexHandle vh[8];   
	vh[0] = tet_mesh.add_vertex(Mesh::Point(0, 0, 0));   
	vh[1] = tet_mesh.add_vertex(Mesh::Point(1, 0, 0));   
	vh[2] = tet_mesh.add_vertex(Mesh::Point(1, 1, 0));   
	vh[3] = tet_mesh.add_vertex(Mesh::Point(0, 1, 0));   
	vh[4] = tet_mesh.add_vertex(Mesh::Point(0, 0, 1));   
	vh[5] = tet_mesh.add_vertex(Mesh::Point(1, 0, 1));   
	vh[6] = tet_mesh.add_vertex(Mesh::Point(1, 1, 1));   
	vh[7] = tet_mesh.add_vertex(Mesh::Point(0, 1, 1));

	std::vector<Mesh::VertexHandle> hedron_vertices;
	hedron_vertices.push_back(vh[0]);
	hedron_vertices.push_back(vh[3]);
	hedron_vertices.push_back(vh[4]);
	hedron_vertices.push_back(vh[1]);

	tet_mesh.add_hedron(hedron_vertices);

	hedron_vertices.clear();
	hedron_vertices.push_back(vh[1]);
	hedron_vertices.push_back(vh[3]);
	hedron_vertices.push_back(vh[4]);
	hedron_vertices.push_back(vh[6]);

	tet_mesh.add_hedron(hedron_vertices);
	
	hedron_vertices.clear();
	hedron_vertices.push_back(vh[2]);
	hedron_vertices.push_back(vh[3]);
	hedron_vertices.push_back(vh[1]);
	hedron_vertices.push_back(vh[6]);

	tet_mesh.add_hedron(hedron_vertices);
	
	hedron_vertices.clear();
	hedron_vertices.push_back(vh[5]);
	hedron_vertices.push_back(vh[6]);
	hedron_vertices.push_back(vh[1]);
	hedron_vertices.push_back(vh[4]);

	tet_mesh.add_hedron(hedron_vertices);

	hedron_vertices.clear();
	hedron_vertices.push_back(vh[7]);
	hedron_vertices.push_back(vh[6]);
	hedron_vertices.push_back(vh[4]);
	hedron_vertices.push_back(vh[3]);

	tet_mesh.add_hedron(hedron_vertices);

	std::cout << "Vertices:" << tet_mesh.n_vertices() << std::endl;
	std::cout << "Tetrahedrons:" << tet_mesh.n_hedrons() << std::endl;

	OVM::IO::write_mesh(tet_mesh, "tet_mesh.mesh");

	//--- build a hexahedral mesh ---//
	Mesh hex_mesh;
	hex_mesh.set_mesh_type(OVM::THKernel::HEXAHEDRON);

	vh[0] = hex_mesh.add_vertex(Mesh::Point(0, 0, 0));   
	vh[1] = hex_mesh.add_vertex(Mesh::Point(1, 0, 0));   
	vh[2] = hex_mesh.add_vertex(Mesh::Point(1, 1, 0));   
	vh[3] = hex_mesh.add_vertex(Mesh::Point(0, 1, 0));   
	vh[4] = hex_mesh.add_vertex(Mesh::Point(0, 0, 1));   
	vh[5] = hex_mesh.add_vertex(Mesh::Point(1, 0, 1));   
	vh[6] = hex_mesh.add_vertex(Mesh::Point(1, 1, 1));   
	vh[7] = hex_mesh.add_vertex(Mesh::Point(0, 1, 1));
	hedron_vertices.clear();

	hedron_vertices.push_back(vh[0]);
	hedron_vertices.push_back(vh[1]);
	hedron_vertices.push_back(vh[2]);
	hedron_vertices.push_back(vh[3]);
	hedron_vertices.push_back(vh[4]);
	hedron_vertices.push_back(vh[5]);
	hedron_vertices.push_back(vh[6]);
	hedron_vertices.push_back(vh[7]);

	hex_mesh.add_hedron(hedron_vertices);

	OVM::IO::write_mesh(hex_mesh, "hex_mesh.mesh");

	std::cout << "Vertices:" << hex_mesh.n_vertices() << std::endl;
	std::cout << "Hexahedrons:" << hex_mesh.n_hedrons() << std::endl;


	return 0;
}