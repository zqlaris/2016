// dllmain.h : Declaration of module class.

class CArkivProxyModule : public CAtlDllModuleT< CArkivProxyModule >
{
public :
	DECLARE_LIBID(LIBID_ArkivProxyLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ARKIVPROXY, "{664B192B-D17A-4921-ABF9-C6F6264E5110}")
};

extern class CArkivProxyModule _AtlModule;


