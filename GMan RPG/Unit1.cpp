//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <string>
#include <fstream.h>
#include <math.h>

#include <SysUtils.hpp>   // If exist command here

#include <windows.h>
//#include <glut32.lib>
                       /*
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
                       */
#include "Unit1.h"
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

WS = new Graphics::TBitmap;
WS->LoadFromFile("wstats.bmp");
WS->Transparent = true;

WI = new Graphics::TBitmap;
WI->LoadFromFile("wstats.bmp");
WI->Transparent = true;


// Walls

for (int i = 1; i <= 31; i++)
   {
    if (i < 29 || i > 31)
       {
        Wall[i] = new Graphics::TBitmap;
        Wall[i]->LoadFromFile("Enviroment/W" + IntToStr(i) + ".bmp");
        Wall[i]->Transparent = true;
       }
    if (i >= 29 && i <= 31) for (int h = 1; h <= 4; h++)
       {
        WallAnim[i][h] = new Graphics::TBitmap;
        WallAnim[i][h]->LoadFromFile("Enviroment/W" + IntToStr(i) + "." + IntToStr(h) + ".bmp");
        WallAnim[i][h]->Transparent = true;
       }
   }

Walltemp[1] = new Graphics::TBitmap;
Walltemp[1]->LoadFromFile("Enviroment/W2i.bmp");

// Items

for (int i = 1; i <= 2000; i++) if (FileExists("Items\\I" + IntToStr(i) + ".bmp")==true)
   {
    Items[i] = new Graphics::TBitmap;
    Items[i]->LoadFromFile("Items/I" + IntToStr(i) + ".bmp");
    Items[i]->Transparent = true;
   }

// Player

for (int i = 1; i <= 16; i++)
   {
    PL[i] = new Graphics::TBitmap;
    PL[i]->LoadFromFile("PL/PL" + IntToStr(i) + ".bmp");
    PL[i]->Transparent = true;
   }

// Load Enemies

TRead = new Graphics::TBitmap;

