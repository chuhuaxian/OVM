/*---------------------------------------------------------------------------------------------------------------------
*  _               _  _             _   *
*   \             /  | \           / |  *     VolumeMesh : The Open Data Structure for Tetrahedral and Hexahedral Mesh
*    \           /   |  \         /  |  *     
*  	  \         /    |   \       /   |  *     Copyright(C) 2010 by Computer Aided Designed Group
*	   \       /     |    \     /    |  *     State Key Lab. of CAD & CG, Zhejiang University
*	    \     /      |     \   /     |  *
*	     \   /       |      \_/      |  *
*		  \_/        |               |_ * 
*                                       *
*-----------------------------------------------------------------------------------------------------------------------
* License
*
*    This file is part of VolumeMesh.
*
*    VolumeMesh is free software: you can redistribute it and/or modify       
*	it under the terms of the GNU Lesser General Public License as          
*	published by the Free Software Foundation, either version 3 of          
*	the License, or (at your option) any later version. 
*	
*	VolumeMesh distributed in the hope that it will be useful,            
*   but WITHOUT ANY WARRANTY; without even the implied warranty of      
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         
*	GNU Lesser General Public License for more details.
*   This project is created by Chuhua Xian
*   Developers : Chuhua Xian,   chuhuaxian@gmail.com 
*                Xiaoshen Chen, chinimei@163.com
*
/---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*
*                                                                                                                     *
*                               VolumeMesh                                                                            *
*      Copyright (C) 2010 by Computer Aided Designed Group                                                            *
*        State Key Lab. of CAD & CG, Zhejiang University                                                              *
*         This project is created by Chuhua Xian, 2010.2                                                              *
*                     Email: chuhuaxian@gmail.com																	   *	
*         Modified by Xiaoshen Chen, 2010.03																		   *
*					   Email: chinimei@163.com																		   *
*---------------------------------------------------------------------------------------------------------------------*/ 


#ifndef _VOLUME_MESH_VMGEO_H_
#define _VOLUME_MESH_VMGEO_H_


#include <VolumeMesh/system/config.h>

//---------------------------------------------------------------------------------------------------------------------

/// namespace VolumeMesh
namespace VolumeMesh
{
//---------------------------------------------------------------------------------------------------------------------
	
	/// definition of PointT
	//template <typename T> 
	//class PointT
	//{
	//public:
	//	PointT()
	//	{
	//	};
	//	PointT(T x, T y, T z)  
	//	{
	//		cdt[0] = x;
	//		cdt[1] = y;
	//		cdt[2] = z;
	//	};
	//	PointT(T p[3]) :
	//	{
	//		cdt[0] = p[0];
	//		cdt[1] = p[1];
	//		cdt[2] = p[2];
	//	};
	//public:
	//	T & operator[] (const int & idx);
	//	const T & operator[] (const int & idx) const;
	//	bool operator == (const PointT<T> &p1);
	//	T * data();
	//	const T * data() const;
	//private:
	//	T cdt[3];
	//};

	/// function object to find PointT
	template <typename T> 
	class PointFindIF
	{
	public:
		PointFindIF(T p) : _p(p)
		{
		};
		bool operator ()(T & p);
		void operator = (T & p);

	private:
		T _p;
	};

//---------------------------------------------------------------------------------------------------------------------
}	// namespace VolumeMesh
//---------------------------------------------------------------------------------------------------------------------

#if defined(_ENABLETEMPLATE_) && !defined(_VM_GEOMETRY_CPP_)
#include "VMGeometry.cpp"
#endif

#endif