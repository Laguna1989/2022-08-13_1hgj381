#include "hud.hpp"
#include <color/color.hpp>
#include <game_interface.hpp>
#include <hud/score_display.hpp>

std::shared_ptr<ObserverInterface<int>> Hud::getObserverBeesCount() const
{
    return m_scoreP1Display;
}
std::shared_ptr<ObserverInterface<int>> Hud::getObserverLives() const { return m_scoreP2Display; }

void Hud::doCreate()
{
    m_scoreBeesText = std::make_shared<jt::Text>();
    m_scoreBeesText->loadFont("assets/font.ttf", 16, renderTarget());
    m_scoreBeesText->setColor(jt::Color { 248, 249, 254 });
    m_scoreBeesText->update(0.0f);
    m_scoreBeesText->setTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreBeesText->setPosition({ 10, 4 });

    m_scoreP1Display = std::make_shared<ScoreDisplay>(m_scoreBeesText, "Bees: ");

    m_scoreTimer = std::make_shared<jt::Text>();
    m_scoreTimer->loadFont("assets/font.ttf", 16, renderTarget());
    m_scoreTimer->setColor(jt::Color { 248, 249, 254 });
    m_scoreTimer->update(0.0f);
    m_scoreTimer->setTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreTimer->setPosition({ 600 / 2 - 10, 4 });

    m_scoreP2Display = std::make_shared<ScoreDisplay>(m_scoreTimer, "Timer: ");
}

void Hud::doUpdate(float const elapsed)
{
    m_scoreBeesText->update(elapsed);
    m_scoreTimer->update(elapsed);
}

void Hud::doDraw() const
{
    m_scoreBeesText->draw(renderTarget());
    m_scoreTimer->draw(renderTarget());
}
