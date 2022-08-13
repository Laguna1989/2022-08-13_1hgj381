
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

    auto const rotationDirection = jt::Random::getChance(0.5f);
    if (rotationDirection) {
        m_rotationSpeedFactor *= -1.0f;
    }

    auto const fastRotate = jt::Random::getChance(0.25f);
    if (fastRotate) {
        auto const axis = jt::Random::getChance();
        if (axis) {
            m_rotationSpeedX = 2.0f;
        } else {
            m_rotationSpeedY = 2.0f;
        }
    }
}
void Bee::doUpdate(float const elapsed)
{
    m_sprite->update(elapsed);

    auto const t = m_timeFrequ * getAge() + m_timePhase;
    auto const radius = 80;
    auto const r = radius + sin(t * 4) * 20;

    auto const rotationSpeed = 1.25f * m_rotationSpeedFactor;
    auto const x = r * sin(t * rotationSpeed * m_rotationSpeedX);
    auto const y = r * cos(t * rotationSpeed * m_rotationSpeedY);

    m_sprite->setPosition(jt::Vector2f { x, y } + m_centerPositon);

    m_spawnTimer -= elapsed;

    if (m_spawnTimer >= 0) {
        m_toggleTimer -= elapsed;
        if (m_toggleTimer <= 0) {
            m_toggleTimer = 0.05f;
            if (m_sprite->getColor().a == 0) {
                m_sprite->setColor(jt::colors::White);
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
void Bee::reset() { m_spawnTimer = 2.0f; }
