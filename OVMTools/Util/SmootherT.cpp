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
* OpenVolumetricMesh (OVM) library, Copyright (C) 2010-2012, Chuhua Xian                                              *
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

#define _OVM_SMOOTHER_CPP_
#include <ovm/OVMTools/Util/SmootherT.h>
#include <map>

namespace OVM
{
	namespace Util
	{
//---------------------------------------------------------------------------------------------------------------------
		template < class MeshT >
		void SmootherT<MeshT>::smooth(unsigned int _n)
		{
			if (!mesh_.has_vertices_status())
			{
				mesh_.request_vertices_status();
			}
			std::map<MeshT::VertexHandle, MeshT::Point> v_map;
			MeshT::VertexIter v_end(mesh_.vertices_end());
			MeshT::Point d;
			MeshT::VertexHandle vh;
			for (unsigned int i = 0; i < _n; i ++)
			{
				for (MeshT::VertexIter v_it = mesh_.vertices_begin(); v_it != v_end; ++ v_it)
				{
					vh = mesh_.handle(*v_it);
					/** if the status of the vertex is not locked, use the laplacian smoothing algorithm to 
					*   to smooth it
					*/
					if (!mesh_.status(vh).locked())
					{
						d = MeshT::Point(0.0, 0.0, 0.0);
						for (MeshT::ConstVertexVertexIter cvv_it = mesh_.const_vertex_vertex_iter(vh); cvv_it; ++ cvv_it)
						{
							d += mesh_.point(cvv_it.handle());
						}
						d /= mesh_.valence(vh);
						v_map[vh] = d;
					}
				}			
				for (std::map<MeshT::VertexHandle, MeshT::Point>::const_iterator c_it = v_map.begin(); c_it != v_map.end(); ++ c_it)
				{
						mesh_.set_point(c_it->first, c_it->second);
				}
				
			}
			
		}
//---------------------------------------------------------------------------------------------------------------------
	}
}