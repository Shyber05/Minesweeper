#include "textureManager.h"
#include <string>
#include <unordered_map>

// Redeclare variable due to static variable
std::unordered_map<std::string, sf::Texture> TextureManager::textures;
std::string TextureManager::m_imgsDirectory;

void TextureManager::loadTexture(std::string fileName)
{
    std::string path = TextureManager::m_imgsDirectory;
    path += fileName + ".png";

    textures[fileName].loadFromFile(path);
};
sf::Texture& TextureManager::getTexture(std::string textureName)
{
    // Load in file if it doesn't already exist
    if (textures.find(textureName) == textures.end())
        loadTexture(textureName);

    return textures[textureName];
}
void TextureManager::clear()
{
    textures.clear(); // Gets rid of all the textures in map
};
void TextureManager::setDirectory(std::string imgsDirectory)
{
    TextureManager::m_imgsDirectory = imgsDirectory;
}


