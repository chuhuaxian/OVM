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


#ifndef _OVM_HANDLES_H_
#define _OVM_HANDLES_H_

#include <OVM/OVMCore/Mesh/BaseHandle.h>

/// namespace OVM
namespace OVM
{
	//---------------------------------------------------------------------------------------------------------------------

	/// Handle for a vertex entity
	struct VertexHandle : public BaseHandle
	{
		explicit VertexHandle(__int64 _idx = -1) : BaseHandle(_idx) 
		{
		}

	};

	/// Handle for a HalfEdgeTH entity
	struct HalfEdgeHandle : public BaseHandle
	{
		explicit HalfEdgeHandle(__int64 _idx = -1) : BaseHandle(_idx) 
		{
		}
	};

	/// Handle for a edge entity
	struct EdgeHandle : public BaseHandle
	{
		explicit EdgeHandle(__int64 _idx = -1) : BaseHandle(_idx) 
		{
		}
	};

	/// Handle for a HalfFace entity
	struct HalfFaceHandle : public BaseHandle
	{
		explicit HalfFaceHandle(__int64 _idx = -1) : BaseHandle(_idx)
		{
		}
	};

	/// Handle for a face entity
	struct FaceHandle : public BaseHandle
	{
		explicit FaceHandle(__int64 _idx = -1) : BaseHandle(_idx) 
		{
		}
	};

	/// Handle for a point
	struct PointHandle : public BaseHandle
	{
		explicit PointHandle(__int64 _idx = -1) : BaseHandle(_idx)
		{
		}
	};

	/// Handle for the polyhedron 
	struct PolyhedronHandle : public BaseHandle
	{
		explicit PolyhedronHandle(__int64 _idx = -1) : BaseHandle(_idx)
		{
		}
	};


//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM
//---------------------------------------------------------------------------------------------------------------------

#endif // _OVM_HANDLES_H_ defined
