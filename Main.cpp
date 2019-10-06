///<summary>
///Copyright 2019 Jin(@CPP_IS_GOD)
///</summary>

#include "Definition.hpp"

void Main() {//Entry point

	fs::current_path(resources_path);
	
	Data data = { true, false, Split(Unicode::FromWString(GetCommandLineW()), ' ')[1] };
	std::unique_ptr<Game> game_ptr = std::make_unique<Start>();
	
	std::thread calc([&]() {
		game_ptr->Initialize(data);
	
		while (data.state) {
			auto ischanged = game_ptr->Calculation(data);
			if (ischanged != nullptr) {
				game_ptr->End();
				game_ptr = std::move(ischanged);
				game_ptr->Initialize(data);
			}
		}
		});
	
	std::thread draw([&]() {
	
		Font debug{ 20 };
	
		Rect black_screen(0, 0, WINDOW_X, WINDOW_Y);
		//TODO: write code more clearly so that everyone can understand what it means.
		while (data.state ? (data.state = System::Update()) : data.state) {
			game_ptr->Draw(data);
			if (data.isloading) {
				black_screen.draw(Palette::Black);
				debug(U"Now Loading...").draw(0, 0);
			}
		}
		});
	
	draw.join();
	calc.join();
}

void Start::Initialize(Data& data) {
	data.isloading = true;

	Window::SetTitle(U"THE HORROR!");
	Window::Resize(WINDOW_X, WINDOW_Y);

	data.isloading = false;
}

[[nodiscard]] std::unique_ptr<Game> Start::Calculation(Data& data) {
	if (!KeySpace.down())return nullptr;
	else return std::make_unique<Menu>("Yeah!");
}

void Start::Draw(Data data) const {
	scary_font(U"Welcome to " + data.title).draw();
}

void Start::End() {

}

Menu::Menu(std::string directory) {
	//std::ifstream rc("menu" + directory + "/text.txt", std::ios::in);
	//if (rc.fail()) {
	//
	//}
}

void Menu::Initialize(Data& data) {
	data.isloading = true;

	data.isloading = false;
}

[[nodiscard]] std::unique_ptr<Game>	Menu::Calculation(Data& data) {
	if (!KeySpace.down())return nullptr;
	else Terminate(0);
}

void Menu::Draw(Data data)const {
	scary_font(U"Menu").draw();
}