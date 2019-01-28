#include "window.hh"

void Window::switch_escape(sf::RenderWindow& window) {
	switch (_background->get_token()) {
		case background_option::bJEU:
		case background_option::bREGLES:
		case background_option::bSCORES:
			_mode = DrawMode::Bg;
			_game->stop();
			_game->reset();
			_game->game_reset();
			//std::cerr<<"Quit"<<std::endl;
			_background->set_sprite(background_option::bMENU);
			_cursor->set_visible(true);
			break;
		default:
			window.close();
			break;
	}
}

void Window::switch_arrowkey(sf::RenderWindow& window, sf::Keyboard::Key dir) {
	switch (_background->get_token()) {
		case bMENU:
			move_cursor(dir);
			break;
		default:
			break;
	}
}

void Window::switch_return(sf::RenderWindow& window) {
	switch (_background->get_token()) {
		case bMENU:
			menu_selected(window);
			break;
		case bREGLES:
			if(_mode == DrawMode::Game) {
				if(_game->is_entering_name()) {
					_game->name_is_entered();
				}
				else if(!_game->is_game_started()) {
						_game->start();
						_game->reset();
				}
				_game->unpause();
			}
			else {
				_mode = DrawMode::Game;
				_game->reset();
				_game->game_reset();
			}
			break;
		case bSCORES:
			_mode = DrawMode::Bg;
			_background->set_sprite(background_option::bMENU);
			_cursor->set_visible(true);
			break;
		default:
			break;
	}

}
void Window::menu_selected(sf::RenderWindow& window) {
	int sel = _cursor->get_selection();
	switch (sel) {
		case JOUER:
			_background->set_sprite(_options[sel]);
			_mode = DrawMode::Bg;
			_cursor->set_visible(false);
			break;
		case SCORES:
			_background->set_sprite(_options[sel]);
			_leaderboard.reopen();
			_mode = DrawMode::Leaderboard;
			_cursor->set_visible(false);
			break;
			/*_mode = DrawMode::Game;*/
			// Don't draw game screen until rules aren't read.
		case QUITTER:
			//std::cerr<<"Quit"<<std::endl;
			window.close();
			break;
		default:
			break;
	}
}
void Window::move_cursor(sf::Keyboard::Key dir) {
	_cursor->move((sf::Keyboard::Up == dir ? Cursor::Direction::Up : Cursor::Direction::Down));
}
