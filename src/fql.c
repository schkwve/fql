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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fql.h>
#include <input.h>
#include <command.h>
#include <statement.h>
#include <db.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Please supply a database filename.\n");
		exit(EXIT_FAILURE);
	}

	inbuf_t *input_buf = input_newbuf();
	table_t *table = db_open(argv[1]);

	for (;;) {
		printf("fql> ");
		input_read(input_buf);

		if (input_buf->buffer[0] == '.') {
			switch (cmd_meta_exec(input_buf, table)) {
			case COMMAND_META_SUCCESS:
				continue;
			case COMMAND_META_UNKNOWN:
				printf("Unknown command: %s\n", input_buf->buffer);
				continue;
			}
		}

		statement_t statement;
		switch (statement_prepare(input_buf, &statement)) {
		case PREPARE_SUCCESS:
			break;
		case PREPARE_STR_TOO_LONG:
			printf("String is too long.\n");
			continue;
		case PREPARE_NEG_ID:
			printf("ID must be positive.\n");
			continue;
		case PREPARE_SYNTAX_ERR:
			printf("Syntax error.\n");
			continue;
		case PREPARE_UNKNOWN:
			printf("Unknown keyword at start of %s\n", input_buf->buffer);
			continue;
		}

		switch (statement_exec(&statement, table)) {
		case EXECUTE_SUCCESS:
			printf("OK.\n");
			break;
		case EXECUTE_TABLE_FULL:
			printf("Error: Table full.\n");
			break;
		}
	}

	return 0;
}