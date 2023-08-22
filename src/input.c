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

#include <input.h>

void input_read(inbuf_t *input)
{
	ssize_t bytes = getline(&(input->buffer), &(input->buflen), stdin);

	if (bytes <= 0) {
		printf("Error reading input\n");
		exit(EXIT_FAILURE);
	}

	input->inlen = bytes - 1;
	input->buffer[bytes - 1] = 0;
}

inbuf_t *input_newbuf()
{
	inbuf_t *new = (inbuf_t *)malloc(sizeof(inbuf_t));
	new->buffer = NULL;
	new->buflen = 0;
	new->inlen = 0;

	return new;
}

void input_freebuf(inbuf_t *input)
{
	free(input->buffer);
	free(input);
}