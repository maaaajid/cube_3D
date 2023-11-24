
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

double    dist(double x1, double y1, double x2, double y2)
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

void    put_textures(t_rayc *rayc, t_txtr *txtr, int x)
{
    while (txtr->y < x * txtr->colom + txtr->colom)
    {
        txtr->distence = cos(rayc->radian[(int)WINDOW_WIDTH / 2] - rayc->radian[x]);
        txtr->distence = rayc->ray[x] * txtr->distence;
        txtr->wall = ((double)50 / txtr->distence) * WINDOW_HIEGHT;
        txtr->i = (WINDOW_HIEGHT / 2) - (txtr->wall / 2);
        if (txtr->i < 0)
            txtr->i = 0;
        txtr->ws = ((WINDOW_HIEGHT / 2) - (txtr->wall / 2));
        while (txtr->inc < (int)txtr->wall && txtr->inc < WINDOW_HIEGHT)
        {
            txtr->color = get_color(rayc, txtr->wall, (txtr->inc + txtr->i) - txtr->ws, txtr->y);
            my_mlx_pixel_put(rayc->data[0], txtr->inc + txtr->i, txtr->y, txtr->color);
            txtr->inc++;
        }
        while (txtr->inc + txtr->i < WINDOW_HIEGHT)
        {
            my_mlx_pixel_put(rayc->data[0], txtr->inc + txtr->i, txtr->y, 0x808080);
            txtr->inc++;
        }
        txtr->y++;
        txtr->inc = 0;
    }
}


void    the_wall(t_rayc *rayc)
{   
    int x = 0;
    t_txtr txtr;

    txtr.inc = 0;
    txtr.colom = WINDOW_WIDTH / RAYS;
    txtr.y = x * txtr.colom;
    rayc->data[0]->img = mlx_new_image(rayc->ptr, WINDOW_WIDTH, WINDOW_HIEGHT);
    rayc->data[0]->addr = mlx_get_data_addr(rayc->data[0]->img, &rayc->data[0]->bits_per_pixel,
                        &rayc->data[0]->line_length, &rayc->data[0]->endian);
    while (x < RAYS)
    {
        txtr.y = x * txtr.colom;
        put_textures(rayc, &txtr, x);
        x++;
    }
    mlx_put_image_to_window(rayc->ptr, rayc->window, rayc->data[0]->img, 0, 0);
    mlx_destroy_image(rayc->ptr, rayc->data[0]->img);
    while (x--)
        rayc->ray[x - 1] = 0;
}

void    get_angel(t_rayc *rayc, int x)
{
    rayc->radian[x] = rayc->angel[x] * (3.141593 / 180);
    rayc->x_cos[x] = cos(rayc->radian[x]) * 2000;
    rayc->y_sin[x] = sin(rayc->radian[x]) * 2000;
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
}

void    get_direction(t_rayc *rayc, int x)
{
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
}


void    draw_rays(t_rayc *rayc)
{
    int x;

    x = -1;
    while (++x < RAYS)
    {
        get_angel(rayc, x);
        while (abs(rayc->y_inc[x]) < abs(rayc->dy[x])
            || abs(rayc->x_inc[x]) < abs(rayc->dx[x]))
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
                get_direction(rayc, x);
                break;
            }
        }
        rayc->ray[x] = dist(rayc->pp_x, rayc->pp_y, rayc->wallx, rayc->wally);
    }
    the_wall(rayc);
}

void    forward(t_rayc *rayc)
{
    rayc->x_cos[RAYS / 2] = cos(rayc->radian[RAYS / 2]) * 8;
    rayc->y_sin[RAYS / 2] = sin(rayc->radian[RAYS / 2]) * 8;
    rayc->pp_x += (int)rayc->x_cos[RAYS / 2];
    rayc->pp_y += (int)rayc->y_sin[RAYS / 2];
    if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[RAYS / 2]) / 50]
        [(rayc->pp_x + (int)rayc->x_cos[RAYS / 2])/ 50] == '0')
        draw_rays(rayc);
    else
    {
        rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
        rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
    }
}

