///<summary>
///Copyright 2019 Jin(@CPP_IS_GOD)
///</summary>

#include "Definition.hpp"

void Main() {//Entry point

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

		while (data.state = System::Update()) {
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
	Console.open();
	fs::current_path(resources_path);
	
	data.isloading = false;
}

[[nodiscard]] std::unique_ptr<Game> Start::Calculation(Data& data) {
	if (!KeySpace.down())return nullptr;
	else return std::make_unique<Menu>();
}

void Start::Draw(Data data) const {
	debug_(U"Welcome to " + data.title).draw();
}

void Start::End() {

}

void Menu::Initialize(Data& data) {
	data.isloading = true;

	for(const fs::directory_entry&x:fs::directory_iterator(resources_path + fs::path("/")))

	data.isloading = false;
}

[[nodiscard]] std::unique_ptr<Game> Menu::Calculation(Data& data) {
	return nullptr;
}

void Menu::Draw(Data data)const {

}