#include "scenes.h"
#include <iostream>
#include <string>

void Scene::load_css_provider(){
	gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

MainScene::MainScene(){
    css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css_provider, "style/mainstyle.css");
	main_box.set_orientation(Gtk::Orientation::VERTICAL);
	
	label_name.set_label("<span foreground='orange' font='Ant 150'>A</span><span foreground='orange' font='pixel operator sc 90'>nthill</span>");
	label_name.set_use_markup(true);
	label_name.set_margin_top(20);
	main_box.append(label_name);

	button_box.set_margin_top(60);
	button_box.set_margin_start(80);
	button_box.set_margin_end(80);
    button_box.set_margin_bottom(180);
	button_box.set_spacing(100);
	button_box.set_size_request(-1, 90);
    button_box.set_valign(Gtk::Align::END);
    button_box.set_halign(Gtk::Align::CENTER);
    button_box.set_vexpand(true);
	button_box.set_homogeneous(true);
	main_box.append(button_box);

	button_start.set_label("Start");
	button_box.append(button_start);

	button_options.set_label("Options");
	button_box.append(button_options);

	button_about.set_label("Exit");
	button_box.append(button_about);
}

MainScene::~MainScene(){

}

Gtk::Box* MainScene::get_main_box(){
    return &main_box;
}

Gtk::Button* MainScene::get_button_about(){
    return &button_about;
}

Gtk::Button* MainScene::get_button_start(){
    return &button_start;
}

Gtk::Button* MainScene::get_button_options(){
    return &button_options;
}

