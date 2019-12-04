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


#ifndef _OVM_COVMPILER_H_
#define _OVM_COVMPILER_H_

//---------------------------------------------------------------------------------------------------------------------

#if defined(ACGMAKE_STATIC_BUILD)
#  define OVM_STATIC_BUILD 1
#endif

//=============================================================================

#if defined(_DEBUG) || defined(DEBUG)
#  define OVM_DEBUG
#endif

//=============================================================================

// Workaround for Intel Compiler with MS VC++ 6
#if defined(_MSC_VER) && \
   ( defined(__ICL) || defined(__INTEL_COVMPILER) || defined(__ICC) )
#  if !defined(__INTEL_COVMPILER)
#    define __INTEL_COVMPILER __ICL
#  endif
#  define OVM_USE_INTEL_COVMPILER 1
#endif

// --------------------------------------------------------- MS Visual C++ ----
// Compiler _MSC_VER
// .NET 2002 1300 
// .NET 2003 1310
// .NET 2005 1400
#if defined(_MSC_VER) && !defined(OVM_USE_INTEL_COVMPILER)
#  if (_MSC_VER == 1300)
#    define OVM_CC_MSVC
#    define OVM_TYPENAME
#    define OVM_OUT_OF_CLASS_TEMPLATE       0
#    define OVM_PARTIAL_SPECIALIZATION      0
#    define OVM_INCLUDE_TEMPLATES           1
#  elif (_MSC_VER == 1310)
#    define OVM_CC_MSVC
#    define OVM_TYPENAME
#    define OVM_OUT_OF_CLASS_TEMPLATE       1
#    define OVM_PARTIAL_SPECIALIZATION      1
#    define OVM_INCLUDE_TEMPLATES           1
#  elif (_MSC_VER >= 1400) // settings for .NET 2005 (NOTE: not fully tested)
#    define OVM_TYPENAME
#    define OVM_OUT_OF_CLASS_TEMPLATE       1
#    define OVM_PARTIAL_SPECIALIZATION      1
#    define OVM_INCLUDE_TEMPLATES           1
#  else
#    error "Version 7 (.NET 2002) or higher of the MS VC++ is required!"
#  endif
//   currently no windows dll supported
#  define OVM_STATIC_BUILD 1
#  if defined(_MT)
#    define OVM_REENTRANT 1
#  endif
#  define OVM_CC "MSVC++"
#  define OVM_CC_VERSION _MSC_VER
// Does not work stable because the define _CPPRTTI sometimes does not exist,
// though the option /GR is set!? 
#  if defined(__cplusplus) && !defined(_CPPRTTI)
#    error "Enable Runtime Type Information (Compiler Option /GR)!"
#  endif
//#  if !defined(_USE_MATH_DEFINES)
//#    error "You have to define _USE_MATH_DEFINES in the compiler settings!"
//#  endif
// ------------------------------------------------------------- Borland C ----
#elif defined(__BORLANDC__)
#  error "Borland Compiler are not supported yet!"
// ------------------------------------------------------------- GNU C/C++ ----
#elif defined(__GNUC__) && !defined(__ICC)
#  define OVM_CC_GCC
#  define OVM_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 )
#  define OVM_GCC_MAJOR                __GNUC__
#  define OVM_GCC_MINOR                __GNUC_MINOR__
#  if (OVM_GCC_VERSION >= 30200)
#    define OVM_TYPENAME typename
#    define OVM_OUT_OF_CLASS_TEMPLATE  1
#    define OVM_PARTIAL_SPECIALIZATION 1
#    define OVM_INCLUDE_TEMPLATES      1
#  else
#    error "Version 3.2.0 or better of the GNU Compiler is required!"
#  endif
#  if defined(_REENTRANT)
#    define OVM_REENTRANT 1
#  endif
#  define OVM_CC "GCC"
#  define OVM_CC_VERSION OVM_GCC_VERSION
// ------------------------------------------------------------- Intel icc ----
#elif defined(__ICC) || defined(__INTEL_COVMPILER)
#  define OVM_CC_ICC
#  define OVM_TYPENAME typename
#  define OVM_OUT_OF_CLASS_TEMPLATE  1
#  define OVM_PARTIAL_SPECIALIZATION 1
#  define OVM_INCLUDE_TEMPLATES      1
#  if defined(_REENTRANT) || defined(_MT)
#    define OVM_REENTRANT 1
#  endif
#  define OVM_CC "ICC"
#  define OVM_CC_VERSION __INTEL_COVMPILER
//   currently no windows dll supported
#  if defined(_MSC_VER) || defined(WIN32)
#    define OVM_STATIC_BUILD 1
#  endif
// ------------------------------------------------------ MIPSpro Compiler ----
#elif defined(__MIPS_ISA) || defined(__mips)
// _MIPS_ISA                    
// _COVMPILER_VERSION            e.g. 730, 7 major, 3 minor
// _MIPS_FPSET                  32|64
// _MIPS_SZINT                  32|64
// _MIPS_SZLONG                 32|64
// _MIPS_SZPTR                  32|64
#  define OVM_CC_MIPS
#  define OVM_TYPENAME typename
#  define OVM_OUT_OF_CLASS_TEMPLATE    1
#  define OVM_PARTIAL_SPECIALIZATION   1
#  define OVM_INCLUDE_TEMPLATES        0
#  define OVM_CC "MIPS"
#  define OVM_CC_VERSION _COVMPILER_VERSION
// ------------------------------------------------------------------ ???? ----
#else
#  error "You're using an unsupported compiler!"
#endif


//---------------------------------------------------------------------------------------------------------------------
#endif // _OVM_MESH_COVMPILER_H_ defined

