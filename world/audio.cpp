#include "audio.h"
#include "../ui/ui.h"

// Constructor

Audio::Audio (UI* ui) : 

    gameUI (ui), 
    AudioPlaying (false),
    FirstTimeAudio (true),
    currentVolume (50) {

    // Initialize SDL
    
	SDL_Init (SDL_INIT_AUDIO);

    // Initialize SDL_mixer
    
	Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2048);

}

// Destructor

Audio::~Audio () {

	// Ending Audio

	Mix_HaltMusic ();
	Mix_CloseAudio ();
	SDL_Quit ();

}

// Background Music

void Audio::PlayMusic (const string &filePath) {

	// sudo apt install libsdl2-dev
	// sudo apt install libsdl2-mixer-dev
	// #include <SDL2/SDL.h>
	// #include <SDL2/SDL_mixer.h>
	// -lSDL2 -lSDL2_mixer (In MakeFile LIBS)
	// This Function
	// 3 Exiting Lines at the end of main

    // Load the music file
    
	Mix_Music* music = Mix_LoadMUS (filePath.c_str());
    
	if (!music) {
    
	    cerr << "Failed to load music file: " << filePath << ". Mix Error: " << Mix_GetError () << endl;
        Mix_CloseAudio ();
        SDL_Quit ();
        return;
    
	}

    // Music being played in a loop 
	
	Mix_PlayMusic (music, -1);
	Mix_VolumeMusic (currentVolume);  // Set initial volume

    cout << endl << endl << "Background music playing: " << filePath << endl;

}

// Toggles Audio On and Off

void Audio::ToggleAudio () {

	if (FirstTimeAudio && !AudioPlaying) {

		PlayMusic ("media/guts.wav");

		FirstTimeAudio = false;

		AudioPlaying = true;

		return;

	}

    else if (AudioPlaying) {

        Mix_PauseMusic ();
        cout << "Audio paused." << endl;

    } 
	
	else {

        Mix_ResumeMusic ();
        cout << "Audio resumed." << endl;

    }

    // Toggle the state

    AudioPlaying = !AudioPlaying;

}

// Increase Volume of Music

void Audio::IncreaseVolume () {

    currentVolume += 16;

    if (currentVolume > MIX_MAX_VOLUME) {
    
	    currentVolume = MIX_MAX_VOLUME;
    
	}

    Mix_VolumeMusic (currentVolume);
    
	cout << "Volume increased to: " << currentVolume << endl;

}

// Decrease Volume of Music

void Audio::DecreaseVolume () {

    currentVolume -= 16;

    if (currentVolume < 0) {
    
	    currentVolume = 0;
    
	}

    Mix_VolumeMusic (currentVolume);
    
	cout << "Volume decreased to: " << currentVolume << endl;

}

// Sound Effects

void Audio::SoundEffect (const string &soundPath) {

    Mix_Chunk* soundEffect = Mix_LoadWAV(soundPath.c_str());
    if (!soundEffect) {
        cerr << "Failed to load sound: " << Mix_GetError() << endl;
        return;
    }

    int channel = Mix_PlayChannel(-1, soundEffect, 0);
    if (channel == -1) {
        cerr << "Failed to play sound: " << Mix_GetError() << endl;
        Mix_FreeChunk(soundEffect);
        return;
    }

    Mix_Volume(channel, currentVolume);

    Mix_ChannelFinished([](int channel) {
        Mix_Chunk* chunk = Mix_GetChunk(channel);
        if (chunk) Mix_FreeChunk(chunk);
    });

}
