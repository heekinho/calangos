/*
 * gameSession.h
 * Created on: 03/06/2012
 * Author: heekinho
 */

#ifndef GAMESESSION_H
#define GAMESESSION_H

#include "referenceCount.h"
#include "pointerTo.h"

class AudioRepository;
class ModelRepository;
class ImageRepository;
class TimeControl;
class Player;
class DebugTools;
class GuiManager;
class World;

class GameSession : public ReferenceCount {
public:
	GameSession();
	virtual ~GameSession();

	PT(World) world() const;

	PT(DebugTools) _debug_tools;

	PT(AudioRepository) _audio_repository;
	PT(ModelRepository) _model_repository;
	PT(ImageRepository) _image_repository;

	PT(GuiManager) _gui_manager;
	PT(TimeControl) _time_control;

	PT(World) _world;

	PT(Player) _player;

	void verify_references();
};

#endif /* GAMESESSION_H */
