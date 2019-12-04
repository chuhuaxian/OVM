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

#ifndef _OVM_TOPOLOGY_KERNEL_H_
#define _OVM_TOPOLOGY_KERNEL_H_


#include <OVM/OVMCore/system/config.h>
#include <OVM/OVMCore/Mesh/Handles.h>
#include <OVM/OVMCore/Mesh/TopologyItems.h>
#include <OVM/OVMCore/Mesh/BaseKernel.h>
#include <OVM/OVMCore/Mesh/Status.h>




#include <assert.h>
#include <vector>
#include <map>

namespace OVM
{
	//---------------------------------------------------------------------------------------------------------------------
	/** Topological kernel using arrays for mesh item storage.

		This kernel uses the std::vector as container to store the
		mesh items. Therefore all handle types are internally represented
		by integers. To get the index from a handle use the handle's \c
		idx() method.
	*/

	class TopologyKernel : public BaseKernel
	{
		//--- handles and items 
	public:
		typedef OVM::VertexHandle   VertexHandle;
		typedef OVM::EdgeHandle     EdgeHandle;
		typedef OVM::HalfEdgeHandle HalfEdgeHandle;
		typedef OVM::FaceHandle     FaceHandle;
		typedef OVM::HalfFaceHandle HalfFaceHandle;
		typedef OVM::HedronHandle   HedronHandle;

		typedef OVM::Vertex   Vertex;
		typedef OVM::HalfEdge HalfEdge;
		typedef OVM::HalfFace HalfFace;
		typedef OVM::Face     Face;
		typedef OVM::Hedron   Hedron;	

		//--- containers and iterators
	protected:
		typedef std::vector<Vertex>   VertexContainer;
		typedef std::vector<HalfEdge> HalfEdgeContainer;
		typedef std::vector<HalfFace> HalfFaceContainer;
		typedef std::vector<Face>     FaceContainer;
		typedef std::vector<Hedron>   HedronContainer;	

		typedef VertexContainer::iterator   KernelVertexIter;
		typedef HalfEdgeContainer::iterator KernelHalfEdgeIter;
		typedef HalfFaceContainer::iterator KernelHalfFaceIter;
		typedef FaceContainer::iterator     KernelFaceIter;
		typedef HedronContainer::iterator   KernelHedronIter;

		typedef VertexContainer::const_iterator   KernelConstVertexIter;
		typedef HalfEdgeContainer::const_iterator KernelConstHalfEdgeIter;
		typedef HalfFaceContainer::const_iterator KernelConstHalfFaceIter;
		typedef FaceContainer::const_iterator     KernelConstFaceIter;
		typedef HedronContainer::const_iterator   KernelConstHedronIter;

		typedef Attributes::StatusInfo StatusInfo;
		typedef VPropHandleT<StatusInfo>  VertexStatusProp;
		typedef HEPropHandleT<StatusInfo> HalfEdgeStatusProp;
		typedef HFPropHandleT<StatusInfo> HalfFaceStatusProp;
		typedef HPropHandleT<StatusInfo>  HedronStatusProp;
		

	//-----------------------------------------------------------------------------------------------------------------
	private:
		/** class for array comparison */
		template < typename T > 
		class LessArray
		{
		public:
			LessArray(std::vector<T> _data) : data_ (_data)
			{
			}
			bool operator == (const LessArray & _rhs) const
			{
				if (data_.size() != _rhs.data_.size())
				{
					return false;
				}
				size_t i;
				i = 0;
				while(( i < data_.size()) && (data_[i] == _rhs.data_[i]))
				{
					++ i;
				}
				if (i < data_.size())
				{
					return false;
				}
				return true;
			}
		public:
			bool operator < (const LessArray & _rhs) const
			{
				size_t i;
				i = 0;
				while(( i < data_.size()) && (data_[i] == _rhs.data_[i]))
				{
					++ i;
				}
				if (i == data_.size())
				{
					return false;
				}
				else if (data_[i] > _rhs.data_[i])
				{
					return false;
				}
				
				
				return true;
			}
		private:
			std::vector<T> data_;
		};
	
