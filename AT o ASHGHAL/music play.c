#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void init_audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to initialize SDL audio: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer Error: %s\n", Mix_GetError());
        exit(1);
    }
}

void play_music(const char *file) {
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, -1); // Play the music in a loop
}

void stop_music() {
    Mix_HaltMusic();
    Mix_CloseAudio();
}

int main() {
    init_audio();

    play_music("c418_-_aria_math.mp3");

    // Simulate game activity
    SDL_Delay(10000); // Play music for 10 seconds

    stop_music();

    return 0;
}
