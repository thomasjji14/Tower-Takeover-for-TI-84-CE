/*
* --------------------------------------
* Program Name : Tower Takeover Calculator for TI - 84 CE
* Author : Thomas Ji
* License : N / A
* Description : Takes input from the user, showing the best possible movesand the results of all possible actions in Tower Takeover, by Vex.
* --------------------------------------
*/

#include "graphics.h"

#define FONT_HEIGHT 8


void initGUI(void) {
            uint8_t i = 0;
            uint8_t j = 0;
            /* Initialize the 8bpp graphics */;
            gfx_FillScreen(0);
            gfx_SetPalette(symbols_gfx_pal, sizeof_symbols_gfx_pal, 0);

            //Fill the screen white
            gfx_FillScreen(0);

            //DRAWINGS: Creates the box surrounding everything
            gfx_SetColor(1);//Black
            gfx_Rectangle_NoClip(0,0,165,224);
            gfx_Rectangle_NoClip(1,1,163,222);
            for (i = 0; i < 16; i++) //Makes all horizontal lines
            {
                switch (i)
                {
                case 0: case 3: case 6: case 7: case 10: case 13:
                    gfx_HorizLine_NoClip(2,14+i*(13),161);
                    gfx_HorizLine_NoClip(2,15+i*(13),161);
                    break;
                default:
                    gfx_HorizLine_NoClip(41,14+i*(13),122);
                    gfx_HorizLine_NoClip(41,15+i*(13),122);
                    break;
                }

            }
            gfx_VertLine_NoClip(39,2,220);
            gfx_VertLine_NoClip(40,2,220);
            gfx_VertLine_NoClip(86,2,51);
            gfx_VertLine_NoClip(87,2,51);
            gfx_VertLine_NoClip(86,94,128);
            gfx_VertLine_NoClip(87,94,128);
            gfx_VertLine_NoClip(133,2,220);
            gfx_VertLine_NoClip(134,2,220);

            //Colored Text Boxes
            //Top boxes, team and delta box
            gfx_TransparentSprite_NoClip(neutralTeamBox, 41, 2);
            gfx_TransparentSprite_NoClip(neutralTeamBox, 88, 2);
            spriteCentered(deltaTextBox,135,2,162,13,deltaTextBox_width,deltaTextBox_height);
            //First 6 normal orange/green/purple boxes
            gfx_TransparentSprite_NoClip(orangeTextBox, 41, 16);
            gfx_TransparentSprite_NoClip(orangeTextBox, 88, 16);
            gfx_TransparentSprite_NoClip(greenTextBox, 41, 29);
            gfx_TransparentSprite_NoClip(greenTextBox, 88, 29);
            gfx_TransparentSprite_NoClip(purpleTextBox, 41, 42);
            gfx_TransparentSprite_NoClip(purpleTextBox, 88, 42);
            //The three long orange/green/purple boxes
            gfx_TransparentSprite_NoClip(orangeTextBoxLong, 41, 55);
            gfx_TransparentSprite_NoClip(greenTextBoxLong, 41, 68);
            gfx_TransparentSprite_NoClip(purpleTextBoxLong, 41, 81);
            //The red text boxes, along with the other 27 orange/green/purple boxes
            for (i = 0; i < 10; i++)
            {
                switch (i)
                {
                case 1: case 4: case 7:
                    gfx_TransparentSprite_NoClip(orangeTextBox, 41, 94+i*13);
                    gfx_TransparentSprite_NoClip(orangeTextBox, 88, 94+i*13);
                    gfx_TransparentSprite_NoClip(shortOrangeTextBox, 135, 94+i*13);
                    break;
                case 2: case 5: case 8:
                    gfx_TransparentSprite_NoClip(greenTextBox, 41, 94+i*13);
                    gfx_TransparentSprite_NoClip(greenTextBox, 88, 94+i*13);
                    gfx_TransparentSprite_NoClip(shortGreenTextBox, 135, 94+i*13);
                    break;
                case 3: case 6: case 9:
                    gfx_TransparentSprite_NoClip(purpleTextBox, 41, 94+i*13);
                    gfx_TransparentSprite_NoClip(purpleTextBox, 88, 94+i*13);
                    gfx_TransparentSprite_NoClip(shortPurpleTextBox, 135, 94+i*13);
                    break;
                default:
                    gfx_TransparentSprite_NoClip(redTextBox, 41, 94);
                    gfx_TransparentSprite_NoClip(redTextBox, 88, 94);
                    gfx_TransparentSprite_NoClip(shortRedTextBox, 135, 94);
                    break;   
                }
            }
            
            //Gray box
            gfx_SetColor(gray);
            gfx_FillRectangle_NoClip(135,16,28,76);
            
            //Black text, along with some of the sprited texts
            gfx_SetTextFGColor(1);
            printStringCentered("SCO",2,94,38,104,gfx_GetStringWidth("SCO"),FONT_HEIGHT);
            printStringCentered("Team",2,2,38,13,gfx_GetStringWidth("Team"),FONT_HEIGHT);
            printStringCentered("Ally",41,2,85,13,gfx_GetStringWidth("Ally"),FONT_HEIGHT);
            printStringCentered("Enemy",88,2,132,13,gfx_GetStringWidth("Enemy"),FONT_HEIGHT);
            gfx_TransparentSprite_NoClip(deltaXText,141,4);
            for (i = 0; i < 2; i++)
            {
                for (j = 0; j < 10; j++)
                {
                    printStringCentered("000",41+47*i,94+13*j,85+47*i,104+13*j,gfx_GetStringWidth("000"),FONT_HEIGHT);
                }
                
            }
            for (i = 0; i < 2; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    printStringCentered("00",41+47*i,16+13*j,85+47*i,26+13*j,gfx_GetStringWidth("00"),FONT_HEIGHT);
                }
                
            }
            for (i = 0; i < 3; i++)
            {
                   printStringCentered("0",41,55+13*i,132,65+13*i,gfx_GetStringWidth("0"),FONT_HEIGHT);             
            }
            for (i = 0; i < 10; i++)
            {
                spriteCentered(plusMinusZero, 135, 94+i*13,162,104+i*13,plusMinusZero_width,plusMinusZero_height);
            }

            //Side symbols
            gfx_TransparentSprite_NoClip(genericCube, 2, 16);
            gfx_TransparentSprite_NoClip(emptyTower, 2, 55);
            gfx_TransparentSprite_NoClip(stackedCube, 2, 107);
            gfx_TransparentSprite_NoClip(towerAdd, 2, 146);
            gfx_TransparentSprite_NoClip(towerRemove, 2, 185);

            //Bottom panels
            for (i = 0; i < 5; i++)
            {
                gfx_TransparentSprite_NoClip(bottomPanel, 64*i, 224);
            }
            gfx_TransparentSprite_NoClip(genericTeamColor,12,227);
            printStringCentered("Reset",194,226,253,237,gfx_GetStringWidth("Reset"),FONT_HEIGHT);
            gfx_PrintStringXY("Quit",275,228); // This really should be "printStringCentered" but for some reason this had some issues

            //Auton Boxes
            gfx_SetColor(1);//Black
            gfx_Rectangle_NoClip(168,2,14,15);
            gfx_Rectangle_NoClip(169,3,12,13);
            gfx_TransparentSprite_NoClip(genericAuton,170,4);
            gfx_TransparentSprite_NoClip(autonA,172,6);
            gfx_Rectangle_NoClip(183,2,14,15);
            gfx_Rectangle_NoClip(184,3,12,13);
            gfx_TransparentSprite_NoClip(genericAuton,185,4);
            gfx_TransparentSprite_NoClip(autonE,187,6);
            gfx_Rectangle_NoClip(176,18,14,15);
            gfx_Rectangle_NoClip(177,19,12,13);
            gfx_TransparentSprite_NoClip(greenAuton,178,20);
            gfx_TransparentSprite_NoClip(autonT,180,22);


            for (i = 0; i < 3; i++)
            {
                gfx_Rectangle_NoClip(175+47*i,92,41,54);
                gfx_Rectangle_NoClip(176+47*i,93,39,52);
                gfx_HorizLine_NoClip(177+47*i,131,37);
                gfx_HorizLine_NoClip(177+47*i,132,37);
                gfx_TransparentSprite_NoClip(recommendationScore,177+47*i,133);
                gfx_TransparentSprite_NoClip(plusMinusZero,184+47*i,135);//This really should be "printStringCentered" but for some reason this had some issues
            }
            gfx_SetColor(gold); gfx_FillRectangle_NoClip(177,94,37,37);
            gfx_SetColor(silver); gfx_FillRectangle_NoClip(224,94,37,37);
            gfx_SetColor(bronze); gfx_FillRectangle_NoClip(271,94,37,37);
        }


