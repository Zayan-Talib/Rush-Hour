#ifndef AUDIO_H_
#define AUDIO_H_

#include "../utility/util.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class UI;

class Audio {

    private:
    
        UI* gameUI;

        int currentVolume;

        bool AudioPlaying;
        bool FirstTimeAudio;
        
    public:

        // Constructor

        Audio (UI* ui);

        // Destructor

        ~Audio ();

        // Draw

        void Draw ();
        void PrintKeys (unsigned char key);
        void NonPrintKeys (int key);

        // Audio

        void PlayMusic(const string& audioPath);
        void ToggleAudio ();
        void IncreaseVolume ();
        void DecreaseVolume ();

        // Sound Effects

        void SoundEffect (const string& soundPath);

};

#endif 