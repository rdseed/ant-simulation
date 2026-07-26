#include "ants.h"

Anthill::Anthill(){
  options.read_options_from_file();
  possible_population = options.anthill_population;
  population = possible_population;

  for (int i=0; i < population/3; i++){
    ants_harvesters.push_back(AntFoodHarvester(this, &food));
  }
  for (int i=0; i < population/3; i++){
    ants_builders.push_back(AntBuilder(this, &materials));
  }
  for (int i=0; i < population/3; i++){
    ants_warriors.push_back(AntWarrior(this, &enemies));
    std::list<AntWarrior>::iterator it = std::next((ants_warriors).begin(), i);
    (*it).set_self_it(it);
  }
  frame_count_food = 0;
  frame_count_materials = 0;
  frame_count_enemies = 0;
  


  material_count = 0;
  food_count = 0;
  size = 20;
  srand(time(0));
}
Anthill::~Anthill(){

}

void Anthill::simulate(){
  if (material_count > 0){
    if (size < 100){
      size++;
    }
    if (possible_population < 600){
      possible_population++;
    }
    material_count--;
  }
  if (possible_population > population and food_count > 0){
    if (ants_harvesters.size() < ants_warriors.size()){
      ants_harvesters.push_back(AntFoodHarvester(this, &food));
      food_count--;
      population++;
      return;
    }
    if (ants_builders.size() < ants_harvesters.size()){
      ants_builders.push_back(AntBuilder(this, &materials));
      food_count--;
      population++;
      return;
    }
    if (ants_warriors.size() < possible_population){
      ants_warriors.push_back(AntWarrior(this, &enemies));
      std::list<AntWarrior>::iterator it = std::next((ants_warriors).begin(), ants_warriors.size()-1);
      it->set_self_it(it);
      food_count--;
      population++;
      return;
    }
  }
  if (options.food_autospawn){
    autospawn_food();
  }
  if (options.material_autospawn){
    autospawn_materials();
  }
  if (options.enemies_autospawn){
    autospawn_enemies();
  }
  for (int i=0; i < ants_harvesters.size(); i++){
    (*std::next(ants_harvesters.begin(), i)).update_position();
  }
  for (int i=0; i < ants_builders.size(); i++){
    (*std::next(ants_builders.begin(), i)).update_position();
  }
  for (int i=0; i < ants_warriors.size(); i++){
    (*std::next(ants_warriors.begin(), i)).update_position();
  }
  check_enemies();
}

void Anthill::autospawn_food(){
  if (frame_count_food == (100-((int)(options.food_spawning_rate * 80)))){
    food.push_back(Food());
    frame_count_food = 0;
    return;
  }
  frame_count_food++;
}

void Anthill::autospawn_materials(){
  if (frame_count_materials ==  (100-((int)(options.material_spawning_rate * 80)))){
    materials.push_back(Material());
    frame_count_materials = 0;
    return;
  }
  frame_count_materials++;
}

void Anthill::autospawn_enemies(){
  if (frame_count_enemies == (150-((int)(options.enemies_spawning_rate * 80)))){
    enemies.push_back(Enemy());
    frame_count_enemies = 0;
    return;
  }
  frame_count_enemies++;
}

void Anthill::check_enemies(){
  std::list<Enemy>::iterator enemy_it; 
  std::list<AntFoodHarvester>::iterator ant_harvester_it;
  std::list<AntBuilder>::iterator ant_builder_it;
  for (int i=0; i < enemies.size(); i++){
    enemy_it = std::next(enemies.begin(), i);
    
    if (enemy_it->attacking == false){
      int dx; 
      int dy;
      double distance;
      double smallest_distance = 800;

      for (int j=0; j < ants_harvesters.size(); j++){
        ant_harvester_it = std::next(ants_harvesters.begin(), j);

        if ((*ant_harvester_it).attacked == false){
          enemy_it->attacking = true;
          dx = ant_harvester_it->x - enemy_it->x;
          dy = ant_harvester_it->y - enemy_it->y;

          distance = sqrt(dx * dx + dy * dy);

          if (distance < smallest_distance){
            smallest_distance = distance;
            enemy_it->ant_harvester_target_it = ant_harvester_it;
          }
        }
      }
      if (enemy_it->attacking == true){
        enemy_it->ant_harvester_target_it->attacked = true;
        enemy_it->harvester = true;
        return;
      }
      for (int j=0; j < ants_builders.size(); j++){
        ant_builder_it = std::next(ants_builders.begin(), j);

        if ((*ant_builder_it).attacked == false){
          enemy_it->attacking = true;
          dx = ant_builder_it->x - enemy_it->x;
          dy = ant_builder_it->y - enemy_it->y;

          distance = sqrt(dx * dx + dy * dy);

          if (distance < smallest_distance){
            smallest_distance = distance;
            enemy_it->ant_builder_target_it = ant_builder_it;
          }
        }
      }
      if (enemy_it->attacking == true){
        enemy_it->ant_builder_target_it->attacked = true;
        enemy_it->harvester = false;
        return;
      }
    }
    else{
      if (enemy_it->harvester == true){
        int dx = enemy_it->ant_harvester_target_it->x - enemy_it->x;
        int dy = enemy_it->ant_harvester_target_it->y - enemy_it->y;

        double distance = sqrt(dx * dx + dy * dy);

        if (distance <= 2){
          ants_harvesters.erase(enemy_it->ant_harvester_target_it);
          population--;
          enemy_it->attacking = false;
        }
        else{
          double ratio = enemy_it->speed / distance;

          enemy_it->x += dx * ratio;
          enemy_it->y += dy * ratio;
        }
      }
      else{
        int dx = enemy_it->ant_builder_target_it->x - enemy_it->x;
        int dy = enemy_it->ant_builder_target_it->y - enemy_it->y;

        double distance = sqrt(dx * dx + dy * dy);

        if (distance <= 2){
          ants_builders.erase(enemy_it->ant_builder_target_it);
          population--;
          enemy_it->attacking = false;
        }
        else{
          double ratio = enemy_it->speed / distance;

          enemy_it->x += dx * ratio;
          enemy_it->y += dy * ratio;
        }
      }
    }
  }
}