for (int h = 1; h <= 1000; h++) if (FileExists("Enemies\\En" + IntToStr(h) + ".bmp")==true)
   {
    TRead->LoadFromFile("Enemies/En" + IntToStr(h) + ".bmp");

    tx = 0;
    ty = TRead->Height * 3 / 4;

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

// Skills

int temp[20];
for (int i = 1; i <= 19; i++)
    temp[i] = -1;

temp[1] = 8; temp[2] = 9; temp[3] = 6; temp[4] = 3; temp[5] = 7; temp[6] = 6;
temp[7] = 5; temp[8] = 7; temp[9] = 7; temp[10] = -1; temp[11] = -1; temp[12] = -1;


for (int i = 1; i <= 19; i++)
for (int j = 0; j <= temp[i]; j++)
   {
    Skill[i][j] = new Graphics::TBitmap;
    Skill[i][j]->LoadFromFile("Skills/Sk" + IntToStr(i) + "/Sk" + IntToStr(i) + "." + IntToStr(j) + ".bmp");
    Skill[i][j]->Transparent = true;
   }

for (int i = 1; i <= 6; i++)
   {
    Death[i] = new Graphics::TBitmap;
    Death[i]->LoadFromFile("Death/Death" + IntToStr(i) + ".bmp");
    Death[i]->Transparent = true;
   }

for (int i = 1; i <= 5; i++)
   {
    ESk[i] = new Graphics::TBitmap;
    ESk[i]->LoadFromFile("Skills/ESk1/ESk" + IntToStr(i) + ".bmp");
    ESk[i]->Transparent = true;
   }

Back = new Graphics::TBitmap;
Back->LoadFromFile("Back.bmp");

Plus = new Graphics::TBitmap;
Plus->LoadFromFile("Plus.bmp");
Plus->Transparent = true;

WindowState = wsMaximized;

Sleep(2);

Button1Click(Sender);
LoadClick(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Timer1Timer(TObject *Sender)
{

// Sets your total strength

P.totatt = P.att;
P.totdemage = P.demage;
P.totdef = P.def;
P.tothp = P.hpmax;
P.totmp = P.mpmax;
P.totsta = P.stamax;

for (int i = 1; i <= 199; i++) if (M[i].equip == 1)
   {
    P.totatt += I[M[i].type].att;
    P.totdemage += I[M[i].type].demage;
    P.totdef += I[M[i].type].def;
    P.tothp += I[M[i].type].hp;
    P.totmp += I[M[i].type].mp;
    P.totsta += I[M[i].type].sta;
   }


// Restore stamina

if (valx == 0 && valy == 0 && P.sta < P.totsta)
   {
    if (P.sta * 100 / P.totsta < 20)P.staregen += 0.002 * P.totsta;
    if (P.sta * 100 / P.totsta >= 20 && P.sta / P.totsta * 100 < 40)P.staregen += 0.0025 * P.totsta;
    if (P.sta * 100 / P.totsta >= 40 && P.sta / P.totsta * 100 < 60)P.staregen += 0.003 * P.totsta;
    if (P.sta * 100 / P.totsta >= 60 && P.sta / P.totsta * 100 < 80)P.staregen += 0.004 * P.totsta;
    if (P.sta * 100 / P.totsta >= 80)P.staregen += 0.005 * P.totsta;
   }
if (P.sta > P.totsta) P.sta = P.totsta;
if (P.sta < 0) P.sta = 0;

// Restore or decrease health & mana

if (P.hp < P.tothp)
    P.hpregen += P.tothp / 14300.1 * 100;   // 1% of hpmax per 5 sec
else P.hp = P.tothp;

if (P.mp < P.totmp)                                                           // 143 is for 5 sec   1 is for 35 ms
    P.mpregen += P.totmp / 3920.1 * 100;   // 3.5% of mpmax per 5 sec               // 28.5 - 1 sec
else P.mp = P.totmp;
                                                                              // 2 * 143 = k   formula for 50% per 5 sec
                                                                              // 10 * 143 = k   formula for 10% per 5 sec
                                                                              // 100 * 143 = k   formula for 1% per 5 sec

if (P.hpregen > 1){P.hpregen--; P.hp++;}
if (P.hpregen > 60){P.hpregen -= 2; P.hp += 2;}
if (P.hpregen > 120){P.hpregen -= 3; P.hp += 3;}
if (P.hpregen > 200){P.hpregen -= 4; P.hp += 4;}

if (P.hpregen < -1){P.hpregen++; P.hp--;}

if (P.mpregen > 1){P.mpregen--; P.mp++;}
if (P.mpregen > 60){P.mpregen -= 2; P.mp += 2;}
if (P.mpregen > 120){P.mpregen -= 3; P.mp += 3;}

if (P.mpregen < -1){P.mpregen++; P.mp--;}
if (P.mpregen < -40){P.mpregen += 2; P.mp -= 2;}

// Run / Walk

if (P.sta < 5) control = 1;

if (control == 0 && shift == 1) P.run = 1.4;
if (control == 0 && shift == 0) P.run = 1;
if (control == 1) P.run = 0.6;

// WASD If you're using WASD Keys

if (wasd[1] == 1){valy = -P.speed / 5 * P.run; valx = 0; facing = 1;}
if (wasd[2] == 1){valx = -P.speed / 5 * P.run; valy = 0; facing = 5;}
if (wasd[3] == 1){valy = P.speed / 5 * P.run; valx = 0; facing = 9;}     // One button pressed
if (wasd[4] == 1){valx = P.speed / 5 * P.run; valy = 0; facing = 13;}

if (wasd[1] == 1 && wasd[2] == 1){valy = -P.speed / 7 * P.run; valx = valy; facing = 1;}
if (wasd[1] == 1 && wasd[4] == 1){valy = -P.speed / 7 * P.run; valx = -valy; facing = 1;}
if (wasd[2] == 1 && wasd[3] == 1){valy = P.speed / 7 * P.run; valx = -valy; facing = 5;}           // Multiple buttons pressed                                                      // Multiple buttons pressed
if (wasd[3] == 1 && wasd[4] == 1){valy = P.speed / 7 * P.run; valx = valy; facing = 13;}

// Enemy wall ---------------------------------------------------

for (int i = 1; i <= ennumr; i++) if (E[i].dead == 0 && valx != 0 | valy != 0)
   {
    // Right       Wall <--- PL
    if (PLx - 4 < EnCoor[i][3] && PLx - 4 > EnCoor[i][3] - 10 && PLy + PL[1]->Height - 16 < EnCoor[i][4] && PLy + PL[1]->Height > EnCoor[i][2])
        if (valx < 0)PLx = EnCoor[i][3] + 2;
    // Left        PL ---> Wall
    if (PLx + 30 < EnCoor[i][1] + 10 && PLx + 30 > EnCoor[i][1] && PLy + PL[1]->Height - 16 < EnCoor[i][4] && PLy + PL[1]->Height > EnCoor[i][2])
        if (valx > 0)PLx = EnCoor[i][1] - PL[1]->Width - 2;
    // Down     ^
    if (PLy + PL[1]->Height - 20 < EnCoor[i][4] && PLy + PL[1]->Height - 20 > EnCoor[i][4] - 10 && PLx < EnCoor[i][3] && PLx + 26 > EnCoor[i][1])
        if (valy < 0)PLy = EnCoor[i][4] - PL[1]->Height + 18;
    // Top      v
    if (PLy + PL[1]->Height + 4 < EnCoor[i][2] + 10 && PLy + PL[1]->Height + 4 > EnCoor[i][2] && PLx < EnCoor[i][3] && PLx + 26 > EnCoor[i][1])
        if (valy > 0)PLy = EnCoor[i][2] - PL[1]->Height - 2;
   }

// Walls ===========================================##########################################

for (int i = 1; i <= wallnum; i++)
   {
    // Right       Wall <--- PL
    if (PLx - 4 < wall[i][3] && PLx - 4 > wall[i][3] - 10 && PLy + PL[1]->Height - 16 < wall[i][4] && PLy + PL[1]->Height > wall[i][2])
        PLx = wall[i][3] + 2;
    // Left        PL ---> Wall
    if (PLx + 30 < wall[i][1] + 10 && PLx + 30 > wall[i][1] && PLy + PL[1]->Height - 16 < wall[i][4] && PLy + PL[1]->Height > wall[i][2])
        PLx = wall[i][1] - PL[1]->Width - 2;
    // Down     ^
    if (PLy + PL[1]->Height - 20 < wall[i][4] && PLy + PL[1]->Height - 20 > wall[i][4] - 10 && PLx < wall[i][3] && PLx + 26 > wall[i][1])
        PLy = wall[i][4] - PL[1]->Height + 18;
    // Top      v
    if (PLy + PL[1]->Height + 4 < wall[i][2] + 10 && PLy + PL[1]->Height + 4 > wall[i][2] && PLx < wall[i][3] && PLx + 26 > wall[i][1])
        PLy = wall[i][2] - PL[1]->Height - 2;
   }

// End of map ||||||||||

if (PLx + 36 > BI->Width - 300 && valx > 0)
   {
    backx -= valx;
    if (backx < -240)backx = 0;
    mx -= valx;
    PLx -= valx;
    for (int i = 1; i <= ennumr; i++){EnCoor[i][1] -= valx; EnCoor[i][3] -= valx;}
    for (int i = 1; i <= wallnum; i++){wall[i][1] -= valx; wall[i][3] -= valx;}
   }
if (PLx < 300 && valx < 0)
   {
    backx -= valx;
    if (backx > 240)backx = 0;
    mx -= valx;
    PLx -= valx;
    for (int i = 1; i <= ennumr; i++){EnCoor[i][1] -= valx; EnCoor[i][3] -= valx;}
    for (int i = 1; i <= wallnum; i++){wall[i][1] -= valx; wall[i][3] -= valx;}
   }
if (PLy + 36 > BI->Height - 300 && valy > 0)
   {
    backy -= valy;
    if (backy < -240)backy = 0;
    my -= valy;
    PLy -= valy;
    for (int i = 1; i <= ennumr; i++){EnCoor[i][2] -= valy; EnCoor[i][4] -= valy;}
    for (int i = 1; i <= wallnum; i++){wall[i][2] -= valy; wall[i][4] -= valy;}
   }
if (PLy < 270 && valy < 0)
   {
    backy -= valy;
    if (backy > 240)backy = 0;
    my -= valy;
    PLy -= valy;
    for (int i = 1; i <= ennumr; i++){EnCoor[i][2] -= valy; EnCoor[i][4] -= valy;}
    for (int i = 1; i <= wallnum; i++){wall[i][2] -= valy; wall[i][4] -= valy;}
   }

PLx += valx; PLy += valy;

// Skills @@@@@@@@@@@@@@@@@@"""""""""""""""@@@@@@@@@@@@@@@@@@@@

for (int i = 1; i <= 19; i++)
    S[i].waited--;
for (int i = 1; i <= 19; i++)
    if (qsnums[S[i].quick] == 1 && S[i].waited < 0 && S[i].mp < P.mp + P.mpregen && S[i].sta < P.sta + P.staregen && S[i].hp < P.hp)         // qsnums[Sk[i].quick] == 1 if you pressed exactly that button where the skill is
       {
        S[i].atk = 1;
        S[i].waited = S[i].wait;
        S[i].hit = 0;
        S[i].face = 1;
        S[i].animnum = 0;

        P.mpregen -= S[i].mp;
        P.staregen -= S[i].sta;
        P.hpregen -= S[i].hp;
       }

// Sword

if (S[1].atk == 1)
   {
    S[1].atk = 2;
    if (facing >= 1 && facing <= 4) {S[1].x = PLx; S[1].y = PLy - 40;}
    if (facing >= 5 && facing <= 8) {S[1].x = PLx - 30; S[1].y = PLy;}
    if (facing >= 9 && facing <= 12) {S[1].x = PLx + 2; S[1].y = PLy + 40;}
    if (facing >= 13 && facing <= 16){S[1].x = PLx + 24; S[1].y = PLy; S[1].face = 5;}
   }
if (S[1].atk == 2)
   {
    S[1].animnum++;
    if (S[1].animnum == 2) S[1].face++;
    if (S[1].animnum == 3) {S[1].y += 5; S[1].face++;}
    if (S[1].animnum == 4) {S[1].y += 5; S[1].face++;}
    if (S[1].animnum >= 5) S[1].atk = 0;
   }


// Implosion

if (S[2].atk == 1)
   {
    S[2].atk = 2;
    if (facing >= 1 && facing <= 4) {S[2].x = PLx - 20; S[2].y = PLy - 60;}
    if (facing >= 5 && facing <= 8) {S[2].x = PLx - 70; S[2].y = PLy - 10;}
    if (facing >= 9 && facing <= 12) {S[2].x = PLx - 20; S[2].y = PLy + 40;}
    if (facing >= 13 && facing <= 16){S[2].x = PLx + 24; S[2].y = PLy - 10;}
   }
if (S[2].atk == 2)
   {
    S[2].animnum++;
    if (S[2].animnum == 2) {S[2].x += 7; S[2].y += 7; S[2].face++;}
    if (S[2].animnum == 3) {S[2].x += 8; S[2].y += 8; S[2].face++;}
    if (S[2].animnum == 4) {S[2].x += 5; S[2].y += 5; S[2].face++;}
    if (S[2].animnum == 5) {S[2].x += 5; S[2].y += 5; S[2].face++;}
    if (S[2].animnum == 6) {S[2].x += 5; S[2].y += 5; S[2].face++;}
    if (S[2].animnum == 8) {S[2].x -= 15; S[2].y -= 15; S[2].face++;}
    if (S[2].animnum == 9) {S[2].x -= 10; S[2].y -= 10; S[2].face++;}
    if (S[2].animnum == 10){S[2].x -= 10; S[2].y -= 10; S[2].face++;}
    if (S[2].animnum >= 11) S[2].atk = 0;
   }


// HpRegen

if (S[3].atk == 1)
   {
    S[3].atk = 2;
    S[3].x = PLx - 15;
    S[3].y = PLy - 10;
   }
if (S[3].atk == 2)
   {
    S[3].animnum++;
    if (S[3].animnum > 1){S[3].face++; S[3].y -= 4;}
    if (S[3].animnum >= 7) S[3].atk = 0;
   }

// Stab

if (S[4].atk == 1)
   {
    S[4].atk = 2;
    if (facing >= 1 && facing <= 4) {S[4].x = PLx - 15; S[4].y = PLy - 48;}
    if (facing >= 5 && facing <= 8) {S[4].x = PLx - 46; S[4].y = PLy- 6;}
    if (facing >= 9 && facing <= 12) {S[4].x = PLx - 15; S[4].y = PLy + 35;}
    if (facing >= 13 && facing <= 16){S[4].x = PLx + 18; S[4].y = PLy - 8;}
   }
if (S[4].atk == 2)
   {
    S[4].animnum++;
    if (S[4].animnum == 2) {S[4].x += 12; S[4].y += 12; S[4].face++;}
    if (S[4].animnum == 3) {S[4].x += 10; S[4].y += 10; S[4].face++;}
    if (S[4].animnum >= 4) S[4].atk = 0;
   }

// Swarm

if (S[5].atk == 1)
   {
    S[5].atk = 2;
    S[5].x = PLx - 40;
    S[5].y = PLy - 20;
   }
if (S[5].atk == 2)
   {
    S[5].animnum++;
    if (S[5].animnum > 1)S[5].face++;
    if (S[5].animnum == 7)S[5].face = 3;
    if (S[5].animnum == 12)S[5].face = 2;
    if (S[5].animnum == 13)S[5].face = 1;
    if (S[5].animnum >= 14)S[5].atk = 0;
   }


// StaRegen

if (S[6].atk == 1)
   {
    S[6].atk = 2;
    S[6].x = PLx - 2;
    S[6].y = PLy + 5;
   }
if (S[6].atk == 2)
   {
    S[6].animnum++;
    if (S[6].animnum == 2) S[6].face++;
    if (S[6].animnum == 3) S[6].face++;
    if (S[6].animnum == 4) S[6].face = 1;
    if (S[6].animnum == 5) S[6].face++;
    if (S[6].animnum == 6) S[6].face++;
    if (S[6].animnum == 8) {S[6].x -= 3; S[6].y -= 2; S[6].face++;}
    if (S[6].animnum == 9) {S[6].x -= 6; S[6].y -= 10; S[6].face++;}
    if (S[6].animnum == 10) {S[6].x -= 7; S[6].y -= 15; S[6].face++;}
    if (S[6].animnum >= 11) S[6].atk = 0;
   }

// Claws

if (S[7].atk == 1)
   {
    S[7].atk = 2;
    if (facing >= 1 && facing <= 4) {S[7].x = PLx - 13; S[7].y = PLy - 48;}
    if (facing >= 5 && facing <= 8) {S[7].x = PLx - 42; S[7].y = PLy- 6;}
    if (facing >= 9 && facing <= 12) {S[7].x = PLx - 12; S[7].y = PLy + 35;}
    if (facing >= 13 && facing <= 16){S[7].x = PLx + 20; S[7].y = PLy - 8;}
   }
if (S[7].atk == 2)
   {
    S[7].animnum++;
    if (S[7].animnum > 1) S[7].face++;
    if (S[7].animnum >= 6) S[7].atk = 0;
   }

// Shock

if (S[8].atk == 1)
   {
    S[8].atk = 2;
    if (facing >= 1 && facing <= 4) {S[8].x = PLx - 31; S[8].y = PLy - 70;}
    if (facing >= 5 && facing <= 8) {S[8].x = PLx - 82; S[8].y = PLy - 15;}
    if (facing >= 9 && facing <= 12) {S[8].x = PLx - 30; S[8].y = PLy + 35;}
    if (facing >= 13 && facing <= 16){S[8].x = PLx + 24; S[8].y = PLy - 19;}
   }
if (S[8].atk == 2)
   {
    S[8].animnum++;
    if (S[8].animnum > 1) S[8].face++;
    if (S[8].animnum >= 8) S[8].atk = 0;
   }

// Stone Skin

if (S[9].atk == 1)
   {
    S[9].atk = 2;
    S[9].x = PLx - 11;
    S[9].y = PLy - 30;
   }
if (S[9].atk == 2)
   {
    S[9].animnum++;
    if (S[9].animnum >= 2) S[9].face++;
    if (S[9].animnum >= 8) S[9].atk = 0;
   }

// Death anim

if (deathanim[0] == 1)
   {
    deathanim[4]++;
    if (deathanim[4] == 2){deathanim[3]++; deathanim[1] -= 5; deathanim[2] -= 5;}
    if (deathanim[4] == 3){deathanim[3]++; deathanim[1] -= 2; deathanim[2] -= 5;}
    if (deathanim[4] == 4){deathanim[3]++; deathanim[1] -= 0; deathanim[2] -= 5;}
    if (deathanim[4] == 5){deathanim[3]++; deathanim[1] += 2; deathanim[2] -= 5;}
    if (deathanim[4] == 6){deathanim[3]++; deathanim[1] += 5; deathanim[2] -= 5;}
    if (deathanim[4] == 7){deathanim[3]--; deathanim[1] += 2; deathanim[2] -= 5;}
    if (deathanim[4] == 8){deathanim[3]++; deathanim[1] += 0; deathanim[2] -= 5;}
    if (deathanim[4] == 9){deathanim[3]--; deathanim[1] -= 2; deathanim[2] -= 5;}
    if (deathanim[4] == 10){deathanim[3]++; deathanim[1] -= 5; deathanim[2] -= 5;}
    if (deathanim[4] == 11){                deathanim[1] -= 2; deathanim[2] -= 5;}
    if (deathanim[4] >= 12){deathanim[0] = 0;}
   }


// Esk anim

if (eskanim[0] == 1)
   {
    eskanim[4]++;
    if (eskanim[4] >= 2 && eskanim[4] <= 5){eskanim[3]++; eskanim[2] += 2;}
    if (eskanim[4] >= 6)eskanim[0] = 0;
   }

// Enemy killed you

if (P.hp < 0)
   {
    Sleep(2000);

    P.exp *= 0.5;
    P.gold *= 0.6;

    P.hp = P.tothp;
    P.mp = P.totmp;
    P.sta = P.totsta;

    PLx = mx + 500;
    PLy = my + 400;
    CenterPlayerClick(Sender);
   }

Timer2Timer(Sender);


// Quick slots taken

for (int i = 1; i <= 8; i++) qst[i] = 0;

for (int i = 1; i <= 19; i++)
    for (int j = 1; j <= 8; j++)
        if (S[i].quick == j) qst[j] = 1;

// Shop available?

if (PLx < mx || PLx > mx + 1000 || PLy < my || PLy > my + 800)
   wb = 0;

// Level up

if (P.exp >= P.expmax)
   {
    P.exp -= P.expmax;
    P.lvl++;
    P.hpmax += P.hpmax * 10 / 100;
    P.hp = P.hpmax;
    P.mpmax += P.mpmax * 7 / 100;
    P.mp = P.mpmax;
    P.expmax = P.lvl * (100 + (16 + 2 * P.lvl) * P.lvl);
    P.statsp += 5;
    P.skillp += 1;
    P.att += 2;
    P.def++;
    P.demage++;
    P.stamax += P.stamax * 4 / 100;
    P.sta = P.stamax;
   }

// Decrease stamina

if (P.run > 1) if (valx != 0 || valy != 0) P.staregen -= 1.2;
if (P.run == 1) if (valx != 0 || valy != 0) P.staregen -= 0.2;
if (P.run < 1) if (valx != 0 || valy != 0) P.staregen += 0.3;

if (P.staregen > 1){P.staregen--; P.sta++;}
if (P.staregen > 50){P.staregen -= 2; P.sta += 2;}
if (P.staregen > 100){P.staregen -= 3; P.sta += 3;}

if (P.staregen < -1){P.staregen++; P.sta--;}
if (P.staregen < -40){P.staregen += 2; P.sta -= 2;}
if (P.staregen < -80){P.staregen += 3; P.sta -= 3;}
if (P.staregen < -120){P.staregen += 4; P.sta -= 4;}

//  Draws new your position *********************************************

DrawClick(Sender);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
Memo1->Lines->Clear();
Memo1->Lines->Add("X = " + IntToStr(X - mx));
Memo1->Lines->Add("Y = " + IntToStr(Y - my));

// Moving Stats window

if (press == 1 && wstats == 1 && X > wsx && X < wsx + 400 && Y > wsy && Y < wsy + 300)
   {
    wsx += X - mx2;
    wsy += Y - my2;
   }

// Moving Inventory window

if (RMB == 1 && wi == 1 && X > wix && X < wix + 400 && Y > wiy && Y < wiy + 300)
   {
    wix += X - mx2;
    wiy += Y - my2;
   }

// Selecting inventory items, ion

ion = 0;

if (wi == 1)
   {
    // Equip

    tx = 20 + wix; ty = 50 + wiy;
    for (int i = 1; i <= 9; i++)
       {
        if (X > tx && X < tx + 30 && Y > ty && Y < ty + 30)
            for (int j = 1; j <= 199; j++)
                if (M[j].equip == 1 && I[M[j].type].type == i)
                    ion = j;

        tx += 35;
        if (i == 3 || i == 6 || i == 9){tx = 20 + wix; ty += 35;}
       }

    // Stocked items

    tx = 160 + wix; ty = 20 + wiy;
    for (int i = 1; i <= 36; i++)
       {
        if (X > tx && X < tx + 30 && Y > ty && Y < ty + 30)
            for (int j = 1; j <= 199; j++)
                if (M[j].slot == i)
                    ion = j;

        tx += 35;
        if (i == 6 || i == 12 || i == 18 || i == 24 || i == 30){tx = 160 + wix; ty += 35;}
       }
   }

// Selecting shop items, wbion

wbion = 0;

    // Stock

    tx = BI->Width / 2 - 95; ty = 30;
    for (int i = 1; i <= 40; i++)
       {

        if (X > tx && X < tx + 30 && Y > ty && Y < ty + 30)
            wbion = i;

        tx += 35;
        if (i == 8 || i == 16 || i == 24 || i == 32){tx = BI->Width / 2 - 95; ty += 35;}
       }

mx2 = X;
my2 = Y;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{

Timer1->Enabled = true;
//Timer2->Enabled = true;

Button1->Enabled = false;
Button1->Visible = false;

Memo1->Lines->Clear();

anim = 0;
facing = 1;
control = 0;

wstats = 0;
wsx = 50;
wsy = 200;

wi = 0;
wix = 400;
wiy = 300;

mx = 0;
my = 0;

P.hp = 200;
P.hpmax = 200;
P.hpregen = 0;
P.mp = 80;
P.mpmax = 80;
P.mpregen = 0;
P.sta = 100;
P.stamax = 100;
P.lvl = 1;
P.speed = 30;
P.run = 1;
P.att = 15;
P.def = 10;
P.demage = 6;
P.exp = 0;
P.expmax = 100;
P.gold = 5;

P.exp += 0;
P.gold += 0;

P.totdemage = P.demage;
P.totatt = P.att;
P.totdef = P.def;
P.tothp = P.hpmax;
P.totmp = P.mpmax;
P.totsta = P.stamax;


S[1].lvl = 1;
S[1].quick = 1;

S[1].wait = 18;
S[1].sta = 12;
S[1].demage = 1;

S[2].wait = 150;
S[2].mp = 25;
S[2].demage = 2;

S[3].wait = 150;
S[3].mp = 25;
S[3].hp = -70;

S[4].wait = 50;
S[4].sta = 22;
S[4].demage = 1.5;

S[5].wait = 200;
S[5].mp = 38;
S[5].demage = 0.2;

S[6].wait = 80;
S[6].mp = 20;
S[6].sta = -50;

S[7].wait = 70;
S[7].sta = 36;
S[7].demage = 2;

S[8].wait = 300;
S[8].mp = 50;
S[8].demage = 5;

S[9].wait = 500;
S[9].sta = -80;

M[1].type = 1; M[1].slot = 1;
M[2].type = 35; M[2].slot = 36; M[2].q = 2;



// Shop

B[1].items[1] = 3;
B[1].items[2] = 5;
B[1].items[3] = 6;
B[1].items[4] = 8;
B[1].items[5] = 9;
B[1].items[6] = 10;
B[1].items[7] = 13;
B[1].items[8] = 14;
B[1].items[9] = 15;
B[1].items[10] = 16;
B[1].items[11] = 17;
B[1].items[12] = 18;
B[1].items[13] = 19;
B[1].items[14] = 21;
B[1].items[15] = 23;
B[1].items[16] = 11;
B[1].items[17] = 35; B[1].q[17] = 39;
B[1].items[18] = 37; B[1].q[18] = 29;
B[1].items[19] = 39; B[1].q[19] = 24;
B[1].items[20] = 7;
B[1].items[21] = 36; B[1].q[21] = 29;
B[1].items[22] = 38; B[1].q[22] = 19;


B[1].sratio = 0.6;
B[1].bratio = 1;


// Read map from file  ================================================#########

ifstream fd("Map1.map");

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


// Reads and converts to integer ennumr

fd.getline(read, 50);
read3 = read;
ennumr = StrToInt(read3);


// Reads all enemies

for (int h = 1; h <= ennumr; h++)
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
           else {EnCoor[h][i] = StrToInt(read4); E[h].spawnCoor[i] = StrToInt(read4); read4 = ""; j = 50;}
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
   ET[h].name = read;                // Reads the name

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
               if (i == 1) ET[h].hpmax = StrToInt(read4);
               if (i == 2) ET[h].speed = StrToInt(read4);
               if (i == 3) ET[h].sight = StrToInt(read4);
               if (i == 4) ET[h].att = StrToInt(read4);
               if (i == 5) ET[h].def = StrToInt(read4);
               if (i == 6) ET[h].demage = StrToInt(read4);
               if (i == 7) ET[h].exp = StrToInt(read4);
               if (i == 8) ET[h].gold = StrToInt(read4);
               if (i == 9) ET[h].icon = StrToInt(read4);
               if (i == 10) ET[h].idropc = StrToInt(read4);
               read4 = "";
               j = 50;
              }
          }
      }

   // Reads enemy item drops E[..].item[..]

   for (int i = 1; i <= ET[h].idropc; i++)
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
           else {ET[h].item[tempDC] = StrToInt(read4); j = 50; read4 = "";}
          }
      }
  }

