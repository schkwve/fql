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

#ifndef __FQL_H_
#define __FQL_H_

// s = structure
// a = attribute
#define sizeof_attr(s, a) sizeof(((s *)0)->a)

typedef enum {
	PREPARE_SUCCESS,
	PREPARE_UNKNOWN,
	PREPARE_SYNTAX_ERR
} prep_result_t;

typedef enum {
	COMMAND_META_SUCCESS,
	COMMAND_META_UNKNOWN,
} cmd_result_t;

typedef enum { EXECUTE_SUCCESS, EXECUTE_TABLE_FULL } exec_result_t;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } statement_type_t;

#endif /* __FQL_H_ */