SimulationScene::SimulationScene(){
	css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css_provider, "style/mainstyle.css");

	main_box.set_orientation(Gtk::Orientation::VERTICAL);

	main_box.append(top_box);

	frame.set_margin(20);
	top_box.append(frame);

	drawing_area.set_content_width(800);
	drawing_area.set_content_height(800);
	frame.set_child(drawing_area);

	top_vert_box.set_margin(20);
	top_vert_box.set_orientation(Gtk::Orientation::VERTICAL);
	top_vert_box.set_spacing(20);
	top_box.append(top_vert_box);

	exit_button.set_label("Exit");
	exit_button.set_halign(Gtk::Align::CENTER);
	top_vert_box.append(exit_button);


	

	possible_population_label.set_label("<span font='pixel operator sc 18'>Possible population: </span>");
	possible_population_label.set_use_markup(true);
	top_vert_box.append(possible_population_label);
	labels[0] = &possible_population_label;

	population_label.set_label("<span font='pixel operator sc 18'>Population: </span>");
	population_label.set_use_markup(true);
	top_vert_box.append(population_label);
	labels[1] = &population_label;

	size_label.set_label("<span font='pixel operator sc 18'>Anthill size: </span>");
	size_label.set_use_markup(true);
	top_vert_box.append(size_label);
	labels[2] = &size_label;

	food_label.set_label("<span font='pixel operator sc 18' color = '#00ff00'>Food: </span>");
	food_label.set_use_markup(true);
	top_vert_box.append(food_label);
	labels[3] = &food_label;

	material_label.set_label("<span font='pixel operator sc 18' color = '#fffa00'>Materials: </span>");
	material_label.set_use_markup(true);
	top_vert_box.append(material_label);
	labels[4] = &material_label;

	harvesters_label.set_label("<span font='pixel operator sc 18' color = '#0012ff'>Ants harvesters: </span>");
	harvesters_label.set_use_markup(true);
	top_vert_box.append(harvesters_label);
	labels[5] = &harvesters_label;

	builders_label.set_label("<span font='pixel operator sc 18' color = '#ff754d'>Ants builders: </span>");
	builders_label.set_use_markup(true);
	top_vert_box.append(builders_label);
	labels[6] = &builders_label;

	warriors_label.set_label("<span font='pixel operator sc 18' color = '#ffbaf2'>Ants warriors: </span>");
	warriors_label.set_use_markup(true);
	top_vert_box.append(warriors_label);
	labels[7] = &warriors_label;

	enemies_label.set_label("<span font='pixel operator sc 18' color = '#ff0000'>Enemies: </span>");
	enemies_label.set_use_markup(true);
	top_vert_box.append(enemies_label);
	labels[8] = &enemies_label;

	

	speed_label.set_label("<span font='pixel operator sc 18'>Simulation Speed</span>");
	speed_label.set_use_markup(true);
	top_vert_box.append(speed_label);

	speed_scale.set_orientation(Gtk::Orientation::HORIZONTAL);
	speed_scale.set_range(0.1,1);
	speed_scale.set_digits(2);
	speed_scale.set_draw_value(true);
	speed_scale.set_size_request(300, -1);
	top_vert_box.append(speed_scale);
	speed_scale.signal_value_changed().connect(sigc::mem_fun(*this, &SimulationScene::speed_scale_h));

	food_auto_box.set_margin(20);
	food_auto_box.set_spacing(20);
	food_auto_box.set_orientation(Gtk::Orientation::HORIZONTAL);
	top_vert_box.append(food_auto_box);

	food_auto_label.set_label("<span font='pixel operator sc 18'>Food autospawn</span>");
	food_auto_label.set_use_markup(true);
	food_auto_box.append(food_auto_label);

	food_auto_switch.set_size_request(80, 10);
	food_auto_switch.signal_state_set().connect(sigc::mem_fun(*this, &SimulationScene::food_auto_h), false);
	food_auto_box.append(food_auto_switch);

	material_auto_box.set_margin(20);
	material_auto_box.set_spacing(20);
	material_auto_box.set_orientation(Gtk::Orientation::HORIZONTAL);
	top_vert_box.append(material_auto_box);

	material_auto_label.set_label("<span font='pixel operator sc 18'>Material autospawn</span>");
	material_auto_label.set_use_markup(true);
	material_auto_box.append(material_auto_label);

	material_auto_switch.set_size_request(80, 10);
	material_auto_switch.signal_state_set().connect(sigc::mem_fun(*this, &SimulationScene::material_auto_h), false);
	material_auto_box.append(material_auto_switch);


	enemies_auto_box.set_margin(20);
	enemies_auto_box.set_spacing(20);
	enemies_auto_box.set_orientation(Gtk::Orientation::HORIZONTAL);
	top_vert_box.append(enemies_auto_box);

	enemies_auto_label.set_label("<span font='pixel operator sc 18'>Enemies autospawn</span>");
	enemies_auto_label.set_use_markup(true);
	enemies_auto_box.append(enemies_auto_label);

	enemies_auto_switch.set_size_request(80, 10);
	enemies_auto_switch.signal_state_set().connect(sigc::mem_fun(*this, &SimulationScene::enemies_auto_h), false);
	enemies_auto_box.append(enemies_auto_switch);

	bottom_box.set_margin(10);
	bottom_box.set_spacing(30);
	main_box.append(bottom_box);

	add_food_button.set_label("Add Food");
	add_food_button.signal_clicked().connect(sigc::mem_fun(*this, &SimulationScene::add_food_h));
	bottom_box.append(add_food_button);

	add_material_button.set_label("Add Material");
	add_material_button.signal_clicked().connect(sigc::mem_fun(*this, &SimulationScene::add_material_h));
	bottom_box.append(add_material_button);

	add_enemy_button.set_label("Add Enemy");
	add_enemy_button.signal_clicked().connect(sigc::mem_fun(*this, &SimulationScene::add_enemy_h));
	bottom_box.append(add_enemy_button);


}

SimulationScene::~SimulationScene(){
	
}

bool SimulationScene::food_auto_h(bool state){
	simulation->anthill.options.food_autospawn = state;
	return false;
}

bool SimulationScene::material_auto_h(bool state){
	simulation->anthill.options.material_autospawn = state;
	return false;
}

bool SimulationScene::enemies_auto_h(bool state){
	simulation->anthill.options.enemies_autospawn = state;
	return false;
}

void SimulationScene::add_food_h(){
	simulation->anthill.food.push_back(Food());
}
void SimulationScene::add_material_h(){
	simulation->anthill.materials.push_back(Material());
}
void SimulationScene::add_enemy_h(){
	simulation->anthill.enemies.push_back(Enemy());
}

void SimulationScene::speed_scale_h(){
	if(simulation->timeout_id != 0){
		g_source_remove(simulation->timeout_id);
		simulation->options.simulation_speed = speed_scale.get_value();
		simulation->start_timeout();
	}
}

void SimulationScene::delete_simulation(){
	if(simulation->timeout_id != 0){
		g_source_remove(simulation->timeout_id);
	}
	delete simulation;
}