fd.close();


//Sets enemy stats

for (int i = 1; i <= ennumr; i++)
   {
                         /*
    if (EnCoor[i][5] == 1)
       {
        E[i].hpmax = 60;
        E[i].speed = 22;
        E[i].sight = 300;
        E[i].att = 30;
        E[i].def = 10;
        E[i].demage = 10;
        E[i].exp = 10;
        E[i].gold = 5;
        E[i].item[1] = 150;
        E[i].item[2] = 180;
        E[i].item[46] = 70;
       }
    if (EnCoor[i][5] == 2)
       {
        E[i].hpmax = 100;
        E[i].speed = 16;
        E[i].sight = 200;
        E[i].att = 40;
        E[i].def = 18;
        E[i].demage = 13;
        E[i].exp = 15;
        E[i].gold = 7;
        E[i].item[25] = 350;
        E[i].item[26] = 450;
        E[i].item[27] = 600;
       }
    if (EnCoor[i][5] == 3)
       {
        E[i].hpmax = 110;
        E[i].speed = 23;
        E[i].sight = 280;
        E[i].att = 30;
        E[i].def = 12;
        E[i].demage = 16;
        E[i].exp = 20;
        E[i].gold = 13;
        E[i].item[4] = 380;
        E[i].item[13] = 280;
        E[i].item[52] = 100;
       }
    if (EnCoor[i][5] == 4)
       {
        E[i].hpmax = 80;
        E[i].speed = 28;
        E[i].sight = 380;
        E[i].att = 55;
        E[i].def = 5;
        E[i].demage = 25;
        E[i].exp = 30;
        E[i].gold = 10;
        E[i].item[2] = 180;
        E[i].item[46] = 60;
        E[i].item[53] = 500;
       }
    if (EnCoor[i][5] == 5)
       {
        E[i].hpmax = 150;
        E[i].speed = 18;
        E[i].sight = 240;
        E[i].att = 50;
        E[i].def = 28;
        E[i].demage = 20;
        E[i].exp = 46;
        E[i].gold = 5;
        E[i].item[47] = 50;
        E[i].item[50] = 180;
       }
    if (EnCoor[i][5] == 6)
       {
        E[i].hpmax = 160;
        E[i].speed = 26;
        E[i].sight = 320;
        E[i].att = 40;
        E[i].def = 20;
        E[i].demage = 30;
        E[i].exp = 65;
        E[i].gold = 15;
        E[i].item[31] = 300;
        E[i].item[32] = 350;
        E[i].item[33] = 500;
        E[i].item[46] = 25;
       }
    if (EnCoor[i][5] == 7)
       {
        E[i].hpmax = 190;
        E[i].speed = 20;
        E[i].sight = 280;
        E[i].att = 35;
        E[i].def = 20;
        E[i].demage = 38;
        E[i].exp = 85;
        E[i].gold = 30;
        E[i].item[35] = 180;
        E[i].item[36] = 300;
        E[i].item[37] = 180;
        E[i].item[38] = 300;
       }
    if (EnCoor[i][5] == 8)
       {
        E[i].hpmax = 240;
        E[i].speed = 18;
        E[i].sight = 300;
        E[i].att = 60;
        E[i].def = 45;
        E[i].demage = 40;
        E[i].exp = 95;
        E[i].gold = 40;
        E[i].item[47] = 40;
        E[i].item[50] = 90;
       }
    if (EnCoor[i][5] == 9)
       {
        E[i].hpmax = 300;
        E[i].speed = 25;
        E[i].sight = 400;
        E[i].att = 65;
        E[i].def = 45;
        E[i].demage = 45;
        E[i].exp = 125;
        E[i].gold = 50;
        E[i].item[28] = 350;
        E[i].item[29] = 400;
        E[i].item[30] = 500;
        E[i].item[54] = 300;
       }
    if (EnCoor[i][5] == 10)
       {
        E[i].hpmax = 350;
        E[i].speed = 30;
        E[i].sight = 460;
        E[i].att = 120;
        E[i].def = 35;
        E[i].demage = 50;
        E[i].exp = 155;
        E[i].gold = 40;
        E[i].item[10] = 350;
        E[i].item[17] = 250;
        E[i].item[53] = 160;
       }
    if (EnCoor[i][5] == 11)
       {
        E[i].hpmax = 500;
        E[i].speed = 22;
        E[i].sight = 380;
        E[i].att = 80;
        E[i].def = 60;
        E[i].demage = 70;
        E[i].exp = 200;
        E[i].gold = 60;
        E[i].item[6] = 180;
        E[i].item[51] = 60;
        E[i].item[55] = 420;
       }
    if (EnCoor[i][5] == 12)
       {
        E[i].hpmax = 600;
        E[i].speed = 24;
        E[i].sight = 340;
        E[i].att = 80;
        E[i].def = 50;
        E[i].demage = 80;
        E[i].exp = 260;
        E[i].gold = 120;
        E[i].item[10] = 450;
        E[i].item[16] = 280;
        E[i].item[18] = 400;
        E[i].item[20] = 360;
        E[i].item[22] = 380;
        E[i].item[23] = 350;
        E[i].item[24] = 500;
       }
    if (EnCoor[i][5] == 13)
       {
        E[i].hpmax = 1000;
        E[i].speed = 18;
        E[i].sight = 300;
        E[i].att = 100;
        E[i].def = 40;
        E[i].demage = 100;
        E[i].exp = 350;
        E[i].gold = 140;
        E[i].item[5] = 200;
        E[i].item[8] = 280;
        E[i].item[34] = 430;
       }
    if (EnCoor[i][5] == 14)
       {
        E[i].hpmax = 4000;
        E[i].speed = 30;
        E[i].sight = 360;
        E[i].att = 250;
        E[i].def = 80;
        E[i].demage = 125;
        E[i].exp = 1500;
        E[i].gold = 2000;
        E[i].item[12] = 9;
       }                   */


    enface[i] = 9;
    E[i].dead = 0;
    E[i].timer = 0;
    E[i].Range = 500;       

    E[i].hpmax = ET[EnCoor[i][5]].hpmax;
    E[i].speed = ET[EnCoor[i][5]].speed;
    E[i].sight = ET[EnCoor[i][5]].sight;
    E[i].att = ET[EnCoor[i][5]].att;
    E[i].def = ET[EnCoor[i][5]].def;
    E[i].demage = ET[EnCoor[i][5]].demage;
    E[i].exp = ET[EnCoor[i][5]].exp;
    E[i].gold = ET[EnCoor[i][5]].gold;
    E[i].icon = ET[EnCoor[i][5]].icon;
    E[i].name = ET[EnCoor[i][5]].name;

    for (int h = 1; h <= itemnum; h++)
        E[i].item[h] = ET[EnCoor[i][5]].item[h];

    E[i].hp = E[i].hpmax;
   }

