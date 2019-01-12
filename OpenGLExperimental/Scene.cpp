#include "Scene.h"
#include <stb_image.h>
void Scene::Init(int argc, char ** argv)
{
	glutInit(&argc,argv);
	
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

}

int Scene::SetupWindow(unsigned int mode, vec2 windowPosition, vec2 windowSize, const char * name)
{
	Window window;
	window.Init(mode, windowPosition, windowSize);
	int a=window.Show(name);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	glEnable(GL_CULL_FACE); //enable culling. make it faster.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
	glEnable(GL_LIGHTING); //turns on lighting
	glEnable(GL_NORMALIZE); //enable automatic normalization
	glCullFace(GL_BACK);//remove the back of objects



	return a;
}

void Scene::SetupConsole(GLUI* glui_v_subwindow,int main_window)
{
	glui_v_subwindow = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_LEFT);
	new GLUI_StaticText(glui_v_subwindow, "OpenGL Experimental\n");
	new GLUI_Separator(glui_v_subwindow);

	GLUI_Panel* glui_v_panel_main = new GLUI_Panel(glui_v_subwindow, "Variables", GLUI_PANEL_EMBOSSED);

	GLUI_Panel* glui_v_panel_ROT = new GLUI_Panel(glui_v_panel_main, "Rotation", GLUI_PANEL_EMBOSSED);

	GLUI_Panel* glui_v_panel_SCALE = new GLUI_Panel(glui_v_panel_main, "Scale", GLUI_PANEL_EMBOSSED);


	GLUI_Panel* glui_v_panel_SPIRAL = new GLUI_Panel(glui_v_panel_main, "Spiral", GLUI_PANEL_EMBOSSED);

	new GLUI_StaticText(glui_v_subwindow, "Press ESC to exit\n");

	glui_v_subwindow->set_main_gfx_window(main_window);
	GLUI_Master.sync_live_all(); 
}

Light Scene::CreateMainLight(vec3 color, vec3 ambient, GLfloat intensity, GLfloat ambientIntensity)
{
	return Light(color, ambient, intensity, ambientIntensity);
}
GLuint Scene:: loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
