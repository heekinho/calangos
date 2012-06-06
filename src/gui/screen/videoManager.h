/*
 * videoManager.h
 * Created on: Apr 22, 2011
 * Author: jonatas
 */

#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "simdunas.h"
#include "audioSound.h"
#include "audioManager.h"
#include "movieTexture.h"
#include "cardMaker.h"
#include "string"

class VideoManager : public TypedReferenceCount {
public:
	VideoManager();
	virtual ~VideoManager();

	PT(AudioManager) get_audio_manager();
	PT(AudioSound) get_audio_sound();
	static bool is_playing();

	void play_video(const string &path);
	static void stop_video(const Event*, void* data);

private:
	void play(const string &path);
	void stop();

	PT(AudioSound) audio_sound;
	PT(AudioManager) audio_manager;
	PT(MovieTexture) movie_texture;
//	CardMaker* card_maker;
	NodePath np_card_maker;
	static bool playing;
};

#endif /* VIDEOMANAGER_H */
