/* Linker script processing
   Copyright (C) 2001, 2002, 2003, 2004, 2005
   Craig Franklin
 
This file is part of gputils.
 
gputils is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.
 
gputils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with gputils; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#ifndef SCRIPT_H
#define SCRIPT_H

#include "libgputils.h"

extern void script_error(const char *Messg, const char *Detail);
extern int script_add_path(const pnode_t *Parms);
extern void script_add_symbol_value(const char *Name, long Value);
extern long script_get_symbol_value(const char *Name);
extern int script_execute_command(const char *Name, const pnode_t *Parms);

#endif
