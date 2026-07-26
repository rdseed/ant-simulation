#include "mainwindow.h"
#include <iostream>



MainWindow::MainWindow(){
	main_scene.get_button_start()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::button_start_h));
	main_scene.get_button_options()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::button_options_h));
	main_scene.get_button_about()->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::button_exit_h));
	simulation_scene.exit_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::button_exit_simulation_h));
	options_scene.button_exit.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::exit_from_options));

	hide_simulation_scene();
	show_main_scene();
}

MainWindow::~MainWindow(){

}

void MainWindow::show_main_scene(){
	set_title("Anthill Main Menu");
	set_default_size(960, 540);
	main_scene.load_css_provider();
	set_child(*main_scene.get_main_box());
	main_scene.get_main_box()->show();
}

void MainWindow::show_simulation_scene(){
	set_title("Anthill Simulation");
	set_default_size(1200, 980);
	simulation_scene.load_css_provider();
	set_child(*simulation_scene.get_main_box());
	simulation_scene.get_main_box()->show();
	simulation_scene.start_simulation();
}

void MainWindow::show_options_scene(){
	set_title("Anthill Options");
	set_default_size(960, 540);
	options_scene.load_css_provider();
	set_child(options_scene.scrolled_window);
	options_scene.scrolled_window.show();
}

void MainWindow::hide_main_scene(){
	main_scene.get_main_box()->hide();
}

void MainWindow::hide_simulation_scene(){
	simulation_scene.get_main_box()->hide();
}

void MainWindow::hide_options_scene(){
	options_scene.scrolled_window.hide();
}

void MainWindow::button_start_h(){
	hide_main_scene();
	show_simulation_scene();
}

void MainWindow::button_options_h(){
	hide_main_scene();
	show_options_scene();
}

void MainWindow::exit_from_options(){
	hide_options_scene();
	show_main_scene();
}

void MainWindow::button_exit_h(){
	this->destroy();
}

void MainWindow::button_exit_simulation_h(){
	simulation_scene.delete_simulation();
	hide_simulation_scene();
	show_main_scene();
}