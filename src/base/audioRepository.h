/* 
 * File:   audioRepository.h
 * Author: fladmy
 *
 * Created on 21 de Fevereiro de 2011, 11:24
 */

#ifndef AUDIOREPOSITORY_H
#define	AUDIOREPOSITORY_H
#include <string>
#include <map>
#include "audioManager.h"
#include "audioSound.h"

using std::string;


class AudioRepository : public ReferenceCount {
public:

	static const string BITE;
	static const string BITE_FAIL;
	static const string MOUSE_ON;
	static const string MOUSE_CLICK;
	static const string HEART_BEAT;
	static const string WARNING;
	static const string PREDATOR_HIT;
	static const string REPROD_SUCCESS;
	static const string REPROD_FAIL;
	static const string BOBBING;
	static const string FROG;
	static const string DASH;
	static const string RUNNING;
	static const string DAY_SOUND;
	static const string NIGHT_SOUND;
	static const string RAIN_SOUND;

	AudioRepository();
    void load_audio();
    void add_audio(const string &name, const string &path);
    void add_bgm(const string &name, const string &path);
    void play_sound(const string &name, bool unique = false, float volume = 1);
    void play_bgm(const string &name, int loops = 1, float volume = 1);
    void pause_bgm();
    void unpause_bgm();
    void play_bgm_infinitely(const string& name, float volume = 1);
    void stop_bgm(const string& name);
    PT(AudioManager) get_audioManager();
    PT(AudioSound) get_audio(string name);
    PT(AudioSound) get_bgm(string name);

    static AsyncTask::DoneStatus sound_finished(GenericAsyncTask* task, void* data);
    static AsyncTask::DoneStatus bgm_finished(GenericAsyncTask* task, void* data);
    static void bgm_end(const Event*, void *data);

    static bool playing;
    static int loops_remaining;

    virtual ~AudioRepository();
private:

 std::map <string,  PT(AudioSound)> audio;
 std::map <string,  PT(AudioSound)> bgm;
 PT(AudioManager) AM;
 PT(AudioManager) bgm_AM;
 PT(AudioSound) current_bgm;
 static bool is_stopped;
 bool using_security_loop;
 float position_before_stop;

};

#endif	/* AUDIOREPOSITORY_H */

