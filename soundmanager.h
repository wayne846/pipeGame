#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>

class SoundManager
{
    //Singleton pattern
    private:
        static SoundManager *instance;

        const QUrl CLICK_SOUND = QUrl("qrc:/click.mp3");
        const QUrl FINISH_SOUND = QUrl("qrc:/finish.mp3");
        const QUrl BGM_SOUND = QUrl("qrc:/prohibition.mp3");
        const QUrl CLICK_SOUND_WAV = QUrl("qrc:/click.wav");
        const QUrl FINISH_SOUND_WAV = QUrl("qrc:/finish.wav");
        const QUrl BGM_SOUND_WAV = QUrl("qrc:/prohibition.wav");

        const double BGM_ORIGIN_VOLUME = 0.15;
        const double FINISH_ORIGIN_VOLUME = 0.3;
        const double CLICK_ORIGIN_VOLUME = 0.5;

        QSoundEffect *sound_bgm;
        QSoundEffect *sound_finish;
        QSoundEffect *sound_click;

        SoundManager();

    public:
        static SoundManager* getInstance();

        void playBgm();
        void playFinish();
        void playClick();
        void stopBgm();

        void setVolume(double v);
};

#endif // SOUNDMANAGER_H
