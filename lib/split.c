#include <stdio.h>
#include <stdlib.h>

int isChrs(char chr, char *chrs)
{
	while (*chrs)
		if (chr == *chrs++)
			return 1;
	return 0;
}

char *skip(char *str, char *chrs)
{
	while (isChrs(*str, chrs))
		str++;
	return str;
}

int wdCount(char *str, char *delim)
{
  int nwords;

	nwords = 0;
  while (*str)
	{
		str = skip(str, delim);
		if (*str)
			nwords++;
		while (*str && !isChrs(*str, delim))
			str++;
	}
	return nwords;
}

int linefCount(FILE *file, size_t bufsize)
{
  char *line;
	size_t offset;
  int nlines;
	int nbytes;

  line = 0;
	offset = ftell(file);
  nlines = -1;
	nbytes = 1;
  while (nbytes > 0)
	{
		nbytes = getline(&line, &bufsize, file);
		line = realloc(line, 0);
    nlines++;
	}
	fseek(file, offset, SEEK_SET);
  return nlines;
}

int wdLinefCount(FILE *file, char *delim, size_t bufsize)
{
	int offset;
	int nwords;
	char *line;

	offset = ftell(file);
	line = 0;
	getline(&line, &bufsize, file);
	nwords = wdCount(line, delim);
	while (1)
	{
		line = realloc(line, 0);
		if (getline(&line, &bufsize, file) <= 0)
			break;
		if (wdCount(line, delim) != nwords)
		{
			printf("There are lines with different sizes\n");
			line = realloc(line, 0);
			return 0;
		}
	}
	line = realloc(line, 0);
	fseek(file, offset, SEEK_SET);
	return nwords;
}

char *strnCpy(char *dest, char *src, unsigned int n)
{
	char *begin;

	if (!dest || !src)
		return 0;
	begin = dest;
	while (*src && n--)
		*dest++ = *src++;
	*dest = 0;
	return begin;
}

char *strnDup(char *str, unsigned int n)
{
	char *new;

	new = malloc(n+1);
	if (!new || !str)
		return 0;
	return strnCpy(new, str, n);
}

char **split(char *str, char *delim)
{
	char **arr;
	char *end;
	int i;

	arr = malloc((wdCount(str, delim)+1) * sizeof(char*));
	if (!arr || !str || !delim)
		return 0;
	end = str = skip(str, delim);
	i = 0;
	while (*str)
	{
		while (*end && !isChrs(*end, delim))
			end++;
		arr[i++] = strnDup(str, end-str);
		if (!arr[i-1])
			i--;
		str = end = skip(end, delim);
	}
	arr[i] = 0;
	if (!i)
	{
		free(arr);
		arr = 0;
	}
	return arr;
}

void freeSplited(char ***splited)
{
	char **p;

	if (!*splited)
		return;
	p = *splited;
	while (*p)
	{
		*p = realloc(*p, 0);
		p++;
	}
	*splited = realloc(*splited, 0);
	return;
}
