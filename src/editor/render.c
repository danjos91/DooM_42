/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:34:19 by dorange-          #+#    #+#             */
/*   Updated: 2020/01/13 14:22:12 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_editor_draw_line(t_wolf3d *w)
{
	int			i;

	i = w->ui_map.v1.x;
	while (i < w->ui_map.v2.y)
	{
		ft_fdf_wu_color(
			&(t_vector3){w->ui_map.v1.x, i, 0, 0}, \
			&(t_vector3){w->ui_map.v2.x, i, 0, 0}, \
			w, \
			0x333333 \
		);
		i += 32;
	}
	i = w->ui_map.v1.y;
	while (i < w->ui_map.v2.x)
	{
		ft_fdf_wu_color(
			&(t_vector3){i, w->ui_map.v1.y, 0, 0}, \
			&(t_vector3){i, w->ui_map.v2.y, 0, 0}, \
			w, \
			0x333333 \
		);
		i += 32;
	}
}

void	ft_editor_map_fill_sectors(t_wolf3d *w)
{
	int	y;
	int	x;
	int	color;
	int	pos;

	y = w->ui_map.v1.y;
	while (y < w->ui_map.v2.y)
	{
		x = w->ui_map.v1.x;
		while (x < w->ui_map.v2.x)
		{
			if (ft_sector_check_sector(w, (t_vector3){x, y, 0, 0}))
			{
				pos = x + (y * WIN_WIDTH);
				color = ft_fdf_get_color(0xffff00, (int)w->sdl->pixels[pos], 0.7);
				w->sdl->pixels[pos] = color;
			}
			x++;
		}
		y++;
	}
}

void		ft_editor_font_draw_sector_item(t_wolf3d *w, t_sector *ptr_sector, t_ui_coord c)
{
	char	*str;

	ft_font_preset_sc(w, 18, ptr_sector->color);
	ft_font_putstr_sdl(w, "Sector", c);\

	c.x += 70;
	str = ft_itoa(ptr_sector->id);
	ft_font_putstr_sdl(w, str, c);
	free(str);

	c.x -= 70;
	c.y += 25;
	ft_font_preset_sc(w, 14, 0xdddddd);
	ft_font_putstr_sdl(w, "floor:", c);

	c.x += 50;
	str = ft_itoa(ptr_sector->floor);
	ft_font_putstr_sdl(w, str, c);
	free(str);

	c.x += 40;
	ft_font_putstr_sdl(w, "height:", c);

	c.x += 55;
	str = ft_itoa(ptr_sector->height);
	ft_font_putstr_sdl(w, str, c);
	free(str);
}

void		ft_editor_font_draw_sector_list(t_wolf3d *w, t_list *sector, int i)
{
	t_ui_coord	c;

	if (sector)
	{
		ft_editor_font_draw_sector_list(w, sector->next, i + 1);
		c = (t_ui_coord){1740, 100 + i * 50, 0};
		ft_editor_font_draw_sector_item(w, (t_sector*)sector->content, c);
	}
}

// void	ft_editor_font_draw_sector_list_2(t_wolf3d *w, t_list *ptr_list)
// {
// 	ft_font_preset_sc(w, 56, 0xff0000);
// 	ft_font_putstr_sdl(
// 		w, "Life:", \
// 		(t_ui_coord){ \
// 			w->sdl->font.g_sz * 15, \
// 			WIN_HEIGHT - w->sdl->font.f_sz * 2.5, \
// 			0
// 		}
// 	);

// 	ft_font_putstr_sdl(
// 		w, ft_itoa(10), \
// 		(t_ui_coord){ \
// 			w->sdl->font.g_sz * 20, \
// 			WIN_HEIGHT - w->sdl->font.f_sz * 2.5, \
// 			0
// 		}
// 	);

// 	ft_font_putstr_sdl(
// 		w, "Ammo:", \
// 		(t_ui_coord){ \
// 			w->sdl->font.g_sz * 15, \
// 			WIN_HEIGHT - w->sdl->font.f_sz * 1.5, \
// 			0
// 		}
// 	);

// 	ft_font_putstr_sdl(
// 		w, ft_itoa(20), \
// 		(t_ui_coord){ \
// 			w->sdl->font.g_sz * 21, \
// 			WIN_HEIGHT - w->sdl->font.f_sz * 1.5, \
// 			0
// 		}
// 	);

// 	TTF_CloseFont(w->sdl->font.ptr);
// }

/*
** **************************************************************************
**	void ft_editor_renderer(t_wolf3d *wolf)
**
**	Function that render all images to window.
** **************************************************************************
*/

void	ft_editor_renderer(t_wolf3d *wolf)
{
	ft_bzero(wolf->sdl->pixels, 4 * WIN_WIDTH * WIN_HEIGHT);
	SDL_SetRenderDrawColor(wolf->sdl->renderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(wolf->sdl->renderer);

	ft_editor_draw_line(wolf);
	ft_editor_draw_map_2d(wolf, wolf->sector);

	// ft_editor_threading(wolf); // sectors color fill
	// ft_editor_map_fill_sectors(wolf);

	if (ft_editor_check_event_area_map(wolf, wolf->mouse_pos))
	{
		ft_editor_draw_mouse_vertex(wolf);
		if (wolf->sector_status == 1)
		{
			if (!ft_sector_check_sector(wolf, wolf->mouse_pos))
				ft_editor_sector_draw_line_to_vertex(wolf);
		}
	}

	SDL_UpdateTexture(wolf->sdl->text, 0, wolf->sdl->pixels, WIN_WIDTH * 4);
	SDL_RenderCopy(wolf->sdl->renderer, wolf->sdl->text, NULL, NULL);
	ft_editor_font_draw_sector_list(wolf, wolf->sector, 0); // draw sector list
	// TTF_CloseFont(wolf->sdl->font.ptr);
	SDL_RenderPresent(wolf->sdl->renderer);
}