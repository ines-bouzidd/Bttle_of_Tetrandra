
#include <math.h>
#include "perso.h"

void init(Personne *p, int numperso)
{
    p->up = 0;
    p->direction = 1;
    p->anim = 0;
    p->vitesse = 6;
    p->acceleration1 = 0;
    p->acceleration2 = 0;

    p->perso_image = IMG_Load("perso.png");
    if (p->perso_image == NULL)
    {
        fprintf(stderr, "Echec de chargement de l'image pour le bouton.\n");
        exit(1);
    }
    p->perso_pos_ecran.x = 5;
    p->perso_pos_ecran.y = 420;
    p->perso_pos_ecran.w = (p->perso_image->w) / 6;
    p->perso_pos_ecran.h = (p->perso_image->h) / 4;

    p->perso_pos_partie.x = 0;
    p->perso_pos_partie.y = 0;
    p->perso_pos_partie.w = (p->perso_image->w) / 6; // 150
    p->perso_pos_partie.h = (p->perso_image->h) / 4; // 200
}

void afficherPerso(Personne p, SDL_Surface *screen)
{
    SDL_BlitSurface(p.perso_image, &p.perso_pos_partie, screen, &p.perso_pos_ecran);
}

void movePerso(Personne *p, Uint32 dt, SDL_Surface *screen)
{

    switch (p->direction)
    {
    case 1:
        p->perso_pos_ecran.x += 0.5 * (p->acceleration1) * dt * dt + (p->vitesse) * dt;
        p->perso_pos_ecran.y = 420;
        p->perso_pos_ecran.w = (p->perso_image->w) / 6;
        p->perso_pos_ecran.h = (p->perso_image->h) / 4;

        p->perso_pos_partie.x = 0;
        p->perso_pos_partie.y = 0;
        p->perso_pos_partie.w = (p->perso_image->w) / 6;
        p->perso_pos_partie.h = (p->perso_image->h) / 4;
        p->anim++;
        break;
    case 2:
        p->perso_pos_ecran.x -= 0.5 * (p->acceleration2) * dt * dt + (p->vitesse) * dt;
        p->perso_pos_ecran.y = 420;
        p->perso_pos_ecran.w = (p->perso_image->w) / 6;
        p->perso_pos_ecran.h = (p->perso_image->h) / 4;
        p->perso_pos_partie.x = 0;
        p->perso_pos_partie.y = (p->perso_image->h) / 4;
        p->perso_pos_partie.w = (p->perso_image->w) / 6;
        p->perso_pos_partie.h = (p->perso_image->h) / 4;
        p->anim++;
        break;
    }
    
    if (p->perso_pos_ecran.x < 0)
        p->perso_pos_ecran.x = 0;
    else if (p->perso_pos_ecran.x > (screen->w - p->perso_pos_partie.w))
        p->perso_pos_ecran.x = screen->w - p->perso_pos_ecran.w;
}

void animerPerso(Personne *p)
{

    switch (p->direction)
    {
    case 1:

        p->perso_pos_partie.x = ((p->perso_image->w) / 6) * (p->anim % 6);
        p->perso_pos_partie.y = 0;
        p->perso_pos_partie.w = (p->perso_image->w) / 6;
        p->perso_pos_partie.h = (p->perso_image->h) / 4;

        break;
    case 2:

        p->perso_pos_partie.x = ((p->perso_image->w) / 6) * (p->anim % 6);
        p->perso_pos_partie.y = p->perso_image->h / 4;
        p->perso_pos_partie.w = (p->perso_image->w) / 6;
        p->perso_pos_partie.h = (p->perso_image->h) / 4;

        break;

    case 3:

        p->perso_pos_partie.x = ((p->perso_image->w) / 6) * (p->anim % 6);
        p->perso_pos_partie.y = (p->perso_image->h) / 2; // 400;
        p->perso_pos_partie.w = (p->perso_image->w) / 6;
        p->perso_pos_partie.h = (p->perso_image->h) / 4;

        break;
    case 4:

        p->perso_pos_partie.x = ((p->perso_image->w) / 6) * (p->anim % 6);
        p->perso_pos_partie.y = (p->perso_image->h) * 3 / 2; // 400;
        p->perso_pos_partie.w = (p->perso_image->w) / 6;
        p->perso_pos_partie.h = (p->perso_image->h) / 4;
    }
}

