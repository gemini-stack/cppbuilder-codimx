//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PrincipalCodi.h"
#include "ClassCoDiMX.h"

#include <System.Net.HttpClient.hpp>
#include <System.IOUtils.hpp>
#include <System.JSON.hpp>

#include <memory>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFCodiMX *FCodiMX;
//---------------------------------------------------------------------------
__fastcall TFCodiMX::TFCodiMX(TComponent* Owner)
	: TForm(Owner)
{
	//Referencia https://docs.bite-size.mx/
    //ApiKey orgada por bite-size
	apiKey = "ApiKey_CoDiMX_128hex";
}
//---------------------------------------------------------------------------

void __fastcall TFCodiMX::BtnGenerarCobroCoDiClick(TObject *Sender)
{
	String Resp;
	String QRBase64;
	 
	if(CoDi->GenerarQR(0.01, "0", "VENTA MOSTRADOR","0",Resp,QRBase64)){
		ShowMessage("Folio: " +	CoDi->FolioCoDi());
		QRBase64 = StringReplace(
		QRBase64,"data:image/png;base64,","", TReplaceFlags() << rfReplaceAll);
		 
		TBytes Datos = TNetEncoding::Base64->DecodeStringToBytes(QRBase64);		 
		if(Datos.Length > 0){
			TMemoryStream *MS =	new TMemoryStream();
			try	{
				MS->WriteBuffer(&Datos[0],Datos.Length);
				MS->Position = 0;
				TPngImage *PNG = new TPngImage();
				try	{
					PNG->LoadFromStream(MS);
					IQRCodi->Picture->Assign(PNG);
					}
				__finally{
					delete PNG;
					}
				}
			__finally{
				delete MS;
				}
			}
		}
	else{
		ShowMessage(Resp);
		}
}
//---------------------------------------------------------------------------
void __fastcall TFCodiMX::BtnGenerarCobroCelClick(TObject *Sender)
{
	String Resp;
 
	if(CoDi->GenerarPush(0.02,"0","VENTA MOSTRADOR","0","3211033515",Resp)){
		ShowMessage("Push enviado");
		ShowMessage(CoDi->FolioCoDi());
		}
	else{
		ShowMessage(Resp);
		}
}
//---------------------------------------------------------------------------
void __fastcall TFCodiMX::Timer1Timer(TObject *Sender)
{
	String Resp;
	int EdoMC;
	 
	if(CoDi->Consultar(Resp,EdoMC)){
		LabelEstado->Caption = "Estado: " + IntToStr(EdoMC);
		if(EdoMC == 2){
			Timer1->Enabled = false;
			ShowMessage("Pago recibido");
			// Guardar venta
			// Descontar inventario
			// Imprimir ticket
			}
		}
}
//---------------------------------------------------------------------------
void __fastcall TFCodiMX::FormCreate(TObject *Sender)
{
	CoDi = new TClassCoDiMX(apiKey);
}
//---------------------------------------------------------------------------

void __fastcall TFCodiMX::FormDestroy(TObject *Sender)
{
    delete CoDi;
}
//---------------------------------------------------------------------------

