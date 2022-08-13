
#include "player.hpp"
#include <game_interface.hpp>

void Player::doCreate() {
    m_shape = std::make_shared<jt::Shape>();
    m_shape->makeCircle(16, textureManager());
    m_shape->setOffset(jt::OffsetMode::CENTER);
    m_shape->setPosition(jt::Vector2f{400,600});
}

void Player::doUpdate(float const elapsed) {
    m_shape->update(elapsed);

    float const moveSpeed = 12.0f;

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::A) ||getGame()->input().keyboard()->pressed(jt::KeyCode::Left))
    {
        m_velocity.x -= elapsed * moveSpeed;
    }
    else if (getGame()->input().keyboard()->pressed(jt::KeyCode::D) ||getGame()->input().keyboard()->pressed(jt::KeyCode::Right))
    {
        m_velocity.x += elapsed * moveSpeed;
    }

    if (getGame()->input().keyboard()->pressed(jt::KeyCode::W) ||getGame()->input().keyboard()->pressed(jt::KeyCode::Up))
    {
        m_velocity.y -= elapsed * moveSpeed;
    }
    else if (getGame()->input().keyboard()->pressed(jt::KeyCode::S) ||getGame()->input().keyboard()->pressed(jt::KeyCode::Down))
    {
        m_velocity.y += elapsed * moveSpeed;
    }

    m_velocity = 0.97f * m_velocity;

    m_position = m_position + m_velocity;

    m_shape->setPosition(m_position);

}
void Player::doDraw() const { m_shape->draw(renderTarget()); }
