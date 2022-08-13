
#ifndef INC_1HGJ381_PLAYER_HPP
#define INC_1HGJ381_PLAYER_HPP

#include <game_object.hpp>
#include <shape.hpp>
#include <memory>

class Player : public jt::GameObject {
public:
    std::shared_ptr<jt::Shape> m_shape;

    void hurt();
    bool canBeHurt() const;
    float playerIdleTime() const;

    float m_playerIdleTime = 0.0f;

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    jt::Vector2f m_velocity { 0.0f, 0.0f };
    jt::Vector2f m_position { 0.0f, 0.0f };

    float m_hurtTimer = 0.0f;
    float m_flashTimer = 0.1f;
};

#endif // INC_1HGJ381_PLAYER_HPP
