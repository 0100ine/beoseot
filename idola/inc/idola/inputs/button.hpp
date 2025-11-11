#ifndef IDOLA_BUTTON_BASE_HPP
#define IDOLA_BUTTON_BASE_HPP

#include "button_state.hpp"

namespace idola {
    struct button {
        button();
        virtual ~button() = default;

        [[nodiscard]] bool is_released() const;
        [[nodiscard]] bool is_pressed() const;
        [[nodiscard]] bool is_up() const;
        [[nodiscard]] bool is_down() const;
        [[nodiscard]] bool is_idle() const;
        [[nodiscard]] bool is_held() const;

        void update();
        [[nodiscard]] virtual bool check_pressed() const = 0;

        BUTTON_STATE state;
    };
}

#endif //IDOLA_BUTTON_BASE_HPP