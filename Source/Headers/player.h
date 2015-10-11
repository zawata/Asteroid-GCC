#include "stdafx.h"
#include "iostream"

#ifndef _ANIM_LENGTH           //because normal variables arent working
#define _ANIM_LENGTH 17        //and im too lazy to figure out why
#endif

#ifndef PLAYER_H
#define PLAYER_H
class Player
{
private:
	const int player_width = 30;
public:
	//ALLEGRO_BITMAP *player_base = NULL;

	ALLEGRO_BITMAP *player_spritemap = NULL;
	ALLEGRO_BITMAP *player_flaming_sub[_ANIM_LENGTH];

	//ALLEGRO_PATH *player_resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

	struct attrib
	{
		float x_pos;
		float y_pos;
		int act_angle;
		int height;
		int width;
		int x_cen;
		int y_cen;
		float x_vec;
		float y_vec;
	};
	attrib traits;
	bool player_init()
	{
		/*this has problems...
		player_spritemap = al_load_bitmap(((std::string)al_path_cstr(player_resource_path, ALLEGRO_NATIVE_PATH_SEP)
		                                   + (std::string)((const char*)"/Resources/ship_smaller_flames.png")).c_str());
		major problems..*/
		//so for the mean time...
		player_spritemap = al_load_bitmap("C:/Users/Zach/Documents/GitHub/Asteroid-GCC/Resources/ship_smaller_flames.png");
		if (player_spritemap == NULL)
			return false;
		if (!init_anim_sprites())
			return false;
		traits.x_pos = 200;
		traits.y_pos = 200;
		traits.act_angle = 0;
		traits.height = al_get_bitmap_height(player_spritemap);
		traits.width = player_width;
		traits.x_cen = (traits.width / 2);
		traits.y_cen = (traits.height / 2);
		traits.x_vec = 0;
		traits.y_vec = 0;
		return true;
	}
	bool init_anim_sprites()
	{
		for (int i = 0; i < _ANIM_LENGTH; i++)
		{
			player_flaming_sub[i] = al_create_sub_bitmap(player_spritemap, i * player_width, 0, player_width, al_get_bitmap_height(player_spritemap));
			if (player_flaming_sub[i] == NULL)
			{
				std::cout << "executed" << std::endl;
				return false;
			}
		}
		return true;
	}
	void inline fix_angle()
	{
		traits.act_angle = traits.act_angle % 360;
		return;
	}
	void check_bounds(float s_width, float s_height)
	{
		if (traits.x_pos < 0 - traits.height)
		{
			traits.x_pos = s_width + traits.height;
		}
		else
		{
			if (traits.x_pos > s_width + traits.height)
			{
				traits.x_pos = 0 - traits.height;
			}
		}
		if (traits.y_pos < 0 - traits.height)
		{
			traits.y_pos = s_height + traits.height;
		}
		else
		{
			if (traits.y_pos > s_height + traits.height)
			{
				traits.y_pos = 0 - traits.height;
			}
		}
		return;
	}
	void destroy_anim_sprites()
	{
		for (int i = 0; i < _ANIM_LENGTH - 1; i++)
		{
			al_destroy_bitmap(player_flaming_sub[i]);
		}
		return;
	}
};
#endif