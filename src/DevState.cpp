#include "DevState.h"

void DevState::onEnter()
{
	fprintf(stdout, "Entered to DevState\n");
	SDL_JoystickEventState(SDL_ENABLE);
	joy = SDL_JoystickOpen(0);
	SDL_bool attached = SDL_JoystickGetAttached(joy);

}

void DevState::onExit()
{
	fprintf(stdout, "Exited to DevState\n");
	SDL_JoystickClose(joy);
}

void DevState::Update()
{
	fprintf(stdout, "Updating DevState\n");
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_KEYDOWN:
			break;
		case SDL_JOYAXISMOTION:
			break;
		case SDL_JOYHATMOTION:
			break;
		case SDL_JOYBALLMOTION:
			break;
		case SDL_JOYBUTTONDOWN:
			break;
		case SDL_JOYBUTTONUP:
			break;
		case SDL_JOYDEVICEADDED:
			break;
		case SDL_JOYDEVICEREMOVED:
			break;
		default:
			break;
		}
	}
}

void DevState::Render()
{
	fprintf(stdout, "Rendering DevState\n");
}

//void DevState::OnQuit()
//{
//
//}
//
//void DevState::OnFullscreen()
//{
//}
//
//void DevState::OnMinimize()
//{
//}
