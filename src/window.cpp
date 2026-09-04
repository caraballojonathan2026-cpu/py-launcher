#include "window.h"
#include "installer.h"

MainWindow::MainWindow() {
    set_title("PyLauncher");
    set_default_size(420, 220);
    set_border_width(16);

    add(m_box);

    m_box.pack_start(m_boton_buscar, Gtk::PACK_SHRINK);
    m_box.pack_start(m_label_ruta, Gtk::PACK_SHRINK);
    m_box.pack_start(m_boton_confirmar, Gtk::PACK_SHRINK);
    m_box.pack_start(m_label_estado, Gtk::PACK_SHRINK);

    // El botón de confirmar arranca deshabilitado hasta que haya una selección
    m_boton_confirmar.set_sensitive(false);

    m_boton_buscar.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_buscar_clicked));
    m_boton_confirmar.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_confirmar_clicked));

    show_all_children();
}

void MainWindow::on_buscar_clicked() {
    Gtk::FileChooserDialog dialog("Seleccioná un .zip o una carpeta",
                                   Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);
    dialog.add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    dialog.add_button("Seleccionar", Gtk::RESPONSE_OK);

    // Filtro para mostrar tanto .zip como carpetas
    auto filtro_zip = Gtk::FileFilter::create();
    filtro_zip->set_name("Archivos .zip");
    filtro_zip->add_pattern("*.zip");
    dialog.add_filter(filtro_zip);
    dialog.set_local_only(true);
    dialog.set_select_multiple(false);

    // Nota: GtkFileChooserDialog en modo OPEN también permite navegar
    // y seleccionar carpetas si el usuario entra en ellas y usa "Seleccionar".
    // Si preferís forzar selección de carpeta, se puede duplicar el diálogo
    // con Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER más adelante.

    int result = dialog.run();
    if (result == Gtk::RESPONSE_OK) {
        m_ruta_seleccionada = dialog.get_filename();
        m_label_ruta.set_text(m_ruta_seleccionada);
        m_boton_confirmar.set_sensitive(true);
        m_label_estado.set_text("");
    }
}

void MainWindow::on_confirmar_clicked() {
    if (m_ruta_seleccionada.empty()) return;

    installer::Result r = installer::install_from_path(m_ruta_seleccionada);
    m_label_estado.set_text(r.message);
}
