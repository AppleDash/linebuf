/*
 * This file is part of linebuf.
 * 
 * linebuf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * linebuf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with linebuf.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "linebuf.h"

linebuf_t *linebuf_new() {
	linebuf_t *linebuf;

	linebuf = (linebuf_t *)calloc(1, sizeof(linebuf_t));

	linebuf->len = 0;
	linebuf->maxlen = 4096;
	linebuf->buffer = (char *)calloc(1, linebuf->maxlen);

	return linebuf;
}

void linebuf_destroy(linebuf_t *linebuf) {
	if (linebuf) {
		if (linebuf->buffer) {
			free(linebuf->buffer);
		}

		free(linebuf);
	}
}

void linebuf_append(linebuf_t *linebuf, char *data, int data_len) {
	int needed_size;

	needed_size = linebuf->len + data_len;

	if (needed_size > linebuf->maxlen) {
		linebuf->buffer = (char *)realloc(linebuf->buffer, needed_size);
		linebuf->maxlen = needed_size;
	}


	memcpy(linebuf->buffer + linebuf->len, data, data_len);
	linebuf->len = needed_size;
}

bool linebuf_pop(linebuf_t *linebuf, char **outline) {
	char *newline_pos = (char *)memchr(linebuf->buffer, '\n', linebuf->len);
	int line_len;

	if (newline_pos != NULL) {
		line_len = (newline_pos - linebuf->buffer);
		*outline = (char *)calloc(1, line_len + 1);
		strncpy(*outline, linebuf->buffer, line_len);
		memmove(linebuf->buffer, newline_pos + 1, linebuf->len - line_len);
		linebuf->len -= line_len;
		return true;
	}

	return false;
}