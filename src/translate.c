/*
** translate.c for rt in /home/theo.ferreira/graphical/raytracer1/src
** 
** Made by Théo Ferreira
** Login   <theo.ferreira@epitech.net>
** 
** Started on  Fri Feb 24 16:07:58 2017 Théo Ferreira
** Last update Tue May 23 17:09:01 2017 Théo Ferreira
*/

#include "raytracer.h"

sfVector3f	translate(sfVector3f to_translate, sfVector3f translations)
{
  sfVector3f	trans;

  trans.x = to_translate.x + translations.x;
  trans.y = to_translate.y + translations.y;
  trans.z = to_translate.z + translations.z;
  return (trans);
}
