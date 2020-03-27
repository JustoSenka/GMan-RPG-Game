//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <SysUtils.hpp>   // If exist command here

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm2::FormShow(TObject *Sender)
{
// Items

IList->Clear();
for (int i = 1; i <= Form1->itemnum; i++)
    IList->Items->Add(Form1->I[i].name);

// Enemies

EList->Clear();
for (int i = 1; i <= Form1->entypenum; i++)
    EList->Items->Add(Form1->E[i].name);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::IListClick(TObject *Sender)
{
if (IList->ItemIndex > -1)
   {
    lvl->Text = Form1->I[IList->ItemIndex + 1].lvl;
    att->Text = Form1->I[IList->ItemIndex + 1].att;
    def->Text = Form1->I[IList->ItemIndex + 1].def;
    dem->Text = Form1->I[IList->ItemIndex + 1].demage;
    price->Text = Form1->I[IList->ItemIndex + 1].price;
    hp->Text = Form1->I[IList->ItemIndex + 1].hp;
    mp->Text = Form1->I[IList->ItemIndex + 1].mp;
    sta->Text = Form1->I[IList->ItemIndex + 1].sta;
    name->Text = Form1->I[IList->ItemIndex + 1].name;
    selicon = Form1->I[IList->ItemIndex + 1].icon;

    TypeCombo->ItemIndex = Form1->I[IList->ItemIndex + 1].type;

    Image->Picture->Bitmap = Items[selicon];
    //Image->Picture->LoadFromFile("Items\\I" + IntToStr(selicon) + ".bmp");
   }
TypeComboChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TypeComboChange(TObject *Sender)
{
lvl->Enabled = true;
att->Enabled = true;
def->Enabled = true;
dem->Enabled = true;
hp->Enabled = true;
mp->Enabled = true;
sta->Enabled = true;

if (TypeCombo->ItemIndex == 0)
   {
    lvl->Enabled = false; lvl->Text = 0;
    att->Enabled = false; att->Text = 0;
    def->Enabled = false; def->Text = 0;
    dem->Enabled = false; dem->Text = 0;
    hp->Enabled = false; hp->Text = 0;
    mp->Enabled = false; mp->Text = 0;
    sta->Enabled = false; sta->Text = 0;
   }

if (TypeCombo->ItemIndex == 10)
   {
    lvl->Enabled = false; lvl->Text = 0;
    att->Enabled = false; att->Text = 0;
    def->Enabled = false; def->Text = 0;
    dem->Enabled = false; dem->Text = 0;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::addClick(TObject *Sender)
{
Form1->itemnum++;

Form1->I[Form1->itemnum].lvl = StrToInt(lvl->Text);
Form1->I[Form1->itemnum].att = StrToInt(att->Text);
Form1->I[Form1->itemnum].def = StrToInt(def->Text);
Form1->I[Form1->itemnum].demage = StrToInt(dem->Text);
Form1->I[Form1->itemnum].price = StrToInt(price->Text);
Form1->I[Form1->itemnum].hp = StrToInt(hp->Text);
Form1->I[Form1->itemnum].mp = StrToInt(mp->Text);
Form1->I[Form1->itemnum].sta = StrToInt(sta->Text);
Form1->I[Form1->itemnum].type = TypeCombo->ItemIndex;
Form1->I[Form1->itemnum].name = name->Text;
Form1->I[Form1->itemnum].icon = selicon;

IList->Items->Add(Form1->I[Form1->itemnum].name);

IList->ItemIndex = Form1->itemnum - 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::delClick(TObject *Sender)
{
if (IList->ItemIndex > -1)
{
Form1->itemnum--;

for (int h = 1; h <= Form1->entypenum; h++)
    if (Form1->E[h].item[IList->ItemIndex + 1] != 0) Form1->E[h].idropc--;

for (int i = IList->ItemIndex + 1; i <= Form1->itemnum; i++)
   {
    // Delete stats for items

    Form1->I[i].lvl = Form1->I[i+1].lvl;
    Form1->I[i].att = Form1->I[i+1].att;
    Form1->I[i].def = Form1->I[i+1].def;
    Form1->I[i].demage = Form1->I[i+1].demage;
    Form1->I[i].price = Form1->I[i+1].price;
    Form1->I[i].hp = Form1->I[i+1].hp;
    Form1->I[i].mp = Form1->I[i+1].mp;
    Form1->I[i].sta = Form1->I[i+1].sta;
    Form1->I[i].type = Form1->I[i+1].type;
    Form1->I[i].name = Form1->I[i+1].name;
    Form1->I[i].icon = Form1->I[i+1].icon;

    // And delete for enemy drops

    for (int h = 1; h <= Form1->entypenum; h++)
        Form1->E[h].item[i] = Form1->E[h].item[i + 1];
   }

int a = IList->ItemIndex;
IList->Items->Delete(IList->ItemIndex);
IList->ItemIndex = a;

IListClick(Sender);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::saveClick(TObject *Sender)
{
Form1->I[IList->ItemIndex + 1].lvl = StrToInt(lvl->Text);
Form1->I[IList->ItemIndex + 1].att = StrToInt(att->Text);
Form1->I[IList->ItemIndex + 1].def = StrToInt(def->Text);
Form1->I[IList->ItemIndex + 1].demage = StrToInt(dem->Text);
Form1->I[IList->ItemIndex + 1].price = StrToInt(price->Text);
Form1->I[IList->ItemIndex + 1].hp = StrToInt(hp->Text);
Form1->I[IList->ItemIndex + 1].mp = StrToInt(mp->Text);
Form1->I[IList->ItemIndex + 1].sta = StrToInt(sta->Text);
Form1->I[IList->ItemIndex + 1].type = TypeCombo->ItemIndex;
Form1->I[IList->ItemIndex + 1].name = name->Text;
Form1->I[IList->ItemIndex + 1].icon = selicon;

IList->Items->Insert(IList->ItemIndex,name->Text);

int a = IList->ItemIndex - 1;
IList->Items->Delete(IList->ItemIndex);
IList->ItemIndex = a;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::IListMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (mouse == 0) sel = IList->ItemIndex;
mouse = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::IListMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
mouse = 0;
sel = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::IListMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if (mouse == 1 && sel > -1)
 {
 int a;
 AnsiString b;

 if (sel > IList->ItemIndex)
   {
    // Replacing variables for items

    a = Form1->I[sel].lvl; Form1->I[sel].lvl = Form1->I[sel + 1].lvl; Form1->I[sel + 1].lvl = a;
    a = Form1->I[sel].att; Form1->I[sel].att = Form1->I[sel + 1].att; Form1->I[sel + 1].att = a;
    a = Form1->I[sel].def; Form1->I[sel].def = Form1->I[sel + 1].def; Form1->I[sel + 1].def = a;
    a = Form1->I[sel].demage; Form1->I[sel].demage = Form1->I[sel + 1].demage; Form1->I[sel + 1].demage = a;
    a = Form1->I[sel].price; Form1->I[sel].price = Form1->I[sel + 1].price; Form1->I[sel + 1].price = a;
    a = Form1->I[sel].hp; Form1->I[sel].hp = Form1->I[sel + 1].hp; Form1->I[sel + 1].hp = a;
    a = Form1->I[sel].mp; Form1->I[sel].mp = Form1->I[sel + 1].mp; Form1->I[sel + 1].mp = a;
    a = Form1->I[sel].sta; Form1->I[sel].sta = Form1->I[sel + 1].sta; Form1->I[sel + 1].sta = a;
    a = Form1->I[sel].type; Form1->I[sel].type = Form1->I[sel + 1].type; Form1->I[sel + 1].type = a;
    b = Form1->I[sel].name; Form1->I[sel].name = Form1->I[sel + 1].name; Form1->I[sel + 1].name = b;
    a = Form1->I[sel].icon; Form1->I[sel].icon = Form1->I[sel + 1].icon; Form1->I[sel + 1].icon = a;

    // And for enemy drop rates

    for (int i = 1; i <= Form1->entypenum; i++)
        {a = Form1->E[i].item[sel]; Form1->E[i].item[sel] = Form1->E[i].item[sel + 1]; Form1->E[i].item[sel + 1] = a;}

    IList->Items->Exchange(sel ,sel - 1);
    sel--;
   }

 else if (sel < IList->ItemIndex)
   {
    // Replacing variables for items
    
    a = Form1->I[sel + 2].lvl; Form1->I[sel + 2].lvl = Form1->I[sel + 1].lvl; Form1->I[sel + 1].lvl = a;
    a = Form1->I[sel + 2].att; Form1->I[sel + 2].att = Form1->I[sel + 1].att; Form1->I[sel + 1].att = a;
    a = Form1->I[sel + 2].def; Form1->I[sel + 2].def = Form1->I[sel + 1].def; Form1->I[sel + 1].def = a;
    a = Form1->I[sel + 2].demage; Form1->I[sel + 2].demage = Form1->I[sel + 1].demage; Form1->I[sel + 1].demage = a;
    a = Form1->I[sel + 2].price; Form1->I[sel + 2].price = Form1->I[sel + 1].price; Form1->I[sel + 1].price = a;
    a = Form1->I[sel + 2].hp; Form1->I[sel + 2].hp = Form1->I[sel + 1].hp; Form1->I[sel + 1].hp = a;
    a = Form1->I[sel + 2].mp; Form1->I[sel + 2].mp = Form1->I[sel + 1].mp; Form1->I[sel + 1].mp = a;
    a = Form1->I[sel + 2].sta; Form1->I[sel + 2].sta = Form1->I[sel + 1].sta; Form1->I[sel + 1].sta = a;
    a = Form1->I[sel + 2].type; Form1->I[sel + 2].type = Form1->I[sel + 1].type; Form1->I[sel + 1].type = a;
    b = Form1->I[sel + 2].name; Form1->I[sel + 2].name = Form1->I[sel + 1].name; Form1->I[sel + 1].name = b;
    a = Form1->I[sel + 2].icon; Form1->I[sel + 2].icon = Form1->I[sel + 1].icon; Form1->I[sel + 1].icon = a;

    // And for enemy drop rates

    for (int i = 1; i <= Form1->entypenum; i++)
        {a = Form1->E[i].item[sel + 2]; Form1->E[i].item[sel + 2] = Form1->E[i].item[sel + 1]; Form1->E[i].item[sel + 1] = a;}

    IList->Items->Exchange(sel,sel + 1);
    sel++;
   }
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
// Items

for (int i = 1; i <= 2000; i++) if (FileExists("Items\\I" + IntToStr(i) + ".bmp")==true)
   {
    Items[i] = new Graphics::TBitmap;
    Items[i]->LoadFromFile("Items\\I" + IntToStr(i) + ".bmp");
    Items[i]->Transparent = true;
    iconnum = i; // ??? I do not know what it is, but let it be..
   }

// Enemies

for (int i = 1; i <= 200; i++) if (FileExists("Enemies\\En" + IntToStr(i) + ".bmp")==true)
   {
    EnType[i] = new Graphics::TBitmap;
    EnType[i]->LoadFromFile("Enemies\\En" + IntToStr(i) + ".bmp");
    EnType[i]->Transparent = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::loadClick(TObject *Sender)
{
if (OpenDialog1->Execute())
   {
    Image->Picture->LoadFromFile(OpenDialog1->FileName);

    AnsiString s = OpenDialog1->FileName;

    char c[15];

    while (1)
       {
        c[0] = s[s.Length() - 4];
        if (s[s.Length() - 5] == 'I')break;

        c[0] = s[s.Length() - 5]; c[1] = s[s.Length() - 4];
        if (s[s.Length() - 6] == 'I')break;

        c[0] = s[s.Length() - 6]; c[1] = s[s.Length() - 5]; c[2] = s[s.Length() - 4];
        if (s[s.Length() - 7] == 'I')break;
        
        c[0] = s[s.Length() - 7]; c[1] = s[s.Length() - 6]; c[2] = s[s.Length() - 5]; c[3] = s[s.Length() - 4];
        break;
       }

    s = c;
    selicon = StrToInt(s);
   }
}
//---------------------------------------------------------------------------



void __fastcall TForm2::EListClick(TObject *Sender)
{
if (EList->ItemIndex > -1)
   {
    Ehp->Text = Form1->E[EList->ItemIndex + 1].hpmax;
    Espeed->Text = Form1->E[EList->ItemIndex + 1].speed;
    Esight->Text = Form1->E[EList->ItemIndex + 1].sight;
    Eatt->Text = Form1->E[EList->ItemIndex + 1].att;
    Edef->Text = Form1->E[EList->ItemIndex + 1].def;
    Edem->Text = Form1->E[EList->ItemIndex + 1].demage;
    Eexp->Text = Form1->E[EList->ItemIndex + 1].exp;
    Egold->Text = Form1->E[EList->ItemIndex + 1].gold;
    selicon2 = Form1->E[EList->ItemIndex + 1].icon;

    Ename->Text = Form1->E[EList->ItemIndex + 1].name;

    ItemCombo->Clear();
        for (int h = 1; h <= Form1->itemnum; h++)
            if (Form1->E[EList->ItemIndex + 1].item[h] != 0)
                ItemCombo->Items->Add(Form1->I[h].name);
    ItemCombo->ItemIndex = 0;
    ItemComboChange(Sender);

    Image2->Picture->Bitmap = EnType[selicon2];
    //Image2->Picture->LoadFromFile("Enemies\\En" + IntToStr(selicon2) + ".bmp");

   }

}
//---------------------------------------------------------------------------

void __fastcall TForm2::EListMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
if (mouse == 0) sel = EList->ItemIndex;
mouse = 1;        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EListMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
mouse = 0;
sel = 0;        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EListMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
if (mouse == 1 && sel > -1)
 {
 int a;
 AnsiString b;

 if (sel > EList->ItemIndex)
   {
    a = Form1->E[sel].hpmax; Form1->E[sel].hpmax = Form1->E[sel + 1].hpmax; Form1->E[sel + 1].hpmax = a;
    a = Form1->E[sel].speed; Form1->E[sel].speed = Form1->E[sel + 1].speed; Form1->E[sel + 1].speed = a;
    a = Form1->E[sel].sight; Form1->E[sel].sight = Form1->E[sel + 1].sight; Form1->E[sel + 1].sight = a;
    a = Form1->E[sel].att; Form1->E[sel].att = Form1->E[sel + 1].att; Form1->E[sel + 1].att = a;
    a = Form1->E[sel].def; Form1->E[sel].def = Form1->E[sel + 1].def; Form1->E[sel + 1].def = a;
    a = Form1->E[sel].demage; Form1->E[sel].demage = Form1->E[sel + 1].demage; Form1->E[sel + 1].demage = a;
    a = Form1->E[sel].exp; Form1->E[sel].exp = Form1->E[sel + 1].exp; Form1->E[sel + 1].exp = a;
    a = Form1->E[sel].gold; Form1->E[sel].gold = Form1->E[sel + 1].gold; Form1->E[sel + 1].gold = a;
    b = Form1->E[sel].name; Form1->E[sel].name = Form1->E[sel + 1].name; Form1->E[sel + 1].name = b;
    a = Form1->E[sel].icon; Form1->E[sel].icon = Form1->E[sel + 1].icon; Form1->E[sel + 1].icon = a;
    a = Form1->E[sel].idropc; Form1->E[sel].idropc = Form1->E[sel + 1].idropc; Form1->E[sel + 1].idropc = a;

    for (int h = 1; h <= Form1->itemnum; h++)
         {a = Form1->E[sel].item[h]; Form1->E[sel].item[h] = Form1->E[sel + 1].item[h]; Form1->E[sel + 1].item[h] = a;}

    EList->Items->Exchange(sel ,sel - 1);
    sel--;
   }

 else if (sel < EList->ItemIndex)
   {
    a = Form1->E[sel + 2].hpmax; Form1->E[sel + 2].hpmax = Form1->E[sel + 1].hpmax; Form1->E[sel + 1].hpmax = a;
    a = Form1->E[sel + 2].speed; Form1->E[sel + 2].speed = Form1->E[sel + 1].speed; Form1->E[sel + 1].speed = a;
    a = Form1->E[sel + 2].sight; Form1->E[sel + 2].sight = Form1->E[sel + 1].sight; Form1->E[sel + 1].sight = a;
    a = Form1->E[sel + 2].att; Form1->E[sel + 2].att = Form1->E[sel + 1].att; Form1->E[sel + 1].att = a;
    a = Form1->E[sel + 2].def; Form1->E[sel + 2].def = Form1->E[sel + 1].def; Form1->E[sel + 1].def = a;
    a = Form1->E[sel + 2].demage; Form1->E[sel + 2].demage = Form1->E[sel + 1].demage; Form1->E[sel + 1].demage = a;
    a = Form1->E[sel + 2].exp; Form1->E[sel + 2].exp = Form1->E[sel + 1].exp; Form1->E[sel + 1].exp = a;
    a = Form1->E[sel + 2].gold; Form1->E[sel + 2].gold = Form1->E[sel + 1].gold; Form1->E[sel + 1].gold = a;
    b = Form1->E[sel + 2].name; Form1->E[sel + 2].name = Form1->E[sel + 1].name; Form1->E[sel + 1].name = b;
    a = Form1->E[sel + 2].icon; Form1->E[sel + 2].icon = Form1->E[sel + 1].icon; Form1->E[sel + 1].icon = a;
    a = Form1->E[sel + 2].idropc; Form1->E[sel + 2].idropc = Form1->E[sel + 1].idropc; Form1->E[sel + 1].idropc = a;

    for (int h = 1; h <= Form1->itemnum; h++)
         {a = Form1->E[sel + 2].item[h]; Form1->E[sel + 2].item[h] = Form1->E[sel + 1].item[h]; Form1->E[sel + 1].item[h] = a;}

    EList->Items->Exchange(sel ,sel + 1);
    sel++;
   }
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm2::ItemComboChange(TObject *Sender)
{
if (ItemCombo->ItemIndex > -1)
   {
    for (int i = 1; i <= Form1->itemnum; i++)
        if (Form1->E[EList->ItemIndex + 1].item[i] != 0 && Form1->I[i].name == ItemCombo->Items->Strings[ItemCombo->ItemIndex])
           {
            Edrop->Text = Form1->E[EList->ItemIndex + 1].item[i];
            selic = i;
           }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EaddClick(TObject *Sender)
{
/*
Form1->itemnum++;

Form1->I[Form1->itemnum].lvl = StrToInt(lvl->Text);
Form1->I[Form1->itemnum].att = StrToInt(att->Text);
Form1->I[Form1->itemnum].def = StrToInt(def->Text);
Form1->I[Form1->itemnum].demage = StrToInt(dem->Text);
Form1->I[Form1->itemnum].price = StrToInt(price->Text);
Form1->I[Form1->itemnum].hp = StrToInt(hp->Text);
Form1->I[Form1->itemnum].mp = StrToInt(mp->Text);          Reikia redaguoti
Form1->I[Form1->itemnum].sta = StrToInt(sta->Text);          Kaip su menu
Form1->I[Form1->itemnum].type = TypeCombo->ItemIndex;         idesi
Form1->I[Form1->itemnum].name = name->Text;                 pakeisti vietoj
Form1->I[Form1->itemnum].icon = selicon;                      I - E

IList->Items->Add(Form1->I[Form1->itemnum].name);

IList->ItemIndex = Form1->itemnum - 1;
*/
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EdelClick(TObject *Sender)
{                          /*
if (IList->ItemIndex > -1)
{
Form1->itemnum--;

for (int i = IList->ItemIndex + 1; i <= Form1->itemnum; i++)
   {
    Form1->I[i].lvl = Form1->I[i+1].lvl;
    Form1->I[i].att = Form1->I[i+1].att;
    Form1->I[i].def = Form1->I[i+1].def;
    Form1->I[i].demage = Form1->I[i+1].demage;
    Form1->I[i].price = Form1->I[i+1].price;
    Form1->I[i].hp = Form1->I[i+1].hp;
    Form1->I[i].mp = Form1->I[i+1].mp;                   Taip pat
    Form1->I[i].sta = Form1->I[i+1].sta;                 redaguoti
    Form1->I[i].type = Form1->I[i+1].type;
    Form1->I[i].name = Form1->I[i+1].name;
    Form1->I[i].icon = Form1->I[i+1].icon;
   }

int a = IList->ItemIndex;
IList->Items->Delete(IList->ItemIndex);
IList->ItemIndex = a;

IListClick(Sender);
}                       */
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EsaveClick(TObject *Sender)
{
Form1->E[EList->ItemIndex + 1].hpmax = StrToInt(Ehp->Text);
Form1->E[EList->ItemIndex + 1].speed = StrToInt(Espeed->Text);
Form1->E[EList->ItemIndex + 1].sight = StrToInt(Esight->Text);
Form1->E[EList->ItemIndex + 1].att = StrToInt(Eatt->Text);
Form1->E[EList->ItemIndex + 1].def = StrToInt(Edef->Text);
Form1->E[EList->ItemIndex + 1].demage = StrToInt(Edem->Text);
Form1->E[EList->ItemIndex + 1].exp = StrToInt(Eexp->Text);
Form1->E[EList->ItemIndex + 1].gold = StrToInt(Egold->Text);
Form1->E[EList->ItemIndex + 1].name = Ename->Text;
Form1->E[EList->ItemIndex + 1].icon = selicon2;

EList->Items->Insert(EList->ItemIndex,Ename->Text);

int a = EList->ItemIndex - 1;
EList->Items->Delete(EList->ItemIndex);
EList->ItemIndex = a;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EloadClick(TObject *Sender)
{
if (OpenDialog1->Execute())
   {
    Image2->Picture->LoadFromFile(OpenDialog1->FileName);

    AnsiString s = OpenDialog1->FileName;

    char c[15];

    while (1)
       {
        c[0] = s[s.Length() - 4];
        if (s[s.Length() - 5] == 'n')break;

        c[0] = s[s.Length() - 5]; c[1] = s[s.Length() - 4];
        if (s[s.Length() - 6] == 'n')break;

        c[0] = s[s.Length() - 6]; c[1] = s[s.Length() - 5]; c[2] = s[s.Length() - 4];
        if (s[s.Length() - 7] == 'n')break;
        
        c[0] = s[s.Length() - 7]; c[1] = s[s.Length() - 6]; c[2] = s[s.Length() - 5]; c[3] = s[s.Length() - 4];
        break;
       }

    s = c;
    selicon2 = StrToInt(s);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::EokClick(TObject *Sender)
{
Form1->E[EList->ItemIndex + 1].item[selic] = StrToInt(Edrop->Text);

if (StrToInt(Edrop->Text) == 0)
   {
    ItemCombo->Items->Delete(ItemCombo->ItemIndex);
    Form1->E[EList->ItemIndex + 1].idropc--;
   }
//ItemCombo->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
Form1->E[EList->ItemIndex + 1].item[IList->ItemIndex + 1] = 100;
Form1->E[EList->ItemIndex + 1].idropc++;

ItemCombo->Items->Add(IList->Items->Strings[IList->ItemIndex]);
}
//---------------------------------------------------------------------------

