//naquele tutorial, tem como fazer triângulos e cubos.
//no seu calculo original PHONG, deve ter algo errado nos vetores, 
//pois deveria gerar uma imagem parecida àquela da wikipedia.
using namespace std;
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Light.h"
#include "Polygon.h"

int contador = 0;
Vec3 miss(-1000, -1000, -1000);
int hit_object_index = 0;
int reflect_object_index = 0;
int reflection_limit = 0;

struct RGBType {
	double r,g,b;	
};

void savebmp(const char *filename, int w, int h,
 int dpi, RGBType *data) {

	FILE *f;
	int k =w*h;
	int s = 4*k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0,
	0,0,0,0,	54,0,0,0	};
	unsigned char bmpinfoheader[40] = {40,0,0,0,	0,0,0,0,
	0,0,0,0,	1,0,24,0	};

	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>>8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w>>8);
	bmpinfoheader[ 6] = (unsigned char)(w>>16);
	bmpinfoheader[ 7] = (unsigned char)(w>>24);

	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);

	f = fopen(filename,"wb");

	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);

	for(int i = 0; i < k ; i++)	{
		RGBType rgb = data[i];

		double red = (data[i].r)*255;
		double green = (data[i].g)*255;
		double blue = (data[i].b)*255;

		unsigned char color[3] = {(int)floor(blue),
			(int)floor(green),(int)floor(red)};

			fwrite(color,1,3,f);
	}

	fclose(f);

}

int indexOfFirstObject(vector<float> intersections_dist,
 vector<int> obj_index){
	if(intersections_dist.size() == 0){
		return -1;
	}
	else if(intersections_dist.size() == 1){
		return	obj_index.at(0);
	}
	else{
		float min = intersections_dist.at(0);
		
		int index = 0;
		for(int i = 1; i < intersections_dist.size(); i++){
			if(min >= intersections_dist.at(i)){
				min = intersections_dist.at(i);
				index = i;
			}
		}
		return obj_index.at(index);	
	}
}

float distanceOfFirstObject(vector<float> intersections_dist){
	if(intersections_dist.size() == 1){
		return intersections_dist.at(0);
	}
	else{
		float min = intersections_dist.at(0);
		for(int i = 1; i < intersections_dist.size(); i++){
			if(min >= intersections_dist.at(i)){
				min = intersections_dist.at(i);
			}
		}
		return min;
	}
}

Color getColorAt(Vec3 position, int obj_index, vector<Light*> lights, 
vector<Object*> objects, Color ambient_light, Vec3 cam_position){
	
	float ka = objects.at(obj_index)->getKa();
	float kd = objects.at(obj_index)->getKd();
	float ks = objects.at(obj_index)->getKs();
	float alfa = objects.at(obj_index)->getAlfa();
	Color c = objects.at(obj_index)->getColor(); 
	Color ia = ambient_light;
		
	Vec3 p = position;
	Vec3 n = objects.at(obj_index)->getNormalAt(p);
	Vec3 v = (cam_position - p).normalized();
	
	// Vec3 intersection_position = p + d*t;
	
	// phong lighting
	Color final_color = c*(ia*ka);

	for(int i = 0; i < lights.size(); i++){
		
		Vec3 pl = lights.at(i)->getLightPosition();
		Vec3 l = (pl - p).normalized();
		Color id = lights.at(i)->getLightId();
		Color is = lights.at(i)->getLightIs();
		Vec3 r = (n*2*(l.dotProduct(n)) - l).normalized();

		// p = p + n*0.5;

		bool shadowed = false;
		Ray light_ray(p, l);
		vector<float> intersec_dist;
		for(int j = 0; j < objects.size() ; j++){
			float t = objects.at(j)->intersectionDistance(light_ray);
			if(t > 0){
				intersec_dist.push_back(t);
			}
		}
		if(intersec_dist.size() > 0){
			float distance_of_first_object = 
			distanceOfFirstObject(intersec_dist);

			Vec3 light_position = lights.at(i)->getLightPosition();
			float distance_from_light = (light_position - p).magnitude();

			if(distance_from_light > distance_of_first_object){
				shadowed = true;
			}				
		}

		if(!shadowed){
			if(l.dotProduct(n) > 0){
				// lembrando, u*v = ||u||*||v||*cos(a) e
				//  -1 <= cos(a) <= 1
				final_color += c*(id*kd*(l.dotProduct(n))) ;
			}
			if(r.dotProduct(v) > 0){
				final_color	+= is*ks*pow(r.dotProduct(v), alfa);
				// se multiplicar pela cor, nao vai ficar igual
				// a definicao la da wikipedia
			}
		}	
	}
	return final_color.clip();
}

