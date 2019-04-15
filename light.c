/*
** trace.c for  in /home/jamie/raytracer1
**
** Made by James Faure
** Login   <james.faure@epitech.eu>
**
** Started on  Fri Mar 10 11:12:10 2017 James Faure
** Last update Sun May 28 18:13:50 2017 Théo Ferreira
*/

#include "raytracer.h"

int		nb_of_lights(t_lights *light)
{
  t_lights	*li;
  int		i;

  li = light;
  i = 0;
  while (li)
    {
      li = li->next;
      i += 1;
    }
  return (i);
}

sfColor	set_light(sfColor color, float light_coef)
{
  color.r *= light_coef;
  color.g *= light_coef;
  color.b *= light_coef;
  color.r = (color.r + 0.5 * 255 * light_coef)
    > 255 ? 255 : color.r + 0.5 * 255 * light_coef;
  color.g = (color.g + 0.5 * 255 * light_coef) >
    255 ? 255 : color.g + 0.5 * 255 * light_coef;
  color.b = (color.b + 0.5 * 255 * light_coef)
    > 255 ? 255 : color.b + 0.5 * 255 * light_coef;
  return (color);
}

int		nb_lights(t_lights *light)
{
  int		i;
  t_lights	*current;

  current = light;
  i = 0;
  while (current)
    {
      i += 1;
      current = current->next;
    }
  return (i);
}
