#include <gtkmm-4.0/gtkmm.h>
#include "mainwindow.h"
#include "ants.h"

int main(int argc, char* argv[]){
	auto app = Gtk::Application::create();

	return app->make_window_and_run<MainWindow>(argc, argv);
}
