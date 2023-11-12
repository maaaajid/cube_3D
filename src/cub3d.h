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
    // void    
    void    *img;
    void    *new_window;
    void    *window;
    int     pp_x;
    int     pp_y;
    double  angel[120];
    double  angel_in_radian[120];
    double x_inc[120], y_inc[120];
    double steps[120];
    double x_cos[120], y_sin[120];
    double dx[120], dy[120];
    int     ray[120];
} t_rayc;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int player(int event, t_rayc *rayc);
