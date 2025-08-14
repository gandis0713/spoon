#include <spdlog/spdlog.h>
#include <spoon/model.h>
#include <filesystem>

int main(int argc, char* argv[]) {
    spdlog::info("TensorFlow Lite Model Loading Example");
    
    if (argc < 1) {
        spdlog::error("Invalid arguments");
        return -1;
    }
    
    // Get the directory where the executable is located
    std::filesystem::path executablePath = std::filesystem::absolute(argv[0]);
    std::filesystem::path executableDir = executablePath.parent_path();
    
    spoon::Model model;
    
    // Try to load each TFLite model from the res folder using absolute paths
    std::vector<std::string> modelFiles = {
        "deeplabv3.tflite",
        "mediapipe.tflite", 
        "selfie_multiclass.tflite"
    };
    
    for (const auto& modelFile : modelFiles) {
        std::filesystem::path absolutePath = executableDir / modelFile;
        std::string absolutePathStr = absolutePath.string();
        
        spdlog::info("Attempting to load: {}", absolutePathStr);
        
        if (model.loadFromFile(absolutePathStr)) {
            spdlog::info("Successfully loaded {} ({} bytes)", 
                        model.getModelPath(), model.getModelSize());
        } else {
            spdlog::error("Failed to load {}", absolutePathStr);
        }
        spdlog::info("---");
    }
    
    return 0;
}