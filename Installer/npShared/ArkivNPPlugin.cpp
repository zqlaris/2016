/*
 *  ArkivNPPlugin.cpp
 *  NPArkivMac
 *
 *  Created by Aaron Wilkowski on 1/4/12.
 *  Copyright 2012 Arkiv. All rights reserved.
 *
 */

#include <string>
#include "ArkivNPPlugin.h"
#include <map>





ArkivNPPlugin *ArkivNPPlugin::_instance = 0;

ArkivNPPlugin *ArkivNPPlugin::Instance(){
	if (_instance == 0) {
		_instance = new ArkivNPPlugin;
	}
	return _instance;
}

ArkivNPPlugin objList;
ArkivNPPlugin *sObjList = objList.Instance();

NPError aCreate(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char *argn[], char *argv[], NPSavedData *saved){
	return objList.create(pluginType, instance, mode, argc, argn, argv, saved);
}
NPError aDestroy(NPP instance, NPSavedData **save){
	return objList.destroy(instance, save);
}
NPError aGetValue(NPP instance, NPPVariable variable, void *value){
	return objList.getValue(instance, variable, value);
}
NPError aHandleEvent(NPP instance, void *ev){
	return objList.handleEvent(instance, ev);
}
NPError aSetWindow(NPP instance, NPWindow* pNPWindow){
	return objList.setWindow(instance, pNPWindow);
}

extern "C"
{
	//exposed functions
	
	NPError OSCALL NP_GetEntryPoints(NPPluginFuncs *nppfuncs) 
	{
		objList.writeLogEntry("NP_GetEntryPoints --> Begin");
		
		if (nppfuncs == NULL)
		{
			objList.writeLogEntry("-- ERROR: nppfuncs is NULL");
			return NPERR_GENERIC_ERROR;
		}
		
		nppfuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
		nppfuncs->newp          = aCreate;
		nppfuncs->destroy       = aDestroy;
		nppfuncs->getvalue      = aGetValue;
		nppfuncs->event         = aHandleEvent;
		nppfuncs->setwindow     = aSetWindow;
		
		objList.writeLogEntry("NP_GetEntryPoints <-- End");
		
		return NPERR_NO_ERROR;
	}
	
#ifndef HIBYTE
#define HIBYTE(x) ((((uint32)(x)) & 0xff00) >> 8)
#endif
	
	NPError OSCALL NP_Initialize(NPNetscapeFuncs *npnf)
	{
		objList.writeLogEntry("NP_Initialize --> Begin");
		
		if(npnf == NULL)
		{
			objList.writeLogEntry("-- Error: npnf is NULL.");
			return NPERR_INVALID_FUNCTABLE_ERROR;
		}
		
		if (HIBYTE(npnf->version) > NP_VERSION_MAJOR)
		{
			objList.writeLogEntry("-- Error: version issue.");
			return NPERR_INCOMPATIBLE_VERSION_ERROR;
		}
		
		//s_netscape_funcs = npnf;
		sObjList->npnfs = npnf; 
		
		objList.writeLogEntry("NP_Initialize <-- End");
		
		return NPERR_NO_ERROR;
	}
	
	NPError OSCALL NP_Shutdown() 
	{
		objList.writeLogEntry("NP_Shutdown --> Begin");
		objList.writeLogEntry("NP_Shutdown <-- End\n");
		return NPERR_NO_ERROR;
	}
	
	const char *NP_GetMIMEDescription(void) 
	{
		return (const char *)MIME_DESCRIPTION;
	}
	
	
	/* needs to be present for WebKit based browsers */
	NPError OSCALL NP_GetValue(void *npp, NPPVariable variable, void *value) 
	{
		objList.writeLogEntry("NP_GetValue --> Begin");
		NPError ret_val = aGetValue((NPP)npp, variable, value);
		objList.writeLogEntry("NP_GetValue <-- End");
		return ret_val;
	}
}
//end C

static bool invokeArkivAdapterHelloWorld(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterHelloWorld 0x%8.8x", (void*)obj);
	IArkivLauncher * arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	
	if (arkivLauncher == NULL) {
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		result->value.intValue = arkivLauncher->HelloWorld();
	}
	
	objList.writeLogEntry("NPArkivProxy: ArkivAdapterHelloWorld result = %d", result->value.intValue);
	
	return true;
}

