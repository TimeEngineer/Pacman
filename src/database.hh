#pragma once
#include <string>   

const std::string _default_path = "./DataBase";
const std::string _bg_image_paths[5] = {"/Images/Fonds/menu.png",
									"/Images/Fonds/rules.png", 
									"/Images/Fonds/basic_level.png", 
									"/Images/Fonds/scores.png"};
                                    
const std::string _image_paths[] = {"/Images/Divers/cursor.png"};

const std::string _sound_paths[] = {"/Sounds/choice.wav",
                                    "/Sounds/cursor.wav",
                                    "/Sounds/chomp.wav",
                                    "/Sounds/death.wav",
                                    "/Sounds/eatfruit.wav",
                                    "/Sounds/eatghost.wav",
                                    "/Sounds/extrapac.wav",
                                    "/Sounds/intermission.wav"};
enum sound_option   {sCHOICE = 0, 
                    sCURSOR = 1, 
                    sCHOMP = 2, 
                    sDEATH = 3, 
                    sEATFRUIT = 4, 
                    sEATGHOST = 5, 
                    sEXPAC = 6, 
                    sINTERMISSION = 7};
                    
enum image_option { iCURSOR  = 0};
