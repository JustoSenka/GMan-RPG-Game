//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <string>
#include <fstream.h>

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
BI = new Graphics::TBitmap;
BI->LoadFromFile("Back.bmp");

MM = new Graphics::TBitmap;
MM->Width = 5000;
MM->Height = 3000;

for (int i = 1; i <= 31; i++)
   {
    Wall[i] = new Graphics::TBitmap;
    Wall[i]->LoadFromFile("Enviroment/W" + IntToStr(i) + ".bmp");
    Wall[i]->Transparent = true;
   }

Walltemp[1] = new Graphics::TBitmap;
Walltemp[1]->LoadFromFile("Enviroment/W2i.bmp");

for (int i = 1; i <= 16; i++)
   {
    PL[i] = new Graphics::TBitmap;
    PL[i]->LoadFromFile("PL/PL" + IntToStr(i) + ".bmp");
    PL[i]->Transparent = true;
   }

// Load enemies

TRead = new Graphics::TBitmap;

for (int h = 1; h <= 14; h++)
   {
    TRead->LoadFromFile("Enemies/En" + IntToStr(h) + ".bmp");

    tx = 0;
    ty = TRead->Height * 3 / 4;;

    for (int i = 1; i <= 16; i++)
       {
        En[h][i] = new Graphics::TBitmap;
        En[h][i]->Width = TRead->Width / 4;
        En[h][i]->Height = TRead->Height / 4;
        En[h][i]->Canvas->Draw(-tx, -ty, TRead);
        En[h][i]->Transparent = true;

        tx += TRead->Width / 4;
        if (i == 4){tx = 0; ty = TRead->Height / 4;}
        if (i == 8){tx = 0; ty = 0;}
        if (i == 12){tx = 0; ty = TRead->Height / 2;}
       }
   }

Back = new Graphics::TBitmap;
Back->LoadFromFile("Back.bmp");

Select = new Graphics::TBitmap;
Select->LoadFromFile("Select.bmp");

Up = new Graphics::TBitmap;
Up->LoadFromFile("Up.bmp");
Up->Transparent = true;

Menu = new Graphics::TBitmap;
Menu->LoadFromFile("Menu.bmp");

Button1Click(Sender);
}
//---------------------------------------------------------------------------





void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
valx = 0;
valy = 0;

// Right mouse button
if (RMB == 1)
   {
    valx = X - mx2 - mx;
    valy = Y - my2 - my;
   }

// move objects
mx2 += valx;
PLx += valx;
for (int i = 1; i <= ennum; i++){EnCoor[i][1] += valx; EnCoor[i][3] += valx;}
for (int i = 1; i <= wallnum; i++){wall[i][1] += valx; wall[i][3] += valx;}

my2 += valy;
PLy += valy;
for (int i = 1; i <= ennum; i++){EnCoor[i][2] += valy; EnCoor[i][4] += valy;}
for (int i = 1; i <= wallnum; i++){wall[i][2] += valy; wall[i][4] += valy;}

if (RMB == 1) DrawClick(Sender);

valx = 0;
valy = 0;

// Left mouse button
if (LMB == 1)
   {
    valx = X - mx2 - mx;
    valy = Y - my2 - my;
   }

// move one object
mx2 += valx;
wall[swall][1] += valx; wall[swall][3] += valx;
EnCoor[sen][1] += valx; EnCoor[sen][3] += valx;

my2 += valy;
wall[swall][2] += valy; wall[swall][4] += valy;
EnCoor[sen][2] += valy; EnCoor[sen][4] += valy;

if (LMB == 1) DrawClick(Sender);


// Sets new mouse coordinates
mx = X - mx2;
my = Y - my2;

Memo1->Lines->Clear();
Memo1->Lines->Add("X = " + IntToStr(mx));
Memo1->Lines->Add("Y = " + IntToStr(my));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
WindowState = wsMaximized;

Button1->Enabled = false;
Button1->Visible = false;

mx2 = 0;
my2 = 0;
swall = 0;
sen = 0;
menunum = 1;

// Sets untitled filename (Char and string)

file = "Untitled.map";

for (int i = 1; i <= file.Length(); i++)
   fileC[i] = file[i];

Form1->Caption = ("GMan RPG Map Creator --- " + file);

// PLayer position
PLx = 400;
PLy = 400;
facing = 3;

wallnum = 0;
ennum = 0;
num = 0;
         /*
// Enemy position
for (int i = 1; i <= 10; i++)
   {
    EnCoor[i][1] = 10000;
    EnCoor[i][2] = 10000;
    EnCoor[i][3] = 10001;
    EnCoor[i][4] = 10001;
    enface[i] = 1;
   }      */

// Items

for (int i = 1; i <= 12; i++)I[i].type = 4;
for (int i = 1; i <= 55; i++)I[i].icon = i;

I[1].name = "Stick";
I[1].lvl = 1;
I[1].att = 5;
I[1].demage = 10;
I[1].price = 50;

I[2].name = "Knife";
I[2].lvl = 2;
I[2].att = 8;
I[2].demage = 12;
I[2].price = 200;

I[3].name = "Spear";
I[3].lvl = 3;
I[3].att = 15;
I[3].demage = 14;
I[3].price = 400;

I[4].name = "Short Sword";
I[4].lvl = 4;
I[4].att = 16;
I[4].demage = 17;
I[4].price = 600;

I[5].name = "Axe";
I[5].lvl = 5;
I[5].att = 38;
I[5].demage = 30;
I[5].price = 3000;

I[6].name = "Fork";
I[6].lvl = 6;
I[6].att = 20;
I[6].demage = 20;
I[6].price = 1000;

I[7].name = "Knight Spear";
I[7].lvl = 7;
I[7].att = 52;
I[7].demage = 40;
I[7].price = 5000;

I[8].name = "Battle Axe";
I[8].lvl = 8;
I[8].att = 35;
I[8].demage = 28;
I[8].price = 2000;

I[9].name = "Scimitar";
I[9].lvl = 9;
I[9].att = 60;
I[9].demage = 55;
I[9].price = 9000;

I[10].name = "Long Sword";
I[10].lvl = 10;
I[10].att = 45;
I[10].demage = 40;
I[10].price = 4500;

I[11].name = "Dark Blade";
I[11].lvl = 12;
I[11].att = 95;
I[11].demage = 80;
I[11].price = 15000;

I[12].name = "Staff";
I[12].lvl = 15;
I[12].att = 500;
I[12].demage = 80;
I[12].price = 20000;


I[13].name = "Round Shield";
I[13].type = 6;
I[13].lvl = 4;
I[13].def = 6;
I[13].price = 500;

