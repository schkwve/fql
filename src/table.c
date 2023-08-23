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

#include <btree.h>
#include <pager.h>
#include <table.h>
#include <fql.h>

cursor_t *table_start(table_t *table)
{
	cursor_t *new = malloc(sizeof(cursor_t));
	new->table = table;
	new->page_num = table->root_page_num;
	new->cell_num = 0;

	void *root_node = pager_get_page(table->pager, table->root_page_num);
	uint32_t num_cells = *leaf_node_num_cells(root_node);
	new->eot = (num_cells == 0);

	return new;
}

cursor_t *table_end(table_t *table)
{
	cursor_t *new = malloc(sizeof(cursor_t));
	new->table = table;
	new->page_num = table->root_page_num;

	void *root_node = pager_get_page(table->pager, table->root_page_num);
	uint32_t num_cells = *leaf_node_num_cells(root_node);
	new->cell_num = num_cells;
	new->eot = true;

	return new;
}