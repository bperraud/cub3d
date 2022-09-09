/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:09:12 by bperraud          #+#    #+#             */
/*   Updated: 2022/09/09 13:40:28 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shuffle(int *array, size_t n)
{
	struct timeval	tv;
	int				usec;
	size_t			i;
	size_t			j;
	int				t;

	gettimeofday(&tv, NULL);
	usec = tv.tv_usec;
	srand48(usec);
	if (n > 1)
	{
		i = n - 1;
		while (i)
		{
			j = (unsigned int) (drand48()*(i+1));
			t = array[j];
			array[j] = array[i];
			array[i] = t;
			i--;
		}
	}
}

static void	put_pixel(t_game *g, t_data *img, int elem, int pixel_size)
{
	int		i;
	int		j;

	i = 0;
	while (i < pixel_size)
	{
		j = 0;
		while (j < pixel_size)
		{
			my_mlx_pixel_put(img, elem / SCREEN_H + i, elem % SCREEN_H + j, RED);
			j++;
		}
		i++;
	}
}

void	anim_death(t_game *game)
{
	int		i;
	int		j;
	t_data	*img;
	int		*red_pixel;

	img = &game->full_buffer;
	red_pixel = x_malloc((SCREEN_W * SCREEN_H / 4) * sizeof(int));
	i = 0;
	j = 0;
	bool t = true;
	while (i < SCREEN_W * SCREEN_H)
	{
		red_pixel[j] = i;
		if (!(i % (SCREEN_H) && i != 0) && t)
		{
			i += 3 * SCREEN_H;
			t = false;
		}
		else
		{
			i += 4;
			t = true;
		}
		j++;
	}
	shuffle(red_pixel, SCREEN_W * SCREEN_H / 4);
	i = 0;
	j = 0;
	while (i < SCREEN_W * SCREEN_H)
	{
		put_pixel(game, img, red_pixel[j], 4);
		if (!(i % 2)  && !(i % 3) && !(i % 17))
			mlx_put_image_to_window(game->mlx, game->window, img->img, 0, 0);
		i += 4;
		j++;
	}
	mlx_put_image_to_window(game->mlx, game->window, img->img, 0, 0);
	usleep(10000000);
}
