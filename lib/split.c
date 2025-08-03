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
	char *begin;
  int nwords;

	nwords = 0;
	begin = str = skip(str, delim);
  while (*str)
    if (isChrs(*str++, delim))
    {   
      nwords++;
			str = skip(str, delim);
    }   
	if (str > begin && !isChrs(*(str-1), delim))
		nwords++;
	return nwords;
}

int linefCount(FILE *file, size_t bufsize)
{
  char *line;
	size_t offset;
  int nlines;

  line = 0;
	offset = ftell(file);
  nlines = 0;
  while (getline(&line, &bufsize, file) > 0)
	{
		line = realloc(line, 0);
    nlines++;
	}
	fseek(file, offset, SEEK_SET);
  return nlines;
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
