/* dependency file generation
   Copyright (C) 2005
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

#include "stdhdr.h"

#include "libgputils.h"
#include "gpasm.h"

/*------------------------------------------------------------------------------------------------*/

void
deps_init(void)
{
  const char *tail;
  char        output_file[BUFSIZ];

  if (state.dep_file != OUT_NAMED) {
    snprintf(state.dep_file_name, sizeof(state.dep_file_name), "%s.d", state.base_file_name);
  }

  if (state.dep_file == OUT_SUPPRESS) {
    state.dep.enabled = false;
    return;
  }

  state.dep.f = fopen(state.dep_file_name, "w");
  if (state.dep.f == NULL) {
    perror(state.dep_file_name);
    exit(1);
  }

  state.dep.enabled = true;

  /* Output file names may not be setup, so make one. */
  tail = (state.mode == MODE_RELOCATABLE) ? "o" : "hex";
  snprintf(output_file, sizeof(output_file), "%s.%s", state.base_file_name, tail);
  fprintf(state.dep.f, "%s : ", output_file);
}

/*------------------------------------------------------------------------------------------------*/

void
deps_add(const char *File_name)
{
  if (state.dep.enabled) {
    fprintf(state.dep.f, " \\\n  %s", File_name);
  }
}

/*------------------------------------------------------------------------------------------------*/

void
deps_close(void)
{
  if (state.dep.enabled) {
    fprintf(state.dep.f, "\n");
    fclose(state.dep.f);
  }
}
