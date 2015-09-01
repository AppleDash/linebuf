#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linebuffer {
	char *buffer;
	int len;
	int maxlen;
} linebuf_t;

linebuf_t *linebuf_new();
void linebuf_destroy(linebuf_t *linebuf);

void linebuf_append(linebuf_t *linebuf, char *data, int data_len);
bool linebuf_pop(linebuf_t *linebuf, char **outline);