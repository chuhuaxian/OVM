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

#ifndef _OVM_OPTIONS_H_
#define _OVM_OPTIONS_H_


namespace OVM
{
//---------------------------------------------------------------------------------------------------------------------
	class Options
	{
	public:
		typedef int       enum_type;
		typedef enum_type value_type;

		/// Definitions of %Options for reading and writing. The options can be
		/// or'ed.
		enum Flag 
		{
			Default = 0x0000, ///< No options
			Binary = 0x0001, ///< Set binary mode for r/w
			HalfFaceRegion = 0x0002, ///< Half face region
			HedronRegion = 0x0004, ///< Hedron region
		};

	public:

		/// Default constructor
		Options() : flags_(Default)
		{ 
		}


		/// Copy constructor
		Options(const Options & _opt) : flags_(_opt.flags_)
		{ 
		}


		/// Initializing constructor setting a single option
		Options(Flag _flg) : flags_(_flg)
		{ 
		}


		/// Initializing constructor setting multiple options
		Options(const value_type _flgs) : flags_(_flgs)
		{ 
		}


		~Options()
		{ }

		/// Restore state after default constructor.
		void cleanup(void)
		{
			flags_ = Default;
		}

		/// Clear all bits.
		void clear(void)
		{
			flags_ = 0;
		}

		/// Returns true if all bits are zero.
		bool is_empty(void) const { return !flags_; }

	public:


		//@{
		/// Copy options defined in _rhs.

		Options& operator = (const Options& _rhs)
		{
			flags_ = _rhs.flags_; return *this;
		}

		Options& operator = (const value_type _rhs)
		{
			flags_ = _rhs; return *this;
		}

		//@}


		//@{
		/// Unset options defined in _rhs.

		Options& operator -= (const value_type _rhs)
		{
			flags_ &= ~_rhs; return *this;
		}

		Options& unset(const value_type _rhs)
		{
			return (*this -= _rhs);
		}

		//@}



		//@{
		/// Set options defined in _rhs

		Options & operator += (const value_type _rhs)
		{
			flags_ |= _rhs; return *this;
		}

		Options & set(const value_type _rhs)
		{
			return (*this += _rhs);
		}

		//@}

	public:


		// Check if an option or several options are set.
		bool check(const value_type _rhs) const
		{
			return (flags_ & _rhs) == _rhs;
		}

		bool is_binary() const 
		{ 
			return check(Binary); 
		}
		bool half_face_has_region() const 
		{ 
			return check(HalfFaceRegion); 
		}
		bool hedron_has_region() const 
		{ 
			return check(HedronRegion); 
		}

		/// Returns true if _rhs has the same options enabled.
		bool operator == (const value_type _rhs) const
		{
			return flags_ == _rhs;
		}


		/// Returns true if _rhs does not have the same options enabled.
		bool operator != (const value_type _rhs) const
		{
			return flags_ != _rhs;
		}


		/// Returns the option set.
		operator value_type ()     const { return flags_; }

	private:

		// bool operator && (const value_type _rhs) const;

		value_type flags_;
	};

//---------------------------------------------------------------------------------------------------------------------
} // namespace OVM

#endif // !_OVM_OPTIONS_H_

