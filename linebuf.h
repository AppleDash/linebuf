#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linebuffer {
	char *buffer;
	int len;
	int maxlen;
} linebuf_t;

/**
 * Create a new line buffer
 */
linebuf_t *linebuf_new();

/**
 * Destroy a line buffer (free it and its contents from memory)
 */
void linebuf_destroy(linebuf_t *linebuf);

/**
 * Append arbitrary data to a line buffer
 * This data may contain anywhere from less than a single full line
 * to multiple lines ending in another partial line.
 */
void linebuf_append(linebuf_t *linebuf, char *data, int data_len);

/**
 * Pop a line from a line buffer, if it has one or more.
 */
bool linebuf_pop(linebuf_t *linebuf, char **outline);