DrawClick(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
press = 1;

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

// Upping stats

if (wstats == 1)
   {
    if (P.statsp > 0 && LMB == 1)
        {
         if (X < 150 + wsx && X > 130 + wsx && Y < 62 + wsy && Y > 42 + wsy)
             {P.statsp--; P.att++;}
         if (X < 150 + wsx && X > 130 + wsx && Y < 87 + wsy && Y > 67 + wsy)
             {P.statsp--; P.def++;}
         if (X < 150 + wsx && X > 130 + wsx && Y < 112 + wsy && Y > 92 + wsy)
             {P.statsp--; P.hpmax += 5;}
         if (X < 150 + wsx && X > 130 + wsx && Y < 137 + wsy && Y > 117 + wsy)
             {P.statsp--; P.mpmax += 3;}
         if (X < 150 + wsx && X > 130 + wsx && Y < 162 + wsy && Y > 142 + wsy)
             {P.statsp--; P.stamax += 3;}
        }

     // Leveling skills

    if (P.skillp > 0 && LMB == 1)
       {
        tx = 245; ty = 20;
        for (int i = 2; i <= 12; i++)
           {
            if (X < tx + 40 + wsx && X > tx + wsx && Y < ty + 40 + wsy && Y > ty + wsy)
             if (i <= 3 || i <= 6 & P.lvl >= 4 || i <= 9 & P.lvl >= 8 || i <= 12 & P.lvl >= 12)
               {
                P.skillp--;
                S[i].lvl++;
                if (S[i].lvl > 1)
                   {
                    if (S[i].demage > 0)S[i].demage += 0.2;
                    S[i].wait *= 1.1;
                    if (S[i].hp > 0)S[i].hp *= 1.2;
                    else S[i].hp *= 1.3;
                    if (S[i].mp > 0)S[i].mp *= 1.2;
                    else S[i].mp *= 1.3;
                    if (S[i].sta > 0)S[i].sta *= 1.334;
                    else S[i].sta *= 1.3;
                   }
               }
            tx += 55;
            if (i == 3 || i == 6 || i == 9){tx = 190; ty += 70;}
           }
       }

    // Adding skills to quick box

    if (RMB == 1)
       {
        tx = 190; ty = 20;
        for (int i = 1; i <= 12; i++)
           {
            if (X < tx + 40 + wsx && X > tx + wsx && Y < ty + 40 + wsy && Y > ty + wsy && S[i].lvl > 0)
                for (int j = 1; j <= 8; j++)
                    if (qst[j] != 1){S[i].quick = j; j = 10;}

            tx += 55;
            if (i == 3 || i == 6 || i == 9){tx = 190; ty += 70;}
           }
       }
   }

// Removing skills from quick box

if (X < 45 && X > 5 && Y < Form1->ClientHeight - 5 && Y > Form1->ClientHeight - 45 && qst[1] == 1 && RMB == 1)
    for (int i = 1; i <= 19; i++)
        if (S[i].quick == 1)S[i].quick = 0;
if (X < 90 && X > 50 && Y < Form1->ClientHeight - 5 && Y > Form1->ClientHeight - 45 && qst[2] == 1 && RMB == 1)
    for (int i = 1; i <= 19; i++)
        if (S[i].quick == 2)S[i].quick = 0;
if (X < 135 && X > 95 && Y < Form1->ClientHeight - 5 && Y > Form1->ClientHeight - 45 && qst[3] == 1 && RMB == 1)
    for (int i = 1; i <= 19; i++)
        if (S[i].quick == 3)S[i].quick = 0;
if (X < 180 && X > 140 && Y < Form1->ClientHeight - 5 && Y > Form1->ClientHeight - 45 && qst[4] == 1 && RMB == 1)
    for (int i = 1; i <= 19; i++)
        if (S[i].quick == 4)S[i].quick = 0;
if (X < 240 && X > 200 && Y < Form1->ClientHeight - 5 && Y > Form1->ClientHeight - 45 && qst[5] == 1 && RMB == 1)
    for (int i = 1; i <= 19; i++)
        if (S[i].quick == 5)S[i].quick = 0;
if (X < 285 && X > 245 && Y < Form1->ClientHeight - 5 && Y > Form1->ClientHeight - 45 && qst[6]== 1 && RMB == 1)
    for (int i = 1; i <= 19; i++)
        if (S[i].quick == 6)S[i].quick = 0;
if (X < 330 && X > 290 && Y < Form1->ClientHeight - 5 && Y > Form1->ClientHeight - 45 && qst[7] == 1 && RMB == 1)
    for (int i = 1; i <= 19; i++)
        if (S[i].quick == 7)S[i].quick = 0;
if (X < 375 && X > 335 && Y < Form1->ClientHeight - 5 && Y > Form1->ClientHeight - 45 && qst[8] == 1 && RMB == 1)
    for (int i = 1; i <= 19; i++)
        if (S[i].quick == 8)S[i].quick = 0;

// Selecting inventory items

if (wi == 1)
   {
    // Equip

    tx = 20 + wix; ty = 50 + wiy;
    for (int i = 1; i <= 9; i++)
       {
        if (X > tx && X < tx + 30 && Y > ty && Y < ty + 30)
            for (int j = 1; j <= 199; j++)
                if (M[j].equip == 1 && I[M[j].type].type == i)
                    if (RMB != 1) isel = j;

        tx += 35;
        if (i == 3 || i == 6 || i == 9){tx = 20 + wix; ty += 35;}
       }

    // Stocked items

    tx = 160 + wix; ty = 20 + wiy;
    for (int i = 1; i <= 36; i++)
       {
        if (X > tx && X < tx + 30 && Y > ty && Y < ty + 30)
            for (int j = 1; j <= 199; j++)
                if (M[j].slot == i)
                   {
                    if (RMB != 1)isel = j;
                    if (RMB == 1 && I[M[j].type].type == 10)
                       {
                        P.hpregen += I[M[j].type].hp;
                        P.mpregen += I[M[j].type].mp;
                        P.staregen += I[M[j].type].sta;
                        if (M[j].q > 0)M[j].q--;
                        else if (M[j].q == 0){M[j].type = 0; M[j].slot = 0;}
                       }
                   }

        tx += 35;
        if (i == 6 || i == 12 || i == 18 || i == 24 || i == 30){tx = 160 + wix; ty += 35;}
       }
   }

// Selecting shop items

    tx = BI->Width / 2 - 95; ty = 30;
    for (int i = 1; i <= 40; i++)
       {

        if (X > tx && X < tx + 30 && Y > ty && Y < ty + 30)
            wbisel = i;

        tx += 35;
        if (i == 8 || i == 16 || i == 24 || i == 32){tx = BI->Width / 2 - 95; ty += 35;}
       }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
press = 0;

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

// Placing inventory items

int t;

if (wi == 1)
   {
    // Equip

    tx = 20 + wix; ty = 50 + wiy;
    if (X > tx && X < tx + 105 && Y > ty && Y < ty + 105 && isel > 0)
       {
        for (int j = 1; j <= 199; j++)
            if (M[j].equip == 1 && I[M[j].type].type == I[M[isel].type].type && I[M[isel].type].lvl <= P.lvl)  // There is sth already
               {
                M[j].equip = 0;
                M[j].slot = M[isel].slot;
                M[isel].equip = 1;
                M[isel].slot = 0;
                t = 1;
               }
        if (t != 1 && I[M[isel].type].type >= 1 && I[M[isel].type].type <= 9 && I[M[isel].type].lvl <= P.lvl)  // Free slot
           {
            M[isel].equip = 1;
            M[isel].slot = 0;
           }
       }

    // Stocked items

    t = 0;
    tx = 160 + wix; ty = 20 + wiy;
    for (int i = 1; i <= 36; i++)
       {
        if (X > tx && X < tx + 30 && Y > ty && Y < ty + 30 && isel > 0)
           {
            for (int j = 1; j <= 199; j++)
                if (M[j].slot == i && M[isel].slot != 0)  // Moving from stock to stock, replace slots
                   {
                    t = M[j].slot;
                    M[j].slot = M[isel].slot;
                    M[isel].slot = t;
                    t = 1;
                   }
                else if (M[j].slot == i && M[isel].slot == 0 && I[M[j].type].type == I[M[isel].type].type && I[M[j].type].lvl <= P.lvl) // Moving from equip to slot, if types are the same, replace
                   {
                    M[isel].slot = M[j].slot;
                    M[isel].equip = 0;
                    M[j].slot = 0;
                    M[j].equip = 1;
                    t = 1;
                   }
                else if (M[j].slot == i && M[isel].slot == 0 && I[M[j].type].type != I[M[isel].type].type | I[M[j].type].lvl > P.lvl) // If types not the same, or lvl to low, do nothing
                    t = 1;
            if (t != 1)    // Free slot
               {
                M[isel].slot = i;
                M[isel].equip = 0;
               }
           }

        tx += 35;
        if (i == 6 || i == 12 || i == 18 || i == 24 || i == 30){tx = 160 + wix; ty += 35;}
       }
   }

// Buying items

if (wb > 0)
   {
    if (X > BI->Width / 2 - 180 && X < BI->Width / 2 - 150 + 30 && Y > 170 && Y < 200 && wbisel > 0 && P.gold >= I[B[wb].items[wbisel]].price * B[wb].bratio && B[wb].items[wbisel] > 0)
       {
        P.gold -= I[B[wb].items[wbisel]].price * B[wb].bratio;
        iadd = B[wb].items[wbisel];

        if (B[wb].q[wbisel] > 0)B[wb].q[wbisel]--; //More than one
        else for (int i = wbisel; i <= 40; i++)    // Only one
           {
            B[wb].items[i] = B[wb].items[i + 1];
            B[wb].q[i] = B[wb].q[i + 1];
           }

        AddItemClick(Sender);
       }
    wbisel = 0;
   }

// Selling item

if (wi == 1 && wb > 0 && shift != 1 && isel > 0)
   {
    if (X > 20 + wix && X < 50 + wix && Y > 250 + wiy && Y < 280 + wiy)
       {
        P.gold += I[M[isel].type].price * B[wb].sratio;

        // Shop add
        for (int i = 1; i <= 40; i++)
           {
            if (B[wb].items[i] == M[isel].type) // Already is
               {
                B[wb].q[i]++;
                i = 45;
               }
            else if (B[wb].items[i] == 0) // Empty space
               {
                B[wb].items[i] = M[isel].type;
                i = 45;
               }
           }

        // Remove from inventory
        if (M[isel].q > 0)M[isel].q--;        // More than one
        else for (int i = isel; i <= 50; i++) // Not
           {
            M[i].type = M[i + 1].type;
            M[i].slot = M[i + 1].slot;
            M[i].equip = M[i + 1].equip;
            M[i].q = M[i + 1].q;
           }
       }
   }

// Selling whole stack

if (wi == 1 && wb > 0 && shift == 1 && isel > 0)
   {
    if (X > 20 + wix && X < 50 + wix && Y > 250 + wiy && Y < 280 + wiy)
       {
        P.gold += I[M[isel].type].price * B[wb].sratio * (M[isel].q + 1);

        // Shop add
        for (int i = 1; i <= 40; i++)
           {
            if (B[wb].items[i] == M[isel].type) // Already is
               {
                B[wb].q[i] += M[isel].q + 1;
                i = 45;
               }
            else if (B[wb].items[i] == 0) // Empty space
               {
                B[wb].items[i] = M[isel].type;
                B[wb].q[i] = M[isel].q;
                i = 45;
               }
           }

        // Remove from inventory
        for (int i = isel; i <= 50; i++)
           {
            M[i].type = M[i + 1].type;
            M[i].slot = M[i + 1].slot;
            M[i].equip = M[i + 1].equip;
            M[i].q = M[i + 1].q;
           }
       }
   }

// Destroying items

if (wi == 1 && wb == 0 && isel > 0)
   {
    if (X > 20 + wix && X < 50 + wix && Y > 250 + wiy && Y < 280 + wiy)
       {
        // Remove from inventory
        if (M[isel].q > 0)M[isel].q--;        // More than one
        else for (int i = isel; i <= 50; i++) // Not
           {
            M[i].type = M[i + 1].type;
            M[i].slot = M[i + 1].slot;
            M[i].equip = M[i + 1].equip;
            M[i].q = M[i + 1].q;
           }
       }
   }


isel = 0;
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

  case VK_CONTROL:
     control ^= 1;
  break;

  case 'O':
     options ^= 1;
     if (BI->Width == Form1->ClientWidth && BI->Height == Form1->ClientHeight){BI->Width = 640; BI->Height = 480;}
     else if (BI->Width == 1280 && BI->Height == 720){BI->Width = Form1->ClientWidth; BI->Height = Form1->ClientHeight;}
     else if (BI->Width == 1024 && BI->Height == 768){BI->Width = 1280; BI->Height = 720;}
     else if (BI->Width == 800 && BI->Height == 600){BI->Width = 1024; BI->Height = 768;}
     else if (BI->Width == 640 && BI->Height == 480){BI->Width = 800; BI->Height = 600;}
  break;

  case VK_SPACE:
     space = 1;
     qsnums[1] = 1;
  break;

  case 'C':
     wstats ^= 1;
  break;

  case 'P':
     if (Timer1->Interval == 5)Timer1->Interval = 2;
     else if (Timer1->Interval == 2)Timer1->Interval = 1;
     else if (Timer1->Interval == 1)Timer1->Interval = 60;
     else Timer1->Interval -= 5;
  break;

  case 'I':
     wi ^= 1;
  break;

  case 'B':
     wb ^= 1;
  break;

  case VK_UP:
  case 'W':
     wasd[1] = 1;
  break;

  case VK_LEFT:
  case 'A':
     wasd[2] = 1;
  break;

  case VK_DOWN:
  case 'S':
     wasd[3] = 1;
  break;

  case VK_RIGHT:
  case 'D':
     wasd[4] = 1;
  break;

  case '1':
     qsnums[1] = 1;
  break;

  case '2':
     qsnums[2] = 1;
  break;

  case '3':
     qsnums[3] = 1;
  break;

  case '4':
     qsnums[4] = 1;
  break;

  case '5':
     qsnums[5] = 1;
  break;

  case '6':
     qsnums[6] = 1;
  break;

  case '7':
     qsnums[7] = 1;
  break;

  case '8':
     qsnums[8] = 1;
  break;
 }
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
     qsnums[1] = 0;
  break;

  case VK_UP:
  case 'W':
     wasd[1] = 0;
     if (valy < 0)valy = 0;
  break;

  case VK_LEFT:
  case 'A':
     wasd[2] = 0;
     if (valx < 0)valx = 0;
  break;

  case VK_DOWN:
  case 'S':
     wasd[3] = 0;
     if (valy > 0)valy = 0;
  break;

  case VK_RIGHT:
  case 'D':
     wasd[4] = 0;
     if (valx > 0)valx = 0;
  break;

  case '1':
     qsnums[1] = 0;
  break;

  case '2':
     qsnums[2] = 0;
  break;

  case '3':
     qsnums[3] = 0;
  break;

  case '4':
     qsnums[4] = 0;
  break;

  case '5':
     qsnums[5] = 0;
  break;

  case '6':
     qsnums[6] = 0;
  break;

  case '7':
     qsnums[7] = 0;
  break;

  case '8':
     qsnums[8] = 0;
  break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{

// Sets the values and where are you

for (int i = 1; i <= ennumr; i++)
{
if (E[i].dead == 0 && EnCoor[i][1] < Form1->ClientWidth + 200 && EnCoor[i][1] > -200 && EnCoor[i][2] < Form1->ClientHeight + 200 && EnCoor[i][2] > -200)
{
ent[1][i] = PLx + 13 - (EnCoor[i][1] + EnCoor[i][3]) / 2;
ent[2][i] = PLy + 36 - (EnCoor[i][4] - 12);

if (ent[1][i] == 0)ent[1][i] = 1;
if (ent[2][i] == 0)ent[2][i] = 1;

if (ent[1][i] < 0)ent[1][i] = - ent[1][i];
if (ent[2][i] < 0)ent[2][i] = - ent[2][i];

// Facing

if (E[i].action == 1 || E[i].Range <= E[i].sight & E[i].busy == 0 & E[i].action == 0)
   {
    if (ent[1][i] > ent[2][i] && PLx + 13 > (EnCoor[i][1] + EnCoor[i][3]) / 2) enface[i] = 13;
    if (ent[1][i] > ent[2][i] && PLx + 13 < (EnCoor[i][1] + EnCoor[i][3]) / 2) enface[i] = 5;
    if (ent[1][i] < ent[2][i] && PLy + 38 > EnCoor[i][4]) enface[i] = 9;
    if (ent[1][i] < ent[2][i] && PLy + 38 < EnCoor[i][4]) enface[i] = 1;
   }

// Attacks you

E[i].num -= 1;
if (E[i].Range <= 40 && E[i].num <= 0)
  {
   E[i].num = 15;

   gotdem = 0;
   gotdem = E[i].att - P.totdef;
   if (gotdem < -0.6 * E[i].att) gotdem = -0.6 * E[i].att;
   gotdem = ((gotdem + E[i].att) / (3 * E[i].att)) * E[i].demage;

    eskanim[0] = 1;
    eskanim[1] = PLx - 20;
    eskanim[2] = PLy - 15;
    eskanim[3] = 1;
    eskanim[4] = 0;

   P.hp -= gotdem;
   P.staregen -= gotdem * 0.3;
   //sndPlaySound("Utopia Default.wav", SND_ASYNC | SND_FILENAME);
   //sndPlaySound("Hurt.ogg", SND_ASYNC | SND_FILENAME);
  }

// You attack him

for (int j = 1; j <= 19; j++)
    if (S[j].atk >= 1 && S[j].hit == 0 && S[j].demage > 0)
       {
        S[j].Range = sqrt ( ((EnCoor[i][1] + EnCoor[i][3]) / 2 - (S[j].x + Skill[j][S[j].face]->Width / 2)) * ((EnCoor[i][1] + EnCoor[i][3]) / 2 - (S[j].x + Skill[j][S[j].face]->Width / 2)) + (EnCoor[i][4] - 30 - (S[j].y + Skill[j][S[j].face]->Height / 2)) * (EnCoor[i][4] - 30 - (S[j].y + Skill[j][S[j].face]->Height / 2)) );
        if (S[j].Range < Skill[j][S[j].face]->Width / 4 + Skill[j][S[j].face]->Height / 4 + 15)
           {
            givedem = 0;
            givedem = P.totatt - E[i].def;
            if (givedem < -0.6 * P.totatt) givedem = -0.6 * P.totatt;
            givedem = ((givedem + P.totatt) / (2 * P.totatt)) * (P.totdemage * S[j].demage);

            Memo1->Lines->Add(FloatToStr(givedem));

            E[i].hp -= givedem;
            S[j].hit = 1;
           }
       }

// Checks if you killed sth

if (E[i].hp <= 0 && E[i].dead != 1)
   {
   // S.hit = 0;
    deathanim[0] = 1;
    deathanim[1] = EnCoor[i][1];
    deathanim[2] = EnCoor[i][2] - 40;
    deathanim[3] = 1;
    deathanim[4] = 0;

    E[i].dead = 1;
    E[i].timer = 800; // ~30 sec

    // Exp & Gold

    float t;
    int t2;
    t = 1 + (EnCoor[i][5] - P.lvl) / 10;

    if (t < 0.5) t = 0.5;
    if (t > 2) t = 2;

    P.exp += (rand()%(E[i].exp) + E[i].exp) * t;
    P.gold += (rand()%(E[i].gold) + E[i].gold) * t;
    P.hp += E[i].hpmax / 20;

    // Add item

    for (int j = 1; j <= 199; j++)
        if (E[i].item[j] > 1)
           {
            t2 = rand()%(E[i].item[j]) + 1;
            if (t2 <= 10)
               {
                iadd = j;
                AddItemClick(Sender);
               }
           }
   }

// Enemys AI =================================================================================

// Checks if you're close enough

E[i].Range = sqrt ((PLx + 13 - (EnCoor[i][1] + EnCoor[i][3]) / 2) * (PLx + 13 - (EnCoor[i][1] + EnCoor[i][3]) / 2) + (PLy + 36 - EnCoor[i][4] + 12) * (PLy + 36 - EnCoor[i][4] + 12));

if (E[i].Range <= E[i].sight / 2 && E[i].action == 0) E[i].action = 1;
if (E[i].Range >= E[i].sight && E[i].action == 1) {E[i].action = 0; envalx[i] = 0; envaly[i] = 0;}

// Passive, action = 0;

E[i].wait--;
if (E[i].action == 0 && E[i].wait < 0 && E[i].busy == 1)
   {
    E[i].wait = rand()%(250) + 50;
    E[i].busy = 0;
    envalx[i] = 0;
    envaly[i] = 0;
   }
if (E[i].action == 0 && E[i].wait < 0 && E[i].busy == 0)
   {
    E[i].tempf = rand()%(99) + 1;
    E[i].tempxy = rand()%(200) + 50;

    E[i].wait = E[i].tempxy / (E[i].speed / 5);
    E[i].busy = 1;

    if (E[i].tempf < 25)                           {envaly[i] = -E[i].speed / 5; enface[i] = 1;}
    else if (E[i].tempf < 50 && E[i].tempf >= 25)  {envalx[i] = -E[i].speed / 5; enface[i] = 5;}
    else if (E[i].tempf < 75 && E[i].tempf >= 50)  {envaly[i] = E[i].speed / 5; enface[i] = 9;}
    else                                           {envalx[i] = E[i].speed / 5; enface[i] = 13;}
   }

// Chase, action = 1;

if (E[i].Range <= 38){envalx[i] = 0; envaly[i] = 0;}
if (E[i].action == 1 && E[i].Range >= 38)
{
    E[i].busy == 1;

    if (ent[1][i] > ent[2][i]) ent[3][i] = ent[1][i] / ent[2][i];
    else ent[3][i] = ent[2][i] / ent[1][i];

    percent = E[i].speed / 5;
    if (ent[3][i] <= 4) percent = E[i].speed / 5 * 1.05;
    if (ent[3][i] <= 2.5) percent = E[i].speed / 5 * 1.1;
    if (ent[3][i] <= 2) percent = E[i].speed / 5 * 1.2;
    if (ent[3][i] <= 1.5) percent = E[i].speed / 5 * 1.3;

    if (ent[1][i] > ent[2][i])
       {
        envalx[i] = ((percent / (ent[3][i] + 1))) * ent[3][i];
        if (((percent / (ent[3][i] + 1))) * ent[3][i] > percent - 0.6) envalx[i] = percent;
        envaly[i] = percent - envalx[i];
       } else
       {
        envaly[i] = ((percent / (ent[3][i] + 1))) * ent[3][i];
        if (((percent / (ent[3][i] + 1))) * ent[3][i] > percent - 0.6) envaly[i] = percent;
        envalx[i] = percent - envaly[i];
       }

    if (PLx + 13 < (EnCoor[i][1] + EnCoor[i][3]) / 2) envalx[i] = -envalx[i];
    if (PLy + 36 < EnCoor[i][4] - 12) envaly[i] = -envaly[i];

} //

// Walls ##########################################

for (int j = 1; j <= wallnum; j++)
   {
    // Right       Wall <----- En

    if (EnCoor[i][1] - 4 < wall[j][3] && EnCoor[i][1] - 4 > wall[j][3] - 10 && EnCoor[i][2] < wall[j][4] && EnCoor[i][4] > wall[j][2])
       {
        EnCoor[i][1] = wall[j][3] + 2;
        EnCoor[i][3] = EnCoor[i][1] + En[EnCoor[i][5]][1]->Width;

        if (E[i].action == 1 && EnCoor[i][1] - 30 > PLx)
           {
            E[i].action = 2;
            E[i].t = 1;
            E[i].obs[1] = 0;E[i].obs[2] = 0;E[i].obs[3] = 0;E[i].obs[4] = 0;

            // Searches where are no walls to go through
            for (int h = EnCoor[i][2]; h >= wall[j][2] - 30; h -= 5)
                for (int k = 1; k <= wallnum; k++)
                    if (EnCoor[i][1] + 15 > wall[k][1] && EnCoor[i][1] + 15 < wall[k][3] && h > wall[k][2] && h < wall[k][4])
                        E[i].obs[1] = 1;

            for (int h = EnCoor[i][2]; h <= wall[j][4] + 30; h += 5)
                for (int k = 1; k <= wallnum; k++)
                    if (EnCoor[i][1] + 15 > wall[k][1] && EnCoor[i][1] + 15 < wall[k][3] && h > wall[k][2] && h < wall[k][4])
                        E[i].obs[3] = 1;

            // sets valx & valy
            envalx[i] = 0;
            envaly[i] = 0;

            // both clear
             if (E[i].obs[1] == 0 && E[i].obs[3] == 0)
                {
                 if (EnCoor[i][2] - wall[j][2] + PLy - wall[j][2] < wall[j][4] - EnCoor[i][4] + wall[j][4] - PLy)
                     E[i].obs[3] = 1;
                 else E[i].obs[1] = 1;
                }

            // Up clear
            if (E[i].obs[1] == 0)
               {
                envaly[i] = -E[i].speed / 5;
                enface[i] = 1;
                E[i].wait = (EnCoor[i][4] - wall[j][2] + 5) / (E[i].speed / 5);
               }

            // Down clear
            if (E[i].obs[3] == 0)
               {
                envaly[i] = E[i].speed / 5;
                enface[i] = 9;
                E[i].wait = (wall[j][4] + 5 - EnCoor[i][2]) / (E[i].speed / 5);
               }

            // No clear
            if (E[i].obs[1] == 1 && E[i].obs[3] == 1)
               {
                envalx[i] = E[i].speed / 5;
                enface[i] = 13;
                E[i].wait = 50;
               }
           }
       }


    // Left          En -----> Wall

    if (EnCoor[i][3] + 4 < wall[j][1] + 10 && EnCoor[i][3] + 4 > wall[j][1] && EnCoor[i][2] < wall[j][4] && EnCoor[i][4] > wall[j][2])
       {
        EnCoor[i][3] = wall[j][1] - 2;
        EnCoor[i][1] = EnCoor[i][3] - En[EnCoor[i][5]][1]->Width;

        if (E[i].action == 1 && EnCoor[i][1] + 40 < PLx)
           {
            E[i].action = 2;
            E[i].t = 1;
            E[i].obs[1] = 0;E[i].obs[2] = 0;E[i].obs[3] = 0;E[i].obs[4] = 0;

            // Searches where are no walls to go through
            for (int h = EnCoor[i][2]; h >= wall[j][2] - 30; h -= 5)
                for (int k = 1; k <= wallnum; k++)
                    if (EnCoor[i][1] + 15 > wall[k][1] && EnCoor[i][1] + 15 < wall[k][3] && h > wall[k][2] && h < wall[k][4])
                        E[i].obs[1] = 1;

            for (int h = EnCoor[i][2]; h <= wall[j][4] + 30; h += 5)
                for (int k = 1; k <= wallnum; k++)
                    if (EnCoor[i][1] + 15 > wall[k][1] && EnCoor[i][1] + 15 < wall[k][3] && h > wall[k][2] && h < wall[k][4])
                        E[i].obs[3] = 1;

            // sets valx & valy
            envalx[i] = 0;
            envaly[i] = 0;

            // both clear
             if (E[i].obs[1] == 0 && E[i].obs[3] == 0)
                {
                 if (EnCoor[i][2] - wall[j][2] + PLy - wall[j][2] < wall[j][4] - EnCoor[i][4] + wall[j][4] - PLy)
                     E[i].obs[3] = 1;
                 else E[i].obs[1] = 1;
                }

            // Up clear
            if (E[i].obs[1] == 0)
               {
                envaly[i] = -E[i].speed / 5;
                enface[i] = 1;
                E[i].wait = (EnCoor[i][4] - wall[j][2] + 5) / (E[i].speed / 5);
               }

            // Down clear
            if (E[i].obs[3] == 0)
               {
                envaly[i] = E[i].speed / 5;
                enface[i] = 9;
                E[i].wait = (wall[j][4] + 5 - EnCoor[i][2]) / (E[i].speed / 5);
               }

            // No clear
            if (E[i].obs[1] == 1 && E[i].obs[3] == 1)
               {
                envalx[i] = -E[i].speed / 5;
                enface[i] = 5;
                E[i].wait = 50;
               }
           }
       }

    // Down     ^

    if (EnCoor[i][2] - 4 < wall[j][4] && EnCoor[i][2] - 4 > wall[j][4] - 10 && EnCoor[i][1] < wall[j][3] && EnCoor[i][3] > wall[j][1])
       {
        EnCoor[i][2] = wall[j][4] + 2;
        EnCoor[i][4] = EnCoor[i][2] + 25;

        if (E[i].action == 1 && EnCoor[i][2] - 15 > PLy + 42)
           {
            E[i].action = 2;
            E[i].t = 2;
            E[i].obs[1] = 0;E[i].obs[2] = 0;E[i].obs[3] = 0;E[i].obs[4] = 0;

            // Searches where are no walls to go through
            for (int h = EnCoor[i][1]; h >= wall[j][1] - 40; h -= 5)
                for (int k = 1; k <= wallnum; k++)
                    if (EnCoor[i][2] + 10 > wall[k][2] && EnCoor[i][2] + 10 < wall[k][4] && h > wall[k][1] && h < wall[k][3])
                        E[i].obs[2] = 1;

            for (int h = EnCoor[i][1]; h <= wall[j][3] + 40; h += 5)
                for (int k = 1; k <= wallnum; k++)
                    if (EnCoor[i][2] + 10 > wall[k][2] && EnCoor[i][2] + 10 < wall[k][4] && h > wall[k][1] && h < wall[k][3])
                        E[i].obs[4] = 1;

            // sets valx & valy
            envalx[i] = 0;
            envaly[i] = 0;

            // both clear
             if (E[i].obs[2] == 0 && E[i].obs[4] == 0)
                {
                 if (EnCoor[i][1] - wall[j][1] + PLx - wall[j][1] < wall[j][3] - EnCoor[i][3] + wall[j][3] - PLx)
                     E[i].obs[4] = 1;
                 else E[i].obs[2] = 1;
                }

            // Left clear
            if (E[i].obs[2] == 0)
               {
                envalx[i] = -E[i].speed / 5;
                enface[i] = 5;
                E[i].wait = (EnCoor[i][3] - wall[j][1] + 5) / (E[i].speed / 5);
               }

            // Right clear
            if (E[i].obs[4] == 0)
               {
                envalx[i] = E[i].speed / 5;
                enface[i] = 13;
                E[i].wait = (wall[j][3] + 5 - EnCoor[i][1]) / (E[i].speed / 5);
               }

            // No clear
            if (E[i].obs[2] == 1 && E[i].obs[4] == 1)
               {
                envaly[i] = E[i].speed / 5;
                enface[i] = 9;
                E[i].wait = 50;
               }
           }
       }

    // Top      v
    if (EnCoor[i][4] + 4 < wall[j][2] + 10 && EnCoor[i][4] + 4 > wall[j][2] && EnCoor[i][1] < wall[j][3] && EnCoor[i][3] > wall[j][1])
       {
        EnCoor[i][4] = wall[j][2] - 2;
        EnCoor[i][2] = EnCoor[i][4] - 25;

        if (E[i].action == 1 && EnCoor[i][2] + 15 < PLy)
           {
            E[i].action = 2;
            E[i].t = 2;
            E[i].obs[1] = 0;E[i].obs[2] = 0;E[i].obs[3] = 0;E[i].obs[4] = 0;

            // Searches where are no walls to go through
            for (int h = EnCoor[i][1]; h >= wall[j][1] - 40; h -= 5)
                for (int k = 1; k <= wallnum; k++)
                    if (EnCoor[i][2] + 10 > wall[k][2] && EnCoor[i][2] + 10 < wall[k][4] && h > wall[k][1] && h < wall[k][3])
                        E[i].obs[2] = 1;

            for (int h = EnCoor[i][1]; h <= wall[j][3] + 40; h += 5)
                for (int k = 1; k <= wallnum; k++)
                    if (EnCoor[i][2] + 10 > wall[k][2] && EnCoor[i][2] + 10 < wall[k][4] && h > wall[k][1] && h < wall[k][3])
                        E[i].obs[4] = 1;

            // sets valx & valy
            envalx[i] = 0;
            envaly[i] = 0;

            // both clear
             if (E[i].obs[2] == 0 && E[i].obs[4] == 0)
                {
                 if (EnCoor[i][1] - wall[j][1] + PLx - wall[j][1] < wall[j][3] - EnCoor[i][3] + wall[j][3] - PLx)
                     E[i].obs[4] = 1;
                 else E[i].obs[2] = 1;
                }

            // Left clear
            if (E[i].obs[2] == 0)
               {
                envalx[i] = -E[i].speed / 5;
                enface[i] = 5;
                E[i].wait = (EnCoor[i][3] - wall[j][1] + 5) / (E[i].speed / 5);
               }

            // Right clear
            if (E[i].obs[4] == 0)
               {
                envalx[i] = E[i].speed / 5;
                enface[i] = 13;
                E[i].wait = (wall[j][3] + 5 - EnCoor[i][1]) / (E[i].speed / 5);
               }

            // No clear
            if (E[i].obs[2] == 1 && E[i].obs[4] == 1)
               {
                envaly[i] = -E[i].speed / 5;
                enface[i] = 1;
                E[i].wait = 50;
               }
           }
       }
   }

if (E[i].action == 2 && E[i].wait < 0)
   {
    envalx[i] = 0;
    envaly[i] = 0;
    E[i].action = 3;

    // Top & Down
    if (E[i].obs[1] == 0 & E[i].t == 1 || E[i].obs[3] == 0 & E[i].t == 1)
       {
        if (EnCoor[i][1] < PLx) {envalx[i] = E[i].speed / 5; enface[i] = 13;}
        else {envalx[i] = -E[i].speed / 5; enface[i] = 5;}
        envaly[i] = 0;
        E[i].wait = 50 / (E[i].speed / 5);
       }
    if (E[i].obs[1] == 1 && E[i].obs[3] == 1)E[i].action = 0;

    // Left & Right
    if (E[i].obs[2] == 0 & E[i].t == 2 || E[i].obs[4] == 0 & E[i].t == 2)
       {
        if (EnCoor[i][2] < PLy) {envaly[i] = E[i].speed / 5; enface[i] = 9;}
        else {envaly[i] = -E[i].speed / 5; enface[i] = 1;}
        envalx[i] = 0;
        E[i].wait = 50 / (E[i].speed / 5);
       }
    if (E[i].obs[2] == 1 && E[i].obs[4] == 1)E[i].action = 0;
   }

if (E[i].action == 3 && E[i].wait < 0)E[i].action = 1;


// Hitting another enemy

for (int j = 1; j <= ennumr; j++) if (E[j].dead == 0 && envalx[i] != 0 | envaly[i] != 0)
   {
    // Right       Wall <----- En
    if (EnCoor[i][1] - 4 <EnCoor[j][3] && EnCoor[i][1] - 4 > EnCoor[j][3] - 10 && EnCoor[i][2] < EnCoor[j][4] && EnCoor[i][4] > EnCoor[j][2])
       {
        if (envalx[i] < 0)
           {
            envalx[i] = 0;
            E[i].tempf = rand()%(99) + 1;
            if (E[i].tempf <= 50){envaly[i] = -E[i].speed / 5; enface[i] = 1;}
            if (E[i].tempf > 50){envaly[i] = E[i].speed / 5; enface[i] = 9;}
            E[i].wait = 35 / (E[i].speed / 5);
            E[i].action = 4;
           }
        if (envalx[j] == 0 && envaly[j] == 0)
           {
            EnCoor[i][1] = EnCoor[j][3] + 2;
            EnCoor[i][3] = EnCoor[i][1] + En[EnCoor[i][5]][1]->Width;
           }
       }
    // Left          En -----> Wall
    else if (EnCoor[i][3] + 4 < EnCoor[j][1] + 10 && EnCoor[i][3] + 4 > EnCoor[j][1] && EnCoor[i][2] < EnCoor[j][4] && EnCoor[i][4] > EnCoor[j][2])
       {
        if (envalx[i] > 0)
           {
            envalx[i] = 0;
            E[i].tempf = rand()%(99) + 1;
            if (E[i].tempf <= 50){envaly[i] = -E[i].speed / 5; enface[i] = 1;}
            if (E[i].tempf > 50){envaly[i] = E[i].speed / 5; enface[i] = 9;}
            E[i].wait = 35 / (E[i].speed / 5);
            E[i].action = 4;
           }
        if (envalx[j] == 0 && envaly[j] == 0)
           {
            EnCoor[i][3] = EnCoor[j][1] - 2;
            EnCoor[i][1] = EnCoor[i][3] - En[EnCoor[i][5]][1]->Width;
           }
       }
    // Down     ^
    else if (EnCoor[i][2] - 4 < EnCoor[j][4] && EnCoor[i][2] - 4 > EnCoor[j][4] - 10 && EnCoor[i][1] < EnCoor[j][3] && EnCoor[i][3] > EnCoor[j][1])
       {
        if (envaly[i] < 0)
           {
            envaly[i] = 0;
            E[i].tempf = rand()%(99) + 1;
            if (E[i].tempf <= 50){envalx[i] = -E[i].speed / 5; enface[i] = 5;}
            if (E[i].tempf > 50){envalx[i] = E[i].speed / 5; enface[i] = 13;}
            E[i].wait = 35 / (E[i].speed / 5);
            E[i].action = 4;
           }
        if (envalx[j] == 0 && envaly[j] == 0)
           {
            EnCoor[i][2] = EnCoor[j][4] + 2;
            EnCoor[i][4] = EnCoor[i][2] + 25;
           }
       }
    // Top      v
    else if (EnCoor[i][4] + 4 < EnCoor[j][2] + 10 && EnCoor[i][4] + 4 > EnCoor[j][2] && EnCoor[i][1] < EnCoor[j][3] && EnCoor[i][3] > EnCoor[j][1])
       {
        if (envaly[i] > 0)
           {
            envaly[i] = 0;
            E[i].tempf = rand()%(99) + 1;
            if (E[i].tempf <= 50){envalx[i] = -E[i].speed / 5; enface[i] = 5;}
            if (E[i].tempf > 50){envalx[i] = E[i].speed / 5; enface[i] = 13;}
            E[i].wait = 35 / (E[i].speed / 5);
            E[i].action = 4;
           }
        if (envalx[j] == 0 && envaly[j] == 0)
           {
            EnCoor[i][4] = EnCoor[j][2] - 2;
            EnCoor[i][2] = EnCoor[i][4] - 25;
           }
       }
   }

if (E[i].action == 4 && E[i].wait < 0)
   {
    envalx[i] = 0;
    envaly[i] = 0;

    if (enface[i] == 1 || enface[i] == 9)
       {
        if (PLx <= EnCoor[i][1])
           {
            envalx[i] = -E[i].speed / 5;
            enface[i] = 5;
           }
        if (PLx > EnCoor[i][1])
           {
            envalx[i] = E[i].speed / 5;
            enface[i] = 13;
           }
       }
    else if (enface[i] == 5 || enface[i] == 13)
       {
        if (PLy + 35 <= EnCoor[i][4])
           {
            envaly[i] = -E[i].speed / 5;
            enface[i] = 1;
           }
        if (PLy + 35 > EnCoor[i][4])
           {
            envaly[i] = E[i].speed / 5;
            enface[i] = 9;
           }
       }

    E[i].wait = 35 / (E[i].speed / 5);
    E[i].action = 5;
 }

if (E[i].action == 5 && E[i].wait < 0 && E[i].Range <= E[i].sight)E[i].action = 1;
if (E[i].action == 5 && E[i].wait < 0 && E[i].Range > E[i].sight)E[i].action = 0;

// AI done!!!!!!!!!!!!!!!!!!!!!!!!!

//  Draws new en position *******************

EnCoor[i][1] += envalx[i];
EnCoor[i][2] += envaly[i];
EnCoor[i][3] += envalx[i];
EnCoor[i][4] += envaly[i];



} // if dead == 0

if (E[i].dead == 1)
{
E[i].timer--;
if (E[i].timer <= 0)
   {
    E[i].dead = 0;
    EnCoor[i][1] = E[i].spawnCoor[1] + mx;
    EnCoor[i][2] = E[i].spawnCoor[2] + my;
    EnCoor[i][3] = E[i].spawnCoor[3] + mx;
    EnCoor[i][4] = E[i].spawnCoor[4] + my;
    envalx[i] = 0;
    envaly[i] = 0;
    E[i].hp = E[i].hpmax;
    E[i].action = 0;
    E[i].wait = 0;
    E[i].busy = 1;
    E[i].Range = 1000;
   }

} // if dead == 1
} // For ennumr
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DrawClick(TObject *Sender)
{

BI->Canvas->Draw(backx - 250, backy - 250, Back);


for (int g = -20; g <= BI->Height + 800; g += 2)
{

// Enemies
for(int i = 1; i <= ennumr; i++)
    if (enface[i] > 0 && enface[i] < 17 && E[i].dead == 0 && EnCoor[i][4] + 8 <= g && EnCoor[i][4] + 8 > g - 2 && EnCoor[i][1] > -200 && EnCoor[i][1] < BI->Width + 200)
        BI->Canvas->Draw(EnCoor[i][1], EnCoor[i][2] - En[EnCoor[i][5]][9]->Height + 25, En[ET[EnCoor[i][5]].icon][enface[i] + enanim[i]]);

// You

if (PLy + 42 <= g && PLy + 42 > g - 2)
    BI->Canvas->Draw(PLx, PLy, PL[facing + anim]);

// Walls

for(int i = 1; i <= wallnum; i++)
if (wall[i][4] <= g && wall[i][4] > g - 2 && wall[i][3] > -200 && wall[i][1] < BI->Width + 200) // For all walls
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
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 24, WallAnim[wall[i][5]][wallanim]);

    if (wall[i][5] == 30)  // Fire with anim
        BI->Canvas->Draw(wall[i][1], wall[i][2] - 36, WallAnim[wall[i][5]][wallanim]);

    if (wall[i][5] == 31)  // Fire pit with anim
        BI->Canvas->Draw(wall[i][1], wall[i][2], WallAnim[wall[i][5]][wallanim]);
   }
}


