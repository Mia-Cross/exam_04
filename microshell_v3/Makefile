NAME = microshell

OBJDIR =	.obj

SRCS = 	microshell.c \
		utils.c \
		parsing.c

OBJS =	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DPDCS =	$(OBJS:.o=.d)

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address 

opti:
	@make -j all

all :
	@make $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@printf "[$(NAME)] "
	gcc $(CFLAGS) -o $(NAME) ${OBJS}
	@echo Compiled $(NAME) successfully !

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR) :
	@mkdir -p .obj

echo :
	./microshell /usr/bin/echo " please work normally | please... ; i beg you"
	./microshell /usr/bin/echo " please work normally |" " please... ; i beg you"
	./microshell "/usr/bin/echo" please work "normally |  please... ; i beg you"

clean :
	@rm -rf $(OBJDIR)

fclean : clean
	@rm -rf $(NAME)

re :
	@make fclean
	@make opti