void SimulationScene::start_simulation(){
	simulation = new Simulation(&drawing_area);
	drawing_area.set_draw_func(sigc::mem_fun(*simulation, &Simulation::drawing_function));
	Options options;
	options.read_options_from_file();
	speed_scale.set_value(options.simulation_speed);
	food_auto_switch.set_active(options.food_autospawn);
	material_auto_switch.set_active(options.material_autospawn);
	enemies_auto_switch.set_active(options.enemies_autospawn);

	simulation->set_labels(labels);
	simulation->start_simulation();
}

Gtk::Box* SimulationScene::get_main_box(){
	return &main_box;
}

OptionsScene::OptionsScene(){
	css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css_provider, "style/mainstyle.css");

	options.read_options_from_file();

	scrolled_window.set_child(main_box);

	main_box.set_orientation(Gtk::Orientation::VERTICAL);

	option_population.set_margin(20);
	option_population.set_spacing(60);
	main_box.append(option_population);
	
	label_population.set_label("<span font='pixel operator sc 24'>Beginning population</span>");
	label_population.set_use_markup(true);
	option_population.append(label_population);
	
	
	button_population.set_range(3, 90);
	button_population.set_increments(3,0);
	button_population.set_value(options.anthill_population);
	button_population.set_snap_to_ticks(true);
	option_population.append(button_population);
	button_population.signal_value_changed().connect(sigc::mem_fun(*this, &OptionsScene::population_h));

	option_simulation_speed.set_margin(20);
	option_simulation_speed.set_spacing(60);
	
	main_box.append(option_simulation_speed);

	label_simulation_speed.set_label("<span font='pixel operator sc 24'>Simulation speed</span>");
	label_simulation_speed.set_use_markup(true);
	option_simulation_speed.append(label_simulation_speed);

	scale_simulation_speed.set_orientation(Gtk::Orientation::HORIZONTAL);
	scale_simulation_speed.set_range(0.1,1);
	scale_simulation_speed.set_digits(2);
	scale_simulation_speed.set_value(options.simulation_speed);
	scale_simulation_speed.set_draw_value(true);
	scale_simulation_speed.set_size_request(300, -1);
	option_simulation_speed.append(scale_simulation_speed);
	scale_simulation_speed.signal_value_changed().connect(sigc::mem_fun(*this, &OptionsScene::speed_h));


	option_food_autospawn.set_margin(20);
	option_food_autospawn.set_spacing(60);
	
	main_box.append(option_food_autospawn);

	label_food_autospawn.set_label("<span font='pixel operator sc 24'>Spawn food automatically</span>");
	label_food_autospawn.set_use_markup(true);
	option_food_autospawn.append(label_food_autospawn);

	
	switch_food_autospawn.set_size_request(80, 10);
	switch_food_autospawn.set_active(options.food_autospawn);
	option_food_autospawn.append(switch_food_autospawn);
	switch_food_autospawn.signal_state_set().connect(sigc::mem_fun(*this, &OptionsScene::food_autospawn_h), false);

	option_food_rate.set_margin(20);
	option_food_rate.set_spacing(60);

	main_box.append(option_food_rate);

	label_food_rate.set_label("<span font='pixel operator sc 24'>Food spawning rate</span>");
	label_food_rate.set_use_markup(true);
	option_food_rate.append(label_food_rate);

	scale_food_rate.set_orientation(Gtk::Orientation::HORIZONTAL);
	scale_food_rate.set_range(0.1,1);
	scale_food_rate.set_digits(2);
	scale_food_rate.set_draw_value(true);
	scale_food_rate.set_size_request(300, -1);
	scale_food_rate.set_value(options.food_spawning_rate);
	option_food_rate.append(scale_food_rate);
	scale_food_rate.signal_value_changed().connect(sigc::mem_fun(*this, &OptionsScene::food_rate_h));


	if (!options.food_autospawn){
		option_food_rate.hide();
	}

	option_material_autospawn.set_margin(20);
	option_material_autospawn.set_spacing(60);
	
	main_box.append(option_material_autospawn);

	label_material_autospawn.set_label("<span font='pixel operator sc 24'>Spawn materials automatically</span>");
	label_material_autospawn.set_use_markup(true);
	option_material_autospawn.append(label_material_autospawn);

	
	switch_material_autospawn.set_size_request(80, 10);
	switch_material_autospawn.set_active(options.material_autospawn);
	option_material_autospawn.append(switch_material_autospawn);
	switch_material_autospawn.signal_state_set().connect(sigc::mem_fun(*this, &OptionsScene::material_autospawn_h), false);


	option_material_rate.set_margin(20);
	option_material_rate.set_spacing(60);

	main_box.append(option_material_rate);

	label_material_rate.set_label("<span font='pixel operator sc 24'>Materials spawning rate</span>");
	label_material_rate.set_use_markup(true);
	option_material_rate.append(label_material_rate);

	scale_material_rate.set_orientation(Gtk::Orientation::HORIZONTAL);
	scale_material_rate.set_range(0.1,1);
	scale_material_rate.set_digits(2);
	scale_material_rate.set_draw_value(true);
	scale_material_rate.set_size_request(300, -1);
	scale_material_rate.set_value(options.material_spawning_rate);
	option_material_rate.append(scale_material_rate);
	scale_material_rate.signal_value_changed().connect(sigc::mem_fun(*this, &OptionsScene::material_rate_h));

	if (!options.material_autospawn){
		option_material_rate.hide();
	}
	
	option_enemies_autospawn.set_margin(20);
	option_enemies_autospawn.set_spacing(60);
	
	main_box.append(option_enemies_autospawn);

	label_enemies_autospawn.set_label("<span font='pixel operator sc 24'>Spawn enemies automatically</span>");
	label_enemies_autospawn.set_use_markup(true);
	option_enemies_autospawn.append(label_enemies_autospawn);

	
	switch_enemies_autospawn.set_size_request(80, 10);
	switch_enemies_autospawn.set_active(options.enemies_autospawn);
	option_enemies_autospawn.append(switch_enemies_autospawn);
	switch_enemies_autospawn.signal_state_set().connect(sigc::mem_fun(*this, &OptionsScene::enemies_autospawn_h), false);


	option_enemies_rate.set_margin(20);
	option_enemies_rate.set_spacing(60);

	main_box.append(option_enemies_rate);

	label_enemies_rate.set_label("<span font='pixel operator sc 24'>Enemies spawning rate</span>");
	label_enemies_rate.set_use_markup(true);
	option_enemies_rate.append(label_enemies_rate);

	scale_enemies_rate.set_orientation(Gtk::Orientation::HORIZONTAL);
	scale_enemies_rate.set_range(0.1,1);
	scale_enemies_rate.set_digits(2);
	scale_enemies_rate.set_draw_value(true);
	scale_enemies_rate.set_size_request(300, -1);
	scale_enemies_rate.set_value(options.enemies_spawning_rate);
	option_enemies_rate.append(scale_enemies_rate);
	scale_enemies_rate.signal_value_changed().connect(sigc::mem_fun(*this, &OptionsScene::enemies_rate_h));

	if (!options.enemies_autospawn){
		option_enemies_rate.hide();
	}

	buttons_box.set_margin(20);
	buttons_box.set_homogeneous(true);
	buttons_box.set_spacing(40);
	main_box.append(buttons_box);

	button_save.set_label("Save");
	button_save.signal_clicked().connect(sigc::mem_fun(*this, &OptionsScene::button_save_h));
	buttons_box.append(button_save);

	button_exit.set_label("Exit");
	buttons_box.append(button_exit);

}
OptionsScene::~OptionsScene(){

}

