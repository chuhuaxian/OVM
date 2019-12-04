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
#include <OVM/OVMCore/Mesh/TopologyKernel.h>

#include <algorithm>

namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	/** set the opposite half face handle */
	void TopologyKernel::set_opposite_half_face(const HalfFaceHandle & _hfh, const HalfFaceHandle & _ohfh, bool _double /* = true */)
	{
		if (is_valid_handle(_hfh))
		{
			half_face(_hfh).opp_hfh_ = _ohfh;
		}
		if (is_valid_handle(_ohfh) && _double)
		{
			half_face(_ohfh).opp_hfh_ = _hfh;
		}		
	}
	/** set the opposite half edge handle */
	void TopologyKernel::set_ccw_opposite_half_edge(const HalfEdgeHandle & _heh, const HalfEdgeHandle & _ohfh, bool _double /* = true */)
	{
		if (is_valid_handle(_heh))
		{
			half_edge(_heh).opp_heh_ = _ohfh;
		}
		if (is_valid_handle(_ohfh) && _double)
		{
			half_edge(_ohfh).opp_heh_ = _heh;
		}
	}
	/** set the first half face handle of the hedron */
	void TopologyKernel::set_first_half_face_handle(const HedronHandle & _hh, const HalfFaceHandle & _hfh)
	{
		if (is_valid_handle(_hh) && is_valid_handle(_hfh))
		{
			hedrons_[_hh].hfh_ = _hfh;
		}
		
	}
	/** set the half edge handle for vertex */
	void TopologyKernel::set_vertex_half_edge(const VertexHandle & _vh, const HalfEdgeHandle & _heh)
	{
		if (is_valid_handle(_vh))
		{
			vertex(_vh).heh_ = _heh;
		}
	}
	/** set the half face handle for half edge */
	void TopologyKernel::set_half_face(const HalfEdgeHandle & _heh, const HalfFaceHandle & _hfh)
	{
		if (is_valid_handle(_heh))
		{
			half_edge(_heh).fh_ = _hfh;
		}
	}
	/** set the start vertex of a half edge */
	void TopologyKernel::set_start_vertex(const HalfEdgeHandle & _heh, const VertexHandle & _vh)
	{
		if (is_valid_handle(_heh))
		{
			half_edge(_heh).vh_ = _vh;

		}
		
	}
	
	/** check if the input half face has opposite half face */
	bool TopologyKernel::has_opposite_half_face(const HalfFaceHandle & _hfh) const 
	{
		if (is_valid_handle(_hfh))
		{
			return (is_valid_handle(half_face(_hfh).opp_hfh_));
		}
		return false;
	}
	/** check if the input half face has opposite half face */
	bool TopologyKernel::has_opposite_half_face(const HalfFace & _hf) const
	{
		return (is_valid_handle(_hf.opp_hfh_));
	}

	/** check if the input half edge has opposite half edge */
	bool TopologyKernel::has_opposite_half_edge(const HalfEdgeHandle & _heh) const 
	{
		if (is_valid_handle(_heh))
		{
			return (is_valid_handle(half_edge(_heh).opp_heh_));
		}
		return false;
	}
	/** check if the input half edge has opposite half edge */
	bool TopologyKernel::has_opposite_half_edge(const HalfEdge & _he) const
	{
		return (is_valid_handle(_he.opp_heh_));
	}
	
	//-----------------------------------------------------------------------------------------------------------------
	/** retrieve the half face handle of a half edge */
	HalfFaceHandle TopologyKernel::half_face_handle(const HalfEdge & _he) const
	{
		return _he.fh_;
	}
	/** retrieve the half face handle of a half edge */
	HalfFaceHandle TopologyKernel::half_face_handle(const HalfEdgeHandle & _heh) const
	{
		if (is_valid_handle(_heh))
		{
			return half_edge(_heh).fh_;
		}
		return HalfFaceHandle(-1);
	}
	/** retrieve the half edge handle of a vertex */
	HalfEdgeHandle TopologyKernel::half_edge_handle(const Vertex & _v) const
	{
		return _v.heh_;
	}
	/** retrieve the half edge handle of a vertex */
	HalfEdgeHandle TopologyKernel::half_edge_handle(const VertexHandle & _vh) const
	{
		if (is_valid_handle(_vh))
		{
			return vertex(_vh).heh_;
		}
		return HalfEdgeHandle(-1);
		
	}
	//-----------------------------------------------------------------------------------------------------------------
	/** retrieve the opposite half face handle */
	HalfFaceHandle TopologyKernel::opp_half_face_handle(const HalfFaceHandle & _hfh) const
	{
		return half_face(_hfh).opp_hfh_;
	}
	/** retrieve the first half edge handle of the half face */
	HalfEdgeHandle TopologyKernel::first_half_edge_handle(const HalfFaceHandle & _hfh) const
	{
		return half_face(_hfh).heh_;
	}
	/** retrieve the opposite half edge handle */
	HalfEdgeHandle TopologyKernel::ccw_opp_half_edge_handle(const HalfEdgeHandle & _heh)  const
	{
		if (is_valid_handle(_heh))
		{
			return half_edge(_heh).opp_heh_;
		}
		return HalfEdgeHandle(-1);
	}
	/** retrieve the start vertex handle of the half edge */
	VertexHandle TopologyKernel::from_vertex_handle(const HalfEdgeHandle & _heh) const
	{
		return half_edge(_heh).vh_;
	}
	//-----------------------------------------------------------------------------------------------------------------

	/** add a new vertex into the kernel 
	*   \return the handle  of the vertex
	*/
	VertexHandle TopologyKernel::new_vertex() 
	{
		vertices_.push_back(Vertex());
		v_properties_resize(n_vertices());

		return handle(vertices_.back());
	}
	/** add a new half edge into the kernel
	*   \return the handle of the half edge
	*/
	HalfEdgeHandle TopologyKernel::new_half_edge(HalfEdge _he) 
	{
		half_edges_.push_back(_he);
		he_properties_resize(n_half_edges());
		return handle(half_edges_.back());
	}
	/** add a new half face into the kernel
	*   \return the handle of the half face
	*/
	HalfFaceHandle TopologyKernel::new_half_face(HalfFace _hf) 
	{
		half_faces_.push_back(_hf);
		hf_properties_resize(n_half_faces());
		return handle(half_faces_.back());
	}
	/** add a new hedron into the kernel
	*   \return the hedron handle of the hedron
	*/
	HedronHandle TopologyKernel::new_hedron(Hedron _h) 
	{
		hedrons_.push_back(_h);
		h_properties_resize(n_hedrons());
		return handle(hedrons_.back());
	}
	/** pop back the last hedron */
	void TopologyKernel::hedrons_pop_back()
	{
		hedrons_.pop_back();
	}
	/** pop back the last face */
	void TopologyKernel::half_faces_pop_back()
	{
		half_faces_.pop_back();
	}
	/** pop back the last half edge */
	void TopologyKernel::half_edges_pop_back()
	{
		half_edges_.pop_back();
	}
	/** pop back the last vertex */
	void TopologyKernel::vertices_pop_back()
	{
		vertices_.pop_back();
	}

	/** clear the containers */
	void TopologyKernel::clear()
	{
		v_properties_clear();
		he_properties_clear();
		hf_properties_clear();
		h_properties_clear();

		vertices_.clear();
		VertexContainer().swap(vertices_);
		half_edges_.clear();
		HalfEdgeContainer().swap(half_edges_);
		half_faces_.clear();
		HalfFaceContainer().swap(half_faces_);
		hedrons_.clear();
		HedronContainer().swap(hedrons_);
		opp_faces_.clear();		
	}
	/** resize */
	void TopologyKernel::vertices_resize(size_t _n)
	{
		vertices_.resize(_n);
	}
	/** resize */
	void TopologyKernel::half_edges_resize(size_t _n)
	{
		half_edges_.resize(_n);
	}
	/** resize */
	void TopologyKernel::half_faces_resize(size_t _n)
	{
		half_faces_.resize(_n);
	}
	/** resize */
	void TopologyKernel::hedrons_resize(size_t _n)
	{
		hedrons_.resize(_n);
	}
	/** reserve*/
	void TopologyKernel::vertices_reserve(size_t _n)
	{
		vertices_.reserve(_n);
	}
	/** reserve */
	void TopologyKernel::half_edges_reserve(size_t _n)
	{
		half_edges_.reserve(_n);
	}
	/** reserve */
	void TopologyKernel::half_faces_reserve(size_t _n)
	{
		half_faces_.reserve(_n);
	}
	/** reserve */
	void TopologyKernel::hedrons_reserve(size_t _n)
	{
		hedrons_.reserve(_n);
	}
	/** swap two vertices */
	void TopologyKernel::swap_vertices(const VertexHandle & _v0, const VertexHandle & _v1)
	{
		std::swap(vertices_[_v0.idx()], vertices_[_v1.idx()]);
	}
	/** swap two half edges */
	void TopologyKernel::swap_half_edges(const HalfEdgeHandle & _heh0, const HalfEdgeHandle & _heh1)
	{
		std::swap(half_edges_[_heh0.idx()], half_edges_[_heh1.idx()]);
	}
	/** swap two half faces */
	void TopologyKernel::swap_half_faces(const HalfFaceHandle & _hfh0, const HalfFaceHandle & _hfh1)
	{
		std::swap(half_faces_[_hfh0.idx()], half_faces_[_hfh1.idx()]);
	}
	/** swap two hedrons */
	void TopologyKernel::swap_hedrons(const HedronHandle & _hh0, const HedronHandle & _hh1)
	{
		std::swap(hedrons_[_hh0.idx()], hedrons_[_hh1.idx()]);
	}
	/** update the opp_faces_
	*   \param _hf_it the half face 
	*   \param _hfh if the handle is valid, reset it; else remove it from opp_faces_ 
	*   \return void
	*/
	void TopologyKernel::update_opp_face(OppFaceContainer::iterator & _hf_it, HalfFaceHandle _hfh)
	{
		if (_hfh.is_valid())
		{
			_hf_it->second = _hfh.idx();
		}
		else
		{
			opp_faces_.erase(_hf_it);
		}
	}
//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM