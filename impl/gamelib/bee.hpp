#ifndef INC_1HGJ381_BEE_HPP
#define INC_1HGJ381_BEE_HPP
#include <game_object.hpp>
#include <sprite.hpp>
#include <vector.hpp>

class Bee : public jt::GameObject {
public:
    void setCenterPosition(jt::Vector2f const& centerPosition);

    bool canHurtPlayer() const;

    std::shared_ptr<jt::Sprite> m_sprite;

    void reset();

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    jt::Vector2f m_centerPositon;

    float m_timePhase { 0.0f };
    float m_timeFrequ { 1.0f };
    float m_rotationSpeedFactor { 1.0f };

    float m_spawnTimer = 2.0f;
    float m_toggleTimer = 0.1f;
};

#endif // INC_1HGJ381_BEE_HPP