Vec3 getReflectionIntersectionPosition(Ray ray, vector<Object*> objects){
	
	Vec3 p = ray.getRayOrigin();
	Vec3 d = ray.getRayDirection();

	vector<float> intersections_dist;
	vector<int> obj_index;
	for( int index = 0; index < objects.size(); index++){
		/*para esse pixel específico, achar todos os objetos
		ao qual esse raio intercepta*/
		float t = objects.at(index)->intersectionDistance(ray); 
		if(t > 0){
			intersections_dist.push_back(t);
			obj_index.push_back(index);
		}
	}

	int index_of_first_object = 
	indexOfFirstObject(intersections_dist, obj_index);
	// Object hit_object = *objects.at(index_of_first_object);

	// cout << index_of_first_object;
	if(index_of_first_object == -1){
		return miss;
	}
	else{
		reflect_object_index = index_of_first_object;

		float t = objects.at(index_of_first_object)->intersectionDistance(ray);

		Vec3 intersection_position = p + d*t;
		
		if(objects.at(index_of_first_object)->getKrflx() == 0.0 ||
		   reflection_limit > 50 ){
			reflection_limit = 0;
			return intersection_position;
		}

		reflection_limit++;


		Vec3 p_rflx = intersection_position;
		Vec3 l = p - p_rflx;
		Vec3 n = objects.at(index_of_first_object)->getNormalAt(p_rflx);
		Vec3 d_rflx = n*l.dotProduct(n)*2 - l;
		
		Ray rflx_ray = Ray(p_rflx, d_rflx);

		return getReflectionIntersectionPosition(rflx_ray, objects);
	}
}

Vec3 getFirstIntersectionPosition(Ray ray, vector<Object *> objects){
	
	Vec3 p = ray.getRayOrigin();
	Vec3 d = ray.getRayDirection();

	vector<float> intersections_dist;
	vector<int> obj_index;
	for( int index = 0; index < objects.size(); index++){
		/*para esse pixel específico, achar todos os objetos
		ao qual esse raio intercepta*/
		float t = objects.at(index)->intersectionDistance(ray); 
		if(t > 0){
			intersections_dist.push_back(t);
			obj_index.push_back(index);
		}
	}

	int index_of_first_object = 
	indexOfFirstObject(intersections_dist, obj_index);

	// cout << index_of_first_object;
	if(index_of_first_object == -1){
		return miss;
	}
	else{
		hit_object_index = index_of_first_object;
		float t = objects.at(index_of_first_object)->intersectionDistance(ray);
		Vec3 intersection_position = p + d*t;
		return intersection_position;
	}
}




Color white(1, 1, 1);
Color light_green(0.5, 1, 0.5);
Color light_blue(0.5, 0.5, 1);
Color light_yellow(1.0, 1.0, 0.5);
Color pink(0.92, 0.42, 0.65);
Color light_purple(0.93, 0.78, 0.93);
Color black(0, 0, 0);
Color almost_black(0.1, 0.1, 0.1);
Color brown(0.5, 0.25, 0.25);
Color red(1, 0, 0);
Color green(0, 1, 0);
Color blue(0, 0, 1);
Color purple(0.8, 0, 0.8);
Color yellow(1, 1, 0);
Color orange(0.94, 0.745, 0.31);
Color ambient_light(1, 1, 1);


/**/
/*    __		  __             __         _    __       _          
     /  \        /  \           /  \       | |  |   \    | |         ||
    / /\ \      / /\ \         / /\ \      | |  | |\ \   | |	     ||
   / /  \ \    / /  \ \       / /__\ \     | |  | | \ \  | |		 ||
  / /    \ \  / /    \ \     / ______ \    | |  | |  \ \ | |      \\ || //
 / /      \ \/ /      \ \   / /      \ \   | |  | |   \ \| |       \\||//
/_/        \__/        \_\ /_/        \_\  |_|  |_|    \___|        \  /
                                                                     \/
*/

