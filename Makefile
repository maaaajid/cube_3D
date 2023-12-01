NAME = cub3D

SOURCES = parse/path.c parse/read_map.c parse/utils.c parse/check_player.c parse/cheking_walls.c parse/check_text.c parse/utils4.c\
	get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c\
	Libft/ft_strlen.c Libft/ft_calloc.c Libft/ft_strjoin.c Libft/ft_split.c Libft/ft_strncmp.c Libft/ft_strchr.c \
	Libft/ft_strcmp.c  Libft/ft_memset.c Libft/ft_isdigit.c Libft/ft_putstr_fd.c Libft/ft_atoi.c\
	Libft/ft_bzero.c Libft/ft_strtrim.c Libft/ft_substr.c Libft/ft_strdup.c  Libft/ft_memcpy.c\
	src/main.c src/moves.c src/reycasting.c src/textures.c src/utils.c src/utils2.c\


OBJECTS = $(SOURCES:.c=.o)

CC = cc

LINK_FLAGS = -L -lft -L./minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz

CFLAGS = -Werror -Wextra -Wall  #-fsanitize=address -g3


$(NAME) : $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) $(LINK_FLAGS) -o $(NAME)


all : $(NAME)

clean :
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all