// Death

if (deathanim[0] == 1) BI->Canvas->Draw(deathanim[1], deathanim[2], Death[deathanim[3]]);

// Esk anim

if (eskanim[0] == 1) BI->Canvas->Draw(eskanim[1], eskanim[2], ESk[eskanim[3]]);

// Attacks

for (int i = 1; i <= 19; i++)
    if (S[i].atk == 2) BI->Canvas->Draw(S[i].x, S[i].y, Skill[i][S[i].face]);

// Enemy hp bar

BI->Canvas->Pen->Width = 1;
for(int i = 1; i <= ennumr; i++)
    if (E[i].action >= 1 && E[i].dead == 0 && E[i].Range <= E[i].sight)
       {
        BI->Canvas->Brush->Color = clWhite;
        BI->Canvas->Rectangle((EnCoor[i][1] + EnCoor[i][3]) / 2 - 25, EnCoor[i][4] - En[EnCoor[i][5]][1]->Height - 16, (EnCoor[i][1] + EnCoor[i][3]) / 2 + 25, EnCoor[i][4] - En[EnCoor[i][5]][1]->Height - 10);
        BI->Canvas->Brush->Color = clRed;
        BI->Canvas->Rectangle((EnCoor[i][1] + EnCoor[i][3]) / 2 - 25, EnCoor[i][4] - En[EnCoor[i][5]][1]->Height - 16, (EnCoor[i][1] + EnCoor[i][3]) / 2 - 25 + (E[i].hp + 0.1) / E[i].hpmax * 50, EnCoor[i][4] - En[EnCoor[i][5]][1]->Height - 10);
       }

