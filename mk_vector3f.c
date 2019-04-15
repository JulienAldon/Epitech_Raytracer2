/*
** init_vector.c for  in /home/james.faure/raytracer1/src
**
** Made by Jamie Faure
** Login   <james.faure@epitech.net>
**
** Started on  Fri Feb 24 10:37:32 2017 Jamie Faure
** Last update Sun May 28 16:16:39 2017 Varé Paul
*/

#include <SFML/Graphics.h>

sfVector3f	mk_vector3f(float x, float y, float z)
{
  sfVector3f	r;

  r.x = x;
  r.y = y;
  r.z = z;
  return (r);
}
