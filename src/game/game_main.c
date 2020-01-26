//
// Created by Nymphadora Shelly on 04/12/2019.
//
#include "doom.h"

typedef	struct		s_new_temp
{
    t_new_sub_ev se;
    t_new_mouse ms;
    t_new_player pl;
    t_new_others ot;
    t_new_sect_ops op;
	t_new_wolf3d w;
}					t_new_temp;

void player_init(t_new_player *pl, t_new_xy *v, float *angle, int *n)//init data for LoadData function
{
    //player = (struct player) { {v->x, v->y, 0}, {0,0,0}, *angle,0,0,0, n };
    pl->where.x = v->x;
    pl->where.y = v->y;
    pl->where.z = 0;
    pl->velocity.x = 0;
    pl->velocity.y = 0;
    pl->velocity.z = 0;
    pl->angle = *angle;
    pl->anglesin = 0;
    pl->anglecos = 0;
    pl->yaw = 0;
    pl->sector = *n;
	pl->ceil.nyceil = 0;
	pl->floor.nyfloor = 0;
	//If it's partially behind the player, clip it against player's view frustrum
	pl->nearz = 1e-4f;
	pl->farz = 5;
	pl->nearside = 1e-5f;
	pl->farside = 20.f;
	pl->door_all = -1;
	pl->but_all = -1;
	pl->lvl = NULL;
}

void UnloadData(t_new_player *pl)
{
	int i;

	i = -1;
	//better use free(pl);
	while (++i < pl->sectors_nb)
		free(pl->sectors[i].vertex);
	i == 2 ? i = 3 : i;
	while (++i < pl->sectors_nb)
		free(pl->sectors[i].neighbors);
    free(pl->sectors);
    pl->sectors = NULL;
    pl->sectors_nb = 0;
}

// //vline: Draw a vertical line on screen, with a different color pixel in top & bottom
// void vline(int x, int y1,int y2, int top,int middle,int bottom, t_new_player *pl)
// {
//     int	*pix;

// 	pix = (int*)pl->pixels;
//     y1 = clamp(y1, 0, WIN_H - 1);
//     y2 = clamp(y2, 0, WIN_H - 1);
//     if(y2 == y1)
//         pix[y1* WIN_W + x] = middle;
//     else if(y2 > y1)
//     {
//         pix[y1 * WIN_W + x] = top;
//         for(int y= y1 + 1; y < y2; ++y)
//             pix[y * WIN_W + x] = middle;
//         pix[y2 * WIN_W + x] = bottom;
//     }
// }

//vline: Draw a vertical line on screen, with a different color pixel in top & bottom
void vline(int x, int y1,int y2, int top,int middle,int bottom, SDL_Surface* surface)
{
    int	*pix;

	pix = (int*)surface->pixels;
    y1 = clamp(y1, 0, WIN_H - 1);
    y2 = clamp(y2, 0, WIN_H - 1);
    if(y2 == y1)
        pix[y1* WIN_W + x] = middle;
    else if(y2 > y1)
    {
        pix[y1 * WIN_W + x] = top;
        for(int y= y1 + 1; y < y2; ++y)
            pix[y * WIN_W + x] = middle;
        pix[y2 * WIN_W + x] = bottom;
    }
}

void	ft_game_redraw(void *d, t_list *dom)
{
	t_wolf3d	*w;
	t_new_temp	*data;

	w = (t_wolf3d*)d;
	data = w->new_data;

	data->pl.srf = w->sdl->srf;
	// data->pl.pixels = w->sdl->pixels;

	// data->pl.srf = w->sdl.surf;

	// data->pl.srf = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, 0, 0, 0, 0);
	// !data->pl.srf ? ft_putstr_fd(SDL_GetError(), 2) : 0;

	// w->sdl->pixels = data->pl.srf->pixels;
	// if (data->)
		// return;

	// if (data->pl.sect)

	engine_begin(&data->pl);




	//texture_init(&pl);

	// data->pl.texture = SDL_CreateTextureFromSurface(data->pl.rend, data->pl.srf);
	// data->pl.texture == NULL ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	// SDL_RenderCopy(data->pl.rend, data->pl.texture, 0, 0) != 0 ? ft_putstr_fd(SDL_GetError(), 2) : 0;
	// SDL_RenderPresent(data->pl.rend);
	// SDL_DestroyTexture(data->pl.texture);


	data->op.eye_h = data->se.ducking ? CROUCH_H : EYE_H;
	data->se.ground = !data->se.falling;
	events_jumps(&data->se, &data->pl, &data->op, &data->ot);
	motion_chk(&data->op, &data->pl, &data->ot, &data->se);
	motion_move_pl(0, 0, &data->pl);//Refresh Vectors. start movement in 0//if this line is in vectors_vel_dir slomaet programmy whe is running, is needed here
	events_new_mouse_move(&data->ms, &data->pl);//mouse aiming
	events_vel(&data->pl, &data->se, &data->ot);
	if (!events(&data->se, &data->pl))
		return ;
	door(&data->pl, &data->se);
}