static bool invokeArkivAdapterHello(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	char ssMess[2048];
	uint32_t size = (uint32_t)strlen(ssMess) + 1;
	objList.writeLogEntry("invokeArkivAdapterHello 0x%8.8x", (void*)obj);
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	if (arkivLauncher == NULL) {
		objList.writeLogEntry("ERROR: Launcher not found");
		result->type = NPVariantType_Int32;
		result->value.intValue = -1;
	} else {
		result->type = NPVariantType_String;
		int hr = arkivLauncher->Hello(ssMess);
		objList.writeLogEntry("IArkivLauncher->Hello() result %d", hr);
		size = (uint32_t)strlen(ssMess) + 1;
		result->value.stringValue.UTF8_LENGTH = size - 1;
		
		result->value.stringValue.UTF8_CHARACTERS = (const NPUTF8 *)sObjList->npnfs->memalloc(size);
		strcpy( (char *)result->value.stringValue.UTF8_CHARACTERS, ssMess );
	}
	
	objList.writeLogEntry("ArkivAdapterHello result=%d size=%d ssMess=%s", result->value.intValue, size, ssMess);
	
	return true;
}

static bool invokeArkivAdapterStartGame(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterStartGame 0x%8.8x", (void*)obj);
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL) {
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		if (argCount != 2) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterStartGame argCount!=2");
			return true;
		}
		if (args[0].type != NPVariantType_String || args[1].type != NPVariantType_String ){
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterStartGame Bad arguments type : MUST BE String");
			return true;
		}
		
		std::vector<char> zauthFF(args[0].value.stringValue.UTF8_LENGTH + 1);
		memcpy(&zauthFF[0], args[0].value.stringValue.UTF8_CHARACTERS, args[0].value.stringValue.UTF8_LENGTH);
		zauthFF[args[0].value.stringValue.UTF8_LENGTH] = 0;
		
		std::vector<char> zscriptFF(args[1].value.stringValue.UTF8_LENGTH + 1);
		memcpy(&zscriptFF[0], args[1].value.stringValue.UTF8_CHARACTERS, args[1].value.stringValue.UTF8_LENGTH);
		zscriptFF[args[1].value.stringValue.UTF8_LENGTH] = 0;
		
		objList.writeLogEntry("ArkivAdapterStartGame Auth = %s, Script = %s", &zauthFF[0], &zscriptFF[0]);
		result->value.intValue = arkivLauncher->StartGame(&zauthFF[0], &zscriptFF[0]);
	}
	
	objList.writeLogEntry("ArkivAdapterStartGame result=%d", result->value.intValue);
	return true;
}

static bool invokeArkivAdapterPreStartGame(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterPreStartGame 0x%8.8x", (void*)obj);
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL) {
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		if (argCount != 0) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterPreStartGame argCount!=0");
			return true;
		}
		
		result->value.intValue = arkivLauncher->PreStartGame();
	}
	
	objList.writeLogEntry("ArkivAdapterPreStartGame result=%d", result->value.intValue);
	return true;
}


static bool invokeArkivAdapterGet_InstallHost(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	char ssMess[2048];
	uint32_t size=(uint32_t)strlen(ssMess) + 1;
	
	objList.writeLogEntry("invokeArkivAdapterGet_InstallHost 0x%8.8x", (void*)obj);
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	if (arkivLauncher == NULL) {
		objList.writeLogEntry("ERROR: Launcher not found");
		result->type = NPVariantType_Int32;
		result->value.intValue = -1;
	} else {
		result->type = NPVariantType_String;
		int hr = arkivLauncher->GetInstallHost(ssMess);
		
		size=(uint32_t)strlen(ssMess) + 1;
		// buggy way of doing things, once web site updated use commented line bellow
		result->value.stringValue.UTF8_LENGTH = size;
		// result->value.stringValue.UTF8_LENGTH = size - 1;
		
		result->value.stringValue.UTF8_CHARACTERS = (const NPUTF8 *) sObjList->npnfs->memalloc(size);
		strcpy((char *)result->value.stringValue.UTF8_CHARACTERS, ssMess);
	}
	
	objList.writeLogEntry("ArkivAdapterGet_InstallHost result=%d size=%d ssMess=%s", result->value.intValue, size, ssMess);
	
	return true;
}


static bool invokeArkivAdapterUpdate(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterUpdate 0x%8.8x", (void*)obj);
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL) {
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		result->value.intValue = arkivLauncher->Update();
	}
	
	return true;
}


