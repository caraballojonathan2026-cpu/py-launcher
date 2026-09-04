#include "installer.h"

#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <optional>

namespace fs = std::filesystem;

namespace installer {

namespace {

// Carpeta donde vamos a dejar copiadas/extraídas las apps instaladas
fs::path apps_root() {
    const char* home = std::getenv("HOME");
    fs::path root = fs::path(home ? home : ".") / ".local" / "share" / "app-installer" / "apps";
    fs::create_directories(root);
    return root;
}

fs::path desktop_entries_dir() {
    const char* home = std::getenv("HOME");
    fs::path dir = fs::path(home ? home : ".") / ".local" / "share" / "applications";
    fs::create_directories(dir);
    return dir;
}

// Nombre de la app derivado del nombre del zip/carpeta (sin extensión)
std::string derive_app_name(const fs::path& input) {
    return input.stem().string();
}

// Busca recursivamente un main.py dentro de una carpeta
std::optional<fs::path> find_entrypoint(const fs::path& dir) {
    if (!fs::exists(dir) || !fs::is_directory(dir)) return std::nullopt;
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file() && entry.path().filename() == "main.py") {
            return entry.path();
        }
    }
    return std::nullopt;
}

// Extrae un .zip usando el comando `unzip` del sistema
bool extract_zip(const fs::path& zip_path, const fs::path& dest_dir) {
    fs::create_directories(dest_dir);
    std::ostringstream cmd;
    cmd << "unzip -o -q '" << zip_path.string() << "' -d '" << dest_dir.string() << "'";
    int ret = std::system(cmd.str().c_str());
    return ret == 0;
}

// Marca el .desktop como ejecutable y confiable (evita el aviso de "no confiable" en GNOME/Nautilus)
void make_trusted(const fs::path& desktop_file) {
    fs::permissions(desktop_file,
        fs::perms::owner_all | fs::perms::group_read | fs::perms::group_exec |
        fs::perms::others_read | fs::perms::others_exec,
        fs::perm_options::add);

    std::ostringstream cmd;
    cmd << "gio set '" << desktop_file.string() << "' metadata::trusted true 2>/dev/null";
    std::system(cmd.str().c_str()); // si falla (ej. no hay gio), no es crítico
}

} // namespace

Result install_from_path(const std::string& input_path) {
    fs::path input(input_path);

    if (!fs::exists(input)) {
        return {false, "La ruta seleccionada no existe."};
    }

    std::string app_name = derive_app_name(input);
    fs::path install_dir = apps_root() / app_name;

    // 1. Extraer o copiar el proyecto a la carpeta de apps instaladas
    if (input.extension() == ".zip") {
        if (!extract_zip(input, install_dir)) {
            return {false, "No se pudo extraer el archivo .zip (¿está instalado 'unzip'?)."};
        }
    } else if (fs::is_directory(input)) {
        std::error_code ec;
        fs::create_directories(install_dir);
        fs::copy(input, install_dir, fs::copy_options::recursive | fs::copy_options::overwrite_existing, ec);
        if (ec) {
            return {false, "No se pudo copiar la carpeta: " + ec.message()};
        }
    } else {
        return {false, "La ruta debe ser un archivo .zip o una carpeta."};
    }

    // 2. Buscar el punto de entrada (main.py)
    auto entrypoint = find_entrypoint(install_dir);
    if (!entrypoint) {
        return {false, "No se encontró un 'main.py' dentro del proyecto seleccionado."};
    }

    // 3. Generar el archivo .desktop
    fs::path desktop_file = desktop_entries_dir() / (app_name + ".desktop");
    std::ofstream out(desktop_file);
    if (!out) {
        return {false, "No se pudo crear el archivo .desktop."};
    }

    out << "[Desktop Entry]\n"
        << "Type=Application\n"
        << "Name=" << app_name << "\n"
        << "Exec=python3 \"" << entrypoint->string() << "\"\n"
        << "Terminal=false\n"
        << "Categories=Utility;\n"
        << "Icon=applications-development\n";
    out.close();

    // 4. Permisos + marcar como confiable
    make_trusted(desktop_file);

    return {true, "'" + app_name + "' se instaló correctamente y ya aparece en el menú de aplicaciones."};
}

} // namespace installer