void	ft_game_init(t_new_temp *data, char *path)
{
	data->pl.sectors_nb = 0;
    data->se.quit = 0;
    load_file(path, &data->pl);//load map and init typedef t_new_player data
    //ft_init_anim(&w);//gun
    // SDL_Window* window = NULL;
	// data->window = NULL;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        ft_error( "SDL could not initialize! SDL_Error: %s\n");
	// data->window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN );

	// if(data->window == NULL)
		// ft_error("Window could not be created! SDL_Error: %s\n");

	// SDL_UpdateWindowSurface(data->window);
	SDL_ShowCursor(SDL_DISABLE);//NOT SHOW MOUSE CURSOR
	data->se.wsad[0] = 0;
	data->se.wsad[1] = 0;
	data->se.wsad[2] = 0;
	data->se.wsad[3] = 0;
	data->se.falling = 1;
	data->se.ground = 0;
	data->ot.moving = 0;
	data->se.ducking = 0;
	data->ms.yaw = 0;
	//load_weapons(&wpn);
}

void	ft_game_gui_init_menu(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;

	ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){118, 18, 0}, \
	 	(t_gui_coord){144, 44, 0});
	// ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){116, 16, 0}, \
	//  	(t_gui_coord){516, 416, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/like.png");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_livescount", (t_gui_coord){150, 10, 0}, \
		(t_gui_coord){254, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_pistol", (t_gui_coord){216, 16, 0}, \
	 	(t_gui_coord){248, 48, 0});
	// ft_gui_elem_init(&elem->child, "win_hud_live", (t_gui_coord){116, 16, 0}, \
	//  	(t_gui_coord){516, 416, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_image(elem->child, "img/pistol.png");
	ft_gui_elem_set_parent(head, elem->child);

	ft_gui_elem_init(&elem->child, "win_hud_pistolcount", (t_gui_coord){250, 10, 0}, \
		(t_gui_coord){354, 50, 0});
	ft_gui_elem_set_color(elem->child, 0xffffff);
	ft_gui_elem_set_text(elem->child, "100", 16);
	ft_gui_elem_set_parent(head, elem->child);

	//pistol.png
}

void	ft_game_gui_init_hud(t_list *head)
{
	t_gui_elem	*elem;

	elem = head->content;
	ft_gui_elem_init(&elem->child, "win_hud", (t_gui_coord){100, 0, 0}, \
		(t_gui_coord){WIN_WIDTH - 100, 60, 0});
	// ft_gui_elem_set_color(elem->child, 0xbffd7c6e);
	ft_gui_elem_set_color(elem->child, 0xbf000000);
	ft_gui_elem_set_parent(head, elem->child);
	ft_game_gui_init_menu(elem->child);
}

void	ft_game_gui_init(t_wolf3d *w)
{
	// gui init element
	w->gui.redraw = 0;
	w->gui.redraw_elem = NULL;
	w->gui.search_elem = GUI_EVENT_OFF;
	w->gui.dom = NULL;
	w->gui.fonts = NULL;
	w->gui.mode = GUI_MD_ME;

	ft_gui_elem_init(&w->gui.dom, "win", (t_gui_coord){0, 0, 0}, \
		(t_gui_coord){WIN_WIDTH, WIN_HEIGHT, 0});
	ft_gui_elem_set_color(w->gui.dom, 0x000000);
	ft_gui_elem_set_redraw(w->gui.dom, ft_game_redraw);
	// ft_gui_elem_set_redraw_font(w->gui.dom, ft_game_render_font);
	ft_game_gui_init_hud(w->gui.dom);
}