I[14].name = "Heavy Shield";
I[14].type = 6;
I[14].lvl = 7;
I[14].def = 12;
I[14].price = 1200;

I[15].name = "Kite Shield";
I[15].type = 6;
I[15].lvl = 10;
I[15].def = 18;
I[15].price = 3000;

I[16].name = "Chest Armor";
I[16].type = 5;
I[16].lvl = 3;
I[16].def = 4;
I[16].price = 350;

I[17].name = "Ancient Chest Armor";
I[17].type = 5;
I[17].lvl = 6;
I[17].def = 8;
I[17].price = 800;

I[18].name = "Plate Body";
I[18].type = 5;
I[18].lvl = 9;
I[18].def = 12;
I[18].price = 1900;

I[19].name = "Leather Boots";
I[19].type = 9;
I[19].lvl = 6;
I[19].def = 3;
I[19].price = 800;

I[20].name = "Iron Boots";
I[20].type = 9;
I[20].lvl = 10;
I[20].def = 7;
I[20].price = 2400;

I[21].name = "Leather Gloves";
I[21].type = 7;
I[21].lvl = 5;
I[21].def = 3;
I[21].price = 700;

I[22].name = "Iron Gloves";
I[22].type = 7;
I[22].lvl = 9;
I[22].def = 7;
I[22].price = 2200;

I[23].name = "Helmet";
I[23].type = 2;
I[23].lvl = 4;
I[23].def = 5;
I[23].price = 1200;

I[24].name = "Horseman Helmet";
I[24].type = 2;
I[24].lvl = 8;
I[24].def = 10;
I[24].price = 2800;

I[25].name = "Ring";
I[25].type = 1;
I[25].lvl = 3;
I[25].hp = 40;
I[25].mp = 20;
I[25].price = 600;

I[26].name = "Ring";
I[26].type = 1;
I[26].lvl = 6;
I[26].hp = 55;
I[26].sta = 26;
I[26].price = 1500;

I[27].name = "Ring";
I[27].type = 1;
I[27].lvl = 9;
I[27].mp = 40;
I[27].sta = 40;
I[27].price = 3000;

I[28].name = "Ring";
I[28].type = 1;
I[28].lvl = 5;
I[28].def = 5;
I[28].att = 10;
I[28].price = 2450;

I[29].name = "Ring";
I[29].type = 1;
I[29].lvl = 8;
I[29].def = 15;
I[29].att = 5;
I[29].price = 5600;

I[30].name = "Ring";
I[30].type = 1;
I[30].lvl = 13;
I[30].def = 10;
I[30].att = 40;
I[30].price = 9500;

I[31].name = "Amulet";
I[31].type = 3;
I[31].lvl = 3;
I[31].hp = 45;
I[31].price = 1100;

I[32].name = "Amulet";
I[32].type = 3;
I[32].lvl = 5;
I[32].mp = 25;
I[32].price = 1800;

I[33].name = "Amulet";
I[33].type = 3;
I[33].lvl = 8;
I[33].sta = 38;
I[33].price = 3300;

I[34].name = "Amulet";
I[34].type = 3;
I[34].lvl = 11;
I[34].def = 15;
I[34].att = 35;
I[34].price = 11400;

I[35].name = "Health Potion";
I[35].type = 10;
I[35].hp = 120;
I[35].price = 70;

I[36].name = "Health Potion";
I[36].type = 10;
I[36].hp = 240;
I[36].price = 180;

I[37].name = "Mana Potion";
I[37].type = 10;
I[37].mp = 60;
I[37].price = 70;

I[38].name = "Mana Potion";
I[38].type = 10;
I[38].mp = 120;
I[38].price = 180;

I[39].name = "Stamina Potion";
I[39].type = 10;
I[39].sta = 100;
I[39].price = 100;

I[40].name = "Leaf";
I[40].price = 35;
I[41].name = "Mana Herb";
I[41].price = 100;
I[42].name = "Health Herb";
I[42].price = 70;
I[43].name = "Flower";
I[43].price = 200;
I[44].name = "Death Flower";
I[44].price = 350;
I[45].name = "Roots";
I[45].price = 400;
I[46].name = "Skull";
I[46].price = 50;
I[47].name = "Meat";
I[47].price = 100;
I[48].name = "Feather";
I[48].price = 220;
I[49].name = "Hide";
I[49].price = 140;
I[50].name = "Shell";
I[50].price = 350;
I[51].name = "Horn";
I[51].price = 600;
I[52].name = "Gold Bars";
I[52].price = 200;
I[53].name = "Ruby";
I[53].price = 1000;
I[54].name = "Saphire";
I[54].price = 1650;
I[55].name = "Emerald";
I[55].price = 2800;

itemnum = 55;


// All Enemy types

for (int i = 1; i <= 14; i++)
    E[i].icon = i;

E[1].hpmax = 60;
E[1].speed = 22;
E[1].sight = 300;
E[1].att = 30;
E[1].def = 10;
E[1].demage = 10;
E[1].exp = 10;
E[1].gold = 5;
E[1].idropc = 3;
E[1].item[1] = 150;
E[1].item[2] = 180;
E[1].item[46] = 70;
E[1].name = "Goblin";

E[2].hpmax = 100;
E[2].speed = 16;
E[2].sight = 200;
E[2].att = 40;
E[2].def = 18;
E[2].demage = 13;
E[2].exp = 15;
E[2].gold = 7;
E[2].idropc = 3;
E[2].item[25] = 350;
E[2].item[26] = 450;
E[2].item[27] = 600;
E[2].name = "Zombie";

E[3].hpmax = 110;
E[3].speed = 23;
E[3].sight = 280;
E[3].att = 30;
E[3].def = 12;
E[3].demage = 16;
E[3].exp = 20;
E[3].gold = 13;
E[3].idropc = 3;
E[3].item[4] = 380;
E[3].item[13] = 280;
E[3].item[52] = 100;
E[3].name = "Skeleton";

E[4].hpmax = 80;
E[4].speed = 28;
E[4].sight = 380;
E[4].att = 55;
E[4].def = 5;
E[4].demage = 25;
E[4].exp = 30;
E[4].gold = 10;
E[4].idropc = 3;
E[4].item[2] = 180;
E[4].item[46] = 60;
E[4].item[53] = 500;
E[4].name = "Goblin Thief";

E[5].hpmax = 150;
E[5].speed = 18;
E[5].sight = 240;
E[5].att = 50;
E[5].def = 28;
E[5].demage = 20;
E[5].exp = 46;
E[5].gold = 5;
E[5].idropc = 2;
E[5].item[47] = 50;
E[5].item[50] = 180;
E[5].name = "Crab";

