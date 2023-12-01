/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymenyoub <ymenyoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:31:55 by ymenyoub          #+#    #+#             */
/*   Updated: 2023/11/30 22:29:35 by ymenyoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../Libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define WINDOW_WIDTH 1600.0
# define WINDOW_HIEGHT 900.0
# define RAYS 1600
# define FOV 60

typedef struct s_vars
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
}					t_vars;

typedef struct s_map
{
	char			*so;
	char			*no;
	char			*we;
	char			*ea;
	int				f_r;
	int				f_g;
	int				f_b;
	int				c_r;
	int				c_g;
	int				c_b;
	int				player_found;
	int				pos_x;
	int				pos_y;
	char			vision;
	int				count;
	char			*str;
	int				fd;
	char			**split_map;
	char			**split_text;
	char			**split_file;
	char			**split_arg;
	int				empty_fd;
	char			*name;
	char			*argv;
	int				width;
	char			caracter;
}					t_map;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				w;
	int				h;
}					t_data;

typedef struct s_rayc
{
	char			**map;
	int				dir_tex;
	int				raw;
	int				a;
	int				b;
	void			*floor;
	int				floor_rgb;
	int				ceiling_rgb;
	int				colom;
	void			*ptr;
	void			*newptr;
	void			*img;
	void			*new_window;
	void			*window;
	double			pp_x;
	double			pp_y;
	double			wallx;
	double			wally;
	double			ray_in_wall[RAYS];
	double			angel[RAYS];
	char			dir[RAYS];
	double			pre_inc_x[RAYS];
	double			pre_inc_y[RAYS];
	double			radian[RAYS];
	double			x_inc[RAYS];
	double			y_inc[RAYS];
	double			steps[RAYS];
	double			x_cos[RAYS];
	double			y_sin[RAYS];
	double			dx[RAYS];
	double			dy[RAYS];
	double			ray[RAYS];
	t_data			*data[5];
}					t_rayc;

typedef struct txtr
{
	unsigned int	color;
	int				i;
	double			distence;
	double			wall;
	float			colom;
	int				y;
	int				ws;
	int				inc;
}					t_txtr;

// --------------------CUB3D--------------
void				read_map_rd(t_map *map);
void				read_texture(t_map *map);
int					map_name(char *name);
void				print_error(char *s);
void				check_args(char **av, t_map *map);
int					my_isspace(char c);
int					checkspace(char **array);
void				final_check(int ac, char **av, t_map *map, t_rayc *rayc);
int					check_map(char *line);
void				check_textures(t_map *map);
void				composed_map(t_map *map);
int					is_valid(char *map);
void				ft_free(char **av);
void				final_map_check(t_map *map, t_rayc *rayc);
int					find_start_position(t_map *map, t_rayc *rayc);
int					is_inside_map(int x, int y, int width, int height);
int					check_is_open(int i, int j, char **dup);
int					biggest_line(char **map);
int					count_line_map(char **map);
void				check_last_line(char **map);
int					check_verg(char *str);
void				get_path(char *line);
int					set_player_vision(t_map *map);
void				fill_textures(t_map *map, char *line);
void				fill_rgb(t_map *map, char *line);
void				mini_window(void);

// ------------------LIBFT---------------
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);
int					ft_strcmp(char *s1, char *s2, char c);
void				ft_putstr_fd(char *s, int fd);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(const char *s, int c);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);

// ---------------Reycast-----------------
void				get_angel(t_rayc *rayc, int x);
void				get_direction(t_rayc *rayc, int x);
void				draw_rays(t_rayc *rayc);
void				forward(t_rayc *t_rayc);
void				move_right(t_rayc *t_rayc);
void				move_left(t_rayc *t_rayc);
void				rotete_right(t_rayc *t_rayc);
void				rotete_left(t_rayc *t_rayc);
int					player(int event, t_rayc *t_rayc);
void				backwards(t_rayc *t_rayc);
int					ft_close(int event);
double				dist(double x1, double y1, double x2, double y2);
void				my_mlx_pixel_put(t_data *data, int y, int x, int color);
unsigned int		my_mlx_pixel_get(t_data *data, int ytex, int xtex);
void				read_textures(t_rayc *rayc, t_map *map);
unsigned int		get_color(t_rayc *rayc, double wall, int x, int y);
void				get_wich_textures(t_rayc *rayc, int x);
void				put_textures(t_rayc *rayc, t_txtr *txtr, int x);
void				the_wall(t_rayc *rayc);
void				draw_floor(t_rayc *rayc, t_txtr *txtr);
int					get_rgb(int r, int g, int b);
void				draw_ceiling(t_rayc *rayc, t_txtr *txtr);
void				sliding(t_rayc *rayc, double old_x_cos, double old_y_sin);

#endif