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

#ifndef _OVM_MESH_IO_H_
#define _OVM_MESH_IO_H_

#include <ovm/OVMCore/system/config.h>
#include <OVM/OVMCore/IO/Options.h>

#if defined(_OVM_TOPOLOGY_KERNEL_H_)
#error "Include MeshIO.h before including a mesh type!"
#endif





#include <OVM/OVMCore/IO/IOManager.h>
#include <fstream>
//#include <cstdio>
#include <string>
#include <vector>


namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	namespace IO
	{	
		///** read a mesh file. the file format is determined by the file extension.
		//*   \param _mesh the mesh
		//*   \param _filename the file name
		//*   \param _clear true for release the resources, false for not
		//*/
		//template < class MeshT >
		//bool read_mesh(MeshT & _mesh, const std::string & _filename, bool _clear = true)
		//{
		//	if (_clear)
		//	{
		//		_mesh.clear();
		//	}
		//	return IOManager().read_mesh(_mesh, _filename);
		//	//true;
		//}

		///** read a mesh file. the file format is determined by the file extension.
		//*   \param _mesh the mesh
		//*   \param _filename the file name
		//*   \param _clear true for release the resources, false for not
		//*/
		//template < class MeshT >
		//bool write_mesh(const MeshT & _mesh, const std::string & _filename)
		//{
		//	return IOManager().write_mesh(_mesh, _filename);
		//	//true;
		//}

		/** read a mesh file. the file format is determined by the file extension.
		*   \param _mesh the mesh
		*   \param _filename the file name
		*   \param _clear true for release the resources, false for not
		*/
		template < class MeshT >
		bool read_mesh(MeshT & _mesh, const std::string & _filename, const Options & _opt = Options::Default, bool _clear = true)
		{
			if (_clear)
			{
				_mesh.clear();
			}
			return IOManager().read_mesh(_mesh, _filename, _opt);
			//true;
		}

		/** read a mesh file. the file format is determined by the file extension.
		*   \param _mesh the mesh
		*   \param _filename the file name
		*   \param _clear true for release the resources, false for not
		*/
		template < class MeshT >
		bool write_mesh(const MeshT & _mesh, const std::string & _filename, const Options & _opt = Options::Default)
		{
			return IOManager().write_mesh(_mesh, _filename, _opt);
			//true;
		}


//---------------------------------------------------------------------------------------------------------------------

	} // namespace IO

//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM 
#endif