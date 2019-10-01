#include "Definition.hpp"

void Main() {//Entry point

	bool state = true, isloading = false;
	Rect black_screen(0, 0, WINDOW_X, WINDOW_Y);
	std::unique_ptr<Game> game_ptr = std::make_unique<Start>();

	std::thread calc([&]() {
		game_ptr->Initialize(isloading);

		while (state) {
			auto ischanged = game_ptr->Calculation(isloading);
			if (ischanged != nullptr) {
				game_ptr->End();
				game_ptr = std::move(ischanged);
				game_ptr->Initialize(isloading);
			}
		}
		});

	std::thread draw([&]() {

		Font debug{ 20 };

		while (state = System::Update()) {
			game_ptr->Draw(isloading);
			if (isloading) {
				black_screen.draw(Palette::Black);
				debug(U"Now Loading...").draw(0, 0);
			}
		}
		});

	draw.join();
	calc.join();
}

void Start::Initialize(bool& isloading) {
	isloading = true;
	Window::SetTitle(U"HORROR!");
	Window::Resize(WINDOW_X, WINDOW_Y);
	std::this_thread::sleep_for(3s);
	isloading = false;
}

[[nodiscard]] std::unique_ptr<Game> Start::Calculation(bool& isloading) {
	if (!KeySpace.down())return nullptr;
	else return std::make_unique<Menu>();
}

void Start::Draw(bool isloading) const {
	title_.draw();
}

void Start::End() {

}

void Menu::Initialize(bool& isloading) {
}

[[nodiscard]] std::unique_ptr<Game> Menu::Calculation(bool& isloading) {
	return nullptr;
}

void Menu::Draw(bool isloading)const {
}