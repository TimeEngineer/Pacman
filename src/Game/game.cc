#include "game.hh"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

Game::Game(unsigned int wnd_width, unsigned int wnd_height, float scale):
is_pacman_moved(false),
is_clyde_out(false),
is_inkey_out(false),
is_pinky_out(false),
_map(_default_path + _map_file, wnd_width, wnd_height, scale, scale),
_pacman(scale),
_blinky(scale),
_clyde(scale),
_inkey(scale),
_pinky(scale),
_pacman_transition(false)
{
    sf::Vector2i offset = _map.get_topleft();
    _pacman.set_offset(offset);
    _inkey.set_offset(offset);
    _blinky.set_offset(offset);
    _clyde.set_offset(offset);
    _pinky.set_offset(offset);

    std::srand(std::time(0));

    move(_pacman, _initial_map_x, _initial_map_y);
    move(_blinky, _blinky_init_x, _blinky_init_y);
    move(_clyde, _clyde_init_x, _clyde_init_y);
    move(_inkey, _inkey_init_x, _inkey_init_y);
    move(_pinky, _pinky_init_x, _pinky_init_y);

    std::vector<std::pair<int, int> > test;
    test.push_back(std::pair<int, int>(4,1));
    test.push_back(std::pair<int, int>(3,1));
    test.push_back(std::pair<int, int>(2,1));
    fill_points(test, scale, offset);
    std::vector<std::pair<int, int> > test2;
    test2.push_back(std::pair<int, int>(5,1));
    test2.push_back(std::pair<int, int>(6,1));
    test2.push_back(std::pair<int, int>(7,1));
    fill_energizers(test2, scale, offset);
}
bool Game::move_ghost(Ghost &ghost, const sf::Vector2i &pos) {
    sf::Vector2i displacement, cur_pos(ghost.get_map_coordinate());
    displacement = pos - cur_pos;

    if (abs(displacement.x) + abs(displacement.y) > 1 || !is_pacman_moved)
        return false;
    if(displacement.y > 0)
        ghost.set_orientation(Creature::Orientation::Top);
    else if(displacement.y < 0)
        ghost.set_orientation(Creature::Orientation::Bottom);
    else if(displacement.x > 0)
        ghost.set_orientation(Creature::Orientation::Left);
    else if(displacement.x < 0)
        ghost.set_orientation(Creature::Orientation::Right);

    if(!check_mobility(ghost, cur_pos, displacement))
        return false;

    move(ghost, cur_pos + displacement);

    return true;
}
bool Game::move_pacman(sf::Keyboard::Key dir) {
    bool bMovable = false;
    // cur = current
    sf::Vector2i displacement, cur_pos(_pacman.get_map_coordinate()),target_pos;
    switch(dir) {
        case sf::Keyboard::Up :
            displacement.y = -1;
            _pacman.set_orientation(Creature::Orientation::Top);
            break;
        case sf::Keyboard::Down :
            displacement.y = 1;
            _pacman.set_orientation(Creature::Orientation::Bottom);
            break;
        case sf::Keyboard::Left :
            displacement.x = -1;
            _pacman.set_orientation(Creature::Orientation::Left);
            break;
        case sf::Keyboard::Right :
            displacement.x = 1;
            _pacman.set_orientation(Creature::Orientation::Right);
            break;
        default:
            break;
    }
    if(!check_mobility(_pacman, cur_pos, displacement))
        return false;
    is_pacman_moved = true;
    _pacman_transition = true;
    pacman_src_pos = _pacman.get_map_coordinate();
    pacman_dst_pos = cur_pos + displacement;
    //move(_pacman, cur_pos + displacement);

    return bMovable;
}
void Game::draw(sf::RenderWindow &window) {
    sf::Font font;
    font.loadFromFile(_default_path + _font_paths[FONT_TYPE::COMIC]);
    sf::Text text("Score:" + std::to_string(_pacman.get_score()), font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    window.draw(text);
    _map.draw(window);
    for(auto &iter : _points)
        iter.draw(window);
    for(auto &iter : _energizers)
        iter.draw(window);
    _pacman.draw(window);
    _blinky.draw(window);
    _clyde.draw(window);
    _inkey.draw(window);
    _pinky.draw(window);
}

bool Game::check_mobility(Creature &creature, sf::Vector2i cur_pos, sf::Vector2i displacement) {
    sf::Vector2i target_pos(cur_pos + displacement);

    //target_pos = _map.get_map_coordinate(target_pos);
    if(target_pos.x < 0 || target_pos.y < 0)
        return false;
    if(target_pos.x >= _map.get_map_dimension().x || target_pos.y >= _map.get_map_dimension().y)
        return false;

    if((_map(target_pos.x, target_pos.y).get_status() & creature.get_entity_id()) == 0x0)
        return false;
    return true;
}
bool Game::timer(sf::Clock &clock) {
    return true;
}
void Game::animate_pacman(void) {
    _pacman.next_frame();
    _inkey.next_frame();
    _blinky.next_frame();
    _clyde.next_frame();
    _pinky.next_frame();
}
void Game::make_transistion() {
    sf::Vector2i displacement, src_screen_pos, dst_screen_pos;
    src_screen_pos = _pacman.get_screen_coordinate();
    dst_screen_pos = _map.get_screen_coordinate(pacman_dst_pos);

    if(_pacman_transition) {
        if(src_screen_pos == dst_screen_pos) {
            _pacman_transition = false;
            if(_map.get_block_status(pacman_dst_pos) == Block::Status::Portal) {
                sf::Vector2i real_dst_pos = _map.get_map_coordinate(pacman_dst_pos);
                _pacman.set_map_coordinate(real_dst_pos);
                _pacman.set_screen_coordinate(_map.get_screen_coordinate(real_dst_pos));
                return;
            }
            _pacman.set_map_coordinate(pacman_dst_pos);
            _pacman_transition = false;

        }
        displacement = dst_screen_pos - src_screen_pos;
        displacement.x = moving_step * (displacement.x == 0 ? 0 : (displacement.x < 0 ? -1 : 1));
        displacement.y = moving_step * (displacement.y == 0 ? 0 : (displacement.y < 0 ? -1 : 1));
        _pacman.set_screen_coordinate(src_screen_pos + displacement);
    }
}
void Game::move(Entity &creature, const sf::Vector2i &pos) {
    // Cela ne change pas la position de l'image.
    creature.set_map_coordinate(_map.get_map_coordinate(pos.x, pos.y));
    // Cela change la position de l'image.
    creature.set_screen_coordinate(_map.get_screen_coordinate(creature.get_map_coordinate()));
}

/*    // Cela ne change pas la position de l'image.
    creature.set_map_coordinate(_map.get_map_coordinate(pos.x, pos.y));
    // Cela change la position de l'image.
    creature.set_screen_coordinate(_map.get_screen_coordinate(creature.get_map_coordinate()));*/
void Game::move(Entity &creature, int x, int y) {
   move(creature, sf::Vector2i(x, y));
}

void Game::chase_pacman(void) {
    if(!is_pacman_moved)
        return;

    for(auto const &iter : _map._cst_vertices) {
        if(iter.get_vertex_block().get_map_coordinate() == _blinky.get_map_coordinate()){
            order_ghost(Ghost_Sprite::BLINKY, Game::GhostBehavior::Chase);
            break;
        }
    }
    _blinky.next();
    move(_blinky, _blinky.get_cur_block());
}
sf::Vector2i Game::closest_intersection_to_pacman() {
    sf::Vector2i pacman_pos = _pacman.get_map_coordinate();
    sf::Vector2i v1, v2;

    for(const auto& edge_iter : _map._cst_edges) {
        v1 = edge_iter.get_vertices().front()->get_map_coordinate();
        v2 = edge_iter.get_vertices().back()->get_map_coordinate();
        if(v1 == pacman_pos)
            return pacman_pos;
        if(v2 == pacman_pos)
            return pacman_pos;

        for(const auto& block_iter : edge_iter.get_route()) {
            if(block_iter->get_map_coordinate() == pacman_pos) {
                v1 -= pacman_pos;
                v2 -= pacman_pos;
                if(std::hypot(v1.x, v1.y) <= std::hypot(v2.x, v2.y))
                    return v1 + pacman_pos;
                else
                    return v2 + pacman_pos;
            }
        }
    }
    return sf::Vector2i(0,0);
}

void Game::order_ghost(Ghost_Sprite::GHOST_TYPE ghost_type, Game::GhostBehavior mode) {
    Ghost &ghost = WHICH_GHOST(ghost_type);
    sf::Vector2i intersection_pos = closest_intersection_to_pacman();

    if(mode == GhostBehavior::Chase)
       ghost.set_path(_map.shortest_route(_map(ghost.get_map_coordinate().x, ghost.get_map_coordinate().y), _map(intersection_pos.x, intersection_pos.y)));
}
bool Game::exit_ghost_house(Ghost_Sprite::GHOST_TYPE ghost_type) {
    Ghost &ghost = WHICH_GHOST(ghost_type);
    const sf::Vector2i closest_intersection1(10, 8);
    const sf::Vector2i closest_intersection2(12, 8);
    const sf::Vector2i exit_pos(11, 9);
    int x = 0, y = 0, displacement;
    displacement = (std::rand() % 2) * (std::rand() % 2 == 0 ? -1 : 1);
    if(std::rand() % 2 == 0)
        x = displacement;
    else
        y = displacement;

    if(ghost.get_map_coordinate_y() <= exit_pos.y)
        y = -abs(y);

    move_ghost(ghost, ghost.get_map_coordinate() + sf::Vector2i(x, y));

    if(ghost.get_map_coordinate() == closest_intersection1 || ghost.get_map_coordinate() == closest_intersection2)
        return true;
    return false;
}

void Game::fill_points(std::vector<std::pair<int,int> > coordinates, float scale, sf::Vector2i offset) {
    int nb_points = static_cast<int>(coordinates.size());
    _points = std::vector<Point>(nb_points, Point(scale));
    for (int i = 0; i < nb_points; i++) {
        _points[i].set_offset(offset);
        move(_points[i], coordinates[i].first, coordinates[i].second);
    }
}

void Game::fill_energizers(std::vector<std::pair<int,int> > coordinates, float scale, sf::Vector2i offset) {
    int nb_energizers = static_cast<int>(coordinates.size());
    _energizers = std::vector<Energizer>(nb_energizers, Energizer(scale));
    for (int i = 0; i < nb_energizers; i++) {
        _energizers[i].set_offset(offset);
        move(_energizers[i], coordinates[i].first, coordinates[i].second);
    }
}

Entity& Game::collision() {
    if(_inkey.get_map_coordinate() == _pacman.get_map_coordinate()) return _inkey;
    if(_blinky.get_map_coordinate() == _pacman.get_map_coordinate()) return _inkey;
    if(_clyde.get_map_coordinate() == _pacman.get_map_coordinate()) return _inkey;
    if(_pinky.get_map_coordinate() == _pacman.get_map_coordinate()) return _inkey;
    for (auto &point : _points)
        if(point.get_map_coordinate() == _pacman.get_map_coordinate()) {
            point.set_visible(false);
            return point;
        }
    for (auto &energizer : _energizers)
        if(energizer.get_map_coordinate() == _pacman.get_map_coordinate()) {
            energizer.set_visible(false);
            return energizer;
        }
    /*for (auto &fruit : _energizers)
        if(fruit.get_map_coordinate() == _pacman.get_map_coordinate()) return fruit;*/
    return _pacman;
}
