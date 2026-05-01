#ifndef HEADERS_H
#define HEADERS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdbool.h>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>


int ROWS=6,COLS=6;
double fps=12.0f;






class SDLinit{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        TTF_Font* font2;
        TTF_Font* font3;
    public:
        SDLinit(std::string title,int w,int h);
        ~SDLinit();
        void clear(int *mode);
        void present();
        void drawtext(int x,int y,const std::string &text,bool ch,int type);
        void drawbut(int x,int y,int w,int h,int r,int g,int b,const std::string &text);
        SDL_Renderer* getrenderer(){return renderer;}
        

};



SDLinit::SDLinit(std::string title,int w,int h){
    SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    font=TTF_OpenFont("font.ttf",25);
    font2=TTF_OpenFont("font2.ttf",40);
    font3=TTF_OpenFont("font.otf",30);
    window=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
}
SDLinit::~SDLinit(){
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}
void SDLinit::clear(int *mode){
    if (*mode==0){
        SDL_SetRenderDrawColor(renderer,156,90,60,255);
    }else{
        SDL_SetRenderDrawColor(renderer,70,80,70,255);

    }
    
    SDL_RenderClear(renderer);
}
void SDLinit::present(){
    SDL_RenderPresent(renderer);
}
void SDLinit::drawtext(int x,int y,const std::string &text,bool ch,int type){
    SDL_Color textColor;
    switch(ch){
        case true:
            textColor = {240, 160, 125, 255};
            break;
        case false:
            textColor = {130, 60, 25, 255};

    }
    SDL_Surface* surf; 
    if(type==1){
        surf=TTF_RenderText_Solid(font,text.c_str(),textColor);
    }else{
        surf=TTF_RenderText_Solid(font3,text.c_str(),textColor);
    }
    int tw = surf->w;
    int th = surf->h;
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,surf);
    
    SDL_Rect rect={x,y,tw,th};
    SDL_RenderCopy(renderer,tex,NULL,&rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}
void SDLinit::drawbut(int x,int y,int w,int h,int r,int g,int b,const std::string &text){
    SDL_SetRenderDrawColor(renderer,r,g,b,255);
    SDL_Rect rect6={x,y,w,h};
    SDL_RenderFillRect(renderer,&rect6);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawRect(renderer,&rect6);
    SDL_Color textColor = {140, 60, 105, 255};
    SDL_Surface* surf=TTF_RenderText_Solid(font2,text.c_str(),textColor);
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,surf);
    SDL_Rect rect5={x+27,y+10,w-50,h-30};
    SDL_RenderCopy(renderer,tex,NULL,&rect5);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
    
}








// i m tired , i m tired , just , someone , i need someone to fill this gap, this gut wrenching gap that no amount of repos or projects will fill, you were never even good to me , falling for the person that u could be























class uinter{
    private:
        std::string  state;
        SDLinit& sdl;
        SDL_Texture* marlboro;
        SDL_Texture* oris;
        SDL_Texture* cuba;
        SDL_Texture* marlboro_m;
        SDL_Texture* oris_m;
        SDL_Texture* cuba_m;
        SDL_Texture* fire;
        SDL_Texture* marl_smoked;
        SDL_Texture* cuba_smoked;
        int chooice=0;
        int COLS=6,ROWS=6;
        int current_frame=0;
        Uint32 lframe=0;
        Uint32 current=0;
        Uint32 current_time=0;
        double frame_delay=100;
        bool burning=false;
        int fy=229;
        Uint32 lframe_burn = 0;

