#include "simulation.h"

Simulation::Simulation(Gtk::DrawingArea* drawing_area_p){
    this->drawing_area_p = drawing_area_p;
    timeout_id = 0;
}

Simulation::~Simulation(){
    
}

void Simulation::set_labels(Gtk::Label* labels[9]){
    
    for (int i=0; i < 9; i++){
        this->labels[i] = labels[i];
    }
}

void Simulation::update_labels(){
    labels[0]->set_label("<span font='pixel operator sc 16'>Possible population: " + std::to_string(anthill.possible_population) + "</span>");
    labels[1]->set_label("<span font='pixel operator sc 16'>Population: " + std::to_string(anthill.population) + "</span>");
    labels[2]->set_label("<span font='pixel operator sc 16'>Anthill size: " + std::to_string(anthill.size) + "</span>");
    labels[3]->set_label("<span font='pixel operator sc 16' color = '#00ff00'>Food: " + std::to_string(anthill.food_count) + "</span>");
    labels[4]->set_label("<span font='pixel operator sc 16' color = '#fffa00'>Materials: " + std::to_string(anthill.material_count) + "</span>");
    labels[5]->set_label("<span font='pixel operator sc 16' color = '#0012ff'>Ants harvesters: " + std::to_string(anthill.ants_harvesters.size()) + "</span>");
    labels[6]->set_label("<span font='pixel operator sc 16' color = '#ff754d'>Ants builders: " + std::to_string(anthill.ants_builders.size()) + "</span>");
    labels[7]->set_label("<span font='pixel operator sc 16' color = '#ffbaf2'>Ants warriors: " + std::to_string(anthill.ants_warriors.size()) + "</span>");
    labels[8]->set_label("<span font='pixel operator sc 16' color = '#ff0000'>Enemies: " + std::to_string(anthill.enemies.size()) + "</span>");

}

void Simulation::start_simulation(){
    anthill.options.read_options_from_file();
    options.read_options_from_file();
    start_timeout();
}

void Simulation::start_timeout(){
    timeout_id = g_timeout_add((100 - (int)(options.simulation_speed*90)), simulation_process, this);
}

gboolean Simulation::simulation_process(gpointer data){
    Simulation* simulation = (Simulation *) data;
    simulation->update_labels();
    simulation->anthill.simulate();
    simulation->drawing_area_p->queue_draw();
    return TRUE;
}


void Simulation::drawing_function(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height){
    cr->set_source_rgb(1,1,1);
    cr->rectangle(0,0,width,height);
    cr->fill();
    cr->set_source_rgb(0.859, 0.4, 0);
    cr->rectangle(400-(anthill.size/2),400-(anthill.size/2),anthill.size,anthill.size);
    cr->fill();
    for(int i=0; i < anthill.ants_harvesters.size(); i++){
        cr->set_source_rgb(0, 0.071, 1);
        cr->arc((*std::next(anthill.ants_harvesters.begin(), i)).x, (*std::next(anthill.ants_harvesters.begin(), i)).y, 3, 0, 2 * G_PI);
        cr->fill();
    }
    for(int i=0; i < anthill.ants_builders.size(); i++){
        cr->set_source_rgb(1, 0.467, 0.31);
        cr->arc((*std::next(anthill.ants_builders.begin(), i)).x, (*std::next(anthill.ants_builders.begin(), i)).y, 3, 0, 2 * G_PI);
        cr->fill();
    }
    for(int i=0; i < anthill.ants_warriors.size(); i++){
        cr->set_source_rgb(1, 0.729, 0.957);
        cr->arc((*std::next(anthill.ants_warriors.begin(), i)).x, (*std::next(anthill.ants_warriors.begin(), i)).y, 3, 0, 2 * G_PI);
        cr->fill();
    }

    for(int i=0; i < anthill.food.size(); i++){
        cr->set_source_rgb(0, 1, 0);
        cr->rectangle((*std::next(anthill.food.begin(), i)).x, (*std::next(anthill.food.begin(), i)).y, 10, 10);
        cr->fill();
    }
    for(int i=0; i < anthill.materials.size(); i++){
        cr->set_source_rgb(1, 0.984, 0);
        cr->rectangle((*std::next(anthill.materials.begin(), i)).x, (*std::next(anthill.materials.begin(), i)).y, 10, 10);
        cr->fill();
    }
    for(int i=0; i < anthill.enemies.size(); i++){
        cr->set_source_rgb(1, 0, 0);
        cr->arc((*std::next(anthill.enemies.begin(), i)).x, (*std::next(anthill.enemies.begin(), i)).y, 8, 0, 2 * G_PI);
        cr->fill();
    }


}

