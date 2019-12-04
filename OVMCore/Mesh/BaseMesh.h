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



#ifndef _OVM_BASE_MESH_H_
#define _OVM_BASE_MESH_H_


#include <OVM/OVMCore/Mesh/Handles.h>
#include <OVM/OVMCore/Geometry/OVMVector.h>
#include <OVM/OVMCore/Mesh/Traits.h>

#include <map>
#include <vector>
#include <algorithm>

namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	/** the base mesh class for all volumetric mesh
	*   the traits is default traits, users can define 
	*   their traits though inheriting from default traits
	*/
	template < class Traits = DefaultTraits >
	class BaseMesh
	{
	//-------Traits------//
	public:
		typedef typename Traits::Point  Point;
		typedef typename Traits::Normal Normal;
		typedef typename Point::Scalar  Scalar;
	public:
		virtual ~BaseMesh()
		{
		}

	//	typedef std::vector<Point>            PContainer;
	//	typedef std::vector<VertexHandle>     VContainer;
	//	typedef std::vector<PolyhedronHandle> HContainer;
	//	
	////-----------------------------------------------------------------------------------------------------------------
	//public:
	//	BaseMesh(unsigned int _mesh_type = 0x0001)
	//	{
	//		mesh_type_ = _mesh_type;
	//	}
		//virtual ~BaseMesh()
	//	{
	//		pc_.clear();
	//		vc_.clear();
	//		hc_.clear();
	//	}
	////-----------------------------------------------------------------------------------------------------------------
	//public:
	//	/** get the mesh type */
	//	unsigned int mesh_type()
	//	{
	//		return mesh_type_;
	//	}		
	//	
	//	/** set the points */
	//	void set_points(const PContainer & _pc)
	//	{		
	//		pc_.resize(_pc.size());
	//		std::copy(_pc.begin(), _pc.end(), pc_);
	//	}
	//	/** get the point container */
	//	const PContainer & get_points() const
	//	{
	//		return pc_;
	//	}
	//	/** set the vertices */
	//	void set_vertics(const VContainer & _vc)
	//	{		
	//		vc_.resize(_vc.size());
	//		std::copy(_vc.begin(), _vc.end(), vc_);
	//	}
	//	/** get the vertex container */
	//	const PContainer & get_vertices() const
	//	{
	//		return vc_;
	//	}
	////-----------------------------------------------------------------------------------------------------------------
	//protected:
	//	/// type of mesh, 0x0001 for tetrahedral mesh, 0x0002 for hexahedral mesh
	//	unsigned int mesh_type_;
	//protected:
	//	PContainer pc_;
	//	VContainer vc_;
	//	HContainer hc_;
	};
//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM
//---------------------------------------------------------------------------------------------------------------------
#endif