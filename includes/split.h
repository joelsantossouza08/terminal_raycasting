#include <stdio.h>

int		wdCount(char *str, char *delim);
int		linefCount(FILE *file, size_t bufsize);
char	**split(char *str, char *delim);