main(){
    clock_t t1, t2;
    t1 = clock();

    cout << "\nrendering..." ;
// camera //(0, 2.5, -8)
    Camera scene_cam(Vec3(0, 2.5, -8), Vec3(0, 0, 0), 30, 1.5);
    ambient_light *= 0.1;
    int pw = 720, ph = pw/ 1.5;
    int dpi = 72;
	int n = pw*ph;
	float aspect_ratio = pw/ ph;
	RGBType *pixels = new RGBType[n];

    int num_lights = 3;
    Light light_a(Vec3(0, 6, -2), white/ num_lights); 
    Light light_b(Vec3(3, 3, -4), white/ num_lights); 
    Light light_c(Vec3(6, 6, -2), white/ num_lights);

    Vec3 a = light_a.getLightPosition();
    Vec3 b = light_b.getLightPosition();
    Vec3 c = light_c.getLightPosition();

	// objetos
	Plane blue_plane(Vec3(1, 0, 0), -4, light_blue);
	Plane blue_plane_2(Vec3(-1, 0, 0), -10, pink);
	Plane green_plane(Vec3(0, 1, 0), 0, light_green);
	Plane yellow_plane(Vec3(0, 0, -1), -6, light_yellow);
	Plane yellow_plane_2(Vec3(0, 0, 1), -10, white*0.7, 1, 1, 0, 1, 0.0);
	
	int bx = -1;
	int by = 0;
	int bz = -3;

	int px = 0;
	int py = 0;
	int pz = 0;

	Sphere pink_sphere(Vec3(0, 2, 0) , 2, pink, 1, 1, 0.5, 10, 0.2); 
	Sphere yellow_sphere(Vec3(-2, 0.75, -3) , 0.75, light_yellow, 1, 1, 0.5, 10, 0.0);
	Sphere red_sphere(Vec3(0, 0.3, -4), 0.3, red, 1, 1, 0.5, 10, 0.0);
	
	Sphere blue_sphere(Vec3(3 + bx, 0.5 + by, 0 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_2(Vec3(4 + bx, 0.5 + by, 0 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_3(Vec3(5 + bx, 0.5 + by, 0 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_4(Vec3(3 + bx, 0.5 + by, -1 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_5(Vec3(4 + bx, 0.5 + by, -1 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_6(Vec3(5 + bx, 0.5 + by, -1 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_7(Vec3(3 + bx, 0.5 + by, 1 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_8(Vec3(4 + bx, 0.5 + by, 1 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_9(Vec3(5 + bx, 0.5 + by, 1 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_10(Vec3(4 + bx, 1.5 + by, 0 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_11(Vec3(4 + bx, 2.5 + by, 0 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	Sphere blue_sphere_12(Vec3(4 + bx, 3.5 + by, 0 + bz) , 0.5, light_blue, 1, 1, 0.5, 10, 0.0);
	
	// vetor de objetos e luzes
	vector<Object*> objects;
	vector<Light*> lights;
	// quando eu tento armazenar objetos em vetores,fica tudo preto,
	// melhor deixar como apontadores mesmo

	lights.push_back(dynamic_cast<Light*>(&light_a));
	lights.push_back(dynamic_cast<Light*>(&light_b));
	lights.push_back(dynamic_cast<Light*>(&light_c));
	
	objects.push_back(dynamic_cast<Object*>(&green_plane));
	objects.push_back(dynamic_cast<Object*>(&blue_plane));
	objects.push_back(dynamic_cast<Object*>(&yellow_plane));
	objects.push_back(dynamic_cast<Object*>(&yellow_plane_2));
	objects.push_back(dynamic_cast<Object*>(&blue_plane_2));

	objects.push_back(dynamic_cast<Object*>(&pink_sphere));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere));
	objects.push_back(dynamic_cast<Object*>(&yellow_sphere));
	objects.push_back(dynamic_cast<Object*>(&red_sphere));

	objects.push_back(dynamic_cast<Object*>(&blue_sphere_2));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_3));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_4));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_5));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_6));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_7));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_8));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_9));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_10));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_11));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_12));

	float x, y;	
	int pixel_index;

	Vec3 p = scene_cam.getCameraPosition();
	Vec3 f = scene_cam.getCameraForward();
	float h = scene_cam.getCameraH();
	float w = scene_cam.getCameraW();
	Vec3 u = scene_cam.getCameraUp();
	Vec3 r = scene_cam.getCameraRight();
 


for(int py = 0 ; py < ph; py++){
	/*para cada pixel criaremos um raio que parte da camera*/
	for(int px = 0; px < pw; px++){
		pixel_index = ((ph-1)-py)*pw + px; 

		x = ((float)2*px/ (float)pw) - 1;
		y = ((float)2*py / (float)ph) - 1;
		Vec3 d = f + r*w*x + u*h*y;
		Ray cam_ray(p, d);


		Vec3 first_intersection_position = getFirstIntersectionPosition(cam_ray, objects);

		Color first_intersection_color = 
		getColorAt(first_intersection_position, hit_object_index, 
		lights, objects, ambient_light, p);

		Vec3 reflection_intersection_position = getReflectionIntersectionPosition(cam_ray, objects);
		
		Color reflection_intersection_color = 
		getColorAt(reflection_intersection_position, reflect_object_index, 
		lights, objects, ambient_light, p);

		float krflx = objects.at(hit_object_index)->getKrflx();

					
		Color intersection_color = 
		first_intersection_color*(1-krflx) + 
		reflection_intersection_color*krflx ;

		if(first_intersection_position == miss
		|| reflection_intersection_position == miss){
			pixels[pixel_index].r = 0;
			pixels[pixel_index].g = 0;
			pixels[pixel_index].b = 0;
		}

		pixels[pixel_index].r = intersection_color.getColorRed();
		pixels[pixel_index].g = intersection_color.getColorGreen();
		pixels[pixel_index].b = intersection_color.getColorBlue();	  	
	} 	
}

	savebmp("scene.bmp", pw, ph, dpi, pixels);
//

	t2 = clock();
	cout << "\nrendering time: " 
	<< (((float)t2 - (float)t1)/ 1000) << " segundos" << endl;
}