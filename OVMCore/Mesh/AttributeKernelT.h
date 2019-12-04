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

#ifndef _OVM_ATTRIBUTE_KERNEL_H_
#define _OVM_ATTRIBUTE_KERNEL_H_
#include <OVM/OVMCore/system/config.h>
#include <OVM/OVMCore/Mesh/Handles.h>
#include <OVM/OVMCore/Util/PropertyContainer.h>



namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	template < class MeshItems, class KernelT >
	class AttributeKernelT : public KernelT
	{
	public:
		typedef typename MeshItems::Vertex   Vertex;
		typedef typename MeshItems::HalfEdge HalfEdge;
		typedef typename MeshItems::HalfFace HalfFace;
		typedef typename MeshItems::Hedron   Hedron;

		typedef typename KernelT::HedronIter     HedronIter;
		typedef typename KernelT::HalfFaceIter   HalfFaceIter;
		typedef typename KernelT::HalfEdgeIter   HalfEdgeIter;
		typedef typename KernelT::VertexIter     VertexIter;

		typedef typename KernelT::ConstHedronIter     ConstHedronIter;
		typedef typename KernelT::ConstHalfFaceIter   ConstHalfFaceIter;
		typedef typename KernelT::ConstHalfEdgeIter   ConstHalfEdgeIter;
		typedef typename KernelT::ConstVertexIter     ConstVertexIter;

		typedef typename MeshItems::Point  Point;
		typedef typename Point::Scalar     Scalar;
		typedef typename MeshItems::Normal Normal;

		typedef typename MeshItems::VertexHandle   VertexHandle;
		typedef typename MeshItems::HalfEdgeHandle HalfEdgeHandle;
		typedef typename MeshItems::HalfFaceHandle HalfFaceHandle;
		typedef typename MeshItems::HedronHandle   HedronHandle;	

		enum Attribs
		{
			VAttrib  = MeshItems::VAttrib,
			HEAttrib = MeshItems::HEAttrib,
			HFAttrib = MeshItems::HFAttrib,
			HAttrib  = MeshItems::HAttrib

		};
	public:
		typedef VPropHandleT<Point>   PointPropertyHandle;
		typedef VPropHandleT<bool>    PointBoundaryPropertyHandle;
		typedef HFPropHandleT<Normal> HFNormalPropertyHandle;
		typedef HFPropHandleT<int>    HFRegionPropertyHandle;
		typedef HPropHandleT<int>     HedronBoundaryPropertyHandle;
		typedef HPropHandleT<int>     HedronRegionPropertyHandle;
		typedef VPropHandleT<bool>    VertexStatus;
		typedef HEPropHandleT<bool>   HalfEdgeStatus;
		typedef HFPropHandleT<bool>   HalfFaceStatus;
	public:
		AttributeKernelT() : re_hf_normals_(0), re_hf_regions_(0), re_hedron_regions_(0)
		{
			KernelT::add_property(points_, "_v_geometry_points_");
			KernelT::add_property(point_boundaries_, "_v_boundaries_");
			KernelT::add_property(hedron_boundaries_, "_h_boundaries_");
			if (HFAttrib && (!re_hf_normals_))
			{
				request_hf_normals();
			}
			if (HFAttrib && (!re_hf_regions_))
			{
				request_hf_regions();
			}
			if (HAttrib && (!re_hedron_regions_))
			{
				request_hedron_regions();
			}
			
		}
		virtual ~ AttributeKernelT()
		{
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		void request_hf_normals()
		{
			if (!re_hf_normals_)
			{
				++ re_hf_normals_;
				KernelT::add_property(hf_normals_, "_hf_normals_");
			}
		}
		void release_hf_normals()
		{
			if (re_hf_normals_ && (!(-- re_hf_normals_)))
			{
				KernelT::remove_property(hf_normals_);
			}
			
		}
		void request_hf_regions()
		{
			if (!re_hf_regions_)
			{
				++ re_hf_regions_;
				KernelT::add_property(hf_regions_, "_hf_regions_");
			}
		}
		void release_hf_regions()
		{
			if (re_hf_regions_ && (!(-- re_hf_regions_)))
			{
				KernelT::remove_property(hf_regions_);
			}

		}
		void request_hedron_regions()
		{
			if (!re_hedron_regions_)
			{
				++ re_hedron_regions_;
				KernelT::add_property(hedron_regions_, "_hedron_regions_");
			}
		}
		void release_hedron_regions()
		{
			if (re_hedron_regions_ && (!(-- re_hedron_regions_)))
			{
				KernelT::remove_property(hedron_regions_);
			}

		}
	public:
		bool has_hf_normals() const
		{
			return re_hf_normals_ != 0;
		}
		bool has_hf_regions() const
		{
			return re_hf_regions_ != 0;
		}
		bool has_hedron_regions() const
		{
			return re_hedron_regions_ != 0;
		}
	public:
		/** retrieve the points of the kernel */
		const Point * points() const
		{
			return KernelT::property(points_).data();
		}
		/** retrieve the geometry point of a vertex */
		const Point &  point(VertexHandle _vh) const
		{
			return KernelT::property(points_, _vh);
		}		
		Point & point(VertexHandle _vh) 
		{
			return KernelT::property(points_, _vh);
		}		
		void set_point(VertexHandle _vh, const Point& _p)
		{ 
			KernelT::property(points_, _vh) = _p;
		}
		/** retrieve the geometry point of a vertex */
		const Point & point(const ConstVertexIter & _v_it) const
		{
			return KernelT::property(points_, KernelT::handle(*_v_it));
		}
		/** retrieve the geometry point of a vertex */
		Point &  point(const ConstVertexIter & _v_it) 
		{
			return KernelT::property(points_, KernelT::handle(*_v_it));
		}			
		void set_point(const VertexIter &	_v_it, const Point& _p)
		{ 
			KernelT::property(points_, KernelT::handle(*_v_it)) = _p;
		}
	public:
		const Normal * normals() const
		{
			return KernelT::property(hf_normals_).data();
		}
		Normal & normal(const HalfFaceHandle & _hfh)
		{
			return KernelT::property(hf_normals_, _hfh);
		}
		const Normal normal(const HalfFaceHandle & _hfh) const
		{
			return KernelT::property(hf_normals_, _hfh);
		}
		void set_normal(HalfFaceHandle _hfh, const Normal& _n)
		{ 
			KernelT::property(hf_normals_, _hfh) = _n;
		}
		const Normal &  normal(const ConstHalfFaceIter & _hf_it) const
		{
			return KernelT::property(hf_normals_, KernelT::handle(*_hf_it));
		}
		void set_normal(const HalfFaceIter & _hf_it, const Normal& _n)
		{ 
			KernelT::property(hf_normals_, KernelT::handle(*_hf_it)) = _n;
		}

		bool is_boundary_vertex(VertexHandle _vh) const
		{
			return KernelT::property(point_boundaries_, _vh);
		}
		//bool is_boundary_vertex(const VertexIter & _v_it) const
		//{
		//	return property(point_boundaries_, handle(_v_it));
		//}
		bool is_boundary_vertex(const ConstVertexIter & _v_it) const
		{
			return KernelT::property(point_boundaries_, KernelT::handle(*_v_it));
		}
		void set_vertex_boundary(VertexHandle _vh, bool _is_boundary)
		{
			KernelT::property(point_boundaries_, _vh) = _is_boundary;
		}
		void set_vertex_boundary(const ConstVertexIter & _v_it, bool _is_boundary)
		{
			KernelT::property(point_boundaries_, KernelT::handle(*_v_it)) = _is_boundary;
		}
		//void set_vertex_boundary(const VertexIter & _v_it, bool _is_boundary)
		//{
		//	property(point_boundaries_, handle(*_v_it)) = _is_boundary;
		//}
		int hedron_boundary_type(HedronHandle _hh) const
		{
			return KernelT::property(hedron_boundaries_, _hh);
		}
		int hedron_boundary_type(const ConstHedronIter & _h_it) const
		{
			return KernelT::property(hedron_boundaries_, KernelT::handle(*_h_it));
		}
		void set_hedron_boundary(HedronHandle _hh, int _hedron_boundary)
		{
			KernelT::property(hedron_boundaries_, _hh) = _hedron_boundary;
		}
		//void set_vertex_boundary(const ConstVertexIter & _v_it, bool _is_boundary)
		//{
		//	property(point_boundaries_, handle(*_v_it)) = _is_boundary;
		//}
		void set_hedron_boundary(const ConstHedronIter & _h_it, bool _hedron_boundary)
		{
			KernelT::property(hedron_boundaries_, KernelT::handle(*_h_it)) = _hedron_boundary;
		}
		void set_half_face_region(const HalfFaceHandle & _hfh, int _region)
		{
			KernelT::property(hf_regions_, _hfh) = _region;
		}
		void set_half_face_region(const ConstHalfFaceIter & _h_it, int _region)
		{
			KernelT::property(hf_regions_, KernelT::handle(*_h_it)) = _region;
		}
		int & half_face_region(const HalfFaceHandle & _hfh)
		{
			return KernelT::property(hf_regions_, _hfh);
		}
		const int half_face_region(const HalfFaceHandle _hfh) const
		{
			return KernelT::property(hf_regions_, _hfh);
		}
		int & half_face_region(const ConstHalfFaceIter & _h_it)
		{
			return KernelT::property(hf_regions_, KernelT::handle(*_h_it));
		}
		const int half_face_region(const ConstHalfFaceIter & _h_it) const
		{
			return KernelT::property(hf_regions_, KernelT::handle(*_h_it));
		}
		int & hedron_region(const HedronHandle & _h)
		{
			return KernelT::property(hedron_regions_, _h);
		}
		const int & hedron_region(const HedronHandle & _h) const
		{
			return KernelT::property(hedron_regions_, _h);
		}
		int & hedron_region(const ConstHedronIter & _h_it)
		{
			return KernelT::property(hedron_regions_, KernelT::handle(*_h_it));
		}
		const int hedron_region(const ConstHedronIter & _h_it) const
		{
			return KernelT::property(hedron_regions_, KernelT::handle(*_h_it));
		}
	public:
		/** return the valence of a vertex */
		//unsigned int valence(VertexHandle _vh) const
		//{
		//	return vertex_star_vertices(_vh).size();
		//}
	protected:
	//-----------------------------------------------------------------------------------------------------------------
	private:
		PointPropertyHandle          points_;
		PointBoundaryPropertyHandle  point_boundaries_;
		HedronBoundaryPropertyHandle hedron_boundaries_;
		HedronRegionPropertyHandle   hedron_regions_;
		HFNormalPropertyHandle       hf_normals_;
		HFRegionPropertyHandle       hf_regions_;

		unsigned int re_hf_normals_;
		unsigned int re_hf_regions_;
		unsigned int re_hedron_regions_;
	};
//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM
#endif