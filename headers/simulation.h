#pragma once
#include <gtkmm-4.0/gtkmm.h>
#include "ants.h"

class Simulation{
public:
    Simulation(Gtk::DrawingArea*);
    ~Simulation();
    void drawing_function(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void start_simulation();
    void set_labels(Gtk::Label* [9]);
    void update_labels();
    void start_timeout();
    guint timeout_id;
    static gboolean simulation_process(gpointer user_data);
    Gtk::DrawingArea* drawing_area_p;
    Anthill anthill;
    Options options;
    Gtk::Label* labels[9];
};