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

#ifndef _OVM_TH_KERNEL_H_
#define _OVM_TH_KERNEL_H_

#include <OVM/OVMCore/system/config.h>
#include <OVM/OVMCore/Mesh/TopologyKernel.h>
#include <OVM/OVMCore/Mesh/CirculatorsT.h>


namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	/** this kernel is used for building the topological for
	*   tetrahedron and hexahedron. It inherits from the 
	*   class \see TopologyKernel.
	*/
	class THKernel : public TopologyKernel
	{
	public:
		/** An enum
		*   define the type of the kernel
		*/
		enum KERNELTYPE {TETRAHEDRON = 1, HEXAHEDRON = 2};
		typedef std::vector<unsigned int> IndexContainer; 
	public:
		//--- iterators definition
		typedef KernelHedronIter     HedronIter;
		typedef KernelHalfFaceIter   HalfFaceIter;
		typedef KernelHalfEdgeIter   HalfEdgeIter;
		typedef KernelVertexIter     VertexIter;

		typedef KernelConstHedronIter     ConstHedronIter;
		typedef KernelConstHalfFaceIter   ConstHalfFaceIter;
		typedef KernelConstHalfEdgeIter   ConstHalfEdgeIter;
		typedef KernelConstVertexIter     ConstVertexIter;
	public:
		THKernel (unsigned int _kernel_type = TETRAHEDRON) : kernel_type_(_kernel_type - 1) //TopologyKernel(_kernel_type - 1) 
		  
		{
		}
		virtual ~THKernel()
		{
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		/** retrieve the hedron handle of the half face */
		HedronHandle hedron_handle(const HalfFace & _hf) const;
		/** retrieve the hedron handle of the half face */
		HedronHandle hedron_handle(const ConstHalfFaceIter & _hf_it) const;
		/** retrieve the hedron handle of the half face */
		HedronHandle hedron_handle(const HalfFaceHandle & _hfh) const;
		/** retrieve the hedron handle of the half edge */
		HedronHandle hedron_handle(const HalfEdge & _he) const;
		/** retrieve the hedron handle of the half edge */
		HedronHandle hedron_handle(const ConstHalfEdgeIter & _he_it) const;
		/** retrieve the hedron handle of the half edge */
		HedronHandle hedron_handle(const HalfEdgeHandle & _heh) const;

		/** retrieve the half face handle of a half edge */
		HalfFaceHandle half_face_handle(const HalfEdge & _he) const;
		/** retrieve the half face handle of a half edge */
		HalfFaceHandle half_face_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the half edge handle of a vertex */
		HalfEdgeHandle half_edge_handle(const Vertex & _v) const;
		/** retrieve the half edge handle of a vertex */
		HalfEdgeHandle half_edge_handle(const VertexHandle & _vh) const;

		/** retrieve the face handle of the hedron */
		HalfFaceHandle first_half_face_handle(const Hedron & _h) const;
		/** retrieve the face handle of the hedron */
		HalfFaceHandle first_half_face_handle(const ConstHedronIter & _h_it) const;
		/** retrieve the face handle of the hedron */
		HalfFaceHandle first_half_face_handle(const HedronHandle & _hh) const;
		/** retrieve the first half edge handle of the hedron */
		HalfEdgeHandle first_half_edge_handle(const ConstHedronIter & _h_it) const;
		/** retrieve the first half edge handle of the hedron */
		HalfEdgeHandle first_half_edge_handle(const HedronHandle & _hh) const;
		/** retrieve the first vertex handle of the hedron */
		VertexHandle   first_vertex_handle(const HedronHandle & _hh) const;
		/** retrieve the first vertex handle of the hedron */
		VertexHandle   first_vertex_handle(const ConstHedronIter & _h_it) const;

		/** retrieve the previous half face handle */
		HalfFaceHandle prev_half_face_handle(const HalfFaceHandle & _hfh) const;
		/** retrieve the next half face handle     */
		HalfFaceHandle next_half_face_handle(const HalfFaceHandle & _hfh) const;
		/** retrieve the opposite half face handle */
		HalfFaceHandle  opp_half_face_handle(const HalfFaceHandle & _hfh) const;
		/** retrieve the previous non boundary half face handle */
		HalfFaceHandle prev_non_boundary_half_face_handle(const HalfFaceHandle & _hfh) const;
		/** retrieve the next non boundary half face handle     */
		HalfFaceHandle next_non_boundary_half_face_handle(const HalfFaceHandle & _hfh) const;
		/** retrieve the first half edge handle of the half face */
		HalfEdgeHandle first_half_edge_handle(const HalfFaceHandle & _hfh) const;
		

		/** retrieve the previous half edge handle */
		HalfEdgeHandle prev_half_edge_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the next half edge handle     */
		HalfEdgeHandle next_half_edge_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the mate half edge handle     */
		HalfEdgeHandle cw_opp_half_edge_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the opposite half edge handle */
		HalfEdgeHandle ccw_opp_half_edge_handle(const HalfEdgeHandle & _heh)  const;
		/** retrieve the start vertex handle of the half edge */
		VertexHandle from_vertex_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the end vertex handle of the half edge   */
		VertexHandle to_vertex_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the ccw hedron hedron handle of the half edge */
		HedronHandle ccw_hedron_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the cw hedron hedron handle of the half edge */
		HedronHandle cw_hedron_handle(const HalfEdgeHandle & _heh) const;


		

		/** retrieve the previous vertex half edge handle of a hedron */
		HalfEdgeHandle prev_hedron_vertex_half_edge_handle(const HalfEdgeHandle & _heh) const;
		/** retrieve the next vertex half edge handle of a hedron     */
		HalfEdgeHandle next_hedron_vertex_half_edge_handle(const HalfEdgeHandle & _heh) const;
		
	protected:
		/** retrieve the out half edges of a vertex */
		std::vector<HalfEdgeHandle> o_half_edges(const VertexHandle & _vh) const;
		/** retrieve the in  half edges of a vertex */
		std::vector<HalfEdgeHandle> i_half_edges(const VertexHandle & _vh) const;
		/** retrieve the out half edges of a vertex */
		std::vector<HalfEdgeHandle> o_half_edges(const ConstVertexIter & _v_it) const;
		/** retrieve the in  half edges of a vertex */
		std::vector<HalfEdgeHandle> i_half_edges(const ConstVertexIter & _v_it) const;
		/** retrieve the one ring adjacent vertices of a vertex */
		std::vector<VertexHandle> vertex_star_vertices(const VertexHandle & _vh) const;
		/** retrieve the one ring adjacent vertices of a vertex */
		std::vector<VertexHandle> vertex_star_vertices(const ConstVertexIter & _v_it) const;
		/** retrieve the star  hedrons of a vertex  */
		std::vector<HedronHandle> vertex_star_hedrons(const VertexHandle & _vh) const;
		/** retrieve the star  hedrons of a vertex  */
		std::vector<HedronHandle> vertex_star_hedrons(const ConstVertexIter & _v_it) const;
	protected:
		/** build the topology of the mesh
		*   \param _indices the point indices of the hedrons.
		*   \return bool true for success.
		*/
		bool build_topology(const IndexContainer & _indices);
		/** build the opposite half face */
		bool build_opposite_half_faces();
		/** build the opposite half edges */
		bool build_opposite_half_edges();
		/** set the half face handle */
		void set_opp_half_face(HalfFaceHandle _hfh, HalfFaceHandle _ohfh, bool _double = true);
		/** collect the opp half faces in opp_faces_ */
		void opp_half_faces_collection();
		/** remove the opp _half_faces in opp_faces_ */
		void remove_opp_half_faces(HalfFaceHandle _hfh);
		/** swap the hedron with topology */
		void swap_hedron_with_topology(HedronHandle _h0, HedronHandle _h1);
	protected:
		/** update the opp_faces_
		*   \param _hfh the half face 
		*   \param _removed true for removing from opp_faces_, false for not
		*   \return void
		*/
		void update_opp_face(HalfFaceHandle _hfh, bool _removed = false);
	private:
		/** build the opposite half face */
		bool build_opposite_half_faces(const HalfFaceIter & _hf_begin, const HalfFaceIter & _hf_end);
		/** build the opposite half face */
		bool build_opposite_half_faces(const std::vector<HalfFaceHandle> & _hfhs); 
		/** build the opposite half edges */
		bool build_opposite_half_edges(const HalfEdgeIter & _he_begin, const HalfEdgeIter & _he_end);
		/** build the opposite half edges */
		bool build_opposite_half_edges(const std::vector<HalfEdgeHandle> & _hehs);
		
	//-----------------------------------------------------------------------------------------------------------------
	public:
		//--- circulators
		typedef Circulators::HedronHedronIterT<THKernel>           HedronHedronIter;
		typedef Circulators::ConstHedronHedronIterT<THKernel>      ConstHedronHedronIter;
		typedef Circulators::HedronHalfFaceIterT<THKernel>         HedronHalfFaceIter;
		typedef Circulators::ConstHedronHalfFaceIterT<THKernel>    ConstHedronHalfFaceIter;
		typedef Circulators::HedronHalfEdgeIterT<THKernel>         HedronHalfEdgeIter;
		typedef Circulators::ConstHedronHalfEdgeIterT<THKernel>    ConstHedronHalfEdgeIter;
		typedef Circulators::HedronVertexIterT<THKernel>           HedronVertexIter;
		typedef Circulators::ConstHedronVertexIterT<THKernel>      ConstHedronVertexIter;
		typedef Circulators::HalfFaceVertexIterT<THKernel>         HalfFaceVertexIter;
		typedef Circulators::ConstHalfFaceVertexIterT<THKernel>    ConstHalfFaceVertexIter;
		typedef Circulators::HalfFaceHalfEdgeIterT<THKernel>       HalfFaceHalfEdgeIter;
		typedef Circulators::ConstHalfFaceHalfEdgeIterT<THKernel>  ConstHalfFaceHalfEdgeIter;
		typedef Circulators::HalfEdgeHedronIterT<THKernel>         HalfEdgeHedronIter;
		typedef Circulators::ConstHalfEdgeHedronIterT<THKernel>    ConstHalfEdgeHedronIter;
		typedef Circulators::VertexHedronIterT<THKernel>           VertexHedronIter;
		typedef Circulators::ConstVertexHedronIterT<THKernel>      ConstVertexHedronIter;
		typedef Circulators::VertexHedronHalfFaceIterT<THKernel>   VertexHedronHalfFaceIter;
		typedef Circulators::ConstVertexHedronHalfFaceIterT<THKernel>   ConstVertexHedronHalfFaceIter;
		typedef Circulators::VertexVertexIterT<THKernel>           VertexVertexIter;
		typedef Circulators::ConstVertexVertexIterT<THKernel>      ConstVertexVertexIter;
	public:
		/** return the first neighbor of the input hedron ()*/
		HedronHedronIter hedron_hedron_iter(const HedronHandle & _hh);
		/** return the first neighbor of the input hedron   */
		HedronHedronIter hedron_hedron_iter(const HedronIter & _h_it); 
		/** return the first neighbor of the input hedron ()*/
		ConstHedronHedronIter const_hedron_hedron_iter(const HedronHandle & _hh) const;
		/** return the first neighbor of the input hedron   */
		ConstHedronHedronIter const_hedron_hedron_iter(const ConstHedronIter & _h_it) const;

		/** return the first half face iter of the input hedron ()*/
		HedronHalfFaceIter hedron_half_face_iter(const HedronHandle & _hh);
		/** return the first half face iter of the input hedron   */
		HedronHalfFaceIter hedron_half_face_iter(const HedronIter & _h_it); 
		/** return the first const half face iter of the input hedron */
		ConstHedronHalfFaceIter const_hedron_half_face_iter(const HedronHandle & _hh) const;
		/** return the first const half face iter of the input hedron */
		ConstHedronHalfFaceIter const_hedron_half_face_iter(const ConstHedronIter & _h_it) const; 

		/** return the first half edge iter of the input hedron ()*/
		HedronHalfEdgeIter hedron_half_edge_iter(const HedronHandle & _hh);
		/** return the first half edge iter of the input hedron   */
		HedronHalfEdgeIter hedron_half_edge_iter(const HedronIter & _h_it); 
		/** return the first const half edge iter of the input hedron */
		ConstHedronHalfEdgeIter const_hedron_half_edge_iter(const HedronHandle & _hh) const;
		/** return the first const half edge iter of the input hedron */
		ConstHedronHalfEdgeIter const_hedron_half_edge_iter(const ConstHedronIter & _h_it) const; 

		/** return the first vertex iter of the input hedron ()*/
		HedronVertexIter hedron_vertex_iter(const HedronHandle & _hh);
		/** return the first vertex iter of the input hedron   */
		HedronVertexIter hedron_vertex_iter(const HedronIter & _h_it); 
		/** return the first const vertex iter of the input hedron */
		ConstHedronVertexIter const_hedron_vertex_iter(const HedronHandle & _hh) const;
		/** return the first const vertex iter of the input hedron */
		ConstHedronVertexIter const_hedron_vertex_iter(const ConstHedronIter & _h_it) const; 

		/** return the first vertex iter of the input half face */
		HalfFaceVertexIter half_face_vertex_iter(const HalfFaceHandle & _hh);
		/** return the first vertex iter of the input half face */
		HalfFaceVertexIter half_face_vertex_iter(const HalfFaceIter & _h_it); 
		/** return the first const vertex iter of the input half face */
		ConstHalfFaceVertexIter const_half_face_vertex_iter(const HalfFaceHandle & _hh) const;
		/** return the first const vertex iter of the input half face */
		ConstHalfFaceVertexIter const_half_face_vertex_iter(const ConstHalfFaceIter & _h_it) const; 

		/** return the first half edge iter of the input half face */
		HalfFaceHalfEdgeIter half_face_half_edge_iter(const HalfFaceHandle & _hh);
		/** return the first half edge iter of the input half face */
		HalfFaceHalfEdgeIter half_face_half_edge_iter(const HalfFaceIter & _h_it); 
		/** return the first const half edge iter of the input half face */
		ConstHalfFaceHalfEdgeIter const_half_face_half_edge_iter(const HalfFaceHandle & _hh) const;
		/** return the first const half edge iter of the input half face */
		ConstHalfFaceHalfEdgeIter const_half_face_half_edge_iter(const ConstHalfFaceIter & _h_it) const; 


		/** return the first hedron of the half edge */
		HalfEdgeHedronIter half_edge_hedron_iter(const HalfEdgeHandle & _heh);
		/** return the first hedron of the half edge */
		HalfEdgeHedronIter half_edge_hedron_iter(const HalfEdgeIter & _he_it); 
		/** return the first hedron of the half edge */
		ConstHalfEdgeHedronIter const_half_edge_hedron_iter(const HalfEdgeHandle & _heh) const;
		/** return the first hedron of the half edge */
		ConstHalfEdgeHedronIter const_half_edge_hedron_iter(const ConstHalfEdgeIter & _he_it) const;


		/** return the first hedron of the vertex */
		VertexHedronIter vertex_hedron_iter(const VertexHandle & _vh);
		/** return the first hedron of the vertex */
		VertexHedronIter vertex_hedron_iter(const VertexIter & _v_it); 
		/** return the first hedron of the vertex */
		ConstVertexHedronIter const_vertex_hedron_iter(const VertexHandle & _vh) const;
		/** return the first hedron of the vertex */
		ConstVertexHedronIter const_vertex_hedron_iter(const ConstVertexIter & _v_it) const;


		/** return the first half face of a hedron attached to the vertex */
		VertexHedronHalfFaceIter vertex_hedron_half_face_iter(const VertexHandle & _vh, HedronHandle _hh);
		/** return the first half face of a hedron attached to the vertex */
		VertexHedronHalfFaceIter vertex_hedron_half_face_iter(const VertexIter & _v_it, HedronHandle _hh); 
		/** return the first half face of a hedron attached to the vertex */
		ConstVertexHedronHalfFaceIter const_vertex_hedron_half_face_iter(const VertexHandle & _vh, HedronHandle _hh) const;
		/** return the first half face of a hedron attached to the vertex */
		ConstVertexHedronHalfFaceIter const_vertex_hedron_half_face_iter(const ConstVertexIter & _v_it, HedronHandle _hh) const;

		/** return the first adjacent vertex of the vertex */
		VertexVertexIter vertex_vertex_iter(const VertexHandle & _vh);
		/** return the first adjacent vertex of the vertex */
		VertexVertexIter vertex_vertex_iter(const VertexIter & _v_it); 
		/** return the first adjacent vertex of the vertex */
		ConstVertexVertexIter const_vertex_vertex_iter(const VertexHandle & _vh) const;
		/** return the first adjacent vertex of the vertex */
		ConstVertexVertexIter const_vertex_vertex_iter(const ConstVertexIter & _v_it) const;
	public:
		/** compute the valence of the vertex */
		size_t valence(VertexHandle _vh) const;
	//-----------------------------------------------------------------------------------------------------------------
	public:
		/** add a hedron into the mesh
		*   \param _h_idx the vertex handles of the hedron
		*   \return the hedron handle
		*/
		HedronHandle add_hedron(const std::vector<VertexHandle> & _h_idx);
		/** delete a hedron
		*   \param _hh the input hedron
		*   \return true for success
		*/
		bool delete_hedron(const ConstHedronIter & _h_it, bool _delete_isolate_vertices = true);
		/** delete a hedron
		*   \param _hh the input hedron
		*   \return true for success
		*/
		bool delete_hedron(HedronHandle _hh, bool _delete_isolate_vertices = true);
		/** collect the garbage. Invoke it after deletion */
		void garbage_collection(bool _h = true, bool _hf = true, bool _he = true, bool _v = true);
		/** split 1-4 */
		VertexHandle split(HedronHandle _hh, VertexHandle _vh);
		/** split 1-3 */
		VertexHandle split(HalfFaceHandle _hfh, VertexHandle _vh);
		/** split 1-2 */
		VertexHandle split(HalfEdgeHandle _heh, VertexHandle _vh);
	public:
		/** Half edge collapse: collapse the from-vertex of _heh into 
		*   the to-vertex.
		*   Needs vertex/edge/half-face/hedron status attributes to delete the generated items.
		*   Before collapsing the half edges, it requires to check the topological consistences
		*   using is_collapse_ok()
		*/
		void collapse(HalfEdgeHandle _heh);
		/** Half face collapse: collapse the half face of two adjacent hedrons  
		*   Needs vertex/edge/half-face/hedron status attributes to delete the generated items.
		*   Before collapsing the half edges, it requires to check the topological consistences
		*   using is_collapse_ok()
		*/
		void collapse(HalfFaceHandle _hfh);
		/** return if collapsing half edge _heh is ok or it would lead to
		*   topological inconsistencies.
		*/
		bool is_collapse_ok(HalfEdgeHandle _heh);
		/** return if collapsing half face _hfh is ok or it would lead to
		*   topological inconsistencies.
		*/
		bool is_collapse_ok(HalfFaceHandle _hfh);
	public:
		/** clear */
		void clear()
		{
			 TopologyKernel::clear();	
			
		}
		
	//-----------------------------------------------------------------------------------------------------------------
	public:
		/** retrieve the type of the kernel
		*/
		unsigned int kernel_type() const 
		{
			return kernel_type_ + 1;
		}
		/** set the type of the kernel
		*/
		void set_kernel_type(unsigned int _kernel_type)
		{
			kernel_type_ = _kernel_type - 1;
		}
	//-----------------------------------------------------------------------------------------------------------------
	protected:
		unsigned int kernel_type_;  /**< kernel type. 0 for tetrahedron, while 1 for hexahedron */
	};
//---------------------------------------------------------------------------------------------------------------------
}  // namespace of OVM
//---------------------------------------------------------------------------------------------------------------------
#endif 