/*
** objects.h for  in /home/james.faure/raytracer1
**
** Made by Jamie Faure
** Login   <james.faure@epitech.net>
**
** Started on  Thu Feb  9 23:50:51 2017 Jamie Faure
** Last update Sun May 28 15:32:05 2017 Varé Paul
*/

/*
** ||X - C||^2 = r^2 (line: X = O + dL)
*/
typedef struct	s_sphere
{
  sfVector3f	c;
  unsigned int	r;
}		t_sphere;

/*
** N . (X - P) = 0
*/
typedef struct	s_plane
{
  sfVector3f	n;
  sfVector3f	p;
}		t_plane;

typedef struct	s_cylinder
{
  sfVector2f	c;
  unsigned int	r;
}		t_cylinder;

typedef struct	s_cone
{
}		t_cone;
