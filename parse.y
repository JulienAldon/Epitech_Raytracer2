/*
** Parser for raytracer objects
*/
%{
  #include "raytracer.h"
  int	yylex();
  void	yyerror(char const *);

  t_shape	*shapes = 0;
  t_3f		eye_pos = {-200, 0, 0};
  t_lights	*lights = 0;

  sfVector3f	mk_vector3f(float x, float y, float z);
  sfColor	mk_color(sfUint8 r, sfUint8 g, sfUint8 b, sfUint8 a)
  {
    sfColor	c;

    c.r = r; c.g = g; c.b = b; c.a = a;
    return (c);
  }

  t_lights	*add_light(t_3f l)
  {
    t_lights	*ne;

    ne = malloc(sizeof(*ne));
    ne->next = lights;
    ne->light = l;
    return (lights = ne);
  }
  
  t_shape	*add_shape(t_types type, float radius)
  {
    t_shape	*r;

    r = malloc(sizeof(*r));
    r->type = type;
    r->translate = mk_vector3f(0, 0, 0);
    r->rotate = mk_vector3f(0, 0, 0);
    r->color = sfRed;
    r->radius = radius;
    r->reflection = r->transparence = 0;
    r->min_max[0] = r->min_max[1] = mk_vector3f(-1, -1, -1);
    r->mobius[0] = r->mobius[1] = 0;
    r->damier = 0;
    r->next = shapes;
    shapes = r;
    return (shapes);
  }
%}

%define api.value.type union /* Generate YYSTYPE from these */
%token <float> NUM /* The fields of sfVector3f */
%token EYE SPHERE CYLINDER CONE PLANE MOBIUS LIGHT
%token TRANSLATE ROTATE COLOR DAMIER TRANSPARENCE REFLECTION MIN MAX BRILLANCE
%type <t_shape *> eye shape
%type <t_lights *> light
%type <sfColor>	color
%type <sfVector3f> vector
%%

start:
'\n'
| eye
| start line

eye:
EYE vector { eye_pos = $2; }
;

line:
 '\n'
| shape '\n'
| light '\n'
| error '\n' { YYABORT; }
;

light:
LIGHT vector	{ $$ = add_light($2); }
| light COLOR color { $$ = $1; $1->color = $3; }
;

shape:
SPHERE NUM		{ $$ = add_shape(T_SPHERE, $2); }
| CYLINDER NUM		{ $$ = add_shape(T_CYLINDER, $2); }
| CONE NUM		{ $$ = add_shape(T_CONE, $2); }
| PLANE	NUM		{ $$ = add_shape(T_PLANE, $2); }
| MOBIUS NUM NUM	{ $$ = add_shape(T_MOBIUS, 0); $$->mobius[0] = $2; $$->mobius[1] = $3;	}
| shape TRANSLATE vector { $$ = $1; $1->translate = $3; }
| shape ROTATE vector   { $$ = $1; $1->rotate = $3; }
| shape COLOR color { $$ = $1; $1->color = $3; }
| shape DAMIER NUM { $$ = $1; $$->damier = $3;	}
| shape TRANSPARENCE NUM { $$ = $1; $1->transparence = $3;	}
| shape REFLECTION NUM { $$ = $1; $1->reflection = $3;	}
| shape MIN vector	{ $$ = $1; $1->min_max[0] = $3;	}
| shape MAX vector	{ $$ = $1; $1->min_max[1] = $3;	}
| shape BRILLANCE NUM	{ $$ = $1; $1->brillance = $3;	}
;

vector: NUM NUM NUM	{ $$ = mk_vector3f($1, $2, $3);	}
| '{' vector '}'	{ $$ = $2;}
| '(' vector ')'	{ $$ = $2;}
color: NUM NUM NUM NUM  { $$ = mk_color($1, $2, $3, $4);}
| vector		{ $$ = mk_color($1.x, $1.y, $1.z, 255);}
| '[' color ']'		{ $$ = $2;	}
| '(' color ')'		{ $$ = $2;	}


%%

void	yyerror(char const *s)
{
  extern int	yylineno;

  fprintf(stderr, "line %d, %s\n", yylineno, s);
}
