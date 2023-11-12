
#include"cub3d.h"

void	my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


















void    the_casting(t_rayc *rayc)
{
    int x = 0;
    int i;
    double wall;
    int colom = 1280 / 320;
    int inc = 0;
    int y = x * colom;
    t_data img;
    img.img = mlx_new_image(rayc->ptr, 1280, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
                            &img.line_length, &img.endian);
    while (x < 320)
    {
        y = x * colom;
        while (y < x * colom + colom)
        {
            wall = ((double)50 / (double)rayc->ray[x]) * 255;
            i = 300 - (wall / 2);
            // printf("WALL%f\n", wall);
            while (inc < (int)wall)
            {
                my_mlx_pixel_put(&img, inc + i, y, 0x0000FF00);
                inc++;
            }
            // printf("%d\n", inc + i);
            // exit(1);
            while (inc + i < 600)
            {
                my_mlx_pixel_put(&img, inc + i, y, 0x808080);
                inc++;
            }
            y++;
            inc = 0;
            // printf("y%d    x%d\n", y, x * colom + colom);
        }
        x++;
    }
    // printf("x == %d\n", x);
    if (x == 320)
        mlx_put_image_to_window(rayc->ptr, rayc->window, img.img, 0, 0);
}























void    draw_rays(t_rayc *rayc)
{
    int x = 0;
    while (x < 320)
    {
        rayc->angel_in_radian[x] = rayc->angel[x] * (3.141593 / 180);
        rayc->x_cos[x] = cos(rayc->angel_in_radian[x]) * 1000;
        rayc->y_sin[x] = sin(rayc->angel_in_radian[x]) * 1000;
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
            rayc->y_inc[x] += rayc->dy[x] / rayc->steps[x];
            rayc->x_inc[x] += rayc->dx[x] / rayc->steps[x];
            rayc->ray[x]++;
            if (rayc->map[(rayc->pp_y + (int)rayc->y_inc[x]) / 50]
                [(rayc->pp_x + (int)rayc->x_inc[x]) / 50] == '1')
            {
                // printf("ray%d\n", rayc->ray[x]);
                break;
            }
        } 
        x++;
    }
    the_casting(rayc);
    while (x)
    {
        rayc->ray[x] = 0;
        x--;
    }
    // printf("======================\n=========================\n");
}

void    draw_img_line(t_rayc *rayc)
{
    int x = 50;
    int y = 0;

    while (x < rayc->raw * 50)
    {
        while (y < rayc->colom * 50)
        {
            mlx_pixel_put(rayc->ptr, rayc->window, x, y, 0x000000);
            y++;
        }
        x += 50;
        y = 0;
    }
    x = 0;
    y = 50;
    while (y < rayc->colom * 50)
    {
        while (x < rayc->raw * 50)
        {
            mlx_pixel_put(rayc->ptr, rayc->window, x, y, 0x000000);
            x++;
        }
        x = 0;
        y += 50;
    }
}

void    draw_img_back(t_rayc *rayc)
{
    int x = 0;
    int y = 0;

    while (rayc->map[y])
    {
        x = 0;
        while (rayc->map[y][x])
        {
            if (rayc->map[y][x] == '1')
                mlx_put_image_to_window(rayc->ptr,
                    rayc->window, rayc->img, x * 50, y * 50);
            else if (rayc->map[y][x] == '0')
                mlx_put_image_to_window(rayc->ptr,
                    rayc->window, rayc->floor, x * 50, y * 50);
            x++;
        }
        y++;
    }
}


void    draw_player(t_rayc *rayc)
{
    int x, y;

    int flag = 0;

    x = 0;
    y = 0;
    // draw_img_back(rayc);
    // draw_img_line(rayc);
    if (rayc->map[rayc->pp_y / 50][rayc->pp_x /50] == '1')
    {
        while (rayc->pp_y < rayc->colom * 50)
        {
            while (rayc->pp_x < rayc->raw * 50)
            {
                if (rayc->map[rayc->pp_y / 50][rayc->pp_x / 50] == '0')
                {
                    flag = 1;
                    break;
                }
                rayc->pp_x += 50;
            }
            if (flag == 1)
                break;
            rayc->pp_x = 50;
            rayc->pp_y += 50;
        }
        rayc->pp_x += 25;
    }
            // mlx_pixel_put(rayc->ptr, rayc->window,
            //     rayc->pp_x + x, rayc->pp_y + y, 0x0000FF00);
}

