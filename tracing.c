/*
** trace.c for  in /home/jamie/raytracer1
**
** Made by James Faure
** Login   <james.faure@epitech.eu>
**
** Started on  Fri Mar 10 11:12:10 2017 James Faure
** Last update Thu Jun  1 14:54:12 2017 Théo Ferreira
*/

#include "raytracer.h"

sfVector3f	inters(sfVector3f pos, sfVector3f dir, float dis)
{
  sfVector3f	r;

  r.x = pos.x + dir.x * dis;
  r.y = pos.y + dir.y * dis;
  r.z = pos.z + dir.z * dis;
  return (r);
}

float		calc_dist(t_3f dir, t_shape *shapes)
{
  t_3f		pos_eye;
  t_3f		tr;
  t_3f		rot;
  float		f;

  pos_eye = eye_pos;
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

sfVector3f	getting_normal(t_shadow sha, sfVector3f inter, sfVector3f pos_eye)
{
  sfVector3f	ret;

  ret = sha.shapes->type == T_SPHERE ? get_normal_sphere(inter) :
    sha.shapes->type == T_CYLINDER ? get_normal_cylinder(inter) :
    sha.shapes->type == T_CONE ? get_normal_cone(inter, sha.shapes->radius) :
    get_normal_plane(pos_eye.z < 0 ? 0 : 1);
  return (ret);
}

sfColor		shapes_trace(t_3f dir, t_lights *light, t_shape *shapes)
{
  float		save;
  float		tmp;
  t_shadow	sha;

  sha.full = shapes;
  save = calc_dist(dir, shapes);
  sha.shapes = save < 0 ? NULL : shapes;
  while ((shapes = shapes->next))
    {
      tmp = calc_dist(dir, shapes);
      if (tmp >= 0 && (tmp < save || save < 0))
	{
	  save = tmp;
	  sha.shapes = shapes;
	}
    }
  if (!sha.shapes)
    return (sfBlack);
  sha.pos = eye_pos;
  return (calcul_color(sha, light, dir, save));
}