void saut(Personne *p, int seuil, Uint32 dt)
{
    double maxJumpHeight = 420.0 - seuil;
    double startJumpHeight = 90;
    double jumpSpeed = 5;

    if (p->up == 1 && p->perso_pos_ecran.y >= (420 - seuil))
    {

        double jumpHeight = startJumpHeight * (1 + fabs(p->acceleration1) * 2500);
        double deltaY = jumpSpeed * (dt);
        if (jumpHeight > maxJumpHeight)
        {
            jumpHeight = maxJumpHeight;
        }
        p->perso_pos_ecran.y -= (int)deltaY;

        if (p->perso_pos_ecran.y < (420 - jumpHeight))
            p->perso_pos_ecran.y = (420 - jumpHeight);

        if (p->direction == 1)
            p->perso_pos_ecran.x += 80;
     
        else if (p->direction == 2)
            p->perso_pos_ecran.x -= 80;         
        animerPerso(p);
        p->up = 0;
    }
    else
    {
        double deltaY = jumpSpeed * (dt);
        p->perso_pos_ecran.y += (int)deltaY;

        if (p->perso_pos_ecran.y > 420)
            p->perso_pos_ecran.y = 420;

        animerPerso(p);

        p->up = 1;
    }
    
}

/*void saut(Personne *p, int seuil, Uint32 dt)
{
    double startjumpheight = 50;
    static double jumpSpeed = 1;
    double accelerationFactor = fabs(p->acceleration1);

    if (p->up == 1)
    {
        double jumpDistance = 0.0;
        double adjustedJumpHeight = startjumpheight * (1 + accelerationFactor);
        if(adjustedJumpHeight>420-seuil)
        {
            adjustedJumpHeight=420-seuil;


        }
        if (p->acceleration1 > 0)
        {
            jumpDistance = 0.7 * adjustedJumpHeight * pow(dt, 2) + p->vitesse;
        }
        else if (p->acceleration1 < 0)
        {
            jumpDistance = -0.7 * adjustedJumpHeight * pow(dt, 2) + p->vitesse;
        }

        while (p->perso_pos_ecran.y > (450 - adjustedJumpHeight))
        {
            p->perso_pos_ecran.y -= jumpSpeed;
            p->perso_pos_ecran.x += (int)jumpDistance;
            animerPerso(p);
        }
    }
    else
    {
        while (p->perso_pos_ecran.y < 450)
        {
            p->perso_pos_ecran.y += jumpSpeed;
            animerPerso(p);
        }
    }
}*/

/* void saut(Personne *p, int seuil,Uint32 dt)
{
    double startjumpheight = 450.0 - seuil;
    static double jumpSpeed = 2;
    double accelerationFactor = fabs(p->acceleration1);

    if (p->up == 1)
    {
        double jumpDistance = 0.0;
        double adjustedJumpHeight = startjumpheight * (1 + accelerationFactor);

        if (p->acceleration1 > 0)
        {
            jumpDistance = 0.7 * p->acceleration1 * pow((adjustedJumpHeight / 10), 2);
        }
        else if (p->acceleration1 < 0)
        {
            jumpDistance = -0.7 * p->acceleration1 * pow((adjustedJumpHeight / 10), 2);
        }

        while (p->perso_pos_ecran.y > (450 - adjustedJumpHeight))
        {
            p->perso_pos_ecran.y -= jumpSpeed;
            p->perso_pos_ecran.x += (int)jumpDistance;
            animerPerso(p);
        }
    }
    else
    {
        while (p->perso_pos_ecran.y < 450)
        {
            p->perso_pos_ecran.y += jumpSpeed;
            animerPerso(p);
        }
    }
}*/
