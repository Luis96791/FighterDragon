#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, string path, int frames,int align_x,int align_y)
{
    this->renderer = renderer;
    texture = IMG_LoadTexture(renderer,path.c_str());
    int w,h;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
    rect.w=w;
    rect.h=h;
    rect.x=align_x;
    rect.y=align_y;
    this->frames = 500;
}

Sprite::~Sprite()
{
    //dtor
}

void Sprite::draw(int character_x, int character_y)
{
    SDL_Rect rect_temp;
    rect_temp.w = rect.w;
    rect_temp.h = rect.h;
    rect_temp.x = rect.x+character_x;
    rect_temp.y = rect.y+character_y;
    SDL_RenderCopy(renderer, texture, NULL, &rect_temp);
}