int player(int event, t_rayc *rayc)
{
    int x = 0;
    if (event == 119)
    {
        rayc->x_cos[160] = cos(rayc->angel_in_radian[160]) * 4;
        rayc->y_sin[160] = sin(rayc->angel_in_radian[160]) * 4;
        rayc->pp_x += (int)rayc->x_cos[160];
        rayc->pp_y += (int)rayc->y_sin[160];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[160]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[160])/ 50] == '0')
        {
            draw_player(rayc);
            draw_rays(rayc);
        }
        else
        {
            rayc->pp_x -= (int)rayc->x_cos[160];
            rayc->pp_y -= (int)rayc->y_sin[160];
        }

    }
    else if (event == 115)
    {
        rayc->x_cos[160] = cos(rayc->angel_in_radian[160]) * 4;
        rayc->y_sin[160] = sin(rayc->angel_in_radian[160]) * 4;
        rayc->pp_x -= (int)rayc->x_cos[160];
        rayc->pp_y -= (int)rayc->y_sin[160];
        if (rayc->map[(rayc->pp_y - (int)rayc->y_sin[160]) / 50]
            [(rayc->pp_x - (int)rayc->x_cos[160])/ 50] == '0')
        {
            draw_player(rayc);
            draw_rays(rayc);
        }
        else
        {
            rayc->pp_x += (int)rayc->x_cos[160];
            rayc->pp_y += (int)rayc->y_sin[160];
        }
    
    }
    else if (event == 100)
    {
        rayc->angel_in_radian[160] = (rayc->angel[160] + 90) * (3.141593 / 180);
        rayc->x_cos[160] = cos(rayc->angel_in_radian[160]) * 4;
        rayc->y_sin[160] = sin(rayc->angel_in_radian[160]) * 4;
        rayc->pp_x += (int)rayc->x_cos[160];
        rayc->pp_y += (int)rayc->y_sin[160];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[160]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[160])/ 50] == '0')
        {
            draw_player(rayc);
            draw_rays(rayc);
        }
        else
        {
            rayc->pp_x -= (int)rayc->x_cos[160];
            rayc->pp_y -= (int)rayc->y_sin[160];
        }
    }
    else if (event == 97)
    {
            rayc->angel_in_radian[160] = (rayc->angel[160] - 90) * (3.141593 / 180);
            rayc->x_cos[160] = cos(rayc->angel_in_radian[160]) * 4;
            rayc->y_sin[160] = sin(rayc->angel_in_radian[160]) * 4;
            rayc->pp_x += (int)rayc->x_cos[160];
            rayc->pp_y += (int)rayc->y_sin[160];
        if (rayc->map[(rayc->pp_y + (int)rayc->y_sin[160]) / 50]
            [(rayc->pp_x + (int)rayc->x_cos[160])/ 50] == '0')
        {
            draw_player(rayc);
            draw_rays(rayc); 
        }
        else
        {
            rayc->pp_x -= (int)rayc->x_cos[160];
            rayc->pp_y -= (int)rayc->y_sin[160];
        }
    }
    else if (event == 65363)
    {
        while (x < 320)
        {
            rayc->angel[x] = rayc->angel[x] + 2;
            x++;
        }
        draw_player(rayc);
        draw_rays(rayc);
    }
    else if (event == 65361)
    {
       while (x < 320)
        {
            rayc->angel[x] = rayc->angel[x] - 2;
            x++;
        }
        draw_player(rayc);
        draw_rays(rayc);
    }
    else if (event == 113)
        exit(1);
    // printf("%d\n", event);
    return (0);
}

int main(int ac, char **av)
{
    (void)ac;
    int x = 0;
    int y = 0;
    int a = 49;
    int b = 49;
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
    // rayc.img = mlx_xpm_file_to_image(rayc.ptr, "./src/wall.xpm", &a, &b);
    // rayc.floor = mlx_xpm_file_to_image(rayc.ptr, "./src/newblue.xpm", &a, &b);
    rayc.window = mlx_new_window(rayc.ptr, 1280, 600, "cub3d");
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
    double ab = (double)60 / (double)320;
    x = 0;
    while (x < 320)
    {
        rayc.angel[x] = 60 + ab;
        rayc.ray[x] = 0;
        ab += (double)60 / (double)320;
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