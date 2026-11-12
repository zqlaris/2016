#include <stdio.h>
#include <windows.h>
#include <ole2.h>
#include <comdef.h>

#include "ArkivProxy_i.h"


const IID IID_ILauncher =
{0x699F0898,0xB7BC,0x4DE5,{0xAF,0xEE,0x0E,0xC3,0x8A,0xD4,0x22,0x40}};

#ifdef _WIN64
	const CLSID CLSID_Launcher =
	{0xDEE03C2B,0x0C0C,0x41A9,{0x98,0x77,0xFD,0x4B,0x4D,0x7B,0x6E,0xA3}};
#else
	const CLSID CLSID_Launcher =
	{0x76D50904,0x6780,0x4c8b,{0x89,0x86,0x1A,0x7E,0xE0,0xB1,0x71,0x6D}};
#endif

//=================================================================================
//=================COM Synchronization routing functions========================================
//=================================================================================

bool isComInitialized = false;

void StartCom(void){
	HRESULT	hr;
	if( !isComInitialized ){
		hr = CoInitialize(0);
		if( SUCCEEDED(hr) ){
			isComInitialized = true;
		}
	}
}

void StopCom(void){
	if( isComInitialized ){
		CoUninitialize();
		isComInitialized = false;
	}
}

bool isComStarted(void){
	return isComInitialized;
}

//=================================================================================
//=================String routing functions========================================
//=================================================================================

/**
* Conversion from ASCII to WideChar
*
*/

int Str2Wc( char* pBuf, WCHAR* pwcBuf, int bufLen){
	if( pwcBuf == NULL || pBuf == NULL )
		return -1;

	// If zero then assume the user has allocated enough
	if( bufLen == 0 ){
		bufLen = (int)( strlen(pBuf) + 1 );
	}
	if( MultiByteToWideChar( CP_ACP, 0, pBuf, -1, pwcBuf, bufLen) == 0 ){
		return -1;
	}
	pwcBuf[strlen(pBuf)] = 0;
	return 0;
}
/**
* Conversion from WideChar to ASCII
*
*/
int Wc2Str(WCHAR* pwcBuf, char* pBuf, int bufLen){
	if( pwcBuf == NULL || pBuf == NULL )
		return -1;

// If zero then assume the user has allocated enough
	if( bufLen == 0 ){
		bufLen = (int)( wcslen( pwcBuf) + 1 );
	}
	if( WideCharToMultiByte( CP_ACP, 0, pwcBuf, -1, pBuf, bufLen, NULL, NULL) == 0 ){
		return -1;
	}
	pBuf[wcslen(pwcBuf)] = 0;
	return 0;
}

//=================================================================================
//=================Arkiv ActiveX functions call===================================
//=================================================================================

/**
* Create Arkiv ActiveX instance
*
*/

ILauncher * GetIArkivLauncherInstance(void){
	// Declare and HRESULT and a pointer to the ArkivProxy interface
	HRESULT	hr;
	ILauncher * IArkivLauncher;
	if( isComStarted() ){
		hr = CoCreateInstance( CLSID_Launcher, NULL, CLSCTX_INPROC_SERVER,
						IID_ILauncher, (void**) &IArkivLauncher);

		if( !SUCCEEDED(hr) ){
			IArkivLauncher=NULL;
		}
	}
	return IArkivLauncher;

}

/**
* Invoke HelloWorld method from Arkiv ActiveX
*
*/
int ArkivAdapterHelloWorld(ILauncher *iIArkivLauncher){
	HRESULT	hr = iIArkivLauncher->HelloWorld();
	return hr;
}

/**
* Invoke Hello method from Arkiv ActiveX
*
*/
int ArkivAdapterHello(ILauncher *iIArkivLauncher,char *retMessage){
	HRESULT			hr;
	BSTR hhh;

	hr = -1;
	hr = iIArkivLauncher->Hello( &hhh );
	if( SUCCEEDED(hr) ){
		Wc2Str( hhh, retMessage, 0 );
	}
	else {
		strcpy( retMessage, "IArkivLauncher->Hello() Error occured !" );
	}

	return hr;
}
/**
* Invoke StartGame method from Arkiv ActiveX
*
*/
int ArkivAdapterStartGame(ILauncher *iIArkivLauncher,char *cbufAuth, char *cbufScript ){
	HRESULT			hr;
	_bstr_t authenticationUrl(cbufAuth);
	_bstr_t script(cbufScript);

	hr = -1;
	hr = iIArkivLauncher->StartGame( authenticationUrl.GetBSTR(), 
									script.GetBSTR() );

	return hr;
}

/**
* Invoke PreStartGame method from Arkiv ActiveX
*
*/
int ArkivAdapterPreStartGame(ILauncher *iIArkivLauncher){
	HRESULT hr = -1;

	hr = iIArkivLauncher->PreStartGame();

	return hr;
}

/**
* Invoke GetInstallHost method from Arkiv ActiveX
*
*/
int ArkivAdapterGet_InstallHost(ILauncher *iIArkivLauncher,char *cbufHost){
	HRESULT			hr;
	BSTR host;
	hr = -1;
	hr = iIArkivLauncher->get_InstallHost( &host );

	if( SUCCEEDED(hr) ){
		Wc2Str( host, cbufHost, 0 );
	}
	else {
		strcpy( cbufHost, "IArkivLauncher->get_InstallHost() Error occured !" );
	}


	return hr;
}

