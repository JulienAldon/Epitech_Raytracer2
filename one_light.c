/*
** one_light.c for rt2 in /home/theo.ferreira/graphical/raytracer2
**
** Made by Théo Ferreira
** Login   <theo.ferreira@epitech.net>
**
** Started on  Wed May 24 13:43:33 2017 Théo Ferreira
** Last update Thu Jun  1 19:51:16 2017 Théo Ferreira
*/

#include "raytracer.h"

sfVector3f	reverse(sfVector3f vector)
{
  sfVector3f	ret;

  ret.x = -vector.x;
  ret.y = -vector.y;
  ret.z = -vector.z;
  return (ret);
}

sfColor	damier(sfColor color, sfVector3f inter, t_shape *shapes, int len)
{
  int	x;
  int	y;
  int	dam;

  if (shapes->type == T_PLANE && len > 0)
    {
      x = (int) abs(inter.x < 0 ? inter.x - len : inter.x);
      y = (int) abs(inter.y < 0 ? inter.y - len : inter.y);
      dam = (x % (len * 2) >= len && y % (len * 2) >= len) ||
	(x % (len * 2) < len && y % (len * 2) < len) ? 1 : 0;
      color.r = dam == 1 ? color.r : 255 - color.r;
      color.g = dam == 1 ? color.g : 255 - color.g;
      color.b = dam == 1 ? color.b : 255 - color.b;
    }
  return (color);
}

sfColor		one_light(t_shadow sha, sfVector3f light,
			  sfVector3f inter, sfVector3f normal)
{
  sfColor	color;
  float		coef;
  sfVector3f	vec;
  int		is_shadow;

  vec = translate(light, reverse(inter));
  color = sha.shapes->color;
  color = sha.shapes->damier ?
    damier(sha.shapes->color, inter, sha.shapes, sha.shapes->damier) :
    sha.shapes->color;
  is_shadow = 1;
  if (is_shadow == 1)
    {
      coef = shadow(inter, light, sha.full, vec) == 0 ?
	get_light_coef(vec, normal) : 0;
    }
  else
    coef = get_light_coef(vec, normal);
  return (set_light(color, coef));
}