E[6].hpmax = 160;
E[6].speed = 26;
E[6].sight = 320;
E[6].att = 40;
E[6].def = 20;
E[6].demage = 30;
E[6].exp = 65;
E[6].gold = 15;
E[6].idropc = 4;
E[6].item[31] = 300;
E[6].item[32] = 350;
E[6].item[33] = 500;
E[6].item[46] = 25;
E[6].name = "Wolf";

E[7].hpmax = 190;
E[7].speed = 20;
E[7].sight = 280;
E[7].att = 35;
E[7].def = 20;
E[7].demage = 38;
E[7].exp = 85;
E[7].gold = 30;
E[7].idropc = 4;
E[7].item[35] = 180;
E[7].item[36] = 300;
E[7].item[37] = 180;
E[7].item[38] = 300;
E[7].name = "Snake";

E[8].hpmax = 240;
E[8].speed = 18;
E[8].sight = 300;
E[8].att = 60;
E[8].def = 45;
E[8].demage = 40;
E[8].exp = 95;
E[8].gold = 40;
E[8].idropc = 2;
E[8].item[47] = 40;
E[8].item[50] = 90;
E[8].name = "Octopus";

E[9].hpmax = 300;
E[9].speed = 25;
E[9].sight = 400;
E[9].att = 65;
E[9].def = 45;
E[9].demage = 45;
E[9].exp = 125;
E[9].gold = 50;
E[9].idropc = 4;
E[9].item[28] = 350;
E[9].item[29] = 400;
E[9].item[30] = 500;
E[9].item[54] = 300;
E[9].name = "Hell Guard";

E[10].hpmax = 350;
E[10].speed = 30;
E[10].sight = 460;
E[10].att = 120;
E[10].def = 35;
E[10].demage = 50;
E[10].exp = 155;
E[10].gold = 40;
E[10].idropc = 3;
E[10].item[10] = 350;
E[10].item[17] = 250;
E[10].item[53] = 160;
E[10].name = "Vampire";

E[11].hpmax = 500;
E[11].speed = 22;
E[11].sight = 380;
E[11].att = 80;
E[11].def = 60;
E[11].demage = 70;
E[11].exp = 200;
E[11].gold = 60;
E[11].idropc = 3;
E[11].item[6] = 180;
E[11].item[51] = 60;
E[11].item[55] = 420;
E[11].name = "Devil";

E[12].hpmax = 600;
E[12].speed = 24;
E[12].sight = 340;
E[12].att = 80;
E[12].def = 50;
E[12].demage = 80;
E[12].exp = 260;
E[12].gold = 120;
E[12].idropc = 7;
E[12].item[10] = 450;
E[12].item[16] = 280;
E[12].item[18] = 400;
E[12].item[20] = 360;
E[12].item[22] = 380;
E[12].item[23] = 350;
E[12].item[24] = 500;
E[12].name = "Goblin Warrior";

E[13].hpmax = 1000;
E[13].speed = 18;
E[13].sight = 300;
E[13].att = 100;
E[13].def = 40;
E[13].demage = 100;
E[13].exp = 350;
E[13].gold = 140;
E[13].idropc = 3;
E[13].item[5] = 200;
E[13].item[8] = 280;
E[13].item[34] = 430;
E[13].name = "Troll";

E[14].hpmax = 4000;
E[14].speed = 30;
E[14].sight = 360;
E[14].att = 250;
E[14].def = 80;
E[14].demage = 125;
E[14].exp = 1500;
E[14].gold = 2000;
E[14].idropc = 1;
E[14].item[12] = 9;
E[14].name = "Witch";

entypenum = 14;


