#include<stdio.h>
#include<unistd.h>
#include"../libft/libft.h"
#include<fcntl.h>
#include<math.h>
#include"../get_next_line/get_next_line.h"
#include"../minilibx-linux/mlx.h"

typedef struct rayc
{
    char    **map;
    int     raw;
    void    *floor;
    int     colom;
    void    *ptr;
    void    *newptr;   
    void    *img;
    void    *new_window;
    void    *window;
    int     pp_x;
    int     pp_y;
    int     wallx;
    int     wally;
    int     ray_in_wall[800];
    double  angel[800];
    char    dir[800];
    double  pre_inc_x[800];
    double  pre_inc_y[800];
    double  angel_in_radian[800];
    double x_inc[800], y_inc[800];
    double steps[800];
    double x_cos[800], y_sin[800];
    double dx[800], dy[800];
    double     ray[800];
} t_rayc;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     w;
    int     h;
}				t_data;

int player(int event, t_rayc *rayc);
