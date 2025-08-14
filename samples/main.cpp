#include <spdlog/spdlog.h>
#include <spoon/model.h>

int main(int argc, char* argv[]) {
    spdlog::info("Hello, World!");
    
    spoon::Model model;
    spdlog::info("Spoon model created successfully!");
    
    return 0;
}