// MiniMap
                /*
Rect.Top = 0;
Rect.Left = Form1->ClientWidth - 300;
Rect.Bottom = 200;
Rect.Right = Form1->ClientWidth;

BI->Canvas->Pen->Color = clBlack;
BI->Canvas->Pen->Width = 2;
BI->Canvas->RoundRect(Form1->ClientWidth - 302, -2, Form1->ClientWidth + 2, 202, 5, 5);
BI->Canvas->StretchDraw(Rect, BI);
                 */


// Stats window ==============================================================================

if (wstats == 1)
   {
    WS->Canvas->Brush->Color = clSilver;
    WS->Canvas->Pen->Width = 2;
    WS->Canvas->RoundRect(5, 5, 395, 295, 50, 50);
    WS->Canvas->TextOutA(15, 20, "  GMan Level   " + IntToStr(P.lvl));
    WS->Canvas->TextOutA(15, 45, "    Attack   " + IntToStr(P.totatt));
    WS->Canvas->TextOutA(15, 70, "    Defence   " + IntToStr(P.totdef));
    WS->Canvas->TextOutA(15, 95, "    Health   " + IntToStr(P.hp) + " / " + IntToStr(P.tothp));
    WS->Canvas->TextOutA(15, 120, "    Mana   " + IntToStr(P.mp) + " / " + IntToStr(P.totmp));
    WS->Canvas->TextOutA(15, 145, "    Stamina   " + IntToStr(P.sta) + " / " + IntToStr(P.totsta));
    WS->Canvas->TextOutA(15, 180, "    Demage   " + IntToStr(P.totdemage));
    WS->Canvas->TextOutA(15, 215, "    Stats points   " + IntToStr(P.statsp));
    WS->Canvas->TextOutA(15, 235, "    Skill points   " + IntToStr(P.skillp));
    WS->Canvas->TextOutA(15, 255, "    Expierence   " + IntToStr(P.exp) + " / " + IntToStr(P.expmax));

    if (P.statsp > 0)
       {
        for (int i = 42; i <= 145; i += 25)
            WS->Canvas->Draw(130, i, Plus);
        WS->Canvas->TextOutA(152, 45, "+1");
        WS->Canvas->TextOutA(152, 70, "+1");
        WS->Canvas->TextOutA(152, 95, "+5");
        WS->Canvas->TextOutA(152, 120, "+3");
        WS->Canvas->TextOutA(152, 145, "+3");
       }

    tx = 190; ty = 20;
    for (int i = 1; i <= 12; i++)
       {
        WS->Canvas->RoundRect(tx, ty, tx + 40, ty + 40, 5, 5);
        WS->Canvas->Draw(tx + 2, ty + 2, Skill[i][0]);
        WS->Canvas->TextOutA(tx + 10,  ty + 45, "Lvl " + IntToStr(S[i].lvl));
        tx += 55;
        if (i == 3 || i == 6 || i == 9){tx = 190; ty += 70;}
       }

    BI->Canvas->Draw(wsx, wsy, WS);
   }

