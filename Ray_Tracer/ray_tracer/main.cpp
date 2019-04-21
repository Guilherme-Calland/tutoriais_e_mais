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
		float min  = intersections_dist.at(0);
		
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
vector<Object*> objects, Color ambient_light,Vec3 cam_position){
	
	float ka = objects.at(obj_index)->getKa();
	float kd = objects.at(obj_index)->getKd();
	float ks = objects.at(obj_index)->getKs();
	float alfa = objects.at(obj_index)->getAlfa();
	Color c = objects.at(obj_index)->getColor(); 
	Color ia = ambient_light;
	// phong lighting
	Color final_color = c*(ia*ka);

	for(int i = 0; i < lights.size(); i++){
		
		Vec3 pl = lights.at(i)->getLightPosition();
		Vec3 p = position;
		Vec3 l = (pl - p).normalized();
		Vec3 n = objects.at(obj_index)->getNormalAt(p);
		Color id = lights.at(i)->getLightId();
		Color is = lights.at(i)->getLightIs();
		Vec3 r = (n*2*(l.dotProduct(n)) - l).normalized();
		Vec3 v = (cam_position - p).normalized();

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
    int pw = 360, ph = pw/ 1.5;
	bool anti_aliasing = false;
	int aadepth = 2;// se aadepth = 2, media de 4 cores //
	//se botar aadepth = 1 , na equação x/aadepth - 1 -> x/0 irreal

    int dpi = 72;
	int n = pw*ph;
	float aspect_ratio = pw/ ph;
	RGBType *pixels = new RGBType[n];

    int num_lights = 3;
    Light light_a(Vec3(0, 4, -2), white/ num_lights); 
    Light light_b(Vec3(3, 1, -4), white/ num_lights); 
    Light light_c(Vec3(6, 4, -2), white/ num_lights);

    Vec3 a = light_a.getLightPosition();
    Vec3 b = light_b.getLightPosition();
    Vec3 c = light_c.getLightPosition();

//    a = a*0.05 + b*0.95;
//    c = c*0.05 + b*0.95;

//    light_a = Light(a,  white/ num_lights);
//    light_c = Light(c,  white/ num_lights);

    Light light_btw_a_b_1(a*0.8 + b*0.2, white/ num_lights); 
    Light light_btw_a_b_2(a*0.6 + b*0.4, white/ num_lights); 
    Light light_btw_a_b_3(a*0.4 + b*0.6, white/ num_lights);
    Light light_btw_a_b_4(a*0.2 + b*0.8, white/ num_lights);

	Light light_btw_a_c_1(a*0.8 + c*0.2, white/ num_lights); 
    Light light_btw_a_c_2(a*0.6 + c*0.4, white/ num_lights); 
    Light light_btw_a_c_3(a*0.4 + c*0.6, white/ num_lights);
    Light light_btw_a_c_4(a*0.2 + c*0.8, white/ num_lights);

    Light light_btw_c_b_1(c*0.8 + b*0.2, white/ num_lights); 
    Light light_btw_c_b_2(c*0.6 + b*0.4, white/ num_lights); 
    Light light_btw_c_b_3(c*0.4 + b*0.6, white/ num_lights);
    Light light_btw_c_b_4(c*0.2 + b*0.8, white/ num_lights);


	// objetos
	Plane blue_plane(Vec3(1, 0, 0), -4, light_blue);
	Plane green_plane(Vec3(0, 1, 0), 0, light_green); 
	Plane yellow_plane(Vec3(0, 0, -1), -6, light_yellow);

	Sphere random_object(Vec3(0, -50, 0), 0.1, white);

	Sphere pink_sphere(Vec3(0, 1, 0) , 1, pink, 1, 1, 0.5, 10); 
	Sphere blue_sphere(Vec3(3, 0.5, 0) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere yellow_sphere(Vec3(-2, 0.75, -3) , 0.75, light_yellow, 1, 1, 0.5, 10);
	
	Sphere blue_sphere_2(Vec3(4, 0.5, 0) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_3(Vec3(5, 0.5, 0) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_4(Vec3(3, 0.5, -1) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_5(Vec3(4, 0.5, -1) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_6(Vec3(5, 0.5, -1) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_7(Vec3(3, 0.5, 1) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_8(Vec3(4, 0.5, 1) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_9(Vec3(5, 0.5, 1) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_10(Vec3(4, 1.5, 0) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_11(Vec3(4, 2.5, 0) , 0.5, light_blue, 1, 1, 0.5, 10);
	Sphere blue_sphere_12(Vec3(4, 3.5, 0) , 0.5, light_blue, 1, 1, 0.5, 10);

	Vec3 A(1, 0.7, -4.5);
	Vec3 B(0.6, 0, -4.5);
	Vec3 C(1.5, 0, -5.5);
	Vec3 D(3, 0, -2.5);

	Polygon polygon(A, B, C, white);
	Polygon polygon_2(A, C, D, white);
	Polygon polygon_3(A, D, B, white);

	
	
	// vetor de objetos e luzes
	vector<Object*> objects;
	vector<Light*> lights;
	// quando eu tento armazenar objetos em vetores,fica tudo preto,
	// melhor deixar como apontadores mesmo

	lights.push_back(dynamic_cast<Light*>(&light_a));
	lights.push_back(dynamic_cast<Light*>(&light_b));
	lights.push_back(dynamic_cast<Light*>(&light_c));

	// lights.push_back(dynamic_cast<Light*>(&light_btw_a_b_1));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_a_b_2));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_a_b_3));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_a_b_4));

	// lights.push_back(dynamic_cast<Light*>(&light_btw_a_c_1));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_a_c_2));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_a_c_3));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_a_c_4));

	// lights.push_back(dynamic_cast<Light*>(&light_btw_c_b_1));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_c_b_2));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_c_b_3));
	// lights.push_back(dynamic_cast<Light*>(&light_btw_c_b_4));
	
	objects.push_back(dynamic_cast<Object*>(&green_plane));
	objects.push_back(dynamic_cast<Object*>(&blue_plane));
	objects.push_back(dynamic_cast<Object*>(&yellow_plane));
	
	objects.push_back(dynamic_cast<Object*>(&pink_sphere));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere));
	objects.push_back(dynamic_cast<Object*>(&yellow_sphere));

	objects.push_back(dynamic_cast<Object*>(&blue_sphere_2));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_3));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_4));
	objects.push_back(dynamic_cast<Object*>(&random_object));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_5));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_6));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_7));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_8));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_9));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_10));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_11));
	objects.push_back(dynamic_cast<Object*>(&blue_sphere_12));

	objects.push_back(dynamic_cast<Object*>(&polygon));
	objects.push_back(dynamic_cast<Object*>(&polygon_2));
	objects.push_back(dynamic_cast<Object*>(&polygon_3));

	
	float x, y;	
	int pixel_index;

	Vec3 p = scene_cam.getCameraPosition();
	Vec3 f = scene_cam.getCameraForward();
	float h = scene_cam.getCameraH();
	float w = scene_cam.getCameraW();
	Vec3 u = scene_cam.getCameraUp();
	Vec3 r = scene_cam.getCameraRight();
 

