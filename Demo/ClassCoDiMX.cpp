#include <vcl.h>
#pragma hdrstop

#include "ClassCoDiMX.h"
 
#include <memory>
#include <System.JSON.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <System.NetEncoding.hpp>
//----------------------------------------------------- 
#pragma package(smart_init)
//----------------------------------------------------- 
__fastcall TClassCoDiMX::TClassCoDiMX(const String &ApiKey)
{
	FApiKey = ApiKey;
}
//-----------------------------------------------------
// GENERAR PUSH
//-----------------------------------------------------
 
bool __fastcall TClassCoDiMX::GenerarPush(double Monto, String Referencia, String Concepto,
				String Vigencia, String Celular, String &Respuesta)
{
	std::unique_ptr<TRESTClient>   Client(new TRESTClient(NULL));
	std::unique_ptr<TRESTRequest>  Request(new TRESTRequest(NULL));
	std::unique_ptr<TRESTResponse> Response(new TRESTResponse(NULL));
	 
	try	{
		Client->BaseURL   = "https://api.bite-size.mx/";
		 
		Request->Client   = Client.get();
		Request->Response = Response.get();
		Request->Method   =  rmPOST;
		Request->Resource =	"v2/codi/push";
		 
		Request->AddParameter("x-api-key",FApiKey,pkHTTPHEADER);
		 
		std::unique_ptr<TJSONObject> Json(new TJSONObject());
		 
		Json->AddPair("monto",new TJSONNumber(Monto));
		Json->AddPair("referenciaNumerica",Referencia);
		Json->AddPair("concepto",Concepto);
		Json->AddPair("vigencia",Vigencia);
		Json->AddPair("celularCliente",	Celular);
		 
		Request->AddBody(Json->ToJSON(),ctAPPLICATION_JSON);
		 
		Request->Execute();
		 
		Respuesta = Response->Content;
		 
		if(Response->StatusCode != 200)
			return false;
		 
		std::unique_ptr<TJSONObject> Root(
		(TJSONObject*)
		TJSONObject::ParseJSONValue(
		Respuesta));
		 
		if(!Root)
		return false;
		 
		TJSONObject *Data =
		(TJSONObject*)
		Root->GetValue("data");
		 
		if(!Data)
			return false;
		 
		FFolioCoDi = Data->GetValue("folioCodi")->Value();
		return true;
		}
	catch(...){
		return false;
		}
}
//-----------------------------------------------------
// GENERAR QR
//-----------------------------------------------------
bool __fastcall TClassCoDiMX::GenerarQR(double Monto, String Referencia, String Concepto,
				String Vigencia, String &Respuesta, String &QRBase64)
{
	std::unique_ptr<TRESTClient>   Client(new TRESTClient(NULL));
	std::unique_ptr<TRESTRequest>  Request(new TRESTRequest(NULL));
	std::unique_ptr<TRESTResponse> Response(new TRESTResponse(NULL));
 
	try{
		Client->BaseURL = "https://api.bite-size.mx/";

		Request->Client    = Client.get();
		Request->Response  = Response.get();
		Request->Method    = rmPOST;
		Request->Resource  = "v2/codi/qr";
		 
		Request->AddParameter("x-api-key",FApiKey,pkHTTPHEADER);
		 
		std::unique_ptr<TJSONObject> Json(new TJSONObject());	 
		Json->AddPair("monto", new TJSONNumber(Monto));
		Json->AddPair("referenciaNumerica",	Referencia);
		Json->AddPair("concepto", Concepto);
		Json->AddPair("vigencia", Vigencia);

		Request->AddBody(Json->ToJSON(), ctAPPLICATION_JSON);
		Request->Execute();

		Respuesta =	Response->Content;
		 
		if(Response->StatusCode != 200)
			return false;
		 
		std::unique_ptr<TJSONObject> Root((TJSONObject*) TJSONObject::ParseJSONValue(Respuesta));
		 
		if(!Root)
			return false;
		 
		QRBase64 = Root->GetValue("qrCode")->Value();
		 
		TJSONObject *Data = (TJSONObject*) Root->GetValue("data");

		if(Data){
			String CadenaMC = Data->GetValue("cadenaMC")->Value();
			std::unique_ptr<TJSONObject> MC((TJSONObject*) TJSONObject::ParseJSONValue(CadenaMC));
			if(MC){
				TJSONObject *IC = (TJSONObject*) MC->GetValue("ic");		 
				if(IC){
					FFolioCoDi = IC->GetValue("IDC")->Value();
					}
				}
			}		 
		return true;
		}
	catch(...){
		return false;
		}
}
 
//-----------------------------------------------------
// CONSULTAR
//-----------------------------------------------------
bool __fastcall TClassCoDiMX::Consultar(String &Respuesta,int &EdoMC)
{
	EdoMC = -999;
 
	std::unique_ptr<TRESTClient>   Client(new TRESTClient(NULL));
	std::unique_ptr<TRESTRequest>  Request(new TRESTRequest(NULL));
	std::unique_ptr<TRESTResponse> Response(new TRESTResponse(NULL));

	try{
		Client->BaseURL   = "https://api.bite-size.mx/";
		Request->Client   = Client.get();
		Request->Response = Response.get();
		Request->Method   = rmPOST;
		Request->Resource = "v2/codi/consulta";

		Request->AddParameter("x-api-key",FApiKey,pkHTTPHEADER);

		std::unique_ptr<TJSONObject> Json(new TJSONObject());
		Json->AddPair("folioCodi",FFolioCoDi);
		Json->AddPair("tpg",new TJSONNumber(10));
		Json->AddPair("npg",new TJSONNumber(1));
		Json->AddPair("fechaInicial",FormatDateTime("yyyymmdd",Date()));
		Json->AddPair("fechaFinal","0");

		Request->AddBody(Json->ToJSON(),ctAPPLICATION_JSON);
		Request->Execute();

		Respuesta = Response->Content;
		if(Response->StatusCode != 200)
			return false;
		std::unique_ptr<TJSONObject> Root((TJSONObject*) TJSONObject::ParseJSONValue(Respuesta));
		if(!Root)
			return false;
		TJSONObject *Data = (TJSONObject*) Root->GetValue("data");
		if(!Data)
			return false;
		TJSONObject *Resultado = (TJSONObject*) Data->GetValue("resultado");
		if(!Resultado)
			return false;
		TJSONArray *Lista = (TJSONArray*) Resultado->GetValue("lstDetalleMC");
		if(!Lista)
			return false;
		if(Lista->Count == 0)
			return false;
		TJSONObject *Detalle = (TJSONObject*) Lista->Items[0];
		EdoMC = StrToIntDef(Detalle->GetValue("edoMC")->Value(),-999);
		return true;
		}
	catch(...){
		return false;
		}
}
//-------------------------------------------------
