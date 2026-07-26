#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include "scenes.h"



class MainWindow : public Gtk::Window
{
public:
	MainWindow();
	~MainWindow() override;
protected:
	MainScene main_scene;
	SimulationScene simulation_scene;
	OptionsScene options_scene;
	void button_start_h();
	void button_options_h();
	void button_exit_h();
	void exit_from_options();
	void show_main_scene();
	void show_simulation_scene();
	void show_options_scene();
	void hide_main_scene();
	void hide_simulation_scene();
	void hide_options_scene();
	void button_exit_simulation_h();
};
