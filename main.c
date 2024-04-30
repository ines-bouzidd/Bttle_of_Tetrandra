#include "botton.h"
#include "background.h"
#include "perso.h"
#include "background_perso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_ttf.h>

int main(int argc, char **argv)
{
    int quitter = 1;
    int j = 0, vol = 5, i = 0;
    int x = 0, y = 0;
    background *bkg = malloc(sizeof(background));
    backanim *anim = malloc(sizeof(backanim));

    boutton *b[3];
    boutton *bop[4];
    SDL_Surface *ecran;
    SDL_Event event;
    Mix_Music *music;
    Uint32 startTime, endTime;
    // text
    SDL_Rect pos_texte;
    SDL_Surface *texte = NULL;
    TTF_Font *police;
    SDL_Color textColor;
    // les bouttons du menu principale
    char *nomb[] = {"bplay1.png", "bplay2.png", "boption1.png", "boption2.png", "quit1.png", "quit2.png"};
    int posbx[] = {50, 175, 300};
    int posby[] = {500, 500, 500, 500};
    // les bouttons du menu option
    char *nombop[] = {"bop_on.png", "bop_off.png", "bop_plus_off.png", "bop_plus_on.png", "bop_moi_off.png", "bop_moi_on.png", "full_off.png", "full.png"};
    int posbopx[] = {140, 140, 265, 140};
    int posbopy[] = {200, 300, 300, 400};
    // pour le perso et boucle du jeux:
    Personne *p = malloc(sizeof(Personne));
    background_perso *bj = malloc(sizeof(background_perso));
    Uint32 startTimej, endTimej;
    Uint32 dt, t_prev;

    // Initialisation
    TTF_Init();
    if (TTF_Init() != 0)
    {
        printf("Echec d'initialisation de SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        printf("SDL est initialise avec succes.\n");
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
        if (ecran == NULL)
        {
            fprintf(stderr, "Echec de creation de la fenetre : %s.\n", SDL_GetError());
            exit(1);
        }
        // Initialisation des background et des bouttons du menu et du option:
        initBackg(bkg);
        initboutonn(b, 3, nomb, posbx, posby);
        initboutonn(bop, 4, nombop, posbopx, posbopy);
        initanim(anim);
        music = Mix_LoadMUS("son_continue.mp3");
        if (music == NULL)
        {
            fprintf(stderr, "Erreur de chargement de music: %s\n", Mix_GetError());
            exit(1);
        }
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 2); // le volume est intialiser au moitier

        // texte:
        // position du texte
        pos_texte.x = 25;
        pos_texte.y = 10;
        // couleur du texte noire
        textColor.r = 255;
        textColor.b = 255;
        textColor.g = 255;
        // téléchargement du police
        police = TTF_OpenFont("arial.ttf", 20);
        texte = TTF_RenderText_Blended(police, "APEX", textColor);
        if (texte == NULL)
        {
            fprintf(stderr, "Echec de rendu du texte : %s\n", TTF_GetError());
            return 1;
        }

        // initialisation du jeux:
        // initialisation_perso
        init(p, 1);
        initBackg_perso(bj);

        while (quitter)
        {
            startTime = SDL_GetTicks();
            afficherBack(bkg, ecran);

            switch (bkg->niveau)
            {
            case 0:

                SDL_BlitSurface(anim->image[i], NULL, ecran, NULL);
                // affichage du texte:
                SDL_BlitSurface(texte, NULL, ecran, &pos_texte);
                afficherboutonn(b, ecran, 3);
                SDL_Flip(ecran);
                endTime = SDL_GetTicks();
                if (endTime - startTime < 0)
                {
                    SDL_Delay(0 - (endTime - startTime));
                }
                i++;
                if (i >= 18)
                {
                    i = 0;
                }
                break;
            case 2:
                afficherboutonn(bop, ecran, 4);
                break;
            case 1:
                afficherBack_perso(bj, ecran);
                startTimej = SDL_GetTicks();
                t_prev = SDL_GetTicks();
                // SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
                afficherPerso(*p, ecran);

                SDL_Flip(ecran);
                endTimej = SDL_GetTicks();
                // Cap the frame rate
                if (endTimej - startTimej < (1000 / 60))
                {
                    SDL_Delay((1000 / 60) - (endTimej - startTimej));
                }
                dt = SDL_GetTicks() - t_prev;

                break;
            }

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quitter = 0;
                }
                switch (bkg->niveau)
                {
                case 0:
                    switch (event.type)
                    {
                    case SDL_KEYDOWN:
                    {
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            quitter = 0;
                            break;
                        case SDLK_p:
                            bkg->niveau = 1;
                            break;
                        case SDLK_o:
                            bkg->niveau = 2;
                            break;
                            // entre
                        case SDLK_RETURN:
                        {
                            if (b[0]->actif == 1 && b[1]->actif == 0 && b[2]->actif == 0)
                                bkg->niveau = 1;
                            else if (b[1]->actif == 1 && b[0]->actif == 0 && b[2]->actif == 0)
                                bkg->niveau = 2;
                            else if (b[2]->actif == 1 && b[0]->actif == 0 && b[1]->actif == 0)
                                quitter = 0;
                            else if (b[0]->actif == 0 && b[1]->actif == 0 && b[2]->actif == 0)
                                bkg->niveau = 0;
                        }
                        break;
                        }

                        // les fleches:
                        if (b[0]->actif == 0 && b[1]->actif == 0 && b[2]->actif == 0 && event.key.keysym.sym == SDLK_RIGHT)
                        {
                            b[0]->actif = 1;
                            Mix_PlayChannel(-1, b[0]->son, 0);
                            b[1]->actif = 0;
                            b[2]->actif = 0;
                        }
                        else if (b[0]->actif == 1 && b[1]->actif == 0 && b[2]->actif == 0 && event.key.keysym.sym == SDLK_RIGHT)
                        {
                            b[1]->actif = 1;
                            Mix_PlayChannel(-1, b[0]->son, 0);
                            b[0]->actif = 0;
                            b[2]->actif = 0;
                        }
                        else if (b[0]->actif == 0 && b[1]->actif == 1 && b[2]->actif == 0 && event.key.keysym.sym == SDLK_RIGHT)
                        {
                            b[2]->actif = 1;
                            Mix_PlayChannel(-1, b[0]->son, 0);
                            b[0]->actif = 0;
                            b[1]->actif = 0;
                        }
                        else if (b[0]->actif == 0 && b[1]->actif == 0 && b[2]->actif == 1 && event.key.keysym.sym == SDLK_LEFT)
                        {
                            b[1]->actif = 1;
                            Mix_PlayChannel(-1, b[0]->son, 0);
                            b[0]->actif = 0;
                            b[2]->actif = 0;
                        }
                        else if (b[0]->actif == 0 && b[1]->actif == 1 && b[2]->actif == 0 && event.key.keysym.sym == SDLK_LEFT)
                        {
                            b[0]->actif = 1;
                            Mix_PlayChannel(-1, b[0]->son, 0);
                            b[1]->actif = 0;
                            b[2]->actif = 0;
                        }
                        else
                            for (j = 0; j < 3; j++)
                                b[j]->actif = 0;
                    }
                    break; // fin SDL_KEYDOWN
                    case SDL_MOUSEMOTION:
                    {
                        x = event.motion.x;
                        y = event.motion.y;

                        if ((x >= b[0]->posimg.x) && (x <= b[0]->posimg.x + b[0]->posimg.w) &&
                            (y >= b[0]->posimg.y) && (y <= b[0]->posimg.y + b[0]->posimg.h))
                        {
                            b[0]->actif = 1;
                            Mix_PlayChannel(-1, b[0]->son, 0);
                            b[1]->actif = 0;
                            b[2]->actif = 0;
                        }
                        else if ((x >= b[1]->posimg.x) && (x <= b[1]->posimg.x + b[1]->posimg.w) &&
                                 (y >= b[1]->posimg.y) && (y <= b[1]->posimg.y + b[1]->posimg.h))
                        {
                            b[1]->actif = 1;
                            Mix_PlayChannel(-1, b[1]->son, 0);
                            b[0]->actif = 0;
                            b[2]->actif = 0;
                        }
                        else if ((x >= b[2]->posimg.x) && (x <= b[2]->posimg.x + b[2]->posimg.w) &&
                                 (y >= b[2]->posimg.y) && (y <= b[2]->posimg.y + b[2]->posimg.h))
                        {
                            b[2]->actif = 1;
                            Mix_PlayChannel(-1, b[2]->son, 0);
                            b[0]->actif = 0;
                            b[1]->actif = 0;
                        }
                        else
                            for (j = 0; j < 3; j++)
                                b[j]->actif = 0;
                        break;
                    }
                    break; // fin_boutton_motion
                    case SDL_MOUSEBUTTONDOWN:
                    {
                        if (event.button.button == SDL_BUTTON_LEFT)
                        {
                            x = event.button.x;
                            y = event.button.y;
                            if ((x >= b[0]->posimg.x) && (x <= b[0]->posimg.x + b[0]->posimg.w) && (y >= b[0]->posimg.y) && (y <= b[0]->posimg.y + b[0]->posimg.h))
                                bkg->niveau = 1;
                            if ((x >= b[1]->posimg.x) && (x <= b[1]->posimg.x + b[1]->posimg.w) && (y >= b[1]->posimg.y) && (y <= b[1]->posimg.y + b[1]->posimg.h))
                                bkg->niveau = 2;
                            if ((x >= b[2]->posimg.x) && (x <= b[2]->posimg.x + b[2]->posimg.w) && (y >= b[2]->posimg.y) && (y <= b[2]->posimg.y + b[2]->posimg.h))
                                quitter = 0;
                        }
                        break;
                    }
                    break; // fin MOUSE_BUTTONDOWN
                    } // fin switch
                    break; // fin du case 0 (menu principale)

                case 2:
                    switch (event.type)
                    {
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            bkg->niveau = 0;
                            break;
                        case SDLK_RIGHT:
                            if (vol < 10)
                            {

                                Mix_VolumeMusic(Mix_VolumeMusic(-1) + (int)(0.1 * MIX_MAX_VOLUME));
                                vol++;
                                bop[1]->actif = 1;
                                bop[2]->actif = 0;
                            }
                            Mix_PlayChannel(-1, bop[0]->son, 0);
                            break;
                        case SDLK_LEFT:
                            if (vol > 0)
                            {

                                Mix_VolumeMusic(Mix_VolumeMusic(-1) - (int)(0.1 * MIX_MAX_VOLUME));
                                vol--;
                                bop[2]->actif = 1;
                                bop[1]->actif = 0;
                            }
                            else if (vol == 0)
                            {
                                Mix_VolumeMusic(0);
                            }
                            Mix_PlayChannel(-1, bop[0]->son, 0);
                            break;
                        case SDLK_m:
                            bop[0]->actif = 1;
                            Mix_VolumeMusic(0);
                            Mix_PlayChannel(-1, bop[0]->son, 0);
                            break;
                        case SDLK_u:
                            bop[0]->actif = 0;
                            Mix_VolumeMusic((int)(0.1 * MIX_MAX_VOLUME)); // prob
                            Mix_PlayChannel(-1, bop[0]->son, 0);
                            break;
                            // full screen
                        case SDLK_f:
                            ecran = SDL_SetVideoMode(1850, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            bop[3]->actif = 1;
                            Mix_PlayChannel(-1, bop[0]->son, 0);
                            break;
                        case SDLK_w:
                            ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            bop[3]->actif = 0;
                            Mix_PlayChannel(-1, bop[0]->son, 0);
                            break;
                        }
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                    {
                        if (event.button.button == SDL_BUTTON_LEFT)
                        {
                            x = event.button.x;
                            y = event.button.y;

                            if ((x >= bop[1]->posimg.x) && (x <= bop[1]->posimg.x + bop[1]->posimg.w) && (y >= bop[1]->posimg.y) && (y <= bop[1]->posimg.y + bop[1]->posimg.h) && vol < 10)

                            {
                                bop[1]->actif = 1;
                                bop[2]->actif = 0;
                                Mix_VolumeMusic(Mix_VolumeMusic(-1) + (int)(0.1 * MIX_MAX_VOLUME));
                                vol++;

                                Mix_PlayChannel(-1, bop[0]->son, 0);
                            }
                            else if ((x >= bop[2]->posimg.x) && (x <= bop[2]->posimg.x + bop[2]->posimg.w) && (y >= bop[2]->posimg.y) && (y <= bop[2]->posimg.y + bop[2]->posimg.h) && vol > 0)

                            {

                                bop[2]->actif = 1;
                                bop[1]->actif = 0;
                                Mix_VolumeMusic(Mix_VolumeMusic(-1) - (int)(0.1 * MIX_MAX_VOLUME));
                                vol--;
                                Mix_PlayChannel(-1, bop[0]->son, 0);
                            }

                            else if ((x >= bop[0]->posimg.x) && (x <= bop[0]->posimg.x + bop[0]->posimg.w) && (y >= bop[0]->posimg.y) && (y <= bop[0]->posimg.y + bop[0]->posimg.h) && (vol != 0))

                            {
                                bop[0]->actif = 1;
                                Mix_VolumeMusic(0);
                                Mix_PlayChannel(-1, bop[0]->son, 0);
                                vol = 0;
                            }
                            else if ((x >= bop[0]->posimg.x) && (x <= bop[0]->posimg.x + bop[0]->posimg.w) && (y >= bop[0]->posimg.y) && (y <= bop[0]->posimg.y + bop[0]->posimg.h) && (vol == 0))

                            {
                                bop[0]->actif = 0;
                                Mix_VolumeMusic((int)(0.1 * MIX_MAX_VOLUME));
                                Mix_PlayChannel(-1, bop[0]->son, 0);
                                vol = 5;
                            }
                            else if ((x >= bop[3]->posimg.x) && (x <= bop[3]->posimg.x + bop[3]->posimg.w) && (y >= bop[3]->posimg.y) && (y <= bop[3]->posimg.y + bop[3]->posimg.h) && bop[3]->actif == 0)

                            {
                                ecran = SDL_SetVideoMode(1850, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                bop[3]->actif = 1;
                                Mix_PlayChannel(-1, bop[0]->son, 0);
                            }
                            else if ((x >= bop[3]->posimg.x) && (x <= bop[3]->posimg.x + bop[3]->posimg.w) && (y >= bop[3]->posimg.y) && (y <= bop[3]->posimg.y + bop[3]->posimg.h) && bop[3]->actif == 1)

                            {
                                ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                bop[3]->actif = 0;
                                Mix_PlayChannel(-1, bop[0]->son, 0);
                            }
                        }
                        break;
                    }
                    break; // fin MOUSE_BUTTONDOWN

                    } // fin switch event

                    break;
                    // case du jeux:
                case 1:

                    if (event.type == SDL_KEYDOWN) // keyup
                    {
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_ESCAPE:
                            bkg->niveau = 0;
                            break;
                        case SDLK_RIGHT:
                            p->direction = 1;
                            movePerso(p, dt, ecran);
                            animerPerso(p);
                            p->acceleration1 += 0.005;
                             p->acceleration2 = 0;

                            printf("%f ", p->acceleration1);
                            break;
                        case SDLK_LEFT:
                            p->direction = 2;
                            movePerso(p, dt, ecran);
                            animerPerso(p);
                            p->acceleration2 += 0.005;
                            p->acceleration1 = 0;

                            break;

                        case SDLK_UP:
                            p->up = 1;
                            saut(p, (p->perso_image->h) / 4,dt);
                            break;
                        }
                        break;
                    }

                    else if (event.type == SDL_KEYUP)
                    {
                        if (event.key.keysym.sym == SDLK_UP)
                        {
                            p->up = 0;
                            saut(p, 350, dt);
                        }
                    }
                }
                break;
            }
        }
    }
    cleanboutton(b, 3);
    cleanboutton(bop, 3);
    cleanBack(bkg);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    cleananim(anim);
    TTF_Quit();
    return 0;
}