//LoadClick(Sender);
DrawClick(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
mx = X - mx2;
my = Y - my2;

switch (Button)
  {
   case VK_RBUTTON:
    LMB = 1;
   break;

   case VK_LBUTTON:
    RMB = 1;
   break;
  }
if (RMB == 0)LMB = 1;

// Unselect sType & senType

if (X < 700 && Y > Form1->ClientHeight - 200) {sType = 0; senType = 0;}

// Drawing new walls on map

if (RMB != 1 && sType > 0)
 {
  wallnum++;
  wall[wallnum][5] = sType;
  swall = wallnum;

if (sType == 1) // Horizontal wall
   {
    wall[wallnum][1] = X - 25; wall[wallnum][3] = X + 24;
    wall[wallnum][2] = Y - 8; wall[wallnum][4] = Y + 8;
   }
if (sType == 2) // Vertical wall
   {
    wall[wallnum][1] = X - 6; wall[wallnum][3] = X + 6;
    wall[wallnum][2] = Y - 24; wall[wallnum][4] = Y + 28;
   }
if (sType == 3) // Tent
   {
    wall[wallnum][1] = X - 72; wall[wallnum][3] = X + 72;
    wall[wallnum][2] = Y - 55; wall[wallnum][4] = Y + 55;
   }
if (sType == 4 || sType == 5 || sType == 8 || sType == 9 || sType >= 15 & sType <= 20 || sType == 31) //Rocks, stumps, fire pit, brushes
   {
    wall[wallnum][1] = X - 16; wall[wallnum][3] = X + 16;
    wall[wallnum][2] = Y - 16; wall[wallnum][4] = Y + 17;
   }
if (sType ==6 || sType == 7) // Colons
   {
    wall[wallnum][1] = X - 16; wall[wallnum][3] = X + 16;
    wall[wallnum][2] = Y - 13; wall[wallnum][4] = Y + 13;
   }
if (sType == 10) // Tree with no leaves
   {
    wall[wallnum][1] = X - 34; wall[wallnum][3] = X + 34;
    wall[wallnum][2] = Y - 20; wall[wallnum][4] = Y + 20;
   }
if (sType >= 11 && sType <= 12) // Tree with leaves
   {
    wall[wallnum][1] = X - 20; wall[wallnum][3] = X + 20;
    wall[wallnum][2] = Y - 15; wall[wallnum][4] = Y + 12;
   }
if (sType == 13) // Well
   {
    wall[wallnum][1] = X - 24; wall[wallnum][3] = X + 24;
    wall[wallnum][2] = Y - 15; wall[wallnum][4] = Y + 15;
   }
if (sType == 14) // Fountain
   {
    wall[wallnum][1] = X - 31; wall[wallnum][3] = X + 31;
    wall[wallnum][2] = Y - 25; wall[wallnum][4] = Y + 25;
   }
if (sType == 21) // Big grave
   {
    wall[wallnum][1] = X - 32; wall[wallnum][3] = X + 31;
    wall[wallnum][2] = Y - 16; wall[wallnum][4] = Y + 16;
   }
if (sType == 22) // Forest Temple
   {
    wall[wallnum][1] = X - 46; wall[wallnum][3] = X + 46;
    wall[wallnum][2] = Y - 22; wall[wallnum][4] = Y + 23;
   }
if (sType == 23) // Horizontal log
   {
    wall[wallnum][1] = X - 31; wall[wallnum][3] = X + 32;
    wall[wallnum][2] = Y - 12; wall[wallnum][4] = Y + 12;
   }
if (sType == 24) // Vertical log
   {
    wall[wallnum][1] = X - 14; wall[wallnum][3] = X + 15;
    wall[wallnum][2] = Y - 27; wall[wallnum][4] = Y + 28;
   }
if (sType == 25 || sType == 26) // Forest trees
   {
    wall[wallnum][1] = X - 33; wall[wallnum][3] = X + 32;
    wall[wallnum][2] = Y - 17; wall[wallnum][4] = Y + 17;
   }
if (sType == 27) // Magic staff
   {
    wall[wallnum][1] = X - 14; wall[wallnum][3] = X + 14;
    wall[wallnum][2] = Y - 12; wall[wallnum][4] = Y + 13;
   }
if (sType == 28) // Grave
   {
    wall[wallnum][1] = X - 17; wall[wallnum][3] = X + 17;
    wall[wallnum][2] = Y - 20; wall[wallnum][4] = Y + 20;
   }
if (sType == 29) // Fountain with anim
   {
    wall[wallnum][1] = X - 45; wall[wallnum][3] = X + 46;
    wall[wallnum][2] = Y - 32; wall[wallnum][4] = Y + 32;
   }
if (sType == 30) // Fire
   {
    wall[wallnum][1] = X - 12; wall[wallnum][3] = X + 13;
    wall[wallnum][2] = Y - 7; wall[wallnum][4] = Y + 8;
   }
 }

// Drawing new enemies on map

if (RMB != 1 && senType > 0)
 {
  ennum += 1;
  EnCoor[ennum][1] = X - En[senType][9]->Width / 2;
  EnCoor[ennum][2] = Y;
  EnCoor[ennum][3] = X + En[senType][9]->Width / 2;
  EnCoor[ennum][4] = Y + 25;
  EnCoor[ennum][5] = senType;
 }


// Selecting objects at map

if (X < 660 || X > 700 || Y > Form1->ClientHeight || Y < Form1->ClientHeight - 60)
   {
    swall = 0;   // Unsellect wall
    sen = 0;     //         en
   }

if (sType == 0 && senType == 0)
  if (X < 660 || X > 700 || Y > Form1->ClientHeight || Y < Form1->ClientHeight - 60) // if pressed + and -
   {
    for (int i = 1; i <= wallnum; i++) // walls
        if (X > wall[i][1] && X < wall[i][3] && Y > wall[i][2] && Y < wall[i][4])
            {swall = i; sen = 0;}

    for (int i = 1; i <= ennum; i++) // enemies
        if (X > EnCoor[i][1] && X < EnCoor[i][3] && Y > EnCoor[i][2] && Y < EnCoor[i][4])
            {swall = 0; sen = i;}
   }

// + and - with walls

if (menunum != 0)
if (X > 660 && X < 700 && Y < Form1->ClientHeight - 30 && Y > Form1->ClientHeight - 60)
   {
    if (wall[swall][5] == 1) wall[swall][3] += 49;
    if (wall[swall][5] == 2) wall[swall][4] += 48;
    if (swall == 0)if (menunum < 10)menunum++;
   }
if (menunum != 0)
if (X > 660 && X < 700 && Y < Form1->ClientHeight && Y > Form1->ClientHeight - 30)
   {
    if (wall[swall][5] == 1 && wall[swall][3] - wall[swall][1] > 49) wall[swall][3] -= 49;
    if (wall[swall][5] == 2 && wall[swall][4] - wall[swall][2] > 48 + 32) wall[swall][4] -= 48;
    if (swall == 0)if (menunum > 0)menunum--;
   }

// Selecting sType

for (int i = 1; i <= 31; i++)
    if (X > menuxy[i][1] && X < menuxy[i][3] && Y > menuxy[i][2] && Y < menuxy[i][4] && menunum == menuxy[i][5])
        sType = i;

// Selecting senType

for (int i = 1; i <= 14; i++)
    if (X > enmenuxy[i][1] && X < enmenuxy[i][3] && Y > enmenuxy[i][2] && Y < enmenuxy[i][4] && menunum == 1)
        senType = i;


DrawClick(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{

switch (Button)
  {
   case VK_RBUTTON:
    LMB = 0;
   break;
   case VK_LBUTTON:
    RMB = 0;
   break;
  }

LMB = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
switch (Key)
 {
  case VK_SHIFT:
     shift = 1;
  break;

  case 'M':
     map++;
     if (map == 3)map = 0;
  break;

  case VK_UP:
     if (menunum < 10)menunum++;
  break;

  case VK_DOWN:
     if (menunum > 0)menunum--;
  break;

  case VK_SPACE:
     space = 1;
     swall = 0;
     sType = 0;
     senType = 0;
  break;

  case 'W':
     wasd[1] = 1;
     if (swall != 0){wall[swall][2]--; wall[swall][4]--;}
  break;
  case 'A':
     wasd[2] = 1;
     if (swall != 0){wall[swall][1]--; wall[swall][3]--;}
  break;
  case 'S':
     wasd[3] = 1;
     if (swall != 0){wall[swall][2]++; wall[swall][4]++;}
  break;
  case 'D':
     wasd[4] = 1;
     if (swall != 0){wall[swall][1]++; wall[swall][3]++;}
  break;
 }

DrawClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
switch (Key)
 {
  case VK_SHIFT:
     shift = 0;
  break;
  
  case VK_SPACE:
     space = 0;
  break;

  case 'W':
     wasd[1] = 0;
     if (valy < 0)valy = 0;
  break;
  case 'A':
     wasd[2] = 0;
     if (valx < 0)valx = 0;
  break;
  case 'S':
     wasd[3] = 0;
     if (valy > 0)valy = 0;
  break;
  case 'D':
     wasd[4] = 0;
     if (valx > 0)valx = 0;
  break;
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DrawClick(TObject *Sender)
{
BI->Canvas->Draw(0, 0, Back);

for (int g = -20; g <= Form1->ClientHeight + 800; g += 2)
{

// Enemies
for(int i = 1; i <= ennum; i++) if (EnCoor[i][4] + 8 <= g && EnCoor[i][4] + 8 > g - 2 && EnCoor[i][1] > -200 && EnCoor[i][1] < Form1->ClientWidth + 200)
    BI->Canvas->Draw(EnCoor[i][1], EnCoor[i][2] - En[EnCoor[i][5]][9]->Height + 25, En[EnCoor[i][5]][9]);


// You
if (PLy + 42 <= g && PLy + 42 > g - 2)
    BI->Canvas->Draw(PLx, PLy, PL[9]);

// Walls

for(int i = 1; i <= wallnum; i++)
if (wall[i][4] <= g && wall[i][4] > g - 2 && wall[i][3] > -200 && wall[i][1] < Form1->ClientWidth + 200) // For all walls
   {
    if (wall[i][5] == 1)  // 1 Fence
        for (int j = wall[i][1]; j < wall[i][3]; j += 49)BI->Canvas->Draw(j, wall[i][2] - 25, Wall[wall[i][5]]);

    if (wall[i][5] == 2)  // 2 & 3 Fence
       {
        for (int j = wall[i][2]; j < wall[i][4] - 34; j += 48)BI->Canvas->Draw(wall[i][1], j - 25, Wall[wall[i][5]]);
        BI->Canvas->Draw(wall[i][1], wall[i][4] - 29, Walltemp[1]);
       }
    if (wall[i][5] == 3)      // Tent
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 50, Wall[wall[i][5]]);
                                    // Rocks
    if (wall[i][5] >= 4 & wall[i][5] <= 5 || wall[i][5] >= 8 & wall[i][5] <= 9 || wall[i][5] >= 15 & wall[i][5] <= 20)  // Rocks, stumps, fire pit
        BI->Canvas->Draw(wall[i][1], wall[i][2], Wall[wall[i][5]]);

    if (wall[i][5] == 6 || wall[i][5] == 7)  // Colons
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 60, Wall[wall[i][5]]);

    if (wall[i][5] == 10)  // Tree with no leaves
        BI->Canvas->Draw(wall[i][1] - 30, wall[i][2] - 90, Wall[wall[i][5]]);

    if (wall[i][5] == 11)  // Tree first
        BI->Canvas->Draw(wall[i][1] - 40, wall[i][2] - 130, Wall[wall[i][5]]);

    if (wall[i][5] == 12)  // Tree second
        BI->Canvas->Draw(wall[i][1] - 44, wall[i][2] - 135, Wall[wall[i][5]]);

    if (wall[i][5] == 13)  // Well
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 15, Wall[wall[i][5]]);

    if (wall[i][5] == 14)  // Fountain
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 13, Wall[wall[i][5]]);

    if (wall[i][5] == 21)  // Big grave
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 35, Wall[wall[i][5]]);

    if (wall[i][5] == 22)  // Forest Temple
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 52, Wall[wall[i][5]]);

    if (wall[i][5] == 23 || wall[i][5] == 24)  // Logs
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 7, Wall[wall[i][5]]);

    if (wall[i][5] == 25 || wall[i][5] == 26)  // Forest trees
        BI->Canvas->Draw(wall[i][1] - 60, wall[i][2] - 120, Wall[wall[i][5]]);

    if (wall[i][5] == 27)  // Magic staff
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 35, Wall[wall[i][5]]);

    if (wall[i][5] == 28)  // Grave
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 26, Wall[wall[i][5]]);

    if (wall[i][5] == 29)  // Fountain with anim
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 24, Wall[wall[i][5]]);

    if (wall[i][5] == 30)  // Fire with anim
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 36, Wall[wall[i][5]]);

    if (wall[i][5] == 31)  // Fire pit with anim
        BI->Canvas->Draw(wall[i][1], wall[i][2], Wall[wall[i][5]]);

   }
}

