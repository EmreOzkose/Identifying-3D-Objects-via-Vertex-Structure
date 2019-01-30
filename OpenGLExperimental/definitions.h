using namespace std;
#include <string>
#include "GameObject.h"
#include "Material.h"
#include "Shader.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_NAME "OpenGL Identfying 3D Objects"
#define PLANES_BEGIN_SIZE 20
#define OBJECTS_BEGIN_SIZE 2
#define MAX_LIGHTS_SIZE 4
#define CONSOLE_WIDTH 325
#define PI 3.14159265359



Shader shader_flat = Shader();
Shader shader_blinnphong = Shader();
Shader shader_bphongsimp = Shader();
Shader shader_water = Shader();
Shader shader_toon = Shader();
Shader shader_particle = Shader();
Shader shader_skybox = Shader();
Shader shader_smoothtoon = Shader();




string albedo_01 = "Textures/Albedo_01.jpg";
string normal_01 = "Textures/Albedo_01_NRM.jpg";
string albedo_03 = "Textures/Albedo_03.jpg";
string normal_03 = "Textures/Albedo_03_NRM.jpg";
string albedo_04 = "Textures/Albedo_04.jpg";
string normal_04 = "Textures/Albedo_04_NRM.jpg";
string albedo_05 = "Textures/Albedo_05.jpg";
string normal_05 = "Textures/Albedo_05_NRM.jpg";
string albedo_06 = "Textures/Albedo_06.jpg";
string normal_06 = "Textures/Albedo_06_NRM.jpg";
string albedo_12 = "Textures/Albedo_12.jpg";
string normal_12 = "Textures/Albedo_12_NRM.jpg";
string albedo_13 = "Textures/Albedo_13.jpg";
string normal_13 = "Textures/Albedo_13_NRM.jpg";
string albedo_15 = "Textures/Albedo_15.jpg";
string normal_15 = "Textures/Albedo_15_NRM.jpg";
string albedo_16 = "Textures/Albedo_16.jpg";
string normal_16 = "Textures/Albedo_16_NRM.jpg";
string albedo_17 = "Textures/Albedo_17.jpg";
string normal_17 = "Textures/Albedo_17_NRM.jpg";




GameObject texturehelper;
struct GameObject::Texture texture_01 = texturehelper.CreateTexture(albedo_01, normal_01);
struct GameObject::Texture texture_03 = texturehelper.CreateTexture(albedo_03, normal_03);
struct GameObject::Texture texture_04 = texturehelper.CreateTexture(albedo_04, normal_04);
struct GameObject::Texture texture_05 = texturehelper.CreateTexture(albedo_05, normal_05);
struct GameObject::Texture texture_06 = texturehelper.CreateTexture(albedo_06, normal_06);
struct GameObject::Texture texture_12 = texturehelper.CreateTexture(albedo_12, normal_12);
struct GameObject::Texture texture_13 = texturehelper.CreateTexture(albedo_13, normal_13);
struct GameObject::Texture texture_15 = texturehelper.CreateTexture(albedo_15, normal_15);
struct GameObject::Texture texture_16 = texturehelper.CreateTexture(albedo_16, normal_16);
struct GameObject::Texture texture_17 = texturehelper.CreateTexture(albedo_17, normal_17);

vector<struct GameObject::Texture> txtreList{ texture_01,texture_03,texture_04,
	texture_05,texture_06,texture_12,texture_13,texture_15,texture_16,texture_17
};

string Sphere_texture = "Textures/Sphere_texture.jpg";
string Sphere_texture_nrm = "Textures/Sphere_texture.jpg";
struct GameObject::Texture sphere_tex = texturehelper.CreateTexture(Sphere_texture, Sphere_texture_nrm);


Material material_red = Material(vec3(1, 0, 0), vec3(1, 1, 1), 32);
Material material_green = Material(vec3(0, 1, 0), vec3(1, 1, 1), 32);
Material material_black = Material(vec3(0, 0, 0), vec3(1, 1, 1), 32);
Material material_white = Material(vec3(1, 1, 1), vec3(1, 1, 1), 32);
Material material_blue = Material(vec3(0, 0, 1), vec3(1, 1, 1), 32);
Material material_yellow = Material(vec3(1, 1, 0), vec3(1, 1, 1), 32);
Material material_magenta = Material(vec3(1, 0, 1), vec3(1, 1, 1), 32);
Material material_cyan = Material(vec3(0, 1, 1), vec3(1, 1, 1), 32);

