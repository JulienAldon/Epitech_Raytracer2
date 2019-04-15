/*
** rotate.c for rt in /home/theo.ferreira/graphical/raytracer1/src
** 
** Made by Théo Ferreira
** Login   <theo.ferreira@epitech.net>
** 
** Started on  Fri Feb 24 16:09:39 2017 Théo Ferreira
** Last update Tue May 23 17:08:34 2017 Théo Ferreira
*/

#include "raytracer.h"

float		get_light_coef(sfVector3f light_vector, sfVector3f normal_vector)
{
  float		coef;
  sfVector3f	n;
  sfVector3f	l;

  n = normal_vector;
  l = light_vector;
  if ((sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2)) *
       (sqrt(pow(l.x, 2) + pow(l.y, 2) + pow(l.z, 2)))) != 0)
    coef = (n.x * l.x + n.y * l.y + n.z * l.z) /
      (sqrt(pow(n.x, 2) + pow(n.y, 2) + pow(n.z, 2)) *
       (sqrt(pow(l.x, 2) + pow(l.y, 2) + pow(l.z, 2))));
  else
    return (0);
  if (coef >= 0)
    return (coef);
  return (0);
}
