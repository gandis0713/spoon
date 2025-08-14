#pragma once 

#include "spoon/export.h"
#include <string>
#include <vector>
#include <memory>

namespace spoon {  

class SPOON_EXPORT Model {
public:
    Model() = default;
    ~Model() = default;
    
    bool loadFromFile(const std::string& filePath);
    bool loadFromBuffer(const void* buffer, size_t size);
    
    bool isLoaded() const { return loaded_; }
    const std::string& getModelPath() const { return modelPath_; }
    size_t getModelSize() const { return modelData_.size(); }

private:
    bool loaded_ = false;
    std::string modelPath_;
    std::vector<uint8_t> modelData_;
    
    bool validateTFLiteModel(const void* buffer, size_t size);
};

}