		typedef std::map<LessArray<size_t>, __int64> OppFaceContainer;
	public:
		typedef LessArray<unsigned int> LessArrayUInt;
	//-----------------------------------------------------------------------------------------------------------------
	public:
		TopologyKernel() : re_v_status_(0), re_he_status_(0), re_hf_status_(0), re_h_status_(0)
		{
		}
		virtual ~TopologyKernel()
		{
		}
	//-----------------------------------------------------------------------------------------------------------------
	protected:
		/** set the opposite half face handle */
		void set_opposite_half_face(const HalfFaceHandle & _hfh, const HalfFaceHandle & _ohfh, bool _double = true);
		/** set the opposite half edge handle */
		void set_ccw_opposite_half_edge(const HalfEdgeHandle & _heh, const HalfEdgeHandle & _ohfh, bool _double = true);
		/** set the first half face handle of the hedron */
		void set_first_half_face_handle(const HedronHandle & _hh, const HalfFaceHandle & _hfh);
		/** set the half edge handle for vertex */
		void set_vertex_half_edge(const VertexHandle & _vh, const HalfEdgeHandle & _heh);
		/** set the half face handle for half edge */
		void set_half_face(const HalfEdgeHandle & _heh, const HalfFaceHandle & _hfh);
		/** set the start vertex of a half edge */
		void set_start_vertex(const HalfEdgeHandle & _heh, const VertexHandle & _vh);
		/** check if the input half face has opposite half face */
		bool has_opposite_half_face(const HalfFaceHandle & _hfh) const;
		/** check if the input half face has opposite half face */
		bool has_opposite_half_face(const HalfFace & _hf) const;
		/** check if the input half edge has opposite half edge */
		bool has_opposite_half_edge(const HalfEdgeHandle & _heh) const;
		/** check if the input half edge has opposite half edge */
		bool has_opposite_half_edge(const HalfEdge & _he) const;
	protected:
		/** retrieve the half face handle of a half edge */
		HalfFaceHandle half_face_handle(const HalfEdge & _he) const;
		/** retrieve the half face handle of a half edge */
		HalfFaceHandle half_face_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the half edge handle of a vertex */
		HalfEdgeHandle half_edge_handle(const Vertex & _v) const;
		/** retrieve the half edge handle of a vertex */
		HalfEdgeHandle half_edge_handle(const VertexHandle & _vh) const;
	protected:
		/** retrieve the opposite half face handle */
		HalfFaceHandle  opp_half_face_handle(const HalfFaceHandle & _hfh) const;
		/** retrieve the first half edge handle of the half face */
		HalfEdgeHandle first_half_edge_handle(const HalfFaceHandle & _hfh) const;
		/** retrieve the opposite half edge handle */
		HalfEdgeHandle ccw_opp_half_edge_handle(const HalfEdgeHandle & _heh)  const;
		/** retrieve the start vertex handle of the half edge */
		VertexHandle from_vertex_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the end vertex handle of the half edge   */
		VertexHandle to_vertex_handle(const HalfEdgeHandle & _heh) const;
	protected:
		/** add a new vertex into the kernel 
		*   \return the handle  of the vertex
		*/
		VertexHandle new_vertex() ;
		/** add a new half edge into the kernel
		*   \return the handle of the half edge
		*/
		HalfEdgeHandle new_half_edge(HalfEdge _he) ;
		/** add a new half face into the kernel
		*   \return the handle of the half face
		*/
		HalfFaceHandle new_half_face(HalfFace _hf) ;
		/** add a new hedron into the kernel
		*   \return the hedron handle of the hedron
		*/
		HedronHandle new_hedron(Hedron _h) ;

	protected:
		/** pop back the last hedron */
		void hedrons_pop_back();
		/** pop back the last face */
		void half_faces_pop_back();
		/** pop back the last half edge */
		void half_edges_pop_back();
		/** pop back the last vertex */
		void vertices_pop_back();
		/** clear the containers */
		void clear();
	protected:
		/** resize */
		void vertices_resize(size_t _n);
		/** resize */
		void half_edges_resize(size_t _n);
		/** resize */
		void half_faces_resize(size_t _n);
		/** resize */
		void hedrons_resize(size_t _n);
		/** reserve */
		void vertices_reserve(size_t _n);
		/** rese */
		void half_edges_reserve(size_t _n);
		/** reserve */
		void half_faces_reserve(size_t _n);
		/** reserve */
		void hedrons_reserve(size_t _n);
		/** swap two vertices */
		void swap_vertices(const VertexHandle & _v0, const VertexHandle & _v1);
		/** swap two half edges */
		void swap_half_edges(const HalfEdgeHandle & _heh0, const HalfEdgeHandle & _heh1);
		/** swap two half faces */
		void swap_half_faces(const HalfFaceHandle & _hfh0, const HalfFaceHandle & _hfh1);
		/** swap two hedrons */
		void swap_hedrons(const HedronHandle & _hh0, const HedronHandle & _hh1);
	protected:
		/** update the opp_faces_
		*   \param _hf_it the half face 
		*   \param _hfh if the handle is valid, reset it; else remove it from opp_faces_ 
		*   \return void
		*/
		void update_opp_face(OppFaceContainer::iterator & _hf_it, HalfFaceHandle _hfh);
	//-----------------------------------------------------------------------------------------------------------------
	public:
		/// --- item -> handle ---

		VertexHandle handle(const Vertex & _v)
		{
			return VertexHandle(&_v - &vertices_.front());
		}

		HalfEdgeHandle handle(const HalfEdge & _he)
		{
			return HalfEdgeHandle(&_he - &half_edges_.front());
		}

		HalfFaceHandle handle(const HalfFace &_hf)
		{
			return HalfFaceHandle(&_hf - &half_faces_.front());
		}

		HedronHandle handle(const Hedron & _h)
		{
			return HedronHandle(&_h - &hedrons_.front());
		}

		const VertexHandle handle(const Vertex & _v) const
		{
			return VertexHandle(&_v - &vertices_.front());
		}

		const HalfEdgeHandle handle(const HalfEdge & _he) const 
		{
			return HalfEdgeHandle(&_he - &half_edges_.front());
		}

		const HalfFaceHandle handle(const HalfFace &_hf) const 
		{
			return HalfFaceHandle(&_hf - &half_faces_.front());
		}

		const HedronHandle handle(const Hedron & _h) const 
		{
			return HedronHandle(&_h - &hedrons_.front());
		}


		/// --- handle -> item ---

		Vertex & vertex(const VertexHandle & _vh)
		{
			assert(is_valid_handle(_vh));
			return vertices_[_vh.idx()];
		}

		HalfEdge & half_edge(const HalfEdgeHandle & _heh)
		{
			assert(is_valid_handle(_heh));
			return half_edges_[_heh.idx()];
		}

		HalfFace & half_face(const HalfFaceHandle & _hfh)
		{
			assert(is_valid_handle(_hfh));
			return half_faces_[_hfh.idx()];
		}
		
		Hedron & hedron(const HedronHandle & _hh)
		{
			assert(is_valid_handle(_hh));
			return hedrons_[_hh.idx()];
		}

		/// --- const operations for handle -> item ---
		const Vertex & vertex(const VertexHandle & _vh) const
		{
			assert(is_valid_handle(_vh));
			return vertices_[_vh.idx()];
		}

		const HalfEdge & half_edge(const HalfEdgeHandle & _heh) const
		{
			assert(is_valid_handle(_heh));
			return half_edges_[_heh.idx()];
		}

