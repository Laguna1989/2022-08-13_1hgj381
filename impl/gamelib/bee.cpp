
#include "bee.hpp"
#include <random/random.hpp>
#include <iostream>

void Bee::setCenterPosition(jt::Vector2f const& centerPosition)
{
    m_centerPositon = centerPosition;
}

void Bee::doCreate()
{
    m_sprite = std::make_shared<jt::Sprite>("assets/bee.png", textureManager());
    m_sprite->setOffset(jt::OffsetMode::CENTER);

    m_timePhase = jt::Random::getFloat(0.0f, 50.0f);
    m_timeFrequ = jt::Random::getFloat(0.8f, 1.2f);
    m_rotationSpeedFactor = jt::Random::getFloatGauss(1.0f, 0.1f);
}
void Bee::doUpdate(float const elapsed)
{
    m_sprite->update(elapsed);

    auto const t = m_timeFrequ * getAge() + m_timePhase;
    auto const radius = 80;
    auto const r = radius + sin(t * 4) * 20;

    auto const rotationSpeed = 1.25f * m_rotationSpeedFactor;
    auto const x = r * sin(t * rotationSpeed);
    auto const y = r * cos(t * rotationSpeed);

    m_sprite->setPosition(jt::Vector2f { x, y } + m_centerPositon);

    m_spawnTimer -= elapsed;

    if (m_spawnTimer >= 0) {
        m_toggleTimer -= elapsed;
        if (m_toggleTimer <= 0) {
            m_toggleTimer = 0.05f;
            if (m_sprite->getColor().a == 0) {
                m_sprite->setColor(jt::colors::White);
                std::cout << "white\n";
            } else {
                m_sprite->setColor(jt::colors::Transparent);
            }
        }
    } else {
        m_sprite->setColor(jt::colors::White);
    }
}
void Bee::doDraw() const { m_sprite->draw(renderTarget()); }
bool Bee::canHurtPlayer() const { return m_spawnTimer <= 0; }
