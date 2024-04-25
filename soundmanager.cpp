/***********************************************************************
 * File: soundmanager.cpp
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: play sound
***********************************************************************/

#include "soundmanager.h"

//Singleton pattern
//instance of the class
SoundManager* SoundManager::instance = NULL;

//Intent: constructor
//Pre: nothing
//Post: set up sound
SoundManager::SoundManager()
{
    //set up sound
    sound_bgm = new QSoundEffect;
    sound_finish = new QSoundEffect;
    sound_click = new QSoundEffect;

    //set url
    sound_bgm->setSource(BGM_SOUND_WAV);
    sound_finish->setSource(FINISH_SOUND_WAV);
    sound_click->setSource(CLICK_SOUND_WAV);

    //set volume
    sound_bgm->setVolume(BGM_ORIGIN_VOLUME);
    sound_finish->setVolume(FINISH_ORIGIN_VOLUME);
    sound_click->setVolume(CLICK_ORIGIN_VOLUME);

    //set loop
    sound_bgm->setLoopCount(QSoundEffect::Infinite);
}

//Intent: get the instance
//Pre: nothing
//Post: return the instance, if it doesn't exist, create it
SoundManager* SoundManager::getInstance(){
    if(instance == NULL){
        instance = new SoundManager();
    }
    return instance;
}

//Intent: play sound of bgm
//Pre: nothing
//Post: play the sound of bgm
void SoundManager::playBgm(){
    sound_bgm->play();
}

//Intent: play sound of finish
//Pre: nothing
//Post: play the sound of finish
void SoundManager::playFinish(){
    sound_finish->play();
}

//Intent: play sound of click
//Pre: nothing 
//Post: play the sound of click
void SoundManager::playClick(){
    sound_click->stop();
    sound_click->play();
}

//Intent: stop sound of bgm
//Pre: nothing
//Post: stop the sound of bgm
void SoundManager::stopBgm(){
    sound_bgm->stop();
}

//Intent: set volume
//Pre: double
//Post: set all volume to double v
void SoundManager::setVolume(double v){
    sound_bgm->setVolume(v * BGM_ORIGIN_VOLUME);
    sound_finish->setVolume(v * FINISH_ORIGIN_VOLUME);
    sound_click->setVolume(v * CLICK_ORIGIN_VOLUME);
}