		const HalfFace & half_face(const HalfFaceHandle & _hfh) const
		{
			assert(is_valid_handle(_hfh));
			return half_faces_[_hfh.idx()];
		}

		const Hedron & hedron(const HedronHandle & _hh) const
		{
			assert(is_valid_handle(_hh));
			return hedrons_[_hh.idx()];
		}

	public:
		Vertex & handle_to_entity(const VertexHandle & _vh) 
		{
			return vertex(_vh);
		}

		HalfEdge & handle_to_entity(const HalfEdgeHandle & _heh)
		{
			return half_edge(_heh);
		}

		HalfFace & handle_to_entity(const HalfFaceHandle & _hfh)
		{
			return half_face(_hfh);
		}

		Hedron & handle_to_entity(const HedronHandle & _hh)
		{
			return hedron(_hh);
		}
		const Vertex & handle_to_entity(const VertexHandle & _vh) const 
		{
			return vertex(_vh);
		}

		const HalfEdge & handle_to_entity(const HalfEdgeHandle & _heh) const
		{
			return half_edge(_heh);
		}

		const HalfFace & handle_to_entity(const HalfFaceHandle & _hfh) const
		{
			return half_face(_hfh);
		}

		const Hedron & handle_to_entity(const HedronHandle & _hh) const
		{
			return hedron(_hh);
		}




	public:
		// --- handle validation ---
		bool is_valid_handle(VertexHandle _vh) const
		{
			return ((_vh.idx() >=0) && (_vh.idx() < signed(vertices_.size())));
		}
		bool is_valid_handle(HalfEdgeHandle _heh) const
		{
			return ((_heh.idx() >=0) && (_heh.idx() < signed(half_edges_.size())));
		}
		bool is_valid_handle(HalfFaceHandle _hfh) const
		{
			return ((_hfh.idx() >=0) && (_hfh.idx() < signed(half_faces_.size())));
		}
		bool is_valid_handle(HedronHandle _hh) const
		{
			return ((_hh.idx() >=0) && (_hh.idx() < signed(hedrons_.size())));
		}
	public:

		/// --- iterator operators --- 

		KernelVertexIter vertices_begin() 
		{
			return vertices_.begin();
		}

		KernelHalfEdgeIter half_edges_begin()
		{
			return half_edges_.begin();
		}

		KernelHalfFaceIter half_faces_begin()
		{
			return half_faces_.begin();
		}

		KernelHedronIter hedrons_begin()
		{
			return hedrons_.begin();
		}

		KernelVertexIter vertices_end() 
		{
			return vertices_.end();
		}

		KernelHalfEdgeIter half_edges_end()
		{
			return half_edges_.end();
		}

		KernelHalfFaceIter half_faces_end()
		{
			return half_faces_.end();
		}

		KernelHedronIter hedrons_end()
		{
			return hedrons_.end();
		}

		/// --- const iterator operations ---
		const KernelConstVertexIter vertices_begin() const 
		{
			return vertices_.begin();
		}

		const KernelConstHalfEdgeIter half_edges_begin() const
		{
			return half_edges_.begin();
		}

		const KernelConstHalfFaceIter half_faces_begin() const
		{
			return half_faces_.begin();
		}

		const KernelConstHedronIter hedrons_begin() const
		{
			return hedrons_.begin();
		}

		const KernelConstVertexIter vertices_end() const 
		{
			return vertices_.end();
		}

		const KernelConstHalfEdgeIter half_edges_end() const
		{
			return half_edges_.end();
		}

		const KernelConstHalfFaceIter half_faces_end() const
		{
			return half_faces_.end();
		}

