#pragma once

#include <Scenes/Component.hpp>

using namespace acid;

namespace test {
class PlayerFps : public Component::Registrar<PlayerFps> {
public:
	PlayerFps();

	void Start() override;
	void Update() override;

	friend const Node &operator>>(const Node &node, PlayerFps &player);
	friend Node &operator<<(Node &node, const PlayerFps &player);

private:
	static bool registered;

	bool m_noclipEnabled = false;
};
}