// SEM ANTI-ALIASING
	if(!anti_aliasing){
		for(int py = 0 ; py < ph; py++){
			/*para cada pixel criaremos um raio que parte da camera*/
			for(int px = 0; px < pw; px++){
				pixel_index = ((ph-1)-py)*pw + px; 

				x = ((float)2*px/ (float)pw) - 1;
				y = ((float)2*py / (float)ph) - 1;
				Vec3 d = f + r*w*x + u*h*y;
				Ray cam_ray(p, d);

				vector<float> intersections_dist;
				vector<int> obj_index;
				for( int index = 0; index < objects.size(); index++){
					/*para esse pixel específico, achar todos os objetos
					ao qual esse raio intercepta*/
					float t = objects.at(index)->intersectionDistance(cam_ray); 
					if(t > 0){
						intersections_dist.push_back(t);
						obj_index.push_back(index);
					}
				}

				int index_of_first_object = 
				indexOfFirstObject(intersections_dist,obj_index);
				// cout << index_of_first_object;
				if(index_of_first_object == -1){
					pixels[pixel_index].r = 0;
					pixels[pixel_index].g = 0;
					pixels[pixel_index].b = 0;
				}
				else{
					float t = objects.at(index_of_first_object)
					->intersectionDistance(cam_ray);

					Vec3 intersection_position = p + d*t;
									
					Color intersection_color = 
					getColorAt(intersection_position, index_of_first_object, 
					lights, objects,ambient_light, p);

					pixels[pixel_index].r = intersection_color.getColorRed();
					pixels[pixel_index].g = intersection_color.getColorGreen();
					pixels[pixel_index].b = intersection_color.getColorBlue();
				}  	
			} 	
		}
	}
