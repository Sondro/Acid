﻿#pragma once

#include <Scenes/Component.hpp>
#include <Files/Node.hpp>

using namespace acid;

namespace test {
class CelestialBody : public Component::Registrar<CelestialBody> {
public:
	enum class Type { Sun, Moon };

	explicit CelestialBody(Type type = Type::Sun);

	void Update() override;

	friend const Node &operator>>(const Node &node, CelestialBody &celestialBody);
	friend Node &operator<<(Node &node, const CelestialBody &celestialBody);

	Type GetType() const { return m_type; }
	void SetType(const Type &type) { m_type = type; }

private:
	static bool registered;

	Type m_type;
};
}
