#include "Game.h"

void drawPlayer (Player player, ColourStack* colourStack)
{
    assert (colourStack);

    txSetColour (RGB (colourStack->colour.red, colourStack->colour.green, colourStack->colour.blue));
    txSetFillColour (RGB (0, 0, 0));

    txRectangle (player.x - player.r, player.y - player.r, player.x + player.r, player.y + player.r);
    txLine      (player.x - player.r, player.y - player.r, player.x + player.r, player.y + player.r);
    txLine      (player.x - player.r, player.y + player.r, player.x + player.r, player.y - player.r);

    txSetFillColour (RGB (colourStack->colour.red, colourStack->colour.green, colourStack->colour.blue));

    txRectangle (player.x - player.hp/50, player.y - 2 * player.r, player.x + player.hp/50, player.y - 1.5 * player.r);

    txSetFillColour (RGB (0, 0, 0));

    if (GetAsyncKeyState (player.keys.healKey))
    {
        colourChange (&colourStack->colour.red  , &colourStack->colourSpeed.red  );
        colourChange (&colourStack->colour.green, &colourStack->colourSpeed.green);
        colourChange (&colourStack->colour.blue , &colourStack->colourSpeed.blue );
    }
}

void createWindow ()
{
    txCreateWindow (WORLD.width, WORLD.height);
    txTextCursor (false);
}

void drawCycle (Player p, Player p1, ColourStack* colourStack, ColourStack* colourStack1)
{
    txBegin ();
    txClear ();

    drawPlayer (p, colourStack);
    drawPlayer (p1, colourStack1);

    drawBullets (p);
    drawBullets (p1);

    txEnd ();
}

void drawBullets (Player player)
{
    txSetColour     (RGB (240, 112, 17));
    txSetFillColour (RGB (  0, 0,   0));

    for (int j = 0; j < BULLET_COUNT; j++)
    {
        OUT_OF_ARRAY (j, BULLET_COUNT);

        Bullet curBullet = player.bullets.bullets[j];
        if (curBullet.time <= 0) continue;

        txRectangle (curBullet.x - curBullet.r,
                     curBullet.y - curBullet.r,
                     curBullet.x + curBullet.r,
                     curBullet.y + curBullet.r);

        txLine (curBullet.x - curBullet.r,
                curBullet.y - curBullet.r,
                curBullet.x + curBullet.r,
                curBullet.y + curBullet.r);

        txLine (curBullet.x - curBullet.r,
                curBullet.y + curBullet.r,
                curBullet.x + curBullet.r,
                curBullet.y - curBullet.r);


    }
}