    public:
        uinter(SDLinit &sdl);
        void update();
        void color();
        void minus(void);
        void animate(int px,int py,int w,int h);
        bool mouse(int x,int y,int w,int h,int mx,int my);
        void handle(SDL_Event event,int* mode);
        void layout(int mode);
};
uinter::uinter(SDLinit &osdl) : sdl(osdl){
    SDL_Surface* marl=IMG_Load("assets/marl_show.png");
    marlboro=SDL_CreateTextureFromSurface(sdl.getrenderer(),marl);
    SDL_FreeSurface(marl);
    SDL_Surface* ori=IMG_Load("assets/oris_show.png");
    oris=SDL_CreateTextureFromSurface(sdl.getrenderer(),ori);
    SDL_FreeSurface(ori);
    SDL_Surface* cub=IMG_Load("assets/cuba_show.png");
    cuba=SDL_CreateTextureFromSurface(sdl.getrenderer(),cub);
    SDL_FreeSurface(cub);
    

    SDL_Surface* marl_m=IMG_Load("assets/marlboro.png");
    marlboro_m=SDL_CreateTextureFromSurface(sdl.getrenderer(),marl_m);
    SDL_FreeSurface(marl_m);
    SDL_Surface* ori_m=IMG_Load("assets/oris.png");
    oris_m=SDL_CreateTextureFromSurface(sdl.getrenderer(),ori_m);
    SDL_FreeSurface(ori_m);
    SDL_Surface* cub_m=IMG_Load("assets/cuba.png");
    cuba_m=SDL_CreateTextureFromSurface(sdl.getrenderer(),cub_m);
    SDL_FreeSurface(cub_m);

    SDL_Surface* fire_s=IMG_Load("assets/fire.png");
    fire=SDL_CreateTextureFromSurface(sdl.getrenderer(),fire_s);
    SDL_FreeSurface(fire_s);



    SDL_Surface* marl_sm=IMG_Load("assets/marl_smo.png");
    marl_smoked=SDL_CreateTextureFromSurface(sdl.getrenderer(),marl_sm);
    SDL_FreeSurface(marl_sm);
    SDL_Surface* cuba_sm=IMG_Load("assets/cuba_smo.png");
    cuba_smoked=SDL_CreateTextureFromSurface(sdl.getrenderer(),cuba_sm);
    SDL_FreeSurface(marl_sm);




}
void uinter::minus(void){
    fy=fy+1;
}


void uinter::animate(int px,int py,int w,int h){
        int W,H;
        SDL_QueryTexture(fire,NULL,NULL,&W,&H);
        int framewidth=W/6;
        int frameheight=H/6;
        SDL_Rect rect;
        rect.w=framewidth;
        rect.h=frameheight;
        int framex=current_frame%6;
        int framey=current_frame/6;
        rect.x=framex*framewidth;
        rect.y=framey*frameheight;
        SDL_Rect dst;
        dst.x=px;
        dst.y=py;
        dst.w=w;
        dst.h=h;

        current_time = SDL_GetTicks();
        if (current_time > lframe + frame_delay) {
            current_frame = (current_frame + 1) % 36; 
            lframe = current_time;
        }
        SDL_RenderCopy(sdl.getrenderer(), fire, &rect, &dst);

}





void uinter::update(){
    std::ifstream file("state.txt");
    std::string line;
    std::getline(file,line);
    state=line[0];
    file.close();
    Uint32 now = SDL_GetTicks();
    if(state=="1" || state=="0"){
        if(std::stoi(state)==1 && burning && now > lframe_burn + 150){
            lframe_burn = now;
            
            minus();
            
            
        }
    }
    
}
void uinter::handle(SDL_Event event,int* mode){
    if(event.type==SDL_KEYDOWN){
        SDL_Keycode key=event.key.keysym.sym;
        if(key==SDLK_ESCAPE && mode!=0){
            *mode=0;
            fy=229;
            burning=false;
        }else if(key==SDLK_i){
            if(burning){minus();}
        }
    

    }else if (event.type==SDL_MOUSEBUTTONDOWN){
        if (event.button.button==SDL_BUTTON_LEFT){
            if(*mode==0){
            int mx=event.button.x;
            int my=event.button.y;
            if(mouse(875,70,370,50,mx,my)){
                chooice=1;
            }else if(mouse(890,200,370,50,mx,my)){
                chooice=2;
            }else if(mouse(845,280,400,70,mx,my)){
                chooice=3;
            }else if (mouse (540,500,200,100,mx,my) && chooice!=0){
                *mode=1;
            }
            }
        else{
            int mx=event.button.x;
            int my=event.button.y;
            if (mouse(980,100,100,50,mx,my) && !burning){
                *mode=0;
                fy=229;
                burning=false;
        }
       
    }
        }}

}
bool uinter::mouse(int x,int y,int w,int h,int mx,int my){
    if(mx>x && mx<x+w && my>y && my<y+h){
        return true;
    }
    return false;

}



