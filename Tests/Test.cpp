#include "Test.h"

Test::Test() {
	//
}

Test::~Test() {
	if (m_World) delete m_World;
	if (m_Time) delete m_Time;
	if (m_Input) delete m_Input;
	if (m_Graphics) delete m_Graphics;
}

void Test::Initialize() {
	m_Graphics = new Graphics();
	m_Graphics->CreateWindow("Physics", 800, 600);
	m_Input = new Input();
	m_Time = new Time();
	m_Time->SetFixedDeltaTime(1 / 60.0f);
	m_World = new World();
}

void Test::Run() {
	// Game loop
	Update();

	m_FixedTime += m_Time->TimeDelta();
	while (m_FixedTime >= m_Time->GetFixedDeltaTime()) {
		FixedUpdate();
		m_FixedTime -= m_Time->GetFixedDeltaTime();
	}

	// Render
	PreRender();
	Render();
	PostRender();

	m_Graphics->DrawCircle(m_Graphics->ScreenToWorld(m_Input->GetMousePosition()), 30, { 1, 0, 0, 1 });
}


void Test::Update() {
	UpdateEvents();

	m_Input->Update();
	m_Time->Update();
}

void Test::PreRender() {
	m_Graphics->SetColor({ 0, 0, 0, 0 });
	m_Graphics->Clear();
}

void Test::PostRender() {
	m_Graphics->Present();
}

void Test::UpdateEvents() {
	SDL_Event Event;
	while (SDL_PollEvent(&Event)) {
		if (Event.type == SDL_QUIT) {
			m_Quit = true;
		}
		if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE) {
			m_Quit = true;
		}
	}
}