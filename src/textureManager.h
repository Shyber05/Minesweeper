#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureManager
{
    static std::unordered_map<std::string, sf::Texture> textures;
    static void loadTexture(std::string textureName);  
    static std::string m_imgsDirectory;
public:
    static sf::Texture& getTexture(std::string textureName);
    static void clear();   
    static void setDirectory(std::string imgDirectory);
};
