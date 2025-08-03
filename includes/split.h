#include <stdio.h>

int		wdCount(char *str, char *delim);
int		linefCount(FILE *file, size_t bufsize);
int		wdLinefCount(FILE *file, char *delim, size_t bufsize);
char	**split(char *str, char *delim);
void	freeSplited(char ***splited);

