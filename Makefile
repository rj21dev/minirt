NAME		= minirt
SRCS_DIR	= srcs/
OBJS_DIR	= objs/
INCS_DIR	= includes

SRCS_F		= rt_main.c rt_ray_trace.c rt_sphere_intersect.c rt_utils.c rt_vector.c rt_init_data.c rt_events_handlers.c \
				rt_parser.c rt_errors.c rt_get_elements.c rt_get_required_elements.c rt_get_objects.c rt_parser_utils.c \
				rt_clear_data.c rt_vector2.c rt_render_scene.c \
				rt_cylinder_intersect.c \
				rt_plane_intersect.c \
				key_hook.c \
				rt_rotation.c rt_ray.c rt_matrix_rot.c

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
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS_L) -o $@

$(LIB_DIR)$(LIB) : ;
		make -C $(LIB_DIR)

clean :
	rm -rf $(OBJS_DIR)
	make clean -C $(LIB_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY:
		all clean fclean re

-include $(DEPS)
