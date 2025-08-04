
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

// Function to wrap text
void wrapText(const char* text, TTF_Font* font, int maxWidth, char* wrappedText) {
    const char* current = text;
    const char* wordStart;
    char line[256] = "";
    char temp[256] = "";
    int width = 0;

    while (*current) {
        wordStart = current;

        // Find the end of the current word
        while (*current && *current != ' ' && *current != '\n') {
            current++;
        }

        // Copy the word to a temporary buffer
        strncpy(temp, wordStart, current - wordStart);
        temp[current - wordStart] = '\0';

        // Check the width of the line if the word is added
        char testLine[256];
        snprintf(testLine, sizeof(testLine), "%s %s", line, temp);
        TTF_SizeText(font, testLine, &width, NULL);

        if (width > maxWidth) {
            // Add the current line to the wrapped text
            strcat(wrappedText, line);
            strcat(wrappedText, "\n");

            // Start a new line with the current word
            strcpy(line, temp);
        } else {
            // Add the word to the current line
            if (*line) {
                strcat(line, " ");
            }
            strcat(line, temp);
        }

        // Move to the next word
        if (*current == ' ') {
            current++;
        }
    }

    // Add the last line to the wrapped text
    if (*line) {
        strcat(wrappedText, line);
        strcat(wrappedText, "\n");
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Text Wrapper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("/home/neon/Documents/projects/DOEngine/sample/DroidSans.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    const char* text = "This is a long paragraph that needs to be wrapped into multiple lines so it can be displayed properly in a limited space.";
    char wrappedText[1024] = "";
    wrapText(text, font, 500, wrappedText);

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Rect renderQuad = {200, 100, 0, 0};
    char* line = strtok(wrappedText, "\n");
    while (line != NULL) {
      
      SDL_Log("%s", line);
       //  SDL_Surface* textSurface = TTF_RenderText_Blended(font, line, textColor);
       // SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
       // renderQuad.w = textSurface->w;
       // renderQuad.h = textSurface->h;
      // SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
      // renderQuad.y += renderQuad.h + 5; // Add some spacing between lines
      //  SDL_FreeSurface(textSurface);
      //  SDL_DestroyTexture(textTexture);
        line = strtok(NULL, "\n");
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

