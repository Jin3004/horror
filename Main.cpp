#include "Definition.hpp"

void Main() {//Entry point
	std::unique_ptr<Game> game_ptr = std::make_unique<Start>();
	bool state = true;
	std::thread draw([&]() {
		while (state = System::Update()) {
			game_ptr->Draw();
		}
		});
	std::thread calc([&] {
		while (state) {
			game_ptr->Calculation();
		}
		});

	draw.join();
	calc.join();
}

Start::Start() {
	Window::SetTitle(U"HORROR!");
	Window::Resize(WINDOW_X, WINDOW_Y);
}

void Start::Calculation() {

}

void Start::Draw() const {
	Rect(0, 0, 100, 100).draw();
}

void Start::End() {

}