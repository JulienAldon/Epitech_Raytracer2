/*
** trace.c for  in /home/jamie/raytracer1
**
** Made by James Faure
** Login   <james.faure@epitech.eu>
**
** Started on  Fri Mar 10 11:12:10 2017 James Faure
** Last update Thu Jun  1 14:51:42 2017 Théo Ferreira
*/

#include "raytracer.h"

t_3f	add_color(t_3f a, sfColor b)
{
  a.x = a.x + b.r;
  a.y = a.y + b.g;
  a.z = a.z + b.b;
  return (a);
}

sfColor		div_color(t_3f a, int div)
{
  sfColor	ret;

  ret.r = a.x / div;
  ret.g = a.y / div;
  ret.b = a.z / div;
  ret.a = 255;
  return (ret);
}

sfColor	putting_ref(t_shadow sha, sfColor color, sfColor ref)
{
  float	temp;

  temp = ref.r * sha.shapes->reflection + color.r *
    (1 - sha.shapes->reflection);
  color.r = temp > 255 ? 255 : temp;
  temp = ref.g * sha.shapes->reflection + color.g *
    (1 - sha.shapes->reflection);
  color.g = temp > 255 ? 255 : temp;
  temp = ref.b * sha.shapes->reflection + color.b *
    (1 - sha.shapes->reflection);
  color.b = temp > 255 ? 255 : temp;
  return (color);
}

sfColor		calcul_color(t_shadow sha, t_lights *light,
			     t_3f dir, float save)
{
  t_calcul	c;

  if ((c.i = nb_lights(light)) == 0)
    return (sha.shapes->color);
  c.tmp = mk_vector3f(0, 0, 0);
  c.path = light;
  c.pos_eye = translate(sha.pos, reverse(sha.shapes->translate));
  dir = rotate_xyz(dir, reverse(sha.shapes->rotate));
  c.pos_eye = rotate_xyz(c.pos_eye, reverse(sha.shapes->rotate));
  c.inter = inters(c.pos_eye, dir, save);
  c.normal = getting_normal(sha, c.inter, c.pos_eye);
  c.inter = translate(c.inter, sha.shapes->translate);
  c.normal = rotate_xyz(c.normal, sha.shapes->rotate);
  while (c.path)
    {
      c.color = one_light(sha, c.path->light, c.inter, c.normal);
      c.ref = reflexion(c.inter, c.normal, dir, light);
      c.color = putting_ref(sha, c.color, c.ref);
      c.tmp = add_color(c.tmp, c.color);
      c.path = c.path->next;
    }
  return (div_color(c.tmp, c.i));
}
