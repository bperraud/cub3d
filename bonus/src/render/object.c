/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:35:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/08/19 23:42:14 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_object_t(t_game *game, int index, char *path_to_texture)
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	img = mlx_xpm_file_to_image(game->mlx, path_to_texture,
			&game->list_object[index].obj_t.width, &game->list_object[index].obj_t.height);
	if (!img)
		parsing_error("error when loading object texture");
	game->list_object[index].obj_t.img = (unsigned int *)mlx_get_data_addr(img,
			&bits_per_pixel,
			&size_line,
			&endian);
	game->list_object[index].obj_t.allocated_img = img;
}

void	init_object(t_game *game)
{
	t_object	tree;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*img;

	tree.x = 3.5;
	tree.y = 7.5;
	tree.size = 0.5;
	game->list_object[0] = tree;
	load_object_t(game, 0, "img/object/tree.xpm");
}

static void draw_object(void *img, double fObjectCeiling, double fMiddleOfObject)
{

}

static void	init_draw_object(void *img, t_object obj, double f_object_angle, double dist)
{
	double fObjectCeiling;
	double fObjectHeight;
	double fObjectWidth;
	double fMiddleOfObject;
	double lx;
	double ly;

	fObjectCeiling = (((double) SCREEN_H / 2.0) - ((double) SCREEN_H / ((double) dist / obj.size)));
	fObjectHeight = (double) SCREEN_H - 2.0 * fObjectCeiling;
	fObjectWidth = fObjectHeight / ((double) obj.obj_t.height  / (double) obj.obj_t.width);
	fMiddleOfObject = (0.5 * (f_object_angle / (FOV / 2.0)) + 0.5) * (double) SCREEN_W;

	for (lx = 0; lx < fObjectWidth; lx++)
	{
		for (ly = 0; ly < fObjectHeight; ly++)
		{
			int tex = ((int) (ly / fObjectHeight * obj.obj_t.height)
			 * obj.obj_t.height + (int) (lx / fObjectWidth * obj.obj_t.width));

			int color = obj.obj_t.img[tex];
			int nObjectColumn = (fMiddleOfObject + lx - (fObjectWidth / 2.0));

			if (nObjectColumn >= 0 && nObjectColumn < SCREEN_W)
			{
				if (color > 0)
					my_mlx_pixel_put(img, nObjectColumn, (int) fObjectCeiling + ly, color);
			}
		}
	}
}

void	render_objects(void	*img, t_game *g)
{
	t_object	obj;
	int			i;
	double		fvec_x;
	double		fvec_y;
	double		dist;
	double		fObjectAngle;

	i = 0;
	while (i < 1)
	{
		obj = g->list_object[i];

		fvec_x = obj.x - g->player.pos.x;
		fvec_y = obj.y - g->player.pos.y;
		dist = sqrt(fvec_x * fvec_x + fvec_y * fvec_y);

		fObjectAngle = atan2(fvec_x, fvec_y) - atan2(g->player.dir.x , g->player.dir.y);
		if (fObjectAngle < -M_PI)
			fObjectAngle += 2.0 * M_PI;
		if (fObjectAngle > M_PI)
			fObjectAngle -= 2.0 * M_PI;

		if (fabs(fObjectAngle) < FOV / 2.0 && sqrt(fvec_x * fvec_x + fvec_y * fvec_y) >= 1.0)
		{
			init_draw_object(img, obj, fObjectAngle, dist);
		}
		i++;
	}
}
