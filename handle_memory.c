#include "shell.h"

/**
 * makefree - the function frees pointer and NULLs address
 * @pter: this will address pointer to free
 * Return: will return 1 if free or 0 if not
 */
int makefree(void **pter)
{
	if (pter && *pter)
	{
		free(*pter);
		*pter = NULL;
		return (1);
	}
	return (0);
}
