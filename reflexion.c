/*
** reflexion.c for  in /home/paul.vare/semestre2/MUL/norm
** 
** Made by Varé Paul
** Login   <paul.vare@epitech.net>
** 
** Started on  Sun May 28 19:15:44 2017 Varé Paul
** Last update Thu Jun  1 14:57:25 2017 Théo Ferreira
*/

#include "raytracer.h"

sfColor		calcul_color_ref(t_shadow sha, t_lights *light,
				 t_3f dir, float save)
{
  int		i;
  t_lights	*path;
  t_3f		tmp;
  sfVector3f	normal;
  sfVector3f	inter;

  if ((i = nb_lights(light)) == 0)
    return (sha.shapes->color);
  tmp = mk_vector3f(0, 0, 0);
  path = light;
  sha.pos = translate(sha.pos, reverse(sha.shapes->translate));
  dir = rotate_xyz(dir, reverse(sha.shapes->rotate));
  sha.pos = rotate_xyz(sha.pos, reverse(sha.shapes->rotate));
  inter = inters(sha.pos, dir, save);
  normal = getting_normal(sha, inter, sha.pos);
  inter = translate(inter, sha.shapes->translate);
  normal = rotate_xyz(normal, sha.shapes->rotate);
  while (path)
    {
      tmp = add_color(tmp, one_light(sha, path->light, inter, normal));
      path = path->next;
    }
  return (div_color(tmp, i));
}

float	calc_dist_ref(t_3f dir, t_shape *shapes, t_3f pos_eye)
{
  t_3f	tr;
  t_3f	rot;
  float	f;

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

sfColor		shapes_trace_ref(t_3f dir, t_lights *light,
				 t_shape *shapes, t_3f pos_eye)
{
  float		save;
  float		tmp;
  t_shadow	sha;

  sha.full = shapes;
  save = calc_dist_ref(dir, shapes, pos_eye);
  sha.shapes = save < 0 ? NULL : shapes;
  while ((shapes = shapes->next))
    {
      tmp = calc_dist_ref(dir, shapes, pos_eye);
      if (tmp >= 0 && (tmp < save || save < 0))
        {
          save = tmp;
          sha.shapes = shapes;
        }
    }
  if (!sha.shapes)
    return (sfBlack);
  sha.pos = pos_eye;
  return (calcul_color_ref(sha, light, dir, save));
}

float	get_scalaire(sfVector3f light_vector, sfVector3f normal_vector)
{
  float	norm_light;
  float	norm_normal;
  float	dot;

  norm_light = pow(light_vector.x, 2) + pow(light_vector.y, 2);
  norm_light = sqrt(norm_light + pow(light_vector.z, 2));
  norm_normal = pow(normal_vector.x, 2) + pow(normal_vector.y, 2);
  norm_normal = sqrt(norm_normal + pow(normal_vector.z, 2));
  dot = light_vector.x * normal_vector.x + light_vector.y * normal_vector.y;
  dot = dot + light_vector.z * normal_vector.z;
  if (norm_normal == 0)
    return (0);
  return (dot);
}

sfColor		reflexion(t_3f inter, t_3f normal, t_3f dir, t_lights *light)
{
  float		scal;
  float		norm_normal;
  float		norm_light;

  inter.x -= dir.x * 0.001;
  inter.y -= dir.y * 0.001;
  inter.z -= dir.z * 0.001;
  norm_light = pow(normal.x, 2) + pow(normal.y, 2);
  norm_light = sqrt(norm_light + pow(normal.z, 2));
  norm_normal = pow(dir.x, 2) + pow(dir.y, 2);
  norm_normal = sqrt(norm_normal + pow(dir.z, 2));
  dir.x = dir.x / norm_normal;
  dir.y = dir.y / norm_normal;
  dir.z = dir.z / norm_normal;
  normal.x = normal.x / norm_light;
  normal.y = normal.y / norm_light;
  normal.z = normal.z / norm_light;
  scal = get_scalaire(normal, dir);
  normal.x = normal.x * scal * (-2);
  normal.y = normal.y * scal * (-2);
  normal.z = normal.z * scal * (-2);
  normal.x += dir.x;
  normal.y += dir.y;
  normal.z += dir.z;
  return (shapes_trace_ref(normal, light, shapes, inter));
}
