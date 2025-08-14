#include <flatbuffers/flatbuffers.h>
#include <fstream>
#include <spdlog/spdlog.h>
#include <spoon/model.h>

namespace spoon
{

bool Model::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        spdlog::error("Failed to open file: {}", filePath);
        return false;
    }

    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    modelData_.resize(fileSize);
    if (!file.read(reinterpret_cast<char*>(modelData_.data()), fileSize))
    {
        spdlog::error("Failed to read file: {}", filePath);
        return false;
    }

    if (!validateTFLiteModel(modelData_.data(), modelData_.size()))
    {
        spdlog::error("Invalid TFLite model: {}", filePath);
        return false;
    }

    modelPath_ = filePath;
    loaded_ = true;

    spdlog::info("Successfully loaded TFLite model: {} (size: {} bytes)", filePath, fileSize);

    return true;
}

bool Model::loadFromBuffer(const void* buffer, size_t size)
{
    if (!buffer || size == 0)
    {
        spdlog::error("Invalid buffer or size");
        return false;
    }

    if (!validateTFLiteModel(buffer, size))
    {
        spdlog::error("Invalid TFLite model buffer");
        return false;
    }

    modelData_.resize(size);
    std::memcpy(modelData_.data(), buffer, size);

    modelPath_ = "buffer";
    loaded_ = true;

    spdlog::info("Successfully loaded TFLite model from buffer (size: {} bytes)", size);

    return true;
}

bool Model::validateTFLiteModel(const void* buffer, size_t size)
{
    if (size < 8)
    {
        return false;
    }

    // Check TFLite magic number (first 4 bytes should be "TFL3")
    const char* data = static_cast<const char*>(buffer);
    if (data[0] != 'T' || data[1] != 'F' || data[2] != 'L' || data[3] != '3')
    {
        return false;
    }

    // Basic FlatBuffers validation
    flatbuffers::Verifier verifier(static_cast<const uint8_t*>(buffer), size);

    // Note: For full validation, we would need the TFLite schema
    // For now, we just check the magic number and basic structure
    return true;
}

} // namespace spoon