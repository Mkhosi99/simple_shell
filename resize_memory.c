#include "shell.h"

/**
 * set_block_memory - function includes memory with a constant type
 * @f: points to the memory area
 * @g: bytes to include *f with
 * @h: the number of bytes to be filled
 * Return: will (f) pointer to memmory area f
 */

char *set_block_memory(char *f, char g, unsigned int h)
{
	unsigned int x;

	for (x = 0; x < h; x++)
		f[x] = g;
	return (f);
}

/**
 * free_the_memory - function frees string of strings
 * @ff: indicates the string of the strings
 */
void free_the_memory(char **ff)
{
	char **m = ff;

	if (!ff)
		return;
	while (*ff)
		free(*ff++);
	free(m);
}

/**
 * resize_mem - function will reallocate a block of memory
 * @pter: points to prev mem allocated block
 * @prev_size: the byte size of the prev block
 * @newSize: the byte size of the new block
 * Return: point to previous block
 */
void *resize_mem(void *pter, unsigned int prev_size, unsigned int newSize)
{
	char *m;

	if (!pter)
		return (malloc(newSize));
	if (!newSize)
		return (free(pter), NULL);
	if (newSize == prev_size)
		return (pter);

	m = malloc(newSize);
	if (!m)
		return (NULL);

	prev_size = prev_size < newSize ? prev_size : newSize;
	while (prev_size--)
		m[prev_size] = ((char *)pter)[prev_size];
	free(pter);
	return (m);
}
