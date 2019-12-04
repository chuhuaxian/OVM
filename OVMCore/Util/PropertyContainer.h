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

#ifndef _OVM_PROPERTY_CONTAINER_H_
#define _OVM_PROPERTY_CONTAINER_H_

#include <OVM/OVMCore/system/config.h>
#include <OVM/OVMCore/Util/PropertyT.h>
#include <OVM/OVMCore/Util/BaseProperty.h>



namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	class PropertyContainer
	{
	public:
		typedef std::vector<BaseProperty *> Properties;
		typedef Properties::iterator iterator;
		typedef Properties::const_iterator const_iterator;
		friend class BaseKernel;
	public:
		PropertyContainer()
		{
		}
		virtual ~PropertyContainer()
		{
			std::for_each(properties_.begin(), properties_.end(), Delete());
		}
		
		
		
		
		PropertyContainer(const PropertyContainer & _rhs)
		{
			operator = (_rhs);
		}
	public:
		const Properties & properties() const
		{
			return properties_;
		}
		PropertyContainer & operator = (const PropertyContainer & _rhs)
		{
			std::for_each(properties_.begin(), properties_.end(), Delete());
			properties_ = _rhs.properties_;
			iterator p_end(properties_.end());
			for (iterator p_it = properties_.begin(); p_it != p_end; ++ p_it)
			{
				if (*p_it)
				{
					*p_it = (*p_it)->clone();
				}
				
			}
			return *this;
			
		}
	public:
		template <class T> 
		BasePropHandleT<T> add(const T &, const std::string _name =  "_unknown_")
		{
			iterator p_end(properties_.end());
			size_t idx;
			idx = 0;
			iterator p_it = properties_.begin();
			for (; (p_it != p_end) && (*p_it != NULL) ; ++ p_it)
			{
				++ idx;
			}
			if (p_it == p_end)
			{
				properties_.push_back(NULL);
			}
			properties_[idx] = new PropertyT<T>(_name);
			return BasePropHandleT<T>(idx); 
		}

		template < class T >
		BasePropHandleT<T> handle(const T & , const std::string _name ) const
		{
			size_t idx;
			idx = 0;
			for (const_iterator p_it = properties_.begin(); p_it != properties_.end(); ++ p_it)
			{
				if ((*p_it != NULL) && ((*p_it)->name() == _name) && 
					(dynamic_cast<PropertyT<T> *> (properties_[idx]) != NULL))
				{
					return BasePropHandleT<T>(idx);
				}
				++ idx;
			}
			return BasePropHandleT<T>();	
		}

		BaseProperty * property(const std::string & _name)
		{
			size_t idx;
			idx = 0;
			for (iterator p_it = properties_.begin(); p_it != properties_.end(); ++ p_it)
			{
				if ((*p_it != NULL) && ((*p_it)->name() == _name))
				{
					return *p_it;
				}
				
			}

			return NULL;
		}
		const BaseProperty * property(const std::string & _name) const
		{
			size_t idx;
			idx = 0;
			for (const_iterator p_it = properties_.begin(); p_it != properties_.end(); ++ p_it)
			{
				if ((*p_it != NULL) && ((*p_it)->name() == _name))
				{
					return *p_it;
				}

			}

			return NULL;
		}

		template < class T >
		PropertyT<T> & property(BasePropHandleT<T> _h)
		{
			assert((_h.idx() >= 0) && (_h.idx() < (int)properties_.size()));
			assert(properties_[_h.idx()] != NULL);
			return *dynamic_cast<PropertyT<T> *> (properties_[_h.idx()]);
			
		}

		template < class T >
		const PropertyT<T> & property(BasePropHandleT<T> _h) const
		{
			assert((_h.idx() >= 0) && (_h.idx() < (int)properties_.size()));
			assert(properties_[_h.idx()] != NULL);
			return *dynamic_cast<PropertyT<T> *> (properties_[_h.idx()]);
		}

		template < class T >
		void remove(BasePropHandleT<T> _h)
		{
			assert((_h.idx() >= 0) && (_h.idx() < (int)properties_.size()));
			delete properties_[_h.idx()];
			properties_[_h.idx()] = NULL;
		}

		
		void clear()
		{
			std::for_each(properties_.begin(), properties_.end(), ClearAll());
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		void reserve(size_t _n) const
		{
			std::for_each(properties_.begin(), properties_.end(), Reserve(_n));
		}

		void resize(size_t _n) const
		{
			std::for_each(properties_.begin(), properties_.end(), Resize(_n));
		}

		void swap(size_t _i0, size_t _i1) const
		{
			std::for_each(properties_.begin(), properties_.end(), Swap(_i0, _i1));
		}
		void pop_back() const
		{
			std::for_each(properties_.begin(), properties_.end(), PopBack());
		}
	//-----------------------------------------------------------------------------------------------------------------
	protected:
		size_t _add(BaseProperty * _bp)
		{
			iterator p_end(properties_.end());
			size_t idx;
			idx = 0;
			iterator p_it = properties_.begin();
			for (; (p_it != p_end) && (*p_it != NULL); ++ p_it)
			{
				++ idx;
			}
			if (p_it == p_end)
			{
				properties_.push_back(NULL);
			}
			properties_[idx] = _bp;
			return idx;
		}

		BaseProperty & _property(size_t _idx)
		{
			assert(_idx < properties_.size());
			assert(properties_[_idx] != NULL);
			return *properties_[_idx];
		}
		
		const BaseProperty & _property(size_t _idx) const
		{
			assert(_idx < properties_.size());
			assert(properties_[_idx] != NULL);
			return *properties_[_idx];
		}
		
	//-----------------------------------------------------------------------------------------------------------------
	public:
		size_t size() const
		{
			return properties_.size();
		}
		iterator begin()
		{
			return properties_.begin();
		}
		iterator end()
		{
			return properties_.end();
		}
		const_iterator begin() const
		{
			return properties_.begin();
		}
		const_iterator end() const
		{
			return properties_.end();
		}
		
	protected:
		struct Reserve
		{
			Reserve(size_t _n) : n_(_n) 
			{

			}
			void operator()(BaseProperty * _p) const 
			{
				if (_p) _p->reserve(n_); 
			}
			size_t n_;
		};

		struct Resize
		{
			Resize(size_t _n) : n_(_n) 
			{

			}
			void operator()(BaseProperty* _p) const 
			{
				if (_p) 
					_p->resize(n_);
			}
			size_t n_;
		};

		struct ClearAll
		{
			void operator()(BaseProperty* _p) const 
			{ 
				if (_p) _p->clear(); 
			}
		};

		struct Swap
		{
			Swap(size_t _i0, size_t _i1) : i0_(_i0), i1_(_i1) 
			{

			}
			void operator()(BaseProperty * _p) const 
			{
				if (_p) _p->swap(i0_, i1_); 
			}
			size_t i0_;
			size_t i1_;
		};

		struct PopBack
		{
			PopBack()
			{

			}
			void operator()(BaseProperty * _p) const
			{
				if (_p)
				{
					_p->pop_back();
				}
			}
		};

		struct Delete
		{
			Delete()
			{

			}
			void operator()(BaseProperty* _p) const 
			{
				if (_p) 
					delete _p;
				_p = NULL; 
			}
		};
	private:
		Properties properties_;
	};
//---------------------------------------------------------------------------------------------------------------------
}  // namespace OVM
#endif