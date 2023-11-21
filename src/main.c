
#include"cub3d.h"




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
	char	*dst;

	dst = data->addr + (ytex * data->line_length + xtex * (data->bits_per_pixel / 8));
	return *(unsigned int*)dst;
}

unsigned int    get_color(t_rayc *rayc, t_data *tex, double wall, int x, int y)
{
    unsigned int color;
    double y_tex;
    double x_tex;
    y_tex = ((double)rayc->ray_in_wall[y] * tex->w ) / 50.0;
    x_tex = ((double)x * tex->h ) / wall;
    color = my_mlx_pixel_get(tex, y_tex, x_tex);
    return (color);

}


void    the_wall(t_rayc *rayc)
{
    unsigned int color;
    int x = 0;
    int i;
    double distence;
    double wall;
    int colom = 800 / 800;
    int inc = 0;
    int y = x * colom;

    t_data img;
    t_data tex;
    img.img = mlx_new_image(rayc->ptr, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
                            &img.line_length, &img.endian);
    tex.img = mlx_xpm_file_to_image(rayc->ptr, "./src/textures.xpm", &tex.w, &tex.h);
    tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, &tex.line_length, &tex.endian);
    while (x < 800)
    {
        // printf("ray%f\n", rayc->ray[x]);
        y = x * colom;
        while (y < x * colom + colom)
        {
            distence = rayc->ray[x] * cos(rayc->angel_in_radian[400] - rayc->angel_in_radian[x]);
            wall = ((double)50 / distence) * (double)500;
            // printf("ray====================[%f]\n", rayc->ray[x]);
            // if (wall > 600)
            //     wall = 600;
            if (rayc->dir[x] == 'W' || rayc->dir[x] == 'E')
                color = 0x009900;
            else
                color = 0x0000FF00;
            i = 300 - (wall / 2);
            if (i < 0)
                i = 0;
            int ws = (300 - (wall / 2));
            while (inc < (int)wall && inc < 600)
            {
                color = get_color(rayc, &tex, wall, (inc + i) - ws, y);
                my_mlx_pixel_put(&img, inc + i, y, color);
                inc++;
            }
            while (inc + i < 600)
            {
                my_mlx_pixel_put(&img, inc + i, y, 0x808080);
                inc++;
            }
            y++;
            inc = 0;
        }
        // exit(1);
        x++;
    }
    if (x == 800)
        mlx_put_image_to_window(rayc->ptr, rayc->window, img.img, 0, 0);

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
            // mlx_pixel_put(rayc->ptr, rayc->window, rayc->pp_x + (int)rayc->x_inc[x],
            //     rayc->pp_y + (int)rayc->y_inc[x], 0x0000FF00);
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
                    // printf("mun of ray %d y is %d ray_in_wall==%d\n", x, rayc->wallx, rayc->ray_in_wall[x]);
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
                // printf("ray num %d is in %d of cub\n", x, rayc->ray_in_wall[x]);
                break;
            }
        } 
        x++;
    }
    the_wall(rayc);
    while (x)
    {
        rayc->ray[x - 1] = 0;
        x--;
    }
    printf("======================\n=======================\n");
}

// void    draw_img_line(t_rayc *rayc)
// {
//     int x = 50;
//     int y = 0;

//     while (x < rayc->raw * 50)
//     {
//         while (y < rayc->colom * 50)
//         {
//             mlx_pixel_put(rayc->ptr, rayc->window, x, y, 0x000000);
//             y++;
//         }
//         x += 50;
//         y = 0;
//     }
//     x = 0;
//     y = 50;
//     while (y < rayc->colom * 50)
//     {
//         while (x < rayc->raw * 50)
//         {
//             mlx_pixel_put(rayc->ptr, rayc->window, x, y, 0x000000);
//             x++;
//         }
//         x = 0;
//         y += 50;
//     }
// }

// void    draw_img_back(t_rayc *rayc)
// {
//     int x = 0;
//     int y = 0;

//     while (rayc->map[y])
//     {
//         x = 0;
//         while (rayc->map[y][x])
//         {
//             if (rayc->map[y][x] == '1')
//                 mlx_put_image_to_window(rayc->ptr,
//                     rayc->window, rayc->img, x * 50, y * 50);
//             else if (rayc->map[y][x] == '0')
//                 mlx_put_image_to_window(rayc->ptr,
//                     rayc->window, rayc->floor, x * 50, y * 50);
//             x++;
//         }
//         y++;
//     }
// }


// void    draw_player(t_rayc *rayc)
// {
//     int x, y;

//     int flag = 0;

//     x = 0;
//     y = 0;
//     // draw_img_back(rayc);
//     // draw_img_line(rayc);
//     if (rayc->map[rayc->pp_y / 50][rayc->pp_x /50] == '1')
//     {
//         while (rayc->pp_y < rayc->colom * 50)
//         {
//             while (rayc->pp_x < rayc->raw * 50)
//             {
//                 if (rayc->map[rayc->pp_y / 50][rayc->pp_x / 50] == '0')
//                 {
//                     flag = 1;
//                     break;
//                 }
//                 rayc->pp_x += 50;
//             }
//             if (flag == 1)
//                 break;
//             rayc->pp_x = 50;
//             rayc->pp_y += 50;
//         }
//         rayc->pp_x += 25;
//     }
//             // mlx_pixel_put(rayc->ptr, rayc->window,
//             //     rayc->pp_x + x, rayc->pp_y + y, 0x0000FF00);
// }

