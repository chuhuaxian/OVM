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

#ifndef _OVM_TH_MESH_H_
#define _OVM_TH_MESH_H_


#include <OVM/OVMCore/system/config.h>
#include <OVM/OVMCore/Mesh/BaseMesh.h>
#include <OVM/OVMCore/Mesh/THKernel.h>


namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------

	/** \class THMesh the mesh for tetrahedral and hexahedral mesh. 
	*   It inherits from the BaseMesh, \see BaseMesh. It uses the 
	*   THKernel as its kernel, \see THKernel.
	*/
	template < class KernelT >
	class THMeshT : public KernelT   
	{
		
	public:
		typedef typename KernelT::Point  Point;
		typedef typename KernelT::Normal Normal;
		typedef typename Point::Scalar   Scalar;

		typedef typename KernelT::Vertex   Vertex;
		typedef typename KernelT::HalfEdge HalfEdge;
		typedef typename KernelT::HalfFace HalfFace;
		typedef typename KernelT::Hedron   Hedron;

		typedef typename KernelT::VertexHandle   VertexHandle;
		typedef typename KernelT::HalfEdgeHandle HalfEdgeHandle;
		typedef typename KernelT::HalfFaceHandle HalfFaceHandle;
		typedef typename KernelT::HedronHandle   HedronHandle;	


		typedef typename KernelT::HedronIter     HedronIter;
		typedef typename KernelT::HalfFaceIter   HalfFaceIter;
		typedef typename KernelT::HalfEdgeIter   HalfEdgeIter;
		typedef typename KernelT::VertexIter     VertexIter;

		typedef typename KernelT::ConstHedronIter     ConstHedronIter;
		typedef typename KernelT::ConstHalfFaceIter   ConstHalfFaceIter;
		typedef typename KernelT::ConstHalfEdgeIter   ConstHalfEdgeIter;
		typedef typename KernelT::ConstVertexIter     ConstVertexIter;	
		

		typedef std::vector<Point> PointContainer;
	//-----------------------------------------------------------------------------------------------------------------
	public:		
		THMeshT(unsigned int _mesh_type = 1)
		{
			THKernel::set_kernel_type(_mesh_type - 1);
		}
		virtual ~THMeshT()
		{
			clear();
		}
		//-----------------------------------------------------------------------------------------------------------------
	public:
		/** clear the containers */
		void clear()
		{
			KernelT::clear();
		}
	public:

		/** build the topology of the mesh
		*   \param _indices the point indices of the hedrons.
		*   \return bool true for success.
		*/
		bool build_topology(const std::vector<unsigned int> & _indices)
		{
			if (!KernelT::build_topology(_indices))
			{
				return false;
			}
			update_boundary();
			return true;
		}
	    /** build the region property of the mesh 
	    *   \param _region_property the property of regions, for tetrahedron, 4 numbers are a group, 5 for hexahedron
	    */
		void build_region_property(const std::vector<unsigned int> & _region_property);

	public:
		/** return the out half edges of an input vertex */
		//std::vector<HalfEdgeHandle> o_half_edges(const VertexHandle & _vh) const
		//{
		//	return THKernel::o_half_edges(_vh);
		//}
		///** return the in half edges of an input vertex  */
		//std::vector<HalfEdgeHandle> i_half_edges(const VertexHandle & _vh) const
		//{
		//	return THKernel::i_half_edges(_vh);
		//}

		///** return the out half edges of an input vertex */
		//std::vector<HalfEdgeHandle> o_half_edges(const ConstVertexIter & _v_it) const
		//{
		//	return THKernel::o_half_edges(_v_it);
		//}
		///** return the in half edges of an input vertex  */
		//std::vector<HalfEdgeHandle> i_half_edges(const ConstVertexIter & _v_it) const
		//{
		//	return THKernel::i_half_edges(_v_it);
		//} 
		///** retrieve the one ring adjacent vertices of a vertex */
		//std::vector<VertexHandle> vertex_star_vertices(const VertexHandle & _vh) const
		//{
		//	return THKernel::vertex_star_vertices(_vh);
		//}
		///** retrieve the one ring adjacent vertices of a vertex */
		//std::vector<VertexHandle> vertex_star_vertices(const ConstVertexIter & _v_it) const
		//{
		//	return THKernel::vertex_star_vertices(_v_it);
		//}
		///** retrieve the star  hedrons of a vertex  */
		//std::vector<HedronHandle> vertex_star_hedrons(const VertexHandle & _vh) const
		//{
		//	return THKernel::vertex_star_hedrons(_vh);
		//}
		///** return the in half edges of an input vertex  */
		//std::vector<HedronHandle> vertex_star_hedrons(const ConstVertexIter & _v_it) const
		//{
		//	return THKernel::vertex_star_hedrons(_v_it);
		//}
	public:
		/** add a new vertex
		*   \param _p the point
		*   \return the vertex handle
		*/
		VertexHandle add_vertex(Point _p) 
		{
			VertexHandle vh;
			vh = KernelT::new_vertex();
			KernelT::set_point(vh, _p);
			return vh;
		}

		/** add a hedron into the mesh
		*   \param _h_idx the vertex handles of the hedron
		*   \return the hedron handle
		*/
		HedronHandle add_hedron(const std::vector<VertexHandle> & _h_idx)
		{
			return THKernel::add_hedron(_h_idx);
		}
		/** retrieve the vertex handle of a point
		*   \param _p the point 
		*   \return the vertex handle, if it equals to -1, it is invalid
		*/
		VertexHandle find_vertex_handle(const Point & _p) const
		{
			
			for (ConstVertexIter cv_it = typename KernelT::vertices_begin(); cv_it != typename KernelT::vertices_end(); ++ cv_it )
			{
				if (point(cv_it) == _p)
				{
					return VertexHandle(cv_it - typename KernelT::vertices_begin());
				}				
			}			
			return VertexHandle(-1);			
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		/** check is the hedron is a boundary hedron
		*   \param _hh the hedron
		*   \param _type 1 for face-boundary, 2 for only edge-boundary, 4 for only vertex-boundary 
		*   \param bool
		*/
		bool is_boundary(HedronHandle _hh, unsigned int _type = 1) const;
		/** check is the hedron is a boundary hedron
		*   \param _h_it the hedron
		*   \param _type 1 for face-boundary, 2 for only edge-boundary, 4 for only vertex-boundary 
		*   \param bool
		*/
		bool is_boundary(const ConstHedronIter & _h_it, unsigned int _type = 1) const;
		bool is_boundary(VertexHandle _vh)    const;
		bool is_boundary(HalfEdgeHandle _heh) const;
		bool is_boundary(HalfFaceHandle _hfh) const;
		bool is_boundary(const ConstVertexIter & _v_it)     const;
		bool is_boundary(const ConstHalfEdgeIter &  _he_it) const;
		bool is_boundary(const ConstHalfFaceIter &  _hf_it) const;
	public:
		/** update boundary */
		void update_boundary();
		/** update the boundary vertices */
		void update_boundary_vertices();	
		/** update the boundary hedrons */
		void update_boundary_hedrons();		
		/** update the boundary hedron  */
		void update_boundary_hedron(HedronHandle _hh);		
		/** update the boundary hedron  */
		void update_boundary_hedron(const ConstHedronIter & _h_it);	
	public:		
		/** update the normals of the half faces */
		void update_hf_normals();
		/** calculate the normal of the face */
		Normal calc_face_normal(const ConstHalfFaceIter _h_it  ) const;
		/** calculate the normal of the face */
		Normal calc_face_normal(HalfFaceHandle _hfh) const;
		/** calculate the normal of the face with three points */
		Normal calc_face_normal(const Point & _p0, const Point & _p1, const Point & _p2) const;
		/** calculate the dihedral angle of two cw faces */
		Scalar calc_cw_dihedral_angle(HalfEdgeHandle _heh);
		/** calculate the dihedral angle of two cw faces */
		Scalar calc_ccw_dihedral_angle(HalfEdgeHandle _heh);
		/** calculate the length length */
		Scalar calc_half_edge_length(HalfEdgeHandle _heh);
		
	public:
		/** check if the flip is ok */
		bool is_flip_ok(HalfFaceHandle _hfh);
		/** check if the flip is ok */
		bool is_flip_ok(HalfEdgeHandle _heh);
		/** check if the flip is ok */
		bool is_flip_ok(HedronHandle _h0, HedronHandle _h1);
		/** check if the flip is ok */
		bool is_flip_ok(HedronHandle _h0, HedronHandle _h1, HedronHandle _h2);
		/** flip two hedrons 2 to 3 */
		std::vector<HedronHandle> flip_23(HalfFaceHandle _hfh);
		/** flip two hedrons 2 to 3 */
		std::vector<HedronHandle> flip_23(HedronHandle _h0, HedronHandle _h1);
		/** flip two hedrons 3 to 2 */
		std::vector<HedronHandle> flip_32(HalfEdgeHandle _heh);
		/** flip two hedrons 3 to 2 */
		std::vector<HedronHandle> flip_32(HedronHandle _h0, HedronHandle _h1, HedronHandle _h2);
	public:
		/** delete hedron */
		bool delete_hedron(HedronHandle _hh);
		/** delete hedron */
		bool delete_hedron(const ConstHedronIter & _h_it);
	public:
		int & half_face_region(const HalfFaceHandle & _hfh);
		const int half_face_region(const HalfFaceHandle & _hfh) const;
		int & half_face_region(const ConstHalfFaceIter & _hf_it);
		const int half_face_region(const ConstHalfFaceIter & _hf_it) const;
	//-----------------------------------------------------------------------------------------------------------------
	public:
		/** retrieve the type ov the mesh
		*   \return 1 for tetrahedron, 2 for hexahedron
		*/
		unsigned int mesh_type() const
		{
			return KernelT::kernel_type();
		}
		/** set the type of the mesh
		*   \param _mesh_type 1 for tetrahedron, 2 for hexahedron
		*/
		void set_mesh_type(unsigned int _mesh_type)
		{
			KernelT::set_kernel_type(_mesh_type);
		}

	public:
		/** set the points of the mesh */
		void set_points(const PointContainer & _points)
		{
			for (unsigned int i = 0; i < _points.size(); i ++)
			{
				add_vertex(_points[i]);
			}			
		}
	//-----------------------------------------------------------------------------------------------------------------
	private:
	};


//---------------------------------------------------------------------------------------------------------------------	
} // namespace OVM

#if defined(OVM_INCLUDE_TEMPLATES) && !defined(_OVM_TH_MESH_CPP_)
//#  define OVM_TH_MESH_TEMPLATES
#  include <OVM/OVMCore/Mesh/THMeshT.cpp>
#endif
#endif