int main(int ac, char **ag)
{
	t_wolf3d	w;
	t_new_temp	data;

	if (ac < 2 || ac > 2)
		ft_error("map error");

	ft_bzero(&data, sizeof(t_new_temp));

	ft_game_init(&data, ag[1]);

	w.sdl = sdl_init(w.sdl);
	ft_init_wolf(&w);
	ft_gui_init(&w);
	ft_game_gui_init(&w);

	w.new_data = &data;

	while (w.sdl->running)
	{
		ft_gui_events(&w);
		ft_gui_redraw(&w);
	}
	
	UnloadData(&data.pl);
	SDL_Quit();
    return (0);
}

// int main(int ac, char **ag)
// {
//     t_new_sub_ev se;
//     t_new_mouse ms;
//     t_new_player pl;
//     t_new_others ot;
//     t_new_sect_ops op;
// 	t_new_wolf3d w;

// 	pl.sectors_nb = 0;
//     w.weapon_texture = SDL_LoadBMP("Textures/pistol.bmp");
// 	if (ac < 2 || ac > 2)
//     {
//         // printf("map error.\n");
//         return (0);
//     }
//     se.quit = 0;
//     load_file(ag[1], &pl);

//     //ft_init_anim(&w);//gun
//     if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
//     {
//         // printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
//     }
//     else
//     {
//         pl.win = SDL_CreateWindow( "SDL Tutorial", 10, 10, WIN_W, WIN_H, SDL_WINDOW_SHOWN);

//         if( pl.win == NULL )
//         {
//             // printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
//         }
//         else
//             {
//             pl.rend = SDL_CreateRenderer(pl.win,-1, SDL_RENDERER_ACCELERATED);
//             SDL_SetRenderDrawColor(pl.rend, 0xFF, 0xFF, 0xFF, 0xFF);
// 			SDL_SetRelativeMouseMode(1);
//             //SDL_ShowCursor(SDL_DISABLE);//NOT SHOW MOUSE CURSOR
//             se.wsad[0] = 0;
//             se.wsad[1] = 0;
//             se.wsad[2] = 0;
//             se.wsad[3] = 0;
//             se.falling = 1;
//             se.ground = 0;
//             ot.moving = 0;
//             se.ducking = 0;
//             ms.yaw = 0;
// 			//pl.textures = load_textures(&pl);
//             while (!se.quit)
//             {
// 				pl.srf = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, 0, 0, 0, 0);
// 				!pl.srf ? ft_putstr_fd(SDL_GetError(), 2) : 0;

// 				engine_begin(&pl);

// 				//texture_init(&pl);

// 				pl.texture = SDL_CreateTextureFromSurface(pl.rend, pl.srf);
// 				pl.texture == NULL ? ft_putstr_fd(SDL_GetError(), 2) : 0;
// 				SDL_RenderCopy(pl.rend, pl.texture, 0, 0) != 0 ? ft_putstr_fd(SDL_GetError(), 2) : 0;
// 				SDL_RenderPresent(pl.rend);
// 				SDL_DestroyTexture(pl.texture);
				

// 				op.eye_h = se.ducking ? CROUCH_H : EYE_H;
// 				se.ground = !se.falling;
// 				events_jumps(&se, &pl, &op, &ot);
// 				motion_chk(&op, &pl, &ot, &se);
// 				motion_move_pl(0, 0, &pl);//Refresh Vectors. start movement in 0//if this line is in vectors_vel_dir slomaet programmy whe is running, is needed here
// 				events_new_mouse_move(&ms, &pl);//mouse aiming
// 				events_vel(&pl, &se, &ot);
// 				if (!events(&se, &pl))
// 					return(0);
// 				door(&pl, &se);
// 			}
			
//             UnloadData(&pl);
//             SDL_Quit();
//         }
//     }
//     return 0;
// }