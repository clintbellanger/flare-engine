/*
Copyright © 2011-2012 Clint Bellanger
Copyright © 2012 Igor Paliychuk
Copyright © 2013 Henrik Andersson
Copyright © 2012-2016 Justin Jacobs

This file is part of FLARE.

FLARE is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

FLARE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
FLARE.  If not, see http://www.gnu.org/licenses/
*/

/**
 * class Avatar
 *
 * Contains logic and rendering routines for the player avatar.
 */

#ifndef AVATAR_H
#define AVATAR_H

#include "CommonIncludes.h"
#include "Entity.h"
#include "Utils.h"

class Entity;
class Hazard;
class StatBlock;

class ActionData {
public:
	int power;
	unsigned hotkey;
	bool instant_item;
	FPoint target;

	ActionData()
		: power(0)
		, hotkey(0)
		, instant_item(false)
		, target(FPoint()) {
	}
};

class Avatar : public Entity {
private:
	class Step_sfx {
	public:
		std::string id;
		std::vector<std::string> steps;
	};

	void loadLayerDefinitions();
	bool pressing_move();
	void set_direction();
	void transform();
	void untransform();
	void setAnimation(std::string name);

	bool lockAttack;

	std::vector<Step_sfx> step_def;

	std::vector<SoundID> sound_steps;

	std::vector<AnimationSet*> animsets; // hold the animations for all equipped items in the right order of drawing.
	std::vector<Animation*> anims; // hold the animations for all equipped items in the right order of drawing.

	short body;

	bool transform_triggered;
	std::string last_transform;

	bool attack_cursor;

protected:
	virtual void resetActiveAnimation();

public:
	class Layer_gfx {
	public:
		std::string gfx;
		std::string type;
	};

	enum {
		MSG_NORMAL = 0,
		MSG_UNIQUE = 1
	};

	Avatar();
	~Avatar();

	void init();
	void loadGraphics(std::vector<Layer_gfx> _img_gfx);
	void loadStepFX(const std::string& stepname);

	void logic(std::vector<ActionData> &action_queue, bool restrict_power_use, bool npc);

	// transformation handling
	bool isTransforming() {
		return transform_triggered;
	}
	void checkTransform();

	void addRenders(std::vector<Renderable> &r);

	void logMsg(const std::string& str, int type);

	std::vector<std::string> layer_reference_order;
	std::vector<std::vector<unsigned> > layer_def;

	std::queue<std::pair<std::string, int> > log_msg;

	std::string attack_anim;
	bool setPowers;
	bool revertPowers;
	int untransform_power;
	StatBlock *hero_stats;
	StatBlock *charmed_stats;
	FPoint transform_pos;
	std::string transform_map;

	// vars
	Hazard *haz;
	int current_power;
	FPoint act_target;
	bool drag_walking;
	bool newLevelNotification;
	bool respawn;
	bool close_menus;
	bool allow_movement;
	std::vector<int> hero_cooldown;
	std::vector<int> power_cast_ticks;
	std::vector<int> power_cast_duration;
	FPoint enemy_pos; // positon of the highlighted enemy
	unsigned long time_played;
	bool questlog_dismissed;
};

#endif

