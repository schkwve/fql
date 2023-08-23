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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <btree.h>
#include <db.h>
#include <pager.h>

table_t *db_open(const char *filename)
{
	pager_t *pager = pager_open(filename);

	table_t *new = malloc(sizeof(table_t));
	new->pager = pager;
	new->root_page_num = 0;

	if (pager->num_pages == 0) {
		void *root_node = pager_get_page(pager, 0);
		leaf_node_init(root_node);
	}

	return new;
}

void db_close(table_t *table)
{
	pager_t *pager = table->pager;

	for (uint32_t i = 0; i < pager->num_pages; i++) {
		if (pager->pages[i] == NULL) {
			continue;
		}

		pager_flush(pager, i);
		free(pager->pages[i]);
		pager->pages[i] = NULL;
	}

	int result = close(pager->file_desc);
	if (result == -1) {
		perror("Error closing db: ");
		exit(EXIT_FAILURE);
	}

	for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
		void *page = pager->pages[i];
		if (page) {
			free(page);
			pager->pages[i] = NULL;
		}
	}

	free(pager);
	free(table);
}