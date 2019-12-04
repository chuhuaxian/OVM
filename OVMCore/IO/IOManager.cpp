/*---------------------------------------------------------------------------------------------------------------------
*                 ----                  __                        __    __                      __    *               *
*            --           --              \                      /     |  \                    /  |   *               *
*         -                   -            \                    /      |   \                  /   |   *               *
*  	   -                         -          \                  /       |    \                /    |   *               *
*	 -                             -         \                /        |     \              /     |   *               *
*	|                               |         \              /         |      \            /      |   *               *
*   |                               |          \            /          |       \          /       |   *               *
*	|                               |           \          /           |        \        /        |   *               *
*	 -                             -             \        /            |         \      /         |   *               *
*      -                         -                \      /             |          \    /          |   *               *
*         -                   -                    \    /              |           \__/           |   *               *     
*           --            --                        \__/              _|                          |__ *               * 
*                 ----                                                                                *               *
*----------------------------------------------------------------------------------------------------------------------
* License                                                                                                             *                                              
*                                                                                                                     *
*    This file is part of OpenVolumericMesh (OVM).                                                                       *
*                                                                                                                     *
*    OpenVolumericMesh (OVM)is free software: you can redistribute it and/or modify                                      *
*	it under the terms of the GNU Lesser General Public License as                                                    *
*	published by the Free Software Foundation, either version 3 of                                                    *
*	the License, or (at your option) any later version.                                                               *
*	                                                                                                                  *
*	OpenVolumericMesh distributed in the hope that it will be useful,                                                    *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of                                                    *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                                     * 
*	GNU Lesser General Public License for more details.                                                               *
*   This project is created by Chuhua Xian                                                                            *
*   Developers : Chuhua Xian,   chuhuaxian@gmail.com                                                                  *
*                                                                                                                     *
/--------------------------------------------------------------------------------------------------------------------*/
#include <OVM/OVMCore/IO/IOManager.h>

#define _IO_MANAGER_C_


//#define _INPUTLINESIZE_ 4096




namespace OVM
{
	namespace IO
	{
		_IOManager_ * _IO_Manager_Instance_ = 0;
		_IOManager_ & IOManager()
		{
			if (!_IO_Manager_Instance_)
			{
				_IO_Manager_Instance_ = new _IOManager_;
			}
			return *_IO_Manager_Instance_;
		}

		/** read_line_chars()   Read a nonempty line from a file.  
		*
		* A line is considered "nonempty" if it contains something more than white  
		* spaces.  If a line is considered empty, it will be dropped and the next   
		* line will be read, this process ends until reaching the end-of-file or a 
		* non-empty line.  Return NULL if it is the end-of-file, otherwise, return 
		* a pointer to the first non-whitespace character of the line.  
		*/
		char * _IOManager_::read_line_chars(char *  _result, std::ifstream & _infile, int & _linenumber)
		{
			// char * _str,;
			//char * _result;
			do 
			{
				if (_infile.eof()) 
				{
					return (char *) NULL;
				}
				//result = fgets(_str, (int)_INPUTLINESIZE_ - 1, _infile);
				_infile.getline(_result, (int) _INPUTLINESIZE_); 
				_linenumber ++;
				// Search for a non-empty line.
				// Skip white spaces.
				while ((*_result == ' ') || (*_result == '\t'))
				{
					_result ++;
				}
				// If it's end of line, read another line and try again.
			} while (*_result == '\0');
			return _result;
		}
		/** find_next_sub_str() find the next field of a numbering string
		*
		* Jumps past the current field by searching for whitespace or a comma, then
		* jumps past the whitespace or the comma to find the next field that looks 
		* like a number.   
		*      
		*/
		char * _IOManager_::find_next_sub_str(char * _str)
		{
			char * result;

			result = _str;
			// Skip the current field.  Stop upon reaching whitespace or a comma.
			while ((*result != '\0') && 
				(*result != '#') && 
				(*result != ' ') && 
				(*result != '\t') && 
				(*result != ','))
			{
				result++;
			}
			// Now skip the whitespace and anything else that doesn't look like a
			//   number, a comment, or the end of a line. 
			while ((*result != '\0') && 
				(*result != '#')  && 
				(*result != '.')  && 
				(*result != '+')  && 
				(*result != '-')  && 
				((*result < '0')  || (*result > '9'))
				) 
			{
				result++;
			}
			// Check for a comment (prefixed with `#').
			if (*result == '#') {
				*result = '\0';
			}
			return result;
		}
		/** trim_str() Trim a string, skip the space and tab char
		*/
		char * _IOManager_::trim_str(char * _str)
		{
			char * result;
			result = _str;
			char * reverse;
			while ((*result == ' ') || 
				   (*result == '\t'))
			{
				++ result;
			}
			reverse = _str + strlen(_str) - 1;
			while ((*reverse == ' ') || 
				   (*reverse == '\t'))
			{
				-- reverse ;
			}
			++ reverse;
			*reverse = '\0';
			return result;

		}
//---------------------------------------------------------------------------------------------------------------------
	}
}