// MiniMap

if (map > 0)
   {
    BI->Canvas->Pen->Width = 2;

    Rect.Top = 0;
    Rect.Right = Form1->ClientWidth;
    if (map == 1)
       {
        Rect.Left = Form1->ClientWidth - 350;
        Rect.Bottom = 200;
        MM->Width = 3500;
        MM->Height = 2000;
        BI->Canvas->Rectangle(Form1->ClientWidth - 352, -2, Form1->ClientWidth + 2, 202);
       }
    if (map == 2)
       {
        Rect.Left = Form1->ClientWidth - 500;
        Rect.Bottom = 300;
        MM->Width = 5000;
        MM->Height = 3000;
        BI->Canvas->Rectangle(Form1->ClientWidth - 502, -2, Form1->ClientWidth + 2, 302);
       }

MM->Canvas->Draw(0, 0, Back);
MM->Canvas->Draw(2500, 0, Back);
MM->Canvas->Draw(0, 1500, Back);
MM->Canvas->Draw(2500, 1500, Back);

// Enemies  MM
for(int i = 1; i <= ennum; i++)
   {
    MM->Canvas->Draw(EnCoor[i][1] + (MM->Width / 2) - 500, EnCoor[i][2] - En[EnCoor[i][5]][9]->Height + 25 + (MM->Height / 2) - 350, En[EnCoor[i][5]][9]);
   }

// You MM
MM->Canvas->Draw(PLx + (MM->Width / 2) - 500, PLy + (MM->Height / 2) - 350, PL[9]);

// Walls MM

for(int i = 1; i <= wallnum; i++) // For all walls
   {
    if (wall[i][5] == 1)  // 1 Fence
        for (int j = wall[i][1]; j < wall[i][3]; j += 49)MM->Canvas->Draw(j + (MM->Width / 2) - 500, wall[i][2] - 25 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 2)  // 2 & 3 Fence
       {
        for (int j = wall[i][2]; j < wall[i][4] - 34; j += 48)MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, j - 25 + (MM->Height / 2) - 350, Wall[wall[i][5]]);
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][4] - 29 + (MM->Height / 2) - 350, Walltemp[1]);
       }
    if (wall[i][5] == 3)      // Tent
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 50 + (MM->Height / 2) - 350, Wall[wall[i][5]]);
                                    // Rocks
    if (wall[i][5] >= 4 & wall[i][5] <= 5 || wall[i][5] >= 8 & wall[i][5] <= 9 || wall[i][5] >= 15 & wall[i][5] <= 20)  // Rocks, stumps, fire pit
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 6 || wall[i][5] == 7)  // Colons
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 60 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 10)  // Tree with no leaves
        MM->Canvas->Draw(wall[i][1] - 30 + (MM->Width / 2) - 500, wall[i][2] - 90 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 11)  // Tree first
        MM->Canvas->Draw(wall[i][1] - 40 + (MM->Width / 2) - 500, wall[i][2] - 130 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 12)  // Tree second
        MM->Canvas->Draw(wall[i][1] - 44 + (MM->Width / 2) - 500, wall[i][2] - 135 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 13)  // Well
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 15 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 14)  // Fountain
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 13 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 21)  // Big grave
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 35 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 22)  // Forest Temple
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 52 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 23 || wall[i][5] == 24)  // Logs
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 7 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 25 || wall[i][5] == 26)  // Forest trees
        MM->Canvas->Draw(wall[i][1] - 60 + (MM->Width / 2) - 500, wall[i][2] - 120 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 27)  // Magic staff
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 35 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 28)  // Grave
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 26 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 29)  // Fountain with anim
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 24 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 30)  // Fire with anim
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] - 36 + (MM->Height / 2) - 350, Wall[wall[i][5]]);

    if (wall[i][5] == 31)  // Fire pit with anim
        MM->Canvas->Draw(wall[i][1] + (MM->Width / 2) - 500, wall[i][2] + (MM->Height / 2) - 350, Wall[wall[i][5]]);

   }

    BI->Canvas->StretchDraw(Rect, MM);
   } // End of MiniMap


