#if !defined(bow_hdr_gfx)
#define bow_hdr_gfx

#include <bow/bs.h>

#include <GLFW/glfw3.h>

extern struct {
	GLFWwindow * win;
	int          frmbufw;
	int          frmbufh;
} bow_gfxdat;

void bow_initgfx(void);

#endif
