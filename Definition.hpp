#pragma once
#include <Siv3D.hpp>
#include <memory>
#include <thread>
//Include dependent files.

extern constexpr int WINDOW_X = 1280;
extern constexpr int WINDOW_Y = 720;
//Declare constant variables.

class Game {
public:
	Game() {};
	virtual void Calculation() {};
	virtual void Draw()const {};
	virtual void End() {};
};
//Declare the base class.

class Start :public Game {
public:
	Start();
	void Calculation()override;
	void Draw()const override;
	void End()override;
};