static bool invokeArkivAdapterPut_AuthenticationTicket(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterPut_AuthenticationTicket 0x%8.8x", (void*)obj);
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL){
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		if (argCount != 1) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterPut_AuthenticationTicket argCount!=1");
			return true;
		}
		
		if (args[0].type != NPVariantType_String) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterPut_AuthenticationTicket Bad arguments type : MUST BE String");
			return true;
		}
		std::vector<char> zticket(args[0].value.stringValue.UTF8_LENGTH + 1);
		memcpy(&zticket[0], args[0].value.stringValue.UTF8_CHARACTERS, args[0].value.stringValue.UTF8_LENGTH);
		zticket[args[0].value.stringValue.UTF8_LENGTH] = 0;
		
		objList.writeLogEntry("ArkivAdapterPut_AuthenticationTicket Ticket = %s", &zticket[0]);
		result->value.intValue = arkivLauncher->Put_AuthenticationTicket(&zticket[0]);
	}
	
	objList.writeLogEntry("ArkivAdapterPut_AuthenticationTicket result=%d", result->value.intValue);
	
	return true;
}


static bool invokeArkivAdapterGet_IsGameStarted(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterGet_IsGameStarted 0x%8.8x", (void*)obj);
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Bool;
	if (arkivLauncher == NULL){
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.boolValue = 0;
	} else {
		bool started;
		int hr = arkivLauncher->IsGameStarted(&started);
		objList.writeLogEntry("ArkivAdapterGet_IsGameStarted HRESULT = %d", hr);
		result->value.boolValue = started;
	}
	
	objList.writeLogEntry("invokeArkivAdapterGet_IsGameStarted result=%d", result->value.boolValue);
	
	return true;
}

static bool invokeArkivAdapterGet_SetSilentModeEnabled(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterGet_IsGameStarted 0x%8.8x", (void*)obj);
	
	char *cbufTicket = NULL;
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL){
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		if (argCount != 1) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterGet_SetSilentModeEnabled argCount!=1");
			return true;
		}
		
		if (args[0].type != NPVariantType_Bool) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterGet_SetSilentModeEnabled Bad arguments type : MUST be BOOL");
			return true;
		}
		
		result->value.intValue = arkivLauncher->SetSilentModeEnabled(NPVARIANT_TO_BOOLEAN(args[0]));
	}
	
	objList.writeLogEntry("invokeArkivAdapterGet_IsGameStarted result=%d", result->value.intValue);
	
	return true;
}

static bool invokeArkivAdapterGet_SetStartInHiddenMode(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterGet_SetStartInHiddenMode 0x%8.8x", (void*)obj);
	
	char *cbufTicket = NULL;
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL){
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		if (argCount != 1) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterGet_SetStartInHiddenMode argCount!=1");
			return true;
		}
		
		if (args[0].type != NPVariantType_Bool) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("ArkivAdapterGet_SetStartInHiddenMode Bad arguments type : MUST be BOOL");
			return true;
		}
		
		result->value.intValue = arkivLauncher->SetStartInHiddenMode(NPVARIANT_TO_BOOLEAN(args[0]));
	}
	
	objList.writeLogEntry("invokeArkivAdapterGet_SetStartInHiddenMode result=%d", result->value.intValue);
	
	return true;
}


static bool invokeArkivAdapterGet_UnhideApp(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterGet_UnhideApp 0x%8.8x", (void*)obj);
	
	char *cbufTicket = NULL;
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL){
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		if (argCount != 0) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("invokeArkivAdapterGet_UnhideApp argCount!=0");
			return true;
		}
		
		result->value.intValue = arkivLauncher->UnhideApp();
	}
	
	objList.writeLogEntry("invokeArkivAdapterGet_UnhideApp result=%d", result->value.intValue);
	
	return true;
}

static bool invokeArkivAdapterBringAppToFront(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterBringAppToFront 0x%8.8x", (void*)obj);
	
	char *cbufTicket = NULL;
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL){
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		if (argCount != 0) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("invokeArkivAdapterBringAppToFront argCount!=0");
			return true;
		}
		
		result->value.intValue = arkivLauncher->BringAppToFront();
	}
	
	objList.writeLogEntry("invokeArkivAdapterBringAppToFront result=%d", result->value.intValue);
	
	return true;
}

static bool invokeArkivAdapterResetLaunchState(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterResetLaunchState 0x%8.8x", (void*)obj);
	
	char *cbufTicket = NULL;
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Int32;
	if (arkivLauncher == NULL){
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.intValue = -1;
	} else {
		if (argCount != 0) {
			result->value.intValue = -1;
			
			objList.writeLogEntry("invokeArkivAdapterBringAppToFront argCount!=0");
			return true;
		}
		
		result->value.intValue = arkivLauncher->ResetLaunchState();
	}
	
	objList.writeLogEntry("invokeArkivAdapterBringAppToFront result=%d", result->value.intValue);
	
	return true;
}

