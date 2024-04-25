/***********************************************************************
 * File: soundmanager.h
 * Author: B112150536 B11215058
 * Create Date: 2024/04/24
 * Editor: B11215036
 * Update Date: 2024/04/25
 * Description: play sound
***********************************************************************/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>

class SoundManager
{
    //Singleton pattern
    private:
        //instance of the class
        static SoundManager *instance;

        //url of the sound
        const QUrl CLICK_SOUND = QUrl("qrc:/click.mp3");
        const QUrl FINISH_SOUND = QUrl("qrc:/finish.mp3");
        const QUrl BGM_SOUND = QUrl("qrc:/prohibition.mp3");
        const QUrl CLICK_SOUND_WAV = QUrl("qrc:/click.wav");
        const QUrl FINISH_SOUND_WAV = QUrl("qrc:/finish.wav");
        const QUrl BGM_SOUND_WAV = QUrl("qrc:/prohibition.wav");

        //origin volume of the sound
        const double BGM_ORIGIN_VOLUME = 0.15;
        const double FINISH_ORIGIN_VOLUME = 0.3;
        const double CLICK_ORIGIN_VOLUME = 0.5;

        //sound of the game
        QSoundEffect *sound_bgm;
        QSoundEffect *sound_finish;
        QSoundEffect *sound_click;

        SoundManager();

    public:
        //get the instance
        static SoundManager* getInstance();

        //play sound
        void playBgm();
        void playFinish();
        void playClick();
        void stopBgm();

        //set volume
        void setVolume(double v);
};

#endif // SOUNDMANAGER_H