//metals
Material material_iron = Material(vec3(.560f, .570f, .580f), vec3(1, 1, 1), 128);
Material material_silver = Material(vec3(.972f, .960f, .915f), vec3(1, 1, 1), 128);
Material material_aliminum = Material(vec3(.913, .921f, .925f), vec3(1, 1, 1), 128);
Material material_gold = Material(vec3(1.0f, .766f, .336f), vec3(1, 1, 1), 128);
Material material_copper = Material(vec3(.955f, .637f, .538f), vec3(1, 1, 1), 128);
Material material_titanium = Material(vec3(.542f, .497f, .449f), vec3(1, 1, 1), 128);

//misc
Material material_mulberry = Material(vec3(.549f, 0.0f, .294f), vec3(1, 1, 1), 128);
Material material_skyblue = Material(vec3(.588f, .784f, .980f), vec3(1, 1, 1), 128);
Material material_bloodred = Material(vec3(.745f, 0.0f, 0.0f), vec3(1, 1, 1), 128);



vector<Material> selectedObj_colors_vec = { material_aliminum,material_gold,material_copper,material_iron,
material_silver ,material_titanium ,material_mulberry,material_skyblue,material_bloodred };

string humanoids_path = "Models/Humanoids";

string path_human = humanoids_path + "/Human.obj";
string path_cyborg = humanoids_path + "/Cyborg.obj";
string path_skeleton = humanoids_path + "/Skeleton.obj";
string path_vampire = humanoids_path + "/Vampire.obj";
string path_goblin = humanoids_path + "/Goblin.obj";

vector<string> humanoids_paths_all = { path_goblin ,path_skeleton,path_vampire,path_cyborg ,path_human };

//class 2_quadripedals
string quadripedals_path = "Models/Quadripedals";

string path_deer = quadripedals_path + "/Deer.obj";
string path_bear = quadripedals_path + "/Bear.obj";
string path_dog = quadripedals_path + "/Dog.obj";
string path_wolf = quadripedals_path + "/Wolf.obj";
string path_elephant = quadripedals_path + "/Elephant.obj";

vector<string> quadripedal_paths_all = { path_deer ,path_bear,path_dog,path_wolf ,path_elephant };


//class 3_vehicles
string vehicles_path = "Models/Vehicles";

string path_veha = vehicles_path + "/MonsterVehicle.obj";
string path_van = vehicles_path + "/Van.obj";
string path_car = vehicles_path + "/Car.obj";
string path_lpcar = vehicles_path + "/LowPcar.obj";
string path_futcar = vehicles_path + "/FuturisticCar.obj";


vector<string> vehicles_paths_all = { path_veha ,path_van,path_car,path_lpcar,path_futcar };




//class 4_trees
string trees_path = "Models/Trees";

string path_tree0 = trees_path + "/Tree_1.obj";
string path_tree1 = trees_path + "/Tree_2.obj";
string path_tree2 = trees_path + "/Tree_3.obj";
string path_tree3 = trees_path + "/Tree_4.obj";
string path_tree4 = trees_path + "/Tree_5.obj";

vector<string> trees_paths_all = { path_tree0 ,path_tree1,path_tree2,path_tree3,path_tree4 };


vector<string> all_models = { path_tree0 ,path_tree1,path_tree2,path_tree3,path_tree4 , path_veha ,path_van,path_car,path_lpcar,path_futcar
,path_deer ,path_bear,path_dog,path_wolf ,path_elephant, path_goblin ,path_skeleton,path_vampire,path_cyborg ,path_human
};


string path_ground = "Models/Ground.obj";
string path_sea = "Models/Plane.obj";
string path_cube = "Models/Cube.obj";
string path_sphere = "Models/SphereA.obj";
string path_ico = "Models/SphereB.obj";
string path_planel = "Models/PlaneLow.obj";


vector<string> some_models = { path_planel ,path_sphere ,path_cube };