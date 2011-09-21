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

	AudioRepository();
    void load_audio();
    void add_audio(const string &name, const string &path);
    void play_sound(const string &name, bool unique = false, float volume = 1);
    PT(AudioManager) get_audioManager();
    PT(AudioSound) get_audio(string name);

    static AsyncTask::DoneStatus finished_sound(GenericAsyncTask* task, void* data);

    static bool playing;

    virtual ~AudioRepository();
private:

 std::map <string,  PT(AudioSound)> audio;
 PT(AudioManager) AM;
 PT(AudioSound) sound;

};

#endif	/* AUDIOREPOSITORY_H */

