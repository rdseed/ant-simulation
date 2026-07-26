#pragma once
#include "options.h"
#include <iostream>
#include <math.h>
#include <list>
#include <random>

enum class Action{WANDERING, MOVING_TO_TARGET};

class Ant;
class AntFoodHarvester;
class Anthill;
class Food;
class Material;
class AntWarrior;
class Enemy;

class Ant{
public:
  Ant(Anthill* anthill_p);
  ~Ant();
  double x;
  double y;
  bool attacked;
  Action action;
  Anthill* anthill_p;
  void update_position();
  void move_in_random_direction();
  void move_to_point(int point_x, int point_y);
  virtual void do_when_wandering();
  virtual void do_when_target();
  static std::uniform_int_distribution<> distr;
  static std::mt19937 gen;
  static int step;
};

class AntFoodHarvester : public Ant{
public:
  AntFoodHarvester(Anthill* anthill_p, std::list<Food>* food_p);
  ~AntFoodHarvester();
  std::list<Food>* food_p;
  std::list<Food>::iterator target_it;
  std::list<AntFoodHarvester>::iterator self_it;
  bool has_food;
  bool moving_to_anthill;
  void check_food_distance();
  void check_target_distance();
  void set_self_it(std::list<AntFoodHarvester>::iterator self_it);
  void do_when_wandering() override;
  void do_when_target() override;
};

class AntBuilder : public Ant{
public:
  AntBuilder(Anthill* anthill_p, std::list<Material>* material_p);
  ~AntBuilder();
  std::list<Material>* material_p;
  std::list<Material>::iterator target_it;
  std::list<AntBuilder>::iterator self_it;
  bool has_material;
  bool moving_to_anthill;
  void check_material_distance();
  void check_target_distance();
  void set_self_it(std::list<AntBuilder>::iterator self_it);
  void do_when_wandering() override;
  void do_when_target() override;
};

class AntWarrior : public Ant{
public:
  AntWarrior(Anthill* anthill_p, std::list<Enemy>* enemy_p);
  ~AntWarrior();
  std::list<Enemy>* enemy_p;
  std::list<Enemy>::iterator target_it;
  std::list<AntWarrior>::iterator self_it;
  void check_enemy_distance();
  void check_target_distance();
  void set_self_it(std::list<AntWarrior>::iterator self_it);
  void do_when_wandering() override;
  void do_when_target() override;
};

class Anthill{
public:
  Anthill();
  ~Anthill();
  Options options;
  std::list<AntFoodHarvester> ants_harvesters;
  std::list<AntBuilder> ants_builders;
  std::list<AntWarrior> ants_warriors;
  std::list<Food> food;
  std::list<Material> materials;
  std::list<Enemy> enemies;
  unsigned int population;
  unsigned int possible_population;
  unsigned int size;
  unsigned int food_count;
  unsigned int material_count;
  unsigned int frame_count_food;
  unsigned int frame_count_materials;
  unsigned int frame_count_enemies;
  void simulate();
  void check_enemies();
  void autospawn_food();
  void autospawn_materials();
  void autospawn_enemies();
  
  bool check_enemy_presense(std::list<Enemy>::iterator iterator);

};

class Food{
public:
  Food();
  ~Food();
  int x;
  int y;
  bool is_active;
  static std::uniform_int_distribution<> distr;
  static std::mt19937 gen;
};

class Material{
public:
  Material();
  ~Material();
  int x;
  int y;
  bool is_active;
  static std::uniform_int_distribution<> distr;
  static std::mt19937 gen;
};

class Enemy{
public:
  Enemy();
  ~Enemy();
  int x;
  int y;
  unsigned int health;
  unsigned int speed;
  static std::uniform_int_distribution<> distr;
  static std::mt19937 gen;
  std::list<AntFoodHarvester>::iterator ant_harvester_target_it;
  std::list<AntBuilder>::iterator ant_builder_target_it;
  bool attacking;
  bool harvester;
};