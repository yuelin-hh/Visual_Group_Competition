#define SDL_MAIN_HANDLED
#include "scene_manager.h"

int main(int argc, char** argv)
{
	return SceneManager::instance()->run(argc,argv);
}