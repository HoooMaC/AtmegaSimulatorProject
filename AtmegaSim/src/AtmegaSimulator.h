#pragma once

#include <KaremEngine.h>

class AtmegaSimulator : public Karem::Application
{
public:
	AtmegaSimulator();
	~AtmegaSimulator();

	void Run() override;

	void EventHandler(Karem::Event& event) override;

protected:
	void Init() override;
	void Shutdown() override;

private:
	bool WindowCloseEventHandler(Karem::WindowCloseEvent& event);

};