// Select & menu

if (menunum != 0)
   {
    BI->Canvas->Draw(0, Form1->ClientHeight - 200, Menu);

    // Walls

    for (int i = 1; i <= 31; i++)
       {
        if (menunum == menuxy[i][5])BI->Canvas->Draw(menuxy[i][1], menuxy[i][2], Wall[i]);
        if (sType == i) BI->Canvas->Draw((menuxy[i][1] + menuxy[i][3]) / 2, (menuxy[i][2] + menuxy[i][4]) / 2, Select);
       }

    // Enemies

    if (menunum == 1)
        for (int i = 1; i <= 14; i++)
           {
            BI->Canvas->Draw(enmenuxy[i][1], enmenuxy[i][2], En[i][9]);
            if (senType == i) BI->Canvas->Draw((enmenuxy[i][1] + enmenuxy[i][3]) / 2, (enmenuxy[i][2] + enmenuxy[i][4]) / 2, Select);
           }

    if (menunum == 2)BI->Canvas->Draw(110, Form1->ClientHeight - 36, Walltemp[1]);
    BI->Canvas->Draw(660, Form1->ClientHeight - 60, Up);

    if (swall != 0) BI->Canvas->Draw(wall[swall][1] / 2 + wall[swall][3] / 2, wall[swall][2] / 2 + wall[swall][4] / 2, Select);
    if (sen != 0) BI->Canvas->Draw(EnCoor[sen][1] / 2 + EnCoor[sen][3] / 2, EnCoor[sen][2] / 2 + EnCoor[sen][4] / 2, Select);
   }

Draw->Enabled = false;
Draw->Enabled = true;

