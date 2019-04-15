/*
** rotate.c for rt in /home/theo.ferreira/graphical/raytracer1/src
** 
** Made by Théo Ferreira
** Login   <theo.ferreira@epitech.net>
** 
** Started on  Fri Feb 24 16:09:39 2017 Théo Ferreira
** Last update Tue May 23 17:08:53 2017 Théo Ferreira
*/

#include "raytracer.h"

sfVector3f	rotate_x(sfVector3f to_rotate, float angle)
{
  sfVector3f	rot;

  angle = angle * M_PI / 180;
  rot.x = to_rotate.x;
  rot.y = (cos(angle)) * to_rotate.y + to_rotate.z * (-sin(angle));
  rot.z = (sin(angle)) * to_rotate.y + to_rotate.z * (cos(angle));
  return (rot);
}

sfVector3f	rotate_y(sfVector3f to_rotate, float angle)
{
  sfVector3f	rot;

  angle = angle * M_PI / 180;
  rot.x = to_rotate.x * (cos(angle)) + (sin(angle)) * to_rotate.z;
  rot.y = to_rotate.y;
  rot.z = to_rotate.x * (-sin(angle)) + to_rotate.z * (cos(angle));
  return (rot);
}

sfVector3f	rotate_z(sfVector3f to_rotate, float angle)
{
  sfVector3f	rot;

  angle = angle * M_PI / 180;
  rot.x = to_rotate.x * (cos(angle)) + to_rotate.y * (-sin(angle));
  rot.y = to_rotate.x * (sin(angle)) + to_rotate.y * (cos(angle));
  rot.z = to_rotate.z;
  return (rot);
}

sfVector3f	rotate_xyz(sfVector3f to_rotate, sfVector3f angles)
{
  sfVector3f	rot;

  rot = rotate_x(to_rotate, angles.x);
  rot = rotate_y(rot, angles.y);
  rot = rotate_z(rot, angles.z);
  return (rot);
}

sfVector3f	rotate_zyx(sfVector3f to_rotate, sfVector3f angles)
{
  sfVector3f	rot;

  rot = rotate_z(to_rotate, angles.z);
  rot = rotate_y(rot, angles.y);
  rot = rotate_x(rot, angles.x);
  return (rot);
}
