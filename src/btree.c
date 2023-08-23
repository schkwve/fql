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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <btree.h>
#include <pager.h>
#include <row.h>
#include <fql.h>

void leaf_node_init(void *node)
{
	*leaf_node_num_cells(node) = 0;
}

uint32_t *leaf_node_num_cells(void *node)
{
	return node + LEAF_NODE_NUM_CELLS_OFFSET;
}

void *leaf_node_cell(void *node, uint32_t cell_num)
{
	return node + LEAF_NODE_HEADER_SIZE + cell_num * LEAF_NODE_CELL_SIZE;
}

uint32_t *leaf_node_key(void *node, uint32_t cell_num)
{
	return leaf_node_cell(node, cell_num);
}

uint32_t *leaf_node_val(void *node, uint32_t cell_num)
{
	return leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_SIZE;
}

void leaf_node_insert(cursor_t *cursor, uint32_t key, row_t *val)
{
	void *node = pager_get_page(cursor->table->pager, cursor->page_num);
	uint32_t num_cells = *leaf_node_num_cells(node);

	if (num_cells >= LEAF_NODE_MAX_CELLS) {
		printf("UNIMPLEMENTED: Splitting a leaf node\n");
		exit(EXIT_FAILURE);
	}

	if (cursor->cell_num < num_cells) {
		for (uint32_t i = num_cells; i > cursor->cell_num; i--) {
			memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i - 1),
				   LEAF_NODE_CELL_SIZE);
		}
	}

	*(leaf_node_num_cells(node)) += 1;
	*(leaf_node_key(node, cursor->cell_num)) = key;
	row_serialize(val, leaf_node_val(node, cursor->cell_num));
}