#include "Sandbox.h"

#include <glad/glad.h>

// TEMP : THIS SHOULD NOT BE HERE (MAYBE)
#include "imgui.h"
#include "imgui_setup.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

Karem::Application* Karem::CreateApplication()
{
	return new Sandbox();
}

Sandbox::Sandbox()
{
	Init();

	m_Camera = Karem::OrthographicCamera(-16.0f, 16.0f, -9.0f, 9.0f);

	std::shared_ptr<Karem::Shader> shader = Karem::CreateShader("res\\shader\\position_color_vertex.glsl", "res\\shader\\position_color_fragment.glsl");
	std::shared_ptr<Karem::VertexArray> vertexArray = Karem::CreateVertexArray();

	Karem::Renderer::SetShader(shader);
	Karem::Renderer::SetVertexArray(vertexArray);

	PushLayer(std::make_shared<AppLayer>());
	//PushLayer(std::make_shared<TestLayer>("just for testing"));
}

Sandbox::~Sandbox()
{
	Shutdown();
}

void Sandbox::Run()
{
	while (m_Running)
	{
		float time = glfwGetTime();
		Karem::TimeStep timeStep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		Karem::RendererCommand::Clear();
		Karem::RendererCommand::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

		if (Karem::Input::IsKeyPressed(KAREM_KEY_E))
		{
			float& rotation = m_Camera.GetRotation();
			rotation += 180.0f * timeStep;
			m_Camera.SetRotation(rotation);
		}
		else if (Karem::Input::IsKeyPressed(KAREM_KEY_Q))
		{
			float& rotation = m_Camera.GetRotation();
			rotation -= 180.0f * timeStep;
			m_Camera.SetRotation(rotation);
		}

		if (Karem::Input::IsKeyPressed(KAREM_KEY_D))
		{
			glm::vec3 pos = m_Camera.GetPosition();
			pos.x += 10.0f * timeStep;
			m_Camera.SetPosition(pos);
		}
		else if(Karem::Input::IsKeyPressed(KAREM_KEY_A))
		{
			glm::vec3 pos = m_Camera.GetPosition();
			pos.x -= 10.0f * timeStep;
			m_Camera.SetPosition(pos);
		}

		if(Karem::Input::IsKeyPressed(KAREM_KEY_W))
		{
			glm::vec3 pos = m_Camera.GetPosition();
			pos.y += 10.0f * timeStep;
			m_Camera.SetPosition(pos);
		}
		else if (Karem::Input::IsKeyPressed(KAREM_KEY_S))
		{
			glm::vec3 pos = m_Camera.GetPosition();
			pos.y -= 10.0f * timeStep;
			m_Camera.SetPosition(pos);
		}

		Karem::Renderer::BeginScene(m_Camera);

		imgui::BeginFrame();

		for (std::shared_ptr<Karem::Layer>& layer : m_Layers)
		{
			if (layer->GetStatus())
				layer->OnUpdate(timeStep);
		}

		m_ControlLayer->OnUpdate(timeStep);
		imgui::EndFrame();
		Karem::Renderer::EndScene();
			
		m_Window.OnUpdate();
	}
}

void Sandbox::Init()
{
	m_Window.SetEventCallbacks(std::bind(&Application::EventHandler, this, std::placeholders::_1));
	GLFWwindow* window = Karem::GraphicsContext::GetContextCurrent();
	imgui::InitializeImGUI(window);

	m_ControlLayer = std::make_shared<ControlLayer>(m_Layers);
}

void Sandbox::Shutdown()
{
}

void Sandbox::EventHandler(Karem::Event& event)
{
	Karem::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Karem::WindowCloseEvent>(std::bind(&Sandbox::WindowCloseAction, this, std::placeholders::_1));
	
	for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
	{
		if((*it)->GetStatus())
			(*it)->EventHandler(event); // Memanggil fungsi yang diinginkan dari shared_ptr
	}

	//ENGINE_TRACE(event);
}

bool Sandbox::WindowCloseAction(Karem::WindowCloseEvent& event)
{
	m_Running = false;
	return true;
}

void Sandbox::PushLayer(std::shared_ptr<Karem::Layer> layer)
{
	m_Layers.PushLayer(layer);
	m_ControlLayer->UpdateLayerCounter(m_Layers.GetSize());
}

void Sandbox::PushOverlay(std::shared_ptr<Karem::Layer> overlay)
{
	m_Layers.PushOverlay(overlay);
	m_ControlLayer->UpdateLayerCounter(m_Layers.GetSize());
}

void Sandbox::PopLayer(std::shared_ptr<Karem::Layer> layer)
{
	m_Layers.PopLayer(layer);
	m_ControlLayer->UpdateLayerCounter(m_Layers.GetSize());
}

void Sandbox::PopOverlay(std::shared_ptr<Karem::Layer> overlay)
{
	m_Layers.PopOverlay(overlay);
	m_ControlLayer->UpdateLayerCounter(m_Layers.GetSize());
}
