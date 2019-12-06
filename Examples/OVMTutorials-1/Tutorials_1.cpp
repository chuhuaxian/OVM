/*---------------------------------------------------------------------------------------------------------------------
* This tutorial is written by Chuhua Xian                                                                             *
* Email: chuhuaxian@gmail.com                                                                                         *
* $Date: 2012-08-05. $                                                                                                *
* This tutorial shows:                                                                                                *
* 1) How to use the iterators                                                                                         *
* 2) How to use the circulators                                                                                       *
*--------------------------------------------------------------------------------------------------------------------*/ 
#include <iostream>
#include <string>

#include <OVM/OVMCore/IO/MeshIO.h>
#include <OVM/OVMCore/Mesh/THMesh_ArrayKernelT.h>

typedef OVM::THMesh_ArrayKernelT<> Mesh;

int main()
{
	std::string file_name;
	std::cout << "Please enter a file name: ";
	std::cin >> file_name;	

	Mesh mesh;
	if (!OVM::IO::read_mesh(mesh, file_name))
	{
		std::cerr << "Cannot open the file!" << std::endl;
		return 0;
	}

	for (Mesh::HedronIter h_it = mesh.hedrons_begin(); h_it != mesh.hedrons_end(); ++ h_it)
	{
		//--- using the circulator to access the vertices of a hedron ---//
		for (Mesh::HedronVertexIter hv_it = mesh.hedron_vertex_iter(h_it); hv_it; ++ hv_it)
		{
			Mesh::Point v;
			v = mesh.point(hv_it.handle());
			std::cout << "Coordinate: " << v[0] << ", " << v[1] << ", " << v[2] << std::endl;			
		}
	}

	for (Mesh::HalfEdgeIter he_it = mesh.half_edges_begin(); he_it != mesh.half_edges_end(); ++ he_it)
	{
		//--- access the polyhedrons attached to the half edge ---//
		for (Mesh::HalfEdgeHedronIter heh_it = mesh.half_edge_hedron_iter(he_it); heh_it; ++ heh_it)
		{
			//.......
		}
	}

	return 0;
}