#include<stdio.h>
#include<unistd.h>
#include"../libft/libft.h"
#include<fcntl.h>
#include<math.h>
#include"../get_next_line/get_next_line.h"
#include"../minilibx-linux/mlx.h"

#define WINDOW_WIDTH 800.0
#define WINDOW_HIEGHT 600.0
#define RAYS 800
#define FOV 60




typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     w;
    int     h;
}				t_data;

typedef struct s_rayc
{
    char    **map;
    int     raw;
    int     a;
    int     b;
    int     old_x;
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
    int     ray_in_wall[RAYS];
    double  angel[RAYS];
    char    dir[RAYS];
    double  pre_inc_x[RAYS];
    double  pre_inc_y[RAYS];
    double  radian[RAYS];
    double x_inc[RAYS], y_inc[RAYS];
    double steps[RAYS];
    double x_cos[RAYS], y_sin[RAYS];
    double dx[RAYS], dy[RAYS];
    double     ray[RAYS];
    t_data  *data[5];
} t_rayc;

typedef struct txtr
{
    unsigned int color;
    int i;
    double distence;
    double wall;
    int colom;
    int y;
    int ws;
    int inc;
} t_txtr;

int player(int event, t_rayc *rayc);

