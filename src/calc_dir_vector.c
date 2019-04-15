/*
** calc_dir_vector.c for rt in /home/theo.ferreira/graphical/raytracer1/src
** 
** Made by Théo Ferreira
** Login   <theo.ferreira@epitech.net>
** 
** Started on  Fri Feb 24 16:05:52 2017 Théo Ferreira
** Last update Tue May 23 17:08:44 2017 Théo Ferreira
*/

#include "raytracer.h"

sfVector3f	calc_dir_vector(float dist_to_plane, sfVector2i screen_size,
				sfVector2i screen_pos)
{
  sfVector3f	dir;

  dir.x = dist_to_plane;
  dir.y = (screen_size.x / 2) - screen_pos.x;
  dir.z = (screen_size.y / 2) - screen_pos.y;
  return (dir);
}
