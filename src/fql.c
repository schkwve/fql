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

int main()
{
	inbuf_t *input_buf = input_newbuf();

	for (;;) {
		printf("fql> ");
		input_read(input_buf);

		if (strcmp(input_buf->buffer, ".exit") == 0) {
			input_freebuf(input_buf);
			exit(EXIT_SUCCESS);
		} else {
			printf("Unknown command: %s\n", input_buf->buffer);
		}
	}

	return 0;
}