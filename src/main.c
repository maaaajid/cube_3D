
#include"cub3d.h"

void    read_textures(t_rayc *rayc)
{
    rayc->data[0]->img = mlx_new_image(rayc->ptr, 800, 600);
    rayc->data[0]->addr = mlx_get_data_addr(rayc->data[0]->img, &rayc->data[0]->bits_per_pixel,
                        &rayc->data[0]->line_length, &rayc->data[0]->endian);
    rayc->data[1]->img = mlx_xpm_file_to_image(rayc->ptr, "./src/wall3.xpm", &rayc->data[1]->w, &rayc->data[1]->h);
    rayc->data[1]->addr = mlx_get_data_addr(rayc->data[1]->img, &rayc->data[1]->bits_per_pixel,
                        &rayc->data[1]->line_length, &rayc->data[1]->endian);
    rayc->data[2]->img = mlx_xpm_file_to_image(rayc->ptr, "./src/wall4.xpm", &rayc->data[2]->w, &rayc->data[2]->h);
    rayc->data[2]->addr = mlx_get_data_addr(rayc->data[2]->img, &rayc->data[2]->bits_per_pixel,
                        &rayc->data[2]->line_length, &rayc->data[2]->endian);
    rayc->data[3]->img = mlx_xpm_file_to_image(rayc->ptr, "./src/wall.xpm", &rayc->data[3]->w, &rayc->data[3]->h);
    rayc->data[3]->addr = mlx_get_data_addr(rayc->data[3]->img, &rayc->data[3]->bits_per_pixel,
                        &rayc->data[3]->line_length, &rayc->data[3]->endian);
    rayc->data[4]->img = mlx_xpm_file_to_image(rayc->ptr, "./src/new.xpm", &rayc->data[4]->w, &rayc->data[4]->h);
    rayc->data[4]->addr = mlx_get_data_addr(rayc->data[4]->img, &rayc->data[4]->bits_per_pixel,
                        &rayc->data[4]->line_length, &rayc->data[4]->endian);
}

int     ft_close(int event)
{
        exit (1);
}

