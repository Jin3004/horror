#pragma once
#include <Siv3D.hpp>
#include <Windows.h>
#include <codecvt>
#include <memory>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
//Include dependent files.

extern constexpr int WINDOW_X = 1280;
extern constexpr int WINDOW_Y = 720;
//Declare constant variables.

template<class string_t>
std::vector<string_t> Split(string_t str, char delim) {//This function splits a given string by a given delim.
	std::vector<string_t> res;
	string_t item;
	for (const auto ch : str) {
		if (ch == delim) {
			if (!item.empty())res.push_back(item);
			item.clear();
		}
		else {
			item += ch;
		}
	}
	if (!item.empty()) res.push_back(item);

	return res;
}

struct Data {//the set of data used for inside.
	bool state;//Application's state. false -> "Closed the window."
	bool isloading;//Whether loading the resources or not.
	String title;//Game title from the command line argument.
};

class Game {
public:
	Game() = default;

	Font debug_{ 40, U"resource/fonts/g_comichorrorR_freeR.ttf" };

	virtual void Initialize(Data& data) {};
	[[nodiscard]] virtual std::unique_ptr<Game> Calculation(Data& data) { return nullptr; };
	virtual void Draw(Data data)const {};
	virtual void End() {};
};
//Declare the base class.

class Start :public Game {
public:

	Start() = default;
	void Initialize(Data& data)override;
	[[nodiscard]] std::unique_ptr<Game> Calculation(Data& data)override;
	void Draw(Data data)const override;
	void End()override;
};

class Menu :public Game {
public:

	std::vector<String> labels;
	std::vector<String> buttons;
	std::vector<String> texture_name;

	Menu() = default;
	void Initialize(Data& data)override;
	Menu(std::initializer_list<String> l, std::initializer_list<String> b) :labels(l), buttons(b) {};
	[[nodiscard]] std::unique_ptr<Game> Calculation(Data& data)override;
	void Draw(Data data)const override;
	//void End()override;
};