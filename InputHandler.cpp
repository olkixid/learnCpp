#include "InputHandler.h"

void InputHandler::register_action_callback(SDL_Keycode keycode, std::function<void()> callback, void* unregisterHandle) {
    action_callbacks.insert({keycode, {callback, unregisterHandle}});
}

void InputHandler::unregister_callback(void* unregisterHandle) {
    toBeRemoved.push_back(unregisterHandle);
}

void InputHandler::remove_callback(void* unregisterHandle) {
    for (auto it = action_callbacks.begin(); it != action_callbacks.end();) {
        if(it->second.second == unregisterHandle) {
            it = action_callbacks.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it = state_callbacks.begin(); it != state_callbacks.end();) {
        if(it->second.second == unregisterHandle) {
            it = state_callbacks.erase(it);
        }
        else {
            ++it;
        }
    }
}

void InputHandler::register_state_callback(SDL_Keycode keycode, std::function<void()> callback, void* unregisterHandle) {
    state_callbacks.insert({keycode, {callback, unregisterHandle}});
}


bool InputHandler::handle() {
    for (auto trash : toBeRemoved) {
        remove_callback(trash);
    }
    toBeRemoved.clear();

    bool quit{false};

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                hit(e.key.keysym.sym);
            default:
                break;
        }
    }

    handle_states();

    return quit;
}

void InputHandler::hit(SDL_Keycode keycode) {
    const auto& range = action_callbacks.equal_range(keycode);
    for (auto it = range.first; it != range.second; ++it)
    {
        it->second.first();
    }
}

bool InputHandler::is_down(SDL_Keycode keycode) {
    SDL_Scancode scancode{SDL_GetScancodeFromKey(keycode)};
    return keyboardState[scancode];
}

void InputHandler::handle_states() {
    for (const auto& entry : state_callbacks)
    {
        if (is_down(entry.first)) {
            entry.second.first();
        }
    }
}