//Canvas->Draw(-1000,-800,BI);
Canvas->Draw(0,0,BI);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::SaveClick(TObject *Sender)
{

ofstream cr(fileC);
cr << PLx - PLx + 500 << ";" << PLy - PLy + 400 << ";" << endl << wallnum << endl;

// Walls

for (int i = 1; i <= wallnum; i++)
   {
    cr << wall[i][1] - PLx + 500 << ";" << wall[i][2] - PLy + 400 << ";" << wall[i][3] - PLx + 500 << ";" << wall[i][4] - PLy + 400 << ";" << wall[i][5] << ";" << endl;
   }

// Enemies

cr << ennum << endl;
for (int i = 1; i <= ennum; i++)
   {
    cr << EnCoor[i][1] - PLx + 500 << ";" << EnCoor[i][2] - PLy + 400 << ";" << EnCoor[i][3] - PLx + 500 << ";" << EnCoor[i][4] - PLy + 400 << ";" << EnCoor[i][5] << ";" << endl;
   }

// Items

cr << itemnum << endl;
for (int i = 1; i <= itemnum; i++)
   {
    // Converting AnsiString to Char

    char *a=new char[I[i].name.Length()+1];
    a[I[i].name.Length()]=0;
    memcpy(a,I[i].name.c_str(),I[i].name.Length());

    // Continue writing

    cr.write(a,I[i].name.Length());
    cr << endl << I[i].lvl << ";" << I[i].att << ";" << I[i].def << ";" << I[i].demage << ";" << I[i].hp << ";"
     << I[i].mp << ";" << I[i].sta << ";" << I[i].price << ";" << I[i].type << ";" << I[i].icon << ";" << endl;
   }

// Enemy stats

cr << entypenum << endl;
for (int i = 1; i <= entypenum; i++)
   {
    // Converting AnsiString to Char

    char *a=new char[E[i].name.Length()+1];
    a[E[i].name.Length()]=0;
    memcpy(a,E[i].name.c_str(),E[i].name.Length());

    // Continue writing

    cr.write(a,E[i].name.Length());
    cr << endl << E[i].hpmax << ";" << E[i].speed << ";" << E[i].sight << ";" << E[i].att << ";" << E[i].def << ";" << E[i].demage << ";"
     << E[i].exp << ";" << E[i].gold << ";" << E[i].icon << ";" << E[i].idropc << ";" << endl;

    for (int h = 1; h <= itemnum; h++)
        if (E[i].item[h] != 0) cr << h << ";" << E[i].item[h] << ";" << endl;
   }




cr.close();

Save->Enabled = false;
Save->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LoadClick(TObject *Sender)
{

if (OpenDialog1->Execute())
{

// Converting AnsiString to Char

char *a=new char[OpenDialog1->FileName.Length()+1];
a[OpenDialog1->FileName.Length()]=0;
memcpy(a,OpenDialog1->FileName.c_str(),OpenDialog1->FileName.Length());

// Setting permament variable for file name (char and string)

for (int i = 0; i < 240; i++)
    fileC[i] = a[i];

file = fileC;


Form1->Caption = ("GMan RPG Map Creator --- " + file);

mx2 = 0;
my2 = 0;

//  ifstream fd("Map1.map");
ifstream fd(fileC);

// Reads your coord

read4 = "";
num = 0;
fd.getline(read, 50);
for (int i = 1; i <= 2; i++)
   {
    for (int j = 0; j < 20; j++)
       {
        read3 = read[num];
        num++;
        if (read3 != ";") read4 = read4 + read3;
        else if (i == 1){PLx = StrToInt(read4); read4 = ""; j = 50;}
        else if (i == 2){PLy = StrToInt(read4); read4 = ""; j = 50;}
       }
   }


// Reads and converts to integer wallnum

fd.getline(read, 50);
read3 = read;
wallnum = StrToInt(read3);


// Reads all fences

for (int h = 1; h <= wallnum; h++)
  {
   read4 = "";
   num = 0;
   fd.getline(read, 50);
   for (int i = 1; i <= 5; i++)
      {
       for (int j = 0; j < 20; j++)
          {
           read3 = read[num];
           num++;
           if (read3 != ";") read4 = read4 + read3;
           else {wall[h][i] = StrToInt(read4); read4 = ""; j = 50;}
          }
      }
  }


// Reads and converts to integer ennum

fd.getline(read, 50);
read3 = read;
ennum = StrToInt(read3);


// Reads all enemies

for (int h = 1; h <= ennum; h++)
  {
   read4 = "";
   num = 0;
   fd.getline(read, 50);
   for (int i = 1; i <= 5; i++)
      {
       for (int j = 0; j < 20; j++)
          {
           read3 = read[num];
           num++;
           if (read3 != ";") read4 = read4 + read3;
           else {EnCoor[h][i] = StrToInt(read4); read4 = ""; j = 50;}
          }
      }
  }


// Reads and converts to integer itemnum

fd.getline(read, 50);
read3 = read;
itemnum = StrToInt(read3);


// Reads all items

for (int h = 1; h <= itemnum; h++)
  {
   fd.getline(read, 50);
   I[h].name = read;                // Reads the name

   read4 = "";
   num = 0;
   fd.getline(read, 100);
   for (int i = 1; i <= 10; i++)
      {
       for (int j = 0; j < 10; j++)
          {
           read3 = read[num];
           num++;
           if (read3 != ";") read4 = read4 + read3;
           else
              {
               if (i == 1) I[h].lvl = StrToInt(read4);
               if (i == 2) I[h].att = StrToInt(read4);
               if (i == 3) I[h].def = StrToInt(read4);
               if (i == 4) I[h].demage = StrToInt(read4);
               if (i == 5) I[h].hp = StrToInt(read4);
               if (i == 6) I[h].mp = StrToInt(read4);
               if (i == 7) I[h].sta = StrToInt(read4);
               if (i == 8) I[h].price = StrToInt(read4);
               if (i == 9) I[h].type = StrToInt(read4);
               if (i == 10) I[h].icon = StrToInt(read4);
               read4 = "";
               j = 50;
              }
          }
      }
  }


// Reads and converts to integer entypenum

fd.getline(read, 50);
read3 = read;
entypenum = StrToInt(read3);

// Reads enemy stats

int tempDC;

for (int h = 1; h <= entypenum; h++)
  {
   fd.getline(read, 50);
   E[h].name = read;                // Reads the name

   read4 = "";
   num = 0;
   fd.getline(read, 100);
   for (int i = 1; i <= 10; i++)
      {
       for (int j = 0; j < 10; j++)
          {
           read3 = read[num];
           num++;
           if (read3 != ";") read4 = read4 + read3;
           else
              {
               if (i == 1) E[h].hpmax = StrToInt(read4);
               if (i == 2) E[h].speed = StrToInt(read4);
               if (i == 3) E[h].sight = StrToInt(read4);
               if (i == 4) E[h].att = StrToInt(read4);
               if (i == 5) E[h].def = StrToInt(read4);
               if (i == 6) E[h].demage = StrToInt(read4);
               if (i == 7) E[h].exp = StrToInt(read4);
               if (i == 8) E[h].gold = StrToInt(read4);
               if (i == 9) E[h].icon = StrToInt(read4);
               if (i == 10) E[h].idropc = StrToInt(read4);
               read4 = "";
               j = 50;
              }
          }
      }

   // Erases default data of E[..].item[..]

   for (int i = 1; i <= itemnum; i++) E[h].item[i] = 0;

   // Reads enemy item drops E[..].item[..]

   for (int i = 1; i <= E[h].idropc; i++)
      {
       read4 = "";
       num = 0;
       fd.getline(read, 100);
       for (int j = 0; j < 10; j++)
          {
           read3 = read[num];
           num++;
           if (read3 != ";") read4 = read4 + read3;
           else {tempDC = StrToInt(read4); j = 50; read4 = "";}
          }
       for (int j = 0; j < 10; j++)
          {
           read3 = read[num];
           num++;
           if (read3 != ";") read4 = read4 + read3;
           else {E[h].item[tempDC] = StrToInt(read4); j = 50; read4 = "";}
          }
      }
  }

fd.close();

Load->Enabled = false;
Load->Enabled = true;

}
DrawClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if (swall != 0)
   {
    Save->Enabled = false;
    Load->Enabled = false;
    Draw->Enabled = false;
   } else
   {
    Save->Enabled = true;
    Load->Enabled = true;
    Draw->Enabled = true;
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Exit1Click(TObject *Sender)
{
Close();        
}
//---------------------------------------------------------------------------









void __fastcall TForm1::Undo1Click(TObject *Sender)
{
wall[wallnum][1] = 0;
wall[wallnum][2] = 0;
wall[wallnum][3] = 0;
wall[wallnum][4] = 0;
wall[wallnum][5] = 0;
wallnum--;
DrawClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Delete1Click(TObject *Sender)
{
// Delete wall

if (swall != 0 && swall != wallnum)
   {
    for (int i = swall; i < wallnum; i++)
        for (int j = 1; j <= 5; j++)
            wall[i][j] = wall[i + 1][j];
    wallnum--;
   }
else if (swall == wallnum)
   Undo1Click(Sender);

// Delete enemy

if (sen != 0 && sen != ennum)
   {
    for (int i = sen; i < ennum; i++)
        for (int j = 1; j <= 5; j++)
            EnCoor[i][j] = EnCoor[i + 1][j];
    ennum--;
   }
else if (sen == ennum)
   {
    for (int i = 1; i <= 5; i++)
        EnCoor[ennum][i] = 0;
    ennum--;
   }
             

DrawClick(Sender);    
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormResize(TObject *Sender)
{
Memo1->Top = Form1->ClientHeight - 96;
Memo1->Left = Form1->ClientWidth - 136;

Draw->Top = Form1->ClientHeight - 96;
Draw->Left = Form1->ClientWidth - 216;

Save->Top = Form1->ClientHeight - 64;
Save->Left = Form1->ClientWidth - 216;

Load->Top = Form1->ClientHeight - 32;
Load->Left = Form1->ClientWidth - 216;

int t = Form1->ClientHeight;

menuxy[1][1] = 50; menuxy[1][2] = t - 50; menuxy[1][3] = 99; menuxy[1][4] = t - 9; menuxy[1][5] = 2;
menuxy[2][1] = 110; menuxy[2][2] = t - 85; menuxy[2][3] = 122; menuxy[2][4] = t - 37; menuxy[2][5] = 2;
menuxy[3][1] = 375; menuxy[3][2] = t - 200; menuxy[3][3] = 519; menuxy[3][4] = t - 38; menuxy[3][5] = 2;
menuxy[4][1] = 584; menuxy[4][2] = t - 200; menuxy[4][3] = 616; menuxy[4][4] = t - 168; menuxy[4][5] = 2;
menuxy[5][1] = 584; menuxy[5][2] = t - 167; menuxy[5][3] = 616; menuxy[5][4] = t - 135; menuxy[5][5] = 2;
menuxy[6][1] = 520; menuxy[6][2] =  t - 200; menuxy[6][3] = 551; menuxy[6][4] = t - 114; menuxy[6][5] = 2;
menuxy[7][1] = 552; menuxy[7][2] = t - 200; menuxy[7][3] = 583; menuxy[7][4] = t - 114; menuxy[7][5] = 2;
menuxy[8][1] = 584; menuxy[8][2] = t - 134; menuxy[8][3] = 616; menuxy[8][4] = t - 102; menuxy[8][5] = 2;
menuxy[9][1] = 584; menuxy[9][2] = t - 100; menuxy[9][3] = 616; menuxy[9][4] = t - 68; menuxy[9][5] = 2;
menuxy[10][1] = 0; menuxy[10][2] = t - 200; menuxy[10][3] = 128; menuxy[10][4] = t - 71; menuxy[10][5] = 2;
menuxy[11][1] = 130; menuxy[11][2] = t - 200; menuxy[11][3] = 247; menuxy[11][4] = t - 43; menuxy[11][5] = 2;
menuxy[12][1] = 250; menuxy[12][2] = t - 200; menuxy[12][3] = 373; menuxy[12][4] = t - 40; menuxy[12][5] = 2;
menuxy[13][1] = 520; menuxy[13][2] = t - 112; menuxy[13][3] = 568; menuxy[13][4] = t - 67; menuxy[13][5] = 2;
menuxy[14][1] = 520; menuxy[14][2] = t - 66; menuxy[14][3] = 582; menuxy[14][4] = t - 3; menuxy[14][5] = 2;
menuxy[15][1] = 10; menuxy[15][2] = t - 50; menuxy[15][3] = 43; menuxy[15][4] = t - 18; menuxy[15][5] = 2;
menuxy[16][1] = 125; menuxy[16][2] = t - 38; menuxy[16][3] = 157; menuxy[16][4] = t - 5; menuxy[16][5] = 2;
menuxy[17][1] = 158; menuxy[17][2] = t - 38; menuxy[17][3] = 191; menuxy[17][4] = t - 5; menuxy[17][5] = 2;
menuxy[18][1] = 192; menuxy[18][2] = t - 38; menuxy[18][3] = 224; menuxy[18][4] = t - 5; menuxy[18][5] = 2;
menuxy[19][1] = 225; menuxy[19][2] = t - 38; menuxy[19][3] = 257; menuxy[19][4] = t - 5; menuxy[19][5] = 2;
menuxy[20][1] = 258; menuxy[20][2] = t - 38; menuxy[20][3] = 290; menuxy[20][4] = t - 5; menuxy[20][5] = 2;
menuxy[21][1] = 618; menuxy[21][2] = t - 198; menuxy[21][3] = 681; menuxy[21][4] = t - 131; menuxy[21][5] = 2;
  menuxy[22][1] = 376; menuxy[22][2] = t - 198; menuxy[22][3] = 468; menuxy[22][4] = t - 101; menuxy[22][5] = 3;
menuxy[23][1] = 291; menuxy[23][2] = t - 36; menuxy[23][3] = 354; menuxy[23][4] = t - 5; menuxy[23][5] = 2;
menuxy[24][1] = 618; menuxy[24][2] = t - 130; menuxy[24][3] = 657; menuxy[24][4] = t - 68; menuxy[24][5] = 2;
  menuxy[25][1] = 0; menuxy[25][2] = t - 200; menuxy[25][3] = 187; menuxy[25][4] = t - 45; menuxy[25][5] = 3;
  menuxy[26][1] = 188; menuxy[26][2] = t - 200; menuxy[26][3] = 375; menuxy[26][4] = t - 45; menuxy[26][5] = 3;
  menuxy[27][1] = 470; menuxy[27][2] = t - 198; menuxy[27][3] = 500; menuxy[27][4] = t - 138; menuxy[27][5] = 3;
menuxy[28][1] = 582; menuxy[28][2] = t - 67; menuxy[28][3] = 616; menuxy[28][4] = t - 1; menuxy[28][5] = 2;
  menuxy[29][1] = 380; menuxy[29][2] = t - 98; menuxy[29][3] = 471; menuxy[29][4] = t - 10; menuxy[29][5] = 3;
  menuxy[30][1] = 470; menuxy[30][2] = t - 135; menuxy[30][3] = 495; menuxy[30][4] = t - 84; menuxy[30][5] = 3;
  menuxy[31][1] = 5; menuxy[31][2] = t - 44; menuxy[31][3] = 37; menuxy[31][4] = t - 11; menuxy[31][5] = 3;


tx = 0;
ty = 198;

for (int i = 1; i <= 14; i++)
   {
    enmenuxy[i][1] = tx;
    enmenuxy[i][2] = t - ty;
    enmenuxy[i][3] = tx + En[i][9]->Width;
    enmenuxy[i][4] = t - ty + En[i][9]->Height;
    enmenuxy[i][5] = 1;

    tx += En[i][9]->Width + 1;
    if (tx > 650){tx = 0; ty = 115;}
   }

DrawClick(Sender);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Usellect1Click(TObject *Sender)
{
swall = 0;
sen = 0;
sType = 0;
DrawClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CenterPlayer1Click(TObject *Sender)
{
PLx = Form1->ClientWidth / 2;
PLy = Form1->ClientHeight / 2;
DrawClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Draw1Click(TObject *Sender)
{
DrawClick(Sender);        
}
//---------------------------------------------------------------------------



void __fastcall TForm1::D(TObject *Sender, TCanvas *ACanvas, int &Width,
      int &Height)
{
DrawClick(Sender);
}
//---------------------------------------------------------------------------





void __fastcall TForm1::Save1Click(TObject *Sender)
{
if (file != "Untitled.map")
    SaveClick(Sender);
else SaveAs1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Load1Click(TObject *Sender)
{
LoadClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::New1Click(TObject *Sender)
{
Button1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit2Click(TObject *Sender)
{
Form1->Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SaveAs1Click(TObject *Sender)
{
if (SaveDialog1->Execute())
{

// Converting AnsiString to Char

char *a=new char[SaveDialog1->FileName.Length()+1];
a[SaveDialog1->FileName.Length()]=0;
memcpy(a,SaveDialog1->FileName.c_str(),SaveDialog1->FileName.Length());

// Setting permament variable for file name (char and string)

for (int i = 0; i < 240; i++)
    fileC[i] = a[i];

file = fileC;


Form1->Caption = ("GMan RPG Map Creator --- " + file);


SaveClick(Sender);
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Database1Click(TObject *Sender)
{
Form2->Show();
}
//---------------------------------------------------------------------------