void uinter::layout(int mode){
    switch(mode){
        case 0 :{
            SDL_Rect mar={830,-50,500,300};
            SDL_RenderCopy(sdl.getrenderer(),marlboro,NULL,&mar);
            sdl.drawtext(700,90,"marlboro red",chooice==1,1);


            SDL_Rect ories={810,70,530,300};
            SDL_RenderCopy(sdl.getrenderer(),oris,NULL,&ories);
            sdl.drawtext(700,205,"oris(for bitches) ",chooice==2,1);

            SDL_Rect cubas={810,190,480,250};
            SDL_RenderCopy(sdl.getrenderer(),cuba,NULL,&cubas);
            sdl.drawtext(700,310,"cuban cigars ",chooice==3,1);


            sdl.drawbut(540,500,200,100,245, 230, 211,"smoke !");
            break;}
        case 1 :
            if (fy>540){
                burning=false;
            }else{
                burning =true;
            }
            SDL_Rect cigar={450,190,400,600};
            SDL_Rect cigar2={440,170,420,600};
            switch(chooice){
                case 1 :{
                    SDL_RenderCopy(sdl.getrenderer(),marlboro_m,NULL,&cigar);
                    SDL_Rect ash={445,110,410,fy-59};
                    SDL_RenderSetClipRect(sdl.getrenderer(), &ash);
                    SDL_RenderCopy(sdl.getrenderer(), marl_smoked, NULL, &cigar2);
                    SDL_RenderSetClipRect(sdl.getrenderer(), NULL);
                    animate(620,fy,60,100);
                    if(!burning){
                        sdl.drawtext(300,100,"its swweet isnt it , want another one :3 ?",true,0);
                        sdl.drawbut(980,100,100,50,160, 230, 187,"YESSS!");
                    }
                    
                    break;}
                case 2 :{
                    SDL_RenderCopy(sdl.getrenderer(),oris_m,NULL,&cigar);
                    SDL_Rect ash={445,110,410,fy-59};
                    SDL_Rect cigar2={435,170,430,600};
                    SDL_RenderSetClipRect(sdl.getrenderer(), &ash);
                    SDL_RenderCopy(sdl.getrenderer(), marl_smoked, NULL, &cigar2);
                    SDL_RenderSetClipRect(sdl.getrenderer(), NULL);
                    animate(620,fy,60,100);
                    if(!burning){
                        sdl.drawtext(300,100,"its swweet isnt it , want another one :3 ?",true,0);
                        sdl.drawbut(980,100,100,50,160, 230, 187,"YESSS!");
                    }
                    break;}
                case 3 :
                    SDL_RenderCopy(sdl.getrenderer(),cuba_m,NULL,&cigar);
                    SDL_Rect ash={445,110,410,fy-92};
                    SDL_RenderSetClipRect(sdl.getrenderer(), &ash);
                    SDL_RenderCopy(sdl.getrenderer(), cuba_smoked, NULL, &cigar2);
                    SDL_RenderSetClipRect(sdl.getrenderer(), NULL);
                    animate(597,fy-30,107,100);
                    if(!burning){
                        sdl.drawbut(980,100,100,50,160, 230, 187,"YESSS!");
                        sdl.drawtext(300,100,"its swweet isnt it , want another one :3 ?",true,0);
                    }
                    
                    break;
                }
        
        }

    }

#endif