void printStringCentered(const char *str, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t stringWidth, uint8_t stringHeight) {
    gfx_PrintStringXY(str, x1 + ((2+x2-x1) - stringWidth) / 2, y1+((2+y2-y1) - stringHeight) / 2);
}


void spriteCentered(gfx_sprite_t *sprite, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t spriteWidth, uint8_t spriteHeight) {
    gfx_TransparentSprite_NoClip(sprite, x1 + ((2+x2-x1) - spriteWidth) / 2, y1+((2+y2-y1) - spriteHeight) / 2);
}


void debugPrintPalette(void) {
    uint8_t i;
    uint8_t j;
            for (i = 0; i < 8; i++)
            {
                for (j = 0; j < 32; j++)
                {
                    gfx_SetColor(i*32+j);
                    gfx_SetPixel(5+j,5+i);
                }
                
            }
}


void draw(teamColor col, bool updates[]) {
	//gfx_SetPalette(symbols_gfx_pal, sizeof_symbols_gfx_pal, 0);
	if (updates[UPDATE_TEAM_COLORS])
	{
		col = col == TEAM_COLOR_BLUE ? TEAM_COLOR_RED : TEAM_COLOR_BLUE;
		if (col == TEAM_COLOR_BLUE)
		{
			//gfx_TransparentSprite_NoClip(blueTeamTextBox, 41, 2);
			//gfx_TransparentSprite_NoClip(redTeamTextBox, 88, 2);
		}
		else {
			//gfx_TransparentSprite_NoClip(redTeamTextBox, 41, 2);
			//gfx_TransparentSprite_NoClip(blueTeamTextBox, 88, 2);
		}
		//printStringCentered("Ally", 41, 2, 85, 13, gfx_GetStringWidth("Ally"), FONT_HEIGHT);
		//printStringCentered("Enemy", 88, 2, 132, 13, gfx_GetStringWidth("Enemy"), FONT_HEIGHT);

	}

}