/**
* Invoke GetVersion method from Arkiv ActiveX
*
*/
int ArkivAdapterGet_Version(ILauncher *iIArkivLauncher,char *cbufHost) {
	HRESULT			hr;
	BSTR host;
	hr = -1;
	hr = iIArkivLauncher->get_Version( &host );

	if( SUCCEEDED(hr) ){
		Wc2Str( host, cbufHost, 0 );
	}
	else {
		strcpy( cbufHost, "IArkivLauncher->get_Version() Error occured !" );
	}


	return hr;
}

/**
* Invoke Update method from Arkiv ActiveX
*
*/
int ArkivAdapterUpdate(ILauncher *iIArkivLauncher){
	HRESULT			hr;
	hr = iIArkivLauncher->Update();

	return hr;
}

/**
* Invoke PutAuthentificationTicket method from Arkiv ActiveX
*
*/
int ArkivAdapterPut_AuthenticationTicket(ILauncher *iIArkivLauncher,char *cbufTicket ){
	HRESULT			hr;
	_bstr_t ticket(cbufTicket);

	hr = -1;
	hr = iIArkivLauncher->put_AuthenticationTicket(ticket.GetBSTR());

	return hr;
}

/**
* Invoke IsGameStarted method from Arkiv ActiveX
*
*/
int ArkivAdapterGet_IsGameStarted(ILauncher *iIArkivLauncher, bool *isStarted){
	HRESULT			hr;
	VARIANT_BOOL started;

	hr = -1;
	hr = iIArkivLauncher->get_IsGameStarted(&started);
	(*isStarted) = (started == VARIANT_TRUE);

	return hr;
}

/**
* Invoke SetSilentModeEnabled method from Arkiv ActiveX
*
*/
int ArkivAdapterGet_SetSilentModeEnabled(ILauncher *iIArkivLauncher, bool silendMode){
	HRESULT			hr;
	VARIANT_BOOL silent = silendMode ? VARIANT_TRUE : VARIANT_FALSE;

	hr = -1;
	hr = iIArkivLauncher->SetSilentModeEnabled(silent);

	return hr;
}

/**
* Invoke UnhideApp method from Arkiv ActiveX
*
*/
int ArkivAdapterGet_UnhideApp(ILauncher *iIArkivLauncher)
{
	HRESULT			hr;

	hr = -1;
	hr = iIArkivLauncher->UnhideApp();

	return hr;
}

/**
* Invoke BringAppToFront method from Arkiv ActiveX
*
*/
int ArkivAdapterBringAppToFront(ILauncher *iIArkivLauncher)
{
	HRESULT			hr;

	hr = -1;
	hr = iIArkivLauncher->BringAppToFront();

	return hr;
}

/**
* Invoke ResetLaunchState method from Arkiv ActiveX
*
*/
int ArkivAdapterResetLaunchState(ILauncher *iIArkivLauncher)
{
	HRESULT			hr;

	hr = -1;
	hr = iIArkivLauncher->ResetLaunchState();

	return hr;
}

/**
* Invoke SetEditMode method from Arkiv ActiveX
*
*/
int ArkivAdapterSetEditMode(ILauncher *iIArkivLauncher)
{
	HRESULT			hr;

	hr = -1;
	hr = iIArkivLauncher->SetEditMode();

	return hr;
}

/**
* Invoke SetStartInHiddenMode method from Arkiv ActiveX
*
*/
int ArkivAdapterGet_SetStartInHiddenMode(ILauncher *iIArkivLauncher, bool hiddenMode){
	HRESULT			hr;
	VARIANT_BOOL hidden = hiddenMode ? VARIANT_TRUE : VARIANT_FALSE;

	hr = -1;
	hr = iIArkivLauncher->SetStartInHiddenMode(hidden);

	return hr;
}

/**
* Invoke get_IsUpToDate method from Arkiv ActiveX
*
*/
int ArkivAdapterGet_IsUpToDate(ILauncher *iIArkivLauncher, bool *isUpToDate){
	int hr;
	VARIANT_BOOL upToDate = VARIANT_FALSE;

	hr = -1;
	hr = iIArkivLauncher->get_IsUpToDate(&upToDate);

	*isUpToDate = (upToDate == VARIANT_TRUE);
	
	return hr;
}

/**
* Invoke GetKeyValue method from Arkiv ActiveX
*
*/
int ArkivAdapterGetKeyValue(ILauncher *iIArkivLauncher, char *key, char *value)
{
	int hr = -1;
	_bstr_t bstrKey(key);
	BSTR bstrValue;
	VARIANT_BOOL exists = VARIANT_FALSE;

	hr = iIArkivLauncher->GetKeyValue(bstrKey, &bstrValue);
	if (SUCCEEDED(hr))
	{
		Wc2Str(bstrValue, value, 0);
	} else {
		value = NULL;
	}

	return hr;
}

/**
* Invoke SetKeyValue method from Arkiv ActiveX
*
*/
int ArkivAdapterSetKeyValue(ILauncher *iIArkivLauncher, char *key, char *value)
{
	_bstr_t bstrKey(key);
	_bstr_t bstrValue(value);

	return iIArkivLauncher->SetKeyValue(bstrKey, bstrValue);
}

/**
* Invoke DeleteKeyValue method from Arkiv ActiveX
*
*/
int ArkivAdapterDeleteKeyValue(ILauncher *iIArkivLauncher, char *key)
{
	_bstr_t bstrKey(key);

	return iIArkivLauncher->DeleteKeyValue(bstrKey);
}

