/*
** main.c for  in /home/james.faure/wolf3d
**
** Made by Jamie Faure
** Login   <james.faure@epitech.net>
**
** Started on  Tue Dec 27 22:43:39 2016 Jamie Faure
** Last update Thu Jun  1 19:34:50 2017 Théo Ferreira
*/

#include "raytracer.h"

sfRenderWindow		*create_window(char *name, int width, int height)
{
  sfRenderWindow	*window;
  sfVideoMode		mode;

  mode.width = width;
  mode.height = height;
  mode.bitsPerPixel = 32;
  window = sfRenderWindow_create(mode, name, sfResize | sfClose, NULL);
  if (!window)
    exit(84);
  return (window);
}

t_my_framebuffer	*create_framebuffer(int width, int height)
{
  int			i;
  t_my_framebuffer	*f;

  f = malloc(sizeof(*f));
  f->pixels = malloc(width * height * 4 * sizeof(*f->pixels));
  f->width = width;
  f->height = height;
  if (!f->pixels)
    exit(84);
  i = 0;
  while (i < width * height * 4)
    f->pixels[i++] = 0;
  return (f);
}

int			main(int ac, char **av)
{
  sfRenderWindow	*window;
  sfTexture		*t;
  sfSprite		*sprite;
  t_my_framebuffer     	*f;
  sfEvent		event;

  if (ac != 2)
    return (!!write(1, "No config file !\n", 17));
  f = create_framebuffer(SCREEN_WIDTH, SCREEN_HEIGHT);
  raytrace_scene(f, av[1]);
  window = create_window("SFML raytrace", SCREEN_WIDTH, SCREEN_HEIGHT);
  t = sfTexture_create(SCREEN_WIDTH, SCREEN_HEIGHT);
  sfTexture_updateFromPixels(t, f->pixels, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  sprite = sfSprite_create();
  sfSprite_setTexture(sprite, t, sfTrue);
  sfRenderWindow_drawSprite(window, sprite, NULL);
  sfRenderWindow_display(window);
  sfRenderWindow_pollEvent(window, &event);
  while ((event.type != sfEvtKeyPressed || event.key.code != sfKeyEscape))
    sfRenderWindow_pollEvent(window, &event);
  return (0);
}
