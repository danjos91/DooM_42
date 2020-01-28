/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map_parse2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:16:26 by tjuana            #+#    #+#             */
/*   Updated: 2020/01/28 15:30:02 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_new_xy	*ft_vertex_save(t_new_player *pl, t_new_xy *vertex)
{
	int	count;

	count = 2;
	pl->file.split = ft_strsplit(pl->file.ptr_my, '\t');
	while (pl->file.split[count] != NULL)
	{
		vertex[pl->file.i].y = ft_atoi(pl->file.split[1]);
		vertex[pl->file.i].x = ft_atoi(pl->file.split[count]);
		pl->file.i++;
		count++;
	}
	ft_2arrclean(&pl->file.split);
	return (vertex);
}

void		ft_sector_save(t_new_player *pl, t_new_xy *vertex)
{
	t_new_sector	*sector;
	int				number;

	sector = &pl->sectors[pl->file.count_sectors];
	number = pl->file.tmp[pl->file.count_sectors];
	pl->sectors[pl->file.count_sectors].npoints = pl->file.count_sector_vertex;
	sector->neighbors = ft_my_malloc(sizeof(char) * (number + 1));
	sector->vertex = ft_my_malloc(sizeof(t_new_xy) * number);
	sector->npoints = number;
	ft_fill_the_sector(sector, number, pl->file, vertex);
	pl->file.count_sectors++;
}

void		ft_fill_the_sector(t_new_sector *sector, int number, \
	t_file_read file, t_new_xy *vertex)
{
	int				v_c;
	int				s_c;

	file.split = ft_strsplit(file.ptr_my, '\t');
	sector->floor = ft_atoi(file.split[1]);
	sector->ceil = ft_atoi(file.split[2]);
	v_c = 1;
	s_c = 3;
	while (number--)
	{
		sector->vertex[v_c] = vertex[ft_atoi(file.split[s_c])];
		v_c++;
		s_c++;
	}
	sector->vertex[0] = vertex[ft_atoi(file.split[s_c - 1])];
	number = file.tmp[file.count_sectors];
	v_c = 0;
	while (number--)
	{
		sector->neighbors[v_c] = ft_atoi(file.split[s_c]);
		s_c++;
		v_c++;
	}
}

void		ft_player_save(t_new_player *pl)
{
	t_new_xy	v;
	int			angle;
	int			n;

	pl->file.split = ft_strsplit(pl->file.ptr_my, '\t');
	v.x = ft_atoi(pl->file.split[1]);
	v.y = ft_atoi(pl->file.split[2]);
	angle = ft_atoi(pl->file.split[3]);
	n = ft_atoi(pl->file.split[4]);
	player_init(pl, &v, &angle, &n);
	pl->where.z = pl->sectors[pl->sector].floor + EYE_H;
}

void		ft_level_save(t_new_player *pl)
{
	t_new_xy	v;
	int			angle;
	int			n;

	pl->file.split = ft_strsplit(pl->file.ptr_my, '\t');
	pl->lvl = pl->file.split[1];
}