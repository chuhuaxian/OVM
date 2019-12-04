/*---------------------------------------------------------------------------------------------------------------------
* This tutorial is written by Chuhua Xian                                                                             *
* Email: chuhuaxian@gmail.com                                                                                         *
* $Date: 2012-08-05. $                                                                                                *
* This tutorial shows:                                                                                                *
* 1) How to delete element of a mesh                                                                                  *
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

	Mesh::HedronHandle hh[5];

	std::vector<Mesh::VertexHandle> hedron_vertices;
	hedron_vertices.push_back(vh[0]);
	hedron_vertices.push_back(vh[3]);
	hedron_vertices.push_back(vh[4]);
	hedron_vertices.push_back(vh[1]);

	hh[0] = tet_mesh.add_hedron(hedron_vertices);

	hedron_vertices.clear();
	hedron_vertices.push_back(vh[1]);
	hedron_vertices.push_back(vh[3]);
	hedron_vertices.push_back(vh[4]);
	hedron_vertices.push_back(vh[6]);

	hh[1] = tet_mesh.add_hedron(hedron_vertices);

	hedron_vertices.clear();
	hedron_vertices.push_back(vh[2]);
	hedron_vertices.push_back(vh[3]);
	hedron_vertices.push_back(vh[1]);
	hedron_vertices.push_back(vh[6]);

	hh[2] = tet_mesh.add_hedron(hedron_vertices);

	hedron_vertices.clear();
	hedron_vertices.push_back(vh[5]);
	hedron_vertices.push_back(vh[6]);
	hedron_vertices.push_back(vh[1]);
	hedron_vertices.push_back(vh[4]);

	hh[3] = tet_mesh.add_hedron(hedron_vertices);

	hedron_vertices.clear();
	hedron_vertices.push_back(vh[7]);
	hedron_vertices.push_back(vh[6]);
	hedron_vertices.push_back(vh[4]);
	hedron_vertices.push_back(vh[3]);

	hh[4] = tet_mesh.add_hedron(hedron_vertices);;

	std::cout << "Vertices:" << tet_mesh.n_vertices() << std::endl;
	std::cout << "Tetrahedrons:" << tet_mesh.n_hedrons() << std::endl;

	OVM::IO::write_mesh(tet_mesh, "tet_mesh.mesh");

	//--- delete tetrahedrons ---//
	tet_mesh.delete_hedron(hh[4]);
	tet_mesh.delete_hedron(hh[3]);
	tet_mesh.delete_hedron(hh[2]);
	//--- delete all tetrahedrons that are all marked as deleted from memory, now release the memory ---//
	tet_mesh.garbage_collection();

	if (!OVM::IO::write_mesh(tet_mesh, "tet_mesh_delete.mesh"))
	{
		std::cerr << "Cannot writ the mesh!" << std::endl;
		return 1;
	}
	
	return 0;
}