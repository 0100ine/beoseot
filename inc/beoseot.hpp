#ifndef BEOSEOT_BEOSEOT_HPP
#define BEOSEOT_BEOSEOT_HPP

#include "game_states/title_state.hpp"
#include <idola/game.hpp>
#include <memory>

namespace bst {

    enum class GAME_STATE {
        TITLE,
        LOADING,
        EXPLORE,
        COMBAT
    };

    class beoseot : public idola::game {
    public:
        beoseot(const idola::game_config &config, SDL_GPUShaderFormat shader_format);
        ~beoseot() override;

        void set_state(const std::shared_ptr<game_state> &state);

    protected:
        void init() override;
        void fixed_step(const idola::game_delta &delta) override;
        void step(const idola::game_delta &delta) override;
        void draw() override;

    private:
        std::shared_ptr<game_state> m_current_state;
    };
}

#endif //BEOSEOT_BEOSEOT_HPP