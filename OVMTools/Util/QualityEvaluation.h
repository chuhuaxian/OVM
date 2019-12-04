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



#ifndef _OVM_QUALITY_EVALUATION_
#define _OVM_QUALITY_EVALUATION_


#include <OVM/OVMCore/system/config.h>
#include <OVM/OVMTools/Math/OVMMath.h>

#include <math.h>
#include <vector>
#include <algorithm>

#include <iostream>
#include <set>



namespace OVM
{
	namespace Util
	{
//---------------------------------------------------------------------------------------------------------------------

		/** this class implements some operations on tetrahedral mesh and hexahedral mesh, including the angle ratio
		*   rule, the ratio of the radius and the shortest rule, and so on. It also statics the number of the hedrons
		*   by given an interval of the quality. The quality of a hedron q is between 0 and 1.
		*/
		template <typename MeshT>
		class QualityEvaluation
		{
		public:
			QualityEvaluation(MeshT * _mesh) : mesh_(_mesh)
			{
				MeshT::ConstHedronIter h_end(_mesh->hedrons_end());
				for (MeshT::ConstHedronIter h_it = _mesh->hedrons_begin(); h_it != h_end; ++ h_it )
				{
					hedrons_.push_back(_mesh->handle(*h_it));
				}
				
			}

			QualityEvaluation(MeshT * _mesh, const std::vector<typename MeshT::HedronHandle> & _hedrons) : 
			                  mesh_(_mesh)
			{
				hedrons_.assign(_hedrons.begin(), _hedrons.end());
			}
			virtual ~QualityEvaluation()
			{
			}
		//-------------------------------------------------------------------------------------------------------------
		public:
			/** evaluate the qualities_ of the hedrons
			*   \param in _type 0x0001 for using angle, 0x0002 for using radius
			*/
			bool evaluate(unsigned int _type = 0x0001)
			{
				qualities_.clear();
				if (_type & 0x0001)
				{
					for (unsigned int i = 0; i < hedrons_.size(); i ++)
					{
						qualities_.push_back(evaluate_by_angle(mesh_, hedrons_[i]));
					}					
				}
				else if ((_type & 0x0002) && (mesh_->mesh_type() & 0x0001))
				{
					for (unsigned int i = 0; i < hedrons_.size(); i ++)
					{
						qualities_.push_back(evaluate_by_radius_edge(mesh_, hedrons_[i]));
					}
				}
				else if ((_type & 0x0004) && (mesh_->mesh_type() & 0x0001))
				{
					for (unsigned int i = 0; i < hedrons_.size(); i ++)
					{
						qualities_.push_back(evaluate_by_volume_ratio(mesh_, hedrons_[i]));
					}
				}
				else
				{
					std::cerr << "Quality evaluation : no proper type.......\n" ;
				}
				
				return true;
			}

			/** static the distribution of the count with the length of interval _inc
			*   \param _inc the length of the interval, it should point out that 0 < _inc < 1
			*   \param _type 0x0001 for [_low, _up), 0x0002 for (_low, _up]
			*/
			std::vector<unsigned int> static_distribute(double _inc, unsigned int _type = 0x0002)
			{
				std::vector<unsigned int> distribution;
				double _low;
				double _up;
				_low = 0;
				_up  = _inc;

				for (; _up <= 1; _up += _inc)
				{
					distribution.push_back(interval_count(_low, _up, _type));
					_low = _up;
				}				
				
				return distribution;
			}

			/** retrieve the count of the hedrons between [_low, _up) or (_low, _up]
			*   \param _type 0x0001 for [_low, _up), 0x0002 for (_low, _up]
			*/
			unsigned int interval_count(double _low, double _up, unsigned int _type = 0x0002)
			{
				unsigned int c;
				c = 0;
				if (_type & 0x0001)
				{
					for (unsigned int i = 0; i < qualities_.size(); i ++)
					{
						if ((qualities_[i] >= _low) && (qualities_[i] < _up))
						{
							c ++;
						}
					}		
				}
				else if (_type & 0x0002)
				{
					for (unsigned int i = 0; i < qualities_.size(); i ++)
					{
						if ((qualities_[i] > _low) && (qualities_[i] <= _up))
						{
							c ++;
						}
					}		
				}
				return c;
			}

			/** retrieve the total qualities_ of the hedrons
			*/
			std::vector<double> hedron_qualities() const
			{
				return qualities_;
			}

