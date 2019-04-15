/*
** exec.c for  in /home/james.faure/PSU_2017_minishell1
**
** Made by Jamie Faure
** Login   <james.faure@epitech.net>
**
** Started on  Fri Jan  6 19:19:17 2017 Jamie Faure
** Last update Sun May 28 16:08:08 2017 Varé Paul
*/

#include "mystring.h"

int	my_strlen(const char *str)
{
  int	r;

  r = 0;
  while (str[r])
    ++r;
  return (r);
}

int	my_strcmp(const char *a, const char *b)
{
  int	ret;

  ret = !a || !b ? a != b : !*a ? !*b ?  0 : -1 : !*b ? 1 :
    *a - *b ? *a - *b : my_strcmp(++a, ++b);
  return (ret);
}

char	*my_strcat(const char *str, const char *ap)
{
  char	*r;
  char	*p;

  p = (r = malloc(my_strlen(str) + my_strlen(ap) + 1));
  if (str)
    while (*str)
      *p++ = *str++;
  if (ap)
    while (*ap)
      *p++ = *ap++;
  *p = 0;
  return (r);
}

char	*my_strdup(const char *str)
{
  char	*r;
  char	*c;

  if (!str)
    return (0);
  r = (c = malloc(my_strlen(str) + 1));
  while (*str)
    *c++ = *str++;
  *c = 0;
  return (r);
}

char	*my_strndup(const char *str, int n)
{
  char	*r;
  char	*c;

  if (!str)
    return (0);
  r = (c = malloc(n + 1));
  while (*str && n--)
    *c++ = *str++;
  *c = 0;
  return (r);
}
