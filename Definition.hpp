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
	Game() = default;
	Font debug{ 20 };
	virtual void Initialize(bool& isloading) {};
	virtual std::unique_ptr<Game> Calculation(bool& isloading) { return nullptr; };
	virtual void Draw(bool isloading)const {};
	virtual void End() {};
};
//Declare the base class.

class Start :public Game {
public:
	Start() = default;
	void Initialize(bool& isloading)override;
	std::unique_ptr<Game> Calculation(bool& isloading)override;
	void Draw(bool isloading)const override;
	void End()override;
};