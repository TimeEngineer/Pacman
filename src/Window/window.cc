#include "window.hh"
// background texture size : 420x460
#define BG_WIDTH Background::bg_width
#define BG_HEIGHT Background::bg_height
Window::Window(unsigned int width, unsigned int height) {
	_width = width;
	_height = height;
	_scale = ((_width < BG_WIDTH * 2 || _height < BG_HEIGHT * 2) ? SMALL_SCALE : MEDIUM_SCALE);
	std::cout << "scale:"<<_scale<<std::endl;
	_background = new Background(_width, _height, _scale);
	_cursor = new Cursor(_width, _height, _scale, 0, 0, 4);
	_game = new Game(_width, _height, _scale);
	_mode = DrawMode::Bg;
}

Window::~Window() {
	delete _background;
	delete _cursor;
	delete _game;
}

void Window::launch() {
	// Init
	sf::RenderWindow window(sf::VideoMode(_width, _height), "Pacman !", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	bool redraw;
	sf::Clock clock;
	sf::Event event;
	clock.restart();

	register_timer_event(100,[&]() {_game->animate_pacman();});
	 register_timer_event(10,[&]() {_game->make_transistion();});
	//register_timer_event(500,_game->chase_pacman);
	redraw = true;
	while (window.isOpen()) {
		timer(clock);
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					key_pressed(window, event.key.code);
					break;
				default:
					break;
			}
			redraw = true;
		}
		if(redraw)
			draw(window); //WinEvents.cc
	}
}

void Window::register_timer_event(int time_ms, CallbackFunction event) {
	struct timer_event *tmev = new struct timer_event;
	tmev->time_ms = time_ms;
	tmev->event = event;
	timer_events.push_back(tmev);
}
