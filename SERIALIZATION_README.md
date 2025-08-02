# Cube Serialization System

This system provides a simple serialization and deserialization solution for the `Cube` class using the nlohmann/json library.

## Features

### 1. Serializer
Converting a `Cube` object to JSON format:

```cpp
Cube cube(Vector3{10.0f, 5.0f, 3.0f}, 2.5f, 1.8f);
nlohmann::json json = cube.Serialize();
```

### 2. Deserializer
Creating a `Cube` object from JSON data:

```cpp
// Update existing object
cube.Deserialize(json);

// Create new object
Cube newCube = Cube::FromJson(json);
```

### 3. File Operations
Saving and loading JSON data from files:

```cpp
// Save
std::ofstream file("cube_data.json");
file << cube.Serialize().dump(4);
file.close();

// Load
std::ifstream file("cube_data.json");
nlohmann::json json;
file >> json;
file.close();
Cube loadedCube = Cube::FromJson(json);
```

## JSON Format

The serializer creates the following JSON structure:

```json
{
    "position": {
        "x": 10.0,
        "y": 5.0,
        "z": 3.0
    },
    "width": 2.5,
    "height": 1.8
}
```

## Usage in the Game

In the main application (`main.cpp`) you can manipulate the cube with ImGui controls and save/load its state:

1. **Position Setup**: Using `SliderFloat3` control
2. **Dimension Setup**: Using `SliderFloat` controls
3. **Save**: "Save Cube to JSON" button
4. **Load**: "Load Cube from JSON" button

## API Reference

### Constructors
- `Cube(Vector3 pos, float width, float height)` - Parameterized constructor
- `Cube()` - Default constructor for deserialization

### Methods
- `nlohmann::json Serialize() const` - Convert object to JSON
- `void Deserialize(const nlohmann::json& json)` - Load JSON data
- `static Cube FromJson(const nlohmann::json& json)` - Create new object from JSON

### Getters
- `Vector3 GetPosition() const` - Get position
- `float GetWidth() const` - Get width
- `float GetHeight() const` - Get height

## Testing

The `serialization_test.cpp` file contains a complete demo program that showcases all functionality.

## Error Handling

The deserializer safely handles missing JSON fields - if a field doesn't exist, the default value remains in effect.
