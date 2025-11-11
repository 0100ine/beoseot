#ifndef IDOLA_INPUTS_HPP
#define IDOLA_INPUTS_HPP

#include "idola/inputs/keyboard.hpp"
#include <SDL3/SDL_events.h>
#include <memory>

namespace idola {
    class inputs {
    public:
        inputs();
        ~inputs() = default;

        void handle_events(const SDL_Event& event);
        void update();

        [[nodiscard]] const std::unique_ptr<keyboard>& get_keyboard() const;

    private:
        std::unique_ptr<keyboard> m_keyboard;
    };
}

#endif //IDOLA_INPUTS_HPP