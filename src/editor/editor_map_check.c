/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:45:52 by dorange-          #+#    #+#             */
/*   Updated: 2020/02/07 17:27:58 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** **************************************************************************
**	int ft_check_point_in_sector_line_diameter(t_sector *s, t_vector3 v, \
**		double d)
**
**
** **************************************************************************
*/

int		ft_check_point_in_sector_line_diameter(t_sector *s, t_vector3 v, \
			double d)
{
	int		i;
	int		vtx1_n;
	int		vtx2_n;
	int		count;

	i = 0;
	count = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;
		if (ft_check_point_in_line_segment_diameter(\
			v, *s->vertex[vtx1_n], *s->vertex[vtx2_n], d))
			return (i);
		i++;
	}
	return (-1);
}

/*
** **************************************************************************
**	int ft_search_point_in_sector_line_diameter(void *a, t_vector3 v, \
**	double d)
**
**
** **************************************************************************
*/

int		ft_search_point_in_sector_line_diameter(void *a, \
			t_vector3 v, double d)
{
	t_wolf3d	*w;
	t_list		*list;
	t_sector	*sector;
	int			i;

	w = (t_wolf3d*)a;
	list = w->sector;
	i = 0;
	while (list)
	{
		sector = list->content;
		if (sector->status == 1)
		{
			if (!ft_check_point_in_sector(w, sector, v))
				if (ft_check_point_in_sector_line_diameter(sector, \
					v, d) != -1)
					return (sector->id);
		}
		list = list->next;
		i++;
	}
	return (0);
}

/*
** **************************************************************************
**	int ft_check_point_in_sector(t_wolf3d *w, t_sector *s, t_vector3 v)
**
**
** **************************************************************************
*/

int		ft_check_point_in_sector(t_wolf3d *w, t_sector *s, t_vector3 v)
{
	int				i;
	int				vtx1_n;
	int				vtx2_n;
	int				count;

	i = 0;
	count = 0;
	while (i < s->vertex_count)
	{
		vtx1_n = i;
		vtx2_n = (i + 1) % s->vertex_count;
		if (ft_compare_vertexes(v, *s->vertex[vtx1_n]) || \
			ft_compare_vertexes(v, *s->vertex[vtx2_n]))
			return (0);
		if (ft_check_point_in_line_segment(v, *s->vertex[vtx1_n], \
			*s->vertex[vtx2_n]))
			return (2);
		if (ft_check_line_segment_intersect_vector(\
			(t_vector3){-10.0, -10.0, 0, 0}, v, \
			*s->vertex[vtx1_n], *s->vertex[vtx2_n]))
			count++;
		i++;
	}
	return (count % 2);
}

/*
** **************************************************************************
**	int ft_search_point_in_sector(void *a, t_vector3 v)
**
**
** **************************************************************************
*/

int		ft_search_point_in_sector(void *a, t_vector3 v)
{
	t_wolf3d	*w;
	t_list		*list;
	t_sector	*sector;
	int			i;

	w = (t_wolf3d*)a;
	list = w->sector;
	i = 0;
	while (list)
	{
		sector = list->content;
		if (sector->status == 1)
		{
			if (ft_check_point_in_sector(w, sector, v))
				return (sector->id);
		}
		list = list->next;
		i++;
	}
	return (0);
}

/*
** **************************************************************************
**	int ft_new_editor_map_check_area(t_wolf3d *w)
**
**
** **************************************************************************
*/

int		ft_new_editor_map_check_area(t_wolf3d *w)
{
	t_vector3	vec1;
	t_vector3	vec2;
	t_sector	*s;
	t_vector3	pos;

	if (w->sector == NULL)
		return (1);
	pos = ft_gui_map_coord_to_vertex(w, w->gui.mouse_pos);
	if (ft_search_point_in_sector(w, pos))
		return (0);
	s = w->sector->content;
	if (s->status == 1 || s->vertex_count < 3)
		return (1);
	vec1 = ft_vec3_create(s->vertex[s->vertex_count - 1], &pos);
	vec2 = ft_vec3_create(s->vertex[s->vertex_count - 2], \
		s->vertex[s->vertex_count - 1]);
	if (ft_vxs_vector(vec1, vec2) > 0.0)
		return (0);
	vec2 = ft_vec3_create(s->vertex[0], s->vertex[s->vertex_count - 1]);
	if (ft_vxs_vector(vec1, vec2) > 0.0)
		return (0);
	if (ft_check_line_segment_intersect_vector(*s->vertex[1], *s->vertex[0], \
		*s->vertex[s->vertex_count - 1], pos))
		return (0);
	return (1);
}
