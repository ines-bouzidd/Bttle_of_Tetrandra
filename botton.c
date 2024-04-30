#include "botton.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>




void initboutonn(boutton *b[],int n,char *nomb[],int posbx[],int posby[]){
 int i;
  for (i = 0; i < n; i++) {
        b[i] = malloc(sizeof(boutton));
        if (b[i] == NULL) {
            fprintf(stderr, "Echec d'allocation mémoire pour le bouton %d.\n", i);
            exit(1);
        }

      b[i]->image[0] = IMG_Load(nomb[2 * i]);     
      b[i]->image[1] = IMG_Load(nomb[2 * i + 1]);
     
     
        if (b[i]->image[0] == NULL || b[i]->image[1] == NULL) {
            fprintf(stderr, "Echec de chargement de l'image pour le bouton %d.\n", i);
            exit(1);
        }  
        
     b[i]->posimg.x = posbx[i];
     b[i]->posimg.y = posby[i];
     b[i]->posimg.w = b[i]->image[0]->w;
     b[i]->posimg.h = b[i]->image[0]->h;
    b[i]->actif = 0; 
    b[i]->son = Mix_LoadWAV("soundeffect.wav");
    if (b[i]->son == NULL) {
            fprintf(stderr, "Echec de chargement du son : %s.\n", Mix_GetError());
            exit(1);
        }
}}




void afficherboutonn(boutton *b[],SDL_Surface *ecran,int n){
int i;
    for (i = 0; i < n; i++) {
        SDL_BlitSurface(b[i]->image[b[i]->actif], NULL, ecran, &b[i]->posimg);
    }}









void cleanboutton(boutton *b[],int n) {
    int i;
    for (i = 0; i < n; i++) {
        SDL_FreeSurface(b[i]->image[0]);
        SDL_FreeSurface(b[i]->image[1]);
        Mix_FreeChunk(b[i]->son);
        free(b[i]);
    }
}












/*void bouttonevents(boutton *boutons[], SDL_Event *event, background *b) {
    int x, y;
    switch (event->type) {
        case SDL_MOUSEMOTION:
            x = event->motion.x;
            y = event->motion.y;
            for (int j = 0; j < 3; j++) {
                if ((x >= boutons[j]->posimg.x) && (x <= boutons[j]->posimg.x + boutons[j]->posimg.w) &&
                    (y >= boutons[j]->posimg.y) && (y <= boutons[j]->posimg.y + boutons[j]->posimg.h) &&
                    (b->niveau == 0)) {
                    boutons[j]->actif = 1;
                    Mix_PlayChannel(-1, boutons[j]->son, 0);
                } else {
                    boutons[j]->actif = 0;
                }
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            x = event->button.x;
            y = event->button.y;
            if (event->button.button == SDL_BUTTON_LEFT) {
                for (int j = 0; j < 3; j++) {
                    if ((x >= boutons[j]->posimg.x) && (x <= boutons[j]->posimg.x + boutons[j]->posimg.w) &&
                        (y >= boutons[j]->posimg.y) && (y <= boutons[j]->posimg.y + boutons[j]->posimg.h) &&
                        (b->niveau == 0)) {
                        // Perform action based on the button clicked
                        if (j == 0) {
                            b->niveau = 2;
                        } else if (j == 1) {
                            b->niveau = 1;
                        } else if (j == 2) {
                            quitter = 0;
                        }
                    }
                }
            }
            break;

        // Add more cases if needed (e.g., SDL_MOUSEBUTTONUP)

        default:
            break;
    }
}

*/


