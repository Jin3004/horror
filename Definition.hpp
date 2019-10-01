#pragma once
#include <Siv3D.hpp>
#include <memory>
#include <thread>
#include <vector>
#include <fstream>
//Include dependent files.

extern constexpr int WINDOW_X = 1280;
extern constexpr int WINDOW_Y = 720;
//Declare constant variables.

class Game {
public:
	Game() = default;

	Font debug_{ 20, U"Noto Sans CJK JP Medium" };

	virtual void Initialize(bool& isloading) {};
	[[nodiscard]] virtual std::unique_ptr<Game> Calculation(bool& isloading) { return nullptr; };
	virtual void Draw(bool isloading)const {};
	virtual void End() {};
};
//Declare the base class.

class Start :public Game {
public:

	Texture title_{ U"resource/img/title.png" };

	Start() = default;
	void Initialize(bool& isloading)override;
	[[nodiscard]] std::unique_ptr<Game> Calculation(bool& isloading)override;
	void Draw(bool isloading)const override;
	void End()override;
};

template<class Func>
class Menu :public Game {
public:

	std::vector<String> labels;
	std::vector<String> buttons;
	std::vector<String> texture_name;

	Menu() = default;
	void Initialize(bool& isloading)override;
	Menu(std::initializer_list<String> l, std::initializer_list<String> b) :labels(l), buttons(b) {};
	[[nodiscard]] std::unique_ptr<Game> Calculation(bool& isloading)override;
	void Draw(bool isloading)const override;
	//void End()override;
};