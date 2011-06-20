/*
 * audioController.h
 *
 *  Created on: 14/06/2011
 *      Author: jonatas
 */

#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include "pandaFramework.h"
#include "audioRepository.h"
#include "frog.h"

class AudioController : public ReferenceCount {
public:
	virtual ~AudioController();

	static PT(AudioController) get_instance();

	PT(AudioRepository) get_audio_repository();
	void only_play(string sound_name);
	void frog(PT(Frog));
	void bobbing();
	void warning_temp(double intern_temp, double extern_temp, double min_temp, double max_temp);
	void warning_hydrat(double hydrat, double min_hydrat);
	void heart_beat(double energy, double min_energy);
	static AsyncTask::DoneStatus finish_frog_delay(GenericAsyncTask* task, void* data);

private:
	AudioController();
	static PT(AudioController) instance;
	PT(AudioRepository) audio_repository;
	bool frog_delay;
};

#endif /* AUDIOCONTROLLER_H */