		//-------------------------------------------------------------------------------------------------------------
		public:
			/** evaluate by angle ratio
			*   \param in _mesh the mesh
			*   \param in _h the hedron handle
			*   \return the quality, its value is between 0 and 1
			*/
			static double evaluate_by_angle(MeshT * _mesh, typename MeshT::HedronHandle & _h)
			{
				std::vector<typename MeshT::Scalar> angles;
				std::set<typename MeshT::HalfEdgeHandle> hes;
				for (typename MeshT::ConstHedronHalfFaceIter chhf_it = _mesh->const_hedron_half_face_iter(_h); chhf_it; ++ chhf_it)
				{
					for (typename MeshT::ConstHalfFaceHalfEdgeIter chfhe_it = _mesh->const_half_face_half_edge_iter(chhf_it.handle()); chfhe_it; ++ chfhe_it)
					{
						std::set<typename MeshT::HalfEdgeHandle>::iterator &it = hes.find(_mesh->cw_opp_half_edge_handle(chfhe_it.handle()));
						if (it == hes.end())
						{
							hes.insert(chfhe_it.handle());
						}					
					}
				}
				std::set<typename MeshT::HalfEdgeHandle>::const_iterator it;	
				for (it = hes.begin(); it != hes.end(); ++ it)
				{
					angles.push_back(2 * OVMMath::OVM_PI - _mesh->calc_cw_dihedral_angle(*it));
				}
				std::sort(angles.begin(), angles.end());
				return angles[0] / angles[angles.size() - 1];			
			}
			/** get the angle distribution of the mesh 
			*   \param _mesh the mesh
			*   \return the angles.
			*/
			static std::vector<double> angle_distribution(MeshT * _mesh)
			{
				std::vector<double> angles;
				std::set<typename MeshT::HalfEdgeHandle> hes;
				typename MeshT::ConstHedronIter ch_end(_mesh->hedrons_end());
				for (typename MeshT::ConstHedronIter ch_it = _mesh->hedrons_begin(); ch_it != ch_end; ++ ch_it)
				{
					for (typename MeshT::ConstHedronHalfFaceIter chhf_it = _mesh->const_hedron_half_edge_iter(ch_it); chhf_it; ++ chhf_it)
					{
						for (typename MeshT::ConstHalfFaceHalfEdgeIter chfhe_it = _mesh->const_half_face_half_edge_iter(chhf_it.handle()); chfhe_it; ++ chfhe_it)
						{

							std::set<typename MeshT::HalfEdgeHandle>::iterator &it = hes.find(_mesh->cw_opp_half_edge_handle(chfhe_it.hancle()));
							if (it == hes.end())
							{
								hes.insert(chfhe_it.handle());
							}					
						}
					}
				}
				
				std::set<typename MeshT::HalfEdgeHandle>::const_iterator it;	
				for (it = hes.begin(); it != hes.end(); ++ it)
				{
					angles.push_back(2 * OVMMath::OVM_PI - _mesh->calc_cw_dihedral_angle(*it));
				}
				std::sort(angles.begin(), angles.end());
				return angles;
			}

			/** evaluate by the ratio of minimal edge's length and the ball, only for tetrahedral mesh
			*   \param in _mesh the mesh
			*   \param in _h the hedron handle
			*   \return the quality, its value is between 0 and 1
			*/
			static double evaluate_by_radius_edge(MeshT * _mesh, typename MeshT::HedronHandle & _h)
			{
				typename MeshT::Point v[4];
				typename MeshT::ConstHedronVertexIter chv_it;
				chv_it = _mesh->const_hedron_vertex_iter(_h);
				v[0] = _mesh->point(chv_it);
				++ chv_it;
				v[1] = _mesh->point(chv_it);
				++ chv_it;
				v[2] = _mesh->point(chv_it);
				++ chv_it;
				v[3] = _mesh->point(chv_it);
				
				typename MeshT::Scalar A[3][3];
				typename MeshT::Scalar x[3];
				for (unsigned int i = 1; i < 4; i ++)
				{
					typename MeshT::Point dv;
					dv = v[i - 1] - v[i];
					A[i - 1][0] = dv[0];
					A[i - 1][1] = dv[1];
					A[i - 1][2] = dv[2];

					x[i - 1] = (v[i - 1] | v[i - 1])  - (v[i] | v[i]) ;
					x[i - 1] /= 2.0;
				}

				if (fabs(OVMMath::LinearAgebra::determination_3x3(A)) < OVMMath::OVM_EPS)
				{
					return 0;
				}
				

				OVMMath::LinearAgebra::solve_linear_system_3x3(A, x);
				double r;
				std::vector<double> el;
				r = (v[0][0] - x[0]) * (v[0][0] - x[0]) + 
					(v[0][1] - x[1]) * (v[0][1] - x[1]) +
					(v[0][2] - x[2]) * (v[0][2] - x[2]);
				for (unsigned int i = 0; i < 4; i ++)
				{
					for (unsigned int k = i + 1; k < 4; k ++)
					{
						el.push_back((v[i] - v[k]).norm());
					}					
				}
				std::sort(el.begin(), el.end());
				return el[0] / sqrt(r) / 4.0 * sqrt(6.0);
			}	
			static double evaluate_by_volume_ratio(MeshT * _mesh, typename MeshT::HedronHandle & _h)
			{
				typename MeshT::Point v[4];
				typename MeshT::ConstHedronVertexIter chv_it;
				chv_it = _mesh->const_hedron_vertex_iter(_h);
				v[0] = _mesh->point(chv_it);
				++ chv_it;
				v[1] = _mesh->point(chv_it);
				++ chv_it;
				v[2] = _mesh->point(chv_it);
				++ chv_it;
				v[3] = _mesh->point(chv_it);
				double Volume;
				Volume = (v[3] - v[0]) % (v[2] - v[0]) | (v[1] - v[0]);
				Volume = abs(Volume) / 3.0 ;
				double e[6];
				unsigned int m = 0;
				for (unsigned int i = 0; i < 4; i ++)
				{
					for (unsigned int k = i + 1; k < 4; k ++)
					{
						e[m] = (v[i] - v[k]).norm(); 
						++ m;
					}
				}
				double length;
				length = 0;
				for (unsigned int i = 0; i < 6; i ++)
				{
					length += e[i] * e[i];
				}
				length /= 6.0;
				length = sqrt(length);
				return 6.0 * Volume / (sqrt(2.0) * length * length * length);
			}										
		//-------------------------------------------------------------------------------------------------------------
		protected:
			MeshT * mesh_;
			std::vector<typename MeshT::HedronHandle> hedrons_; 
			std::vector<double>                       qualities_; /**< stores the qualities_ of the hedrons */
		};

//---------------------------------------------------------------------------------------------------------------------
	} // namespace Util

} // namespace OVM

#endif