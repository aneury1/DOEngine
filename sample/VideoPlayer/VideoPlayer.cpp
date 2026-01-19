extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include "DOEngine_SDL_includes.h"
#include <iostream>
int main(int argc, char* argv[])
{
 

    const char* filename = "/home/neonland/snap/obs-studio/1316/1.mp4";/// argv[1];

    avformat_network_init();

    AVFormatContext* formatCtx = nullptr;
    avformat_open_input(&formatCtx, filename, nullptr, nullptr);
    avformat_find_stream_info(formatCtx, nullptr);

    int videoStream = -1;
    for (unsigned i = 0; i < formatCtx->nb_streams; i++) {
        if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }

    AVCodecParameters* codecPar = formatCtx->streams[videoStream]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codecPar->codec_id);

    AVCodecContext* codecCtx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecCtx, codecPar);
    avcodec_open2(codecCtx, codec, nullptr);

   SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Video Player",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        codecCtx->width,
        codecCtx->height,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_IYUV,
        SDL_TEXTUREACCESS_STREAMING,
        codecCtx->width,
        codecCtx->height
    );

        AVPacket packet;
    AVFrame* frame = av_frame_alloc();

    bool running = true;
    SDL_Event event;

    while (running && av_read_frame(formatCtx, &packet) >= 0) {
        if (packet.stream_index == videoStream) {
            avcodec_send_packet(codecCtx, &packet);

            while (avcodec_receive_frame(codecCtx, frame) == 0) {

                SDL_UpdateYUVTexture(
                    texture,
                    nullptr,
                    frame->data[0], frame->linesize[0],
                    frame->data[1], frame->linesize[1],
                    frame->data[2], frame->linesize[2]
                );

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, nullptr, nullptr);
                SDL_RenderPresent(renderer);

                SDL_Delay(33); // ~30 FPS
            }
        }

        av_packet_unref(&packet);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }
    }
    av_frame_free(&frame);
    avcodec_free_context(&codecCtx);
    avformat_close_input(&formatCtx);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
