#ifndef BEOSEOT_BEOSEOT_HPP
#define BEOSEOT_BEOSEOT_HPP

#include "game_states/title_state.hpp"
#include <idola/game.hpp>

namespace bst {
    class beoseot : public idola::game {
    public:
        beoseot(const idola::game_config &config, SDL_GPUShaderFormat shader_format);
        ~beoseot() override;

    protected:
        void init() override;
        void fixed_step(const idola::game_delta &delta) override;
        void step(const idola::game_delta &delta) override;
        void draw() override;
        
    private:
        std::unique_ptr<title_state> m_title_state;
    };
}

#endif //BEOSEOT_BEOSEOT_HPP