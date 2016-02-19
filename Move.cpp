#include "Move.h"

Move::Move(SDL_Renderer* renderer,vector<Sprite*>sprites,vector<string>cancels)
{
    this->renderer=renderer;
    for(int i=0;i<sprites.size();i++)
    {
        this->sprites.push_back(sprites[i]);
    }
    frame=0;
    current_sprite_frame=1;
    this->cancels = cancels;
}

Move::~Move()
{
    //dtor
}

void Move::draw(int current_sprite,int character_x, int character_y)
{
    Sprite* sprite = sprites[current_sprite];
    sprite->draw(character_x,character_y);
    frame+=100;
}

bool Move::canCancel(string move_name)
{
    for(int i=0;i<cancels.size();i++)
    {
        if(cancels[i]==move_name)
        {
            return true;
        }
    }
    return false;
}
