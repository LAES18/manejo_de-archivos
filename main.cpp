#include <shlobj.h>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include "Extenciones.h"
#include <windows.h>

namespace fs = std::filesystem;

// Función para convertir una cadena a minúsculas
std::string toLower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

// Función para obtener una lista de las extensiones de archivo más comunes
std::vector<std::string> getFiles(std::string fileType) {
    fileType = toLower(fileType);
    if (fileType == "imagenes") {
        return Imagenes();
    } else if (fileType == "pdf") {
        return Pdf();
    } else if (fileType == "videos") {
        return Videos();
    } else if (fileType == "office") {
        return Office();
    } else if (fileType == "word") {
        return Word();
    } else if (fileType == "excel") {
        return Excel();
    } else if (fileType == "powerpoint") {
        return PowerPoint();
    } else if (fileType == "texto") {
        return Text();
    } else if (fileType == "audio") {
        return Audio();
    } else {
        return {};
    }
}

// Función para seleccionar una carpeta a través de una interfaz
std::string seleccionarCarpeta() {
    BROWSEINFO bi = {0};
    bi.lpszTitle = "Elige una carpeta:";
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != 0) {
        TCHAR path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path)) {
            return path;
        }
    }
    return "";
}

// Función para mover archivos basados en su extensión
void moverArchivos(const std::string& sourceDir, const std::string& targetDir, const std::vector<std::string>& extensions) {
    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        if (std::find(extensions.begin(), extensions.end(), entry.path().extension()) != extensions.end()) {
            fs::path newPath = targetDir / entry.path().filename();
            try {
                fs::rename(entry.path(), newPath);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error al mover el archivo: " << e.what() << std::endl;
            }
        }
    }
}

int main() {
    char path[MAX_PATH];
    HRESULT result = SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, path);
    if (FAILED(result)) {
        std::cerr << "Error al obtener la ruta del escritorio" << std::endl;
        return 1;
    }
    std::string desktopPath = path;

    std::string folderName;
    std::cout << "Introduce el nombre de la carpeta: ";
    std::cin >> folderName;

    int pregunta;
    std::cout << "Donde quieres guardar la carpeta '" << folderName << "': 1-En el escritorio, 2-En una ubicacion espeficica: ";
    std::cin >> pregunta;

    if (pregunta != 1 && pregunta != 2) {
        std::cout << "Opción inválida." << std::endl;
        return 1;
    }

    std::string targetDir;
    if (pregunta == 1) {
        targetDir = desktopPath;
    } else {
        targetDir = seleccionarCarpeta();
        if (targetDir.empty()) {
            std::cerr << "No se seleccionó ninguna carpeta." << std::endl;
            return 1;
        }
    }

    fs::path newFolderPath = targetDir + "/" + folderName;
    try {
        fs::create_directory(newFolderPath);
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error al crear la carpeta: " << e.what() << std::endl;
        return 1;
    }

    std::string fileType;
    std::cout << "Introduce el tipo de archivo que quieres manejar (Imagenes, Pdf, Videos, Documentos Office, Word, Excel, PowerPoint, Texto, Audio): ";
    std::cin >> fileType;

    // Lista de extensiones de archivo
    std::vector<std::string> files = getFiles(fileType);

    // Mueve los archivos al nuevo directorio
    moverArchivos(desktopPath, newFolderPath, files);

    std::cout << "¡Archivos movidos con éxito!" << std::endl;

    return 0;
}
