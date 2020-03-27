//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TListBox *IList;
        TLabel *Label1;
        TLabeledEdit *lvl;
        TLabeledEdit *price;
        TLabeledEdit *att;
        TLabeledEdit *def;
        TLabeledEdit *dem;
        TLabeledEdit *hp;
        TLabeledEdit *mp;
        TLabeledEdit *sta;
        TLabeledEdit *name;
        TButton *add;
        TButton *save;
        TComboBox *TypeCombo;
        TLabel *Label2;
        TButton *del;
        TImage *Image;
        TButton *load;
        TOpenDialog *OpenDialog1;
        TBevel *Bevel1;
        TListBox *EList;
        TLabeledEdit *Ehp;
        TLabeledEdit *Espeed;
        TLabeledEdit *Esight;
        TLabeledEdit *Eatt;
        TLabeledEdit *Edef;
        TLabeledEdit *Edem;
        TLabeledEdit *Eexp;
        TLabeledEdit *Egold;
        TLabeledEdit *Ename;
        TLabel *Label3;
        TButton *Eadd;
        TImage *Image2;
        TComboBox *ItemCombo;
        TLabeledEdit *Edrop;
        TButton *Esave;
        TButton *Edel;
        TButton *Eload;
        TButton *Eok;
        TButton *Button1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall IListClick(TObject *Sender);
        void __fastcall TypeComboChange(TObject *Sender);
        void __fastcall addClick(TObject *Sender);
        void __fastcall delClick(TObject *Sender);
        void __fastcall saveClick(TObject *Sender);
        void __fastcall IListMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall IListMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall IListMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall loadClick(TObject *Sender);
        void __fastcall EListClick(TObject *Sender);
        void __fastcall EListMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall EListMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall EListMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall ItemComboChange(TObject *Sender);
        void __fastcall EaddClick(TObject *Sender);
        void __fastcall EdelClick(TObject *Sender);
        void __fastcall EsaveClick(TObject *Sender);
        void __fastcall EloadClick(TObject *Sender);
        void __fastcall EokClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations

Graphics::TBitmap*    Items[2000];
Graphics::TBitmap*    EnType[200];

public:		// User declarations

int pop, sel, mouse, selicon, selicon2, iconnum, selic;

        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
