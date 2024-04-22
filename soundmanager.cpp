#include "soundmanager.h"

SoundManager* SoundManager::instance = NULL;

SoundManager::SoundManager()
{
    sound_bgm = new QSoundEffect;
    sound_finish = new QSoundEffect;
    sound_click = new QSoundEffect;

    sound_bgm->setSource(BGM_SOUND_WAV);
    sound_finish->setSource(FINISH_SOUND_WAV);
    sound_click->setSource(CLICK_SOUND_WAV);

    sound_bgm->setVolume(BGM_ORIGIN_VOLUME);
    sound_finish->setVolume(FINISH_ORIGIN_VOLUME);
    sound_click->setVolume(CLICK_ORIGIN_VOLUME);

    sound_bgm->setLoopCount(QSoundEffect::Infinite);
}

SoundManager* SoundManager::getInstance(){
    if(instance == NULL){
        instance = new SoundManager();
    }
    return instance;
}

void SoundManager::playBgm(){
    sound_bgm->play();
}

void SoundManager::playFinish(){
    sound_finish->play();
}

void SoundManager::playClick(){
    sound_click->stop();
    sound_click->play();
}

void SoundManager::stopBgm(){
    sound_bgm->stop();
}

void SoundManager::setVolume(double v){
    sound_bgm->setVolume(v * BGM_ORIGIN_VOLUME);
    sound_finish->setVolume(v * FINISH_ORIGIN_VOLUME);
    sound_click->setVolume(v * CLICK_ORIGIN_VOLUME);
}
