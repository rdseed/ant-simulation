#include "options.h"

Options::Options(){
    anthill_population = 3;
    simulation_speed = 0.1;
    food_spawning_rate = 0.1;
    material_spawning_rate = 0.1;
    enemies_spawning_rate = 0.1;
    food_autospawn = false;
    material_autospawn = false;
    enemies_autospawn = false;
}

Options::~Options(){

}

void Options::write_options_to_file(){
    std::fstream file;
    file.open("options.bin", std::ios::binary | std::ios::out);
    file.write((char*)this, sizeof(Options));
    file.close();
}

void Options::read_options_from_file(){
    std::fstream file;
    file.open("options.bin", std::ios::binary | std::ios::in);
    file.read((char*)this, sizeof(Options));
    file.close();
}