#ifndef ClassCoDiMXH
#define ClassCoDiMXH
//-----------------------------------------------------  
#include <System.hpp>
#include <REST.Client.hpp>
//-----------------------------------------------------  
class TClassCoDiMX
{
private:
 
	String FApiKey;
	String FFolioCoDi;
 
public:
 
	__fastcall TClassCoDiMX(const String &ApiKey);
 
	bool __fastcall GenerarQR(
	double Monto,
	String Referencia,
	String Concepto,
	String Vigencia,
	String &Respuesta,
	String &QrBase64);
	 
	bool __fastcall GenerarPush(
	double Monto,
	String Referencia,
	String Concepto,
	String Vigencia,
	String Celular,
	String &Respuesta);
	 
	bool __fastcall Consultar(
	String &Respuesta,
	int &EdoMC);
	 
	String FolioCoDi()
	{
		return FFolioCoDi;
	}
};
//-----------------------------------------------------  
#endif
