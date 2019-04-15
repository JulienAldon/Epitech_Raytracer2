##
## Makefile for raytracer2 in ~/rt
##
## Made by James Faure
## Login   <james.faure@epitech.eu>
##
## Started on  Mon Feb 20 22:50:19 2017 James Faure
## Last update Sun May 28 20:24:36 2017 Varé Paul
##

NAME    =	raytracer2

LEXER	=	lexer.c

PARSER	=	parser.c

CC      =	gcc

CFLAGS  =	-Iinclude -ggdb3

LFLAGS	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lm -pthread

RM      =	rm -f

OBJDIR  =	obj

SRC_	=	$(addprefix src/,\
		calc_dir_vector.c cone.c cylinder.c \
		light.c plane.c rotate.c sphere.c translate.c\
		)

SRC	=	main.c  \
		file_trace.c	\
		mk_vector3f.c	\
		string.c	\
		one_light.c	\
		shadow.c	\
		op_color.c	\
		limitation.c	\
		light.c		\
		tracing.c	\
		reflexion.c	\
		$(SRC_)

OBJ	=	$(SRC:%.c=$(OBJDIR)/%.o)

D_FILES	=	$(OBJ:%.o=%.d)

all:    $(NAME)
	$(RM) $(PARSER) $(LEXER) newparser.h include/parser.h

include $(D_FILES)

$(D_FILES): $(OBJDIR)/%.d : %.c | $(OBJDIR)
	@set -e; $(RM) $@; $(CC) $(CFLAGS) -MM -MT $|/$*.o $<>$@;\
	sed -i 's,\($*\)\.o[ :]*,\1.o $@ : ,g' $@;

$(NAME):	$(OBJ) $(PARSER) $(LEXER)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(OBJ): $(OBJDIR)/%.o : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	-mkdir -p $@/src

$(LEXER): flex.l
	flex -o $@ $^
	sed -i '1s/^/\#include <string.h>\n/' $@

$(PARSER): parse.y
	bison -t --defines=include/parser.h -o $@ $^&&\
	sed -i '35i\#include "raytracer.h"' include/parser.h

clean:
	$(RM) $(OBJ) $(D_FILES)

sclean:
	$(RM) $(PARSER) $(LEXER)

fclean:
	$(RM) $(NAME)

re:	clean fclean all

.PHONY:	all clean fclean re
