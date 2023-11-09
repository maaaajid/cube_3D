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
    void    *img;
    void    *window;
    int     pp_x;
    int     pp_y;
    double  angel[60];
    double  angel_in_radian[60];
    double x_inc[60], y_inc[60];
    double steps[60];
    double x_cos[60], y_sin[60];
    double dx[60], dy[60];
    int     ray[60];
} t_rayc;


int player(int event, t_rayc *rayc);
