#include "Scene1.hpp"

#include <Uis/Uis.hpp>

namespace test {
Scene1::Scene1() :
	Scene(std::make_unique<Camera>()),
	m_pannable(&Uis::Get()->GetCanvas()) {
}

void Scene1::Start() {
}

void Scene1::Update() {
}

bool Scene1::IsPaused() const {
	return true;
}
}
