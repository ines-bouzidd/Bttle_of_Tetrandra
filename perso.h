#ifndef PERSO_H
#define PERSO_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct
{
    SDL_Surface *perso_image;
    SDL_Rect perso_pos_ecran;
    SDL_Rect perso_pos_partie;
    Mix_Chunk *son;
    // Correction de Mix_chunk à Mix_Chunk
    int direction;
    int score;
    int up;
    int anim;
    int vitesse;
    double acceleration1, acceleration2;
} Personne;

void init(Personne *p, int numperso);
void afficherPerso(Personne p, SDL_Surface *screen);
void movePerso(Personne *p, Uint32 dt, SDL_Surface *screen);
void animerPerso(Personne *p);
// void saut_Personnage ( Personne *P, Uint32 dt, int posx_absolu, int posy_absolu);
// void saut(Personne *p, int seuil);
void saut(Personne *p, int seuil, Uint32 dt);
#endif
