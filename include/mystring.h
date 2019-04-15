/*
** string.h for  in /home/jamie/PSU_2016_minishell2
**
** Made by James Faure
** Login   <james.faure@epitech.eu>
**
** Started on  Thu Mar 16 13:10:08 2017 James Faure
** Last update Sun May 28 15:32:32 2017 Varé Paul
*/

#ifndef STRING_H_
# define STRING_H_

#include <malloc.h>
#include <unistd.h>

int	my_strlen(const char *);
int	my_strcmp(const char *, const char *);
char	*my_strcat(const char *str, const char *ap);
int	my_puts(char *s);
int	my_perror(char *s);
char	*my_strstr(char *needle, char *haystack);
char	*my_strdup(const char *str);
char	*my_strndup(const char *str, int n);

#endif
