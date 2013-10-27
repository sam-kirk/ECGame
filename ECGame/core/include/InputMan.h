#pragma once
#ifndef INPUTMAN_H
#define INPUTMAN_H

#include "ec.h"

// The last entry in in the SDLkey enum, whose value will specify the enum size
#define SDLKEYCOUNT         SDLK_LAST

class InputMan
{
public:
    // Set the down status SDLKey, k, to true
    void set_key_down(SDLKey k);

    // Set the down status SDLKey, k, to false
    void set_key_up(SDLKey k);

    // Returns the down status of SDLKey, k
    bool get_key(SDLKey k);

    // Set the down status of all keys to false
    void release_all();

private:
    bool keys[SDLKEYCOUNT];
};

#endif