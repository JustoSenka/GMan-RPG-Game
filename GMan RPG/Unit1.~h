//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <graphics.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <MPlayer.hpp>
#include <string>
#include <mmsystem.h>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TMemo *Memo1;
        TButton *Button1;
        TTimer *Timer2;
        TButton *Draw;
        TTimer *Timer3;
        TButton *CenterPlayer;
        TButton *AddItem;
        TButton *Save;
        TButton *Load;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall DrawClick(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall CenterPlayerClick(TObject *Sender);
        void __fastcall AddItemClick(TObject *Sender);
        void __fastcall SaveClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall LoadClick(TObject *Sender);
private:	// User declarations
    Graphics::TBitmap*    Wall[50];
    Graphics::TBitmap*    Walltemp[10];
    Graphics::TBitmap*    WallAnim[50][5];
    Graphics::TBitmap*    PL[17];
    Graphics::TBitmap*    En[40][17];
    Graphics::TBitmap*    Skill[20][17];
    Graphics::TBitmap*    ESk[6];
    Graphics::TBitmap*    Items[2000];
    Graphics::TBitmap*    Death[7];
    Graphics::TBitmap*    TRead;
    Graphics::TBitmap*    Back;
    Graphics::TBitmap*    Plus;
    Graphics::TBitmap*    BI;
    Graphics::TBitmap*    WS;
    Graphics::TBitmap*    WI;
    Graphics::TBitmap*    AT;

    TRect Rect;

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

struct EnemyStats
{
int hp, hpmax, speed, sight, att, def, demage,
num, dead, timer, spawnCoor[5],
exp, gold, idropc, item[2000], icon,
/* AI */
x, y, cpx, cpy, action, busy, wait, t, tempf, tempxy, obs[5];

// if action == 0 passive; 1 - chase; 2 - obstacles; 3 finish obstacles; 4 friend obs; 5 finish friend obs

float Range, sta, stamax;
AnsiString name;
}  E[1000];

struct EnemyTypeStats
{
int hpmax, speed, sight, att, def, demage,
exp, gold, idropc, item[2000], icon;
AnsiString name;
}  ET[200];

struct MyStats
{
int lvl, hp, mp, sta, hpmax, mpmax, stamax, att, def, demage,
    totatt, totdef, totdemage, tothp, totmp, totsta,
    num, speed, statsp, skillp, exp, expmax, gold;
float Range, run, hpregen, mpregen, staregen;
AnsiString name;
}  P;

struct Skills
{
int lvl, atk, hit, animnum, face, x, y,
    wait, waited, quick, mp, sta, hp;
float Range, demage;
}  S[20];

struct Inventory
{
int lvl, att, def, demage, hp, mp, sta,
     type, price, icon;
AnsiString name;
}  I[2000];

struct MyItems
{
int type, equip, slot, q;
}  M[200];

struct Shop
{
int items[50], q[50];
float sratio, bratio;
}  B[11];

int mx, my, mx2, my2, press, facing, shift, control, space, options, qsnums[9], valx, valy,
    anim, num, iadd, backx, backy,
    wstats, wsx, wsy, qst[9], wi, wix, wiy, isel, ion, wb, wbisel, wbion,
    wall[5000][7], wallanim, wallnum, ennumr, deathanim[6], eskanim[6],
    EnCoor[1000][6], enface[1000], enanim[1000], envalx[1000], envaly[1000],
    wasd[5], tempf, tempdraw, tx, ty, LMB, RMB,
    itemnum, entypenum;

float t1, t2, t3, tf1, tf2, percent, gotdem, givedem, PLx, PLy,
      ent[4][1000];

char read[50];

AnsiString tempc, read3, read4;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
