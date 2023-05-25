#include <SDL.h>
#include "Graphics.h"
#include "Primitives.h"

Graphics::Graphics() {
	SDL_Init(SDL_INIT_VIDEO);
}

Graphics::~Graphics() {
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Graphics::CreateWindow(const char* title, int width, int height, float size) {
	m_Width = width;
	m_Height = height;

	float Ratio = m_Width / (float)m_Height;
	m_Extents = glm::vec2{ size * Ratio, size };

	m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
}

void Graphics::Clear() {
	SDL_RenderClear(m_Renderer);
}

void Graphics::Present() {
	SDL_RenderPresent(m_Renderer);
}

void Graphics::SetColor(const glm::vec4& color) {
	glm::ivec4 IColor;
	IColor.r = (int)(color.r * 255);
	IColor.g = (int)(color.g * 255);
	IColor.b = (int)(color.b * 255);
	IColor.a = (int)(color.a * 255);

	SDL_SetRenderDrawColor(m_Renderer, IColor.r, IColor.g, IColor.b, IColor.a);
}

glm::ivec4 Graphics::ConvertColor(const glm::vec4& color) {
	glm::ivec4 IColor;
	IColor.r = (int)(color.r * 255);
	IColor.g = (int)(color.g * 255);
	IColor.b = (int)(color.b * 255);
	IColor.a = (int)(color.a * 255);

	return IColor;
}

void Graphics::DrawPoint(const glm::ivec2& point, const glm::vec4& color) {
	SetColor(color);
	SDL_RenderDrawPoint(m_Renderer, point.x, point.y);
}

void Graphics::DrawLine(const glm::ivec2& start, const glm::ivec2& end, const glm::vec4& color) {
	SetColor(color);
	SDL_RenderDrawLine(m_Renderer, start.x, start.y, end.x, end.y);
}

void Graphics::DrawCircle(const glm::ivec2& point, int radius, const glm::vec4& color) {
	glm::ivec4 IColor = ConvertColor(color);

	circleRGBA(m_Renderer, point.x, point.y, radius, IColor.r, IColor.g, IColor.b, IColor.a);
}

void Graphics::DrawFilledCircle(const glm::ivec2& point, int radius, const glm::vec4& color) {
	glm::ivec4 IColor = ConvertColor(color);

	filledCircleRGBA(m_Renderer, point.x, point.y, radius, IColor.r, IColor.g, IColor.b, IColor.a);
}

glm::vec2 Graphics::ScreenToWorld(const glm::ivec2& screen) {
	float x = screen.x / (float)m_Width; // screen x (0 - 800) -> x (0 - 1)
	float y = (m_Height - screen.y) / (float)m_Height; // screen y (0 - 600) -> (0 - 1) flip

	glm::vec2 World;
	World.x = ((1 - x) * -m_Extents.x) + (x * m_Extents.x);
	World.y = ((1 - y) * -m_Extents.y) + (y * m_Extents.y);

	return World;
}

glm::ivec2 Graphics::WorldToScreen(const glm::vec2& world) {
	float x = (world.x + m_Extents.x) / (m_Extents.x * 2); // world.x = 0 -> (0 + 6.66) / 13.33 -> 0.5
	float y = (world.y + m_Extents.y) / (m_Extents.y * 2); // world.y = 0 -> (0 + 5) / 10 = 0.5

	glm::vec2 Screen;
	Screen.x = x * m_Width;
	Screen.y = (1.0f - y) * m_Height;

	return Screen;
}

int Graphics::WorldToPixels(float world) {
	return (int)(world * (m_Height / (m_Extents.y * 2)));
}