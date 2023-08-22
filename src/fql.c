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

int main()
{
	inbuf_t *input_buf = input_newbuf();

	for (;;) {
		printf("fql> ");
		input_read(input_buf);

		if (input_buf->buffer[0] == '.') {
			switch (cmd_meta_exec(input_buf)) {
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
			case PREPARE_UNKNOWN:
				printf("Unknown keyword at start of %s\n", input_buf->buffer);
				continue;
		}
		statement_exec(&statement);
	}

	return 0;
}