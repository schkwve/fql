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

#include <row.h>
#include <pager.h>
#include <fql.h>

void *row_slot(table_t *table, uint32_t row_num)
{
	uint32_t page_num = row_num / ROWS_PER_PAGE;
	void *page = pager_get_page(table->pager, page_num);

	uint32_t row_off = row_num % ROWS_PER_PAGE;
	uint32_t byte_off = row_off * ROW_SIZE;
	return page + byte_off;
}

void row_print(row_t *row)
{
	printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

void row_serialize(row_t *src, void *dest)
{
	memcpy(dest + ID_OFFSET, &(src->id), ID_SIZE);
	memcpy(dest + USERNAME_OFFSET, &(src->username), USERNAME_SIZE);
	memcpy(dest + EMAIL_OFFSET, &(src->email), EMAIL_SIZE);
}

void row_deserialize(void *src, row_t *dest)
{
	memcpy(&(dest->id), src + ID_OFFSET, ID_SIZE);
	memcpy(&(dest->username), src + USERNAME_OFFSET, USERNAME_SIZE);
	memcpy(&(dest->email), src + EMAIL_OFFSET, EMAIL_SIZE);
}