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

#include <btree.h>
#include <db.h>
#include <command.h>
#include <statement.h>
#include <input.h>
#include <row.h>
#include <table.h>
#include <pager.h>
#include <fql.h>

cmd_result_t cmd_meta_exec(inbuf_t *input, table_t *table)
{
	// @todo: port hashtable from psh
	if (strcmp(input->buffer, ".exit") == 0) {
		db_close(table);
		exit(EXIT_SUCCESS);
	}

	return COMMAND_META_UNKNOWN;
}

exec_result_t cmd_insert(statement_t *statement, table_t *table)
{
	void *node = pager_get_page(table->pager, table->root_page_num);
	if ((*leaf_node_num_cells(node) >= LEAF_NODE_MAX_CELLS)) {
		return EXECUTE_TABLE_FULL;
	}

	row_t *insert_row = &(statement->insert_row);
	cursor_t *cursor = table_end(table);

	leaf_node_insert(cursor, insert_row->id, insert_row);

	free(cursor);

	return EXECUTE_SUCCESS;
}

exec_result_t cmd_select(statement_t *statement, table_t *table)
{
	cursor_t *cursor = table_start(table);
	row_t row;

	while (!(cursor->eot)) {
		row_deserialize(cursor_val(cursor), &row);
		row_print(&row);
		cursor_advance(cursor);
	}

	free(cursor);

	return EXECUTE_SUCCESS;
}