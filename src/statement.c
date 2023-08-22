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

#include <statement.h>
#include <input.h>
#include <fql.h>

prep_result_t statement_prepare(inbuf_t *input, statement_t *statement)
{
	// @todo: port over hashtable from psh
	if (strncmp(input->buffer, "insert", 6) == 0) {
		statement->type = STATEMENT_INSERT;
		return PREPARE_SUCCESS;
	} else if (strcmp(input->buffer, "select") == 0) {
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}

	return PREPARE_UNKNOWN;
}

void statement_exec(statement_t *statement)
{
	switch(statement->type) {
		case STATEMENT_INSERT:
			break;
		case STATEMENT_SELECT:
			break;
	}
}