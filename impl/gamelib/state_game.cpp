#include "state_game.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <random/random.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <state_menu.hpp>
#include <tweens/tween_alpha.hpp>

void StateGame::doInternalCreate()
{
    m_world = std::make_shared<jt::Box2DWorldImpl>(jt::Vector2f { 0.0f, 0.0f });

    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;
    using jt::TweenAlpha;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);

    m_bees = std::make_shared<jt::ObjectGroup<Bee>>();
    add(m_bees);

    m_player = std::make_shared<Player>();
    add(m_player);

    spawnBee();

    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here
        m_hud->getObserverBeesCount()->notify(m_bees->size());
        //        m_hud->getObserverTimer()->notify(m_timer);

        m_timer -= elapsed;

        if (m_timer <= 0.0f) {
            spawnBee();
            m_timer = 5.0f;
        }
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
}

void StateGame::doInternalDraw() const
{
    m_background->draw(renderTarget());
    drawObjects();
    m_vignette->draw();
    m_hud->draw();
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    getGame()->stateManager().switchState(std::make_shared<StateMenu>());
}
std::string StateGame::getName() const { return "Game"; }

void StateGame::spawnBee()
{
    auto bee = std::make_shared<Bee>();
    auto const margin = 64;
    bee->setCenterPosition(jt::Random::getRandomPointIn(jt::Rectf {
        margin, margin, GP::GetScreenSize().x - margin, GP::GetScreenSize().y - margin }));
    add(bee);
    m_bees->push_back(bee);
}