		const KernelConstHedronIter hedrons_end() const
		{
			return hedrons_.end();
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		/// --- count ---
		size_t n_vertices() const
		{
			return vertices_.size();
		}
		size_t n_half_edges()const
		{
			return half_edges_.size();
		}
		size_t n_half_faces() const
		{
			return half_faces_.size();
		}
		size_t n_hedrons() const
		{
			return hedrons_.size();
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		bool has_vertices_status()
		{
			return (re_v_status_ != 0);
		}
		bool has_half_edges_status()
		{
			return (re_he_status_ != 0);
		}
		bool has_half_faces_status()
		{
			return (re_hf_status_ != 0);
		}
		bool has_hedrons_status()
		{
			return (re_h_status_ != 0);
		}
		void request_vertices_status()
		{
			if ((!re_v_status_) && (++ re_v_status_))
			{
				add_property(vertices_status_, "_v_status_");
			}
			
		}
		void request_half_edges_status()
		{
			if ((!re_he_status_) && (++ re_he_status_))
			{
				add_property(half_edges_status_, "_half_edges_status_");
			}

		}
		void request_half_faces_status()
		{
			if ((!re_hf_status_) && (++ re_hf_status_))
			{

				add_property(half_faces_status_, "_half_faces_status_");
			}
		}
		void request_hedrons_status()
		{
			if ((!re_h_status_) && (++ re_h_status_))
			{
				add_property(hedrons_status_, "_v_status_");
			}
		}
		
		void release_vertices_status()
		{
			if ((re_v_status_) && (!(--re_v_status_)))
			{
				remove_property(vertices_status_);
			}

		}
		void release_half_edges_status()
		{
			if ((re_he_status_) && (!(-- re_he_status_)))
			{
				remove_property(half_edges_status_);
			}

		}
		void release_half_faces_status()
		{
			if ((re_hf_status_) && (!(-- re_hf_status_)))
			{
				remove_property(half_faces_status_);
			}
		}
		void release_hedron_status()
		{
			if ((re_h_status_) && (! (-- re_h_status_)))
			{
				remove_property(hedrons_status_);
			}

		}
		const StatusInfo & status(VertexHandle _vh) const
		{
			return property(vertices_status_, _vh);
		}
		StatusInfo & status(VertexHandle _vh) 
		{
			return property(vertices_status_, _vh);
		}
		const StatusInfo & status(HalfEdgeHandle _heh) const
		{
			return property(half_edges_status_, _heh);
		}
		StatusInfo & status(HalfEdgeHandle _heh) 
		{
			return property(half_edges_status_, _heh);
		}
		const StatusInfo & status(HalfFaceHandle _hfh) const
		{
			return property(half_faces_status_, _hfh);
		}
		StatusInfo & status(HalfFaceHandle _hfh) 
		{
			return property(half_faces_status_, _hfh);
		}
		const StatusInfo & status(HedronHandle _hh) const
		{
			return property(hedrons_status_, _hh);
		}
		StatusInfo & status(HedronHandle _hh) 
		{
			return property(hedrons_status_, _hh);
		}
	//-----------------------------------------------------------------------------------------------------------------

	private:
		VertexStatusProp   vertices_status_;
		HalfEdgeStatusProp half_edges_status_;
		HalfFaceStatusProp half_faces_status_;
		HedronStatusProp   hedrons_status_;
		size_t re_v_status_;
		size_t re_he_status_;
		size_t re_hf_status_;		
		size_t re_h_status_;
	protected:
		//size_t kernel_type_;      /**< the type of the kernel, 0x0001 for tetrahedron, 0x0002 for hexahedron */
		VertexContainer   vertices_;    /**< the vertices of the kernel                                            */
		HalfEdgeContainer half_edges_;  /**< the half edges of the kernel                                          */
		HalfFaceContainer half_faces_;  /**< the half faces of the kernel                                          */
		HedronContainer   hedrons_;     /**< the hedrons of the kernel                                             */

		OppFaceContainer  opp_faces_;   
	};


//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM
//---------------------------------------------------------------------------------------------------------------------
#endif