#ifndef _ROLBOX_ADAPTER_H_
#define _ROLBOX_ADAPTER_H_

void StartCom(void);
void StopCom(void);
bool isComStarted(void);

ILauncher * GetIArkivLauncherInstance(void);

int ArkivAdapterHelloWorld(ILauncher *iIArkivLauncher);
int ArkivAdapterHello(ILauncher *iIArkivLauncher,char *retMessage);
int ArkivAdapterStartGame(ILauncher *iIArkivLauncher,char *cbufAuth, char *cbufScript );
int ArkivAdapterPreStartGame(ILauncher *iIArkivLauncher);
int ArkivAdapterGet_InstallHost(ILauncher *iIArkivLauncher,char *cbufHost);
int ArkivAdapterGet_Version(ILauncher *iIArkivLauncher,char *cbufHost);
int ArkivAdapterUpdate(ILauncher *iIArkivLauncher);
int ArkivAdapterPut_AuthenticationTicket(ILauncher *iIArkivLauncher,char *cbufTicket );
int ArkivAdapterGet_IsGameStarted(ILauncher *iIArkivLauncher, bool *isStarted);
int ArkivAdapterGet_SetSilentModeEnabled(ILauncher *iIArkivLauncher, bool silendMode);
int ArkivAdapterGet_UnhideApp(ILauncher *iIArkivLauncher);
int ArkivAdapterBringAppToFront(ILauncher *iIArkivLauncher);
int ArkivAdapterResetLaunchState(ILauncher *iIArkivLauncher);
int ArkivAdapterSetEditMode(ILauncher *iIArkivLauncher);
int ArkivAdapterGet_SetStartInHiddenMode(ILauncher *iIArkivLauncher, bool hiddenMode);
int ArkivAdapterGet_IsUpToDate(ILauncher *iIArkivLauncher, bool *isUpToDate);
int ArkivAdapterGetKeyValue(ILauncher *iIArkivLauncher, char *key, char *value);
int ArkivAdapterSetKeyValue(ILauncher *iIArkivLauncher, char *key, char *value);
int ArkivAdapterDeleteKeyValue(ILauncher *iIArkivLauncher, char *key);

#endif



