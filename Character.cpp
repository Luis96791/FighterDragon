#include "Character.h"

std::string toString(int number)
{
    if (number == 0)
        return "0";

    if(number < 0)
        return "-"+toString(-number);
    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

Character::Character(SDL_Renderer* renderer, int x, int y)
{
    this->x=x;
    this->y=y;

    moves["bola"]=getMove(renderer,"bola",6);
    moves["vuelta"]=getMove(renderer,"vuelta",10);

    this->current_move = "bola";
    this->current_sprite = 0;
    this->current_sprite_frame = 0;
}

Move* Character::getMove(SDL_Renderer *renderer, string name, int sprite_amount)
{
    //Sprites load
    vector<Sprite*>sprites;
    string align_file_path = "assets/" + name + "/align.txt";
    ifstream align_file(align_file_path.c_str());
    for(int i=1;i<=sprite_amount;i++)
    {
        string path="assets/" + name + "/" + toString(i) + ".png";
        int align_x;
        int align_y;
        align_file>>align_x;
        align_file>>align_y;

        sprites.push_back(new Sprite(renderer,path,500,align_x,align_y));
    }

    //Cancel load
    string cancels_file_path = "assets/" + name + "/cancel.txt";
    ifstream cancels_file(cancels_file_path.c_str());
    vector<string>cancels;
    string cancel_temp;
    while(cancels_file>>cancel_temp)
    {
        cancels.push_back(cancel_temp);
    }

    return new Move(renderer,sprites,cancels);
}

Character::~Character()
{
    //dtor
}

void Character::logic()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    if( currentKeyStates[ SDL_SCANCODE_Q ] )
    {
        this->current_move = "bola";
        this->current_sprite = 0;
    }
    else if( currentKeyStates[ SDL_SCANCODE_W ] )
    {
        if(moves["bola"]->canCancel(this->current_move))
        {
            this->current_move = "bola";
            this->current_sprite = 0;
        }
    }
    else if( currentKeyStates[ SDL_SCANCODE_E ] )
    {
        if(moves["vuelta"]->canCancel(this->current_move))
        {
            this->current_move = "vuelta";
            this->current_sprite = 0;
        }
    }
    else if( currentKeyStates[ SDL_SCANCODE_R ] )
    {
        if(moves["bola"]->canCancel(this->current_move))
        {
            if(this->current_move!="bola")
            {
                this->current_sprite = 0;
            }
            this->current_move = "bola";
            this->x-=1;
        }
    }
    else if( currentKeyStates[ SDL_SCANCODE_T ] )
    {
        if(this->current_move=="bola"
           || this->current_move=="bola")
       {
            if(this->current_move!="bola")
            {
                this->current_sprite = 0;
            }
            this->current_move = "bola";
            this->x+=1;
       }

    }
    else if( currentKeyStates[ SDL_SCANCODE_M ] )
    {
        if(this->current_move=="bola"
           || this->current_move=="bola")
       {
            if(this->current_move!="bola")
            {
                this->current_sprite = 0;
            }
            this->current_move = "bola";
            this->x-=1;
       }

    }
    else
    {
        if(this->current_move=="bola")
        {
            this->current_move = "bola";
            this->current_sprite = 0;
        }
    }

    current_sprite_frame+=1;
    if(current_sprite_frame>=moves[current_move]->sprites[current_sprite]->frames)
    {
        current_sprite++;
        if(current_sprite>=moves[current_move]->sprites.size())
        {
            current_move= "bola";
            current_sprite=0;
        }
        current_sprite_frame=0;
    }
}

void Character::draw()
{
    moves[current_move]->draw(current_sprite,x,y);
}
