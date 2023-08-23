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

#include <table.h>
#include <fql.h>

cursor_t *table_start(table_t *table)
{
	cursor_t *new = malloc(sizeof(cursor_t));
	new->table = table;
	new->row_num = 0;
	new->eot = (table->num_rows == 0);

	return new;
}

cursor_t *table_end(table_t *table)
{
	cursor_t *new = malloc(sizeof(cursor_t));
	new->table = table;
	new->row_num = table->num_rows;
	new->eot = true;

	return new;
}