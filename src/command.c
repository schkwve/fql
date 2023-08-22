/**
 * FQL
 * Copyright (C) 2023 Jozef Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string.h>
#include <stdlib.h>

#include <command.h>
#include <input.h>
#include <fql.h>

cmd_result_t cmd_meta_exec(inbuf_t *input)
{
	// @todo: port hashtable from psh
	if (strcmp(input->buffer, ".exit") == 0) {
		exit(EXIT_SUCCESS);
	}

	return COMMAND_META_UNKNOWN;
}