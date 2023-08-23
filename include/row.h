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

#ifndef __ROW_H_
#define __ROW_H_

#include <stdlib.h>

#include <fql.h>

#define COL_USERNAME_SIZE 32
#define COL_EMAIL_SIZE 255

typedef struct {
	uint32_t id;
	char username[COL_USERNAME_SIZE + 1];
	char email[COL_EMAIL_SIZE + 1];
} row_t;

/// TEMPORARY
const static uint32_t PAGE_SIZE = 4096;

#define TABLE_MAX_PAGES 100

const static uint32_t ID_SIZE = sizeof_attr(row_t, id);
const static uint32_t USERNAME_SIZE = sizeof_attr(row_t, username);
const static uint32_t EMAIL_SIZE = sizeof_attr(row_t, email);
const static uint32_t ID_OFFSET = 0;
const static uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const static uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const static uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

const static uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const static uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;
/// TEMPORARY

typedef struct {
	statement_type_t type;
	row_t insert_row;
} statement_t;

typedef struct {
	uint32_t num_rows;
	void *pages[TABLE_MAX_PAGES];
} table_t;

void *row_slot(table_t *table, uint32_t row_num);

void row_print(row_t *row);

void row_serialize(row_t *src, void *dest);
void row_deserialize(void *src, row_t *dest);

#endif /* __ROW_H_ */