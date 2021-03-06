/* gpasm preprocessor defines and includes
   Copyright (C) 1012 Borut Razem

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

#ifndef __PREPROCESS_H__
#define __PREPROCESS_H__

#define PREPROC_MAX_DEPTH       16

/* from preprocess.c */
extern void preprocess_line(char *Buf, int *Num, int Max_size);

/* from ppscan.c */
extern int ppcol_begin;
extern int ppcol_end;

extern int ppparse_chunk(char *Buf, int Begin, int End);
extern int pplex(void);

/* from ppparse.c */
extern int ppresult;

extern int ppparse(void);

#endif
