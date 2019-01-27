#include "leaderboard.hh"


Leaderboard::Leaderboard(std::string file_path, sf::Vector2i offset, float scale):

_offset(offset),
_name_offset(100,140),
_score_offset(330,140),
_file_path(file_path),
_scale(scale)
{
	_font.loadFromFile(_default_path + _font_paths[FONT_TYPE::COMIC]);
}
Leaderboard::~Leaderboard()
{

}

void Leaderboard::reopen()
{ 
    std::ifstream ifs(_file_path, std::ifstream::in);   
    std::string line;
    unsigned int begin = 0, middle = 0, end = 0;
    struct Score score;
    _scores.clear();
    while(getline(ifs, line)) {
        begin = 0;
        middle = line.find_first_of(';');
        end = line.size() - 1;
        //Parse:
        score.name = line.substr(begin, middle - begin);
        score.score = std::stoi(line.substr(middle + 1, end - middle));
        //insert the first one.
        if (_scores.size() == 0)
            _scores.push_back(score);
        else {
            bool inserted = false;
            //Sort before inserting
            for(std::vector<struct Score>::iterator it = _scores.begin(); it != _scores.end(); it++ ){
                if(score.score > it->score) {
                    inserted = true;    
                    _scores.insert(it, score);
                    break;
                }
            }
            if(!inserted)
                _scores.push_back(score);
        }
    }
    ifs.close();
    
}
std::vector<struct Leaderboard::Score> Leaderboard::get_top(int n)
{
    if(_scores.size() == 0)
        return std::vector<struct Score>();
    //Get first n records.
    return std::vector<struct Score>(_scores.begin(), _scores.begin() + (static_cast<int>(_scores.size()) >= n ? n : _scores.size()));  
}
void Leaderboard::draw(sf::RenderWindow& window) {
    sf::Vector2i name_pos(_name_offset.x * _scale, _name_offset.y * _scale);
    sf::Vector2i score_pos(_score_offset.x * _scale, _score_offset.y * _scale); 

	sf::Text text("", _font);	
	text.setCharacterSize(20 * _scale);
	//text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);
	
    unsigned int i =0;
    
    do {
	    text.setString(_scores[i].name);
	    text.setPosition(_offset.x + name_pos.x - text.getLocalBounds().width / 2, _offset.y + name_pos.y);
        window.draw(text);

	    text.setString(std::to_string(_scores[i].score));
	    text.setPosition(_offset.x + score_pos.x - text.getLocalBounds().width / 2, _offset.y + name_pos.y);
        window.draw(text);
        name_pos.y += static_cast<int>(text.getLocalBounds().height * 2.0f);
        i++;

    }while( name_pos.y  - _name_offset.y < (260 * _scale)  && i < _scores.size());
       
}