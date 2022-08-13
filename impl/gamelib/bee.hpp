#ifndef INC_1HGJ381_BEE_HPP
#define INC_1HGJ381_BEE_HPP
#include <game_object.hpp>
#include <sprite.hpp>
#include <vector.hpp>


class Bee  : public jt::GameObject{
public:

    void setPlayerPosition(jt::Vector2f const& playerPos);
private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    jt::Vector2f m_playerPosition;
    std::shared_ptr<jt::Sprite> m_sprite;
};

#endif // INC_1HGJ381_BEE_HPP
