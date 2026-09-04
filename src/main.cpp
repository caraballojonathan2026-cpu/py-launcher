#include <gtkmm/application.h>
#include "window.h"

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.jonathan.appinstaller");
    MainWindow window;
    return app->run(window);
}
