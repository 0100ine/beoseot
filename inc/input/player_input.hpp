#ifndef BEOSEOT_PLAYER_INPUT_HPP
#define BEOSEOT_PLAYER_INPUT_HPP

#include <idola/inputs/button.hpp>

namespace bst {
    struct player_input {
        const idola::button& forward;
        const idola::button& back;
        const idola::button& left;
        const idola::button& right;
    };
}

#endif //BEOSEOT_PLAYER_INPUT_HPP