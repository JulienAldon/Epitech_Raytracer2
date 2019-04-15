/*
** ombre.c for raytracer2 in /home/julien.aldon/raytracer2
**
** Made by Julien Aldon
** Login   <julien.aldon@epitech.net>
**
** Started on  Tue May 23 15:30:09 2017 Julien Aldon
** Last update Wed May 31 18:10:34 2017 Théo Ferreira
*/

#include "raytracer.h"

float	calc_dist_inter(t_3f dir, t_shape *shapes, t_3f inter)
{
  t_3f	pos_eye;
  t_3f	tr;
  t_3f	rot;
  float	f;

  pos_eye = inter;
  tr = reverse(shapes->translate);
  pos_eye = translate(pos_eye, tr);
  rot = reverse(shapes->rotate);
  pos_eye = rotate_xyz(pos_eye, rot);
  dir = rotate_xyz(dir, rot);
  f = shapes->type == T_SPHERE ?
    intersect_sphere(pos_eye, dir, shapes->radius) :
    shapes->type == T_CYLINDER ?
    intersect_cylinder(pos_eye, dir, shapes->radius) :
    shapes->type == T_CONE ?
    intersect_cone(pos_eye, dir, shapes->radius) :
    intersect_plane(pos_eye, dir);
  return (limitation(shapes, f, pos_eye, dir));
}

float	trace_shadow(t_3f dir, t_3f light, t_shape *shapes, t_3f inter)
{
  float save;
  float tmp;

  (void) light;
  save = calc_dist_inter(dir, shapes, inter);
  while ((shapes = shapes->next))
    {
      tmp = calc_dist_inter(dir, shapes, inter);
      if (tmp >= 0 && (tmp < save || save < 0))
	save = tmp;
    }
  return (save);
}

int	shadow(t_3f inter, t_3f light, t_shape *shapes, t_3f vec)
{
  float	c;

  inter.x = inter.x + vec.x * 0.0001;
  inter.y = inter.y + vec.y * 0.0001;
  inter.z = inter.z + vec.z * 0.0001;
  c = trace_shadow(vec, light, shapes, inter);
  if (c < 1 && c > 0)
    return (1);
  return (0);
}
