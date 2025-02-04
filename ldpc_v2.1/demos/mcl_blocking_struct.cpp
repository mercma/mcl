/* $Id: mcl_blocking_struct.cpp,v 1.2 2006/03/07 16:55:07 roca Exp $ */
/*
 *  (c) Copyright 2002-2006 INRIA - All rights reserved
 *  Main authors: Christoph Neumann (christoph.neumann@inrialpes.fr)
 *                Vincent Roca      (vincent.roca@inrialpes.fr)
 *		  Julien Laboure   (julien.laboure@inrialpes.fr)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
 *  USA.
 */


#include "./perf_tool2.h"


INT32	double_to_closest_int (double value);


/**
 * Compute source block structure.
 * => See header file for more informations.
 */
void
mcl_compute_blocking_struct (UINT32			B,
			     UINT32			L,
			     UINT32			E,
			     mcl_blocking_struct_t	*bs)
{
	UINT32	T; /* number of source symbols in the object */
	double	A; /* average length of a source block in number of symbols */
	double	A_fraction;

	T = (UINT32)ceil((double)L / (double)E);
	bs->block_nb = (INT32)ceil((double)T / (double)B);
	A = (double)T/(double)bs->block_nb; /* average size of a block; non integer */
	bs->A_large = (UINT32)ceil((double)A);
	bs->A_small = (UINT32)floor((double)A);
	ASSERT(bs->A_large <= B);
	A_fraction = A - bs->A_small;
	bs->I = double_to_closest_int(A_fraction * (double)bs->block_nb);
#if 0
	PRINT_OUT((mcl_stdout,
	"    mcl_compute_blocking_struct: B=%d, L=%d, E=%d\n\t\tblock_nb=%d, I=%d, A_large=%d, A_small=%d\n",
		B, L, E, bs->block_nb, bs->I, bs->A_large, bs->A_small))
#endif
}


/*
 *   MAD-ALC, implementation of ALC/LCT protocols
 *   Copyright (c) 2003 TUT - Tampere University of Technology
 *   main authors/contacts: jani.peltotalo@tut.fi and sami.peltotalo@tut.fi
 */ 
/**
 * This function converts double value to the closest integer value.
 * Usefull if the double value can have small calculation errors.
 * @params value	value to be converted.
 * @return		converted integer value.
 */
INT32
double_to_closest_int (double	value)
{
	double ceil_value;
	double floor_value;
	double abs_diff1;
	double abs_diff2;

	ceil_value = ceil(value);
	floor_value = floor(value);
	abs_diff1 = fabs(value - ceil_value);
	abs_diff2 = fabs(value - floor_value);
	if(abs_diff1 < abs_diff2) {
		return((INT32)ceil_value);
	} else {
		return((INT32)floor_value);
	}
}

