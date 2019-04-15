/*
** get_next_line.h for  in /home/james.faure/CPE_2017_getnextline
** 
** Made by Jamie Faure
** Login   <james.faure@epitech.net>
** 
** Started on  Tue Jan  3 14:24:04 2017 Jamie Faure
** Last update Tue Jan 17 20:58:41 2017 Jamie Faure
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

#ifndef READ_SIZE
# define READ_SIZE 100
#endif

char	*my_dup(char *, int);
char	*main_work(const int fd, char *buf, int len);
char	*get_next_line(const int fd);

# endif
