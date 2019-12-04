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

#ifndef _OVM_BASE_PROPERTY_H_
#define _OVM_BASE_PROPERTY_H_

#include <OVM/OVMCore/system/config.h>

#include <string>

namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	/** abstract class for a dynamic property
	*/
	class BaseProperty
	{
	public:
		static const __int64 unknown_size_ = (__int64)(-1);
	public:
		BaseProperty(std::string _name = "_unknown_") : property_name_ (_name)
		{

		}
		BaseProperty(const BaseProperty & _rhs) : property_name_ (_rhs.property_name_)
		{
		}
		virtual ~BaseProperty()
		{
		}
	public:
		virtual BaseProperty * clone() const = 0;
		virtual void reserve(size_t _n) = 0;
		virtual void resize(size_t _n) = 0;
		virtual void clear() = 0;
		virtual void push_back() = 0;
		virtual void pop_back() = 0;
		virtual void swap(size_t _i0, size_t _i1) = 0;
	public:
		/** return the name of the property
		*   \return the name of the property
		*/
		const std::string name() const
		{
			return property_name_;
		}
	public:
		/** return the count of the elements */
		virtual size_t n_elements() const = 0;
		/** return the size of one element in byte */
		virtual size_t element_size() const = 0;
		
	protected:
	//-----------------------------------------------------------------------------------------------------------------
	private:
		std::string property_name_;
	};
//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM
#endif