static bool invokeArkivAdapterGet_IsUpToDate(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterGet_IsUpToDate 0x%8.8x", (void*)obj);
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	
	result->type = NPVariantType_Bool;
	if (arkivLauncher == NULL){
		objList.writeLogEntry("ERROR: Launcher not found");
		result->value.boolValue = 0;
	} else {
		bool isUpToDate;
		int hr = arkivLauncher->IsUpToDate(&isUpToDate);
		objList.writeLogEntry("ArkivAdapterGet_IsUpToDate HRESULT = %d", hr);
		result->value.boolValue = isUpToDate;
	}
	
	objList.writeLogEntry("invokeArkivAdapterGet_IsUpToDate result=%d", result->value.boolValue);
	
	return true;
}

static bool invokeArkivAdapterGetKeyValue(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterGetKeyValue");
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	result->type = NPVariantType_String;
	if (arkivLauncher == NULL) {
		result->type = NPVariantType_Int32;
		result->value.intValue = -1;
	} else {
		if (argCount != 1) {
			result->type = NPVariantType_Int32;
			result->value.intValue = -1;
			
			objList.writeLogEntry("invokeArkivAdapterGetKeyValue argCount != 1");
			return true;
		}
		
		if (args[0].type != NPVariantType_String) {
			result->value.intValue = -1;
			result->type = NPVariantType_Int32;
			
			objList.writeLogEntry("invokeArkivAdapterGetKeyValue arg[0] : must be string");
			return true;
		}
		char *key = (char *)args[0].value.stringValue.UTF8_CHARACTERS;
		
		std::vector<char> zkey(args[0].value.stringValue.UTF8_LENGTH + 1);
		memcpy(&zkey[0], args[0].value.stringValue.UTF8_CHARACTERS, args[0].value.stringValue.UTF8_LENGTH);
		zkey[args[0].value.stringValue.UTF8_LENGTH] = 0;
		
		objList.writeLogEntry("invokeArkivAdapterGetKeyValue key = %s len = %d", &zkey[0], args[0].value.stringValue.UTF8_LENGTH);
		char strValue[2048] = {0};
		
		int hr = arkivLauncher->GetKeyValue(&zkey[0], strValue);
		if (hr > 0) // !Failed
		{
			int size = (uint32_t)strlen(strValue) + 1;
			result->value.stringValue.UTF8_LENGTH = size - 1;
			objList.writeLogEntry("invokeArkivAdapterGetKeyValue value = %s len = %d", strValue, result->value.stringValue.UTF8_LENGTH);
			
			result->value.stringValue.UTF8_CHARACTERS = (const NPUTF8 *) sObjList->npnfs->memalloc(size);
			strcpy((char *)result->value.stringValue.UTF8_CHARACTERS, strValue);
		} else {
			result->value.intValue = -1;
			result->type = NPVariantType_Int32;
			
			objList.writeLogEntry("invokeArkivAdapterGetKeyValue failed error = %d", hr);
		}
	}
	return true;
}

static bool invokeArkivAdapterSetKeyValue(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterSetKeyValue");
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	result->type = NPVariantType_Int32;
	result->value.intValue = -1;
	if (arkivLauncher != NULL) {
		if (argCount != 2) {
			objList.writeLogEntry("invokeArkivAdapterSetKeyValue argCount != 2");
			return true;
		}
		
		if (args[0].type != NPVariantType_String) {
			objList.writeLogEntry("invokeArkivAdapterSetKeyValue arg[0] : must be string");
			return true;
		}
		
		if (args[1].type != NPVariantType_String) {
			objList.writeLogEntry("invokeArkivAdapterSetKeyValue arg[1] : must be string");
			return true;
		}
		
		std::vector<char> zkey(args[0].value.stringValue.UTF8_LENGTH + 1);
		memcpy(&zkey[0], args[0].value.stringValue.UTF8_CHARACTERS, args[0].value.stringValue.UTF8_LENGTH);
		zkey[args[0].value.stringValue.UTF8_LENGTH] = 0;
		
		std::vector<char> zvalue(args[1].value.stringValue.UTF8_LENGTH + 1);
		memcpy(&zvalue[0], args[1].value.stringValue.UTF8_CHARACTERS, args[1].value.stringValue.UTF8_LENGTH);
		zvalue[args[1].value.stringValue.UTF8_LENGTH] = 0;
		
		result->value.intValue = arkivLauncher->SetKeyValue(&zkey[0], &zvalue[0]);
		if (result->value.intValue != 0) {
			objList.writeLogEntry("ArkivAdapterSetKeyValue returned %d", result->value.intValue);
		}
	}
	
	return true;
}


