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


#ifndef _OVM_BASE_HANDLE_H_
#define _OVM_BASE_HANDLE_H_
//---------------------------------------------------------------------------------------------------------------------


#include <OVM/OVMCore/system/config.h>

/// namespace OVM
namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	class BaseHandle
	{
	public:

		explicit BaseHandle(__int64 _idx = -1) : idx_(_idx) 
		{
		}

		// Get the underlying index of this handle
		__int64 idx() const 
		{
			return idx_;
		}

		// The handle is valid iff the index is not equal to -1.
		bool is_valid() const 
		{
			return idx_ != -1; 
		}

		// reset handle to be invalid
		void reset() 
		{
			idx_= -1; 
		}

		// reset handle to be invalid
		void invalidate() 
		{
			idx_ = -1; 
		}

		bool operator == (const BaseHandle& _rhs) const 
		{ 
			return (idx_ == _rhs.idx_); 
		}

		bool operator != (const BaseHandle& _rhs) const 
		{ 
			return (idx_ != _rhs.idx_); 
		}

		bool operator < (const BaseHandle& _rhs) const 
		{ 
			return (idx_ < _rhs.idx_); 
		}

		BaseHandle & operator ++ ()
		{
			++ idx_;
			return *this;
		}

		BaseHandle & operator -- ()
		{
			-- idx_;
			return *this;
		}

		operator int() const
		{
			return (int)idx_;
		}
		operator size_t() const
		{
			return idx_;
		}
		operator __int64() const
		{
			return idx_;
		}

		// this is to be used only by the iterators
		void __increment() 
		{ 
			++ idx_; 
		}

		void __decrement() 
		{
			-- idx_; 
		}

		void set_idx(__int64 _idx)
		{
			idx_ = _idx;
		}

	private:
		__int64 idx_; 
	};

//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM
//---------------------------------------------------------------------------------------------------------------------

#endif // _OVM_BASE_HANDLE_H_ defined