void    backwards(t_rayc *rayc)
{
    rayc->x_cos[RAYS / 2] = cos(rayc->radian[RAYS / 2]) * 8;
    rayc->y_sin[RAYS / 2] = sin(rayc->radian[RAYS / 2]) * 8;
    rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
    rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
    if (rayc->map[(rayc->pp_y - (int)rayc->y_sin[RAYS / 2]) / 50]
        [(rayc->pp_x - (int)rayc->x_cos[RAYS / 2])/ 50] == '0')
        draw_rays(rayc);
    else
    {
        rayc->pp_x += (int)rayc->x_cos[RAYS / 2];
        rayc->pp_y += (int)rayc->y_sin[RAYS / 2];
    }
}
void    move_right(t_rayc *rayc)
{
    rayc->radian[RAYS / 2] = (rayc->angel[RAYS / 2] + 90) * (3.141593 / 180);
    rayc->x_cos[RAYS / 2] = cos(rayc->radian[RAYS / 2]) * 8;
    rayc->y_sin[RAYS / 2] = sin(rayc->radian[RAYS / 2]) * 8;
    rayc->pp_x += (int)rayc->x_cos[RAYS / 2];
    rayc->pp_y += (int)rayc->y_sin[RAYS / 2];
    if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[RAYS / 2]) / 50]
        [(rayc->pp_x + (int)rayc->x_cos[RAYS / 2])/ 50] == '0')
        draw_rays(rayc);
    else
    {
        rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
        rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
    }
}

void    move_left(t_rayc *rayc)
{
    rayc->radian[RAYS / 2] = (rayc->angel[RAYS / 2] - 90) * (3.141593 / 180);
    rayc->x_cos[RAYS / 2] = cos(rayc->radian[RAYS / 2]) * 8;
    rayc->y_sin[RAYS / 2] = sin(rayc->radian[RAYS / 2]) * 8;
    rayc->pp_x += (int)rayc->x_cos[RAYS / 2];
    rayc->pp_y += (int)rayc->y_sin[RAYS / 2];
    if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[RAYS / 2]) / 50]
        [(rayc->pp_x + (int)rayc->x_cos[RAYS / 2])/ 50] == '0')
        draw_rays(rayc); 
    else
    {
        rayc->pp_x -= (int)rayc->x_cos[RAYS / 2];
        rayc->pp_y -= (int)rayc->y_sin[RAYS / 2];
    }
}
void    rotete_right(t_rayc *rayc)
{
    int x;

    x = 0;
    while (x < RAYS)
    {
        rayc->angel[x] = rayc->angel[x] + 5;
        x++;
    }
    draw_rays(rayc);
}

void    rotete_left(t_rayc *rayc)
{
    int x;

    x = 0;
    while (x < RAYS)
    {
        rayc->angel[x] = rayc->angel[x] - 5;
        x++;
    }
    draw_rays(rayc);
}

int player(int event, t_rayc *rayc)
{
    int x = 0;
    if (event == 119)
        forward(rayc);
    else if (event == 115)
        backwards(rayc);
    else if (event == 100)
        move_right(rayc);
    else if (event == 97)
        move_left(rayc);
    else if (event == 65363)
        rotete_right(rayc);
    else if (event == 65361)
        rotete_left(rayc);
    else if (event == 65307)
        exit(1);
}
int mouse_move(int x, int y, t_rayc *rayc)
{
    (void)y;
    int i = 0;
    mlx_mouse_get_pos(rayc->ptr, rayc->window, &rayc->a, &rayc->b);
    if (rayc->a >= 700 || rayc->a <= 100)
        mlx_mouse_move(rayc->ptr, rayc->window, RAYS / 2, 300);
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
    rayc->window = mlx_new_window(rayc->ptr, WINDOW_WIDTH, WINDOW_HIEGHT, "cub3d");
    double ab = (double)FOV / (double)RAYS;
    x = 0;
    while (x < RAYS)
    {
        rayc->angel[x] = 60 + ab;
        rayc->ray[x] = 0;
        ab += (double)FOV / (double)RAYS;
        x++;
    }
    rayc->old_x = RAYS / 2;
    rayc->pp_x = rayc->raw * 25;
    rayc->pp_y = rayc->colom * 25;
    draw_rays(rayc);
    // mlx_mouse_hide(rayc->ptr,rayc->window);
    mlx_hook(rayc->window, 3, 3, &player, rayc);
    mlx_hook(rayc->window, 17, 0, &ft_close, NULL);
    // mlx_hook(rayc->window, 6, 1L << 6, &mouse_move, rayc);
    mlx_loop(rayc->ptr);
}