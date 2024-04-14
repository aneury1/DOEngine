


void create(){
        SDL_GetCurrentDisplayMode(0, &mode);
    window = SDL_CreateWindow(
        "", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN);
    render = new SDLRenderer(SDL_CreateRenderer(
        window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));
    run = render->isRenderOk();
    window_rect.w = mode.w;
    window_rect.h = mode.h;
}