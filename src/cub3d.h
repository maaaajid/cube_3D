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
    double  angel[320];
    double  angel_in_radian[320];
    double x_inc[320], y_inc[320];
    double steps[320];
    double x_cos[320], y_sin[320];
    double dx[320], dy[320];
    int     ray[320];
} t_rayc;


int player(int event, t_rayc *rayc);
