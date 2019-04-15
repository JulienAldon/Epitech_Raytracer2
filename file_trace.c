/*
** trace.c for  in /home/jamie/raytracer1
**
** Made by James Faure
** Login   <james.faure@epitech.eu>
**
** Started on  Fri Mar 10 11:12:10 2017 James Faure
** Last update Thu Jun  1 19:34:47 2017 Théo Ferreira
*/

#include "raytracer.h"
#include <pthread.h>

void	my_put_pixel(t_my_framebuffer *framebuffer,
		     int x, int y, sfColor color)
{
  int	p;

  if (y < 0 || x < 0 || y > framebuffer->height || x > framebuffer->width)
    return ;
  p = (framebuffer->width * y + x) * 4;
  framebuffer->pixels[p++] = color.r;
  framebuffer->pixels[p++] = color.g;
  framebuffer->pixels[p++] = color.b;
  framebuffer->pixels[p] = color.a;
}

void			*thr_func(void *arg)
{
  t_arg			*a;
  sfVector3f		dir;
  sfVector2i		screen_size;
  sfColor		color;
  int			range;
  extern t_lights	*lights;

  a = (t_arg *) arg;
  range = a->screen_pos.y + a->y_range;
  screen_size.x = a->framebuffer->width;
  screen_size.y = a->framebuffer->height;
  while (++a->screen_pos.y <= range && (a->screen_pos.x = -1))
    while (++a->screen_pos.x < a->framebuffer->width)
      {
	dir = calc_dir_vector(500, screen_size, a->screen_pos);
	color = shapes_trace(dir, lights, a->h);
	my_put_pixel(a->framebuffer, a->screen_pos.x, a->screen_pos.y, color);
      }
  return (arg);
}

void			raytrace_scene(t_my_framebuffer *framebuffer,
				       const char *config_file)
{
  pthread_t		thrs[4];
  int			i;
  t_arg			a[4];
  extern t_shape	*shapes;
  extern FILE		*yyin;

  yyin = fopen(config_file, "r");
  if (yyparse())
    exit(1);
  fclose(yyin);
  a[0].h = shapes;
  a[0].screen_pos.y = -1;
  a[0].framebuffer = framebuffer;
  a[0].y_range = framebuffer->height / 4;
  a[3] = a[2] = a[1] = a[0];
  a[1].screen_pos.y += a[0].y_range;
  a[2].screen_pos.y += 2 * a[0].y_range;
  a[3].screen_pos.y += 3 * a[0].y_range;
  i = -1;
  while (++i < 4)
    pthread_create(thrs + i, 0, thr_func, a + i);
  while (--i >= 0)
    pthread_join(thrs[i], 0);
}