double    distance(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	my_mlx_pixel_get(t_data *data, int ytex, int xtex)
{
	void	*dst;

	dst = data->addr + (ytex * data->line_length + xtex * (data->bits_per_pixel / 8));
	return *(unsigned int*)dst;
}

unsigned int    get_color(t_rayc *rayc, double wall, int x, int y)
{
    unsigned int color;
    double y_tex;
    double x_tex;
    y_tex = ((double)rayc->ray_in_wall[y] * rayc->data[1]->w) / 50.0;
    x_tex = ((double)x * rayc->data[2]->h ) / wall;
    color = my_mlx_pixel_get(rayc->data[2], x_tex, y_tex);
    return (color);

}

void    the_wall(t_rayc *rayc)
{   
    unsigned int color;
    int x = 0;
    int i;
    double distence;
    double wall;
    int colom = WINDOW_WIDTH / RAYS;
    int inc = 0;
    int y = x * colom;

    rayc->data[0]->img = mlx_new_image(rayc->ptr, WINDOW_WIDTH, WINDOW_HIEGHT);
    rayc->data[0]->addr = mlx_get_data_addr(rayc->data[0]->img, &rayc->data[0]->bits_per_pixel,
                        &rayc->data[0]->line_length, &rayc->data[0]->endian);
    while (x < RAYS)
    {
        y = x * colom;
        while (y < x * colom + colom)
        {
            distence = rayc->ray[x] * cos(rayc->radian[WINDOW_WIDTH / 2] - rayc->radian[x]);
            wall = ((double)50 / distence) * (double)600;
            i = 300 - (wall / 2);
            if (i < 0)
                i = 0;
            int ws = (300 - (wall / 2));
            while (inc < (int)wall && inc < 600)
            {
                color = get_color(rayc, wall, (inc + i) - ws, y);
                my_mlx_pixel_put(rayc->data[0], inc + i, y, color);
                inc++;
            }
            while (inc + i < 600)
            {
                my_mlx_pixel_put(rayc->data[0], inc + i, y, 0x808080);
                inc++;
            }
            y++;
            inc = 0;
        }
        x++;
    }
    mlx_put_image_to_window(rayc->ptr, rayc->window, rayc->data[0]->img, 0, 0);
    mlx_destroy_image(rayc->ptr, rayc->data[0]->img);
}

void    draw_rays(t_rayc *rayc)
{
    int x = 0;
    while (x < 800)
    {
        rayc->angel_in_radian[x] = rayc->angel[x] * (3.141593 / 180);
        rayc->x_cos[x] = cos(rayc->angel_in_radian[x]) * 2000;
        rayc->y_sin[x] = sin(rayc->angel_in_radian[x]) * 2000;
        rayc->dx[x] = rayc->x_cos[x];
        rayc->dy[x] = rayc->y_sin[x];
        if (abs(rayc->dx[x]) > abs(rayc->dy[x]))
            rayc->steps[x] = abs(rayc->dx[x]);
        else if (abs(rayc->dx[x]) < abs(rayc->dy[x]))
            rayc->steps[x] = abs(rayc->dy[x]);
        else
        {
            if ((int)rayc->dx[x] > (int)rayc->dy[x])
                rayc->steps[x] = rayc->dx[x];
            else if ((int)rayc->dx[x] < (int)rayc->dy[x])
                rayc->steps[x] = rayc->dy[x];
            else if (abs(rayc->dx[x]) == abs(rayc->dy[x]))
                rayc->steps[x] = abs(rayc->dx[x]);
        }
        rayc->x_inc[x] = rayc->dx[x] / rayc->steps[x];
        rayc->y_inc[x] = rayc->dy[x] / rayc->steps[x];
        while (abs(rayc->y_inc[x]) < abs(rayc->dy[x]) || abs(rayc->x_inc[x]) < abs(rayc->dx[x]))
        {
            rayc->pre_inc_x[x] = rayc->x_inc[x];
            rayc->pre_inc_y[x] = rayc->y_inc[x];
            rayc->y_inc[x] += rayc->dy[x] / rayc->steps[x];
            rayc->x_inc[x] += rayc->dx[x] / rayc->steps[x];
            if (rayc->map[(rayc->pp_y + (int)rayc->y_inc[x]) / 50]
                [(rayc->pp_x + (int)rayc->x_inc[x]) / 50] == '1')
            {
                rayc->wallx = rayc->pp_x + (int)rayc->x_inc[x];
                rayc->wally = rayc->pp_y + (int)rayc->y_inc[x];
                if (rayc->map[(rayc->pp_y + (int)rayc->pre_inc_y[x] + 1) / 50]
                    [(rayc->pp_x + (int)rayc->pre_inc_x[x]) / 50] == '1')
                {
                    rayc->dir[x] = 'S';
                    rayc->ray_in_wall[x] = rayc->wallx % 50;
                }
                else if (rayc->map[(rayc->pp_y + (int)rayc->pre_inc_y[x] - 1) / 50]
                    [(rayc->pp_x + (int)rayc->pre_inc_x[x]) / 50] == '1')
                {
                    rayc->dir[x] = 'N';
                    rayc->ray_in_wall[x] = rayc->wallx % 50;
                }
                else if (rayc->map[(rayc->pp_y + (int)rayc->pre_inc_y[x]) / 50]
                    [(rayc->pp_x + (int)rayc->pre_inc_x[x] + 1) / 50] == '1')
                {
                    rayc->dir[x] = 'E';
                    rayc->ray_in_wall[x] = rayc->wally % 50;
                }
                else if (rayc->map[(rayc->pp_y + (int)rayc->pre_inc_y[x]) / 50]
                    [(rayc->pp_x + (int)rayc->pre_inc_x[x] - 1) / 50] == '1')
                {
                    rayc->dir[x] = 'W';
                    rayc->ray_in_wall[x] = rayc->wally % 50;
                }
                rayc->ray[x] = distance(rayc->pp_x, rayc->pp_y, rayc->wallx, rayc->wally);
                break;
            }
        } 

        x++;
        // printf("xx%d\n", x);
    }
    the_wall(rayc);
    printf("hamid\n");
    while (x)
    {
        rayc->ray[x - 1] = 0;
        x--;
    }
}

int player(int event, t_rayc *rayc)
{
    int x = 0;
    if (event == 119)
    {
        rayc->x_cos[400] = cos(rayc->angel_in_radian[400]) * 4;
        rayc->y_sin[400] = sin(rayc->angel_in_radian[400]) * 4;
        rayc->pp_x += (int)rayc->x_cos[400];
        rayc->pp_y += (int)rayc->y_sin[400];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[400]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[400])/ 50] == '0')
            draw_rays(rayc);
        else
        {
            rayc->pp_x -= (int)rayc->x_cos[400];
            rayc->pp_y -= (int)rayc->y_sin[400];
        }

    }
    else if (event == 115)
    {
        rayc->x_cos[400] = cos(rayc->angel_in_radian[400]) * 4;
        rayc->y_sin[400] = sin(rayc->angel_in_radian[400]) * 4;
        rayc->pp_x -= (int)rayc->x_cos[400];
        rayc->pp_y -= (int)rayc->y_sin[400];
        if (rayc->map[(rayc->pp_y - (int)rayc->y_sin[400]) / 50]
            [(rayc->pp_x - (int)rayc->x_cos[400])/ 50] == '0')
            draw_rays(rayc);
        else
        {
            rayc->pp_x += (int)rayc->x_cos[400];
            rayc->pp_y += (int)rayc->y_sin[400];
        }
    
    }
    else if (event == 100)
    {
        rayc->angel_in_radian[400] = (rayc->angel[400] + 90) * (3.141593 / 180);
        rayc->x_cos[400] = cos(rayc->angel_in_radian[400]) * 4;
        rayc->y_sin[400] = sin(rayc->angel_in_radian[400]) * 4;
        rayc->pp_x += (int)rayc->x_cos[400];
        rayc->pp_y += (int)rayc->y_sin[400];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[400]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[400])/ 50] == '0')
            draw_rays(rayc);
        else
        {
            rayc->pp_x -= (int)rayc->x_cos[400];
            rayc->pp_y -= (int)rayc->y_sin[400];
        }
    }
    else if (event == 97)
    {
            rayc->angel_in_radian[400] = (rayc->angel[400] - 90) * (3.141593 / 180);
            rayc->x_cos[400] = cos(rayc->angel_in_radian[400]) * 4;
            rayc->y_sin[400] = sin(rayc->angel_in_radian[400]) * 4;
            rayc->pp_x += (int)rayc->x_cos[400];
            rayc->pp_y += (int)rayc->y_sin[400];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[400]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[400])/ 50] == '0')
            draw_rays(rayc); 
        else
        {
            rayc->pp_x -= (int)rayc->x_cos[400];
            rayc->pp_y -= (int)rayc->y_sin[400];
        }
    }

    else if (event == 65363)
    {
        while (x < 800)
        {
            rayc->angel[x] = rayc->angel[x] + 3;
            x++;
        }
        draw_rays(rayc);
    }
    else if (event == 65361)
    {
       while (x < 800)
        {
            rayc->angel[x] = rayc->angel[x] - 3;
            x++;
        }
        draw_rays(rayc);
    }
    else if (event == 65307)
        exit(1);
    
    // printf("%d\n", event);
}
int mouse_move(int x, int y, t_rayc *rayc)
{
    (void)y;
    int i = 0;
    mlx_mouse_get_pos(rayc->ptr, rayc->window, &rayc->a, &rayc->b);
    if (rayc->a >= 700 || rayc->a <= 100)
        mlx_mouse_move(rayc->ptr, rayc->window, 400, 300);
    if (x > rayc->old_x)
    {
        if (x >= rayc->old_x + 10)
            while (i < 800)
            {
                rayc->angel[i] += 0.8;
                i++;
            }
    }
    else
        if (x <= rayc->old_x - 10)
            while (i < 800)
            {
                rayc->angel[i] -= 0.8;
                i++;
            }
        draw_rays(rayc);
    rayc->old_x = x;
}
int main(int ac, char **av)
{
    (void)ac;
    int x = 0;
    int y = 0;
    int a;
    int b;
    t_rayc *rayc;
    char *tmp;
    char *str;
    rayc = malloc(sizeof(t_rayc));
    int fd = open(av[1], O_RDONLY, 0666);
    str = get_next_line(fd);
    tmp = get_next_line(fd);
    while (tmp)
    {
        str = ft_strjoin(str, tmp);
        free(tmp);
        tmp = get_next_line(fd);
    }
    rayc->map = ft_split(str, '\n');
    rayc->raw = ft_strlen(rayc->map[0]);
    while (rayc->map[x])
    {
        if (rayc->raw < ft_strlen(rayc->map[x]))
            rayc->raw = ft_strlen(rayc->map[x]);
        x++;
    }
    rayc->colom = x;
    x = 0;
    rayc->ptr = mlx_init();
    while (x < 5)
    {
        rayc->data[x] = malloc(sizeof(t_data));
        x++;
    }
    read_textures(rayc);
    rayc->window = mlx_new_window(rayc->ptr, 800, 600, "cub3d");
    double ab = (double)60 / (double)800;
    x = 0;
    while (x < 800)
    {
        rayc->angel[x] = 60 + ab;
        rayc->ray[x] = 0;
        ab += (double)60 / (double)800;
        x++;
    }
    rayc->old_x = 400;
    rayc->pp_x = rayc->raw * 25;
    rayc->pp_y = rayc->colom * 25;
    draw_rays(rayc);
    // mlx_mouse_hide(rayc->ptr,rayc->window);
    mlx_hook(rayc->window, 3, 3, &player, rayc);
    mlx_hook(rayc->window, 17, 0, &ft_close, NULL);
    // mlx_hook(rayc->window, 6, 1L << 6, &mouse_move, rayc);
    mlx_loop(rayc->ptr);

}