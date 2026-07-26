#pragma once
#include <fstream>


class Options{
public:
    Options();
    ~Options();
    unsigned int anthill_population;
    double simulation_speed;
    double food_spawning_rate;
    double material_spawning_rate;
    double enemies_spawning_rate;
    bool food_autospawn;
    bool material_autospawn;
    bool enemies_autospawn;
    void write_options_to_file();
    void read_options_from_file();
};