// COM ANTI-ALIASING
	else{
		int aa_index;
		float tempRed[aadepth*aadepth];
		float tempGreen[aadepth*aadepth];
		float tempBlue[aadepth*aadepth];

		for(int py = 0 ; py < ph; py++){
			for(int px = 0; px < pw; px++){
				pixel_index = ((ph-1)-py)*pw + px; 
				for(int aax = 0; aax < aadepth; aax++){
					for(int aay = 0; aay < aadepth; aay++){
						
						aa_index = aay*aadepth + aax;
						
						x = ((float)2*(px + (aax/ (aadepth - 1)) - 0.5)
						/ (float)pw ) - 1;
						y = ((float)2*(py + (aay/ (aadepth - 1)) - 0.5)
						/ (float)ph ) - 1;
						
						Vec3 d = f + r*w*x + u*h*y;
					
						Ray cam_ray(p, d);

						vector<float> intersections_dist;
						vector<int> obj_index;
						for( int index = 0; index < objects.size(); index++){
							/*para esse pixel específico, achar todos os objetos
							ao qual esse raio intercepta*/
							float t = objects.at(index)->intersectionDistance(cam_ray); 
							if(t > 0){
								intersections_dist.push_back(t);
								obj_index.push_back(index);
							}
						}

						int index_of_first_object = 
						indexOfFirstObject(intersections_dist,obj_index);
						// cout << index_of_first_object;

						if(index_of_first_object == 9){
							tempRed[aa_index] = 0;
							tempGreen[aa_index] = 0;
							tempBlue[aa_index] = 0;
						}
						else{
							float t = objects.at(index_of_first_object)
							->intersectionDistance(cam_ray);
							
							Vec3 intersection_position = p + d*t;
							
							Color intersection_color = 
							getColorAt(intersection_position, index_of_first_object, 
							lights, objects,ambient_light, p);

							tempRed[aa_index] = intersection_color.getColorRed();
							tempGreen[aa_index] = intersection_color.getColorGreen();
							tempBlue[aa_index] = intersection_color.getColorBlue();
						}	
					} 	
				}
						float totalRed = 0;
						float totalGreen = 0;
						float totalBlue = 0;
						for(int iRed = 0; iRed < aadepth*aadepth; iRed++){
							totalRed = totalRed + tempRed[iRed];
						}
						for(int iGreen = 0; iGreen < aadepth*aadepth; iGreen++){
							totalGreen = totalGreen + tempGreen[iGreen];	
						}
						for(int iBlue = 0; iBlue < aadepth*aadepth; iBlue++){
							totalBlue = totalBlue + tempBlue[iBlue];	
						}
						float avgRed = totalRed/ (aadepth*aadepth);
						float avgGreen = totalGreen/ (aadepth*aadepth);
						float avgBlue = totalBlue/ (aadepth*aadepth);
						pixels[pixel_index].r = avgRed;
						pixels[pixel_index].g = avgGreen;
						pixels[pixel_index].b = avgBlue;

			}
		}
	}
	savebmp("scene.bmp", pw, ph, dpi, pixels);
//

	t2 = clock();
	cout << "\nrendering time: " 
	<< (((float)t2 - (float)t1)/ 1000) << " segundos" << endl;
}