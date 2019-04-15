/*
** trace.c for  in /home/jamie/raytracer1
**
** Made by James Faure
** Login   <james.faure@epitech.eu>
**
** Started on  Fri Mar 10 11:12:10 2017 James Faure
** Last update Sun May 28 16:14:31 2017 Varé Paul
*/

#include "raytracer.h"
#include <pthread.h>

float	circle_plane(sfVector3f inter, float f, float radius)
{
  if ((powf(inter.x, 2) + powf(inter.y, 2)) < powf(radius, 2))
    return (f);
  return (-1.0);
}

float	rectangle_plane(sfVector3f inter, float f, t_shape *shapes)
{
  if (inter.x < shapes->translate.x + shapes->min_max[0].x
      || inter.y < shapes->translate.y + shapes->min_max[0].y
      || inter.x > shapes->translate.x + shapes->min_max[1].x
      || inter.y > shapes->translate.y + shapes->min_max[1].y)
    return (-1.0);
  return (f);
}

float	limit_plane(t_shape *shapes, float f, sfVector3f inter)
{
  if (shapes->min_max[1].z == -1 && shapes->min_max[0].z == -1 &&
      shapes->min_max[1].y == -1 && shapes->min_max[0].y == -1 &&
      shapes->min_max[1].x == -1 && shapes->min_max[0].x >= 0)
    f = circle_plane(inter, f, shapes->min_max[0].x);
  else if (shapes->min_max[1].z == -1 && shapes->min_max[0].z == -1 &&
	   shapes->min_max[1].y != -1 && shapes->min_max[0].y != -1 &&
	   shapes->min_max[1].x != -1 && shapes->min_max[0].x != -1)
    f = rectangle_plane(inter, f, shapes);
  return (f);
}

float		limitation(t_shape *shapes, float f,
			   sfVector3f pos_eye, sfVector3f dir)
{
  sfVector3f	inter;

  inter = inters(pos_eye, dir, f);
  if (shapes->type == T_CYLINDER || shapes->type == T_CONE ||
      shapes->type == T_SPHERE)
    {
      if (shapes->min_max[1].z != -1 && shapes->min_max[0].z != -1 &&
	  shapes->min_max[1].y == -1 && shapes->min_max[0].y == -1 &&
	  shapes->min_max[1].x == -1 && shapes->min_max[0].x == -1)
	{
	  if (inter.z > shapes->translate.z + shapes->min_max[1].z ||
	      inter.z < shapes->translate.z + shapes->min_max[0].z)
	    return (-1.0);
	}
    }
  else if (shapes->type == T_PLANE)
    f = limit_plane(shapes, f, inter);
  return (f);
}
