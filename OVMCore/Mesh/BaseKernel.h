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

#ifndef _OVM_BASE_KERNEL_
#define _OVM_BASE_KERNEL_


#include <OVM/OVMCore/Util/PropertyContainer.h>
namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	class BaseKernel
	{
	public:
		typedef PropertyContainer::iterator       prop_iterator;
		typedef PropertyContainer::const_iterator const_prop_iterator;
	public:
		BaseKernel()
		{

		}
		virtual ~ BaseKernel()
		{
			v_properties_.clear();
			he_properties_.clear();
			hf_properties_.clear();
			h_properties_.clear();
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		template < class T >
		void add_property(VPropHandleT<T> & _ph, const std::string & _name = "_v_property_")
		{
			_ph = VPropHandleT<T>(v_properties_.add(T(), _name));
			v_properties_.resize(n_vertices());
		}
		template < class T >
		void add_property(HEPropHandleT<T> & _ph, const std::string & _name = "_he_property_")
		{
			_ph = HEPropHandleT<T>(he_properties_.add(T(), _name));
			he_properties_.resize(n_half_edges());
		}
		template < class T >
		void add_property(HFPropHandleT<T> & _ph, const std::string & _name = "_hf_property_")
		{
			_ph = HFPropHandleT<T>(hf_properties_.add(T(), _name));
			hf_properties_.resize(n_half_faces());
		}
		template < class T >
		void add_property(HPropHandleT<T> & _ph, const std::string & _name = "_h_property_")
		{
			_ph = HPropHandleT<T>(h_properties_.add(T(), _name));
			h_properties_.resize(n_hedrons());
		}
	public:
		template < class T >
		void remove_property(VPropHandleT<T> & _ph)
		{
			if (_ph.is_valid())
			{
				v_properties_.remove(_ph);
			}
			_ph.reset();
		}
		template < class T >
		void remove_property(HEPropHandleT<T> & _ph)
		{
			if (_ph.is_valid())
			{
				he_properties_.remove(_ph);
			}
			_ph.reset();
		}
		template < class T >
		void remove_property(HFPropHandleT<T> & _ph)
		{
			if (_ph.is_valid())
			{
				hf_properties_.remove(_ph);
			}
			_ph.reset();
		}
		template < class T >
		void remove_property(HPropHandleT<T> & _ph)
		{
			if (_ph.is_valid())
			{
				h_properties_.remove(_ph);
			}
			_ph.reset();
		}
	public:
		template < class T >
		bool get_property_handle(VPropHandleT<T> & _ph, const std::string & _name) const
		{
			_ph = VPropHandleT<T>(v_properties_.handle(T(), _name));
			return _ph.is_valid();
		}
		template < class T >
		bool get_property_handle(HEPropHandleT<T> & _ph, const std::string & _name) const
		{
			_ph = HEPropHandleT<T>(he_properties_.handle(T(), _name));
			return _ph.is_valid();
		}
		template < class T >
		bool get_property_handle(HFPropHandleT<T> & _ph, const std::string & _name) const
		{
			_ph = HFPropHandleT<T>(hf_properties_.handle(T(), _name));
			return _ph.is_valid();
		}
		template < class T >
		bool get_property_handle(HPropHandleT<T> & _ph, const std::string & _name) const
		{
			_ph = HPropHandleT<T>(h_properties_.handle(T(), _name));
			return _ph.is_valid();
		}
	public:
		template < class T > 
		PropertyT<T> & property(VPropHandleT<T> & _ph)
		{
			return v_properties_.property(_ph);
		}

		template < class T >
		PropertyT<T> & property(HEPropHandleT<T> & _ph)
		{
			return he_properties_.property(_ph);
		}
		template < class T >
		PropertyT<T> & property(HFPropHandleT<T> & _ph)
		{
			return hf_properties_.property(_ph);
		}
		template < class T >
		PropertyT<T> & property(HPropHandleT<T> & _ph)
		{
			return h_properties_.property(_ph);
		}
		
		template < class T > 
		const PropertyT<T> & property(VPropHandleT<T> & _ph) const
		{
			return v_properties_.property(_ph);
		}

		template < class T >
		const PropertyT<T> & property(HEPropHandleT<T> & _ph) const
		{
			return he_properties_.property(_ph);
		}
		template < class T >
		const HFPropHandleT<T> & property(HFPropHandleT<T> & _ph) const
		{
			return hf_properties_.property(_ph);
		}
		template < class T >
		const PropertyT<T> & property(HPropHandleT<T> & _ph) const
		{
			return hf_properties_.property(_ph);

		}

	public:
		template < class T > 
		typename VPropHandleT<T>::reference property(VPropHandleT<T> _ph, VertexHandle _vh)
		{
			return v_properties_.property(_ph)[_vh.idx()];
		}

		template < class T >
		typename HEPropHandleT<T>::reference property(HEPropHandleT<T> _ph, HalfEdgeHandle _heh)
		{
			return he_properties_.property(_ph)[_heh.idx()];
		}
		template < class T >
		typename HFPropHandleT<T>::reference property(HFPropHandleT<T> _ph, HalfFaceHandle _hfh)
		{
			return hf_properties_.property(_ph)[_hfh.idx()];
		}
		template < class T >
		typename HPropHandleT<T>::reference property(HPropHandleT<T> _ph, HedronHandle _hh)
		{
			return h_properties_.property(_ph)[_hh.idx()];
		}


		template < class T > 
		typename VPropHandleT<T>::const_reference property(VPropHandleT<T> _ph, VertexHandle _vh) const
		{
			return v_properties_.property(_ph)[_vh.idx()];
		}

		template < class T >
		const typename HEPropHandleT<T>::const_reference property(HEPropHandleT<T> _ph, HalfEdgeHandle _heh) const
		{
			return he_properties_.property(_ph)[_heh.idx()];
		}
		template < class T >
		typename HFPropHandleT<T>::const_reference property(HFPropHandleT<T> _ph, HalfFaceHandle _hfh) const
		{
			return hf_properties_.property(_ph)[_hfh.idx()];
		}
		template < class T >
		typename HPropHandleT<T>::const_reference property(HPropHandleT<T> _ph, HedronHandle _hh) const
		{
			return h_properties_.property(_ph)[_hh.idx()];
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		BaseProperty * _get_v_property(const std::string & _name)
		{
			return v_properties_.property(_name);
		}
		BaseProperty * _get_he_property(const std::string & _name)
		{
			return he_properties_.property(_name);
		}
		BaseProperty * _get_hf_property(const std::string & _name)
		{
			return hf_properties_.property(_name);
		}
		BaseProperty * _get_h_property(const std::string & _name)
		{
			return h_properties_.property(_name);
		}
		const BaseProperty * _get_v_property(const std::string & _name) const
		{
			return v_properties_.property(_name);
		}
		const BaseProperty * _get_he_property(const std::string & _name) const
		{
			return he_properties_.property(_name);
		}
		const BaseProperty * _get_hf_property(const std::string & _name) const 
		{
			return hf_properties_.property(_name);
		}
		const BaseProperty * _get_h_property(const std::string & _name) const
		{
			return h_properties_.property(_name);
		}

		size_t _add_v_property(BaseProperty * _bp)
		{
			return v_properties_._add(_bp);
		}
		size_t _add_he_property(BaseProperty * _bp)
		{
			return he_properties_._add(_bp);
		}
		size_t _add_hf_property(BaseProperty * _bp)
		{
			return hf_properties_._add(_bp);
		}
		size_t _add_h_property(BaseProperty * _bp)
		{
			return h_properties_._add(_bp);
		}


		BaseProperty & _v_property(size_t  _idx)
		{
			return v_properties_._property(_idx);
		}
		BaseProperty & _he_property(size_t _idx)
		{
			return v_properties_._property(_idx);
		}
		BaseProperty & _hf_property(size_t _idx)
		{
			return v_properties_._property(_idx);
		}
		BaseProperty & _h_property(size_t _idx)
		{
			return v_properties_._property(_idx);
		}
		const BaseProperty & _v_property(size_t _idx) const
		{
			return v_properties_._property(_idx);
		}
		const BaseProperty & _he_property(size_t _idx) const
		{
			return v_properties_._property(_idx);
		}
		const BaseProperty & _hf_property(size_t _idx) const
		{
			return v_properties_._property(_idx);
		}
		const BaseProperty & _h_property(size_t _idx) const
		{
			return v_properties_._property(_idx);
		}
	protected:
		BaseProperty & _v_property(BaseHandle _h)
		{
			return v_properties_._property(_h.idx());
		}
		BaseProperty & _he_property(BaseHandle _h)
		{
			return v_properties_._property(_h.idx());
		}
		BaseProperty & _hf_property(BaseHandle _h)
		{
			return v_properties_._property(_h.idx());
		}
		BaseProperty & _h_property(BaseHandle _h)
		{
			return v_properties_._property(_h.idx());
		}
		const BaseProperty & _v_property(BaseHandle _h) const
		{
			return v_properties_._property(_h.idx());
		}
		const BaseProperty & _he_property(BaseHandle _h) const
		{
			return v_properties_._property(_h.idx());
		}
		const BaseProperty & _hf_property(BaseHandle _h) const
		{
			return v_properties_._property(_h.idx());
		}
		const BaseProperty & _h_property(BaseHandle _h) const
		{
			return v_properties_._property(_h.idx());
		}
	protected:
		void v_properties_reserve(size_t _n) const
		{
			v_properties_.reserve(_n);
		}
		void v_properties_resize(size_t _n) const
		{
			v_properties_.resize(_n);
		}
		void v_properties_clear()
		{
			v_properties_.clear();
		}
		void v_properties_swap(size_t _i0, size_t _i1) const
		{
			v_properties_.swap(_i0, _i1);
		}

		void he_properties_reserve(size_t _n) const
		{
			he_properties_.reserve(_n);
		}
		void he_properties_resize(size_t _n) const
		{
			he_properties_.resize(_n);
		}
		void he_properties_clear()
		{
			he_properties_.clear();
		}
		void he_properties_swap(size_t _i0, size_t _i1) const
		{
			he_properties_.swap(_i0, _i1);
		}
		void hf_properties_reserve(size_t _n) const
		{
			hf_properties_.reserve(_n);
		}
		void hf_properties_resize(size_t _n) const
		{
			hf_properties_.resize(_n);
		}
		void hf_properties_clear()
		{
			hf_properties_.clear();
		}
		void hf_properties_swap(size_t _i0, size_t _i1) const
		{
			hf_properties_.swap(_i0, _i1);
		}
		void h_properties_reserve(size_t _n) const
		{
			h_properties_.reserve(_n);
		}
		void h_properties_resize(size_t _n) const
		{
			h_properties_.resize(_n);
		}
		void h_properties_clear()
		{
			h_properties_.clear();
		}
		void h_properties_swap(size_t _i0, size_t _i1) const
		{
			h_properties_.swap(_i0, _i1);
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		virtual size_t n_vertices() const
		{
			return 0;
		}
		virtual size_t n_half_edges()const
		{
			return 0;
		}
		virtual size_t n_half_faces() const
		{
			return 0;
		}
		virtual size_t n_hedrons() const
		{
			return 0;
		}
	//-----------------------------------------------------------------------------------------------------------------
	public:
		size_t n_v_properties() const
		{
			return v_properties_.size();
		}
		size_t n_he_properties() const
		{
			return he_properties_.size();
		}
		size_t n_hf_properties() const
		{
			return hf_properties_.size();
		}
		size_t n_h_properties() const
		{
			return h_properties_.size();
		}
	public:
		prop_iterator v_prop_begin()
		{
			return v_properties_.begin();
		}
		prop_iterator v_prop_end()
		{
			return v_properties_.end();
		}
		prop_iterator he_prop_begin()
		{
			return he_properties_.begin();
		}
		prop_iterator he_prop_end()
		{
			return he_properties_.end();
		}
		prop_iterator hf_prop_begin()
		{
			return hf_properties_.begin();
		}
		prop_iterator hf_prop_end()
		{
			return hf_properties_.end();
		}
		prop_iterator h_prop_begin()
		{
			return h_properties_.begin();
		}
		prop_iterator h_prop_end()
		{
			return h_properties_.end();
		}


		const_prop_iterator v_prop_begin() const
		{
			return v_properties_.begin();
		}
		const_prop_iterator v_prop_end() const
		{
			return v_properties_.end();
		}
		const_prop_iterator he_prop_begin() const
		{
			return he_properties_.begin();
		}
		const_prop_iterator he_prop_end() const
		{
			return he_properties_.end();
		}
		const_prop_iterator hf_prop_begin() const
		{
			return hf_properties_.begin();
		}
		const_prop_iterator hf_prop_end() const
		{
			return hf_properties_.end();
		}
		const_prop_iterator h_prop_begin() const
		{
			return h_properties_.begin();
		}
		const_prop_iterator h_prop_end() const
		{
			return h_properties_.end();
		}
	//-----------------------------------------------------------------------------------------------------------------
	private:
		PropertyContainer v_properties_;
		PropertyContainer he_properties_;
		PropertyContainer hf_properties_;
		PropertyContainer h_properties_;
	};

//---------------------------------------------------------------------------------------------------------------------
}  
#endif