#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include <thread>
#include <chrono>
#include "simulation.h"

class Scene{
public:
	void load_css_provider();
	GtkCssProvider* css_provider;
};

class MainScene : public Scene{
public:
	MainScene();
	~MainScene();
    Gtk::Box* get_main_box();
    Gtk::Button* get_button_start();
    Gtk::Button* get_button_options();
    Gtk::Button* get_button_about();

protected:
	Gtk::Box button_box;
	Gtk::Box main_box;
	Gtk::Button button_start;
	Gtk::Button button_options;
	Gtk::Button button_about;
	Gtk::Label label_name;
};

class SimulationScene : public Scene{
public:
	SimulationScene();
	~SimulationScene();
	Gtk::Box* get_main_box();
	void start_simulation();
	void delete_simulation();
	void speed_scale_h();
	void add_food_h();
	void add_material_h();
	void add_enemy_h();
	bool food_auto_h(bool state);
	bool material_auto_h(bool state);
	bool enemies_auto_h(bool state);
	Gtk::Button exit_button;
	Simulation* simulation;
protected:
	Gtk::DrawingArea drawing_area;
	Gtk::Frame frame;
	Gtk::Box main_box;
	Gtk::Box top_box;
	Gtk::Box top_vert_box;
	Gtk::Label possible_population_label;
	Gtk::Label population_label;
	Gtk::Label size_label;
	Gtk::Label food_label;
	Gtk::Label material_label;
	Gtk::Label harvesters_label;
	Gtk::Label builders_label;
	Gtk::Label warriors_label;
	Gtk::Label enemies_label;
	Gtk::Label* labels[9];
	Gtk::Label speed_label;
	Gtk::Scale speed_scale;
	
	Gtk::Box food_auto_box;
	Gtk::Switch food_auto_switch;
	Gtk::Label food_auto_label;
	Gtk::Box material_auto_box;
	Gtk::Switch material_auto_switch;
	Gtk::Label material_auto_label;
	Gtk::Box enemies_auto_box;
	Gtk::Switch enemies_auto_switch;
	Gtk::Label enemies_auto_label;
	Gtk::Box bottom_box;
	Gtk::Button add_food_button;
	Gtk::Button add_material_button;
	Gtk::Button add_enemy_button;
};

class OptionsScene : public Scene{
public:
	OptionsScene();
	~OptionsScene();
	void population_h();
	void speed_h();
	bool food_autospawn_h(bool state);
	void food_rate_h();
	bool material_autospawn_h(bool state);
	void material_rate_h();
	bool enemies_autospawn_h(bool state);
	void enemies_rate_h();
	void button_save_h();

	Options options;
	Gtk::ScrolledWindow scrolled_window;
	Gtk::Box main_box;
	Gtk::Box option_population;
	Gtk::Label label_population;
	Gtk::SpinButton button_population;
	Gtk::Box option_simulation_speed;
	Gtk::Label label_simulation_speed;
	Gtk::Scale scale_simulation_speed;
	Gtk::Box option_food_autospawn;
	Gtk::Label label_food_autospawn;
	Gtk::Switch switch_food_autospawn;
	Gtk::Box option_material_autospawn;
	Gtk::Label label_material_autospawn;
	Gtk::Switch switch_material_autospawn;
	Gtk::Box option_enemies_autospawn;
	Gtk::Label label_enemies_autospawn;
	Gtk::Switch switch_enemies_autospawn;
	Gtk::Box option_food_rate;
	Gtk::Label label_food_rate;
	Gtk::Scale scale_food_rate;
	Gtk::Box option_material_rate;
	Gtk::Label label_material_rate;
	Gtk::Scale scale_material_rate;
	Gtk::Box option_enemies_rate;
	Gtk::Label label_enemies_rate;
	Gtk::Scale scale_enemies_rate;

	Gtk::Box buttons_box;
	Gtk::Button button_exit;
	Gtk::Button button_save;
};