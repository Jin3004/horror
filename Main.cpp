#include "Definition.hpp"

void Main() {//Entry point

	bool state = true, isloading = false;
	std::unique_ptr<Game> game_ptr = std::make_unique<Start>();
	
	std::thread calc([&]() {
		game_ptr->Initialize(isloading);

		while (state) {
			auto ischanged = game_ptr->Calculation(isloading);
			if (ischanged != nullptr) {
				game_ptr = std::move(ischanged);
				game_ptr->Initialize(isloading);
			}
		}
		});

	std::thread draw([&]() {
		while (state = System::Update()) {
			game_ptr->Draw(isloading);
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

std::unique_ptr<Game> Start::Calculation(bool& isloading) {
	return nullptr;
}

void Start::Draw(bool isloading) const {
	if (isloading)debug(U"Now Loading...").draw(0, 0);
	else debug(U"Finish loading.").draw(0, 0);
}

void Start::End() {

}