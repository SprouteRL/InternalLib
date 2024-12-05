#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include <fstream>

namespace functions // templates can NOT be used in .cpp files apperantly
{
    template <typename... Ty>
    std::string Stringify(Ty&&... args) {
        std::stringstream ss;
        (ss << ... << std::forward<Ty>(args));
        return ss.str(); 
    }

    std::string ReadFile(const std::string& filepath);
}