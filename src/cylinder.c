/*
** cylinder.c for rt in /home/theo.ferreira/graphical/raytracer1/src
** 
** Made by Théo Ferreira
** Login   <theo.ferreira@epitech.net>
** 
** Started on  Fri Feb 24 16:09:39 2017 Théo Ferreira
** Last update Tue May 23 17:08:25 2017 Théo Ferreira
*/

#include "raytracer.h"

float		result_cyl(sfVector3f equa, float delta)
{
  sfVector2f	k;
  float		inter;

  if (delta == 0)
    {
      if (equa.x == 0)
	return (-1.0);
      inter = (-equa.y) / (2 * equa.x);
      if (inter < 0)
	return (-1.0);
      return (inter);
    }
  if (delta > 0)
    {
      if (equa.x == 0)
	return (-1.0);
      k.x = (-equa.y - sqrt(delta)) / (2 * equa.x);
      k.y = (-equa.y + sqrt(delta)) / (2 * equa.x);
      if (k.x > 0)
	return (k.x);
      if (k.x < 0 && k.y > 0)
	return (k.y);
      return (-1.0);
    }
  return (-1.0);
}

float		intersect_cylinder(sfVector3f eye_pos, sfVector3f dir_vector,
				   float radius)
{
  float		inter;
  sfVector3f	equa;
  float		delta;

  equa.x = powf(dir_vector.x, 2) + powf(dir_vector.y, 2);
  equa.y = 2 * (eye_pos.x * dir_vector.x + eye_pos.y * dir_vector.y);
  equa.z = powf(eye_pos.x, 2) + powf(eye_pos.y, 2) - powf(radius, 2);
  delta = powf(equa.y, 2) - (4 * equa.x * equa.z);
  if (delta < 0)
    return (-1.0);
  inter = result_cyl(equa, delta);
  return (inter);
}

sfVector3f	get_normal_cylinder(sfVector3f intersection_point)
{
  intersection_point.z = 0;
  return (intersection_point);
}
