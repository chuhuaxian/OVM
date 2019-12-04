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


#ifndef _OVM_CIRCULATORS_H_
#define _OVM_CIRCULATORS_H_




#include <OVM/OVMCore/System/config.h>

#include <assert.h>


namespace OVM 
{
	namespace Circulators 
	{
		//---------------------------------------------------------------------------------------------------------------------
		//template <class MeshT>	class HedronHedronIterT;	

		/** HedronHedronIterT is a circulator to access the neighboring hedrons of a hedron.
		*   It just likes the iterators of the STL
		*/
		template <class MeshT>
		class HedronHedronIterT
		{
		public:
			typedef typename MeshT::HalfFaceHandle    HalfFaceHandle;
			typedef typename MeshT::Hedron            value_type;
			typedef typename MeshT::HedronHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                            mesh_ref;
			typedef MeshT*                            mesh_ptr;
			typedef typename MeshT::Hedron&           reference;
			typedef typename MeshT::Hedron*           pointer;
		public:
			/** default constructor */
			HedronHedronIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			HedronHedronIterT(mesh_ref _mesh,typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			                  mesh_(&_mesh), 
						      start_(_mesh.half_face_handle(_start)),
							  hfh_(start_),
							  lap_counter_(_end)

			{
		    }
		    /** construct with mesh and a half face */
			HedronHedronIterT(mesh_ref _mesh, typename MeshT::HalfFaceHandle _start, bool _end = false) : 
			                  mesh_(&_mesh), 
				              start_(_start),
				              hfh_(start_),
				              lap_counter_(_end)

			{
			}

		    /** copy constructor */
			HedronHedronIterT(const HedronHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				              start_(_rhs.start_), hfh_(_rhs.hfh_), lap_counter_(_rhs.lap_counter_) 
			{
			}
		    
		public:
			HedronHedronIterT & operator = (const HedronHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hfh_         = _rhs.hfh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const HedronHedronIterT<MeshT> & _rhs) const
			{
				return (
				        (mesh_        == _rhs.mesh_) &&
				        (start_       == _rhs.start_) &&
				        (hfh_         == _rhs.hfh_) &&
				        (lap_counter_ == _rhs.lap_counter_)
						);
			
			}

			bool operator !=  (const HedronHedronIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}

			
			/** increment operator */
			HedronHedronIterT & operator ++ ()
			{
				assert(mesh_);
				hfh_ = mesh_->next_non_boundary_half_face_handle(hfh_);
				if (hfh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			HedronHedronIterT & operator -- ()
			{
				assert(mesh_);
				if (hfh_ == start_)
				{
					-- lap_counter_;
				}
				hfh_ = mesh_->prev_non_boundary_half_face_handle(hfh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfFaceHandle current_half_face_handle() const
			{
				return hfh_;
			}
			/** get the current hedron handle */
			HedronHandle handle() const
			{
				return mesh_->hedron_handle(mesh_->opp_half_face_handle(hfh_));
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HedronHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handle_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (hfh_.is_valid()) && ((start_ != hfh_) || (lap_counter_ == 0));
			}
			

		private:
			mesh_ptr       mesh_;
			HalfFaceHandle start_;
			HalfFaceHandle hfh_;
			int            lap_counter_;
		};
		//-------------------------------------------------------------------------------------------------------------
		/** HedronHedronIterT is a circulator to access the neighboring hedrons of a hedron.
		*   It just likes the iterators of the STL
		*/
		template <class MeshT>
		class ConstHedronHedronIterT
		{
		public:
			typedef typename MeshT::HalfFaceHandle    HalfFaceHandle;
			typedef typename MeshT::Hedron            value_type;
			typedef typename MeshT::HedronHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::Hedron&     reference;
			typedef const typename MeshT::Hedron*     pointer;
		public:
			/** default constructor */
			ConstHedronHedronIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			ConstHedronHedronIterT(mesh_ref _mesh,typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_mesh.half_face_handle(_start)),
				hfh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a half face */
			ConstHedronHedronIterT(mesh_ref _mesh, typename MeshT::HalfFaceHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_start),
				hfh_(start_),
				lap_counter_(_end)

			{
			}

			/** copy constructor */
			ConstHedronHedronIterT(const HedronHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), hfh_(_rhs.hfh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

			/** copy constructor */
			ConstHedronHedronIterT(const ConstHedronHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), hfh_(_rhs.hfh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstHedronHedronIterT & operator = (const ConstHedronHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hfh_         = _rhs.hfh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstHedronHedronIterT & operator = (const HedronHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hfh_         = _rhs.hfh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstHedronHedronIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(hfh_         == _rhs.hfh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstHedronHedronIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstHedronHedronIterT & operator ++ ()
			{
				assert(mesh_);
				hfh_ = mesh_->next_non_boundary_half_face_handle(hfh_);
				if (hfh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstHedronHedronIterT & operator -- ()
			{
				assert(mesh_);
				if (hfh_ == start_)
				{
					-- lap_counter_;
				}
				hfh_ = mesh_->prev_non_boundary_half_face_handle(hfh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfFaceHandle current_half_face_handle() const
			{
				return hfh_;
			}
			/** get the current hedron handle */
			HedronHandle handle() const
			{
				return mesh_->hedron_handle(mesh_->opp_half_face_handle(hfh_));
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HedronHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (hfh_.is_valid()) && ((start_ != hfh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfFaceHandle start_;
			HalfFaceHandle hfh_;
			int            lap_counter_;
		};
		//-------------------------------------------------------------------------------------------------------------
		/** HedronHedronIterT is a circulator to access half faces of a hedron.
		*   It just likes the iterators of the STL
		*/
		template <class MeshT>
		class HedronHalfFaceIterT
		{
		public:
			typedef typename MeshT::HalfFaceHandle    HalfFaceHandle;
			typedef typename MeshT::HalfFace          value_type;
			typedef typename MeshT::HalfFaceHandle    value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                      mesh_ref;
			typedef MeshT*                      mesh_ptr;
			typedef typename MeshT::HalfFace&     reference;
			typedef typename MeshT::HalfFace*     pointer;
		public:
			/** default constructor */
			HedronHalfFaceIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			HedronHalfFaceIterT(mesh_ref _mesh,typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			    mesh_(&_mesh), 
				start_(_mesh.half_face_handle(_start)),
				hfh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a half face */
			HedronHalfFaceIterT(mesh_ref _mesh, typename MeshT::HalfFaceHandle _start, bool _end = false) : 
			    mesh_(&_mesh), 
				start_(_start),
				hfh_(start_),
				lap_counter_(_end)

			{
			}

			/** copy constructor */
			HedronHalfFaceIterT(const HedronHalfFaceIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), hfh_(_rhs.hfh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			HedronHalfFaceIterT & operator = (const HedronHalfFaceIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hfh_         = _rhs.hfh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const HedronHalfFaceIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(hfh_         == _rhs.hfh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const HedronHalfFaceIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			HedronHalfFaceIterT & operator ++ ()
			{
				assert(mesh_);
				hfh_ = mesh_->next_half_face_handle(hfh_);
				if (hfh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			HedronHalfFaceIterT & operator -- ()
			{
				assert(mesh_);
				if (hfh_ == start_)
				{
					-- lap_counter_;
				}
				hfh_ = mesh_->prev_half_face_handle(hfh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfFaceHandle current_half_face_handle() const
			{
				return hfh_;
			}
			/** get the current hedron handle */
			HalfFaceHandle handle() const
			{
				return hfh_;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HalfFaceHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (hfh_.is_valid()) && ((start_ != hfh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfFaceHandle start_;
			HalfFaceHandle hfh_;
			int            lap_counter_;
		};
		//-------------------------------------------------------------------------------------------------------------
		/** HedronHedronIterT is a circulator to access half faces of  a hedron.
		*   It just likes the iterators of the STL
		*/
		template <class MeshT>
		class ConstHedronHalfFaceIterT
		{
		public:
			typedef typename MeshT::HalfFaceHandle    HalfFaceHandle;
			typedef typename MeshT::HalfFace          value_type;
			typedef typename MeshT::HalfFaceHandle    value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::HalfFace&   reference;
			typedef const typename MeshT::HalfFace*   pointer;
		public:
			/** default constructor */
			ConstHedronHalfFaceIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			ConstHedronHalfFaceIterT(mesh_ref _mesh,typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_mesh.half_face_handle(_start)),
				hfh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a half face */
			ConstHedronHalfFaceIterT(mesh_ref _mesh, typename MeshT::HalfFaceHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_start),
				hfh_(start_),
				lap_counter_(_end)

			{
			}

			/** copy constructor */
			ConstHedronHalfFaceIterT(const HedronHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), hfh_(_rhs.hfh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

			/** copy constructor */
			ConstHedronHalfFaceIterT(const ConstHedronHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), hfh_(_rhs.hfh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstHedronHalfFaceIterT & operator = (const HedronHalfFaceIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hfh_         = _rhs.hfh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstHedronHalfFaceIterT & operator = (const ConstHedronHalfFaceIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hfh_         = _rhs.hfh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstHedronHalfFaceIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(hfh_         == _rhs.hfh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstHedronHalfFaceIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstHedronHalfFaceIterT & operator ++ ()
			{
				assert(mesh_);
				hfh_ = mesh_->next_half_face_handle(hfh_);
				if (hfh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstHedronHalfFaceIterT & operator -- ()
			{
				assert(mesh_);
				if (hfh_ == start_)
				{
					-- lap_counter_;
				}
				hfh_ = mesh_->prev_half_face_handle(hfh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfFaceHandle current_half_face_handle() const
			{
				return hfh_;
			}
			/** get the current hedron handle */
			HalfFaceHandle handle() const
			{
				return hfh_;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HalfFaceHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (hfh_.is_valid()) && ((start_ != hfh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfFaceHandle start_;
			HalfFaceHandle hfh_;
			int            lap_counter_;
		};
		

		//-------------------------------------------------------------------------------------------------------------

		/** HedronVertexIterT is a circulator to access the  of a hedron.
		*   It just likes the iterators of the STL
		*/
		template <class MeshT>
		class HedronVertexIterT
		{
		public:
			typedef typename MeshT::HalfEdgeHandle        HalfEdgeHandle;
			typedef typename MeshT::Vertex            value_type;
			typedef typename MeshT::VertexHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                            mesh_ref;
			typedef MeshT*                            mesh_ptr;
			typedef typename MeshT::Vertex&           reference;
			typedef typename MeshT::Vertex*           pointer;
		public:
			/** default constructor */
			HedronVertexIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			HedronVertexIterT(mesh_ref _mesh, typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			    mesh_(&_mesh), 
				start_(_start),
				heh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a half edge */
			HedronVertexIterT(mesh_ref _mesh, typename MeshT::HedronHandle _start, bool _end = false) : 
				mesh_(&_mesh), 
				start_(_mesh.first_half_edge_handle(_start)),
				heh_(start_),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			HedronVertexIterT(const HedronVertexIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			HedronVertexIterT & operator = (const HedronVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const HedronVertexIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const HedronVertexIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			HedronVertexIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->next_hedron_vertex_half_edge_handle(heh_);
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			HedronVertexIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				if (lap_counter_ < 0)
				{
					heh_ = start_;
					return (*this);				
				}
				
				heh_ = mesh_->prev_hedron_vertex_half_edge_handle(heh_);
				return (*this);				
			}

			/** get the current half edge handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_ ;
			}
			/** get the current vertex handle */
			VertexHandle handle() const
			{
				return mesh_->from_vertex_handle(heh_) ;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle( ));
			}

			/** cast the current handle to the target */
			operator VertexHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr         mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int            lap_counter_;
		};

		/** HedronVertexIterT is a circulator to access the vertices of a hedron.
		*   It just likes the iterators of the STL
		*/
		template <class MeshT>
		class ConstHedronVertexIterT
		{
		public:
			typedef typename MeshT::HalfEdgeHandle    HalfEdgeHandle;
			typedef typename MeshT::Vertex            value_type;
			typedef typename MeshT::VertexHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::Vertex&     reference;
			typedef const typename MeshT::Vertex*     pointer;
		public:
			/** default constructor */
			ConstHedronVertexIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			ConstHedronVertexIterT(mesh_ref _mesh, typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			    mesh_(&_mesh), 
				start_(_start),
				heh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a hedron */
			ConstHedronVertexIterT(mesh_ref _mesh, typename MeshT::HedronHandle _start, bool _end = false) : 
				mesh_(&_mesh), 
				start_(_mesh.first_half_edge_handle(_start)),
				heh_(start_),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			ConstHedronVertexIterT(const ConstHedronVertexIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstHedronVertexIterT & operator = (const HedronVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstHedronVertexIterT & operator = (const ConstHedronVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstHedronVertexIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstHedronVertexIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstHedronVertexIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->next_hedron_vertex_half_edge_handle(heh_);
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstHedronVertexIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				if (lap_counter_ < 0)
				{
					heh_ = start_;
					return (*this);				
				}
				heh_ = mesh_->prev_hedron_vertex_half_edge_handle(heh_);
				return (*this);				
			}

			/** get the current half handle	*/
			VertexHandle current_half_edge_handle() const
			{
				return heh_ ;
			}
			/** get the current hedron handle */
			VertexHandle handle() const
			{
				return mesh_->from_vertex_handle(heh_); ;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator VertexHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int            lap_counter_;
		};

		//-------------------------------------------------------------------------------------------------------------

		/** ConstHalfFaceVertexIterT is a circulator to access the vertices of a half face
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class HalfFaceVertexIterT
		{
		public:
			typedef typename MeshT::HalfEdgeHandle    HalfEdgeHandle;
			typedef typename MeshT::Vertex            value_type;
			typedef typename MeshT::VertexHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                      mesh_ref;
			typedef MeshT*                      mesh_ptr;
			typedef typename MeshT::Vertex&     reference;
			typedef typename MeshT::Vertex*     pointer;
		public:
			/** default constructor */
			HalfFaceVertexIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			HalfFaceVertexIterT(mesh_ref _mesh, typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_start),
				heh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a half face */
			HalfFaceVertexIterT(mesh_ref _mesh, typename MeshT::HalfFaceHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_mesh.first_half_edge_handle(_start)),
				heh_(start_),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			HalfFaceVertexIterT(const HalfFaceVertexIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			HalfFaceVertexIterT & operator = (const HalfFaceVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const HalfFaceVertexIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const HalfFaceVertexIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			HalfFaceVertexIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->next_half_edge_handle(heh_);
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			HalfFaceVertexIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				heh_ = mesh_->prev_half_edge_handle(heh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_ ;
			}
			/** get the current hedron handle */
			VertexHandle handle() const
			{
				return mesh_->from_vertex_handle(heh_); ;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator VertexHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int            lap_counter_;
		};


		//-------------------------------------------------------------------------------------------------------------

		/** ConstHalfFaceVertexIterT is a circulator to access the vertices of a half face
		*   It just likes the iterators of STL
		*/
		template <class MeshT>
		class ConstHalfFaceVertexIterT
		{
		public:
			typedef typename MeshT::HalfEdgeHandle    HalfEdgeHandle;
			typedef typename MeshT::Vertex            value_type;
			typedef typename MeshT::VertexHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::Vertex&     reference;
			typedef const typename MeshT::Vertex*     pointer;
		public:
			/** default constructor */
			ConstHalfFaceVertexIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			ConstHalfFaceVertexIterT(mesh_ref _mesh, typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_start),
				heh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a half face */
			ConstHalfFaceVertexIterT(mesh_ref _mesh, typename MeshT::HalfFaceHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_mesh.first_half_edge_handle(_start)),
				heh_(start_),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			ConstHalfFaceVertexIterT(const ConstHalfFaceVertexIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstHalfFaceVertexIterT & operator = (const HalfFaceVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstHalfFaceVertexIterT & operator = (const ConstHalfFaceVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstHalfFaceVertexIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstHalfFaceVertexIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstHalfFaceVertexIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->next_half_edge_handle(heh_);
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstHalfFaceVertexIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				heh_ = mesh_->prev_half_edge_handle(heh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_ ;
			}
			/** get the current hedron handle */
			VertexHandle handle() const
			{
				return mesh_->from_vertex_handle(heh_); ;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator VertexHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int            lap_counter_;
		};
		//-------------------------------------------------------------------------------------------------------------

		/** HalfFaceEdgeIterT is a circulator to access the half edges of a half face
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class HalfFaceHalfEdgeIterT
		{
		public:
			typedef typename MeshT::HalfEdgeHandle    HalfEdgeHandle;
			typedef typename MeshT::Vertex            value_type;
			typedef typename MeshT::VertexHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                      mesh_ref;
			typedef MeshT*                      mesh_ptr;
			typedef typename MeshT::Vertex&     reference;
			typedef typename MeshT::Vertex*     pointer;
		public:
			/** default constructor */
			HalfFaceHalfEdgeIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			HalfFaceHalfEdgeIterT(mesh_ref _mesh, typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_start),
				heh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a half face */
			HalfFaceHalfEdgeIterT(mesh_ref _mesh, typename MeshT::HalfFaceHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_mesh.first_half_edge_handle(_start)),
				heh_(start_),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			HalfFaceHalfEdgeIterT(const HalfFaceHalfEdgeIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			HalfFaceHalfEdgeIterT & operator = (const HalfFaceHalfEdgeIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const HalfFaceHalfEdgeIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const HalfFaceHalfEdgeIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			HalfFaceHalfEdgeIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->next_half_edge_handle(heh_);
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			HalfFaceHalfEdgeIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				heh_ = mesh_->prev_half_edge_handle(heh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_ ;
			}
			/** get the current hedron handle */
			HalfEdgeHandle handle() const
			{
				return heh_; ;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HalfEdgeHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int            lap_counter_;
		};


		//-------------------------------------------------------------------------------------------------------------

		/** ConstHalfFaceHalfEdgeIterT is a circulator to access the half edges of a half face
		*   It just likes the iterators of STL
		*/
		template <class MeshT>
		class ConstHalfFaceHalfEdgeIterT
		{
		public:
			typedef typename MeshT::HalfEdgeHandle    HalfEdgeHandle;
			typedef typename MeshT::Vertex            value_type;
			typedef typename MeshT::VertexHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::Vertex&     reference;
			typedef const typename MeshT::Vertex*     pointer;
		public:
			/** default constructor */
			ConstHalfFaceHalfEdgeIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			ConstHalfFaceHalfEdgeIterT(mesh_ref _mesh, typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_start),
				heh_(start_),
				lap_counter_(_end)

			{
			}
			/** construct with mesh and a half face */
			ConstHalfFaceHalfEdgeIterT(mesh_ref _mesh, typename MeshT::HalfFaceHandle _start, bool _end = false) : 
			mesh_(&_mesh), 
				start_(_mesh.first_half_edge_handle(_start)),
				heh_(start_),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			ConstHalfFaceHalfEdgeIterT(const ConstHalfFaceHalfEdgeIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstHalfFaceHalfEdgeIterT & operator = (const HalfFaceHalfEdgeIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstHalfFaceHalfEdgeIterT & operator = (const ConstHalfFaceHalfEdgeIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstHalfFaceHalfEdgeIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstHalfFaceHalfEdgeIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstHalfFaceHalfEdgeIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->next_half_edge_handle(heh_);
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstHalfFaceHalfEdgeIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				heh_ = mesh_->prev_half_edge_handle(heh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_ ;
			}
			/** get the current hedron handle */
			HalfEdgeHandle handle() const
			{
				return heh_; ;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HalfEdgeHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int            lap_counter_;
		};

		/** HalfEdgeHedronIterT is a circulator to access the hedrons of a half edge
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class HalfEdgeHedronIterT
		{
		public:
			typedef typename MeshT::HalfEdgeHandle    HalfEdgeHandle;
			typedef typename MeshT::Hedron            value_type;
			typedef typename MeshT::HedronHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                      mesh_ref;
			typedef MeshT*                      mesh_ptr;
			typedef typename MeshT::Hedron&     reference;
			typedef typename MeshT::Hedron*     pointer;
		public:
			/** default constructor */
			HalfEdgeHedronIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			HalfEdgeHedronIterT(mesh_ref _mesh, typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			    mesh_(&_mesh), 
				start_(_start),
				heh_(start_),
				lap_counter_(_end)

			{
			}

			/** copy constructor */
			HalfEdgeHedronIterT(const HalfEdgeHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			HalfEdgeHedronIterT & operator = (const HalfEdgeHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const HalfEdgeHedronIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const HalfEdgeHedronIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			HalfEdgeHedronIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->ccw_opp_half_edge_handle(heh_);
				heh_ = mesh_->cw_opp_half_edge_handle(heh_);
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			HalfEdgeHedronIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				heh_ = mesh_->cw_opp_half_edge_handle(heh_);
				heh_ = mesh_->ccw_opp_half_edge_handle(heh_);
				
				return (*this);				
			}

			/** get the current half handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_ ;
			}
			/** get the current hedron handle */
			HedronHandle handle() const
			{
				return mesh_->hedron_handle(heh_) ;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HedronHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int            lap_counter_;
		};
		/** HalfEdgeHedronIterT is a circulator to access the hedrons of a half edge
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class ConstHalfEdgeHedronIterT
		{
		public:
			typedef typename MeshT::HalfEdgeHandle    HalfEdgeHandle;
			typedef typename MeshT::Hedron            value_type;
			typedef typename MeshT::HedronHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::Hedron&     reference;
			typedef const typename MeshT::Hedron*     pointer;
		public:
			/** default constructor */
			ConstHalfEdgeHedronIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			ConstHalfEdgeHedronIterT(mesh_ref _mesh, typename MeshT::HalfEdgeHandle _start, bool _end = false) : 
			    mesh_(&_mesh), 
				start_(_start),
				heh_(start_),
				lap_counter_(_end)

			{
			}

			/** copy constructor */
			ConstHalfEdgeHedronIterT(const ConstHalfEdgeHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstHalfEdgeHedronIterT & operator = (const HalfEdgeHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstHalfEdgeHedronIterT & operator = (const ConstHalfEdgeHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstHalfEdgeHedronIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_) &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstHalfEdgeHedronIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstHalfEdgeHedronIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->ccw_opp_half_edge_handle(heh_);
				heh_ = mesh_->cw_opp_half_edge_handle(heh_);
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstHalfEdgeHedronIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				heh_ = mesh_->cw_opp_half_edge_handle(heh_);
				heh_ = mesh_->ccw_opp_half_edge_handle(heh_);
				return (*this);				
			}

			/** get the current half handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_ ;
			}
			/** get the current hedron handle */
			HedronHandle handle() const
			{
				return mesh_->hedron_handle(heh_) ;
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HedronHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}


		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int            lap_counter_;
		};

		//-------------------------------------------------------------------------------------------------------------
		/** VertexHedronIterT is a circulator to access the hedrons of a vertex
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class VertexHedronIterT
		{
		public:
			typedef typename MeshT::VertexHandle      VertexHandle;
			typedef typename MeshT::Hedron            value_type;
			typedef typename MeshT::HedronHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                      mesh_ref;
			typedef MeshT*                      mesh_ptr;
			typedef typename MeshT::Hedron&     reference;
			typedef typename MeshT::Hedron*     pointer;
			typedef std::vector<HedronHandle>   HedronContainer;
		public:
			/** default constructor */
			VertexHedronIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			VertexHedronIterT(typename mesh_ref _mesh, const typename HedronContainer::iterator & _start, const typename HedronContainer::iterator & _h_end, bool _end = false) : 
			    mesh_(&_mesh),
				//hedrons_.assign(),
				start_(0),
				hh_(0),
				lap_counter_(_end)

			{
				hedrons_.assign(_start, _h_end);
			}
			/** construct with mesh and a half face */
			VertexHedronIterT(typename mesh_ref _mesh, HedronContainer _hedrons, bool _end = false) : 
			    mesh_(&_mesh),
				hedrons_(_hedrons),
				start_(0),
				hh_(0),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			VertexHedronIterT(const VertexHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				              start_(_rhs.start_), hh_(_rhs.hh_), hedrons_(_rhs.hedrons_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
		    VertexHedronIterT & operator = (const VertexHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hh_          = _rhs.hh_;
				hedrons_     = _rhs.hedrons_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const VertexHedronIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(hh_         == _rhs.hh_) &&
					(compare_hedrons(hedrons_, _rhs.hedrons_)) && 
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const VertexHedronIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			VertexHedronIterT & operator ++ ()
			{
				assert(mesh_);
				++ hh_;
				if (hh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			VertexHedronIterT & operator -- ()
			{
				assert(mesh_);
				if (hh_ == start_)
				{
					-- lap_counter_;
				}
				-- hh_;
				return (*this);				
			}

			/** get the current half handle	*/
			HedronHandle current_hedron_handle() const
			{
				return hedrons_[hh_];
			}
			/** get the current hedron handle */
			HedronHandle handle() const
			{
				return current_hedron_handle();
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HedronHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return ((hh_ >=0) && (hh_ < hedrons_.size())) && ((start_ != hh_) || (lap_counter_ == 0));
			}
		private:
			/** compare two array hedrons */
			bool compare_hedrons(const HedronContainer & _hc0, const HedronContainer & _hc1)
			{
				if (_hc0.size() != _hc1.size())
				{
					return false;
				}
				for (unsigned int i = 0; i < _hc0.size(); i ++)
				{
					if (_hc0[i] != _hc1[i])
					{
						return false;
					}
				}
				
				return true;
			}


		private:
			mesh_ptr       mesh_;
			unsigned int   start_;
			unsigned int   hh_;
			HedronContainer hedrons_;
			int            lap_counter_;
		};

		/** ConstVertexHedronIterT is a circulator to access the hedrons of a vertex
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class ConstVertexHedronIterT
		{
		public:
			typedef typename MeshT::VertexHandle      VertexHandle;
			typedef typename MeshT::Hedron            value_type;
			typedef typename MeshT::HedronHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::Hedron&     reference;
			typedef const typename MeshT::Hedron*     pointer;
			typedef std::vector<HedronHandle>         HedronContainer;
		public:
			/** default constructor */
			ConstVertexHedronIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			ConstVertexHedronIterT(mesh_ref _mesh, const typename HedronContainer::iterator & _start, const typename HedronContainer::iterator & _h_end, bool _end = false) : 
			    mesh_(&_mesh),
				start_(0),
				hh_(0),
				lap_counter_(_end)

			{
				hedrons_.assign(_start, _h_end);
				
			}
			/** construct with mesh and a half face */
			ConstVertexHedronIterT(mesh_ref _mesh, HedronContainer _hedrons, bool _end = false) : 
			mesh_(&_mesh),
				hedrons_(_hedrons),
				start_(0),
				hh_(0),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			ConstVertexHedronIterT(const VertexHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), hh_(_rhs.hh_), hedrons_(_rhs.hedrons_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstVertexHedronIterT & operator = (const VertexHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hh_          = _rhs.hh_;
				hedrons_     = _rhs.hedrons_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstVertexHedronIterT & operator = (const ConstVertexHedronIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				hh_          = _rhs.hh_;
				hedrons_     = _rhs.hedrons_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstVertexHedronIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(hh_          == _rhs.hh_) &&
					(compare_hedrons(hedrons_, _rhs.hedrons_)) && 
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstVertexHedronIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstVertexHedronIterT & operator ++ ()
			{
				assert(mesh_);
				++ hh_;
				if (hh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstVertexHedronIterT & operator -- ()
			{
				assert(mesh_);
				if (hh_ == start_)
				{
					-- lap_counter_;
				}
				-- hh_;
				return (*this);				
			}

			/** get the current half handle	*/
			HedronHandle current_hedron_handle() const
			{
				return hedrons_[hh_];
			}
			/** get the current hedron handle */
			HedronHandle handle() const
			{
				return current_hedron_handle();
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HedronHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return ((hh_ >=0) && (hh_ < hedrons_.size())) && ((start_ != hh_) || (lap_counter_ == 0));
			}
		private:
			/** compare two array hedrons */
			bool compare_hedrons(const HedronContainer & _hc0, const HedronContainer & _hc1)
			{
				if (_hc0.size() != _hc1.size())
				{
					return false;
				}
				for (unsigned int i = 0; i < _hc0.size(); i ++)
				{
					if (_hc0[i] != _hc1[i])
					{
						return false;
					}
				}

				return true;
			}


		private:
			mesh_ptr       mesh_;
			unsigned int   start_;
			unsigned int   hh_;
			HedronContainer hedrons_;
			int            lap_counter_;
		};

		//-------------------------------------------------------------------------------------------------------------
		/** VertexHedronHalfFaceIterT is a circulator to access the half face of a specified hedron attached to a vertex
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class VertexHedronHalfFaceIterT
		{
		public:
			typedef typename MeshT::VertexHandle      VertexHandle;
			typedef typename MeshT::HalfFace          value_type;
			typedef typename MeshT::HalfFaceHandle    value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                            mesh_ref;
			typedef MeshT*                            mesh_ptr;
			typedef typename MeshT::HalfFace&         reference;
			typedef typename MeshT::HalfFace*         pointer;
		public:
			/** default constructor */
			VertexHedronHalfFaceIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			VertexHedronHalfFaceIterT(mesh_ref _mesh, const typename MeshT::HalfEdgeHandle & _start, bool _end = false) : 
			    mesh_(&_mesh),
				start_(_start),
				heh_(_start),
				lap_counter_(_end)

			{
			}

			/** copy constructor */
			VertexHedronHalfFaceIterT(const VertexHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			VertexHedronHalfFaceIterT & operator = (const VertexHedronHalfFaceIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_          = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const VertexHedronHalfFaceIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_)  &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_)   &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const VertexHedronHalfFaceIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			VertexHedronHalfFaceIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->cw_opp_half_edge_handle(mesh_->prev_half_edge_handle(heh_));
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			VertexHedronHalfFaceIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				heh_ = mesh_->next_half_edge_handle(mesh_->cw_opp_half_edge_handle(heh_));
				return (*this);				
			}

			/** get the current half face handle	*/
			HalfFaceHandle current_half_face_handle() const
			{
				return mesh_->half_face_handle(heh_);
			}
			/** get the current half face handle */
			HalfFaceHandle handle() const
			{
				return current_half_face_handle();
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HalfFaceHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}

		private:
			mesh_ptr         mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int              lap_counter_;
		};
		/** ConstVertexHedronHalfFaceIterT is a circulator to access the half face of a specified hedron attached to a vertex
		*   It just likes the iterators of STL
		*/			
		template <class MeshT>
		class ConstVertexHedronHalfFaceIterT
		{
		public:
			typedef typename MeshT::VertexHandle      VertexHandle;
			typedef typename MeshT::HalfFace          value_type;
			typedef typename MeshT::HalfFaceHandle    value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                            mesh_ref;
			typedef const MeshT*                            mesh_ptr;
			typedef const typename MeshT::HalfFace&         reference;
			typedef const typename MeshT::HalfFace*         pointer;
		public:
			/** default constructor */
			ConstVertexHedronHalfFaceIterT() : mesh_(NULL), lap_counter_(0)
			{
			}
			/** construct with mesh and a half edge */
			ConstVertexHedronHalfFaceIterT(mesh_ref _mesh, const typename MeshT::HalfEdgeHandle & _start, bool _end = false) : 
			mesh_(&_mesh),
				start_(_start),
				heh_(_start),
				lap_counter_(_end)

			{
			}

			/** copy constructor */
			ConstVertexHedronHalfFaceIterT(const ConstVertexHedronIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstVertexHedronHalfFaceIterT & operator = (const VertexHedronHalfFaceIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstVertexHedronHalfFaceIterT & operator = (const ConstVertexHedronHalfFaceIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstVertexHedronHalfFaceIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_)  &&
					(start_       == _rhs.start_) &&
					(heh_         == _rhs.heh_)   &&
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstVertexHedronHalfFaceIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstVertexHedronHalfFaceIterT & operator ++ ()
			{
				assert(mesh_);
				heh_ = mesh_->cw_opp_half_edge_handle(mesh_->prev_half_edge_handle(heh_));
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstVertexHedronHalfFaceIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				heh_ = mesh_->next_half_edge_handle(mesh_->cw_opp_half_edge_handle(heh_));
				return (*this);				
			}

			/** get the current half face handle	*/
			HalfFaceHandle current_half_face_handle() const
			{
				return mesh_->half_face_handle(heh_);
			}
			/** get the current half face handle */
			HalfFaceHandle handle() const
			{
				return current_half_face_handle();
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HalfFaceHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return (heh_.is_valid()) && ((start_ != heh_) || (lap_counter_ == 0));
			}

		private:
			mesh_ptr         mesh_;
			HalfEdgeHandle   start_;
			HalfEdgeHandle   heh_;
			int              lap_counter_;
		};
		//-------------------------------------------------------------------------------------------------------------
		/** HedronHalfEdgeIterT is a circulator to access the half edges of a hedron
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class HedronHalfEdgeIterT
		{
		public:
			typedef typename MeshT::VertexHandle      VertexHandle;
			typedef typename MeshT::HalfEdge          value_type;
			typedef typename MeshT::HalfEdgeHandle    value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                      mesh_ref;
			typedef MeshT*                      mesh_ptr;
			typedef typename MeshT::HalfEdge&     reference;
			typedef typename MeshT::HalfEdge*     pointer;
		public:
			/** default constructor */
			HedronHalfEdgeIterT() : mesh_(NULL), lap_counter_(0)
			{
			}

			/** construct with mesh and a half edge */
			HedronHalfEdgeIterT(mesh_ref _mesh, const HalfEdgeHandle & _start, unsigned long long _he_count, bool _end = false) : 
			                    mesh_(&_mesh),
								start_(_start),
								heh_(_start),
								he_count_(_he_count),
								lap_counter_(_end)

			{
			}

			/** copy constructor */
			HedronHalfEdgeIterT(const HedronHalfEdgeIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				                start_(_rhs.start_), he_count_(_rhs.he_count_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			HedronHalfEdgeIterT & operator = (const HedronHalfEdgeIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				he_count_    = _rhs.he_count_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const HedronHalfEdgeIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_)     &&
					(start_       == _rhs.start_)    &&
					(he_count_    == _rhs.he_count_) &&
					(heh_         == _rhs.heh_)      &&  
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const HedronHalfEdgeIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			HedronHalfEdgeIterT & operator ++ ()
			{
				assert(mesh_);
				++ heh_;
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			HedronHalfEdgeIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				-- heh_;
				return (*this);				
			}

			/** get the current half edge handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_;
			}
			/** get the current hedron handle */
			HalfEdgeHandle handle() const
			{
				return current_half_edge_handle();
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HalfEdgeHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return ((heh_.idx() >=0) && ((heh_.idx() - start_.idx()) < he_count_) && ((heh_.idx() - start_.idx()) > -1 )) && ((start_ != heh_) || (lap_counter_ == 0));
			}
		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle start_;
			HalfEdgeHandle heh_;
			long long   he_count_;
			long long            lap_counter_;
		};
		/** ConstHedronHalfEdgeIterT is a circulator to access the half edge of a hedron
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class ConstHedronHalfEdgeIterT
		{
		public:
			typedef typename MeshT::VertexHandle      VertexHandle;
			typedef typename MeshT::HalfEdge          value_type;
			typedef typename MeshT::HalfEdgeHandle    value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::HalfEdge&     reference;
			typedef const typename MeshT::HalfEdge*     pointer;
		public:
			/** default constructor */
			ConstHedronHalfEdgeIterT() : mesh_(NULL), lap_counter_(0)
			{
			}

			/** construct with mesh and a half edge */
			ConstHedronHalfEdgeIterT(mesh_ref _mesh, const HalfEdgeHandle & _start, unsigned long long _he_count, bool _end = false) : 
			    mesh_(&_mesh),
				start_(_start),
				heh_(_start),
				he_count_(_he_count),
				lap_counter_(_end)

			{
			}

			/** copy constructor */
			ConstHedronHalfEdgeIterT(const ConstHedronHalfEdgeIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), he_count_(_rhs.he_count_), heh_(_rhs.heh_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstHedronHalfEdgeIterT & operator = (const HedronHalfEdgeIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				he_count_    = _rhs.he_count_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstHedronHalfEdgeIterT & operator = (const ConstHedronHalfEdgeIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				he_count_    = _rhs.he_count_;
				heh_         = _rhs.heh_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstHedronHalfEdgeIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_)     &&
					(start_       == _rhs.start_)    &&
					(he_count_    == _rhs.he_count_) &&
					(heh_         == _rhs.heh_)      &&  
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstHedronHalfEdgeIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstHedronHalfEdgeIterT & operator ++ ()
			{
				assert(mesh_);
				++ heh_;
				if (heh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstHedronHalfEdgeIterT & operator -- ()
			{
				assert(mesh_);
				if (heh_ == start_)
				{
					-- lap_counter_;
				}
				-- heh_;
				return (*this);				
			}

			/** get the current half edge handle	*/
			HalfEdgeHandle current_half_edge_handle() const
			{
				return heh_;
			}
			/** get the current hedron handle */
			HalfEdgeHandle handle() const
			{
				return current_half_edge_handle();
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator HalfEdgeHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return ((heh_.idx() >= 0) && ((heh_.idx() - start_.idx()) < he_count_) && ((heh_.idx() - start_.idx()) > -1 )) && ((start_ != heh_) || (lap_counter_ == 0));
			}
		private:
			mesh_ptr       mesh_;
			HalfEdgeHandle start_;
			HalfEdgeHandle heh_;
			long long   he_count_;
			long long            lap_counter_;
		};

		

		//-------------------------------------------------------------------------------------------------------------
		/** VertexVertexIterT is a circulator to access the adjacent of a vertex
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class VertexVertexIterT
		{
		public:
			typedef typename MeshT::VertexHandle      VertexHandle;
			typedef typename MeshT::Vertex            value_type;
			typedef typename MeshT::VertexHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef MeshT&                      mesh_ref;
			typedef MeshT*                      mesh_ptr;
			typedef typename MeshT::Vertex&     reference;
			typedef typename MeshT::Vertex*     pointer;
			typedef std::vector<VertexHandle>   VertexContainer;
		public:
			/** default constructor */
			VertexVertexIterT() : mesh_(NULL), lap_counter_(0)
			{
			}

			/** construct with mesh and a half edge */
			VertexVertexIterT(mesh_ref _mesh, const typename VertexContainer::iterator & _start, const typename VertexContainer::iterator & _v_end, bool _end = false) : 
			    mesh_(&_mesh),
				start_(0),
				vh_(0),
				lap_counter_(_end)

			{
				vertices_.assign(_start, _v_end);
			}

			/** construct with mesh and a half face */
			VertexVertexIterT(mesh_ref _mesh, VertexContainer _vertices, bool _end = false) : 
			    mesh_(&_mesh),
				vertices_(_vertices),
				start_(0),
				vh_(0),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			VertexVertexIterT(const VertexVertexIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), vh_(_rhs.vh_), vertices_(_rhs.vertices_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			VertexVertexIterT & operator = (const VertexVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				vh_          = _rhs.vh_;
				vertices_    = _rhs.vertices_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const VertexVertexIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(vh_         == _rhs.vh_) &&
					(compare_vertices(vertices_, _rhs.vertices_)) && 
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const VertexVertexIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			VertexVertexIterT & operator ++ ()
			{
				assert(mesh_);
				++ vh_;
				if (vh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			VertexVertexIterT & operator -- ()
			{
				assert(mesh_);
				if (vh_ == start_)
				{
					-- lap_counter_;
				}
				-- vh_;
				return (*this);				
			}

			/** get the current half handle	*/
			VertexHandle current_vertex_handle() const
			{
				return vertices_[vh_];
			}
			/** get the current hedron handle */
			VertexHandle handle() const
			{
				return current_vertex_handle();
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator VertexHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return ((vh_ >=0) && (vh_ < vertices_.size())) && ((start_ != vh_) || (lap_counter_ == 0));
			}
		private:
			/** compare two array hedrons */
			bool compare_vertices(const VertexContainer & _vc0, const VertexContainer & _vc1)
			{
				if (_vc0.size() != _vc1.size())
				{
					return false;
				}
				for (unsigned int i = 0; i < _vc0.size(); i ++)
				{
					if (_vc0[i] != _vc1[i])
					{
						return false;
					}
				}

				return true;
			}


		private:
			mesh_ptr       mesh_;
			unsigned int   start_;
			unsigned int   vh_;
			VertexContainer vertices_;
			int            lap_counter_;
		};
		/** VertexVertexIterT is a circulator to access the adjacent of a vertex
		*   It just likes the iterators of STL
		*/		
		template <class MeshT>
		class ConstVertexVertexIterT
		{
		public:
			typedef typename MeshT::VertexHandle      VertexHandle;
			typedef typename MeshT::Vertex            value_type;
			typedef typename MeshT::VertexHandle      value_handle;

			typedef std::bidirectional_iterator_tag   iterator_category;
			typedef ptrdiff_t                         difference_type;
			typedef const MeshT&                      mesh_ref;
			typedef const MeshT*                      mesh_ptr;
			typedef const typename MeshT::Vertex&     reference;
			typedef const typename MeshT::Vertex*     pointer;
			typedef std::vector<VertexHandle>   VertexContainer;
		public:
			/** default constructor */
			ConstVertexVertexIterT() : mesh_(NULL), lap_counter_(0)
			{
			}

			/** construct with mesh and a half edge */
			ConstVertexVertexIterT(mesh_ref _mesh, const typename VertexContainer::const_iterator & _start, const typename VertexContainer::const_iterator & _v_end, bool _end = false) : 
			    mesh_(&_mesh),
				start_(0),
				vh_(0),
				lap_counter_(_end)

			{
				vertices_.assign(_start, _v_end);
			}

			/** construct with mesh and a half face */
			ConstVertexVertexIterT(mesh_ref _mesh, VertexContainer _vertices, bool _end = false) : 
			mesh_(&_mesh),
				vertices_(_vertices),
				start_(0),
				vh_(0),
				lap_counter_(_end)
			{
			}

			/** copy constructor */
			ConstVertexVertexIterT(const ConstVertexVertexIterT<MeshT> & _rhs) : mesh_(_rhs.mesh_),
				start_(_rhs.start_), vh_(_rhs.vh_), vertices_(_rhs.vertices_), lap_counter_(_rhs.lap_counter_) 
			{
			}

		public:
			ConstVertexVertexIterT & operator = (const VertexVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				vh_          = _rhs.vh_;
				vertices_    = _rhs.vertices_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}
			ConstVertexVertexIterT & operator = (const ConstVertexVertexIterT<MeshT> & _rhs)
			{
				mesh_        = _rhs.mesh_;
				start_       = _rhs.start_;
				vh_          = _rhs.vh_;
				vertices_    = _rhs.vertices_;
				lap_counter_ = _rhs.lap_counter_;
				return *this;
			}

			bool operator ==  (const ConstVertexVertexIterT<MeshT> & _rhs) const
			{
				return (
					(mesh_        == _rhs.mesh_) &&
					(start_       == _rhs.start_) &&
					(vh_          == _rhs.vh_) &&
					(compare_vertices(vertices_, _rhs.vertices_)) && 
					(lap_counter_ == _rhs.lap_counter_)
					);

			}

			bool operator !=  (const ConstVertexVertexIterT<MeshT> & _rhs) const
			{
				return !(operator == (_rhs));
			}


			/** increment operator */
			ConstVertexVertexIterT & operator ++ ()
			{
				assert(mesh_);
				++ vh_;
				if (vh_ == start_)
				{
					++ lap_counter_;
				}
				return (*this);				
			}

			/** pre-decrement operator */
			ConstVertexVertexIterT & operator -- ()
			{
				assert(mesh_);
				if (vh_ == start_)
				{
					-- lap_counter_;
				}
				-- vh_;
				return (*this);				
			}

			/** get the current half handle	*/
			VertexHandle current_vertex_handle() const
			{
				return vertices_[vh_];
			}
			/** get the current hedron handle */
			VertexHandle handle() const
			{
				return current_vertex_handle();
			}

			/** return a reference to current handle */
			reference operator *() const
			{
				assert(mesh_);
				return mesh_->handl_to_entity(handle());
			}

			/** cast the current handle to the target */
			operator VertexHandle() const
			{
				assert(mesh_);
				return handle();
			}

			/** return a pointer to the current handle */
			pointer operator -> () const
			{
				assert(mesh_);
				return &mesh_->handl_to_entity(handle());
			}

			/** return whether the circulator is still valid 
			*   After one complete round the hedron, the circulator
			*   becomes invalid.
			*/
			operator bool() const
			{
				return ((vh_ >=0) && (vh_ < vertices_.size())) && ((start_ != vh_) || (lap_counter_ == 0));
			}
		private:
			/** compare two array hedrons */
			bool compare_vertices(const VertexContainer & _vc0, const VertexContainer & _vc1)
			{
				if (_vc0.size() != _vc1.size())
				{
					return false;
				}
				for (unsigned int i = 0; i < _vc0.size(); i ++)
				{
					if (_vc0[i] != _vc1[i])
					{
						return false;
					}
				}

				return true;
			}


		private:
			mesh_ptr       mesh_;
			unsigned int   start_;
			unsigned int   vh_;
			VertexContainer vertices_;
			int            lap_counter_;
		};







			
//--------------------------------------------------------------------------------------------------------------------
     } // namespace Circulators
} // namespace OVM
#endif
