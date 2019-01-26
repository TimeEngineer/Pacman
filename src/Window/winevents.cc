#include "window.hh"
#include <functional>
void Window::draw(sf::RenderWindow& window) {
	window.clear();

	switch(_mode) {
		case DrawMode::Game :
			// _map->draw(window);
			_game->draw(window);
			break;
		case DrawMode::Bg :
				_background->draw(window);
			if (_cursor->get_visible())
				_cursor->draw(window);
		break;
		default:
		break;

	}
	window.display();
}
void Window::timer(sf::Clock &clock) {
	sf::Time chrono;
	//chrono measures the time since the start of the game.(A)
	chrono = clock.getElapsedTime();
	for(const auto &tmev : timer_events) {
		// A - B > the wait duration needed to launch a time event
		if(chrono.asMilliseconds() - tmev->timer.asMilliseconds() >= tmev->time_ms) {
			tmev->event();
			// tmev->timer saves the "chrono" value at the time the event was executed(B)
			tmev->timer = clock.getElapsedTime();
		}
	}
}

void Window::key_pressed(sf::RenderWindow& window, sf::Keyboard::Key key) {
	//switch.cc
	switch (key) {
		case sf::Keyboard::Escape:
			switch_escape(window);
			break;
		case sf::Keyboard::Return:
			switch_return(window);
			break;
		case sf::Keyboard::P:
			if (_mode == DrawMode::Game) {
				if(_game->is_game_started())
					_game->pause();
			}
			break;
		case sf::Keyboard::Up:
		case sf::Keyboard::Down:
		case sf::Keyboard::Left:
		case sf::Keyboard::Right:
			switch(_mode) {
				case DrawMode::Game :
					if(_game->is_game_started()) {
						_game->move_pacman(key);
					}
					break;
				case DrawMode::Bg :
					switch_arrowkey(window, key);
					break;
				default:
					break;
			}
			break;
	default:
		break;
	}
}
