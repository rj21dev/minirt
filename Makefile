NAME		= miniRT
SRCS_DIR	= srcs/
OBJS_DIR	= objs/
INCS_DIR	= includes

SRCS_F = main.c	\
		parser.c \
		errors.c \
		get_elements.c \
		get_objects.c \
		get_required_elements.c \
		parser_utils.c \
		vector.c \
		vector2.c \
		color.c \
		color2.c \
		render_scene.c \
		init_data.c \
		get_normal.c \
		quad_solve.c \
		cylinder_intersect.c \
		sphere_intersect.c \
		plane_intersect.c \
		get_ray.c \
		shader.c \
		clear_data.c \
		rotation.c \
		key_hook.c \
		utils.c

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_F))
OBJS_F		= $(patsubst %.c, %.o, $(SRCS_F))
DEPS_F		= $(patsubst %.c, %.d, $(SRCS_F))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_F))
DEPS		= $(addprefix $(OBJS_DIR), $(DEPS_F))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD
LFLAGS_M	= -Llibft -L/usr/local/lib -lft -lmlx -framework OpenGL -framework AppKit
LFLAGS_L	= -Llibft -L/usr/local/lib -lft -lmlx -lXext -lX11 -lm
LIB			= libft.a
LIB_DIR		= libft/

all: $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
		$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

$(OBJS_DIR) :
		mkdir -p $@

$(NAME):  $(OBJS_DIR) $(OBJS) $(LIB_DIR)$(LIB) Makefile
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS_M) -o $@

$(LIB_DIR)$(LIB) : ;
		@make --no-print-directory -C $(LIB_DIR)

clean :
	@rm -rf $(OBJS_DIR)
	@make clean --no-print-directory -C $(LIB_DIR)

fclean : clean
	@rm -f $(NAME)
	@make fclean --no-print-directory -C $(LIB_DIR)

re: fclean all

.PHONY:
		all clean fclean re

-include $(DEPS)
