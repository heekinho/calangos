/*
 * gameSession.cxx
 * Created on: 03/06/2012
 * Author: heekinho
 */

#include "gameSession.h"

#include "audioRepository.h"
#include "modelRepository.h"
#include "imageRepository.h"
#include "timeControl.h"
#include "player.h"
#include "debugTools.h"
#include "guiManager.h"
#include "world.h"

#define VERIFY_REFERENCES(member_name) \
	if(member_name.is_null()) \
		simdunas_cat.debug() << #member_name << " is null!" << endl; \
	else \
		simdunas_cat.debug() << "refcount of " << #member_name << " is: " << member_name->get_ref_count() << endl;


GameSession::GameSession() {
	// TODO Auto-generated constructor stub

}

GameSession::~GameSession() {
	// TODO Auto-generated destructor stub
}

void GameSession::verify_references(){
//	simdunas_cat.debug() << "_debug_tools" << _debug_tools->get_ref_count()is_null() << endl;
	VERIFY_REFERENCES(_debug_tools);
}
