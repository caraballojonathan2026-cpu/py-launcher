# PyLauncher

Herramienta nativa de Linux tipo "apt" con interfaz gráfica GTK para convertir
archivos `.zip` o carpetas de proyectos Python en aplicaciones de escritorio de
fácil acceso. Las apps instaladas aparecen automáticamente en el menú de
aplicaciones del sistema.

## Características

- ✅ Interfaz gráfica nativa GTK (se ve como una app Linux real)
- ✅ Instala proyectos Python como apps del menú de aplicaciones
- ✅ Detecta automáticamente el punto de entrada (`main.py`)
- ✅ Marca los accesos como "confiables" (sin avisos de seguridad molestos)
- ✅ Metadatos completos en el archivo `.desktop` (Nombre, Descripción, Ícono)
- ✅ Compatible con cualquier distro Linux (Ubuntu, Mint, Fedora, Arch, etc.)

## Requisitos

### Ubuntu / Linux Mint / Debian
```bash
sudo apt install build-essential cmake libgtkmm-3.0-dev unzip
```

### Fedora
```bash
sudo dnf install gcc-c++ cmake gtkmm30-devel unzip
```

### Arch Linux
```bash
sudo pacman -S base-devel cmake gtkmm3 unzip
```

## Compilar desde GitHub

```bash
git clone https://github.com/tuusuario/py-launcher.git
cd py-launcher
cmake -B build
cmake --build build
```

## Ejecutar

```bash
./build/py-launcher
```

## Uso

1. Hacé click en **"Buscar archivo/carpeta"**
2. Seleccioná un archivo `.zip` o una carpeta que contenga un proyecto Python
3. Asegurate que el proyecto tenga un `main.py` en la raíz o dentro
4. Hacé click en **"Confirmar instalación"**
5. ¡Listo! La app aparece en el menú de aplicaciones

## Instalación de la carpeta

La carpeta `~/.local/share/app-installer/apps/` es donde se guardan todas las
apps instaladas. Podés navegar ahí para ver/actualizar/eliminar apps manualmente
si lo necesitás.

## Estructura del Proyecto

```
py-launcher/
├── CMakeLists.txt
├── icon.svg                 # Ícono de PyLauncher
├── src/
│   ├── main.cpp            # Punto de entrada
│   ├── window.cpp/.h       # Interfaz GTK
│   └── installer.cpp/.h    # Lógica de instalación
└── README.md
```

## Licencia

MIT — podés usarlo, modificarlo y distribuirlo libremente.