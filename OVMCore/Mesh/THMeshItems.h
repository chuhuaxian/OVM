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

#ifndef _OVM_TH_MESH_ITEMS_H_
#define _OVM_TH_MESH_ITEMS_H_

#include <OVM/OVMCore/system/config.h>
#include <OVM/OVMCore/Mesh/Handles.h>
#include <OVM/OVMCore/Mesh/TopologyItems.h>

namespace OVM
{
	template <class Traits>
	class THMeshItems
	{
	public:
		typedef typename Traits::Point  Point;
		typedef typename Point::Scalar  Scalar;
		typedef typename Traits::Normal Normal;
		typedef typename OVM::BaseHandle     BaseHandle;
		typedef typename OVM::VertexHandle   VertexHandle;
		typedef typename OVM::HalfEdgeHandle HalfEdgeHandle;
		typedef typename OVM::HalfFaceHandle HalfFaceHandle;
		typedef typename OVM::HedronHandle   HedronHandle;	

	public:
		enum Attribs
		{			
			HAttrib  = Traits::HAttributes,
			HFAttrib = Traits::HFAttributes,
			HEAttrib = Traits::HEAttributes,
			VAttrib  = Traits::VAttributes
		};
		

		typedef OVM::Vertex   Vertex;
		typedef OVM::HalfEdge HalfEdge;
		typedef OVM::HalfFace HalfFace;
		typedef OVM::Hedron   Hedron;
	};
}
#endif