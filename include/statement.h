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

#ifndef __STATEMENT_H_
#define __STATEMENT_H_

#include <input.h>
#include <fql.h>

typedef enum {
	STATEMENT_INSERT,
	STATEMENT_SELECT
} statement_type_t;

typedef struct {
	statement_type_t type;
} statement_t;

prep_result_t statement_prepare(inbuf_t *input, statement_t *statement);
void statement_exec(statement_t *statement);

#endif /* __STATEMENT_H_ */