#pragma once
#include <string>   

const std::string _default_path = "./DataBase";
const std::string _map_file = "./Map/Map.txt";
const std::string _bg_image_paths[5] = {"./Images/Fonds/menu.png",
									"./Images/Fonds/rules.png", 
									"./Images/Fonds/basic_level.png", 
									"./Images/Fonds/scores.png"};
                                    
const std::string _image_paths[] = {"./Images/Divers/cursor.png"};
const std::string _ghost_paths[] = {"./Images/Creature/Ghost/Cyan",
                                    "./Images/Creature/Ghost/Orange",
                                    "./Images/Creature/Ghost/Pink",
                                    "./Images/Creature/Ghost/Red",
                                    "./Images/Creature/Ghost/Blue",
                                    "./Images/Creature/Ghost/Dead"};
                                            
const std::string _ghost_dir[] = {"Left"
                                 "Right"
                                 "Top",
                                 "Bottom"};
                                            
const std::string _ghost_movement[] = {"00",
                                      "01"};
const std::string _ghost_ext = ".png";
namespace Ghost_Sprite {
enum GHOST_TYPE{CYAN = 0, ORANGE, PINK, RED, BLUE, DEAD};
enum GHOST_DIR{LEFT = 0, RIGHT = 1, TOP = 2, BOTTOM = 3};
enum GHOST_STATUS{STAY = 0, MOVE = 1};
}


const std::string _pacman_path = "./Images/Creature/Pacman/Pacman.png";
const int _pacman_scence_index[][2] = {{0,3},{4,29}};
const int _pacman_frames = 29;
//const std::string _pacman_ext = ".png";
namespace Pacman_Sprite {
enum PACMAN_TYPE{LIVE = 0, DEAD};
enum PACMAN_ANIM{BEGIN = 0, END};
}

const std::string _sound_paths[] = {"./Sounds/choice.wav",
                                    "./Sounds/cursor.wav",
                                    "./Sounds/chomp.wav",
                                    "./Sounds/death.wav",
                                    "./Sounds/eatfruit.wav",
                                    "./Sounds/eatghost.wav",
                                    "./Sounds/extrapac.wav",
                                    "./Sounds/intermission.wav"};
enum sound_option {sCHOICE = 0, 
                         sCURSOR = 1, 
                         sCHOMP = 2, 
                         sDEATH = 3, 
                         sEATFRUIT = 4, 
                         sEATGHOST = 5, 
                         sEXTRAPACMAN = 6, 
                         sINTERMISSION = 7};
                    
enum image_option { iCURSOR  = 0};

enum background_option {bMENU = 0, 
                             bREGLES = 1, 
                             bJEU = 2, 
                             bSCORES = 3, 
                             bOPTIONS = 4, 
                             bCREDITS = 5, 
                             bQUIT = 6 };
		