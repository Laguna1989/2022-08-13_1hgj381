
#include "bee.hpp"

void Bee::setPlayerPosition(jt::Vector2f const& playerPos) { m_playerPosition = playerPos; }

void Bee::doCreate() {
    m_sprite = std::make_shared<jt::Sprite>("assets/bee.png", textureManager());

}
void Bee::doUpdate(float const elapsed) { m_sprite->update(elapsed);}
void Bee::doDraw() const { m_sprite->draw(renderTarget());}
