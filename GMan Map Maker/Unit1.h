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
#include <Menus.hpp>
#include <Dialogs.hpp>
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
        TMemo *Memo1;
        TButton *Button1;
        TButton *Draw;
        TButton *Save;
        TButton *Load;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Save1;
        TMenuItem *Load1;
        TMenuItem *Exit1;
        TTimer *Timer1;
        TMenuItem *Edit1;
        TMenuItem *Undo1;
        TMenuItem *Delete1;
        TMenuItem *Tools1;
        TMenuItem *CenterPlayer1;
        TMenuItem *Usellect1;
        TMenuItem *Draw1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TMenuItem *New1;
        TMenuItem *SaveAs1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *Exit2;
        TMenuItem *Database1;
        void __fastcall FormCreate(TObject *Sender);
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
        void __fastcall DrawClick(TObject *Sender);
        void __fastcall SaveClick(TObject *Sender);
        void __fastcall LoadClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall Undo1Click(TObject *Sender);
        void __fastcall Delete1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Usellect1Click(TObject *Sender);
        void __fastcall CenterPlayer1Click(TObject *Sender);
        void __fastcall Draw1Click(TObject *Sender);
        void __fastcall D(TObject *Sender, TCanvas *ACanvas, int &Width,
          int &Height);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall Load1Click(TObject *Sender);
        void __fastcall New1Click(TObject *Sender);
        void __fastcall Exit2Click(TObject *Sender);
        void __fastcall SaveAs1Click(TObject *Sender);
        void __fastcall Database1Click(TObject *Sender);
private:	// User declarations
    Graphics::TBitmap*    Wall[50];
    Graphics::TBitmap*    Walltemp[10];
    Graphics::TBitmap*    PL[17];
    Graphics::TBitmap*    En[40][17];
    Graphics::TBitmap*    TRead;
    Graphics::TBitmap*    Back;
    Graphics::TBitmap*    Select;
    Graphics::TBitmap*    Up;
    Graphics::TBitmap*    Menu;
    Graphics::TBitmap*    BI;
    Graphics::TBitmap*    MM;

    TRect                 Rect;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);


int PLx, PLy, mx, my, press, facing, shift, space, drawback, RMB, LMB, mx2, my2,
    wall[5000][6], sType, senType, swall, menunum, menuxy[50][6], enmenuxy[40][6],
    EnCoor[1000][6], enface[1000], sen, map,
    wasd[5], tempf, valx, valy, tx, ty,

    num, wallnum, ennum, itemnum, entypenum;

AnsiString read3, read4, file;


struct EnemyStats
{
int hpmax, speed, sight, att, def, demage,
exp, gold, idropc, item[2000], icon;
AnsiString name;
}  E[200];


struct Inventory
{
int lvl, att, def, demage, hp, mp, sta,
     type, price, icon;
AnsiString name;
}  I[200];

char read[100], fileC[250];
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
