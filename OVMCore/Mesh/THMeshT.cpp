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
#define _OVM_TH_MESH_CPP_
#include <OVM/OVMCore/Mesh/THMeshT.h>
#include <set>

#define _THMESH_

namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------

	/** check is the hedron is a boundary hedron
	*   \param _hh the hedron
	*   \param _type 1 for face-boundary, 2 for only edge-boundary, 4 for only vertex-boundary 
	*   \param bool
	*/
	template < class KernelT >
	bool THMeshT<KernelT>::is_boundary(HedronHandle _hh, unsigned int _type) const
	{
		return (KernelT::hedron_boundary_type(_hh) == (int)_type);
	}
	/** check is the hedron is a boundary hedron
	*   \param _h_it the hedron
	*   \param _type 1 for face-boundary, 2 for only edge-boundary, 4 for only vertex-boundary 
	*   \param bool
	*/
	template < class KernelT >
	bool THMeshT<KernelT>::is_boundary(const ConstHedronIter & _h_it, unsigned int _type) const
	{
		return (KernelT::hedron_boundary_type(_h_it) == (int)_type);

	}


	 
	template < class KernelT >
	bool THMeshT<KernelT>::is_boundary(VertexHandle _vh) const
	{
		return KernelT::is_boundary_vertex(_vh);
	}
	template < class KernelT >
	bool THMeshT<KernelT>::is_boundary(const ConstVertexIter & _v_it) const
	{
		return KernelT::is_boundary_vertex(_v_it);
	}
	template < class KernelT >
	bool THMeshT<KernelT>::is_boundary(HalfEdgeHandle _heh) const
	{
		assert(_heh.is_valid());
		return !KernelT::opp_half_face_handle(KernelT::half_face_handle(_heh)).is_valid();
	}
	template < class KernelT >
	bool THMeshT<KernelT>::is_boundary(const ConstHalfEdgeIter & _he_it) const
	{
		return !KernelT::opp_half_face_handle(KernelT::half_face_handle(KernelT::handle(*_he_it))).is_valid();
	}
	template < class KernelT >
	bool THMeshT<KernelT>::is_boundary(HalfFaceHandle _hfh) const
	{
		assert(_hfh.is_valid());
		return !KernelT::opp_half_face_handle(_hfh).is_valid();
	}
	template < class KernelT >
	bool THMeshT<KernelT>::is_boundary(const ConstHalfFaceIter & _hf_it) const
	{
		return !KernelT::opp_half_face_handle(KernelT::handle(*_hf_it)).is_valid();
	}	
	/** update the boundary vertices */
	template < class KernelT >
	void THMeshT<KernelT>::update_boundary_vertices()
	{

		ConstVertexIter v_end(typename KernelT::vertices_end());
		for (ConstVertexIter v_it = typename KernelT::vertices_begin(); v_it != v_end; ++ v_it)
		{
			KernelT::set_vertex_boundary(KernelT::handle(*v_it), false);
		}		
		
		ConstHalfEdgeIter e_end(typename KernelT::half_edges_end());
		for (ConstHalfEdgeIter e_it = typename KernelT::half_edges_begin(); e_it != e_end; ++ e_it)
		{
			VertexHandle vh = KernelT::from_vertex_handle(KernelT::handle(*e_it));
			if (is_boundary(e_it))
			{
				KernelT::set_vertex_boundary(vh, true);
			}
		}		
	}
	/** update the boundary hedrons */
	template < class KernelT >
	void THMeshT<KernelT>::update_boundary()
	{
		update_boundary_vertices();
		update_boundary_hedrons();
	}	
	/** update the boundary hedrons */
	template < class KernelT >
	void THMeshT<KernelT>::update_boundary_hedrons()
	{
		ConstHedronIter h_it;
		ConstHedronIter h_end(typename KernelT::hedrons_end());
		for (h_it = typename KernelT::hedrons_begin(); h_it != h_end; ++ h_it)
		{
			update_boundary_hedron(h_it);
		}
	}	
	/** update the boundary hedron  */
	template < class KernelT >
	void THMeshT<KernelT>::update_boundary_hedron(HedronHandle _hh)
	{
		unsigned int _type;
		_type = 0;
		for (typename KernelT::ConstHedronHalfFaceIter chhf_it = KernelT::const_hedron_half_face_iter(_hh); chhf_it; ++ chhf_it)
		{
			if (is_boundary(chhf_it.handle()))
			{
				KernelT::set_hedron_boundary(_hh, 1);
				_type = 1;
				return;
			}
		}
		if (!_type)
		{
			for (typename KernelT::ConstHedronHalfFaceIter chhf_it = KernelT::const_hedron_half_face_iter(_hh); chhf_it; ++ chhf_it)
			{
				for (typename KernelT::ConstHalfFaceHalfEdgeIter chfhe_it = KernelT::const_half_face_half_edge_iter(chhf_it.handle()); chfhe_it; ++ chfhe_it)
				{
				
					if (is_boundary(KernelT::from_vertex_handle(chfhe_it.handle())) && is_boundary(KernelT::to_vertex_handle(chfhe_it.handle())))
					{
						KernelT::set_hedron_boundary(_hh, 2);
						_type = 2;
						return;
					}					
				}
			}
		}
		if (!_type)
		{
			for (typename KernelT::ConstHedronVertexIter chv_it = KernelT::const_hedron_vertex_iter(_hh); chv_it; ++ chv_it)
			{
				if (is_boundary(chv_it.handle()))
				{
					KernelT::set_hedron_boundary(_hh, 4);
					_type = 4;
					return;
				}					
			}
		}
		KernelT::set_hedron_boundary(_hh, 0);
	}
	/** update the boundary hedron  */
	template < class KernelT >
	void THMeshT<KernelT>::update_boundary_hedron(const ConstHedronIter & _h_it)
	{
		update_boundary_hedron(KernelT::handle(*_h_it));
	}
	/** update the normals of the half faces */
	template < class KernelT >
	void THMeshT<KernelT>::update_hf_normals()
	{
		if (!typename KernelT::has_hf_normals())
		{
			return ;
		}
		HalfFaceIter f_it;//(half_faces_begin())
		HalfFaceIter f_end(typename KernelT::half_faces_end());
		for (f_it = typename KernelT::half_faces_begin(); f_it != f_end; ++ f_it)
		{
			KernelT::set_normal(KernelT::handle(*f_it), calc_face_normal(f_it));
		}
	}

	/** calculate the normal of the face */
	template < class KernelT >
	typename THMeshT<KernelT>::Normal THMeshT<KernelT>::calc_face_normal(const ConstHalfFaceIter _h_it ) const
	{
		//assert(_hfh.is_valid());
		typename KernelT::ConstHalfFaceVertexIter chfv_it(KernelT::const_half_face_vertex_iter(_h_it));
		Point p0 = KernelT::point(chfv_it.handle());
		++ chfv_it;
		Point  p1 = KernelT::point(chfv_it.handle());
		++ chfv_it;
		Point  p2 = KernelT::point(chfv_it.handle());
		if (p1 == p2)
		{
			++ chfv_it;
			Point  p2 = KernelT::point(chfv_it.handle());
		}	
		if (p2 == p0)
		{
			++ chfv_it;
			if (chfv_it.handle().is_valid())
			{
				Point  p0 = KernelT::point(chfv_it.handle());
			}
		}

		//Normal n;

		//n = calc_face_normal(p0, p1, p2);

		////--- check the directions and make sure the normal points outside ---//
		//HedronHandle hh = KernelT::hedron_handle(_h_it);
		//Point c(0, 0, 0);
		//int count;
		//count = 0;
		//for (typename KernelT::ConstHedronVertexIter chv_it; chv_it; ++chv_it)
		//{
		//	++ count;
		//	c += KernelT::point(chv_it.handle());
		//}
		//Normal n1;
		//n1 = ((p0 + p1 + p2) / 3.0 - c / count).normalize();
		//if ((n | n1) < 0)
		//{
		//	n = Point(0, 0, 0) - n;
		//}



		return calc_face_normal(p0, p1, p2);
	}

	/** calculate the normal of the face */
	template < class KernelT >
	typename THMeshT<KernelT>::Normal THMeshT<KernelT>::calc_face_normal(HalfFaceHandle _hfh) const
	{
		assert(_hfh.is_valid());
		typename KernelT::ConstHalfFaceVertexIter chfv_it(const_half_face_vertex_iter(_hfh));
		Point p0 = point(chfv_it.handle());
		++ chfv_it;
		Point  p1 = point(chfv_it.handle());
		++ chfv_it;
		Point  p2 = point(chfv_it.handle());
		if (p1 == p2)
		{
			++ chfv_it;
			Point  p2 = point(chfv_it.handle());
		}	
		if (p2 == p0)
		{
			++ chfv_it;
			if (chfv_it.handle().is_valid())
			{
				Point  p0 = point(chfv_it.handle());
			}
		}


		//Normal n;

		//n = calc_face_normal(p0, p1, p2);

		////--- check the directions and make sure the normal points outside ---//
		//HedronHandle hh = KernelT::hedron_handle(_hfh);
		//Point c(0, 0, 0);
		//int count;
		//count = 0;
		//for (typename KernelT::ConstHedronVertexIter chv_it; chv_it; ++chv_it)
		//{
		//	++count;
		//	c += KernelT::point(chv_it.handle());
		//}
		//Normal n1;
		//n1 = ((p0 + p1 + p2) / 3.0 - c / count).normalize();
		//if ((n | n1) < 0)
		//{
		//	n = Point(0, 0, 0) - n;
		//}


		return calc_face_normal(p0, p1, p2);
	}
	/** calculate the normal of the face with three points */
	template < class KernelT >
	typename THMeshT<KernelT>::Normal THMeshT<KernelT>::calc_face_normal(const typename THMeshT<KernelT>::Point & _p0, 
		                                                                 const typename THMeshT<KernelT>::Point & _p1, 
																		 const typename THMeshT<KernelT>::Point & _p2) const
	{
		return ((_p1 - _p0) % (_p2 - _p0)).normalize();   
	}
	/** calculate the dihedral angle of two cw faces */
	template < class KernelT >
	typename THMeshT<KernelT>::Scalar THMeshT<KernelT>::calc_cw_dihedral_angle(HalfEdgeHandle _heh)
	{
		Point v[4];
		v[0] = point(from_vertex_handle(_heh));
		v[1] = point(to_vertex_handle(_heh));
		v[2] = point(to_vertex_handle(next_half_edge_handle(_heh)));

		v[3] = point(to_vertex_handle(next_half_edge_handle(cw_opp_half_edge_handle(_heh))));

		Normal n[2];

		n[0] = (v[1] - v[0]) % (v[2] - v[0]);
		n[0].normalize();
		n[1] = (v[3] - v[0]) % (v[1] - v[0]);
		n[1].normalize();

		Scalar da_cos;
		da_cos = acos(std::max(-1.0, std::min(1.0, n[0] | n[1])));
		Scalar da_sign;
		da_sign = (n[0] % n[1]) | (v[1] - v[0]);
		if (da_sign > 0)
		{
			return M_PI + da_cos;
		} 
		return da_cos;
	}
	/** calculate the dihedral angle of two cw faces */
	template < class KernelT >
	typename THMeshT<KernelT>::Scalar THMeshT<KernelT>::calc_ccw_dihedral_angle(HalfEdgeHandle _heh)
	{
		Point v[4];
		v[0] = point(from_vertex_handle(_heh));
		v[1] = point(to_vertex_handle(_heh));
		v[2] = point(to_vertex_handle(next_half_edge_handle(_heh)));

		v[3] = point(to_vertex_handle(next_half_edge_handle(ccw_opp_half_edge_handle(_heh))));

		Normal n[2];

		n[0] = (v[1] - v[0]) % (v[2] - v[0]);
		n[0].normalize();
		n[1] = (v[3] - v[0]) % (v[1] - v[0]);
		n[1].normalize();

		Scalar da_cos;
		da_cos = acos(std::max(-1.0, std::min(1.0, n[0] | n[1])));
		Scalar da_sign;
		da_sign = (n[0] % n[1]) | (v[1] - v[0]);
		if (da_sign > 0)
		{
			return M_PI + da_cos;
		} 
		return da_cos;
	}
	/** calculate the length length */
	template < class KernelT >
	typename THMeshT<KernelT>::Scalar THMeshT<KernelT>::calc_half_edge_length(HalfEdgeHandle _heh)
	{
		VertexHandle v0;
		VertexHandle v1;
		v0 = from_vertex_handle(_heh);
		v1 = to_vertex_handle(_heh);
		return (point(v0) - point(v1)).norm();
	}
	/** delete hedron */
	template < class KernelT >
	bool THMeshT<KernelT>::delete_hedron(HedronHandle _hh)
	{
		for (typename KernelT::ConstHedronVertexIter chv_it = const_hedron_vertex_iter(_hh); chv_it; ++ chv_it)
		{
			set_vertex_boundary(chv_it.handle(), true);
			for (typename KernelT::ConstVertexHedronIter cvh_it = const_vertex_hedron_iter(chv_it.handle()); cvh_it; ++ cvh_it)
			{
				if (hedron_boundary_type(cvh_it.handle()))
				{
					set_hedron_boundary(cvh_it.handle(), std::min(4, hedron_boundary_type(cvh_it.handle())));
				}
				else
				{
					set_hedron_boundary(cvh_it.handle(), 4);

				}
			}
		}
		std::set<HalfEdgeHandle> hes;
		for (typename KernelT::ConstHedronHalfFaceIter chhf_it = const_hedron_half_face_iter(_hh); chhf_it; ++ chhf_it)
		{
			HalfEdgeHandle ohe;
			for (typename KernelT::ConstHalfFaceHalfEdgeIter chfhe_it = const_half_face_half_edge_iter(chhf_it.handle()); chfhe_it; ++ chfhe_it)
			{
				ohe = cw_opp_half_edge_handle(chfhe_it.handle());
				if (hes.find(ohe) == hes.end())
				{
					hes.insert(chfhe_it.handle());
				}				
			}
		}
		for (auto cit = hes.begin(); cit != hes.end(); ++ cit)
		{
			for (typename KernelT::ConstHalfEdgeHedronIter cheh_it = const_half_edge_hedron_iter(*cit); cheh_it; ++ cheh_it)
			{
				if (hedron_boundary_type(cheh_it.handle()))
				{
					set_hedron_boundary(cheh_it.handle(), std::min(2, hedron_boundary_type(cheh_it.handle())));
				}
				else
				{
					set_hedron_boundary(cheh_it.handle(), 2);
				}				
			}
		}
		for (typename KernelT::ConstHedronHedronIter chh_it = const_hedron_hedron_iter(_hh); chh_it; ++ chh_it)
		{
			set_hedron_boundary(chh_it.handle(), 1);
		}
		return KernelT::delete_hedron(_hh);
	}
	/** delete hedron */
	template < class KernelT >
	bool THMeshT<KernelT>::delete_hedron(const ConstHedronIter & _h_it)
	{
		return KernelT::delete_hedron(handle(*_h_it));
	}
	/** check if the flip is ok */
	template < class KernelT >
	bool THMeshT<KernelT>::is_flip_ok(HalfFaceHandle _hfh)
	{
		if (is_boundary(_hfh))
		{
			return false;
		}
		return true;
	}
	/** check if the flip is ok */
	template < class KernelT >
	bool THMeshT<KernelT>::is_flip_ok(HalfEdgeHandle _heh)
	{	
		unsigned int n;
		n = 0;
		for (typename KernelT::ConstHalfEdgeHedronIter cheh_it = const_half_edge_hedron_iter(_heh); cheh_it; ++ cheh_it)
		{
			++ n;
		}
		if ((!mesh_type() & 1) || (n != 3))
		{
			return false;			
		}
		
		
		return true;
	}
	/** check if the flip is ok */
	template < class KernelT >
	bool THMeshT<KernelT>::is_flip_ok(HedronHandle _h0, HedronHandle _h1)
	{
		for (typename KernelT::ConstHedronHedronIter chh_it = const_hedron_hedron_iter(_h0); chh_it; ++ chh_it)
		{
			if (_h1 == chh_it.handle())
			{
				return true;
			}
		}		
		return false;
	}
	/** check if the flip is ok */
	template < class KernelT >
	bool THMeshT<KernelT>::is_flip_ok(HedronHandle _h0, HedronHandle _h1, HedronHandle _h2)
	{	
		unsigned int is_ok;
		is_ok = 0;
		for (typename KernelT::ConstHedronHedronIter chh_it = const_hedron_hedron_iter(_h0); chh_it; ++ chh_it)
		{
			if ((chh_it.handle() == _h2) ||(chh_it.handle() == _h1) )
			{
				++ is_ok;
			}			
		}
		for (typename KernelT::ConstHedronHedronIter chh_it = const_hedron_hedron_iter(_h1); chh_it; ++ chh_it)
		{
			if ((chh_it.handle() == _h2) ||(chh_it.handle() == _h0) )
			{
				++ is_ok;
			}

		}
		if (is_ok == 4)
		{
			return true;
		}		
		
		return false;
	}
	/** flip hedrons 2 to 3 */
	template < class KernelT >
	std::vector<typename THMeshT<KernelT>::HedronHandle> THMeshT<KernelT>::flip_23(HalfFaceHandle _hfh)
	{
		HedronHandle h0;
		HedronHandle h1;
		h0 = hedron_handle(_hfh);
		h1 = hedron_handle(opp_half_face_handle(_hfh));
		return flip_23(h0, h1);		
	}
	/** flip hedrons 2 to 3 */
	template < class KernelT >
	std::vector<typename THMeshT<KernelT>::HedronHandle> THMeshT<KernelT>::flip_23(HedronHandle _h0, HedronHandle _h1)
	{
		std::vector<HedronHandle> hedrons;
		if (! (mesh_type() & 1))
		{
			std::cerr << "Filp Error : not tetrahedral mesh ... " << std::endl;
			return hedrons;
		}
		
		if (!is_flip_ok(_h0, _h1))
		{
			return hedrons;
		}
		HalfFaceHandle hfh;
		std::vector<VertexHandle> vhs;
		vhs.reserve(5);
		//--- find the common face ---
		for (typename KernelT::ConstHedronHalfFaceIter chhf_it = const_hedron_half_face_iter(_h0); chhf_it; ++ chhf_it)
		{
			hfh = chhf_it.handle();
			if (hedron_handle(opp_half_face_handle(hfh)) == _h1)
			{
				break;
			}
		}
		//--- get the common vertices
		for (typename KernelT::ConstHalfFaceVertexIter chfv_it = const_half_face_vertex_iter(hfh); chfv_it; ++ chfv_it)
		{
			vhs.push_back(chfv_it.handle());
		}
		
		//--- get another two opposite vertices
		for (typename KernelT::ConstHedronVertexIter chv_it = const_hedron_vertex_iter(_h0); chv_it; ++ chv_it)
		{
			if (std::find(vhs.begin(), vhs.end(), chv_it.handle()) == vhs.end())
			{
				vhs.push_back(chv_it.handle());
			}
		}
		for (typename KernelT::ConstHedronVertexIter chv_it = const_hedron_vertex_iter(_h1); chv_it; ++ chv_it)
		{
			if (std::find(vhs.begin(), vhs.end(), chv_it.handle()) == vhs.end())
			{
				vhs.push_back(chv_it.handle());
			}
		}

		delete_hedron(_h0);
		delete_hedron(_h1);
		KernelT::garbage_collection(true, true, true, false);
		std::vector<VertexHandle> h_idx;
		h_idx.resize(4);
		HedronHandle hh;
		hedrons.reserve(3);
		//--- 0134
		h_idx[0] = vhs[0];
		h_idx[1] = vhs[1];
		h_idx[2] = vhs[3];
		h_idx[3] = vhs[4];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
			//update_boundary_hedron(hh);
		}
		//--- 0324
		h_idx[0] = vhs[0];
		h_idx[1] = vhs[3];
		h_idx[2] = vhs[2];
		h_idx[3] = vhs[4];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		//--- 1342
		h_idx[0] = vhs[1];
		h_idx[1] = vhs[3];
		h_idx[2] = vhs[4];
		h_idx[3] = vhs[2];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		for (unsigned int i = 0; i < hedrons.size(); ++ i)
		{
			
			update_boundary_hedron(hedrons[i]);
		}
		if (hedrons.size() == 3)
		{
			swap_hedron_with_topology(_h0, hedrons[0]);
			swap_hedron_with_topology(_h1, hedrons[1]);
			hedrons[0] = _h0;
			hedrons[1] = _h1;
		}

		return hedrons;		
	}
	/** flip hedrons 2 to 3 */
	template < class KernelT >
	std::vector<typename THMeshT<KernelT>::HedronHandle> THMeshT<KernelT>::flip_32(HedronHandle _h0, HedronHandle _h1, HedronHandle _h2)
	{
		HalfEdgeHandle heh;
		unsigned int n;
		n = 0;

		for (typename KernelT::ConstHedronHalfFaceIter chhf_it = const_hedron_half_face_iter(_h0); chhf_it; ++ chhf_it)
		{
			for (typename KernelT::ConstHalfFaceHalfEdgeIter chfhe_it = const_half_face_half_edge_iter(chhf_it.handle()); chfhe_it; ++ chfhe_it)
			{
				if ((ccw_hedron_handle(chfhe_it.handle()) == _h2) ||(ccw_hedron_handle(chfhe_it.handle()) == _h1) )
				{
					++ n;
					if (n == 2)
					{
						heh = chfhe_it.handle();						
						break;
					}
				}
			}
			if (n == 2)
			{
				break;
			}
		}	

		return flip_32(heh);		
	}
	/** flip hedrons 2 to 3 */
	template < class KernelT >
	std::vector<typename THMeshT<KernelT>::HedronHandle> THMeshT<KernelT>::flip_32(HalfEdgeHandle _heh)
	{
		std::vector<HedronHandle> hedrons;
		if (! (mesh_type() & 1))
		{
			std::cerr << "Flip Error : not tetrahedral mesh ... " << std::endl;
			return hedrons;
		}

		if (!is_flip_ok(_heh))
		{
			return hedrons;
		}
		HalfFaceHandle hfh;
		std::vector<VertexHandle> vhs;
		vhs.reserve(5);
		//--- find the vertices ---
		vhs.push_back(from_vertex_handle(_heh));
		vhs.push_back(to_vertex_handle(_heh));
		vhs.push_back(to_vertex_handle(next_half_edge_handle(_heh)));
		vhs.push_back(to_vertex_handle(next_half_edge_handle(cw_opp_half_edge_handle(_heh))));
		vhs.push_back(to_vertex_handle(next_half_edge_handle(cw_opp_half_edge_handle(ccw_opp_half_edge_handle(_heh)))));
		std::vector<HedronHandle> deleted_hedrons;
		deleted_hedrons.reserve(3);
		for (typename KernelT::ConstHalfEdgeHedronIter cheh_it = const_half_edge_hedron_iter(_heh); cheh_it; ++ cheh_it)
		{
			deleted_hedrons.push_back(cheh_it.handle());
		}
		for (unsigned int i = 0; i < deleted_hedrons.size(); i ++)
		{
			delete_hedron(deleted_hedrons[i]);
		}
		
		
	KernelT::garbage_collection(true, true, true, false);
		std::vector<VertexHandle> h_idx;
		h_idx.resize(4);
		HedronHandle hh;
		hedrons.reserve(2);
		//--- 0243
		h_idx[0] = vhs[0];
		h_idx[1] = vhs[2];
		h_idx[2] = vhs[4];
		h_idx[3] = vhs[3];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		//--- 1234
		h_idx[0] = vhs[1];
		h_idx[1] = vhs[2];
		h_idx[2] = vhs[3];
		h_idx[3] = vhs[4];
		hh = add_hedron(h_idx);
		if (hh.is_valid())
		{
			hedrons.push_back(hh);
		}
		for (unsigned int i = 0; i < hedrons.size(); ++ i)
		{
			update_boundary_hedron(hedrons[i]);
		}
		std::sort(deleted_hedrons.begin(), deleted_hedrons.end());
		if (hedrons.size() == 2)
		{			
			swap_hedron_with_topology(deleted_hedrons[0], hedrons[0]);
			swap_hedron_with_topology(deleted_hedrons[1], hedrons[1]);
			hedrons[0] = deleted_hedrons[0];
			hedrons[1] = deleted_hedrons[1];
		}
		
		return hedrons;		
	}
	/** build the region property of the mesh 
	*   \param _region_property the property of regions, for tetrahedron, 4 numbers are a group, 5 for hexahedron
	*/
	template < class KernelT >
	void THMeshT<KernelT>::build_region_property(const std::vector<unsigned int> & _region_property)
	{
		unsigned int idx_len;
		idx_len = 0;
		if (KernelT::kernel_type_ == 0)
		{
			idx_len = 3;
		}
		else if (KernelT::kernel_type_ == 1)
		{
			idx_len = 4;
		}

		//--- find the boundary faces ---//
		std::map<typename KernelT::LessArrayUInt, int> boundary_faces;
		typename std::map<typename KernelT::LessArrayUInt, int>::iterator bf_it;
		std::vector<unsigned int> face_vertices;
		for (typename KernelT::ConstHalfFaceIter chf_it = KernelT::half_faces_begin(); chf_it != KernelT::half_faces_end(); ++ chf_it)
		{
			if (is_boundary(chf_it))
			{
				face_vertices.clear();
				for (typename KernelT::ConstHalfFaceVertexIter chfv_it = KernelT::const_half_face_vertex_iter(chf_it); chfv_it; ++ chfv_it)
				{
					face_vertices.push_back(chfv_it.handle().idx() + 1);
				}
				std::sort(face_vertices.begin(), face_vertices.end());
				boundary_faces.insert(std::make_pair(face_vertices, KernelT::handle(*chf_it).idx()));
			}
		}

		//--- set the region property for the boundary half faces ---//
		unsigned int start_idx;
		start_idx = 0;
		for (unsigned int i = 0; i < _region_property.size(); i += (idx_len + 1))
		{
			face_vertices.clear();
			start_idx = i;
			for (unsigned int k = 0; k < idx_len; ++ k)
			{
				face_vertices.push_back(_region_property[start_idx + k + 1]);
			}
			std::sort(face_vertices.begin(), face_vertices.end());
			typename KernelT::LessArrayUInt less_array(face_vertices);
			bf_it = boundary_faces.find(less_array);
			if (bf_it != boundary_faces.end())
			{
				KernelT::set_half_face_region(HalfFaceHandle(bf_it->second), _region_property[start_idx]);
			}
		}
	}

	template < class KernelT >
	int & THMeshT<KernelT>::half_face_region(const HalfFaceHandle & _hfh)
	{
		return KernelT::half_face_region(_hfh);
	}
	template < class KernelT >
	const int THMeshT<KernelT>::half_face_region(const HalfFaceHandle & _hfh) const
	{
		return KernelT::half_face_region(_hfh);
	}


	template < class KernelT >
	int & THMeshT<KernelT>::half_face_region(const ConstHalfFaceIter & _h_it)
	{
		return KernelT::half_face_region(_h_it);
	}

	template < class KernelT >
	const int THMeshT<KernelT>::half_face_region(const ConstHalfFaceIter & _h_it) const
	{
		return KernelT::half_face_region(_h_it);
	}

//---------------------------------------------------------------------------------------------------------------------

} // namespace OVM