bool Anthill::check_enemy_presense(std::list<Enemy>::iterator iterator)
{
  for (int i=0; i<enemies.size(); i++){
    if (std::next(enemies.begin(), i) == iterator){
      return true;
    }
  }
  return false;
}

std::mt19937 Ant::gen(std::random_device{}());
std::uniform_int_distribution<> Ant::distr(-step,step);
int Ant::step = 3;

Ant::Ant(Anthill* anthill_p){
  x = 400 + distr(gen);
  y = 400 + distr(gen);
  action = Action::WANDERING;
  this->anthill_p = anthill_p;
  attacked = false;
}

Ant::~Ant(){

}

void Ant::do_when_target(){}
void Ant::do_when_wandering(){}

void Ant::move_in_random_direction(){
  int dx = distr(gen);
  int dy = distr(gen);

  double x_new;
  double y_new;

  x_new = x + dx;
  y_new = y + dy;

  if (x_new < 800 and x_new > 0){
    if(y_new < 800 and y_new > 0){
      y = y_new;
    }
    else{
      y = -y_new;
    }
    x = x_new;
  }
  else{
    if(y_new < 800 and y_new > 0){
      y = y_new;
    }
    else{
      y = -y_new;
    }
    x = -x_new;
  }
}

void Ant::move_to_point(int point_x, int point_y){
  int dx = point_x - x;
  int dy = point_y - y;

  double distance = sqrt(dx * dx + dy * dy);
  double ratio = step / distance;

  x += dx * ratio;
  y += dy * ratio;
}

void Ant::update_position(){
  switch(action){
    case Action::WANDERING:
      do_when_wandering();
      break;
    case Action::MOVING_TO_TARGET:
      do_when_target();
      break;
  }
}


AntFoodHarvester::AntFoodHarvester(Anthill* anthill_p, std::list<Food>* food_p) : Ant(anthill_p){
  this->food_p = food_p;
  has_food = false;
  moving_to_anthill = false;
}

AntFoodHarvester::~AntFoodHarvester(){

}

void AntFoodHarvester::set_self_it(std::list<AntFoodHarvester>::iterator self_it){
  this->self_it = self_it;
}

void AntFoodHarvester::check_food_distance(){
  double distance;
  int dx;
  int dy;
  int smallest_distance = 800;
  bool found_food = false;
  for (int i=0; i < food_p->size(); i++){
    dx = x - (*std::next((*food_p).begin(), i)).x;
    dy = y - (*std::next((*food_p).begin(), i)).y;
    distance = sqrt(dx * dx + dy * dy);
    if((*std::next((*food_p).begin(), i)).is_active == true){
      if (distance < smallest_distance){
        target_it = std::next((*food_p).begin(), i);
        smallest_distance = distance;
      }
    found_food = true;
    }
    
  }
  if (found_food == true){
    action = Action::MOVING_TO_TARGET;
    target_it->is_active = false;
    return;
  }
}

void AntFoodHarvester::check_target_distance(){
  if(moving_to_anthill == false){
    int dx = x - target_it->x;
    int dy = y - target_it->y;
    double distance = sqrt(dx * dx + dy * dy);
    if (distance <= 3){
      has_food = true;
      (*food_p).erase(target_it);
      moving_to_anthill = true;
    }
  }else{
    int dx = x - 400;
    int dy = y - 400;
    double distance = sqrt(dx * dx + dy * dy);
    if (distance <= 3){
      has_food = false;
      moving_to_anthill = false;
      anthill_p->food_count += 1;
      action = Action::WANDERING;
    }
  }
  
}

void AntFoodHarvester::do_when_wandering(){
  check_food_distance();
  move_in_random_direction();
}

void AntFoodHarvester::do_when_target(){
  check_target_distance();
  if (action == Action::MOVING_TO_TARGET){
    if (moving_to_anthill == false){
      move_to_point(target_it->x, target_it->y);
    }else{
      move_to_point(400, 400);
    }
  }
  
  
}

