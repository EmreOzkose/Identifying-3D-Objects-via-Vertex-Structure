#include "Scene.h"

void Scene::Init(int argc, char ** argv)
{
	glutInit(&argc,argv);
	glEnable(GL_CULL_FACE); //enable culling. make it faster.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_ALWAYS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
	glEnable(GL_LIGHTING); //turns on lighting
	glEnable(GL_NORMALIZE); //enable automatic normalization
	glClearDepth(1.0); //specify depth for clear buffer. [0,1]
	glDepthFunc(GL_LEQUAL); //remove anything equal or farther away
	glCullFace(GL_BACK);//remove the back of objects

}

int Scene::SetupWindow(unsigned int mode, vec2 windowPosition, vec2 windowSize, const char * name)
{
	Window window;
	window.Init(mode, windowPosition, windowSize);
	int a=window.Show(name);
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