void OptionsScene::button_save_h(){
	options.write_options_to_file();
}


void OptionsScene::population_h(){
	options.anthill_population = button_population.get_value();
}

bool OptionsScene::food_autospawn_h(bool state){
	options.food_autospawn = state;
	switch(state){
		case true:
		option_food_rate.show();
		break;
		case false:
		option_food_rate.hide();
		break;
	}
	return false;
}

bool OptionsScene::material_autospawn_h(bool state){
	options.material_autospawn = state;
	switch(state){
		case true:
		option_material_rate.show();
		break;
		case false:
		option_material_rate.hide();
		break;
	}
	return false;
}

bool OptionsScene::enemies_autospawn_h(bool state){
	options.enemies_autospawn = state;
	switch(state){
		case true:
		option_enemies_rate.show();
		break;
		case false:
		option_enemies_rate.hide();
		break;
	}
	return false;
}

void OptionsScene::speed_h(){
	options.simulation_speed = scale_simulation_speed.get_value();
}

void OptionsScene::food_rate_h(){
	options.food_spawning_rate = scale_food_rate.get_value();
}

void OptionsScene::material_rate_h(){
	options.material_spawning_rate = scale_material_rate.get_value();
}
void OptionsScene::enemies_rate_h(){
	options.enemies_spawning_rate = scale_enemies_rate.get_value();
}