AntBuilder::AntBuilder(Anthill* anthill_p, std::list<Material>* material_p) : Ant(anthill_p){
  this->material_p = material_p;
  has_material = false;
  moving_to_anthill = false;
}

AntBuilder::~AntBuilder(){

}

void AntBuilder::set_self_it(std::list<AntBuilder>::iterator self_it){
  this->self_it = self_it;
}

void AntBuilder::check_material_distance(){
  double distance;
  int dx;
  int dy;
  int smallest_distance = 800;
  bool found_material = false;
  for (int i=0; i < material_p->size(); i++){
    dx = x - (*std::next((*material_p).begin(), i)).x;
    dy = y - (*std::next((*material_p).begin(), i)).y;
    distance = sqrt(dx * dx + dy * dy);
    if((*std::next((*material_p).begin(), i)).is_active == true){
      if (distance < smallest_distance){
        target_it = std::next((*material_p).begin(), i);
        smallest_distance = distance;
      }
    found_material = true;
    }
  }
  if (found_material == true){
    action = Action::MOVING_TO_TARGET;
    target_it->is_active = false;
    return;
  }
}

void AntBuilder::check_target_distance(){
  if(moving_to_anthill == false){
    int dx = x - target_it->x;
    int dy = y - target_it->y;
    double distance = sqrt(dx * dx + dy * dy);
    if (distance >= 5 and distance <= 10){
      has_material = true;
      (*material_p).erase(target_it);
      moving_to_anthill = true;
    }
  }else{
    int dx = x - 400;
    int dy = y - 400;
    double distance = sqrt(dx * dx + dy * dy);
    if (distance >= 5 and distance <= 10){
      has_material = false;
      moving_to_anthill = false;
      anthill_p->material_count += 1;
      action = Action::WANDERING;
    }
  }
  
}

void AntBuilder::do_when_wandering(){
  check_material_distance();
  move_in_random_direction();
}

void AntBuilder::do_when_target(){
  check_target_distance();
  if (action == Action::MOVING_TO_TARGET){
    if (moving_to_anthill == false){
      move_to_point(target_it->x, target_it->y);
    }else{
      move_to_point(400, 400);
    }
  }
  
  
}


AntWarrior::AntWarrior(Anthill* anthill_p, std::list<Enemy>* enemy_p) : Ant(anthill_p){
  this->enemy_p = enemy_p;
}

AntWarrior::~AntWarrior(){

}

void AntWarrior::check_enemy_distance(){
  double distance;
  int dx;
  int dy;
  int smallest_distance = 800;
  for (int i=0; i < enemy_p->size(); i++){
    dx = x - (*std::next((*enemy_p).begin(), i)).x;
    dy = y - (*std::next((*enemy_p).begin(), i)).y;
    distance = sqrt(dx * dx + dy * dy);
    if (distance < smallest_distance){
      target_it = std::next((*enemy_p).begin(), i);
      smallest_distance = distance;
    }
    action = Action::MOVING_TO_TARGET;
  }
  
}

void AntWarrior::check_target_distance(){
  if (anthill_p->check_enemy_presense(target_it) == false){
    action = Action::WANDERING;
    return;
  }
  if (target_it->health == 0){
    if (target_it->attacking == true){
      if (target_it->harvester){
        target_it->ant_harvester_target_it->attacked = false;
      }else{
        target_it->ant_builder_target_it->attacked = false;
      }
        
      }
      anthill_p->enemies.erase(target_it);
      return;
    }
  int dx = x - target_it->x;
  int dy = y - target_it->y;
  double distance = sqrt(dx * dx + dy * dy);
  if (distance >= 5 and distance <= 10){
    (*target_it).health--;
    anthill_p->ants_warriors.erase(self_it);
    anthill_p->population--;
  }
}

void AntWarrior::do_when_wandering(){
  check_enemy_distance();
  if(action == Action::WANDERING){
    move_in_random_direction();
  }
}

void AntWarrior::do_when_target(){
  check_target_distance();
  if (action == Action::MOVING_TO_TARGET){
    move_to_point(target_it->x, target_it->y);
  }
}

void AntWarrior::set_self_it(std::list<AntWarrior>::iterator self_it){
  this->self_it = self_it;
}

Food::Food(){

  x = distr(gen);
  y = distr(gen);

  is_active = true;
}

std::mt19937 Food::gen(std::random_device{}());
std::uniform_int_distribution<> Food::distr(0,780);

Food::~Food(){
  
}

Material::Material(){

  x = distr(gen);
  y = distr(gen);

  is_active = true;
}

std::mt19937 Material::gen(std::random_device{}());
std::uniform_int_distribution<> Material::distr(0,780);

Material::~Material(){
  
}

Enemy::Enemy(){
  x = distr(gen);
  y = distr(gen);
  health = 3;
  attacking = false;
  speed = 2;
}

std::mt19937 Enemy::gen(std::random_device{}());
std::uniform_int_distribution<> Enemy::distr(0,780);

Enemy::~Enemy(){

}