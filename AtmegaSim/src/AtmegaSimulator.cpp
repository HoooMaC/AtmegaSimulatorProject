#include "AtmegaSimulator.h"

#include "imgui_setup.h"

Karem::Application* Karem::CreateApplication()
{
	return new AtmegaSimulator();
}

AtmegaSimulator::AtmegaSimulator()
{
	Init();
}

AtmegaSimulator::~AtmegaSimulator()
{
}

void AtmegaSimulator::Run()
{
	while (m_Running)
	{
		Karem::RendererCommand::Clear();
		Karem::RendererCommand::ClearColor("#0000ff");

		ENGINE_TRACE("Atmega Simulation first test");

		m_Window.OnUpdate();
	}
}

void AtmegaSimulator::EventHandler(Karem::Event& event)
{
	Karem::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Karem::WindowCloseEvent>(std::bind(&AtmegaSimulator::WindowCloseEventHandler, this, std::placeholders::_1));
}

void AtmegaSimulator::Init()
{
	m_Window.SetEventCallbacks(std::bind(&AtmegaSimulator::EventHandler, this, std::placeholders::_1));

	GLFWwindow* window = Karem::GraphicsContext::GetContextCurrent();

	imgui::InitializeImGUI(window);
}

void AtmegaSimulator::Shutdown()
{
}

bool AtmegaSimulator::WindowCloseEventHandler(Karem::WindowCloseEvent& event)
{
	m_Running = false;
	return true;
}
