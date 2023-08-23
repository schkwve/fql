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
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <pager.h>
#include <btree.h>
#include <fql.h>

pager_t *pager_open(const char *filename)
{
	int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	if (fd == -1) {
		perror("Unable to open db '%s': ");
		exit(EXIT_FAILURE);
	}

	off_t file_length = lseek(fd, 0, SEEK_END);

	pager_t *pager = malloc(sizeof(pager_t));
	pager->file_desc = fd;
	pager->file_length = file_length;
	pager->num_pages = (file_length / PAGE_SIZE);

	if (file_length % PAGE_SIZE != 0) {
		printf("Error: Database file '%s' is corrupt.\n", filename);
		exit(EXIT_FAILURE);
	}

	for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
		pager->pages[i] = NULL;
	}

	return pager;
}

void pager_flush(pager_t *pager, uint32_t page_num)
{
	if (pager->pages[page_num] == NULL) {
		printf("Tried to flush null page\n");
		exit(EXIT_FAILURE);
	}

	off_t offset = lseek(pager->file_desc, page_num * PAGE_SIZE, SEEK_SET);

	if (offset == -1) {
		perror("Error while flushing database: ");
		exit(EXIT_FAILURE);
	}

	ssize_t bytes = write(pager->file_desc, pager->pages[page_num], PAGE_SIZE);

	if (bytes == -1) {
		perror("Error while writing to database: ");
		exit(EXIT_FAILURE);
	}
}

void *pager_get_page(pager_t *pager, uint32_t page_num)
{
	if (page_num > TABLE_MAX_PAGES) {
		printf("Tried to fetch page number out of bounds (%d > %d)", page_num,
			   TABLE_MAX_PAGES);
		exit(EXIT_FAILURE);
	}

	if (pager->pages[page_num] == NULL) {
		// cache miss
		void *page = malloc(PAGE_SIZE);
		uint32_t num_pages = pager->file_length / PAGE_SIZE;

		if (pager->file_length % PAGE_SIZE) {
			num_pages += 1;
		}

		if (page_num <= num_pages) {
			lseek(pager->file_desc, page_num * PAGE_SIZE, SEEK_SET);
			ssize_t bytes = read(pager->file_desc, page, PAGE_SIZE);
			if (bytes == -1) {
				perror("Error reading database: ");
				exit(EXIT_FAILURE);
			}
		}

		pager->pages[page_num] = page;

		if (page_num >= pager->num_pages) {
			pager->num_pages = page_num + 1;
		}
	}

	return pager->pages[page_num];
}