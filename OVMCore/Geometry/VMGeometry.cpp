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

#define _VM_GEOMETRY_CPP_

#include <VolumeMesh/Geometry/VMGeometry.h>


namespace VolumeMesh
{
//---------------------------------------------------------------------------------------------------------------------

	/** Check whether 2 PointT are equal.
	*   \return true  equal.
	*			false not equal.
	*/
	//template <typename T>
	//bool PointT<T>::operator ==(const PointT& p1)
	//{
	//	if ( (p1[0] == cdt[0]) && (p1[1] == cdt[1]) && (p1[2] == cdt[2]))
	//	{
	//		return true;
	//	} 
	//	else
	//	{
	//		return false;
	//	}
	//}

	///** Retrieve the _x, _y, _z
	//*   \return _x, _y, _z.
	//*/
	//template <typename T>
	//T & PointT<T>::operator[](const int & idx)
	//{
	//	assert((idx > -1) && (idx < 3));
	//	return cdt[idx];
	//	//if (idx == 0)
	//	//{
	//	//	return _x;
	//	//}
	//	//else if (idx == 1)
	//	//{
	//	//	return _y;
	//	//}
	//	//else if (idx == 2)
	//	//{
	//	//	return _z;
	//	//}
	//}

	///** Retrieve the _x, _y, _z
	//*   \return _x, _y, _z.
	//*/
	//template <typename T>
	//const T & PointT<T>::operator[](const int & idx) const
	//{
	//	assert((idx > -1) && (idx < 3));
	//	return cdt[idx];
	//		//if (idx == 0)
	//		//{
	//		//	return _x;
	//		//}
	//		//else if (idx == 1)
	//		//{
	//		//	return _y;
	//		//}
	//		//else if (idx == 2)
	//		//{
	//		//	return _z;
	//		//}
	//}

	///** Retrieve the data
	//*   \return cdt.
	//*/
	//template <typename T>
	//T * PointT<T>::data() 
	//{
	//	return cdt;
	//}

	///** Retrieve the data
	//*   \return cdt.
	//*/
	//template <typename T>
	//const T * PointT<T>::data() const 
	//{
	//	return cdt;
	//}


	//

	/** Function object to find equal PointT.
	*   \return true  found.
	*			false not found.
	*/
	template <typename T>
	bool PointFindIF<T>::operator ()(T & p)
	{
		return _p == p;
	}

	/** Assignment function of Function object to find PointT.
	*/
	template <typename T>
	void PointFindIF<T>::operator = (T & p)
	{
		_p = p;
	}

//---------------------------------------------------------------------------------------------------------------------
}	// namespace VolumeMesh
//---------------------------------------------------------------------------------------------------------------------
