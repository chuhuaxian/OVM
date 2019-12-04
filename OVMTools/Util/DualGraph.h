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

#ifndef _OVM_DUAL_GRAPH_
#define _OVM_DUAL_GRAPH_

#include <set>
#include <map>


namespace OVM
{
	namespace Util
	{
	//-----------------------------------------------------------------------------------------------------------------
		template <typename MeshT>
		class DualGraph
		{
		public:
			/** constructor
			*   \param in _mesh the mesh 
			*/
			DualGraph(MeshT * _mesh)
			{
				assert(_mesh);
				mesh_ = _mesh;
				hedrons_.clear();
				typename MeshT::ConstHedronIter h_end(_mesh->hedrons_end());
				for (typename MeshT::ConstHedronIter h_it = mesh_->hedrons_begin(); h_it != h_end; ++ h_it)
				{
					hedrons_.insert(mesh_->handle(*h_it));
				}				
			}

			/** constructor
			*   \param in _mesh the mesh
			*   \param in _hedrons the hedrons need to be constructed the corresponding dual graph
			*/
			DualGraph(MeshT * _mesh, const std::set<typename MeshT::HedronHandle> & _hedrons)
			{
				assert(_mesh);
				mesh_ = _mesh;
				hedrons_ = _hedrons;
			}

			~DualGraph()
			{
			}
		public:
			/** generate the dual graph of the hedrons
			*   \return the dual graph of the hedrons represented in adjacent map
			*/
			std::map<typename MeshT::HedronHandle, std::set<typename MeshT::HedronHandle>> generate_dual_graph()
			{
				std::map<typename MeshT::HedronHandle, std::set<typename MeshT::HedronHandle>> g;
				std::set<typename MeshT::HedronHandle> s;
				std::set<typename MeshT::HedronHandle>::const_iterator it;

				for (it = hedrons_.begin(); it != hedrons_.end(); ++it)
				{
					typename MeshT::ConstHedronHedronIter chh_it;
					s.clear();
					for (chh_it = mesh_->const_hedron_hedron_iter(*it); chh_it; ++ chh_it)
					{
						if (hedrons_.find(chh_it.handle()) != hedrons_.end())
						{
							s.insert(chh_it.handle());
						}
					}
					g.insert(std::make_pair(*it, s));
				}
				
				return g;
			}
		//-------------------------------------------------------------------------------------------------------------
		private:
			MeshT * mesh_;
			std::set<typename MeshT::HedronHandle> hedrons_;
		};
	//-----------------------------------------------------------------------------------------------------------------
	}
}
#endif