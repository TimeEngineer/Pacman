#pragma once
#include <string>

const std::string _default_path = "./DataBase/";
const std::string _map_file = "./Map/Map.txt";
const std::string _bg_image_paths[5] = {"Images/Fonds/menu.png",
									"Images/Fonds/rules.png",
									"Images/Fonds/basic_level.png",
									"Images/Fonds/scores.png"};

const std::string _image_paths[] = {"Images/Divers/cursor.png"};
const std::string _ghost_paths[] = {"Images/Creature/Ghost/Blinky.png",
                                    "Images/Creature/Ghost/Clyde.png",
                                    "Images/Creature/Ghost/Inkey.png",
                                    "Images/Creature/Ghost/Pinky.png"};

namespace Ghost_Sprite {
    enum GHOST_TYPE{BLINKY = 0, CLYDE = 1, INKEY = 2, PINKY = 3};
    enum GHOST_ORIENTATION{LEFT = 0, RIGHT = 2, TOP = 4, BOTTOM = 6};
    enum GHOST_STATUS{LIVE = 0x00, BLUE = 0x10, DEAD = 0x20, GRAY = 0x30};
};


const std::string _pacman_path = "Images/Creature/Pacman/Pacman.png";
const std::string _point_path = "Images/Points/point.png";
const std::string _energizer_path = "Images/Points/pilule.png";
const int _pacman_scence_index[][2] = {{0,3},{4,29}};
const int _pacman_frames = 29;
//const std::string _pacman_ext = ".png";
namespace Pacman_Sprite {
    enum PACMAN_TYPE{LIVE = 0, DEAD};
    enum PACMAN_ANIM{BEGIN = 0, END};
};

const std::string _sound_paths[] = {"Sounds/choice.wav",
                                    "Sounds/cursor.wav",
                                    "Sounds/chomp.wav",
                                    "Sounds/death.wav",
                                    "Sounds/eatfruit.wav",
                                    "Sounds/eatghost.wav",
                                    "Sounds/extrapac.wav",
                                    "Sounds/intermission.wav"};
enum sound_option {  sCHOICE = 0,
	                 sCURSOR = 1,
	                 sCHOMP = 2,
	                 sDEATH = 3,
	                 sEATFRUIT = 4,
	                 sEATGHOST = 5,
	                 sEXTRAPACMAN = 6,
	                 sINTERMISSION = 7};

enum image_option { iCURSOR  = 0 };

enum background_option { bMENU = 0,
                         bREGLES = 1,
                         bJEU = 2,
                         bSCORES = 3,
                         bOPTIONS = 4,
                         bCREDITS = 5,
                         bQUIT = 6 };
