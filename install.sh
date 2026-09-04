#!/bin/bash
set -e

echo "Installing PyLauncher..."

# Compilar
cmake -B build
cmake --build build

# Crear directorios necesarios
mkdir -p ~/.local/bin
mkdir -p ~/.local/share/applications
mkdir -p ~/.local/share/icons/hicolor/256x256/apps

# Copiar ejecutable
cp build/py-launcher ~/.local/bin/
chmod +x ~/.local/bin/py-launcher

# Copiar ícono
cp icon.svg ~/.local/share/icons/hicolor/256x256/apps/pylauncher.svg

# Copiar .desktop
cp py-launcher.desktop ~/.local/share/applications/
gio set ~/.local/share/applications/py-launcher.desktop metadata::trusted true

echo "✓ PyLauncher instalado correctamente"
echo "  Ejecutable: ~/.local/bin/py-launcher"
echo "  Aparecerá en el menú de aplicaciones en unos segundos"
