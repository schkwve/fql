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
#include <stdio.h>

#include <command.h>
#include <statement.h>
#include <input.h>
#include <fql.h>

prep_result_t statement_prepare(inbuf_t *input, statement_t *statement)
{
	// @todo: port over hashtable from psh
	if (strncmp(input->buffer, "insert", 6) == 0) {
		statement->type = STATEMENT_INSERT;
		int args = sscanf(
			input->buffer, "insert %d %s %s", &(statement->insert_row.id),
			statement->insert_row.username, statement->insert_row.email);
		if (args < 3) {
			return PREPARE_SYNTAX_ERR;
		}
		return PREPARE_SUCCESS;
	} else if (strcmp(input->buffer, "select") == 0) {
		statement->type = STATEMENT_SELECT;
		return PREPARE_SUCCESS;
	}

	return PREPARE_UNKNOWN;
}

exec_result_t statement_exec(statement_t *statement, table_t *table)
{
	switch (statement->type) {
	case STATEMENT_INSERT:
		return cmd_insert(statement, table);
	case STATEMENT_SELECT:
		return cmd_select(statement, table);
	}
}