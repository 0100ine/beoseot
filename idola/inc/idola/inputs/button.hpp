#ifndef IDOLA_BUTTON_STATE_HPP
#define IDOLA_BUTTON_STATE_HPP

namespace idola {
    enum class BUTTON_STATE {
        IDLE,
        RELEASED,
        PRESSED,
        HELD
    };

    struct button {
        BUTTON_STATE state;

        void update(bool pressed);

        [[nodiscard]] bool is_up() const;
        [[nodiscard]] bool is_down() const;
        [[nodiscard]] bool is_held() const;
        [[nodiscard]] bool is_idle() const;
    };

    static BUTTON_STATE operator |= (const BUTTON_STATE& left, const BUTTON_STATE& right) {
        if (left == BUTTON_STATE::IDLE) {
            return right;
        }

        if (left == BUTTON_STATE::PRESSED) {
            if (right == BUTTON_STATE::HELD) {
                return BUTTON_STATE::HELD;
            }
            return left;
        }

        if (left == BUTTON_STATE::RELEASED) {
            if (right == BUTTON_STATE::PRESSED || right == BUTTON_STATE::HELD) {
                return right;
            }
            return left;
        }

        return left;
    }
}
#endif //IDOLA_BUTTON_STATE_HPP