#include "Cube.hpp"

void Cube::Render() {
    DrawCube(mPos, mWidth, mHeight, 1.0f, RED);
}

nlohmann::json Cube::Serialize() const {
    nlohmann::json json;
    
    // Serialize position
    json["position"]["x"] = mPos.x;
    json["position"]["y"] = mPos.y;
    json["position"]["z"] = mPos.z;
    
    // Serialize dimensions
    json["width"] = mWidth;
    json["height"] = mHeight;
    
    return json;
}

void Cube::Deserialize(const nlohmann::json& json) {
    // Deserialize position
    if (json.contains("position")) {
        mPos.x = json["position"]["x"].get<float>();
        mPos.y = json["position"]["y"].get<float>();
        mPos.z = json["position"]["z"].get<float>();
    }
    
    // Deserialize dimensions
    if (json.contains("width")) {
        mWidth = json["width"].get<float>();
    }
    
    if (json.contains("height")) {
        mHeight = json["height"].get<float>();
    }
}

Cube Cube::FromJson(const nlohmann::json& json) {
    Cube cube;
    cube.Deserialize(json);
    return cube;
}