#pragma once

#include "AppLayer.h"
#include "ControlLayer.h"
#include "KaremEngine.h"

class Sandbox : public Karem::Application
{
public:
	Sandbox();
	~Sandbox();

	void Run() override;
	void EventHandler(Karem::Event& event) override;
protected:
	void Init() override;
	void Shutdown() override;

private:
	bool WindowCloseAction(Karem::WindowCloseEvent& event);
	
	void PushLayer(std::shared_ptr<Karem::Layer> layer);
	void PushOverlay(std::shared_ptr<Karem::Layer> overlay);
	void PopLayer(std::shared_ptr<Karem::Layer> layer);
	void PopOverlay(std::shared_ptr<Karem::Layer> overlay);
private:
	Karem::Layers m_Layers;
	Karem::OrthographicCamera m_Camera;
	std::shared_ptr<Karem::Shader> m_Shader;
	std::shared_ptr<ControlLayer> m_ControlLayer;

	float m_LastFrameTime = 0.0f;
};

