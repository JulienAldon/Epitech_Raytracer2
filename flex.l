%{
#include "parser.h"
  #define DB_PRINTF
%}

%option		yylineno

DIGIT		[0-9]
ID		[a-z][a-z0-9]*
NOT_ALNUM	[^a-zA-Z0-9]

%%

" "|"\t"|("#".*"\n"?) /* Skip these */ {DB_PRINTF("skip\n");}

("+"|"-")*[0-9]*"."?[0-9]*  { yylval.NUM = atof(yytext);
  DB_PRINTF("returning num\n"); return (NUM); }
"eye"	        DB_PRINTF("returning eye\n"); return (EYE);
"light"		return (LIGHT);
"sphere"	DB_PRINTF("returning sphere\n"); return (SPHERE);
"cylinder"	return (CYLINDER);
"cone"		return (CONE);
"plane"		return (PLANE);
"mobius"	return (MOBIUS);
"translate"	return (TRANSLATE);
"rotate"	return (ROTATE);
"color"		return (COLOR);
"damier"	return (DAMIER);
"transparence"	return (TRANSPARENCE);
"reflection"	return (REFLECTION);
"min""imium"?	return (MIN);
"max""imum"?	return (MAX);
<<EOF>>		|
'\0'		{ static char first = 0; ++first; return (first ? '\n' : EOF); }
\n		return ('\n');
.		DB_PRINTF("unrecognized (%c).\n", *yytext);return (*yytext);

%%

int	yywrap()
{
  return (1);
}