int player(int event, t_rayc *rayc)
{
    int x = 0;
    if (event == 119)
    {
        rayc->x_cos[400] = cos(rayc->angel_in_radian[400]) * 6;
        rayc->y_sin[400] = sin(rayc->angel_in_radian[400]) * 6;
        rayc->pp_x += (int)rayc->x_cos[400];
        rayc->pp_y += (int)rayc->y_sin[400];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[400]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[400])/ 50] == '0')
        {
            // draw_player(rayc);
            draw_rays(rayc);
        }
        else
        {
            rayc->pp_x -= (int)rayc->x_cos[400];
            rayc->pp_y -= (int)rayc->y_sin[400];
        }

    }
    else if (event == 115)
    {
        rayc->x_cos[400] = cos(rayc->angel_in_radian[400]) * 6;
        rayc->y_sin[400] = sin(rayc->angel_in_radian[400]) * 6;
        rayc->pp_x -= (int)rayc->x_cos[400];
        rayc->pp_y -= (int)rayc->y_sin[400];
        if (rayc->map[(rayc->pp_y - (int)rayc->y_sin[400]) / 50]
            [(rayc->pp_x - (int)rayc->x_cos[400])/ 50] == '0')
        {
            // draw_player(rayc);
            draw_rays(rayc);
        }
        else
        {
            rayc->pp_x += (int)rayc->x_cos[400];
            rayc->pp_y += (int)rayc->y_sin[400];
        }
    
    }
    else if (event == 100)
    {
        rayc->angel_in_radian[400] = (rayc->angel[400] + 90) * (3.141593 / 180);
        rayc->x_cos[400] = cos(rayc->angel_in_radian[400]) * 6;
        rayc->y_sin[400] = sin(rayc->angel_in_radian[400]) * 6;
        rayc->pp_x += (int)rayc->x_cos[400];
        rayc->pp_y += (int)rayc->y_sin[400];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[400]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[400])/ 50] == '0')
        {
            // draw_player(rayc);
            draw_rays(rayc);
        }
        else
        {
            rayc->pp_x -= (int)rayc->x_cos[400];
            rayc->pp_y -= (int)rayc->y_sin[400];
        }
    }
    else if (event == 97)
    {
            rayc->angel_in_radian[400] = (rayc->angel[400] - 90) * (3.141593 / 180);
            rayc->x_cos[400] = cos(rayc->angel_in_radian[400]) * 6;
            rayc->y_sin[400] = sin(rayc->angel_in_radian[400]) * 6;
            rayc->pp_x += (int)rayc->x_cos[400];
            rayc->pp_y += (int)rayc->y_sin[400];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[400]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[400])/ 50] == '0')
        {
            // draw_player(rayc);
            draw_rays(rayc); 
        }
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
        // draw_player(rayc);
        draw_rays(rayc);
    }
    else if (event == 65361)
    {
       while (x < 800)
        {
            rayc->angel[x] = rayc->angel[x] - 3;
            x++;
        }
        // draw_player(rayc);
        draw_rays(rayc);
    }
    else if (event == 113)
        exit(1);
    // printf("%d\n", event);ab
}

int main(int ac, char **av)
{
    (void)ac;
    int x = 0;
    int y = 0;
    int a;
    int b;
    t_rayc rayc;
    char *tmp;
    char *str;

    int fd = open(av[1], O_RDONLY, 0666);
    str = get_next_line(fd);
    tmp = get_next_line(fd);
    while (tmp)
    {
        str = ft_strjoin(str, tmp);
        free(tmp);
        tmp = get_next_line(fd);
    }
    rayc.map = ft_split(str, '\n');
    rayc.raw = ft_strlen(rayc.map[0]);
    while (rayc.map[x])
    {
        if (rayc.raw < ft_strlen(rayc.map[x]))
            rayc.raw = ft_strlen(rayc.map[x]);
        x++;
    }
    rayc.colom = x;
    x = 0;
    rayc.ptr = mlx_init();
    rayc.img = mlx_xpm_file_to_image(rayc.ptr, "./src/wall.xpm", &a, &b);
    rayc.floor = mlx_xpm_file_to_image(rayc.ptr, "./src/newblue.xpm", &a, &b);
    // if (!rayc.img || )
    rayc.window = mlx_new_window(rayc.ptr, 800, 600, "cub3d");
    // while (rayc.map[y])
    // {
    //     x = 0;
    //     while (rayc.map[y][x])
    //     {
    //         if (rayc.map[y][x] == '1')
    //             mlx_put_image_to_window(rayc.ptr,
    //                 rayc.window, rayc.img, x * 50, y * 50);
    //         else if (rayc.map[y][x] == '0')
    //             mlx_put_image_to_window(rayc.ptr,
    //                 rayc.window, rayc.floor, x * 50, y * 50);
    //         x++;
    //     }
    //     y++;
    // }
    double ab = (double)60 / (double)800;
    x = 0;
    while (x < 800)
    {
        rayc.angel[x] = 60 + ab;
        rayc.ray[x] = 0;
        ab += (double)60 / (double)800;
        x++;
    }
    // printf("%f", ab);
    // exit (1);
    rayc.pp_x = rayc.raw * 25;
    rayc.pp_y = rayc.colom * 25;
    // draw_player(&rayc);
    draw_rays(&rayc);
    mlx_hook(rayc.window, 3, 3, &player, &rayc);
    mlx_loop(rayc.ptr);

}