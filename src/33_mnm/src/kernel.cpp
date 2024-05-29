extern "C"{
    #include "libc/system.h"
    #include "memory.h"
    #include "common.h"
    #include "interrupts.h"
    #include "input.h"
    #include "pit.h"
    #include "monitor.h"

    #include "song.h"

}

// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}


SongPlayer* create_song_player() {
    auto* player = new SongPlayer();
    player->play_song = play_song_impl;
    return player;
}




extern "C" int kernel_main(void);

int kernel_main(){

    Song* songs[] = {

        new Song({battlefield_1942_theme, sizeof(battlefield_1942_theme) / sizeof(Note)}),
        new Song({starwars_theme, sizeof(starwars_theme) / sizeof(Note)}),
        new Song({music_1, sizeof(music_1) / sizeof(Note)}),
        new Song({music_6, sizeof(music_6) / sizeof(Note)}),
        new Song({music_5, sizeof(music_5) / sizeof(Note)}),
        new Song({music_4, sizeof(music_4) / sizeof(Note)}),
        new Song({music_3, sizeof(music_3) / sizeof(Note)}),
        new Song({music_2, sizeof(music_2) / sizeof(Note)})
    };
    uint32_t n_songs = sizeof(songs) / sizeof(Song*);

    // Create a song player and play each song
    SongPlayer* player = create_song_player();
    for(uint32_t i = 0; i < n_songs; i++) {
        printf("Playing Song...\n");
        player->play_song(songs[i]);
        printf("Finished playing the song.\n");
    }


malloc(100);

while(true){
    int counter = 0;
       while(true){
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        sleep_busy(1000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);
        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
 };
 };
}