static bool invokeArkivAdapterDeleteKeyValue(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	objList.writeLogEntry("invokeArkivAdapterDeleteKeyValue");
	
	IArkivLauncher *arkivLauncher = sObjList->find(obj);
	result->type = NPVariantType_Int32;
	result->value.intValue = -1;
	if (arkivLauncher != NULL) {
		if (argCount != 1) {
			objList.writeLogEntry("invokeArkivAdapterDeleteKeyValue argCount != 1");
			return true;
		}
		
		if (args[0].type != NPVariantType_String) {
			objList.writeLogEntry("invokeArkivAdapterDeleteKeyValue arg[0] : must be string");
			return true;
		}
		
		std::vector<char> zkey(args[0].value.stringValue.UTF8_LENGTH + 1);
		memcpy(&zkey[0], args[0].value.stringValue.UTF8_CHARACTERS, args[0].value.stringValue.UTF8_LENGTH);
		zkey[args[0].value.stringValue.UTF8_LENGTH] = 0;
		
		result->value.intValue = arkivLauncher->DeleteKeyValue(&zkey[0]);// ArkivAdapterDeleteKeyValue(arkivLauncher, &zkey[0]);
		
		//_launcher->DeleteKeyValue(%zkey[0]);
		
		if (result->value.intValue != 0) {
			objList.writeLogEntry("ArkivAdapterDeleteKeyValue returned %d", result->value.intValue);
		}
	}
	return true;
}



typedef bool (*invokePtr)(NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result);

static std::map<std::string, invokePtr> InitKnownMethods()
{
	std::map<std::string, invokePtr> result;
	
	// javascript interface method declaration
	result["HelloWorld"] = invokeArkivAdapterHelloWorld;
	result["Hello"] = invokeArkivAdapterHello;
	result["StartGame"] = invokeArkivAdapterStartGame;
	result["PreStartGame"] = invokeArkivAdapterPreStartGame;
	result["Get_InstallHost"] = invokeArkivAdapterGet_InstallHost;
	result["Update"] = invokeArkivAdapterUpdate;
	result["Put_AuthenticationTicket"] = invokeArkivAdapterPut_AuthenticationTicket;
	result["Get_GameStarted"] = invokeArkivAdapterGet_IsGameStarted;
	result["SetSilentModeEnabled"] = invokeArkivAdapterGet_SetSilentModeEnabled;
	result["SetStartInHiddenMode"] = invokeArkivAdapterGet_SetStartInHiddenMode;
	result["UnhideApp"] = invokeArkivAdapterGet_UnhideApp;
	result["BringAppToFront"] = invokeArkivAdapterBringAppToFront;
	result["ResetLaunchState"] = invokeArkivAdapterResetLaunchState;
	result["Get_IsUpToDate"] = invokeArkivAdapterGet_IsUpToDate;
	result["GetKeyValue"] = invokeArkivAdapterGetKeyValue;
	result["SetKeyValue"] = invokeArkivAdapterSetKeyValue;
	result["DeleteKeyValue"] = invokeArkivAdapterDeleteKeyValue;
	
	
	
	return result;
}

/**
 * Invoke GetInstallHost method from Arkiv ActiveX
 *
 */
bool invoke(NPObject* obj, NPIdentifier methodName, const NPVariant *args, uint32_t argCount, NPVariant *result) {
	//gPlugin->invoke(obj, );
	objList.writeLogEntry("invoke");
	static std::map<std::string, invokePtr> methods = InitKnownMethods();
	
	char *name = sObjList->npnfs->utf8fromidentifier(methodName);
	if (name != NULL && methods[name] != NULL)
	{
		return methods[name](obj, args, argCount, result);
	} 
	else
	{
		// aim exception handling
		sObjList->npnfs->setexception(obj, "exception during invocation");
		return false;
	}
}

bool hasMethod(NPObject* obj, NPIdentifier methodName) 
{
	return true;
}

bool hasProperty(NPObject *obj, NPIdentifier propertyName) 
{
	return false;
}

bool getProperty(NPObject *obj, NPIdentifier propertyName, NPVariant *result) 
{
	return false;
}




