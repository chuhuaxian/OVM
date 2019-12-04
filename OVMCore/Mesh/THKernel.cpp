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
#include <OVM/OVMCore/Mesh/THKernel.h>

#include <algorithm>
#include <set>
#include <queue>
#include <iostream>
#include <fstream>

namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	const static size_t FaceCount[2]   = {4, 6};
	const static size_t RR[2]          = {2, 3};
	const static size_t PrevFactor[2]  = {3, 5};
	const static size_t FaceEdge[2]    = {3, 4};
	const static size_t EdgeCount[2]   = {12, 24};
	const static size_t VertexCount[2] = {4, 8};
	const static size_t PreVertex[2]   = {3, 7};
	const static size_t StartVertex[2] = {3, 0}; 

	// --------------------0,  1, 2, 3, 4, 5,  6, 7, 8, 9, 10, 11     ----------//
	const int TMate[12] = {10, 4, 7, 8, 1, 9, 11, 2, 3, 5, 0,  6};

	// -------------------- 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11 ------//
	const int HMate[24] = { 7, 19, 12,  8, 11, 23, 16,  0,  3, 15, 20,  4,
	// --------------------12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 ------//
	                        2, 18, 21,  9,  6, 22, 13,  1, 10, 14, 17,  5};
	const int * Mate[2] = {&TMate[0], &HMate[0]};



	//---------------------------- 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 ------------------// 
	const int TVertexMatrix[12] = {1, 2, 3, 0, 3, 2, 0, 1, 3, 0, 2,  1};

	//----------------------------   0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11 --------// 
	//const int HVertexMatrix[24] = {0,  2,  3,  1,  0,  4,  6,  2,  0,  1,  5,  4,
	////---------------------------- 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 --------//
	//                               1,  3,  7,  5,  2,  6,  7,  3,  4,  5,  7,  6};

	//---------------------------- 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11 --------// 
	const int HVertexMatrix[24] = {0,  3,  2,  1,  0,  4,  7,  3,  0,  1,  5,  4,
	//---------------------------- 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 --------//
		                           1,  2,  6,  5,  3,  7,  6,  2,  4,  5,  6,  7};
	const int * VertexMatrix[2] = {&TVertexMatrix[0], &HVertexMatrix[0]};


	
	//-----------------------------    0, 1, 2, 3 ------------------------------------------//
	const int NTVertexHalfEdge[4]   = {1, 2, 3, 0};
	//-----------------------------    0,   1,  2,  3   ------------------------------------//
	const int NHVertexHalfEdge[24]  = { 3, 20,  1,  2, 
		                               -1, -1, -1, -1,
									   -1, -1, -1, -1,
									   -1, -1, -1, -1,
									   -1, -1, -1, -1,
    //------------------------------   4,  5,  6,  7   ------------------------------------//
		                              21, 22, 23,  0};
	const int * NVertexHalfEdge[2] = {&NTVertexHalfEdge[0], &NHVertexHalfEdge[0]};



	//-------------------------------  0, 1, 2, 3 -----------------------------------------//
	const int PTVertexHalfEdge[4]   = {3, 0, 1, 2};
	//-----------------------------      0,  1,  2,  3   ----------------------------------//
	const int PHVertexHalfEdge[24]  = { 23,  2,  3,  0,  
		                                -1, -1, -1, -1,
										-1, -1, -1, -1,
										-1, -1, -1, -1,
										-1, -1, -1, -1,
		//------------------------------ 4,  5,  6,  7   ------------------------------------//
		                                 1, 20, 21, 22};
	const int * PVertexHalfEdge[2] = {&PTVertexHalfEdge[0], &PHVertexHalfEdge[0]};	
	//-----------------------------------------------------------------------------------------------------------------

	/** retrieve the hedron handle of the face */
	HedronHandle THKernel::hedron_handle(const HalfFace & _hf) const
	{
		return HedronHandle((size_t)handle(_hf) / FaceCount[kernel_type_]);
	}
	HedronHandle THKernel::hedron_handle(const ConstHalfFaceIter & _hf_it) const
	{
		return HedronHandle((size_t)handle(*_hf_it) / FaceCount[kernel_type_]);
	}
	/** retrieve the hedron handle of the face */
	HedronHandle THKernel::hedron_handle(const HalfFaceHandle & _hfh) const
	{
		if (is_valid_handle(_hfh))
		{
			return HedronHandle(_hfh.idx() / FaceCount[kernel_type_]);
		}
		return HedronHandle(-1);
	}
	/** retrieve the hedron handle of the half edge */
	HedronHandle THKernel::hedron_handle(const HalfEdge & _he) const
	{
		return HedronHandle((size_t)handle(_he) / EdgeCount[kernel_type_]);
	}
	/** retrieve the hedron handle of the half edge */
	HedronHandle THKernel::hedron_handle(const ConstHalfEdgeIter & _he_it) const
	{
		return HedronHandle((size_t)handle(*_he_it) / EdgeCount[kernel_type_]);
	}
	/** retrieve the hedron handle of the half edge */
	HedronHandle THKernel::hedron_handle(const HalfEdgeHandle & _heh) const
	{
		return HedronHandle(_heh.idx() / EdgeCount[kernel_type_]);
	}

	/** retrieve the half face handle of a half edge */
	HalfFaceHandle THKernel::half_face_handle(const HalfEdge & _he) const
	{
		return TopologyKernel::half_face_handle(_he);
	}
	/** retrieve the half face handle of a half edge */
	HalfFaceHandle THKernel::half_face_handle(const HalfEdgeHandle & _heh) const
	{
		return TopologyKernel::half_face_handle(_heh);
	}
	/** retrieve the half edge handle of a vertex */
	HalfEdgeHandle THKernel::half_edge_handle(const Vertex & _v) const
	{
		return TopologyKernel::half_edge_handle(_v);
	}
	/** retrieve the half edge handle of a vertex */
	HalfEdgeHandle THKernel::half_edge_handle(const VertexHandle & _vh) const
	{
		return TopologyKernel::half_edge_handle(_vh);
	}

	/** retrieve the face handle of the hedron */
	HalfFaceHandle THKernel::first_half_face_handle(const Hedron & _h) const
	{
		return HalfFaceHandle(handle(_h).idx() * FaceCount[kernel_type_]);
	}
	/** retrieve the hedron handle of the half face */
	HalfFaceHandle THKernel::first_half_face_handle(const THKernel::ConstHedronIter & _h_it) const
	{
		return HalfFaceHandle(handle(*_h_it).idx() * FaceCount[kernel_type_]);
	}

	/** retrieve the face handle of the hedron */
	HalfFaceHandle THKernel::first_half_face_handle(const HedronHandle & _hh) const
	{
		return HalfFaceHandle(_hh.idx() * FaceCount[kernel_type_]);
	}
	/** retrieve the first half edge handle of the hedron */
	HalfEdgeHandle THKernel::first_half_edge_handle(const ConstHedronIter & _h_it) const
	{
		return HalfEdgeHandle(handle(*_h_it).idx() * EdgeCount[kernel_type_]);
	}
	/** retrieve the first half edge handle of the hedron */
	HalfEdgeHandle THKernel::first_half_edge_handle(const HedronHandle & _hh) const
	{
		return HalfEdgeHandle(_hh.idx() * EdgeCount[kernel_type_]);
	}
	/** retrieve the first vertex handle of the hedron */
	VertexHandle THKernel::first_vertex_handle(const HedronHandle & _hh) const
	{	
		return from_vertex_handle(first_half_edge_handle(first_half_face_handle(_hh)));
	}
	/** retrieve the first vertex handle of the hedron */
	VertexHandle   THKernel::first_vertex_handle(const ConstHedronIter & _h_it) const
	{		
		return from_vertex_handle(first_half_edge_handle(first_half_face_handle(handle(*_h_it))));
	}
	/** retrieve the previous half face handle */
	HalfFaceHandle THKernel::prev_half_face_handle(const HalfFaceHandle & _hfh) const
	{
		return HalfFaceHandle( (_hfh.idx() / FaceCount[kernel_type_] * FaceCount[kernel_type_] + 
			                   (_hfh.idx() + PrevFactor[kernel_type_]) % FaceCount[kernel_type_]) ); 
	}
	/** retrieve the next half face handle     */
	HalfFaceHandle THKernel::next_half_face_handle(const HalfFaceHandle & _hfh) const
	{
		return HalfFaceHandle( (_hfh.idx() / FaceCount[kernel_type_] * FaceCount[kernel_type_] + 
			                   (_hfh.idx() + 1) % FaceCount[kernel_type_]) ); 

	}
	/** retrieve the opposite half face handle */
	HalfFaceHandle  THKernel::opp_half_face_handle(const HalfFaceHandle & _hfh) const
	{
		return TopologyKernel::opp_half_face_handle(_hfh);
		//return half_face(_hfh).opp_hfh_;
	}
	/** retrieve the previous non boundary half face handle */
	HalfFaceHandle THKernel::prev_non_boundary_half_face_handle(const HalfFaceHandle & _hfh) const
	{
		HalfFaceHandle hfh(_hfh);
		do 
		{
			hfh = next_half_face_handle(hfh);
			if (hfh == _hfh)
			{
				return HalfFaceHandle(-1);
			}			
		} while (!has_opposite_half_face(hfh));
		return hfh;
		
	}
	/** retrieve the next non boundary half face handle     */
	HalfFaceHandle THKernel::next_non_boundary_half_face_handle(const HalfFaceHandle & _hfh) const
	{
		HalfFaceHandle hfh(_hfh);
		do 
		{
			hfh = prev_half_face_handle(hfh);
			if (hfh == _hfh)
			{
				return HalfFaceHandle(-1);
			}			
		} while (!has_opposite_half_face(hfh));
		return hfh;

	}
	/** retrieve the first half edge handle of the half face */
	HalfEdgeHandle THKernel::first_half_edge_handle(const HalfFaceHandle & _hfh) const
	{
		return HalfEdgeHandle(_hfh.idx() * FaceEdge[kernel_type_]);
	}

	/** retrieve the previous half edge handle */
	HalfEdgeHandle THKernel::prev_half_edge_handle(const HalfEdgeHandle & _heh) const
	{
		return HalfEdgeHandle( _heh.idx() / FaceEdge[kernel_type_] * FaceEdge[kernel_type_] +
			                  (_heh.idx() + RR[kernel_type_]) % FaceEdge[kernel_type_]);
	}
	/** retrieve the next half edge handle     */
	HalfEdgeHandle THKernel::next_half_edge_handle(const HalfEdgeHandle & _heh) const
	{
		return HalfEdgeHandle( _heh.idx() / FaceEdge[kernel_type_] * FaceEdge[kernel_type_] + 
			                  (_heh.idx() + 1) % FaceEdge[kernel_type_]);
	}	
	
	/** retrieve the mate half edge handle     */
	HalfEdgeHandle THKernel::cw_opp_half_edge_handle(const HalfEdgeHandle & _heh) const
	{
		if (_heh.is_valid())
		{
			return HalfEdgeHandle( _heh.idx() / EdgeCount[kernel_type_] * EdgeCount[kernel_type_] + 
				                   Mate[kernel_type_][_heh.idx() % EdgeCount[kernel_type_]] );
				                   
		}
		return HalfEdgeHandle(-1);
	}
	/** retrieve the opposite half edge handle */
	HalfEdgeHandle THKernel::ccw_opp_half_edge_handle(const HalfEdgeHandle & _heh)  const
	{
		return TopologyKernel::ccw_opp_half_edge_handle(_heh);
	}

	/** retrieve the start vertex handle of the half edge */
	VertexHandle THKernel::from_vertex_handle(const HalfEdgeHandle & _heh) const
	{
		return TopologyKernel::from_vertex_handle(_heh);
		//return half_edge(_heh).vh_;
	}
	/** retrieve the end vertex handl of the half edge    */
	VertexHandle THKernel::to_vertex_handle(const HalfEdgeHandle & _heh) const
	{
		//HalfEdgeHandle heh;
		//heh = next_half_edge_handle(_heh);
		return TopologyKernel::from_vertex_handle(next_half_edge_handle(_heh));
	}
	/** retrieve the ccw hedron hedron handle of the half edge */
	HedronHandle THKernel::ccw_hedron_handle(const HalfEdgeHandle & _heh) const
	{
		return hedron_handle(ccw_opp_half_edge_handle(_heh));
	}
	/** retrieve the cw hedron hedron handle of the half edge */
	HedronHandle THKernel::cw_hedron_handle(const HalfEdgeHandle & _heh) const
	{
		return hedron_handle(ccw_opp_half_edge_handle(cw_opp_half_edge_handle(_heh)));
	}

	/** retrieve the previous half edge handle of a hedron */
	HalfEdgeHandle THKernel::prev_hedron_vertex_half_edge_handle(const HalfEdgeHandle & _heh) const
	{
		return HalfEdgeHandle(_heh.idx() / EdgeCount[kernel_type_] * EdgeCount[kernel_type_] + 
			                  PVertexHalfEdge[kernel_type_][_heh.idx() % EdgeCount[kernel_type_]]);
	}
	/** retrieve the next half edge handle of a hedron     */
	HalfEdgeHandle THKernel::next_hedron_vertex_half_edge_handle(const HalfEdgeHandle & _heh) const
	{
		return HalfEdgeHandle(_heh.idx() / EdgeCount[kernel_type_] * EdgeCount[kernel_type_] + 
			                  NVertexHalfEdge[kernel_type_][_heh.idx() % EdgeCount[kernel_type_]]);
	}
	//-----------------------------------------------------------------------------------------------------------------
	/** retrieve the out half edges of a vertex */
	std::vector<HalfEdgeHandle> THKernel::o_half_edges(const VertexHandle & _vh) const
	{
		std::vector<HalfEdgeHandle> ohehs;
		HalfEdgeHandle heh;
		HalfEdgeHandle nheh;
		std::set<HalfEdgeHandle> ahehs;
		std::queue<HalfEdgeHandle> bfs;
		heh = half_edge_handle(_vh);
		bfs.push(heh);
		ahehs.insert(heh);
		while(!bfs.empty())
		{
			heh = bfs.front();
			bfs.pop();
			nheh = next_half_edge_handle(cw_opp_half_edge_handle(heh));
			if (ahehs.find(nheh) == ahehs.end())
			{
				bfs.push(nheh);
				ahehs.insert(nheh);
			}
			nheh = next_half_edge_handle(ccw_opp_half_edge_handle(heh));
			if (ahehs.find(nheh) == ahehs.end())
			{
				bfs.push(nheh);
				ahehs.insert(nheh);
			}
		}
		ohehs.assign(ahehs.begin(), ahehs.end());
		return ohehs;
		
		
	}
	/** retrieve the in  half edges of a vertex */
	std::vector<HalfEdgeHandle> THKernel::i_half_edges(const VertexHandle & _vh) const
	{
		std::vector<HalfEdgeHandle> ihehs;
		HalfEdgeHandle heh;
		HalfEdgeHandle pheh;
		std::set<HalfEdgeHandle> ahehs;
		std::queue<HalfEdgeHandle> bfs;
		heh = prev_half_edge_handle(half_edge_handle(_vh));
		bfs.push(heh);
		ahehs.insert(heh);
		while(!bfs.empty())
		{
			heh = bfs.front();
			bfs.pop();
			pheh = prev_half_edge_handle(cw_opp_half_edge_handle(heh));
			if (ahehs.find(pheh) == ahehs.end())
			{
				bfs.push(pheh);
				ahehs.insert(pheh);
			}
			pheh = prev_half_edge_handle(ccw_opp_half_edge_handle(heh));
			if (ahehs.find(pheh) == ahehs.end())
			{
				bfs.push(pheh);
				ahehs.insert(pheh);
			}
		}

		ihehs.assign(ahehs.begin(), ahehs.end());
		
		
		return ihehs;
	}
	/** retrieve the out half edges of a vertex */
	std::vector<HalfEdgeHandle> THKernel::o_half_edges(const ConstVertexIter & _v_it) const
	{
		return o_half_edges(handle(*_v_it));
	}
	/** retrieve the in  half edges of a vertex */
	std::vector<HalfEdgeHandle> THKernel::i_half_edges(const ConstVertexIter & _v_it) const
	{
		return i_half_edges(handle(*_v_it));
	}
	/** retrieve the one ring adjacent vertices of a vertex */
	std::vector<VertexHandle> THKernel::vertex_star_vertices(const VertexHandle & _vh) const
	{
		std::vector<VertexHandle> vhs;
		HalfEdgeHandle heh;
		HalfEdgeHandle ccwheh;
		HalfEdgeHandle cwheh;
		VertexHandle vh;
		HalfEdgeHandle pheh;
		heh = prev_half_edge_handle(half_edge_handle(_vh));
		std::set<VertexHandle> avhs;
		std::set<HalfEdgeHandle> ahehs;
		std::queue<HalfEdgeHandle> bfs;
		bfs.push(heh);
		ahehs.insert(heh);
		avhs.insert(from_vertex_handle(heh));
		while(!bfs.empty())
		{
			heh = bfs.front();
			bfs.pop();
			pheh = prev_half_edge_handle(cw_opp_half_edge_handle(heh));
			if (ahehs.find(pheh) == ahehs.end())
			{
				ahehs.insert(pheh);
				bfs.push(pheh);
			}
			//vh = from_vertex_handle(pheh);
			//avhs.insert(vh);

			pheh = prev_half_edge_handle(ccw_opp_half_edge_handle(heh));
			if (ahehs.find(pheh) == ahehs.end())
			{
				ahehs.insert(pheh);
				bfs.push(pheh);
			}
			vh = from_vertex_handle(pheh);
			avhs.insert(vh);
		}
		vhs.assign(avhs.begin(), avhs.end());
		return vhs;
	}
	/** retrieve the one ring adjacent vertices of a vertex */
	std::vector<VertexHandle> THKernel::vertex_star_vertices(const ConstVertexIter & _v_it) const
	{
		return vertex_star_vertices(handle(*_v_it));
	}

	/** retrieve the star  hedrons of a vertex  */
	std::vector<HedronHandle> THKernel::vertex_star_hedrons(const VertexHandle & _vh) const
	{
		std::vector<HedronHandle> shhs;
		HalfEdgeHandle heh;
		HalfEdgeHandle ccwheh;
		HalfEdgeHandle cwheh;
		HalfEdgeHandle nheh;
		HedronHandle hh;		
		heh = half_edge_handle(_vh);
		std::set<HedronHandle> ahhs;
		std::set<HalfEdgeHandle> ahehs;
		std::queue<HalfEdgeHandle> bfs;
		bfs.push(heh);
		ahehs.insert(heh);
		hh = hedron_handle(heh);
		ahhs.insert(hh);
		while(!bfs.empty())
		{
			heh = bfs.front();
			bfs.pop();
			nheh = heh;
			do 
			{
				ccwheh = ccw_opp_half_edge_handle(nheh);
				cwheh  = cw_opp_half_edge_handle(nheh);
				if (ccwheh != cwheh)
				{
					hh = hedron_handle(ccwheh);
					if (ahhs.find(hh) == ahhs.end())
					{
						ahhs.insert(hh);
						bfs.push(cw_opp_half_edge_handle(ccwheh));
					}
				}
				nheh = cw_opp_half_edge_handle(prev_half_edge_handle(nheh));				
			} while (nheh != heh);
		}
		shhs.assign(ahhs.begin(), ahhs.end());
		return shhs;
	}

	/** retrieve the star  hedrons of a vertex  */
	std::vector<HedronHandle> THKernel::vertex_star_hedrons(const ConstVertexIter & _v_it) const
	{
		return vertex_star_hedrons(handle(*_v_it));
	}

	//-----------------------------------------------------------------------------------------------------------------
	/** return the first neighbor of the input hedron ()*/
	THKernel::HedronHedronIter THKernel::hedron_hedron_iter(const HedronHandle & _hh) 
	{
		HalfFaceHandle hf;
		hf = first_half_face_handle(_hh);
		HalfFaceHandle hfh;
		hfh = hf;
		while(!has_opposite_half_face(hfh))
		{
			hfh = next_non_boundary_half_face_handle(hfh);
			if (!hfh.is_valid())
			{
				break;
			}
			
		}
		
		return HedronHedronIter(*this, hfh);
	}
	/** return the first neighbor of the input hedron */
	THKernel::HedronHedronIter THKernel::hedron_hedron_iter(const HedronIter & _h_it) 
	{
		HalfFaceHandle hf;
		hf = first_half_face_handle(*_h_it);
		HalfFaceHandle hfh;
		hfh = hf;
		while(!has_opposite_half_face(hfh))
		{
			hfh = next_non_boundary_half_face_handle(hfh);
			if (!hfh.is_valid())
			{
				break;
			}
			
		}

		return HedronHedronIter(*this, hfh);
	}
	/** return the first neighbor of the input hedron ()*/
	THKernel::ConstHedronHedronIter THKernel::const_hedron_hedron_iter(const HedronHandle & _hh) const 
	{
		HalfFaceHandle hf;
		hf = first_half_face_handle(_hh);
		HalfFaceHandle hfh;
		hfh = hf;
		while(!has_opposite_half_face(hfh))
		{
			hfh = next_non_boundary_half_face_handle(hfh);	
			if (!hfh.is_valid())
			{
				break;
			}			
		}

		return ConstHedronHedronIter(*this, hfh);
	}
	/** return the first neighbor of the input hedron */
	THKernel::ConstHedronHedronIter THKernel::const_hedron_hedron_iter(const ConstHedronIter & _h_it) const
	{
		HalfFaceHandle hf;
		hf = first_half_face_handle(*_h_it);
		HalfFaceHandle hfh;
		hfh = hf;
		while(!has_opposite_half_face(hfh))
		{
			hfh = next_non_boundary_half_face_handle(hfh);
			if (!hfh.is_valid())
			{
				break;
			}			
		}

		return ConstHedronHedronIter(*this, hfh);
	}
	/** return the first half face iter of the input hedron ()*/
	THKernel::HedronHalfFaceIter THKernel::hedron_half_face_iter(const HedronHandle & _hh)
	{
		HalfFaceHandle hf;
		hf = first_half_face_handle(_hh);
		return HedronHalfFaceIter(*this, hf);

	}
	/** return the first half face iter of the input hedron   */
	THKernel::HedronHalfFaceIter THKernel::hedron_half_face_iter(const HedronIter & _h_it)
	{
		HalfFaceHandle hf;
		hf = first_half_face_handle(*_h_it);

		return HedronHalfFaceIter(*this, hf);
	}
	/** return the first half face iter of the input hedron ()*/
	THKernel::ConstHedronHalfFaceIter THKernel::const_hedron_half_face_iter(const HedronHandle & _hh) const
	{
		HalfFaceHandle hf;
		hf = first_half_face_handle(_hh);
		return ConstHedronHalfFaceIter(*this, hf);

	}
	/** return the first half face iter of the input hedron   */
	THKernel::ConstHedronHalfFaceIter THKernel::const_hedron_half_face_iter(const ConstHedronIter & _h_it)const
	{
		HalfFaceHandle hf;
		hf = first_half_face_handle(*_h_it);

		return ConstHedronHalfFaceIter(*this, hf);
	}
	/** return the first half edge iter of the input hedron ()*/
	THKernel::HedronHalfEdgeIter THKernel::hedron_half_edge_iter(const HedronHandle & _hh)
	{
		return HedronHalfEdgeIter(*this, first_half_edge_handle(_hh), EdgeCount[kernel_type_]);
	}
	/** return the first half edge iter of the input hedron   */
	THKernel::HedronHalfEdgeIter THKernel::hedron_half_edge_iter(const THKernel::HedronIter & _h_it)
	{
		return HedronHalfEdgeIter(*this, first_half_edge_handle(_h_it), EdgeCount[kernel_type_]);
	}
	/** return the first half edge iter of the input hedron ()*/
	THKernel::ConstHedronHalfEdgeIter THKernel::const_hedron_half_edge_iter(const HedronHandle & _hh) const 
	{
		return ConstHedronHalfEdgeIter(*this, first_half_edge_handle(_hh), EdgeCount[kernel_type_]);
	}
	/** return the first half edge iter of the input hedron ()*/
	THKernel::ConstHedronHalfEdgeIter THKernel::const_hedron_half_edge_iter(const THKernel::ConstHedronIter & _h_it) const 
	{
		return ConstHedronHalfEdgeIter(*this, first_half_edge_handle(_h_it), EdgeCount[kernel_type_]);
	}
	/** return the first vertex iter of the input hedron ()*/
	THKernel::HedronVertexIter THKernel::hedron_vertex_iter(const HedronHandle & _hh)
	{
		HalfEdgeHandle heh;
		heh = HalfEdgeHandle(first_half_edge_handle(_hh).idx() + StartVertex[kernel_type_]);
		return HedronVertexIter(*this, heh);
	}
	/** return the first vertex iter of the input hedron   */
	THKernel::HedronVertexIter THKernel::hedron_vertex_iter(const THKernel::HedronIter & _h_it)
	{	
		HalfEdgeHandle heh;
		heh = HalfEdgeHandle(first_half_edge_handle(_h_it).idx() + StartVertex[kernel_type_]);
		return HedronVertexIter(*this, heh);
	}
	/** return the first vertex iter of the input hedron ()*/
	THKernel::ConstHedronVertexIter THKernel::const_hedron_vertex_iter(const HedronHandle & _hh) const 
	{
		HalfEdgeHandle heh;
		heh = HalfEdgeHandle(first_half_edge_handle(_hh).idx() + StartVertex[kernel_type_]);
		return ConstHedronVertexIter(*this, heh);
	}
	/** return the first vertex iter of the input hedron   */
	THKernel::ConstHedronVertexIter THKernel::const_hedron_vertex_iter(const ConstHedronIter & _h_it) const
	{
		HalfEdgeHandle heh;
		heh = HalfEdgeHandle(first_half_edge_handle(_h_it).idx() + StartVertex[kernel_type_]);
		return ConstHedronVertexIter(*this, heh);
	}
	/** return the first vertex iter of the input half face */
	THKernel::HalfFaceVertexIter THKernel::half_face_vertex_iter(const HalfFaceHandle & _hfh)
	{
		return HalfFaceVertexIter(*this, first_half_edge_handle(_hfh));
	}
	/** return the first vertex iter of the input half face */
	THKernel::HalfFaceVertexIter THKernel::half_face_vertex_iter(const HalfFaceIter & _hf_it)
	{
		return HalfFaceVertexIter(*this, first_half_edge_handle(handle(*_hf_it)));

	}
	/** return the first const vertex iter of the input half face */
	THKernel::ConstHalfFaceVertexIter THKernel::const_half_face_vertex_iter(const HalfFaceHandle & _hfh) const
	{
		return ConstHalfFaceVertexIter(*this, first_half_edge_handle(_hfh));
	}
	/** return the first const vertex iter of the input half face */
	THKernel::ConstHalfFaceVertexIter THKernel::const_half_face_vertex_iter(const ConstHalfFaceIter & _hf_it) const
	{
		return ConstHalfFaceVertexIter(*this, first_half_edge_handle(handle(*_hf_it)));
	}
	/** return the first half edge iter of the input half face */
	THKernel::HalfFaceHalfEdgeIter THKernel::half_face_half_edge_iter(const HalfFaceHandle & _hh)
	{
		return HalfFaceHalfEdgeIter(*this, first_half_edge_handle(_hh));
	}
	/** return the first half edge iter of the input half face */
	THKernel::HalfFaceHalfEdgeIter THKernel::half_face_half_edge_iter(const HalfFaceIter & _h_it)
	{
		return HalfFaceHalfEdgeIter(*this, first_half_edge_handle(handle(*_h_it)));
	}
	/** return the first half edge iter of the input half face */
	THKernel::ConstHalfFaceHalfEdgeIter THKernel::const_half_face_half_edge_iter(const HalfFaceHandle & _hh) const
	{
		return ConstHalfFaceHalfEdgeIter(*this, first_half_edge_handle(_hh));
	}
	/** return the first half edge iter of the input half face */
	THKernel::ConstHalfFaceHalfEdgeIter THKernel::const_half_face_half_edge_iter(const ConstHalfFaceIter & _h_it) const  
	{
		return ConstHalfFaceHalfEdgeIter(*this, first_half_edge_handle(handle(*_h_it)));
	}
	/** return the first hedron of the half edge */
	THKernel::HalfEdgeHedronIter THKernel::half_edge_hedron_iter(const HalfEdgeHandle & _heh)
	{
		return HalfEdgeHedronIter(*this, _heh);
	}
	/** return the first hedron of the half edge */
	THKernel::HalfEdgeHedronIter THKernel::half_edge_hedron_iter(const HalfEdgeIter & _he_it)
	{
		return HalfEdgeHedronIter(*this, handle(*_he_it));
	}
	/** return the first hedron of the half edge */
	THKernel::ConstHalfEdgeHedronIter THKernel::const_half_edge_hedron_iter(const HalfEdgeHandle & _heh) const
	{
		return ConstHalfEdgeHedronIter(*this, _heh);
	}
	/** return the first hedron of the half edge */
	THKernel::ConstHalfEdgeHedronIter THKernel::const_half_edge_hedron_iter(const ConstHalfEdgeIter & _he_it) const    
	{
		return ConstHalfEdgeHedronIter(*this, handle(*_he_it));
	}
	/** return the first hedron of the vertex */
	THKernel::VertexHedronIter THKernel::vertex_hedron_iter(const VertexHandle & _vh)
	{
		return VertexHedronIter(*this, vertex_star_hedrons(_vh));
	}
	/** return the first hedron of the vertex */
	THKernel::VertexHedronIter THKernel::vertex_hedron_iter(const VertexIter & _v_it)
	{
		return VertexHedronIter(*this, vertex_star_hedrons(_v_it));
	}
	/** return the first hedron of the vertex */
	THKernel::ConstVertexHedronIter THKernel::const_vertex_hedron_iter(const VertexHandle & _vh) const
	{
		return ConstVertexHedronIter(*this, vertex_star_hedrons(_vh));
	}
	/** return the first hedron of the vertex */
	THKernel::ConstVertexHedronIter THKernel::const_vertex_hedron_iter(const ConstVertexIter & _v_it) const
	{
		return ConstVertexHedronIter(*this, vertex_star_hedrons(_v_it));
	}

	/** return the first half face of a hedron attached to the vertex */
	THKernel::VertexHedronHalfFaceIter THKernel::vertex_hedron_half_face_iter(const VertexHandle & _vh, HedronHandle _hh)
	{
		HalfEdgeHandle heh;
		for (ConstHedronHalfEdgeIter chhe_it = const_hedron_half_edge_iter(_hh); chhe_it; ++ chhe_it)
		{
			heh = chhe_it.handle();
			if (from_vertex_handle(heh) == _vh)
			{
				break;
			}
		}
		return VertexHedronHalfFaceIter(*this, heh);		
	}

	/** return the first half face of a hedron attached to the vertex */
	THKernel::VertexHedronHalfFaceIter THKernel::vertex_hedron_half_face_iter(const VertexIter & _v_it, HedronHandle _hh)
	{
		VertexHandle vh;
		HalfEdgeHandle heh;
		vh = handle(*_v_it);
		for (ConstHedronHalfEdgeIter chhe_it = const_hedron_half_edge_iter(_hh); chhe_it; ++ chhe_it)
		{
			heh = chhe_it.handle();
			if (from_vertex_handle(heh) == vh)
			{
				break;
			}
		}
		return VertexHedronHalfFaceIter(*this, heh);		
	}

	/** return the first half face of a hedron attached to the vertex */
	THKernel::ConstVertexHedronHalfFaceIter THKernel::const_vertex_hedron_half_face_iter(const VertexHandle & _vh, HedronHandle _hh) const
	{
		HalfEdgeHandle heh;
		for (ConstHedronHalfEdgeIter chhe_it = const_hedron_half_edge_iter(_hh); chhe_it; ++ chhe_it)
		{
			heh = chhe_it.handle();
			if (from_vertex_handle(heh) == _vh)
			{
				break;
			}
		}
		return ConstVertexHedronHalfFaceIter(*this, heh);		
	}

	/** return the first half face of a hedron attached to the vertex */
	THKernel::ConstVertexHedronHalfFaceIter THKernel::const_vertex_hedron_half_face_iter(const ConstVertexIter & _v_it, HedronHandle _hh) const
	{
		VertexHandle vh;
		HalfEdgeHandle heh;
		vh = handle(*_v_it);
		for (ConstHedronHalfEdgeIter chhe_it = const_hedron_half_edge_iter(_hh); chhe_it; ++ chhe_it)
		{
			heh = chhe_it.handle();
			if (from_vertex_handle(heh) == vh)
			{
				break;
			}
		}
		return ConstVertexHedronHalfFaceIter(*this, heh);		
	}

	/** return the first adjacent vertex of the vertex */
	THKernel::VertexVertexIter THKernel::vertex_vertex_iter(const VertexHandle & _vh)
	{
		return VertexVertexIter(*this, vertex_star_vertices(_vh)); 
	}
	/** return the first adjacent vertex of the vertex */
	THKernel::VertexVertexIter THKernel::vertex_vertex_iter(const VertexIter & _v_it)
	{
		return VertexVertexIter(*this, vertex_star_vertices(_v_it)); 
	}
	/** return the first adjacent vertex of the vertex */
	THKernel::ConstVertexVertexIter THKernel::const_vertex_vertex_iter(const VertexHandle & _vh) const
	{
		return ConstVertexVertexIter(*this, vertex_star_vertices(_vh)); 
	}
	/** return the first adjacent vertex of the vertex */
	THKernel::ConstVertexVertexIter THKernel::const_vertex_vertex_iter(const ConstVertexIter & _v_it) const    
	{
		return ConstVertexVertexIter(*this, vertex_star_vertices(_v_it)); 
	}
	/** compute the valence of the vertex */
	size_t THKernel::valence(VertexHandle _vh) const
	{
		if (_vh.is_valid())
		{			
			return vertex_star_vertices(_vh).size();
		}
		return 0;
	}
	//-----------------------------------------------------------------------------------------------------------------

	/** add a hedron into the mesh
	*   \param _h_idx the vertex handles of the hedron
	*   \return the hedron handle
	*/
	HedronHandle THKernel::add_hedron(const std::vector<VertexHandle> & _h_idx)
	{
		assert(_h_idx.size() == VertexCount[kernel_type_]);

		size_t heIdx;
		size_t hfIdx;
		size_t faceHE;
		size_t face_count;
		size_t edge_count;
		size_t vertex_count;
		size_t face_edge;
		std::vector<size_t> phs;
		OppFaceContainer::iterator opp_it;
		const int * matrixType = VertexMatrix[kernel_type_];
		face_count   = FaceCount[kernel_type_];
		edge_count   = EdgeCount[kernel_type_];
		vertex_count = VertexCount[kernel_type_];
		face_edge  = FaceEdge[kernel_type_];
		hfIdx = n_half_faces();
		heIdx = n_half_edges();
		HalfEdgeHandle heh;
		VertexHandle vh;

		faceHE = 0;
		//--- generate the half faces
		for (size_t k = 0; k < face_count; k ++)
		{
			new_half_face(HalfFace(HalfEdgeHandle(heIdx + faceHE)));
			faceHE += face_edge; 
		}
		//--- generate the half edges EdgeCount[kernel_type_]
		for (size_t k = 0; k < edge_count; k ++)
		{
			vh = _h_idx[matrixType[k]];
			heh =  new_half_edge(HalfEdge(HalfFaceHandle((hfIdx +  k / face_edge)), VertexHandle(_h_idx[matrixType[k]])));
			if (!half_edge_handle(vh).is_valid())
			{
				set_vertex_half_edge(vh, heh);
			}
		}

		//------------- the following codes are used to build the topology 

		//--- build the opposite faces
		//phs.resize(face_edge);
		//for (size_t i = 0; i < face_count; i ++)
		//{

		//	for (size_t k = 0; k < face_edge; k ++)
		//	{
		//		phs[k] = from_vertex_handle(HalfEdgeHandle(heIdx + k)).idx();
		//	}

		//	std::sort(phs.begin(), phs.end());
		//	LessArray<size_t> faceIdx(phs);
		//	opp_it = opp_faces_.find(faceIdx);
		//	if (opp_it != opp_faces_.end())
		//	{
		//		if (opp_it->second != -1)
		//		{
		//			set_opposite_half_face(HalfFaceHandle(hfIdx + i), HalfFaceHandle(opp_it->second));
		//			opp_it->second = -1;
		//		}
		//		else
		//		{
		//			std::cerr << "Error! the half face of the " << i << "-th half face has been existed !" << std::endl;
		//			return HedronHandle(-1);
		//		}
		//	}
		//	else
		//	{				

		//		opp_faces_[faceIdx] = hfIdx + i;
		//	}
		//	heIdx += face_edge; //EdgeCount[kernel_type_];
		//	
		//}

		HalfFaceIter hf_begin;
		HalfFaceIter hf_end(half_faces_end());
		hf_begin = hf_end - face_count;
		if (!build_opposite_half_faces(hf_begin, hf_end))
		{
			std::cerr << "Error :  cannot add a new hedron ! \n Failure to build opposite half faces!" << std::endl;
			half_faces_resize(n_half_faces() - face_count);
			half_edges_resize(n_half_edges() - edge_count);
			return HedronHandle(-1);
		}

		//--- build the opposite half edges
		HalfEdgeIter he_begin;
		HalfEdgeIter he_end(half_edges_end());
		he_begin = he_end - edge_count; 
		if (!build_opposite_half_edges(he_begin, he_end))
		{
			half_faces_resize(n_half_faces() - face_count);
			half_edges_resize(n_half_edges() - edge_count);
			std::cerr << "Error : cannot add a new hedron !\n Failure to build opposite half edges!" << std::endl;
			
			return HedronHandle(-1);
		}
		return new_hedron(Hedron(HalfFaceHandle(hfIdx)));
	}
	/** delete a hedron
	*   \param _hh the input hedron
	*   \return true for success
	*/
	bool THKernel::delete_hedron(const ConstHedronIter & _h_it, bool _delete_isolate_vertices)
	{
		
		return delete_hedron(handle(*_h_it));
	}
	/** delete a hedron
	*   \param _hh the input hedron
	*   \return true for success
	*/
	bool THKernel::delete_hedron(HedronHandle _hh, bool _delete_isolate_vertices)
	{
		assert(is_valid_handle(_hh) && (!status(_hh).deleted()));

		
		//--- mark the status ---
		status(_hh).set_deleted(true);

		std::vector<HalfFaceHandle> deleted_faces;
		std::vector<HalfEdgeHandle> deleted_edges;
		deleted_faces.reserve(FaceCount[kernel_type_]);
		deleted_edges.reserve(EdgeCount[kernel_type_]);

		std::vector<VertexHandle> vertex_handles;
		vertex_handles.reserve(VertexCount[kernel_type_]);
		HalfFaceHandle hfh;

		//--- set invalid half face handle ---
		for (HedronHalfFaceIter hhf_it = hedron_half_face_iter(_hh); hhf_it; ++ hhf_it)
		{
			hfh = hhf_it.handle();
			update_opp_face(hfh, true);
			//remove_opp_half_faces(hfh);
			//set_opposite_half_face(hfh, HalfFaceHandle(-1));
			set_opposite_half_face(opp_half_face_handle(hfh), HalfFaceHandle(-1));
			deleted_faces.push_back(hfh);
			status(hfh).set_deleted(true);
			for (HalfFaceHalfEdgeIter hfhe_it = half_face_half_edge_iter(hfh); hfhe_it; ++ hfhe_it)
			{
				deleted_edges.push_back(hfhe_it.handle());
				status(hfhe_it.handle()).set_deleted(true);
			}
		}
		for (HedronVertexIter hv_it = hedron_vertex_iter(_hh); hv_it; ++ hv_it)
		{
			vertex_handles.push_back(hv_it.handle());
		}

		//--- record the deleted vertices ---
		HalfEdgeHandle heh;
		std::vector<HalfEdgeHandle> ohes;
		std::vector<HalfEdgeHandle>::iterator it;
		for (size_t i = 0; i < vertex_handles.size(); i ++)
		{
			heh = half_edge_handle(vertex_handles[i]);
			it  = std::find(deleted_edges.begin(), deleted_edges.end(), heh);
			if (it != deleted_edges.end())
			{
				ohes = o_half_edges(vertex_handles[i]);
				bool has_find;
				has_find = false;
				for (size_t k = 0; k < ohes.size(); k ++)
				{
					it  = std::find(deleted_edges.begin(), deleted_edges.end(), ohes[k]);
					if (it == deleted_edges.end())
					{
						has_find = true;
						set_vertex_half_edge(vertex_handles[i], ohes[k]);
						break;
					}
				}
				if (!has_find)
				{
					//--- all out edges in the same hedron, delete it ---
					status(vertex_handles[i]).set_deleted(true);
				}
			}
		}

		//--- change the opposite half edges ---
		for (size_t i = 0; i < deleted_edges.size();i ++)
		{
			set_ccw_opposite_half_edge(ccw_opp_half_edge_handle(deleted_edges[i]), ccw_opp_half_edge_handle(cw_opp_half_edge_handle(deleted_edges[i])));
			//set_ccw_opposite_half_edge(deleted_edges[i], HalfEdgeHandle(-1));
		}
				
		return true;
	}
	/** collect the garbage. Invoke it after deletion */
	void THKernel::garbage_collection(bool _h /* = true */, bool _hf /* = true */, bool _he /* = true */, bool _v /* = true */)
	{
		size_t nv(n_vertices());
		size_t nhe(n_half_edges());
		size_t nhf(n_half_faces());
		size_t nh(n_hedrons());

		//--- setup the mapping ---
		std::vector<HedronHandle> h_maps;
		h_maps.reserve(nh);
		for (size_t i = 0; i < nh; i ++)
		{
			h_maps.push_back(HedronHandle(i));
		}

		std::vector<HalfFaceHandle> hf_maps;
		hf_maps.reserve(nhf);
		for (size_t i = 0; i < nhf; i ++)
		{
			hf_maps.push_back(HalfFaceHandle(i));
		}
		std::vector<HalfEdgeHandle> he_maps;
		he_maps.reserve(nhe);
		for (size_t i = 0; i < nhe; i ++)
		{
			he_maps.push_back(HalfEdgeHandle(i));
		}
		std::vector<VertexHandle> v_maps;
		v_maps.reserve(nv);
		for (size_t i = 0; i < nv; i ++)
		{
			v_maps.push_back(VertexHandle(i));
		}

		//--- remove the deleted items

		size_t i0; 
		size_t i1;
		std::set<VertexHandle> vhs;
		for (i0 = 0; i0 < nv; ++ i0)
		{
			if (status(VertexHandle(i0)).deleted())
			{
				vhs.insert(VertexHandle(i0));
			}
		}
		
		//--- in order to avoid the non-manifold connection , re-check if the deleted vertices should be deleted 
		for (i0 = 0; i0 < nh; ++ i0)
		{	
			if (!status(HedronHandle(i0)).deleted())
			{
				for (ConstHedronVertexIter chv_it = const_hedron_vertex_iter(HedronHandle(i0)); chv_it; ++ chv_it)
				{
					std::set<VertexHandle>::iterator  it = vhs.find(chv_it.handle());
					if (it != vhs.end())
					{
						for (ConstHedronHalfFaceIter chhf_it = const_hedron_half_face_iter(HedronHandle(i0)); chhf_it; ++ chhf_it)
						{
							bool found = false;
							for (ConstHalfFaceHalfEdgeIter chfhe_it = const_half_face_half_edge_iter(chhf_it.handle()); chfhe_it; ++ chfhe_it)
							{
								if (from_vertex_handle(chfhe_it.handle()) == (*it))
								{
									set_vertex_half_edge(*it, chfhe_it.handle());
									found = true;
									break;
								}
							}
							if (found)
							{
								status(*it).set_deleted(false);
								vhs.erase(it);
								break;
							}
						}
					}
				}
			}			
		}
		
		//--- remove the vertices
		if (_v && (nv > 0))
		{
			i0 = 0;
			i1 = nv - 1;

			while(1)
			{
				//--- find the first deleted and the last non-deleted vertices
				while((!status(VertexHandle(i0)).deleted()) && (i0 < i1)) ++ i0; 
				while(( status(VertexHandle(i1)).deleted()) && (i0 < i1)) -- i1;

				if (i0 >= i1)
				{
					break;
				}

				//--- swap ---
				std::swap(vertices_[i0], vertices_[i1]);
				std::swap(v_maps[i0], v_maps[i1]);
				v_properties_swap(i0, i1);
			}
			vertices_resize(status(VertexHandle(i0)).deleted() ? i0: i0 + 1);
			v_properties_resize(n_vertices());
		}

		size_t face_cout(FaceCount[kernel_type_]);
		size_t edge_cout(EdgeCount[kernel_type_]);
		size_t face_idx0;
		size_t face_idx1;
		size_t edge_idx0; 
		size_t edge_idx1;

		if (_h && (nh > 0))
		{
			i0 = 0;
			i1 = nh - 1;

			while(1)
			{
				//--- find the first deleted and the last non-deleted hedron ---
				while((!status(HedronHandle(i0)).deleted()) && (i0 < i1)) ++ i0; 
				while(( status(HedronHandle(i1)).deleted()) && (i0 < i1)) -- i1;

				if (i0 >= i1)
				{
					break;
				}

				//--- swap ---
				swap_hedrons(HedronHandle(i0), HedronHandle(i1));
				std::swap(h_maps[i0], h_maps[i1]);
				h_properties_swap(i0, i1);

				//--- swap the half faces ---
				face_idx0 = i0 * face_cout;
				face_idx1 = i1 * face_cout;
				for (size_t i = 0; i < face_cout; i ++)
				{
					swap_half_faces(HalfFaceHandle(face_idx0), HalfFaceHandle(face_idx1));					
					std::swap(hf_maps[face_idx0], hf_maps[face_idx1]);
					hf_properties_swap(face_idx0, face_idx1);	
					
					++ face_idx0;
					++ face_idx1;
				}
				
				//--- swap the half edges ---
				edge_idx0 = i0 * edge_cout;
				edge_idx1 = i1 * edge_cout;
				for (size_t i = 0; i < edge_cout; i ++)
				{
					swap_half_edges(HalfEdgeHandle(edge_idx0), HalfEdgeHandle(edge_idx1));					
					std::swap(he_maps[edge_idx0], he_maps[edge_idx1]);
					he_properties_swap(edge_idx0, edge_idx1);	

					++ edge_idx0;
					++ edge_idx1;
				}
			}
			hedrons_resize(status(HedronHandle(i0)).deleted() ? i0: i0 + 1);
			h_properties_resize(n_hedrons());

			half_faces_resize(n_hedrons() * face_cout);
			hf_properties_resize(n_half_faces());

			half_edges_resize(n_hedrons() * edge_cout);
			he_properties_resize(n_half_edges());
		}

		VertexHandle vh;
		HalfEdgeHandle heh;
		HalfEdgeHandle oheh;
		HalfFaceHandle hfh;
		HalfFaceHandle ohfh;
		HedronHandle hh;

		//--- update the handles ---
		VertexIter v_end(vertices_end());
		nhe = n_half_edges();
		for (VertexIter v_it = vertices_begin(); v_it != v_end; ++ v_it)
		{			
			vh = handle(*v_it);
			heh = half_edge_handle(vh);
			
			if (heh.is_valid())
			{
				set_vertex_half_edge(vh, he_maps[heh.idx()]);
			}			
		}

		//--- update the handles of the half edges ---
		HalfEdgeIter he_end(half_edges_end());
		for (HalfEdgeIter he_it = half_edges_begin(); he_it != he_end; ++ he_it)
		{
			heh  = handle(*he_it);
			oheh = ccw_opp_half_edge_handle(heh);
			set_ccw_opposite_half_edge(heh, he_maps[oheh.idx()], false);

			vh = from_vertex_handle(heh);
			set_start_vertex(heh, v_maps[vh.idx()]);

			hfh = half_face_handle(heh);
			set_half_face(heh, hf_maps[hfh.idx()]);
		}
		//--- update the opposite half faces of the half faces ---
		HalfFaceIter hf_end(half_faces_end());
		for (HalfFaceIter hf_it = half_faces_begin(); hf_it != hf_end; ++ hf_it)
		{
			hfh = handle(*hf_it);
			ohfh = opp_half_face_handle(hfh);
			if (ohfh.is_valid())
			{
				set_opp_half_face(hfh, hf_maps[ohfh.idx()], false);
			}			
		}
		opp_half_faces_collection();
		v_maps.clear();
		he_maps.clear();
		hf_maps.clear();
		h_maps.clear();
	}

	//-----------------------------------------------------------------------------------------------------------------

	/** build the topology of the mesh
	*   \param _indices the point indices of the hedrons.
	*   \return bool true for success.
	*/
	bool THKernel::build_topology(const IndexContainer & _indices)
	{
		if (!n_vertices())
		{
			std::cerr << "Error : there are no points ! " << std::endl;
			return false;
		}
		
		if (_indices.empty())
		{
			return true;
		}
		
		size_t hedronCount;
		size_t heIdx;
		size_t hfIdx;
		size_t hvIdx;
		size_t faceHE;
		size_t face_count;
		size_t edge_count;
		size_t vertex_count;
		size_t face_edge;
		const int * matrixType = VertexMatrix[kernel_type_];
		face_count   = FaceCount[kernel_type_];
		edge_count   = EdgeCount[kernel_type_];
		vertex_count = VertexCount[kernel_type_];
		face_edge  = FaceEdge[kernel_type_];
		hedronCount = _indices.size() / VertexCount[kernel_type_]; 
		hfIdx = 0;
		heIdx = 0;
		hvIdx = 0;
		HalfEdgeHandle heh;
		VertexHandle vh;
		for (size_t i = 0; i < hedronCount; i ++)
		{
			//--- generate a new hedron 
			new_hedron(Hedron(HalfFaceHandle(hfIdx)));
			faceHE = 0;
			//--- generate the half faces
			for (size_t k = 0; k < FaceCount[kernel_type_]; k ++)
			{
				new_half_face(HalfFace(HalfEdgeHandle(heIdx + faceHE)));
				faceHE += face_edge; //FaceEdge[kernel_type_];
			}
			//--- generate the half edges EdgeCount[kernel_type_]
			for (size_t k = 0; k < edge_count; k ++)
			{
				vh = VertexHandle(_indices[hvIdx +  matrixType[k]]);
				heh =  new_half_edge(HalfEdge(HalfFaceHandle(hfIdx +  k / face_edge), VertexHandle(vh.idx())));
				if (!half_edge_handle(vh).is_valid())
				{
					set_vertex_half_edge(vh, heh);
				}
			}
			hfIdx += face_count; 
			heIdx += edge_count; 
			hvIdx += vertex_count; 
		}
		if (!build_opposite_half_faces())
		{
			return false;
		}
		if (!build_opposite_half_edges())
		{
			return false;
		}
		
		
		return true;
	}
	/** build the opposite half face */
	bool THKernel::build_opposite_half_faces()
	{
		size_t hn;
		hn = n_half_faces(); //n_hedrons() * FaceCount[kernel_type_];
		std::vector<size_t> phs;
		phs.resize(FaceEdge[kernel_type_]); 
		size_t heIdx;
		OppFaceContainer::iterator opp_it;
		heIdx = 0;
		for (size_t i = 0; i < hn; i ++)
		{
			for (size_t k = 0; k < FaceEdge[kernel_type_]; k ++)
			{
				phs[k] = from_vertex_handle(HalfEdgeHandle(heIdx + k)).idx();
			}

			std::sort(phs.begin(), phs.end());
			LessArray<size_t> faceIdx(phs);
			opp_it = opp_faces_.find(faceIdx);
			if (opp_it != opp_faces_.end())
			{
				if (opp_it->second != -1)
				{
					set_opposite_half_face(HalfFaceHandle(i), HalfFaceHandle(opp_it->second));
					opp_it->second = -1;
				}
				else
				{
					std::cerr << "Error! the half face of the " << i << "-th half face has been existed !" << std::endl;
					return false;
				}
			}
			else
			{						
				opp_faces_[faceIdx] = (int)i;
			}
			heIdx += FaceEdge[kernel_type_];
		}
		return true;
	}
	/** build the opposite half face */
	bool THKernel::build_opposite_half_faces(const HalfFaceIter & _hf_begin, const HalfFaceIter & _hf_end)
	{
		std::vector<size_t> phs;
		phs.resize(FaceEdge[kernel_type_]); 
		size_t heIdx;
		size_t hfIdx;
		OppFaceContainer::iterator opp_it;
		
		for (HalfFaceIter hf_it = _hf_begin; hf_it != _hf_end; ++ hf_it)
		{
			hfIdx = (size_t)handle(*hf_it);
			heIdx = hfIdx * FaceEdge[kernel_type_];
			for (size_t k = 0; k < FaceEdge[kernel_type_]; k ++)
			{
				phs[k] = from_vertex_handle(HalfEdgeHandle(heIdx + k)).idx();
			}

			std::sort(phs.begin(), phs.end());
			LessArray<size_t> faceIdx(phs);
			opp_it = opp_faces_.find(faceIdx);
			if (opp_it != opp_faces_.end())
			{
				if (opp_it->second != -1)
				{
					set_opposite_half_face(HalfFaceHandle(hfIdx), HalfFaceHandle(opp_it->second));
					opp_it->second = -1;
				}
				else
				{
					std::cerr << "Error! the half face of the " << hfIdx << "-th half face has been existed !" << std::endl;
					return false;
				}
			}
			else
			{
				opp_faces_[faceIdx] = (int)hfIdx;
			}
			heIdx += FaceEdge[kernel_type_];
		}
		return true;
	}
	/** build the opposite half face */
	bool THKernel::build_opposite_half_faces(const std::vector<HalfFaceHandle> & _hfhs)
	{
		std::vector<size_t> phs;
		phs.resize(FaceEdge[kernel_type_]); 
		size_t heIdx;
		size_t hfIdx;
		OppFaceContainer::iterator opp_it;

		for (size_t i = 0; i < _hfhs.size(); i ++)
		{
			hfIdx = _hfhs[i].idx();
			heIdx = hfIdx * FaceEdge[kernel_type_];
			for (size_t k = 0; k < FaceEdge[kernel_type_]; k ++)
			{
				phs[k] = from_vertex_handle(HalfEdgeHandle(heIdx + k)).idx();
			}

			std::sort(phs.begin(), phs.end());
			LessArray<size_t> faceIdx(phs);
			opp_it = opp_faces_.find(faceIdx);
			if (opp_it != opp_faces_.end())
			{
				if (opp_it->second != -1)
				{
					set_opposite_half_face(HalfFaceHandle(hfIdx), HalfFaceHandle(opp_it->second));
					opp_it->second = -1;
				}
				else
				{
					std::cerr << "Error! the half face of the " << hfIdx << "-th half face has been existed !" << std::endl;
					return false;
				}
			}
			else
			{	
				opp_faces_[faceIdx] = (int)hfIdx;
			}
		}
		return true;
	}
	/** build the opposite half edges */
	bool THKernel::build_opposite_half_edges()
	{
		VertexHandle vh;
		HalfFaceHandle hfh;
		HalfEdgeHandle heh;	
		HalfEdgeHandle fheh;
		HalfEdgeHandle _heh;
		HalfEdgeHandle mheh;
		HalfEdgeHandle omheh;		
		for (THKernel::KernelHalfEdgeIter he_it = half_edges_begin(); he_it != half_edges_end(); ++ he_it)
		{			
			if (!has_opposite_half_edge(*he_it))
			{
				_heh = handle(*he_it);
				vh = from_vertex_handle(_heh);
				hfh = TopologyKernel::opp_half_face_handle(half_face_handle(*he_it));
				if (is_valid_handle(hfh))
				{
					fheh = first_half_edge_handle(hfh);
					heh  = fheh;

					while(to_vertex_handle(heh) != vh)
					{
						heh = next_half_edge_handle(heh);
						if (heh == fheh)
						{
							std::cerr << "Error : the " << handle(*he_it).idx() << "-th half edges has no half edges ! \n";
							return false;
						}
					}
					set_ccw_opposite_half_edge(_heh, heh);
				}
			}
		}
		//--- build opposite half edges for boundary half edges
		for (THKernel::KernelHalfEdgeIter he_it = half_edges_begin(); he_it != half_edges_end(); ++ he_it)
		{
			if (!has_opposite_half_edge(*he_it))
			{
				_heh = handle(*he_it);
				omheh = _heh;				
				do 
				{
					mheh  = cw_opp_half_edge_handle(omheh);
					omheh = ccw_opp_half_edge_handle(mheh);
				} while (is_valid_handle(omheh));
				set_ccw_opposite_half_edge(_heh, mheh);
			}
		}
		return true;
	}
	/** build the opposite half edges */
	bool THKernel::build_opposite_half_edges(const HalfEdgeIter & _he_begin, const HalfEdgeIter & _he_end)
	{
		VertexHandle vh;
		HalfFaceHandle hfh;
		HalfEdgeHandle heh;	
		HalfEdgeHandle fheh;
		HalfEdgeHandle _heh;
		HalfEdgeHandle mheh;
		HalfEdgeHandle omheh;
		HalfEdgeHandle ccwheh;
		HalfEdgeHandle cwheh;
		for (HalfEdgeIter he_it = _he_begin; he_it != _he_end; ++ he_it)
		{	
			_heh = handle(*he_it);		
			if (!has_opposite_half_edge(_heh))
			{
				vh = from_vertex_handle(_heh);
				
				hfh = TopologyKernel::opp_half_face_handle(half_face_handle(*he_it));
				if (is_valid_handle(hfh))
				{
					fheh = first_half_edge_handle(hfh);
					heh  = fheh;

					while(to_vertex_handle(heh) != vh)
					{
						heh = next_half_edge_handle(heh);
						if (heh == fheh)
						{
							std::cerr << "Error : the " << _heh.idx() << "-th half edges has no half edges ! \n";
							return false;
						}
					}
					//cwheh = cw_opp_half_edge_handle(heh);
					ccwheh = ccw_opp_half_edge_handle(heh);
					//if (ccwheh == cwheh)
					//{
						set_ccw_opposite_half_edge(ccwheh, HalfEdgeHandle(-1));
					//}
					set_ccw_opposite_half_edge(_heh, heh);
				}
			}
		}
		//--- build opposite half edges for boundary half edges
		for (HalfEdgeIter he_it = _he_begin; he_it != _he_end; ++ he_it)
		{
			_heh = handle(*he_it);
			if (!has_opposite_half_edge(_heh))
			{
				omheh = _heh;
				do 
				{
					mheh  = cw_opp_half_edge_handle(omheh);
					omheh = ccw_opp_half_edge_handle(mheh);
				} while (is_valid_handle(omheh));
				set_ccw_opposite_half_edge(_heh, mheh);
			}
		}
		return true;
	}
	/** build the opposite half edges */
	bool THKernel::build_opposite_half_edges(const std::vector<HalfEdgeHandle> & _hehs)
	{
		VertexHandle vh;
		HalfFaceHandle hfh;
		HalfEdgeHandle heh;	
		HalfEdgeHandle fheh;
		HalfEdgeHandle _heh;
		HalfEdgeHandle mheh;
		HalfEdgeHandle omheh;
		HalfEdgeHandle ccwheh;
		HalfEdgeHandle cwheh;
		for (size_t i = 0; i < _hehs.size(); i ++)
		{	
			_heh = _hehs[i];		
			if (!has_opposite_half_edge(_heh))
			{
				vh = from_vertex_handle(_heh);
				hfh = TopologyKernel::opp_half_face_handle(half_face_handle(_heh));
				if (is_valid_handle(hfh))
				{
					fheh = first_half_edge_handle(hfh);
					heh  = fheh;

					while(to_vertex_handle(heh) != vh)
					{
						heh = next_half_edge_handle(heh);
						if (heh == fheh)
						{
							std::cerr << "Error : the " << _heh.idx() << "-th half edges has no half edges ! \n";
							return false;
						}
					}
					//cwheh = cw_opp_half_edge_handle(heh);
					ccwheh = ccw_opp_half_edge_handle(heh);
					//if (ccwheh == cwheh)
					//{
					set_ccw_opposite_half_edge(ccwheh, HalfEdgeHandle(-1));
					//}
					set_ccw_opposite_half_edge(_heh, heh);
				}
			}
		}
		//--- build opposite half edges for boundary half edges
		for (size_t i = 0; i < _hehs.size(); i ++)
		{	
			_heh = _hehs[i];
			if (!has_opposite_half_edge(_heh))
			{
				omheh = _heh;
				do 
				{
					mheh  = cw_opp_half_edge_handle(omheh);
					omheh = ccw_opp_half_edge_handle(mheh);
				} while (is_valid_handle(omheh));
				set_ccw_opposite_half_edge(_heh, mheh);
			}
		}
		return true;
	}
	/** set the half face handle */
	void THKernel::set_opp_half_face(HalfFaceHandle _hfh, HalfFaceHandle _ohfh, bool _double /* = true */)
	{
		TopologyKernel::set_opposite_half_face(_hfh, _ohfh, _double);
		if (_hfh.is_valid() && (!_ohfh.is_valid()))
		{
			std::vector<size_t> phs;
			OppFaceContainer::iterator it;
			for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(_hfh); chfv_it; ++ chfv_it)
			{
				phs.push_back(chfv_it.handle().idx());
			}
			std::sort(phs.begin(), phs.end());
			LessArray<size_t> faceIdx(phs);
			it = opp_faces_.find(faceIdx);
			if (it != opp_faces_.end())
			{
				it->second = _hfh.idx();
			}
		}
		
	}
	/** collect the opp half faces in opp_faces_ */
	void THKernel::opp_half_faces_collection()
	{
		ConstHalfFaceIter chf_end(half_faces_end());
		opp_faces_.clear();
		OppFaceContainer::iterator it;
		for (ConstHalfFaceIter chf_it = half_faces_begin(); chf_it != chf_end; ++ chf_it)
		{
			std::vector<size_t> phs;
			OppFaceContainer::iterator it;
			for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(chf_it); chfv_it; ++ chfv_it)
			{
				phs.push_back(chfv_it.handle().idx());
			}
			std::sort(phs.begin(), phs.end());
			LessArray<size_t> faceIdx(phs);
			it = opp_faces_.find(faceIdx);
			if (it != opp_faces_.end())
			{
				it->second = -1;
			}
			else
			{
				opp_faces_[faceIdx] = handle(*chf_it).idx();
			}
		}
	}
	/** remove the opposite  half faces in opp_faces_ */
	void THKernel::remove_opp_half_faces(HalfFaceHandle _hfh)
	{
		if (_hfh.is_valid())
		{
			std::vector<size_t> phs;
			OppFaceContainer::iterator it;
			for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(_hfh); chfv_it; ++ chfv_it)
			{
				phs.push_back(chfv_it.handle().idx());
			}
			std::sort(phs.begin(), phs.end());
			LessArray<size_t> faceIdx(phs);
			it = opp_faces_.find(faceIdx);
			if (it != opp_faces_.end())
			{
				if (it->second != -1)
				{
					opp_faces_.erase(it);
				}
				else
				{
					it->second = _hfh.idx();
				}
			}
		}
	}
	/** swap the hedron with topology */
	void THKernel::swap_hedron_with_topology(HedronHandle _h0, HedronHandle _h1)
	{
		std::vector<HalfFaceHandle> hfs0;
		std::vector<HalfFaceHandle> hfs1;
		std::vector<HalfFaceHandle> ohfs0;
		std::vector<HalfFaceHandle> ohfs1;
		std::vector<HalfEdgeHandle> hes0;
		std::vector<HalfEdgeHandle> hes1;
		std::vector<HalfEdgeHandle> ccwhes0;
		std::vector<HalfEdgeHandle> ccwhes1;
		std::vector<VertexHandle>   vhs0;
		std::vector<VertexHandle>   vhs1;
		size_t nhf(FaceCount[kernel_type_]);
		size_t nhe(EdgeCount[kernel_type_]);
		size_t nv(VertexCount[kernel_type_]);
		//--- copy the half faces, opposite half faces and ccw opposite half edges ---
		for (ConstHedronHalfFaceIter chhf_it = const_hedron_half_face_iter(_h0); chhf_it; ++ chhf_it)
		{
			hfs0.push_back(chhf_it.handle());
			ohfs0.push_back(opp_half_face_handle(hfs0.back()));
			for (ConstHalfFaceHalfEdgeIter chfhe_it = const_half_face_half_edge_iter(chhf_it.handle()); chfhe_it; ++ chfhe_it)
			{
				hes0.push_back(chfhe_it.handle());
				ccwhes0.push_back(ccw_opp_half_edge_handle(hes0.back()));
			}			
		}
		//--- copy the vertex handles ---
		for (ConstHedronVertexIter chv_it = const_hedron_vertex_iter(_h0); chv_it; ++ chv_it)
		{
			vhs0.push_back(chv_it.handle());
		}
		for (ConstHedronHalfFaceIter chhf_it = const_hedron_half_face_iter(_h1); chhf_it; ++ chhf_it)
		{
			hfs1.push_back(chhf_it.handle());
			ohfs1.push_back(opp_half_face_handle(hfs1.back()));
			for (ConstHalfFaceHalfEdgeIter chfhe_it = const_half_face_half_edge_iter(chhf_it.handle()); chfhe_it; ++ chfhe_it)
			{
				hes1.push_back(chfhe_it.handle());
				ccwhes1.push_back(ccw_opp_half_edge_handle(hes1.back()));
			}			
		}
		for (ConstHedronVertexIter chv_it = const_hedron_vertex_iter(_h1); chv_it; ++ chv_it)
		{
			vhs1.push_back(chv_it.handle());
		}

		//--- swap topological items ---
		swap_hedrons(_h0, _h1);
		h_properties_swap(_h0.idx(), _h1.idx());
		for (size_t i = 0; i < nhf; ++ i)
		{
			swap_half_faces(hfs0[i], hfs1[i]);
			hf_properties_swap(hfs0[i].idx(), hfs1[i].idx());
		}
		for (size_t i = 0; i < nhe; ++ i)
		{
			swap_half_edges(hes0[i], hes1[i]);
			he_properties_swap(hes0[i].idx(), hes1[i].idx());
		}
		//--- reset the opposite half face
		for (size_t i = 0; i < nhf; i ++)
		{
			set_opp_half_face(ohfs0[i], hfs1[i]);
			set_opp_half_face(ohfs1[i], hfs0[i]);
		}
		//--- reset the ccw half edge ---
		for (size_t i = 0; i < nhe; i ++)
		{
			set_ccw_opposite_half_edge(ccwhes0[i], hes1[i]);
			set_ccw_opposite_half_edge(ccwhes1[i], hes0[i]);
		}
		std::vector<HalfEdgeHandle>::const_iterator it;
		HalfEdgeHandle heh;
		
		//--- reset the start half edge ---
		for (size_t i = 0; i < nv; i ++)
		{
			heh = half_edge_handle(vhs0[i]);
			it = std::find(hes0.begin(), hes0.end(), heh);
			if (it != hes0.end())
			{
				set_vertex_half_edge(vhs0[i], hes1[it - hes0.begin()]);
			}
			heh = half_edge_handle(vhs1[i]);
			it = std::find(hes1.begin(), hes1.end(), heh);
			if (it != hes1.end())
			{
				set_vertex_half_edge(vhs1[i], hes0[it - hes1.begin()]);
			}			
		}
	}
	/** update the opp_faces_
	*   \param _hfh the half face 
	*   \param _removed true for removing from opp_faces_, false for not
	*   \return void
	*/
	void THKernel::update_opp_face(HalfFaceHandle _hfh, bool _removed)
	{
		std::vector<size_t> vhs;
		for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(_hfh); chfv_it; ++ chfv_it)
		{
			vhs.push_back(chfv_it.handle().idx());
		}
		std::sort(vhs.begin(), vhs.end());
		LessArray<size_t> less_array(vhs);
		OppFaceContainer::iterator it;
		it = opp_faces_.find(less_array);
		if (it != opp_faces_.end())
		{
			if ((it->second != -1) && _removed)
			{
				TopologyKernel::update_opp_face(it, HalfFaceHandle(-1));
			}
			else if ((it->second == -1) && _removed)
			{
				opp_faces_.erase(it);
			}
			// _removed == false ?
		}		
	}
	/** split 1-4 */
	VertexHandle THKernel::split(HedronHandle _hh, VertexHandle _vh)
	{
		assert(kernel_type() & 1 );
		std::vector<VertexHandle> vhs;
		vhs.reserve(4);
		for (ConstHedronVertexIter chv_it = const_hedron_vertex_iter(_hh); chv_it; ++ chv_it)
		{
			vhs.push_back(chv_it.handle());
		}
		delete_hedron(_hh);
		garbage_collection(true, true, true, false);
		std::vector<VertexHandle> h_idx;
		h_idx.resize(4);
		HedronHandle hh;
		std::vector<HedronHandle> hedrons;
		hedrons.reserve(4);
		//--- delete the hedron ---
		//delete_hedron(_hh);
		h_idx[0] = _vh;
		h_idx[1] = vhs[0];
		h_idx[2] = vhs[2];
		h_idx[3] = vhs[3];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		h_idx[0] = _vh;
		h_idx[1] = vhs[1];
		h_idx[2] = vhs[2];
		h_idx[3] = vhs[3];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		h_idx[0] = _vh;
		h_idx[1] = vhs[0];
		h_idx[2] = vhs[1];
		h_idx[3] = vhs[3];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		h_idx[0] = _vh;
		h_idx[1] = vhs[0];
		h_idx[2] = vhs[2];
		h_idx[3] = vhs[1];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		if (hedrons.size() == 4)
		{
			swap_hedron_with_topology(_hh, hedrons[0]);
			hedrons[0] = _hh;
		}
		
		return _vh;
	}
	/** split 1-3 */
	VertexHandle THKernel::split(HalfFaceHandle _hfh, VertexHandle _vh)
	{
		assert(kernel_type() & 1 );
		assert(_hfh.is_valid() && _vh.is_valid());
		VertexHandle cvh;
		HalfFaceHandle ohfh;
		HedronHandle dhh0;
		HedronHandle dhh1;
		dhh0 = hedron_handle(_hfh);
		ohfh = opp_half_face_handle(_hfh);
		dhh1 = hedron_handle(ohfh);
		std::vector<VertexHandle> vhs;
		std::vector<VertexHandle> ovhs;
		std::vector<VertexHandle> fvhs;
		vhs.reserve(4);
		for (ConstHedronVertexIter chv_it = const_hedron_vertex_iter(dhh0); chv_it; ++ chv_it)
		{
			vhs.push_back(chv_it.handle());
		}
		//--- store the vertices of the opposite hedron ---
		if (dhh1.is_valid())
		{
			ovhs.reserve(4);
			for (ConstHedronVertexIter chv_it = const_hedron_vertex_iter(dhh1); chv_it; ++ chv_it)
			{
				ovhs.push_back(chv_it.handle());
			}
		}
		fvhs.reserve(3);
		for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(_hfh); chfv_it; ++ chfv_it)
		{
			fvhs.push_back(chfv_it.handle());
		}
		for (size_t i = 0; i < vhs.size(); i ++)
		{
			if (std::find(fvhs.begin(), fvhs.end(), vhs[i]) == fvhs.end()) 
			{
				cvh = vhs[i];
				break;
			}
		}
		//--- delete the hedron ---
		delete_hedron(dhh0);
		if (dhh1.is_valid())
		{
			delete_hedron(dhh1);
		}		
		garbage_collection(true, true, true, false);
		std::vector<VertexHandle> h_idx;
		h_idx.resize(4);
		HedronHandle hh;
		std::vector<HedronHandle> hedrons;
		hedrons.reserve(4);
		h_idx[0] = cvh;
		h_idx[1] = _vh;
		h_idx[2] = fvhs[0];
		h_idx[3] = fvhs[1];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		h_idx[0] = cvh;
		h_idx[1] = _vh;
		h_idx[2] = fvhs[1];
		h_idx[3] = fvhs[2];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		h_idx[0] = cvh;
		h_idx[1] = _vh;
		h_idx[2] = fvhs[2];
		h_idx[3] = fvhs[0];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		
		//--- add another side ---
		if (dhh1.is_valid())
		{
			for (size_t i = 0; i < ovhs.size(); i ++)
			{
				if (std::find(fvhs.begin(), fvhs.end(), ovhs[i]) == fvhs.end()) 
				{
					cvh = ovhs[i];
					break;
				}
			}
			std::reverse(fvhs.begin(), fvhs.end());
			h_idx[0] = cvh;
			h_idx[1] = _vh;
			h_idx[2] = fvhs[0];
			h_idx[3] = fvhs[1];
			hh = add_hedron(h_idx);
			if (hh.is_valid())
			{
				hedrons.push_back(hh);
			}
			h_idx[0] = cvh;
			h_idx[1] = _vh;
			h_idx[2] = fvhs[1];
			h_idx[3] = fvhs[2];
			hh = add_hedron(h_idx);
			if (hh.is_valid())
			{
				hedrons.push_back(hh);
			}
			h_idx[0] = cvh;
			h_idx[1] = _vh;
			h_idx[2] = fvhs[2];
			h_idx[3] = fvhs[0];
			hh = add_hedron(h_idx);
			if (hh.is_valid())
			{
				hedrons.push_back(hh);
			}
		}

		if ((hedrons.size() == 3) && (!dhh1.is_valid()))
		{
			swap_hedron_with_topology(dhh0, hedrons[0]);
			hedrons[0] = dhh0;
		}
		else if ((hedrons.size() == 6) && (dhh1.is_valid()))
		{
			swap_hedron_with_topology(dhh0, hedrons[0]);
			hedrons[0] = dhh0;
			swap_hedron_with_topology(dhh1, hedrons[1]);
			hedrons[1] = dhh0;
		}

		return _vh;
	}
	/** split 1-2 */
	VertexHandle THKernel::split(HalfEdgeHandle _heh, VertexHandle _vh)
	{
		assert(kernel_type() & 1 );
		assert(_heh.is_valid() && _vh.is_valid());


		//--- to find all start vertices related to the start vertex ---//

		//---record some seperated elements ---//
		std::vector<std::vector<VertexHandle>> added_hedrons;
		std::vector<std::vector<size_t>> split_face_vertices;
		std::vector<std::vector<size_t>> not_split_face_vertices;
		std::vector<HalfFaceHandle> all_split_face_opp_half_faces;
		std::vector<HedronHandle>   split_hedrons;
		std::vector<HalfFaceHandle> split_half_faces;
		std::vector<HalfFaceHandle> split_opp_half_faces;
		std::vector<HalfFaceHandle> not_split_related_half_faces;
		std::vector<HalfEdgeHandle> same_direction_half_edges;
		std::vector<HalfEdgeHandle> prev_cw_half_edges;
		std::vector<HalfEdgeHandle> cw_next_half_edges;

		std::set<HalfEdgeHandle> all_start_half_edges;

		HalfEdgeHandle heh_it;
		HalfEdgeHandle heh_ccw_cw;
		HalfFaceHandle hfh;

		

		//--- find the same direction half edges around the same edge of the split half edge ---//
		heh_it = _heh;
		heh_ccw_cw = cw_opp_half_edge_handle(ccw_opp_half_edge_handle(_heh));

		all_start_half_edges.insert(_heh);
		same_direction_half_edges.push_back(_heh);

		split_hedrons.push_back(hedron_handle(_heh));

		while (heh_ccw_cw != _heh)
		{
			split_hedrons.push_back(hedron_handle(heh_ccw_cw));
			all_start_half_edges.insert(heh_ccw_cw);
			same_direction_half_edges.push_back(heh_ccw_cw);
			heh_it = heh_ccw_cw;
			heh_ccw_cw = cw_opp_half_edge_handle(ccw_opp_half_edge_handle(heh_it));
		}

		std::vector<VertexHandle> hedron_vertices;
		hedron_vertices.resize(4);

		//--- find the half edges related to the start vertex of the split half edge ---//
		for (size_t i = 0; i < same_direction_half_edges.size(); i++)
		{
			hedron_vertices[0] = _vh;
			hedron_vertices[1] = from_vertex_handle(same_direction_half_edges[i]);

			heh_it = cw_opp_half_edge_handle(prev_half_edge_handle(same_direction_half_edges[i]));
			prev_cw_half_edges.push_back(heh_it);
			all_start_half_edges.insert(heh_it);

			hedron_vertices[2] = to_vertex_handle(heh_it);

			//--- find the related half face and its valid opposite half faces ---//
			hfh = half_face_handle(heh_it);

			//--- collect the vertices ---//
			std::vector<size_t> phs;
			for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(hfh); chfv_it; ++ chfv_it)
			{
				phs.push_back(chfv_it.handle().idx());
			}
			split_face_vertices.push_back(phs);
			all_split_face_opp_half_faces.push_back(opp_half_face_handle(hfh));


			//--- collect its opposite half face ---//
			split_half_faces.push_back(hfh);

			hfh = opp_half_face_handle(hfh);
			if (hfh.is_valid())
			{
				split_opp_half_faces.push_back(hfh);
			}

			heh_it = next_half_edge_handle(cw_opp_half_edge_handle(same_direction_half_edges[i]));
			cw_next_half_edges.push_back(heh_it);
			all_start_half_edges.insert(heh_it);


			hedron_vertices[3] = to_vertex_handle(heh_it);

			added_hedrons.push_back(hedron_vertices);
		}

		for (size_t i = 0; i < same_direction_half_edges.size(); ++ i)
		{
			std::vector<size_t> phs;

			hfh = half_face_handle(same_direction_half_edges[i]);
			not_split_related_half_faces.push_back(hfh);

			for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(hfh); chfv_it; ++chfv_it)
			{
				phs.push_back(chfv_it.handle().idx());
			}

			not_split_face_vertices.push_back(phs);


			hfh = half_face_handle(cw_opp_half_edge_handle(same_direction_half_edges[i]));
			not_split_related_half_faces.push_back(hfh);

			phs.clear();

			for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(hfh); chfv_it; ++chfv_it)
			{
				phs.push_back(chfv_it.handle().idx());
			}

			not_split_face_vertices.push_back(phs);
		}

		//--- to change the related half edge of the original vertex ---//

	
		VertexHandle   svh;
		HalfEdgeHandle sheh;
		svh = from_vertex_handle(_heh);
		sheh = half_edge_handle(svh);

		std::set<HalfEdgeHandle>::const_iterator che_it;

		che_it = all_start_half_edges.find(sheh);
		//--- one of the half edges is related to the original vertex ---//
		if (che_it != all_start_half_edges.end())
		{
			std::vector<HalfEdgeHandle> out_half_edges;
			std::vector<HalfEdgeHandle>::const_iterator oche_it;
			out_half_edges = o_half_edges(svh);

			for (oche_it = out_half_edges.begin(); oche_it != out_half_edges.end(); ++oche_it)
			{
				che_it = all_start_half_edges.find(*oche_it);
				if (che_it == all_start_half_edges.end())
				{
					break;
				}
			}

			if (oche_it != out_half_edges.end())
			{
				set_vertex_half_edge(svh, *oche_it);
			}
			else
			{
				set_vertex_half_edge(svh, HalfEdgeHandle(-1));
			}
		}	

		//--- modify the start vertex of the half edges related to the new vertex ---//
		for (std::set<HalfEdgeHandle>::iterator it = all_start_half_edges.begin(); it != all_start_half_edges.end(); ++ it)
		{			
			set_start_vertex(*it, _vh);
		}	
		

		//--- modify the split outside half edges ---//
		
		HalfEdgeHandle prev_heh;
		HalfEdgeHandle prev_cw_heh;
		HalfEdgeHandle prev_cw_ccw_heh;

		HalfEdgeHandle cw_next_heh;
		HalfEdgeHandle cw_next_cw_heh;
		HalfEdgeHandle cw_next_cw_ccw_heh;
		std::vector<HalfEdgeHandle> outside_halfedges;
		for (size_t i = 0; i < same_direction_half_edges.size(); ++ i)
		{	
			//--- process the previous half edge ---//
			prev_heh         = prev_half_edge_handle(same_direction_half_edges[i]);
			prev_cw_heh      = cw_opp_half_edge_handle(prev_heh);
			prev_cw_ccw_heh  = ccw_opp_half_edge_handle(prev_cw_heh);

			//--- it is not the boundary half edge ---//
			if (prev_cw_ccw_heh != prev_heh)
			{
				outside_halfedges.push_back(prev_cw_heh);
				outside_halfedges.push_back(prev_cw_ccw_heh);
			}

			//--- process the cw next half edge ---
			cw_next_heh = next_half_edge_handle(cw_opp_half_edge_handle(same_direction_half_edges[i]));
			cw_next_cw_heh = cw_opp_half_edge_handle(cw_next_heh);
			cw_next_cw_ccw_heh = ccw_opp_half_edge_handle(cw_next_cw_heh);

			//--- it is not the boundary half edge ---//
			if (cw_next_cw_ccw_heh != cw_next_heh)
			{
				outside_halfedges.push_back(cw_next_cw_heh);
				outside_halfedges.push_back(cw_next_cw_ccw_heh);
			}
		} 

		//--- set the ccw half edges to -1 ---//
		for (size_t i = 0; i < outside_halfedges.size(); i++)
		{
			set_ccw_opposite_half_edge(outside_halfedges[i], HalfEdgeHandle(-1));
		}

		//--- reconstruct the ccw opposite half edges for the boundary half edges ---//
		HalfEdgeHandle cur_heh;
		HalfEdgeHandle cw_heh;
		HalfEdgeHandle cw_ccw_heh;

		for (size_t i = 0; i < outside_halfedges.size(); ++ i)
		{
			cur_heh = outside_halfedges[i];
			cw_heh = cw_opp_half_edge_handle(cur_heh);
			cw_ccw_heh = ccw_opp_half_edge_handle(cw_heh);
			while ((cw_ccw_heh.is_valid()) && (cw_ccw_heh != outside_halfedges[i]))
			{
				cur_heh = cw_ccw_heh;
				cw_heh = cw_opp_half_edge_handle(cur_heh);
				cw_ccw_heh = ccw_opp_half_edge_handle(cw_heh);
			}

			if (cw_ccw_heh != outside_halfedges[i])
			{
				set_ccw_opposite_half_edge(outside_halfedges[i], cw_heh);
			}
		}

		
		
		//--- reconstruct the opposite half face, and make it as the boundary half face ---//
		std::vector<size_t> phs;
		OppFaceContainer::iterator it;
		for (size_t i = 0; i < split_half_faces.size(); ++ i)
		{
			set_opposite_half_face(split_half_faces[i], HalfFaceHandle(-1));


		}

		for (size_t i = 0; i < split_opp_half_faces.size(); ++ i)
		{
			set_opposite_half_face(split_opp_half_faces[i], HalfFaceHandle(-1));
		}
			
		//--- modify the opposite map ---//
		for (size_t i = 0; i < split_face_vertices.size(); ++ i)
		{
			phs = split_face_vertices[i];

			std::sort(phs.begin(), phs.end());
			LessArray<size_t> face_idx(phs);
			it = opp_faces_.find(face_idx);
			if (it != opp_faces_.end())
			{
				if (!all_split_face_opp_half_faces[i].is_valid())
				{
					opp_faces_.erase(it);					
				}
				else
				{
					it->second = all_split_face_opp_half_faces[i].idx();
				}
			}
			else
			{
				opp_faces_[face_idx] = -1;
			}

		}

		for (size_t i = 0; i < split_half_faces.size(); ++ i)
		{
			phs.clear();
			for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(split_half_faces[i]); chfv_it; ++chfv_it)
			{
				phs.push_back(chfv_it.handle().idx());
			}

			std::sort(phs.begin(), phs.end());
			LessArray<size_t> face_idx(phs);
			opp_faces_[face_idx] = split_half_faces[i].idx(); 
		}

		for (size_t i = 0; i < not_split_face_vertices.size(); ++ i)
		{
			phs = not_split_face_vertices[i];

			std::sort(phs.begin(), phs.end());
			LessArray<size_t> face_idx(phs);
			
			it = opp_faces_.find(face_idx);
			if (it != opp_faces_.end())
			{
				opp_faces_.erase(it);
			}
		}

		for (size_t i = 0; i < not_split_related_half_faces.size(); ++i)
		{
			phs.clear();

			for (ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(not_split_related_half_faces[i]); chfv_it; ++chfv_it)
			{
				phs.push_back(chfv_it.handle().idx());
			}

			std::sort(phs.begin(), phs.end());
			LessArray<size_t> face_idx(phs);

			if (opp_half_face_handle(not_split_related_half_faces[i]).is_valid())
			{
				opp_faces_[face_idx] = -1;
			}
			else
			{
				opp_faces_[face_idx] = not_split_related_half_faces[i].idx();
			}
		}

		for (size_t i = 0; i < added_hedrons.size(); ++ i)
		{
			add_hedron(added_hedrons[i]);
		}

		return _vh;
	}
	/** Half edge collapse: collapse the from-vertex of _heh into 
	*   the to-vertex.
	*   Needs vertex/edge/half-face/hedron status attributes to delete the generated items.
	*   Before collapsing the half edges, it requires to check the topological consistences
	*   using is_collapse_ok()
	*/
	void THKernel::collapse(HalfEdgeHandle _heh)
	{
		if (!is_collapse_ok(_heh))
		{
			std::cerr << "cannot collapse this half edge...\n";
			return;
		}
		std::set<HedronHandle> deleted_hedrons;
		for (ConstHalfEdgeHedronIter cheh_it = const_half_edge_hedron_iter(_heh); cheh_it; ++ cheh_it)
		{
			deleted_hedrons.insert(cheh_it.handle());
		}
		VertexHandle vh0;
		VertexHandle vh1;
		vh0 = from_vertex_handle(_heh);
		vh1 = to_vertex_handle(_heh);
		std::vector<HedronHandle> modified_hedrons;
		std::vector<HedronHandle> to_hedrons;
		/** get the star hedrons of the from-vertex */
		modified_hedrons = vertex_star_hedrons(vh0);
		/** get the star hedrons of the to-vertex   */
		to_hedrons = vertex_star_hedrons(vh1);


		std::vector<HalfEdgeHandle> modified_hes;
		std::vector<HalfFaceHandle> modified_hfs;
		std::set<HalfFaceHandle> deleted_faces;
		std::vector<HedronHandle>::iterator h_it;
		for (std::set<HedronHandle>::iterator it = deleted_hedrons.begin(); it != deleted_hedrons.end(); ++ it)
		{
			/** collect the deleted half faces */
			for (HedronHalfFaceIter hhf_it = hedron_half_face_iter(*it); hhf_it; ++ hhf_it)
			{
				deleted_faces.insert(hhf_it.handle());
			}

		    /** exclude the deleted hedrons */
			h_it = std::find(modified_hedrons.begin(), modified_hedrons.end(), *it);
			if (h_it != modified_hedrons.end())
			{
				modified_hedrons.erase(h_it);
			}
			h_it = std::find(to_hedrons.begin(), to_hedrons.end(), *it);
			if (h_it != to_hedrons.end())
			{
				to_hedrons.erase(h_it);
			}
		}
		
		for (size_t i = 0; i < modified_hedrons.size(); i ++)
		{	
			/** record the modified half faces */
			for (HedronHalfFaceIter hhf_it = hedron_half_face_iter(modified_hedrons[i]); hhf_it; ++ hhf_it)
			{
				if (deleted_faces.find(opp_half_face_handle(hhf_it.handle())) != deleted_faces.end())
				{
					modified_hfs.push_back(hhf_it.handle());
					for (HalfFaceHalfEdgeIter hfhe_it = half_face_half_edge_iter(hhf_it.handle()); hfhe_it; ++ hfhe_it)
					{
						modified_hes.push_back(hfhe_it.handle());
					}
				}
			}

			/** modified the start vertex of the modified half edges */
			for (HedronHalfEdgeIter hhe_it = hedron_half_edge_iter(modified_hedrons[i]); hhe_it; ++ hhe_it)
			{
				if (from_vertex_handle(hhe_it.handle()) == vh0)
				{
					set_start_vertex(hhe_it.handle(), vh1);
				}
			}			
		}

		/** record the half edges of the to vertex in the related half faces */
		for (size_t i = 0; i < to_hedrons.size(); i ++)
		{	
			/** record the modified half faces */
			for (HedronHalfFaceIter hhf_it = hedron_half_face_iter(to_hedrons[i]); hhf_it; ++ hhf_it)
			{
				if (deleted_faces.find(opp_half_face_handle(hhf_it.handle())) != deleted_faces.end())
				{
					modified_hfs.push_back(hhf_it.handle());
					for (HalfFaceHalfEdgeIter hfhe_it = half_face_half_edge_iter(hhf_it.handle()); hfhe_it; ++ hfhe_it)
					{
						modified_hes.push_back(hfhe_it.handle());
					}
				}
			}
		}

		/** delete hedrons */
		for (std::set<HedronHandle>::iterator it = deleted_hedrons.begin(); it != deleted_hedrons.end(); ++ it)
		{
			delete_hedron(*it);
		}
		status(vh0).set_deleted(true);

		for (size_t i = 0; i < modified_hes.size(); i ++)
		{
			set_ccw_opposite_half_edge(modified_hes[i], HalfEdgeHandle(-1), false);
		}
		/** rebuild the opposite half faces and ccw opposite half edges */
		build_opposite_half_faces(modified_hfs);
		build_opposite_half_edges(modified_hes);

		garbage_collection();
	}
	/** Half face collapse: collapse the half face of two adjacent hedrons  
	*   Needs vertex/edge/half-face/hedron status attributes to delete the generated items.
	*   Before collapsing the half edges, it requires to check the topological consistences
	*   using is_collapse_ok()
	*/
	void THKernel::collapse(HalfFaceHandle _hfh)
	{
		if (!is_collapse_ok(_hfh))
		{
			std::cerr << "cannot collapse this half edge...\n";
			return ;
		}
		
	}
	/** return if collapsing half edge _heh is ok or it would lead to
	*   topological inconsistencies.
	*/
	bool THKernel::is_collapse_ok(HalfEdgeHandle _heh)
	{
		std::set<HedronHandle> deleted_hedrons;
		for (ConstHalfEdgeHedronIter cheh_it = const_half_edge_hedron_iter(_heh); cheh_it; ++ cheh_it)
		{
			deleted_hedrons.insert(cheh_it.handle());
		}
		VertexHandle vh0;
		VertexHandle vh1;
		vh0 = from_vertex_handle(_heh);
		vh1 = to_vertex_handle(_heh);
		std::vector<HedronHandle> from_hedrons;
		std::vector<HedronHandle> to_hedrons;
		/** get the star hedrons of the from-vertex */
		from_hedrons = vertex_star_hedrons(vh0);
		/** get the star hedrons of the to-vertex   */
		to_hedrons = vertex_star_hedrons(vh1);

		std::set<HalfFaceHandle> deleted_faces;
		std::vector<HedronHandle>::iterator h_it;
		for (std::set<HedronHandle>::iterator it = deleted_hedrons.begin(); it != deleted_hedrons.end(); ++ it)
		{
			/** collect the deleted half faces */
			for (HedronHalfFaceIter hhf_it = hedron_half_face_iter(*it); hhf_it; ++ hhf_it)
			{
				deleted_faces.insert(hhf_it.handle());
			}

			/** exclude the deleted hedrons */
			h_it = std::find(from_hedrons.begin(), from_hedrons.end(), *it);
			if (h_it != from_hedrons.end())
			{
				from_hedrons.erase(h_it);
			}
			h_it = std::find(to_hedrons.begin(), to_hedrons.end(), *it);
			if (h_it != to_hedrons.end())
			{
				to_hedrons.erase(h_it);
			}
		}

		
		std::set<HalfFaceHandle> to_hfs;
		std::set<HalfFaceHandle> from_hfs;

		/** collect the half faces which are adjacent to the deleted hedrons and contain the from-vertex*/
		for (size_t i = 0; i < from_hedrons.size(); i ++)
		{
			for (ConstHedronHalfFaceIter chhf_it = const_hedron_half_face_iter(from_hedrons[i]); chhf_it; ++ chhf_it)
			{
				if (deleted_faces.find(opp_half_face_handle(chhf_it.handle())) != deleted_faces.end())
				{
					from_hfs.insert(chhf_it.handle());
				}				
			}
		}

		/** collect the half faces which are adjacent to the deleted hedrons and contain the to-vertex*/
		for (size_t i = 0; i < to_hedrons.size(); i ++)
		{
			for (ConstHedronHalfFaceIter chhf_it = const_hedron_half_face_iter(to_hedrons[i]); chhf_it; ++ chhf_it)
			{
				if (deleted_faces.find(opp_half_face_handle(chhf_it.handle())) != deleted_faces.end())
				{
					to_hfs.insert(chhf_it.handle());
				}				
			}
		}

		/** collect the index of the to-half faces */
		std::set<LessArray<__int64>> opp_arrays;
		std::set<LessArray<__int64>>::iterator opp_it;
		std::vector<__int64> face_idx;
		for (std::set<HalfFaceHandle>::iterator it = to_hfs.begin(); it != to_hfs.end(); ++ it)
		{
			face_idx.clear();
			for (ConstHalfFaceVertexIter hfv_it = const_half_face_vertex_iter(*it); hfv_it; ++ hfv_it)
			{
				face_idx.push_back(hfv_it.handle().idx());
			}
			std::sort(face_idx.begin(), face_idx.end());
			opp_arrays.insert(LessArray<__int64>(face_idx));
		}
		for (std::set<HalfFaceHandle>::iterator it = from_hfs.begin(); it != from_hfs.end(); ++ it)
		{
			face_idx.clear();
			for (ConstHalfFaceVertexIter hfv_it = const_half_face_vertex_iter(*it); hfv_it; ++ hfv_it)
			{
				if (hfv_it.handle() == vh0)
				{
					face_idx.push_back(vh1.idx());
				}
				else
				{
					face_idx.push_back(hfv_it.handle().idx());
				}
			}
			std::sort(face_idx.begin(), face_idx.end());
			opp_it = opp_arrays.find(LessArray<__int64>(face_idx));
			if (opp_it == opp_arrays.end())
			{
				return false;
			}
		}
		
		

		return true;
	}
	/** return if collapsing half face _hfh is ok or it would lead to
	*   topological inconsistencies.
	*/
	bool THKernel::is_collapse_ok(HalfFaceHandle _hfh)
	{
		return true;
	}

	//-----------------------------------------------------------------------------------------------------------------


	/**
	*                       
	*                       |y
	*						|
	*						|
	*						|
	*					 010|_________________________011
	*					   /|                        /|
	*					  / |                       / |
	*					 /  |                      /  |
	*					/   |                     /   |
	*			   110 /____|____________________/111 |
	*				  |  	|                    |    |
	*				  |  000|____________________|____|________________x
	*				  |    /                     |    /001
	*				  |   /                      |   /                                  
	*				  |  /                       |  /
	*				  | /                        | /
	*              100|/_________________________|/101
	*			      /
	*				 /
	*			    /
	*			   /z
	*			    
	*			    
	*					 
	*
	*/

	
	/**

	Hexahedron

	Face 0 : back
	0 : 0-->2
	1 : 2-->3
	2 : 3-->1
	3 : 1-->0

	Face 1 : left
	4 : 0-->4
	5 : 4-->6
	6 : 6-->2
	7 : 2-->0

	Face 2 : bottom
	8 :  0-->1
	9 :  1-->5
	10 : 5-->4
	11 : 4-->0

	Face 3 : right
	12 : 1-->3
	13 : 3-->7
	14 : 7-->5
	15 : 5-->1

	Face  4 : top 
	16 : 2-->6
	17 : 6-->7
	18 : 7-->3
	19 : 3-->2

	Face 5 : front
	20 : 4-->5
	21 : 5-->7
	22 : 7-->6
	23 : 6-->4

	*/



	/**
	*                          1
	*                         /|\
	*                        / | \
	*                       /  |  \
	*                      /   |   \
	*                     /    |    \
	*                    /     |     \
	*                  0-------|-------3
	*                    \     |     /
	*                     \    |    /
	*                      \   |   /
	*                       \  |  /
	*                        \ | /
	*                         \|/
	*                          2
	*/

	/**


	
	Tetrahedron

	Face 0 : 1-2-3
	0 : 1-->2
	1 : 2-->3
	2 : 3-->1


	Face 1 : 0-3-2
	3 : 0-->3
	4 : 3-->2
	5 : 2-->0

	Face 2 : 0-1-3
	6 : 0-->1
	7 : 1-->3
	8 : 3-->0

	Face 3 : 0-2-1
	9 : 0-->2
	10 : 2-->1
	11 : 1-->0

	*/


//---------------------------------------------------------------------------------------------------------------------
}