// Inventory window  |||||||||||||||||||||||||||||||||||||||||||||||||||||||

if (wi == 1)
   {
    WI->Canvas->Brush->Color = clSilver;
    WI->Canvas->Pen->Width = 2;
    WI->Canvas->RoundRect(5, 5, 395, 295, 50, 50);

    WI->Canvas->TextOutA(20, 20, "Inventory");

    // Equip

    tx = 20; ty = 50;
    for (int i = 1; i <= 9; i++)
       {
        WI->Canvas->RoundRect(tx, ty, tx + 30, ty + 30, 5, 5);

        for (int j = 1; j <= 199; j++)
            if (M[j].equip == 1 && I[M[j].type].type == i && isel != j)
                WI->Canvas->Draw(tx + 2, ty + 2, Items[I[M[j].type].icon]);

        tx += 35;
        if (i == 3 || i == 6 || i == 9){tx = 20; ty += 35;}
       }

    // Stocked items

    tx = 160; ty = 20;
    for (int i = 1; i <= 36; i++)
       {
        WI->Canvas->RoundRect(tx, ty, tx + 30, ty + 30, 5, 5);

        for (int j = 1; j <= 199; j++)
            if (M[j].slot == i && isel != j)
               {
                WI->Canvas->Draw(tx + 2, ty + 2, Items[I[M[j].type].icon]);
                if (M[j].q > 0)WI->Canvas->TextOutA(tx + 15, ty + 1, IntToStr(M[j].q + 1));
               }

        tx += 35;
        if (i == 6 || i == 12 || i == 18 || i == 24 || i == 30){tx = 160; ty += 35;}
       }

    // Stats

    ty = 155;

    WI->Canvas->TextOutA(20, ty, I[M[ion].type].name);
    if (I[M[ion].type].lvl > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Level " + IntToStr(I[M[ion].type].lvl));}
    if (I[M[ion].type].att > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Attack " + IntToStr(I[M[ion].type].att));}
    if (I[M[ion].type].demage > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Demage " + IntToStr(I[M[ion].type].demage));}
    if (I[M[ion].type].def > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Defence " + IntToStr(I[M[ion].type].def));}
    if (I[M[ion].type].hp > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Health +" + IntToStr(I[M[ion].type].hp));}
    if (I[M[ion].type].mp > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Mana +" + IntToStr(I[M[ion].type].mp));}
    if (I[M[ion].type].sta > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Stamina +" + IntToStr(I[M[ion].type].sta));}
    if (wb == 0)if (I[M[ion].type].price > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Price " + IntToStr(I[M[ion].type].price) + " G");}
    int t;
    t = I[M[ion].type].price * B[wb].sratio;
    if (wb > 0)if (I[M[ion].type].price > 0){ty += 17; WI->Canvas->TextOutA(20, ty, "Price " + IntToStr(t) + " G");}

    if (isel > 0)
       {
        // Sell

        WI->Canvas->RoundRect(20, 250, 50, 280, 5, 5);
        if (wb > 0)WI->Canvas->TextOutA(55, 255, "Sell?");
        else WI->Canvas->TextOutA(55, 255, "Destroy?");
        // Moving items with mouse

        WI->Canvas->Draw(mx2 - wix - 12, my2 - wiy - 12, Items[I[M[isel].type].icon]);
       }

    BI->Canvas->Draw(wix, wiy, WI);
   }


// Shop window  ____________________________________________________________

if (wb > 0)
   {
    BI->Canvas->Brush->Color = clSilver;
    BI->Canvas->Pen->Width = 2;
    BI->Canvas->RoundRect(BI->Width / 2 - 200, 20, BI->Width / 2 + 200, 220, 50, 50);

    BI->Canvas->TextOutA(BI->Width / 2 - 180, 30, "Store");

    // Stock

    tx = BI->Width / 2 - 95; ty = 30;
    for (int i = 1; i <= 40; i++)
       {
        BI->Canvas->RoundRect(tx, ty, tx + 30, ty + 30, 5, 5);

        if (wbisel != i)
           {
            BI->Canvas->Draw(tx + 2, ty + 2, Items[I[B[wb].items[i]].icon]);
            if (B[wb].q[i] > 0)BI->Canvas->TextOutA(tx + 15, ty + 1, IntToStr(B[wb].q[i] + 1));
           }

        tx += 35;
        if (i == 8 || i == 16 || i == 24 || i == 32){tx = BI->Width / 2 - 95; ty += 35;}
       }

    // Stats

    ty = 55;

    BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, I[B[wb].items[wbion]].name);
    if (I[B[wb].items[wbion]].lvl > 0){ty += 17; BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, "Level " + IntToStr(I[B[wb].items[wbion]].lvl));}
    if (I[B[wb].items[wbion]].att > 0){ty += 17; BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, "Attack " + IntToStr(I[B[wb].items[wbion]].att));}
    if (I[B[wb].items[wbion]].demage > 0){ty += 17; BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, "Demage " + IntToStr(I[B[wb].items[wbion]].demage));}
    if (I[B[wb].items[wbion]].def > 0){ty += 17; BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, "Defence " + IntToStr(I[B[wb].items[wbion]].def));}
    if (I[B[wb].items[wbion]].hp > 0){ty += 17; BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, "Health +" + IntToStr(I[B[wb].items[wbion]].hp));}
    if (I[B[wb].items[wbion]].mp > 0){ty += 17; BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, "Mana +" + IntToStr(I[B[wb].items[wbion]].mp));}
    if (I[B[wb].items[wbion]].sta > 0){ty += 17; BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, "Stamina +" + IntToStr(I[B[wb].items[wbion]].sta));}
    if (I[B[wb].items[wbion]].price > 0){ty += 17; BI->Canvas->TextOutA(BI->Width / 2 - 185, ty, "Price " + IntToStr(I[B[wb].items[wbion]].price) + " G");}

    if (wbisel > 0)
       {
        // Sell

        BI->Canvas->RoundRect(BI->Width / 2 - 180, 170, BI->Width / 2 - 150, 200, 5, 5);
        BI->Canvas->TextOutA(BI->Width / 2 - 140, 177, "Buy?");

        // Moving items with mouse

        BI->Canvas->Draw(mx2 - 12, my2 - 12, Items[I[B[wb].items[wbisel]].icon]);
       }
   }


