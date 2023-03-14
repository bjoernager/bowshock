#define bow_sym "initgfx"

#include <bow/gfx.h>

#include <GLFW/glfw3.h>

typeof (bow_gfxdat) bow_gfxdat;

void bow_initgfx(void) {
	bow_log("initialising graphics");
	if (!glfwInit()) {
		bow_log("unable to initialise glfw");
		bow_quit(bow_stat_err);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,0x3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0x0);
	GLFWwindow * win = glfwCreateWindow(0x300,0x200,"Bowshock",nullptr,nullptr);
	if (win == nullptr) {
		bow_log("unable to open window");
		bow_quit(bow_stat_err);
	}
	glfwMakeContextCurrent(win);
	int frmbufw;
	int frmbufh;
	glfwGetFramebufferSize(win,&frmbufw,&frmbufh);
	glViewport(0x0,0x0,frmbufw,frmbufh);
	bow_gfxdat.win = win;
}
