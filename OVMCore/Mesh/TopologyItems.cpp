/*---------------------------------------------------------------------------------------------------------------------
*                 ----                  __                        __    __                      __    *               *
*            --           --              \                      /     |  \                    /  |   *               *
*         -                   -            \                    /      |   \                  /   |   *               *
*      -                         -          \                  /       |    \                /    |   *               *
*    -                             -         \                /        |     \              /     |   *               *
*   |                               |         \              /         |      \            /      |   *               *
*   |                               |          \            /          |       \          /       |   *               *
*   |                               |           \          /           |        \        /        |   *               *
*    -                             -             \        /            |         \      /         |   *               *
*      -                         -                \      /             |          \    /          |   *               *
*         -                   -                    \    /              |           \__/           |   *               *     
*           --            --                        \__/              _|                          |__ *               * 
*                 ----                                                                                *               *
*----------------------------------------------------------------------------------------------------------------------
* OpenVolumetricMesh (OVM) library, Copyright (C) 2010-2020, Chuhua Xian                                              *
* All rights reserved                                                                                                 *
*                                                                                                                     *
* Code author: Chuhua Xian                                                                                            *
* Version: 1.0                                                                                                        *
* License                                                                                                             *  
*                                                                                                                     *
*    This file is part of OpenVolumericMesh (OVM).                                                                    *
*                                                                                                                     *
*    OpenVolumericMesh (OVM)is free software: you can redistribute it and/or modify                                   *
*    it under the terms of the GNU Lesser General Public License as                                                   *
*    published by the Free Software Foundation, either version 3 of                                                   *
*    the License, or (at your option) any later version.                                                              *
*                                                                                                                     *
*   OpenVolumericMesh distributed in the hope that it will be useful,                                                 *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of                                                    *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                                     * 
*   GNU Lesser General Public License for more details.                                                               *
*   This project is created by Chuhua Xian                                                                            *
*   Developers : Chuhua Xian,   chuhuaxian@gmail.com                                                                  *
*                                                                                                                     *
/--------------------------------------------------------------------------------------------------------------------*/
#include <OVM/OVMCore/Mesh/TopologyItems.h>

namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	///** the implementation of the edges and faces operations */



	///// constant arrays	

	//const int TNEXT[4][4] = 
	//{
	//	-1,  2,  3,  1,
	//	3, -1,  0,  2,
	//	1,  3, -1,  0,
	//	2,  0,  1,  -1
	//};

	//const int TPREV[4][4] = 
	//{
	//	-1,  3,  1,  2,
	//	2, -1,  3,  0,
	//	3,  0, -1,  1,
	//	1,  2,  0, -1
	//};

	//const int THEPosition[4][4] = 
	//{
	//	-1,  0,  1,  2,
	//	0, -1,  1,  2,
	//	0,  1, -1,  2,
	//	0,  1,  2,  -1
	//};

	//const int HMate[6][8] = 
	//{
	//	-1, -1,  3,  4, -1, -1,  2,  1,
	//	-1, -1, -1, -1,  5,  2,  0,  4,
	//	-1,  3,  0, -1, -1,  5,  1, -1,
	//	4,  5,  2,  0, -1, -1, -1, -1,
	//	5, -1, -1,  3,  1, -1, -1,  0,
	//	3,  2, -1, -1,  4,  1, -1, -1
	//};

	//const int HHEPosition[6][8] = 
	//{
	//	-1, -1,  0,  1, -1, -1,  3,  2,
	//	-1, -1, -1, -1,  0,  1,  2,  3,
	//	-1,  0,  1, -1, -1,  3,  2, -1,
	//	0,  3,  2,  1, -1, -1, -1, -1,
	//	0, -1, -1,  3,  1, -1, -1,  2,
	//	0,  1, -1, -1,  3,  2, -1, -1
	//};

	//const int HNEXT[6][8] =
	//{
	//	-1, -1,  3,  7, -1, -1,  2,  6,
	//	-1, -1, -1, -1,  5,  6,  7,  4,
	//	-1,  2,  6, -1, -1,  1,  5, -1,
	//	3,  0,  1,  2, -1, -1, -1, -1,
	//	4, -1, -1,  0,  7, -1, -1,  3,
	//	1,  5, -1, -1,  0,  4, -1, -1
	//};

	//const int HD[3] = {0, 12, 24};
	//const int FD[3] = {0, 3, 4};
	//const int RD[3] = {0, 2, 3};
	//const int LD[3] = {0, 4, 6};


	//const int * mate[3] = {0, &TPREV[0][0], &HMate[0][0]};
	//const int * pos[3]  = {0, &THEPosition[0][0], &HHEPosition[0][0]};




	////-----------------------------------------------------------------------------------------------------------------


	////-----------------------functions for edge operations------------------------------// 

	///** retrieve hedron handle which half edge belongs to
	//*   \param _he the half edge entity
	//*   \param _mt 1 for tetrahedron, 2 for hexahedron
	//*   \return the hedron handle
	//*/
	//HedronHandle Topology::hedron_handle(const HalfEdge & _he, int _mt)
	//{
	//	//return HedronHandle(_he.heh_.idx() / HD[_mt]);
	//}

	///** retrieve half face handle which half edge belongs to
	//*   \param _he the half edge entity
	//*   \param _mt 1 for tetrahedron, 2 for hexahedron
	//*   \return the hedron handle
	//*/
	//HalfFaceHandle Topology::half_face_handle(const HalfEdge & _he, int _mt)
	//{
	//	//return HalfFaceHandle(_he.heh_.idx() / FD[_mt]);
	//}

	///** retrieve previous half edge handle
	//*   \param _he the half edge entity
	//*   \param _mt 1 for tetrahedron, 2 for hexahedron
	//*   \return the next half edge handle
	//*/
	//HalfEdgeHandle prev_half_edge_handle(const HalfEdge & _he, int _mt)
	//{
	//	//return HalfEdgeHandle(_he.heh_ / FD[_mt] * FD[_mt] + (_he.heh_ + RD[_mt]) % FD[_mt]);
	//}

	///** retrieve the next half edge handle
	//*   \param _he the half edge entity
	//*   \param _mt 1 for tetrahedron, 2 for hexahedron
	//*   \return the next half edge handle
	//*/
	//HalfEdgeHandle next_half_edge_handle(const HalfEdge & _he, int _mt)
	//{
	//	//return HalfEdgeHandle(_he.heh_ / FD[_mt] * FD[_mt] + (_he.heh_ + 1) % FD[_mt]);
	//}

	///** retrieve the mate  half edge handle
	//*   \param _he the half edge entity
	//*   \param _mt 1 for tetrahedron, 2 for hexahedron
	//*   \return the mate half edge handle
	//*/
	//HalfEdgeHandle Topology::mate_half_edge_handle(const HalfEdge & _he, int _mt)
	//{		
	//}

	///** retrieve the hedron handle of the half face
	//*   \param _hf the half face
	//*   \param 1 for tetrahedron, 2 for hexahedron
	//*   \return the hedron handle
	//*/
	//HedronHandle   Topology::hedron_handle(const HalfFace & _hf, int _mt)
	//{
	//	//return HedronHandle(_hf.hfh_.idx() / LD[_mt]);
	//}

	///** retrieve the opposite half face handle
	//*   \param _hf the half face entity
	//*   \return the opposite half face handle
	//*/
	//HalfFaceHandle Topology::opp_half_face_handle(const HalfFace & _hf)
	//{
	//	return _hf.opp_hfh_;
	//}

	///** retrieve the opposite half face handle 
	//*   \param _hf the half faace entity
	//*   \param 1 for tetrahedron, 2 for hexahedron
	//*   \return the half face handle
	//*/
	//HalfFaceHandle Topology::prev_half_face_handle(const HalfFace & _hf, int _mt)
	//{

	//}

	///** retrieve the next half face handle 
	//*   \param _hf the half face entity
	//*   \param 1 for tetrahedron, 2 for hexahedron
	//*   \return the next half face handle
	//*/
	//HalfFaceHandle Topology::next_half_face_handle(const HalfFace & _hf, int _mt)
	//{

	//}

	///** retrieve the first half edge handle of the half face 
	//*   \param _hf the half face entity
	//*   \param 1 for tetrahedron, 2 for hexahedron
	//*   \return the first edge handle of the  half face
	//*/
	//HalfEdgeHandle Topology::first_half_edge_handle(const HalfFace & _hf, int _mt)
	//{

	//}


	////-----------------------------------------------------------------------------------------------------------------

	////-------------------------- functions for hedron operations ----------------------------//

	///** retrieve the first half face handle of the hedron 
	//*   \param _h the hedron entity
	//*   \param 1 for tetrahedron, 2 for hexahedron
	//*   \return the first half face handle of the hedron
	//*/
	//HalfFaceHandle Topology::first_half_face_handle(const Hedron & _h, int _mt)
	//{

	//}

	///** retrieve the first vertex handle of the hedron 
	//*   \param _h the hedron entity
	//*   \param 1 for tetrahedron, 2 for hexahedron
	//*   \return the first vertex handle of the hedron
	//*/
	//VertexHandle Topology::first_vertex_handle(const Hedron & _h, int _mt)
	//{

	//}

//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM
//---------------------------------------------------------------------------------------------------------------------