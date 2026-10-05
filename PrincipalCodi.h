//---------------------------------------------------------------------------

#ifndef PrincipalCodiH
#define PrincipalCodiH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <Vcl.Buttons.hpp>

#include "ClassCoDiMX.h"
//---------------------------------------------------------------------------
class TFCodiMX : public TForm
{
__published:	// IDE-managed Components
	TImage *IQRCodi;
	TBitBtn *BtnGenerarCobroCoDi;
	TMemo *Memo1;
	TTimer *Timer1;
	TBitBtn *BtnGenerarCobroCel;
	TLabel *LabelEstado;
	void __fastcall BtnGenerarCobroCoDiClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall BtnGenerarCobroCelClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations

	TClassCoDiMX *CoDi;

	String apiKey;

public:		// User declarations


	__fastcall TFCodiMX(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFCodiMX *FCodiMX;
//---------------------------------------------------------------------------
#endif
