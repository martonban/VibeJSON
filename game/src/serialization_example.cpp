#include "Cube.hpp"
#include <iostream>
#include <fstream>

void SerializationExample() {
    // Create a cube
    Vector3 position = {10.0f, 5.0f, 3.0f};
    Cube originalCube(position, 2.5f, 1.8f);
    
    std::cout << "Original Cube:" << std::endl;
    std::cout << "Position: (" << originalCube.GetPosition().x << ", " 
              << originalCube.GetPosition().y << ", " 
              << originalCube.GetPosition().z << ")" << std::endl;
    std::cout << "Width: " << originalCube.GetWidth() << std::endl;
    std::cout << "Height: " << originalCube.GetHeight() << std::endl;
    
    // Serialize to JSON
    nlohmann::json cubeJson = originalCube.Serialize();
    std::cout << "\nSerialized JSON:" << std::endl;
    std::cout << cubeJson.dump(4) << std::endl;
    
    // Save to file
    std::ofstream file("cube_data.json");
    file << cubeJson.dump(4);
    file.close();
    std::cout << "\nCube data saved to cube_data.json" << std::endl;
    
    // Deserialize from JSON
    Cube deserializedCube = Cube::FromJson(cubeJson);
    
    std::cout << "\nDeserialized Cube:" << std::endl;
    std::cout << "Position: (" << deserializedCube.GetPosition().x << ", " 
              << deserializedCube.GetPosition().y << ", " 
              << deserializedCube.GetPosition().z << ")" << std::endl;
    std::cout << "Width: " << deserializedCube.GetWidth() << std::endl;
    std::cout << "Height: " << deserializedCube.GetHeight() << std::endl;
    
    // Load from file and deserialize
    std::ifstream inputFile("cube_data.json");
    nlohmann::json loadedJson;
    inputFile >> loadedJson;
    inputFile.close();
    
    Cube loadedCube = Cube::FromJson(loadedJson);
    
    std::cout << "\nCube loaded from file:" << std::endl;
    std::cout << "Position: (" << loadedCube.GetPosition().x << ", " 
              << loadedCube.GetPosition().y << ", " 
              << loadedCube.GetPosition().z << ")" << std::endl;
    std::cout << "Width: " << loadedCube.GetWidth() << std::endl;
    std::cout << "Height: " << loadedCube.GetHeight() << std::endl;
}
