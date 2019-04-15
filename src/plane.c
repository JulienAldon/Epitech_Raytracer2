/*
** plane.c for  in /home/james.faure/raytracer1/src
** 
** Made by Jamie Faure
** Login   <james.faure@epitech.net>
** 
** Started on  Mon Feb 20 05:14:04 2017 Jamie Faure
** Last update Fri Mar 10 16:08:24 2017 James Faure
*/

#include <SFML/Graphics.h>

float	intersect_plane(sfVector3f eye_pos, sfVector3f dir_vector)
{
  float	dist;

  if (!dir_vector.z)
    return (-1);
  dist = -eye_pos.z / dir_vector.z;
  return (dist >= 0 ? dist : -1);
}

sfVector3f	get_normal_plane(int upward)
{
  sfVector3f	r;

  r.x = 0;
  r.y = 0;
  r.z = upward == 1 ? 100 : -100;
  return (r);
}
