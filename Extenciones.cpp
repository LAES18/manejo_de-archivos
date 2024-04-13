#include <vector>
#include <string>
#include "Extenciones.h"
using namespace std;

std::vector<std::string> Imagenes();

std::vector <string> Imagenes() {
    return {".png", ".jpg", ".jpeg", ".bmp", ".gif", ".tiff", ".ico", ".svg", ".icon"};
}

std::vector<std::string> Pdf() {
    return {".pdf"};
}

std::vector<std::string> Videos() {
    return {".mp4", ".mov", ".avi", ".mkv", ".webm", ".avchd", ".flv", ".swf", ".f4v"};
}

std::vector<std::string> Office() {
    return {".doc", ".docm", ".docx", ".dot", ".dotm", ".dotx", ".xls", ".xlsx", ".xlsm", ".xlt", ".ppt", ".pptx", ".pps", ".pot"};
}

std::vector<std::string> Word() {
    return {".doc", ".docm", ".docx", ".dot", ".dotm", ".dotx"};
}

std::vector<std::string> Excel() {
    return {".xls", ".xlsx", ".xlsm", ".xlt"};
}

std::vector<std::string> PowerPoint() {
    return {".ppt", ".pptx", ".pps", ".pot"};
}

std::vector<std::string> Text() {
    return {".txt", ".rtf", ".tex", ".md"};
}

std::vector<std::string> Audio() {
    return {".mp3", ".wav", ".ogg", ".flac", ".aac", ".m4a"};
}