// Your Exp, HP, MP & STA box & bars

BI->Canvas->Brush->Color = clSilver;
BI->Canvas->Pen->Width = 2;
BI->Canvas->RoundRect(-50, -50, 140, 80, 100, 100);

BI->Canvas->TextOutA(20 , 57, "Level " + IntToStr(P.lvl));

if (P.statsp > 0 || P.skillp > 0)
    BI->Canvas->Draw(60, 54, Plus);


BI->Canvas->Pen->Width = 1;
BI->Canvas->Brush->Color = clWhite;
BI->Canvas->Rectangle(20,10,120,25);
BI->Canvas->Brush->Color = clRed;
BI->Canvas->Rectangle(20,10,20 + (P.hp + 0.1) / P.tothp * 100, 25);

BI->Canvas->Brush->Color = clWhite;
BI->Canvas->Rectangle(20,27,120,37);
BI->Canvas->Brush->Color = clBlue;
BI->Canvas->Rectangle(20,27,20 + (P.mp + 0.1) / P.totmp * 100, 37);

BI->Canvas->Brush->Color = clWhite;
BI->Canvas->Rectangle(20,39,120,44);
BI->Canvas->Brush->Color = clGreen;
BI->Canvas->Rectangle(20,39,20 + (P.sta + 0.1) / P.totsta * 100, 44);

BI->Canvas->Brush->Color = clBlack;
BI->Canvas->Rectangle(20,46,120,51);
BI->Canvas->Brush->Color = clYellow;
BI->Canvas->Rectangle(20,46,20 + (P.exp + 0.1) / P.expmax * 100, 51);

// Gold box

BI->Canvas->Brush->Color = clSilver;
BI->Canvas->Pen->Width = 2;
BI->Canvas->RoundRect(BI->Width - 100, -50, BI->Width + 50, 30, 50, 50);
BI->Canvas->TextOutA(BI->Width - 75, 5, IntToStr(P.gold) + " G");

// Quick skill box ++++++++++++++++++++************+++++++++++++++++++++++++++++++

BI->Canvas->Brush->Color = clSilver;
BI->Canvas->Pen->Width = 2;
BI->Canvas->RoundRect(-25,  BI->Height - 60, 400, BI->Height + 25, 50, 50);

// Draws 8 little boxes

tempdraw = 0;
for (int i = 5; i <= 350; i += 45)
   {
    tempdraw++;
    if (i == 5 + 4 * 45) i += 15;
    BI->Canvas->Brush->Color = clSilver;
    BI->Canvas->RoundRect(i,  BI->Height - 45, i + 40, BI->Height - 5, 5, 5);
    BI->Canvas->TextOutA(i + 15, BI->Height - 30, IntToStr(tempdraw));

    // Draws skill in the boxes

    for (int j = 1; j <= 19; j++)
        if (S[j].quick == tempdraw)
           {

            // Grren or red dots

            if (S[j].mp < P.mp + P.mpregen && S[j].sta < P.sta + P.staregen && S[j].hp < P.hp)
                BI->Canvas->Brush->Color = clLime;
            else BI->Canvas->Brush->Color = clRed;
            BI->Canvas->RoundRect(i + 30, BI->Height - 55, i + 40, BI->Height - 45, 5, 5);

            // Waited bar

            BI->Canvas->Brush->Color = clLime;
            BI->Canvas->RoundRect(i, BI->Height - 55, i + 30, BI->Height - 45, 5, 5);
            BI->Canvas->Brush->Color = clRed;
            if (S[j].waited > 0)BI->Canvas->RoundRect(i + 30 - (S[j].waited * 30 / S[j].wait), BI->Height - 55, i + 30, BI->Height - 45, 5, 5);

            // icons

            BI->Canvas->Draw(i + 2,  BI->Height - 43, Skill[j][0]);
           }
   }

Rect.Top = 0;
Rect.Left = 0;
Rect.Bottom = Form1->ClientHeight;
Rect.Right = Form1->ClientWidth;

BI->Canvas->TextOutA(BI->Width - 13, BI->Height - 13, IntToStr(Timer1->Interval));

Canvas->StretchDraw(Rect, BI);
//Canvas->Draw(0, 0, BI);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
if (valx != 0 || valy != 0)
   {
    anim++;
    if (anim == 4) anim = 0;
   } else anim = 0;

for (int i = 1; i <= ennumr; i++)
   {
    if (envalx[i] != 0 || envaly[i] != 0)
       {
        enanim[i]++;
        if (enanim[i] == 4) enanim[i] = 0;
       } else enanim[i] = 0;
   }

wallanim++;
if (wallanim > 4) wallanim = 1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormResize(TObject *Sender)
{
Memo1->Left = Form1->ClientWidth - 129 - 8;
Memo1->Top = Form1->ClientHeight - 145 - 8;

BI->Width = Form1->ClientWidth;
BI->Height = Form1->ClientHeight;

DrawClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CenterPlayerClick(TObject *Sender)
{

for (int i = 1; i <= ennumr; i++){EnCoor[i][1] -= PLx - 500; EnCoor[i][3] -= PLx - 500;}
for (int i = 1; i <= wallnum; i++){wall[i][1] -= PLx - 500; wall[i][3] -= PLx - 500;}
mx -= PLx - 500;
PLx = 500;

for (int i = 1; i <= ennumr; i++){EnCoor[i][2] -= PLy - 350; EnCoor[i][4] -= PLy - 350;}
for (int i = 1; i <= wallnum; i++){wall[i][2] -= PLy - 350; wall[i][4] -= PLy - 350;}
my -= PLy - 350;
PLy = 350;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddItemClick(TObject *Sender)
{
int t;

for (int i = 1; i <= 40; i++)
   {
    if (M[i].type == iadd && I[M[i].type].type == 0 | I[M[i].type].type == 10)
       {
        M[i].q++;
        i = 45;
       }
    else if (M[i].type == 0)
       {
        for (int j = 1; j <= 36; j++)
           {
            t = 0;
            for (int h = 1; h <= 40; h++)
                if (M[h].slot == j)t = 1;
            if (t == 0){t = j; j = 45;}
           }

        M[i].type = iadd;
        M[i].slot = t;
        i = 45;
       }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveClick(TObject *Sender)
{
ofstream cr("Save1.sav");

cr << mx << endl << my << endl << PLx << endl << PLy << endl;
cr << P.hp << endl << P.hpmax << endl << P.mp << endl << P.mpmax << endl << P.sta << endl << P.stamax
 << endl << P.lvl << endl << P.att << endl << P.def << endl << P.demage << endl
 << P.exp << endl << P.expmax << endl << P.gold << endl ;


for (int i = 1; i <= 12; i++)
   {
    cr << S[i].lvl << endl << S[i].wait << endl << S[i].sta << endl << S[i].mp <<
    endl << S[i].hp << endl << S[i].demage << endl << S[i].quick << endl;
   }


for (int i = 1; i <= 50; i++)
   {
    cr << M[i].type << endl << M[i].slot << endl << M[i].equip << endl << M[i].q << endl;
   }


for (int i = 1; i <= 40; i++)
   {
    cr << B[1].items[i] << endl << B[1].q[i] << endl;
   }

cr.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
SaveClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LoadClick(TObject *Sender)
{

// Read Save from file

ifstream fd("Save1.sav");


fd.getline(read, 50);read3 = read; mx = StrToInt(read3);
fd.getline(read, 50);read3 = read; my = StrToInt(read3);
fd.getline(read, 50);read3 = read; PLx = StrToInt(read3);
fd.getline(read, 50);read3 = read; PLy = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.hp = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.hpmax = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.mp = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.mpmax = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.sta = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.stamax = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.lvl = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.att = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.def = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.demage = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.exp = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.expmax = StrToInt(read3);
fd.getline(read, 50);read3 = read; P.gold = StrToInt(read3);

for (int i = 1; i <= 12; i++)
   {
    fd.getline(read, 50);read3 = read; S[i].lvl = StrToInt(read3);
    fd.getline(read, 50);read3 = read; S[i].wait = StrToInt(read3);
    fd.getline(read, 50);read3 = read; S[i].sta = StrToInt(read3);
    fd.getline(read, 50);read3 = read; S[i].mp = StrToInt(read3);
    fd.getline(read, 50);read3 = read; S[i].hp = StrToInt(read3);
    fd.getline(read, 50);read3 = read; S[i].demage = StrToFloat(read3);
    fd.getline(read, 50);read3 = read; S[i].quick = StrToInt(read3);
   }

for (int i = 1; i <= 50; i++)
   {
    fd.getline(read, 50);read3 = read; M[i].type = StrToInt(read3);
    fd.getline(read, 50);read3 = read; M[i].slot = StrToInt(read3);
    fd.getline(read, 50);read3 = read; M[i].equip = StrToInt(read3);
    fd.getline(read, 50);read3 = read; M[i].q = StrToInt(read3);
   }

for (int i = 1; i <= 40; i++)
   {
    fd.getline(read, 50);read3 = read; B[1].items[i] = StrToInt(read3);
    fd.getline(read, 50);read3 = read; B[1].q[i] = StrToInt(read3);
   }

fd.close();

for (int i = 1; i <= wallnum; i++)
   {
    wall[i][1] += mx;
    wall[i][2] += my;
    wall[i][3] += mx;
    wall[i][4] += my;
   }

for (int i = 1; i <= ennumr; i++)
   {
    EnCoor[i][1] += mx;
    EnCoor[i][2] += my;
    EnCoor[i][3] += mx;
    EnCoor[i][4] += my;
   }
}
//---------------------------------------------------------------------------

