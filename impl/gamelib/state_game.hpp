#ifndef GAME_STATE_GAME_HPP
#define GAME_STATE_GAME_HPP

#include "object_group.hpp"
#include <bee.hpp>
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <hud/hud.hpp>
#include <player.hpp>
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class Shape;
class Sprite;
class Vignette;
} // namespace jt

class StateGame : public jt::GameState {
public:
    std::string getName() const override;

private:
    std::shared_ptr<jt::Shape> m_background;
    std::shared_ptr<jt::Vignette> m_vignette;
    std::shared_ptr<Hud> m_hud;
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    std::shared_ptr<jt::ObjectGroup<Bee>> m_bees;
    std::shared_ptr<Player> m_player;

    bool m_running { true };
    bool m_hasEnded { false };

    int m_lives { 4 };
    int m_scoreP2 { 0 };

    float m_timer { 5.0f };

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;

    void endGame();
    void createPlayer();

    void spawnBee();
};

#endif
