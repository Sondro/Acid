#include "MainRenderer.hpp"

#include <Fonts/SubrenderFonts.hpp>
#include <Gizmos/SubrenderGizmos.hpp>
#include <Guis/SubrenderGuis.hpp>
#include <Devices/Keyboard.hpp>
#include <Meshes/SubrenderMeshes.hpp>
#include <Models/Shapes/ModelSphere.hpp>
#include <Particles/SubrenderParticles.hpp>
#include <Post/Deferred/SubrenderDeferred.hpp>
#include <Post/Filters/FilterBlit.hpp>
#include <Post/Filters/FilterCrt.hpp>
#include <Post/Filters/FilterDefault.hpp>
#include <Post/Filters/FilterDof.hpp>
#include <Post/Filters/FilterEmboss.hpp>
#include <Post/Filters/FilterFxaa.hpp>
#include <Post/Filters/FilterGrain.hpp>
#include <Post/Filters/FilterLensflare.hpp>
#include <Post/Filters/FilterPixel.hpp>
#include <Post/Filters/FilterSsao.hpp>
#include <Post/Filters/FilterTiltshift.hpp>
#include <Post/Filters/FilterTone.hpp>
#include <Post/Filters/FilterVignette.hpp>
#include <Graphics/Graphics.hpp>
#include <Scenes/Scenes.hpp>
#include <Shadows/SubrenderShadows.hpp>

namespace test {
MainRenderer::MainRenderer() {
	std::vector<Attachment> renderpassAttachments0 = {
		{0, "shadows", Attachment::Type::Image, false, VK_FORMAT_R8_UNORM}
	};
	std::vector<SubpassType> renderpassSubpasses0 = {
		{0, {0}}
	};
	AddRenderStage(std::make_unique<RenderStage>(renderpassAttachments0, renderpassSubpasses0, Viewport({4096, 4096})));

	std::vector<Attachment> renderpassAttachments1 = {
		{0, "depth", Attachment::Type::Depth, false},
#if defined(ACID_RELOAD)
		{1, "swapchain", Attachment::Type::Image, false, VK_FORMAT_R8G8B8A8_UNORM},
#else
		{1, "swapchain", Attachment::Type::Swapchain},
#endif
		{2, "position", Attachment::Type::Image, false, VK_FORMAT_R16G16B16A16_SFLOAT},
		{3, "diffuse", Attachment::Type::Image, false, VK_FORMAT_R8G8B8A8_UNORM},
		{4, "normal", Attachment::Type::Image, false, VK_FORMAT_R16G16B16A16_SFLOAT},
		{5, "material", Attachment::Type::Image, false, VK_FORMAT_R8G8B8A8_UNORM},
		{6, "resolved", Attachment::Type::Image, false, VK_FORMAT_R8G8B8A8_UNORM}
	};
	std::vector<SubpassType> renderpassSubpasses1 = {
		{0, {0, 2, 3, 4, 5}},
		{1, {0, 6}},
		{2, {0, 1}}
	};
	AddRenderStage(std::make_unique<RenderStage>(renderpassAttachments1, renderpassSubpasses1));

#if defined(ACID_RELOAD)
	std::vector<Attachment> renderpassAttachments2 = {
		{0, "swapchainReal", Attachment::Type::Swapchain}
	};
	std::vector<SubpassType> renderpassSubpasses2 = {
		{0, {0}}
	};
	AddRenderStage(std::make_unique<RenderStage>(renderpassAttachments2, renderpassSubpasses2));
#endif
}

void MainRenderer::Start() {
	//AddSubrender<RenderShadows>(Pipeline::Stage(0, 0));

	AddSubrender<SubrenderMeshes>(Pipeline::Stage(1, 0));

	AddSubrender<SubrenderDeferred>(Pipeline::Stage(1, 1));
	AddSubrender<SubrenderParticles>(Pipeline::Stage(1, 1));

	//AddSubrender<FilterFxaa>(Pipeline::Stage(1, 2));
	//AddSubrender<FilterTone>(Pipeline::Stage(1, 2));
	//AddSubrender<FilterSsao>(Pipeline::Stage(1, 2));
	//AddSubrender()->AddRenderer<PipelineBlur>(Pipeline::Stage(1, 2), 1.8f, PipelineBlur::Type::_5, false, 0.6f, 1.0f);
	//AddSubrender<FilterDof>(Pipeline::Stage(1, 2), sceneBlur, 1.11f);
	//AddSubrender<FilterEmboss>(Pipeline::Stage(1, 2));
	//AddSubrender<FilterCrt>(Pipeline::Stage(1, 2));
	//AddSubrender<FilterLensflare>(Pipeline::Stage(1, 2));
	//AddSubrender<FilterTiltshift>(Pipeline::Stage(1, 2));
	//AddSubrender<FilterPixel>(Pipeline::Stage(1, 2), 8.0f);
	//AddSubrender<FilterVignette>(Pipeline::Stage(1, 2));
	//AddSubrender<FilterGrain>(Pipeline::Stage(1, 2));
	AddSubrender<FilterDefault>(Pipeline::Stage(1, 2), true);
	//AddSubrender<RenderGizmos>(Pipeline::Stage(1, 2));
	AddSubrender<SubrenderGuis>(Pipeline::Stage(1, 2));
	AddSubrender<SubrenderFonts>(Pipeline::Stage(1, 2));

#if defined(ACID_RELOAD)
	AddSubrender<FilterBlit>({2, 0});
#endif
}

void MainRenderer::Update() {
	//auto renderpassCreate1 = Renderer::Get()->GetRenderStage(1);
	//renderpassCreate1->GetViewport().SetScale(0.75f);

	//Renderer::Get()->GetRenderer<FilterVignette>(true)->SetEnabled(Keyboard::Get()->GetKey(KEY_I));
	
#if defined(ACID_RELOAD)
	auto renderpassCreate1 = GetRenderStage(1);
	//renderpassCreate1->GetViewport().SetOffset({0.1f, 0.0f});

	if (Keyboard::Get()->GetKey(Key::Q) == InputAction::Release) {
		renderpassCreate1->GetViewport().SetScale({1.0f, 1.0f});
	} else {
		renderpassCreate1->GetViewport().SetScale({0.5f, 1.0f});
	}

	//Renderer::Get()->GetRenderer<FilterVignette>(true)->SetEnabled(Keyboard::Get()->GetKey(Key::I));
#endif
}
}
