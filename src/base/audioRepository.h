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


class audioRepository {
public:

    static audioRepository* get_instance();
    void load_audio();
    void add_audio(const string &name, const string &path);
    static void play_sound(const string &name);
    PT(AudioManager) get_audioManager();

    virtual ~audioRepository();
private:

 audioRepository();
 static audioRepository *instance;
 std::map <string,  PT(AudioSound)> audio;
 PT(AudioManager) AM;
 PT(AudioSound) sound;


};

#endif	/* AUDIOREPOSITORY_H */

