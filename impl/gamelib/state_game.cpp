#include "state_game.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <math_helper.hpp>
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
    //    add(m_player);
    // TODO fix this
    m_player->setGameInstance(getGame());
    m_player->create();

    spawnBee();

    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_player->update(elapsed);
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here
        m_hud->getObserverBeesCount()->notify(m_bees->size());
        //        m_hud->getObserverTimer()->notify(m_timer);

        m_timer -= elapsed;

        if (m_timer <= 0.0f) {
            spawnBee();
            m_timer = 5.0f;
        }

        // check player bee collision
        for (auto const& bee : *m_bees) {
            auto b = bee.lock();
            if (!b->canHurtPlayer()) {
                continue;
            }

            auto const bp = b->m_sprite->getPosition();
            auto const pp = m_player->m_shape->getPosition();

            auto const diff = bp - pp;
            auto const l = jt::MathHelper::length(diff);
            if (l <= 16 + 18) {
                b->reset();
                m_lives--;
                m_hud->getObserverLives()->notify(m_lives);

                if (m_lives <= 0) {
                    endGame();
                }
            }
        }
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
}

void StateGame::doInternalDraw() const
{
    m_background->draw(renderTarget());
    drawObjects();
    m_player->draw();
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
    auto s = std::make_shared<StateMenu>();
    s->setScore(m_bees->size());
    getGame()->stateManager().switchState(s);
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
