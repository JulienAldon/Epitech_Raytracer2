/*
** raytracer1.h for  in /home/james.faure/raytracer1
** 
** Made by Jamie Faure
** Login   <james.faure@epitech.net>
** 
** Started on  Fri Feb 10 03:28:07 2017 Jamie Faure
** Last update Thu Jun  1 19:35:00 2017 Théo Ferreira
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 900
#define SQUARE(a) (a * a)
#define EQUAL(a, b) (!my_strcmp(a, b))

#include <SFML/Graphics.h>
#include <math.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>
#include "mystring.h"

typedef sfVector3f	t_3f;
typedef struct	s_my_framebuffer
{
  sfUint8	*pixels;
  int		width;
  int		height;
}		t_my_framebuffer;

typedef enum	s_types
  {
    T_SPHERE,
    T_CYLINDER,
    T_CONE,
    T_PLANE,
    T_MOBIUS,
  }		t_types;

typedef struct	s_shape t_shape;
struct		s_shape
{
  t_types	type;
  sfVector3f	translate;
  sfVector3f	rotate;
  float		radius;
  sfColor	color;
  float		transparence;
  float		brillance;
  float		reflection;
  sfVector3f	min_max[2];
  float		damier;
  float		mobius[2];
  t_shape	*next;
};

typedef struct
{
  sfVector2i		screen_pos;
  int			y_range;
  sfVector3f		eye_pos;
  t_shape		*h;
  t_my_framebuffer	*framebuffer;
}			t_arg;

typedef struct	s_shadow
{
  t_shape	*full;
  t_shape	*shapes;
  sfVector3f	pos;
}		t_shadow;

typedef struct		s_lights
{
  t_3f			light;
  sfColor		color;
  struct s_lights	*next;
}			t_lights;

typedef struct	s_calcul
{
  int		i;
  t_lights	*path;
  t_3f		tmp;
  sfVector3f	normal;
  sfVector3f	pos_eye;
  sfVector3f	inter;
  sfColor	color;
  sfColor	ref;
}		t_calcul;

extern t_shape	*shapes;
extern t_3f	eye_pos;
extern t_lights	light;

int		yyparse();
sfVector3f	mk_vector3f(float, float, float);
void		raytrace_scene(t_my_framebuffer *, const char *);
sfVector3f	calc_dir_vector(float, sfVector2i, sfVector2i);
float		intersect_cone(sfVector3f, sfVector3f, float);
sfVector3f	get_normal_cone(sfVector3f, float);
float		intersect_cylinder(sfVector3f, sfVector3f, float);
sfVector3f	get_normal_cylinder(sfVector3f);
float		get_light_coef(sfVector3f, sfVector3f);
float		intersect_plane(sfVector3f, sfVector3f);
sfVector3f	get_normal_plane(int);
sfVector3f	rotate_xyz(sfVector3f, sfVector3f);
sfVector3f	rotate_zyx(sfVector3f, sfVector3f);
float		intersect_sphere(sfVector3f, sfVector3f, float);
sfVector3f	get_normal_sphere(sfVector3f);
sfVector3f	translate(sfVector3f, sfVector3f);
void		print_shapes(t_shape *);

char		**to_wordtab(char *str);
void		free_tab(char **av);
void		show_tab(char **av);
int		my_tablen(char **tab);

char		check_length(char **tab, int len);

sfVector3f	inters(sfVector3f, sfVector3f, float);
sfColor		one_light(t_shadow, sfVector3f, sfVector3f, sfVector3f);
sfColor		set_light(sfColor, float);
int		shadow(sfVector3f, sfVector3f, t_shape *, t_3f);
sfVector3f	reverse(sfVector3f);
float		limitation(t_shape *, float, sfVector3f, sfVector3f);
sfVector3f	add_color(sfVector3f, sfColor);
sfColor		div_color(sfVector3f, int);
int		nb_lights(t_lights *);
sfColor		calcul_color(t_shadow, t_lights *, t_3f, float);
sfVector3f	getting_normal(t_shadow, sfVector3f, sfVector3f);
sfColor		shapes_trace(sfVector3f, t_lights *, t_shape *);
sfColor         reflexion(t_3f inter, t_3f normal, t_3f dir, t_lights *light);

#endif /* !RAYTRACER_H_ */
