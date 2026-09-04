#pragma once
#include <gtkmm.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow();

private:
    void on_buscar_clicked();
    void on_confirmar_clicked();

    Gtk::Box m_box{Gtk::ORIENTATION_VERTICAL, 12};
    Gtk::Button m_boton_buscar{"Buscar archivo/carpeta"};
    Gtk::Button m_boton_confirmar{"Confirmar instalación"};
    Gtk::Label m_label_ruta{"(ninguna selección todavía)"};
    Gtk::Label m_label_estado{""};

    std::string m_ruta_seleccionada;
};
