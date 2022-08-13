#include "hud.hpp"
#include <color/color.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
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
    m_scoreBeesText->setColor(GP::PaletteFontFront());
    m_scoreBeesText->update(0.0f);
    m_scoreBeesText->setTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreBeesText->setPosition({ 10, 4 });

    m_scoreP1Display = std::make_shared<ScoreDisplay>(m_scoreBeesText, "Bees: ");

    m_scoreLives = std::make_shared<jt::Text>();
    m_scoreLives->loadFont("assets/font.ttf", 16, renderTarget());
    m_scoreLives->setColor(GP::PaletteFontFront());
    m_scoreLives->update(0.0f);
    m_scoreLives->setTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreLives->setPosition({ 600 / 2 - 10, 4 });

    m_scoreP2Display = std::make_shared<ScoreDisplay>(m_scoreLives, "Lives: ");
}

void Hud::doUpdate(float const elapsed)
{
    m_scoreBeesText->update(elapsed);
    m_scoreLives->update(elapsed);
}

void Hud::doDraw() const
{
    m_scoreBeesText->draw(renderTarget());
    m_scoreLives->draw(renderTarget());
}
