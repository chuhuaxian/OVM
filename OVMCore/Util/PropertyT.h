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

#ifndef _OVM_PROPERTY_H_
#define _OVM_PROPERTY_H_


#include <OVM/OVMCore/system/config.h>
#include <OVM/OVMCore/Mesh/Handles.h>
#include <OVM/OVMCore/Util/BaseProperty.h>
#include <vector>
#include <string>
#include <algorithm>

namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	template < class T >
	class PropertyT : public BaseProperty
	{
	public:
		typedef std::vector<T>                        vector_type;
		typedef T                                     value_type;
		typedef typename vector_type::reference       reference;
		typedef typename vector_type::const_reference const_reference;	
	//-----------------------------------------------------------------------------------------------------------------
	public:
		PropertyT(const std::string & _name = "_unknown_") : BaseProperty(_name)
		{
		}
		PropertyT(const PropertyT<T> & _rhs) : BaseProperty(_rhs.name()), data_(_rhs.data_)
		{
		}
		virtual ~ PropertyT()
		{
		}
	public:
		virtual void reserve(size_t _n) 
		{
			data_.reserve(_n);
		}
		virtual void resize(size_t _n)
		{
			data_.resize(_n);
		}
		virtual void clear()
		{
			data_.clear();
			vector_type().swap(data_);
		}
		virtual void push_back()
		{
			data_.push_back(T());
		}
		virtual void pop_back()
		{
			data_.pop_back();
		}
		virtual void swap(size_t _i0, size_t _i1)
		{
			std::swap(data_[_i0], data_[_i1]);
		}
	public:
		/** return the size of the data */
		virtual size_t n_elements() const
		{
			return data_.size();
		}
		virtual size_t element_size() const
		{
			return sizeof(value_type);
		}
		/** return the pointer of the array */
		const value_type * data() const
		{
			if (data_.empty())
			{
				return NULL;
			}
			
			return &data_[0];
		}
		/** return the reference to the vector */
		vector_type & data_vector()
		{
			return data_;
		}
		/** overload the [] operator, access the i th element */
		reference operator[](size_t _idx)
		{
			assert((size_t)(_idx) < data_.size());
			return data_[_idx];
		}
		/** overload the [] operator, constant access the i th element */
		const_reference operator[] (size_t _idx) const   
		{
			assert((size_t)(_idx) < data_.size());
			return data_[_idx];
		}
		/** make a copy of the property */
		PropertyT<T> * clone() const
		{
			PropertyT<T> * p = new PropertyT<T>(*this);
			return p;
		}
	private:
		vector_type data_;
	};

	/** base property handle 
	*/
	template <class T>
	struct BasePropHandleT : public BaseHandle
	{
		typedef T                                       Value;
		typedef std::vector<T>                          vector_type;
		typedef T                                       value_type;
		typedef typename vector_type::reference         reference;
		typedef typename vector_type::const_reference   const_reference;

		explicit BasePropHandleT(__int64 _idx=-1) : BaseHandle(_idx) 
		{
		}
	};

	/** handle to represent a vertex property
	*/
	template <class T>
	struct VPropHandleT : public BasePropHandleT<T>
	{
		typedef T                       Value;
		typedef T                       value_type;

		explicit VPropHandleT(int _idx=-1) : BasePropHandleT<T>(_idx) 
		{
		}
		explicit VPropHandleT(const BasePropHandleT<T>& _b) : BasePropHandleT<T>(_b) 
		{
		}
	};

	/** handle to represent a half edge property
	*/
	template <class T>
	struct HEPropHandleT : public BasePropHandleT<T>
	{
		typedef T                       Value;
		typedef T                       value_type;

		explicit HEPropHandleT(int _idx=-1) : BasePropHandleT<T>(_idx) 
		{
		}
		explicit HEPropHandleT(const BasePropHandleT<T>& _b) : BasePropHandleT<T>(_b) 
		{
		}
	};

	/** handle to represent a half face property
	*/
	template <class T>
	struct HFPropHandleT : public BasePropHandleT<T>
	{
		typedef T                       Value;
		typedef T                       value_type;

		explicit HFPropHandleT(int _idx=-1) : BasePropHandleT<T>(_idx) 
		{
		}
		explicit HFPropHandleT(const BasePropHandleT<T>& _b) : BasePropHandleT<T>(_b) 
		{
		}
	};

	/** handle to represent a hedron property
	*/
	template <class T>
	struct HPropHandleT : public BasePropHandleT<T>
	{
		typedef T                       Value;
		typedef T                       value_type;

		explicit HPropHandleT(int _idx=-1) : BasePropHandleT<T>(_idx) 
		{
		}
		explicit HPropHandleT(const BasePropHandleT<T>& _b) : BasePropHandleT<T>(_b) 
		{
		}
	};



	
//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM
#endif