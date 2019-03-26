#ifndef LEARNCPP_INPUTHANDLER_H
#define LEARNCPP_INPUTHANDLER_H

#include <functional>
#include <map>
#include <vector>

#include <SDL.h>

class InputHandler {
public:
    InputHandler() : keyboardState{SDL_GetKeyboardState(nullptr)} { };
    bool handle();
    void register_action_callback(SDL_Keycode keycode, std::function<void()> callback, void* unregisterHandle);
    void register_state_callback(SDL_Keycode keycode, std::function<void()> callback, void* unregisterHandle);
    void unregister_callback(void* unregisterHandle);
    bool is_down(SDL_Keycode keycode);
private:
    std::multimap<SDL_Keycode, std::pair<std::function<void()>, void*>> action_callbacks;
    std::multimap<SDL_Keycode, std::pair<std::function<void()>, void*>> state_callbacks;
    std::vector<void*> toBeRemoved;
    const Uint8 *keyboardState;
    void hit(SDL_Keycode keycode);
    void remove_callback(void* unregisterHandle);
    void handle_states();
};


#endif //LEARNCPP_INPUTHANDLER_H
