/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 13 09:09:00 2004
 */
/* Compiler settings for S:\NeroSDK\Sources\NeroCBUI\Src\NeroCBUI.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __NeroCBUI_h__
#define __NeroCBUI_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __InitSettings_FWD_DEFINED__
#define __InitSettings_FWD_DEFINED__

#ifdef __cplusplus
typedef class InitSettings InitSettings;
#else
typedef struct InitSettings InitSettings;
#endif /* __cplusplus */

#endif 	/* __InitSettings_FWD_DEFINED__ */


#ifndef __BurnSettings_FWD_DEFINED__
#define __BurnSettings_FWD_DEFINED__

#ifdef __cplusplus
typedef class BurnSettings BurnSettings;
#else
typedef struct BurnSettings BurnSettings;
#endif /* __cplusplus */

#endif 	/* __BurnSettings_FWD_DEFINED__ */


#ifndef __RecorderCombobox_FWD_DEFINED__
#define __RecorderCombobox_FWD_DEFINED__

#ifdef __cplusplus
typedef class RecorderCombobox RecorderCombobox;
#else
typedef struct RecorderCombobox RecorderCombobox;
#endif /* __cplusplus */

#endif 	/* __RecorderCombobox_FWD_DEFINED__ */


#ifndef __BurnSettingsDlg_FWD_DEFINED__
#define __BurnSettingsDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class BurnSettingsDlg BurnSettingsDlg;
#else
typedef struct BurnSettingsDlg BurnSettingsDlg;
#endif /* __cplusplus */

#endif 	/* __BurnSettingsDlg_FWD_DEFINED__ */


#ifndef __BurnSettingsDlgParam_FWD_DEFINED__
#define __BurnSettingsDlgParam_FWD_DEFINED__

#ifdef __cplusplus
typedef class BurnSettingsDlgParam BurnSettingsDlgParam;
#else
typedef struct BurnSettingsDlgParam BurnSettingsDlgParam;
#endif /* __cplusplus */

#endif 	/* __BurnSettingsDlgParam_FWD_DEFINED__ */


#ifndef __BurnProgressDlg_FWD_DEFINED__
#define __BurnProgressDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class BurnProgressDlg BurnProgressDlg;
#else
typedef struct BurnProgressDlg BurnProgressDlg;
#endif /* __cplusplus */

#endif 	/* __BurnProgressDlg_FWD_DEFINED__ */


#ifndef __ChooseRecorderDlg_FWD_DEFINED__
#define __ChooseRecorderDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChooseRecorderDlg ChooseRecorderDlg;
#else
typedef struct ChooseRecorderDlg ChooseRecorderDlg;
#endif /* __cplusplus */

#endif 	/* __ChooseRecorderDlg_FWD_DEFINED__ */


#ifndef __EraseSettingsDlg_FWD_DEFINED__
#define __EraseSettingsDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class EraseSettingsDlg EraseSettingsDlg;
#else
typedef struct EraseSettingsDlg EraseSettingsDlg;
#endif /* __cplusplus */

#endif 	/* __EraseSettingsDlg_FWD_DEFINED__ */


#ifndef __EraseDiscDlg_FWD_DEFINED__
#define __EraseDiscDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class EraseDiscDlg EraseDiscDlg;
#else
typedef struct EraseDiscDlg EraseDiscDlg;
#endif /* __cplusplus */

#endif 	/* __EraseDiscDlg_FWD_DEFINED__ */


#ifndef __DiscInfoDlg_FWD_DEFINED__
#define __DiscInfoDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class DiscInfoDlg DiscInfoDlg;
#else
typedef struct DiscInfoDlg DiscInfoDlg;
#endif /* __cplusplus */

#endif 	/* __DiscInfoDlg_FWD_DEFINED__ */


#ifndef __ImageInfoDlg_FWD_DEFINED__
#define __ImageInfoDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageInfoDlg ImageInfoDlg;
#else
typedef struct ImageInfoDlg ImageInfoDlg;
#endif /* __cplusplus */

#endif 	/* __ImageInfoDlg_FWD_DEFINED__ */


#ifndef __ImageInfoDlgParam_FWD_DEFINED__
#define __ImageInfoDlgParam_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageInfoDlgParam ImageInfoDlgParam;
#else
typedef struct ImageInfoDlgParam ImageInfoDlgParam;
#endif /* __cplusplus */

#endif 	/* __ImageInfoDlgParam_FWD_DEFINED__ */


#ifndef __ChooseSessionDlg_FWD_DEFINED__
#define __ChooseSessionDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChooseSessionDlg ChooseSessionDlg;
#else
typedef struct ChooseSessionDlg ChooseSessionDlg;
#endif /* __cplusplus */

#endif 	/* __ChooseSessionDlg_FWD_DEFINED__ */


#ifndef __SpeedCombobox_FWD_DEFINED__
#define __SpeedCombobox_FWD_DEFINED__

#ifdef __cplusplus
typedef class SpeedCombobox SpeedCombobox;
#else
typedef struct SpeedCombobox SpeedCombobox;
#endif /* __cplusplus */

#endif 	/* __SpeedCombobox_FWD_DEFINED__ */


#ifndef __WaitForMediaDlg_FWD_DEFINED__
#define __WaitForMediaDlg_FWD_DEFINED__

#ifdef __cplusplus
typedef class WaitForMediaDlg WaitForMediaDlg;
#else
typedef struct WaitForMediaDlg WaitForMediaDlg;
#endif /* __cplusplus */

#endif 	/* __WaitForMediaDlg_FWD_DEFINED__ */


#ifndef __UserDlgHandler_FWD_DEFINED__
#define __UserDlgHandler_FWD_DEFINED__

#ifdef __cplusplus
typedef class UserDlgHandler UserDlgHandler;
#else
typedef struct UserDlgHandler UserDlgHandler;
#endif /* __cplusplus */

#endif 	/* __UserDlgHandler_FWD_DEFINED__ */


#ifndef __IModelessDialog_FWD_DEFINED__
#define __IModelessDialog_FWD_DEFINED__
typedef interface IModelessDialog IModelessDialog;
#endif 	/* __IModelessDialog_FWD_DEFINED__ */


#ifndef __INERO_SCSI_DEVICE_INFO_FWD_DEFINED__
#define __INERO_SCSI_DEVICE_INFO_FWD_DEFINED__
typedef interface INERO_SCSI_DEVICE_INFO INERO_SCSI_DEVICE_INFO;
#endif 	/* __INERO_SCSI_DEVICE_INFO_FWD_DEFINED__ */


#ifndef __IRecorderComboboxCallbacks_FWD_DEFINED__
#define __IRecorderComboboxCallbacks_FWD_DEFINED__
typedef interface IRecorderComboboxCallbacks IRecorderComboboxCallbacks;
#endif 	/* __IRecorderComboboxCallbacks_FWD_DEFINED__ */


#ifndef __IRecorderCombobox_FWD_DEFINED__
#define __IRecorderCombobox_FWD_DEFINED__
typedef interface IRecorderCombobox IRecorderCombobox;
#endif 	/* __IRecorderCombobox_FWD_DEFINED__ */


#ifndef __IRecorderCombobox2_FWD_DEFINED__
#define __IRecorderCombobox2_FWD_DEFINED__
typedef interface IRecorderCombobox2 IRecorderCombobox2;
#endif 	/* __IRecorderCombobox2_FWD_DEFINED__ */


#ifndef __IRecorderCombobox3_FWD_DEFINED__
#define __IRecorderCombobox3_FWD_DEFINED__
typedef interface IRecorderCombobox3 IRecorderCombobox3;
#endif 	/* __IRecorderCombobox3_FWD_DEFINED__ */


#ifndef __IBurnSettings_FWD_DEFINED__
#define __IBurnSettings_FWD_DEFINED__
typedef interface IBurnSettings IBurnSettings;
#endif 	/* __IBurnSettings_FWD_DEFINED__ */


#ifndef __IBurnSettingsDlg_FWD_DEFINED__
#define __IBurnSettingsDlg_FWD_DEFINED__
typedef interface IBurnSettingsDlg IBurnSettingsDlg;
#endif 	/* __IBurnSettingsDlg_FWD_DEFINED__ */


#ifndef __IBurnCallbacks_FWD_DEFINED__
#define __IBurnCallbacks_FWD_DEFINED__
typedef interface IBurnCallbacks IBurnCallbacks;
#endif 	/* __IBurnCallbacks_FWD_DEFINED__ */


#ifndef __IBurnProgressDlgCallbacks_FWD_DEFINED__
#define __IBurnProgressDlgCallbacks_FWD_DEFINED__
typedef interface IBurnProgressDlgCallbacks IBurnProgressDlgCallbacks;
#endif 	/* __IBurnProgressDlgCallbacks_FWD_DEFINED__ */


#ifndef __IBurnProgressDlg_FWD_DEFINED__
#define __IBurnProgressDlg_FWD_DEFINED__
typedef interface IBurnProgressDlg IBurnProgressDlg;
#endif 	/* __IBurnProgressDlg_FWD_DEFINED__ */


#ifndef __IBurnProgressDlg2_FWD_DEFINED__
#define __IBurnProgressDlg2_FWD_DEFINED__
typedef interface IBurnProgressDlg2 IBurnProgressDlg2;
#endif 	/* __IBurnProgressDlg2_FWD_DEFINED__ */


#ifndef __IExternalChildWindow_FWD_DEFINED__
#define __IExternalChildWindow_FWD_DEFINED__
typedef interface IExternalChildWindow IExternalChildWindow;
#endif 	/* __IExternalChildWindow_FWD_DEFINED__ */


#ifndef __IBurnProgressDlg3_FWD_DEFINED__
#define __IBurnProgressDlg3_FWD_DEFINED__
typedef interface IBurnProgressDlg3 IBurnProgressDlg3;
#endif 	/* __IBurnProgressDlg3_FWD_DEFINED__ */


#ifndef __IBurnProgressDlgEx_FWD_DEFINED__
#define __IBurnProgressDlgEx_FWD_DEFINED__
typedef interface IBurnProgressDlgEx IBurnProgressDlgEx;
#endif 	/* __IBurnProgressDlgEx_FWD_DEFINED__ */


#ifndef __IModalDialog_FWD_DEFINED__
#define __IModalDialog_FWD_DEFINED__
typedef interface IModalDialog IModalDialog;
#endif 	/* __IModalDialog_FWD_DEFINED__ */


#ifndef __INEROAPI_CDRW_ERASE_MODE_FWD_DEFINED__
#define __INEROAPI_CDRW_ERASE_MODE_FWD_DEFINED__
typedef interface INEROAPI_CDRW_ERASE_MODE INEROAPI_CDRW_ERASE_MODE;
#endif 	/* __INEROAPI_CDRW_ERASE_MODE_FWD_DEFINED__ */


#ifndef __IEraseDiscDlg_FWD_DEFINED__
#define __IEraseDiscDlg_FWD_DEFINED__
typedef interface IEraseDiscDlg IEraseDiscDlg;
#endif 	/* __IEraseDiscDlg_FWD_DEFINED__ */


#ifndef __IEraseDiscDlg2_FWD_DEFINED__
#define __IEraseDiscDlg2_FWD_DEFINED__
typedef interface IEraseDiscDlg2 IEraseDiscDlg2;
#endif 	/* __IEraseDiscDlg2_FWD_DEFINED__ */


#ifndef __IEraseDiscCallbacks_FWD_DEFINED__
#define __IEraseDiscCallbacks_FWD_DEFINED__
typedef interface IEraseDiscCallbacks IEraseDiscCallbacks;
#endif 	/* __IEraseDiscCallbacks_FWD_DEFINED__ */


#ifndef __IEraseDiscDlg3_FWD_DEFINED__
#define __IEraseDiscDlg3_FWD_DEFINED__
typedef interface IEraseDiscDlg3 IEraseDiscDlg3;
#endif 	/* __IEraseDiscDlg3_FWD_DEFINED__ */


#ifndef __IEraseDiscDlg4_FWD_DEFINED__
#define __IEraseDiscDlg4_FWD_DEFINED__
typedef interface IEraseDiscDlg4 IEraseDiscDlg4;
#endif 	/* __IEraseDiscDlg4_FWD_DEFINED__ */


#ifndef __IEraseSettingsDlg_FWD_DEFINED__
#define __IEraseSettingsDlg_FWD_DEFINED__
typedef interface IEraseSettingsDlg IEraseSettingsDlg;
#endif 	/* __IEraseSettingsDlg_FWD_DEFINED__ */


#ifndef __IEraseSettingsDlg2_FWD_DEFINED__
#define __IEraseSettingsDlg2_FWD_DEFINED__
typedef interface IEraseSettingsDlg2 IEraseSettingsDlg2;
#endif 	/* __IEraseSettingsDlg2_FWD_DEFINED__ */


#ifndef __IInitSettings_FWD_DEFINED__
#define __IInitSettings_FWD_DEFINED__
typedef interface IInitSettings IInitSettings;
#endif 	/* __IInitSettings_FWD_DEFINED__ */


#ifndef __IInitSettings2_FWD_DEFINED__
#define __IInitSettings2_FWD_DEFINED__
typedef interface IInitSettings2 IInitSettings2;
#endif 	/* __IInitSettings2_FWD_DEFINED__ */


#ifndef __IInitSettings3_FWD_DEFINED__
#define __IInitSettings3_FWD_DEFINED__
typedef interface IInitSettings3 IInitSettings3;
#endif 	/* __IInitSettings3_FWD_DEFINED__ */


#ifndef __IInformation_FWD_DEFINED__
#define __IInformation_FWD_DEFINED__
typedef interface IInformation IInformation;
#endif 	/* __IInformation_FWD_DEFINED__ */


#ifndef __IChildWindow_FWD_DEFINED__
#define __IChildWindow_FWD_DEFINED__
typedef interface IChildWindow IChildWindow;
#endif 	/* __IChildWindow_FWD_DEFINED__ */


#ifndef __IImageInfoDlg_FWD_DEFINED__
#define __IImageInfoDlg_FWD_DEFINED__
typedef interface IImageInfoDlg IImageInfoDlg;
#endif 	/* __IImageInfoDlg_FWD_DEFINED__ */


#ifndef __IChooseSessionDlg_FWD_DEFINED__
#define __IChooseSessionDlg_FWD_DEFINED__
typedef interface IChooseSessionDlg IChooseSessionDlg;
#endif 	/* __IChooseSessionDlg_FWD_DEFINED__ */


#ifndef __ISpeedComboboxCallbacks_FWD_DEFINED__
#define __ISpeedComboboxCallbacks_FWD_DEFINED__
typedef interface ISpeedComboboxCallbacks ISpeedComboboxCallbacks;
#endif 	/* __ISpeedComboboxCallbacks_FWD_DEFINED__ */


#ifndef __ISpeedCombobox_FWD_DEFINED__
#define __ISpeedCombobox_FWD_DEFINED__
typedef interface ISpeedCombobox ISpeedCombobox;
#endif 	/* __ISpeedCombobox_FWD_DEFINED__ */


#ifndef __ISpeedCombobox2_FWD_DEFINED__
#define __ISpeedCombobox2_FWD_DEFINED__
typedef interface ISpeedCombobox2 ISpeedCombobox2;
#endif 	/* __ISpeedCombobox2_FWD_DEFINED__ */


#ifndef __IWaitForMediaDlg_FWD_DEFINED__
#define __IWaitForMediaDlg_FWD_DEFINED__
typedef interface IWaitForMediaDlg IWaitForMediaDlg;
#endif 	/* __IWaitForMediaDlg_FWD_DEFINED__ */


#ifndef __IUserDlgHandler_FWD_DEFINED__
#define __IUserDlgHandler_FWD_DEFINED__
typedef interface IUserDlgHandler IUserDlgHandler;
#endif 	/* __IUserDlgHandler_FWD_DEFINED__ */


#ifndef __IMfcPropertyPage_FWD_DEFINED__
#define __IMfcPropertyPage_FWD_DEFINED__
typedef interface IMfcPropertyPage IMfcPropertyPage;
#endif 	/* __IMfcPropertyPage_FWD_DEFINED__ */


#ifndef __IPrivateDeviceInfos_FWD_DEFINED__
#define __IPrivateDeviceInfos_FWD_DEFINED__
typedef interface IPrivateDeviceInfos IPrivateDeviceInfos;
#endif 	/* __IPrivateDeviceInfos_FWD_DEFINED__ */


#ifndef __IPrivateImageInfoDlg_FWD_DEFINED__
#define __IPrivateImageInfoDlg_FWD_DEFINED__
typedef interface IPrivateImageInfoDlg IPrivateImageInfoDlg;
#endif 	/* __IPrivateImageInfoDlg_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_NeroCBUI_0000 */
/* [local] */ 

#if 0
typedef long LPNERO_SCSI_DEVICE_INFO;

typedef long LPCNERO_SCSI_DEVICE_INFO;

typedef long LPNERO_SCSI_DEVICE_INFOS;

typedef long LPCNERO_SCSI_DEVICE_INFOS;

typedef void __RPC_FAR *NERO_DEVICEHANDLE;

typedef LONG NERO_TEXT_TYPE;

typedef LONG NERO_CD_FORMAT;

typedef LONG NEROAPI_BURN_ERROR;

typedef LONG NEROAPI_CDRW_ERASE_MODE;

typedef LONG NERO_MEDIA_TYPE;

typedef LONG NERO_MEDIA_SET;

typedef LONG NERO_MAJOR_PHASE;

typedef LONG NeroUserDlgInOut;

#endif
#ifdef REGISTER_PROXY_DLL
#include "..\..\NeroAPI6Package\Include\NeroAPIGlue.h"
#endif
typedef NERO_SCSI_DEVICE_INFO * LPNERO_SCSI_DEVICE_INFO;
typedef const NERO_SCSI_DEVICE_INFO * LPCNERO_SCSI_DEVICE_INFO;
typedef NERO_SCSI_DEVICE_INFOS * LPNERO_SCSI_DEVICE_INFOS;
typedef const NERO_SCSI_DEVICE_INFOS * LPCNERO_SCSI_DEVICE_INFOS;


extern RPC_IF_HANDLE __MIDL_itf_NeroCBUI_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_NeroCBUI_0000_v0_0_s_ifspec;


#ifndef __NEROCBUILib_LIBRARY_DEFINED__
#define __NEROCBUILib_LIBRARY_DEFINED__

/* library NEROCBUILib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_NEROCBUILib;

EXTERN_C const CLSID CLSID_InitSettings;

#ifdef __cplusplus

class DECLSPEC_UUID("9871f8af-152a-4651-834c-cdc5fe61c14c")
InitSettings;
#endif

EXTERN_C const CLSID CLSID_BurnSettings;

#ifdef __cplusplus

class DECLSPEC_UUID("ec39bf14-ca12-46cd-8ea2-b48d5a44350a")
BurnSettings;
#endif

EXTERN_C const CLSID CLSID_RecorderCombobox;

#ifdef __cplusplus

class DECLSPEC_UUID("f495ebbe-a068-41fb-89b6-c605d20a2df3")
RecorderCombobox;
#endif

EXTERN_C const CLSID CLSID_BurnSettingsDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("e6028af3-ee0a-4e49-a043-c44437680ad8")
BurnSettingsDlg;
#endif

EXTERN_C const CLSID CLSID_BurnSettingsDlgParam;

#ifdef __cplusplus

class DECLSPEC_UUID("0b1511cd-37ee-4f0a-9647-cb2785b68a29")
BurnSettingsDlgParam;
#endif

EXTERN_C const CLSID CLSID_BurnProgressDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("a861a366-0c7a-484b-9116-f366bf0fa23f")
BurnProgressDlg;
#endif

EXTERN_C const CLSID CLSID_ChooseRecorderDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("0edcdb7d-cd9e-44e6-9e9a-adbaa85540e8")
ChooseRecorderDlg;
#endif

EXTERN_C const CLSID CLSID_EraseSettingsDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("1c613f47-70c5-4551-a264-f7254139854c")
EraseSettingsDlg;
#endif

EXTERN_C const CLSID CLSID_EraseDiscDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("7b9717b1-2d9b-4d14-b2da-d4bf5a28c6af")
EraseDiscDlg;
#endif

EXTERN_C const CLSID CLSID_DiscInfoDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("f1f2ece6-0289-4992-a536-f82dfc6f6d6e")
DiscInfoDlg;
#endif

EXTERN_C const CLSID CLSID_ImageInfoDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("940f79d9-2062-41b7-a22f-9e99ffdd1b85")
ImageInfoDlg;
#endif

EXTERN_C const CLSID CLSID_ImageInfoDlgParam;

#ifdef __cplusplus

class DECLSPEC_UUID("712a2867-02b2-402b-8f8d-74437494dcfb")
ImageInfoDlgParam;
#endif

EXTERN_C const CLSID CLSID_ChooseSessionDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("e5b2709a-0e6b-45d3-83c8-ef90c2ed5340")
ChooseSessionDlg;
#endif

EXTERN_C const CLSID CLSID_SpeedCombobox;

#ifdef __cplusplus

class DECLSPEC_UUID("612fbd09-aad2-4f1c-ba97-f56658b1161b")
SpeedCombobox;
#endif

EXTERN_C const CLSID CLSID_WaitForMediaDlg;

#ifdef __cplusplus

class DECLSPEC_UUID("9e42f1b8-de23-4af5-a79a-0976e9ec5781")
WaitForMediaDlg;
#endif

EXTERN_C const CLSID CLSID_UserDlgHandler;

#ifdef __cplusplus

class DECLSPEC_UUID("bc91ed21-e702-44e5-aa88-9f2f70e986c6")
UserDlgHandler;
#endif
#endif /* __NEROCBUILib_LIBRARY_DEFINED__ */

#ifndef __IModelessDialog_INTERFACE_DEFINED__
#define __IModelessDialog_INTERFACE_DEFINED__

/* interface IModelessDialog */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IModelessDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98654976-9086-4817-841c-b75b0ac0aaa6")
    IModelessDialog : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ HWND hWndParent,
            /* [in] */ LPCRECT pRect,
            /* [retval][out] */ HWND __RPC_FAR *phWndRet) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Destroy( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ MSG __RPC_FAR *pMsg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModelessDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IModelessDialog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IModelessDialog __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IModelessDialog __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IModelessDialog __RPC_FAR * This,
            /* [in] */ HWND hWndParent,
            /* [in] */ LPCRECT pRect,
            /* [retval][out] */ HWND __RPC_FAR *phWndRet);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Destroy )( 
            IModelessDialog __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TranslateAccelerator )( 
            IModelessDialog __RPC_FAR * This,
            /* [in] */ MSG __RPC_FAR *pMsg);
        
        END_INTERFACE
    } IModelessDialogVtbl;

    interface IModelessDialog
    {
        CONST_VTBL struct IModelessDialogVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModelessDialog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IModelessDialog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IModelessDialog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IModelessDialog_Create(This,hWndParent,pRect,phWndRet)	\
    (This)->lpVtbl -> Create(This,hWndParent,pRect,phWndRet)

#define IModelessDialog_Destroy(This)	\
    (This)->lpVtbl -> Destroy(This)

#define IModelessDialog_TranslateAccelerator(This,pMsg)	\
    (This)->lpVtbl -> TranslateAccelerator(This,pMsg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IModelessDialog_Create_Proxy( 
    IModelessDialog __RPC_FAR * This,
    /* [in] */ HWND hWndParent,
    /* [in] */ LPCRECT pRect,
    /* [retval][out] */ HWND __RPC_FAR *phWndRet);


void __RPC_STUB IModelessDialog_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModelessDialog_Destroy_Proxy( 
    IModelessDialog __RPC_FAR * This);


void __RPC_STUB IModelessDialog_Destroy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModelessDialog_TranslateAccelerator_Proxy( 
    IModelessDialog __RPC_FAR * This,
    /* [in] */ MSG __RPC_FAR *pMsg);


void __RPC_STUB IModelessDialog_TranslateAccelerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModelessDialog_INTERFACE_DEFINED__ */


#ifndef __INERO_SCSI_DEVICE_INFO_INTERFACE_DEFINED__
#define __INERO_SCSI_DEVICE_INFO_INTERFACE_DEFINED__

/* interface INERO_SCSI_DEVICE_INFO */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_INERO_SCSI_DEVICE_INFO;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8268ed13-82f5-4dcc-bb13-95b5c7a64590")
    INERO_SCSI_DEVICE_INFO : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_NERO_SCSI_DEVICE_INFO( 
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NERO_SCSI_DEVICE_INFO( 
            /* [retval][out] */ LPNERO_SCSI_DEVICE_INFO __RPC_FAR *ppDeviceInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INERO_SCSI_DEVICE_INFOVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INERO_SCSI_DEVICE_INFO __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INERO_SCSI_DEVICE_INFO __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INERO_SCSI_DEVICE_INFO __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NERO_SCSI_DEVICE_INFO )( 
            INERO_SCSI_DEVICE_INFO __RPC_FAR * This,
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NERO_SCSI_DEVICE_INFO )( 
            INERO_SCSI_DEVICE_INFO __RPC_FAR * This,
            /* [retval][out] */ LPNERO_SCSI_DEVICE_INFO __RPC_FAR *ppDeviceInfo);
        
        END_INTERFACE
    } INERO_SCSI_DEVICE_INFOVtbl;

    interface INERO_SCSI_DEVICE_INFO
    {
        CONST_VTBL struct INERO_SCSI_DEVICE_INFOVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INERO_SCSI_DEVICE_INFO_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INERO_SCSI_DEVICE_INFO_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INERO_SCSI_DEVICE_INFO_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INERO_SCSI_DEVICE_INFO_put_NERO_SCSI_DEVICE_INFO(This,pDeviceInfo)	\
    (This)->lpVtbl -> put_NERO_SCSI_DEVICE_INFO(This,pDeviceInfo)

#define INERO_SCSI_DEVICE_INFO_get_NERO_SCSI_DEVICE_INFO(This,ppDeviceInfo)	\
    (This)->lpVtbl -> get_NERO_SCSI_DEVICE_INFO(This,ppDeviceInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE INERO_SCSI_DEVICE_INFO_put_NERO_SCSI_DEVICE_INFO_Proxy( 
    INERO_SCSI_DEVICE_INFO __RPC_FAR * This,
    /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo);


void __RPC_STUB INERO_SCSI_DEVICE_INFO_put_NERO_SCSI_DEVICE_INFO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE INERO_SCSI_DEVICE_INFO_get_NERO_SCSI_DEVICE_INFO_Proxy( 
    INERO_SCSI_DEVICE_INFO __RPC_FAR * This,
    /* [retval][out] */ LPNERO_SCSI_DEVICE_INFO __RPC_FAR *ppDeviceInfo);


void __RPC_STUB INERO_SCSI_DEVICE_INFO_get_NERO_SCSI_DEVICE_INFO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INERO_SCSI_DEVICE_INFO_INTERFACE_DEFINED__ */


#ifndef __IRecorderComboboxCallbacks_INTERFACE_DEFINED__
#define __IRecorderComboboxCallbacks_INTERFACE_DEFINED__

/* interface IRecorderComboboxCallbacks */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IRecorderComboboxCallbacks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3bd2799a-b364-405a-a63b-104d7fbfeb8a")
    IRecorderComboboxCallbacks : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnFilterRecorder( 
            /* [in] */ LPCNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [retval][out] */ BOOL __RPC_FAR *pbAccept) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnFilterEnd( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnContentRefreshed( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnCurSelInUseStatusChange( 
            /* [in] */ BOOL bInUse) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRecorderComboboxCallbacksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRecorderComboboxCallbacks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRecorderComboboxCallbacks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRecorderComboboxCallbacks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFilterRecorder )( 
            IRecorderComboboxCallbacks __RPC_FAR * This,
            /* [in] */ LPCNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [retval][out] */ BOOL __RPC_FAR *pbAccept);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFilterEnd )( 
            IRecorderComboboxCallbacks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnContentRefreshed )( 
            IRecorderComboboxCallbacks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnCurSelInUseStatusChange )( 
            IRecorderComboboxCallbacks __RPC_FAR * This,
            /* [in] */ BOOL bInUse);
        
        END_INTERFACE
    } IRecorderComboboxCallbacksVtbl;

    interface IRecorderComboboxCallbacks
    {
        CONST_VTBL struct IRecorderComboboxCallbacksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRecorderComboboxCallbacks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRecorderComboboxCallbacks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRecorderComboboxCallbacks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRecorderComboboxCallbacks_OnFilterRecorder(This,pDeviceInfo,pbAccept)	\
    (This)->lpVtbl -> OnFilterRecorder(This,pDeviceInfo,pbAccept)

#define IRecorderComboboxCallbacks_OnFilterEnd(This)	\
    (This)->lpVtbl -> OnFilterEnd(This)

#define IRecorderComboboxCallbacks_OnContentRefreshed(This)	\
    (This)->lpVtbl -> OnContentRefreshed(This)

#define IRecorderComboboxCallbacks_OnCurSelInUseStatusChange(This,bInUse)	\
    (This)->lpVtbl -> OnCurSelInUseStatusChange(This,bInUse)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRecorderComboboxCallbacks_OnFilterRecorder_Proxy( 
    IRecorderComboboxCallbacks __RPC_FAR * This,
    /* [in] */ LPCNERO_SCSI_DEVICE_INFO pDeviceInfo,
    /* [retval][out] */ BOOL __RPC_FAR *pbAccept);


void __RPC_STUB IRecorderComboboxCallbacks_OnFilterRecorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecorderComboboxCallbacks_OnFilterEnd_Proxy( 
    IRecorderComboboxCallbacks __RPC_FAR * This);


void __RPC_STUB IRecorderComboboxCallbacks_OnFilterEnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecorderComboboxCallbacks_OnContentRefreshed_Proxy( 
    IRecorderComboboxCallbacks __RPC_FAR * This);


void __RPC_STUB IRecorderComboboxCallbacks_OnContentRefreshed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecorderComboboxCallbacks_OnCurSelInUseStatusChange_Proxy( 
    IRecorderComboboxCallbacks __RPC_FAR * This,
    /* [in] */ BOOL bInUse);


void __RPC_STUB IRecorderComboboxCallbacks_OnCurSelInUseStatusChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRecorderComboboxCallbacks_INTERFACE_DEFINED__ */


#ifndef __IRecorderCombobox_INTERFACE_DEFINED__
#define __IRecorderCombobox_INTERFACE_DEFINED__

/* interface IRecorderCombobox */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IRecorderCombobox;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c76f66ef-b4d7-496b-9ab7-409a965d9c43")
    IRecorderCombobox : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Callbacks( 
            /* [in] */ IRecorderComboboxCallbacks __RPC_FAR *pCallbacks) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRecorderComboboxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRecorderCombobox __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRecorderCombobox __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRecorderCombobox __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            IRecorderCombobox __RPC_FAR * This,
            /* [in] */ IRecorderComboboxCallbacks __RPC_FAR *pCallbacks);
        
        END_INTERFACE
    } IRecorderComboboxVtbl;

    interface IRecorderCombobox
    {
        CONST_VTBL struct IRecorderComboboxVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRecorderCombobox_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRecorderCombobox_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRecorderCombobox_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRecorderCombobox_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IRecorderCombobox_put_Callbacks_Proxy( 
    IRecorderCombobox __RPC_FAR * This,
    /* [in] */ IRecorderComboboxCallbacks __RPC_FAR *pCallbacks);


void __RPC_STUB IRecorderCombobox_put_Callbacks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRecorderCombobox_INTERFACE_DEFINED__ */


#ifndef __IRecorderCombobox2_INTERFACE_DEFINED__
#define __IRecorderCombobox2_INTERFACE_DEFINED__

/* interface IRecorderCombobox2 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IRecorderCombobox2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("de6f71ce-1faf-405c-8e8e-0a32dc023b59")
    IRecorderCombobox2 : public IRecorderCombobox
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Refresh( 
            /* [in] */ BOOL bRescan) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PrependCustomEntry( 
            /* [in] */ HICON hIcon,
            /* [in] */ BSTR bstrText,
            /* [in] */ const void __RPC_FAR *pUserData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AppendCustomEntry( 
            /* [in] */ HICON hIcon,
            /* [in] */ BSTR bstrText,
            /* [in] */ const void __RPC_FAR *pUserData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveCustomEntry( 
            /* [in] */ const void __RPC_FAR *pUserData,
            /* [retval][out] */ BOOL __RPC_FAR *pbSuccess) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_CustomEntry( 
            /* [in] */ const void __RPC_FAR *pUserData) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CustomEntry( 
            /* [retval][out] */ const void __RPC_FAR *__RPC_FAR *pUserData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRecorderCombobox2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRecorderCombobox2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRecorderCombobox2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRecorderCombobox2 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            IRecorderCombobox2 __RPC_FAR * This,
            /* [in] */ IRecorderComboboxCallbacks __RPC_FAR *pCallbacks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IRecorderCombobox2 __RPC_FAR * This,
            /* [in] */ BOOL bRescan);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrependCustomEntry )( 
            IRecorderCombobox2 __RPC_FAR * This,
            /* [in] */ HICON hIcon,
            /* [in] */ BSTR bstrText,
            /* [in] */ const void __RPC_FAR *pUserData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendCustomEntry )( 
            IRecorderCombobox2 __RPC_FAR * This,
            /* [in] */ HICON hIcon,
            /* [in] */ BSTR bstrText,
            /* [in] */ const void __RPC_FAR *pUserData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveCustomEntry )( 
            IRecorderCombobox2 __RPC_FAR * This,
            /* [in] */ const void __RPC_FAR *pUserData,
            /* [retval][out] */ BOOL __RPC_FAR *pbSuccess);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CustomEntry )( 
            IRecorderCombobox2 __RPC_FAR * This,
            /* [in] */ const void __RPC_FAR *pUserData);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CustomEntry )( 
            IRecorderCombobox2 __RPC_FAR * This,
            /* [retval][out] */ const void __RPC_FAR *__RPC_FAR *pUserData);
        
        END_INTERFACE
    } IRecorderCombobox2Vtbl;

    interface IRecorderCombobox2
    {
        CONST_VTBL struct IRecorderCombobox2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRecorderCombobox2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRecorderCombobox2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRecorderCombobox2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRecorderCombobox2_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)


#define IRecorderCombobox2_Refresh(This,bRescan)	\
    (This)->lpVtbl -> Refresh(This,bRescan)

#define IRecorderCombobox2_PrependCustomEntry(This,hIcon,bstrText,pUserData)	\
    (This)->lpVtbl -> PrependCustomEntry(This,hIcon,bstrText,pUserData)

#define IRecorderCombobox2_AppendCustomEntry(This,hIcon,bstrText,pUserData)	\
    (This)->lpVtbl -> AppendCustomEntry(This,hIcon,bstrText,pUserData)

#define IRecorderCombobox2_RemoveCustomEntry(This,pUserData,pbSuccess)	\
    (This)->lpVtbl -> RemoveCustomEntry(This,pUserData,pbSuccess)

#define IRecorderCombobox2_put_CustomEntry(This,pUserData)	\
    (This)->lpVtbl -> put_CustomEntry(This,pUserData)

#define IRecorderCombobox2_get_CustomEntry(This,pUserData)	\
    (This)->lpVtbl -> get_CustomEntry(This,pUserData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRecorderCombobox2_Refresh_Proxy( 
    IRecorderCombobox2 __RPC_FAR * This,
    /* [in] */ BOOL bRescan);


void __RPC_STUB IRecorderCombobox2_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecorderCombobox2_PrependCustomEntry_Proxy( 
    IRecorderCombobox2 __RPC_FAR * This,
    /* [in] */ HICON hIcon,
    /* [in] */ BSTR bstrText,
    /* [in] */ const void __RPC_FAR *pUserData);


void __RPC_STUB IRecorderCombobox2_PrependCustomEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecorderCombobox2_AppendCustomEntry_Proxy( 
    IRecorderCombobox2 __RPC_FAR * This,
    /* [in] */ HICON hIcon,
    /* [in] */ BSTR bstrText,
    /* [in] */ const void __RPC_FAR *pUserData);


void __RPC_STUB IRecorderCombobox2_AppendCustomEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRecorderCombobox2_RemoveCustomEntry_Proxy( 
    IRecorderCombobox2 __RPC_FAR * This,
    /* [in] */ const void __RPC_FAR *pUserData,
    /* [retval][out] */ BOOL __RPC_FAR *pbSuccess);


void __RPC_STUB IRecorderCombobox2_RemoveCustomEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IRecorderCombobox2_put_CustomEntry_Proxy( 
    IRecorderCombobox2 __RPC_FAR * This,
    /* [in] */ const void __RPC_FAR *pUserData);


void __RPC_STUB IRecorderCombobox2_put_CustomEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRecorderCombobox2_get_CustomEntry_Proxy( 
    IRecorderCombobox2 __RPC_FAR * This,
    /* [retval][out] */ const void __RPC_FAR *__RPC_FAR *pUserData);


void __RPC_STUB IRecorderCombobox2_get_CustomEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRecorderCombobox2_INTERFACE_DEFINED__ */


#ifndef __IRecorderCombobox3_INTERFACE_DEFINED__
#define __IRecorderCombobox3_INTERFACE_DEFINED__

/* interface IRecorderCombobox3 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IRecorderCombobox3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("40a779dc-9ddc-4d02-bf07-717f419c00aa")
    IRecorderCombobox3 : public IRecorderCombobox2
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DriveByName( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DriveByLetter( 
            /* [in] */ BSTR bstrLetter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRecorderCombobox3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRecorderCombobox3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRecorderCombobox3 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ IRecorderComboboxCallbacks __RPC_FAR *pCallbacks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ BOOL bRescan);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrependCustomEntry )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ HICON hIcon,
            /* [in] */ BSTR bstrText,
            /* [in] */ const void __RPC_FAR *pUserData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendCustomEntry )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ HICON hIcon,
            /* [in] */ BSTR bstrText,
            /* [in] */ const void __RPC_FAR *pUserData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveCustomEntry )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ const void __RPC_FAR *pUserData,
            /* [retval][out] */ BOOL __RPC_FAR *pbSuccess);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CustomEntry )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ const void __RPC_FAR *pUserData);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CustomEntry )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [retval][out] */ const void __RPC_FAR *__RPC_FAR *pUserData);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DriveByName )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ BSTR bstrName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DriveByLetter )( 
            IRecorderCombobox3 __RPC_FAR * This,
            /* [in] */ BSTR bstrLetter);
        
        END_INTERFACE
    } IRecorderCombobox3Vtbl;

    interface IRecorderCombobox3
    {
        CONST_VTBL struct IRecorderCombobox3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRecorderCombobox3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRecorderCombobox3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRecorderCombobox3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRecorderCombobox3_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)


#define IRecorderCombobox3_Refresh(This,bRescan)	\
    (This)->lpVtbl -> Refresh(This,bRescan)

#define IRecorderCombobox3_PrependCustomEntry(This,hIcon,bstrText,pUserData)	\
    (This)->lpVtbl -> PrependCustomEntry(This,hIcon,bstrText,pUserData)

#define IRecorderCombobox3_AppendCustomEntry(This,hIcon,bstrText,pUserData)	\
    (This)->lpVtbl -> AppendCustomEntry(This,hIcon,bstrText,pUserData)

#define IRecorderCombobox3_RemoveCustomEntry(This,pUserData,pbSuccess)	\
    (This)->lpVtbl -> RemoveCustomEntry(This,pUserData,pbSuccess)

#define IRecorderCombobox3_put_CustomEntry(This,pUserData)	\
    (This)->lpVtbl -> put_CustomEntry(This,pUserData)

#define IRecorderCombobox3_get_CustomEntry(This,pUserData)	\
    (This)->lpVtbl -> get_CustomEntry(This,pUserData)


#define IRecorderCombobox3_put_DriveByName(This,bstrName)	\
    (This)->lpVtbl -> put_DriveByName(This,bstrName)

#define IRecorderCombobox3_put_DriveByLetter(This,bstrLetter)	\
    (This)->lpVtbl -> put_DriveByLetter(This,bstrLetter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IRecorderCombobox3_put_DriveByName_Proxy( 
    IRecorderCombobox3 __RPC_FAR * This,
    /* [in] */ BSTR bstrName);


void __RPC_STUB IRecorderCombobox3_put_DriveByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IRecorderCombobox3_put_DriveByLetter_Proxy( 
    IRecorderCombobox3 __RPC_FAR * This,
    /* [in] */ BSTR bstrLetter);


void __RPC_STUB IRecorderCombobox3_put_DriveByLetter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRecorderCombobox3_INTERFACE_DEFINED__ */


#ifndef __IBurnSettings_INTERFACE_DEFINED__
#define __IBurnSettings_INTERFACE_DEFINED__

/* interface IBurnSettings */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IBurnSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29c0c344-4c3c-4d4c-bd49-622ccfbd2c2e")
    IBurnSettings : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BurnFlags( 
            /* [retval][out] */ DWORD __RPC_FAR *pdwBurnFlags) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BurnFlags( 
            /* [in] */ DWORD dwBurnFlags) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Speed( 
            /* [retval][out] */ DWORD __RPC_FAR *pdwSpeed) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Speed( 
            /* [in] */ DWORD dwSpeed) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBurnSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBurnSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBurnSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBurnSettings __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BurnFlags )( 
            IBurnSettings __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwBurnFlags);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BurnFlags )( 
            IBurnSettings __RPC_FAR * This,
            /* [in] */ DWORD dwBurnFlags);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Speed )( 
            IBurnSettings __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwSpeed);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Speed )( 
            IBurnSettings __RPC_FAR * This,
            /* [in] */ DWORD dwSpeed);
        
        END_INTERFACE
    } IBurnSettingsVtbl;

    interface IBurnSettings
    {
        CONST_VTBL struct IBurnSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBurnSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBurnSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBurnSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBurnSettings_get_BurnFlags(This,pdwBurnFlags)	\
    (This)->lpVtbl -> get_BurnFlags(This,pdwBurnFlags)

#define IBurnSettings_put_BurnFlags(This,dwBurnFlags)	\
    (This)->lpVtbl -> put_BurnFlags(This,dwBurnFlags)

#define IBurnSettings_get_Speed(This,pdwSpeed)	\
    (This)->lpVtbl -> get_Speed(This,pdwSpeed)

#define IBurnSettings_put_Speed(This,dwSpeed)	\
    (This)->lpVtbl -> put_Speed(This,dwSpeed)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IBurnSettings_get_BurnFlags_Proxy( 
    IBurnSettings __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pdwBurnFlags);


void __RPC_STUB IBurnSettings_get_BurnFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnSettings_put_BurnFlags_Proxy( 
    IBurnSettings __RPC_FAR * This,
    /* [in] */ DWORD dwBurnFlags);


void __RPC_STUB IBurnSettings_put_BurnFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBurnSettings_get_Speed_Proxy( 
    IBurnSettings __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pdwSpeed);


void __RPC_STUB IBurnSettings_get_Speed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnSettings_put_Speed_Proxy( 
    IBurnSettings __RPC_FAR * This,
    /* [in] */ DWORD dwSpeed);


void __RPC_STUB IBurnSettings_put_Speed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBurnSettings_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_NeroCBUI_0264 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum _tagBURN_SETTINGS_GUI_FLAGS
    {	BSGF_DETERMINE_MAXIMUM_SPEED	= 1L << 0,
	BSGF_SIMULATION	= 1L << 1,
	BSGF_WRITE	= 1L << 2,
	BSGF_FINALIZE_CD	= 1L << 3,
	BSGF_WRITE_SPEED	= 1L << 4,
	BSGF_WRITE_METHOD	= 1L << 5,
	BSGF_BURN_PROOF	= 1L << 6,
	BSGF_PROGRESS	= 1L << 7,
	BSGF_VERIFY_WRITTEN_DATA	= 1L << 8
    }	BURN_SETTINGS_GUI_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_NeroCBUI_0264_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_NeroCBUI_0264_v0_0_s_ifspec;

#ifndef __IBurnSettingsDlg_INTERFACE_DEFINED__
#define __IBurnSettingsDlg_INTERFACE_DEFINED__

/* interface IBurnSettingsDlg */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IBurnSettingsDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0e17506d-ef14-4f3f-92bc-d3ae0739d079")
    IBurnSettingsDlg : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BurnSettings( 
            /* [in] */ IBurnSettings __RPC_FAR *pBurnSettings) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_GUIFlags( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MediaType( 
            /* [in] */ NERO_MEDIA_TYPE mediaType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBurnSettingsDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBurnSettingsDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBurnSettingsDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBurnSettingsDlg __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BurnSettings )( 
            IBurnSettingsDlg __RPC_FAR * This,
            /* [in] */ IBurnSettings __RPC_FAR *pBurnSettings);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GUIFlags )( 
            IBurnSettingsDlg __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MediaType )( 
            IBurnSettingsDlg __RPC_FAR * This,
            /* [in] */ NERO_MEDIA_TYPE mediaType);
        
        END_INTERFACE
    } IBurnSettingsDlgVtbl;

    interface IBurnSettingsDlg
    {
        CONST_VTBL struct IBurnSettingsDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBurnSettingsDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBurnSettingsDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBurnSettingsDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBurnSettingsDlg_put_BurnSettings(This,pBurnSettings)	\
    (This)->lpVtbl -> put_BurnSettings(This,pBurnSettings)

#define IBurnSettingsDlg_put_GUIFlags(This,dwFlags)	\
    (This)->lpVtbl -> put_GUIFlags(This,dwFlags)

#define IBurnSettingsDlg_put_MediaType(This,mediaType)	\
    (This)->lpVtbl -> put_MediaType(This,mediaType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnSettingsDlg_put_BurnSettings_Proxy( 
    IBurnSettingsDlg __RPC_FAR * This,
    /* [in] */ IBurnSettings __RPC_FAR *pBurnSettings);


void __RPC_STUB IBurnSettingsDlg_put_BurnSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnSettingsDlg_put_GUIFlags_Proxy( 
    IBurnSettingsDlg __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IBurnSettingsDlg_put_GUIFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnSettingsDlg_put_MediaType_Proxy( 
    IBurnSettingsDlg __RPC_FAR * This,
    /* [in] */ NERO_MEDIA_TYPE mediaType);


void __RPC_STUB IBurnSettingsDlg_put_MediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBurnSettingsDlg_INTERFACE_DEFINED__ */


#ifndef __IBurnCallbacks_INTERFACE_DEFINED__
#define __IBurnCallbacks_INTERFACE_DEFINED__

/* interface IBurnCallbacks */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IBurnCallbacks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("01e72686-14ec-4a44-be83-6c1cf9bfa2c0")
    IBurnCallbacks : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnDoneBurn( 
            /* [in] */ NEROAPI_BURN_ERROR burnError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Progress( 
            /* [in] */ DWORD dwProgressInPercent,
            /* [retval][out] */ BOOL __RPC_FAR *pbRetVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SubtaskProgress( 
            /* [in] */ DWORD dwProgressInPercent,
            /* [retval][out] */ BOOL __RPC_FAR *pbRetVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddLogLine( 
            /* [in] */ NERO_TEXT_TYPE type,
            /* [in] */ BSTR bstrLogLine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPhase( 
            /* [in] */ BSTR bstrPhase) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMajorPhase( 
            /* [in] */ NERO_MAJOR_PHASE majorPhase) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Aborted( 
            /* [retval][out] */ BOOL __RPC_FAR *pbRetVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisableAbort( 
            /* [in] */ BOOL bAbortEnabled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBurnCallbacksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBurnCallbacks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBurnCallbacks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDoneBurn )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [in] */ NEROAPI_BURN_ERROR burnError);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Progress )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [in] */ DWORD dwProgressInPercent,
            /* [retval][out] */ BOOL __RPC_FAR *pbRetVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubtaskProgress )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [in] */ DWORD dwProgressInPercent,
            /* [retval][out] */ BOOL __RPC_FAR *pbRetVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddLogLine )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [in] */ NERO_TEXT_TYPE type,
            /* [in] */ BSTR bstrLogLine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPhase )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [in] */ BSTR bstrPhase);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMajorPhase )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [in] */ NERO_MAJOR_PHASE majorPhase);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Aborted )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbRetVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisableAbort )( 
            IBurnCallbacks __RPC_FAR * This,
            /* [in] */ BOOL bAbortEnabled);
        
        END_INTERFACE
    } IBurnCallbacksVtbl;

    interface IBurnCallbacks
    {
        CONST_VTBL struct IBurnCallbacksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBurnCallbacks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBurnCallbacks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBurnCallbacks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBurnCallbacks_OnDoneBurn(This,burnError)	\
    (This)->lpVtbl -> OnDoneBurn(This,burnError)

#define IBurnCallbacks_Progress(This,dwProgressInPercent,pbRetVal)	\
    (This)->lpVtbl -> Progress(This,dwProgressInPercent,pbRetVal)

#define IBurnCallbacks_SubtaskProgress(This,dwProgressInPercent,pbRetVal)	\
    (This)->lpVtbl -> SubtaskProgress(This,dwProgressInPercent,pbRetVal)

#define IBurnCallbacks_AddLogLine(This,type,bstrLogLine)	\
    (This)->lpVtbl -> AddLogLine(This,type,bstrLogLine)

#define IBurnCallbacks_SetPhase(This,bstrPhase)	\
    (This)->lpVtbl -> SetPhase(This,bstrPhase)

#define IBurnCallbacks_SetMajorPhase(This,majorPhase)	\
    (This)->lpVtbl -> SetMajorPhase(This,majorPhase)

#define IBurnCallbacks_Aborted(This,pbRetVal)	\
    (This)->lpVtbl -> Aborted(This,pbRetVal)

#define IBurnCallbacks_DisableAbort(This,bAbortEnabled)	\
    (This)->lpVtbl -> DisableAbort(This,bAbortEnabled)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBurnCallbacks_OnDoneBurn_Proxy( 
    IBurnCallbacks __RPC_FAR * This,
    /* [in] */ NEROAPI_BURN_ERROR burnError);


void __RPC_STUB IBurnCallbacks_OnDoneBurn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnCallbacks_Progress_Proxy( 
    IBurnCallbacks __RPC_FAR * This,
    /* [in] */ DWORD dwProgressInPercent,
    /* [retval][out] */ BOOL __RPC_FAR *pbRetVal);


void __RPC_STUB IBurnCallbacks_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnCallbacks_SubtaskProgress_Proxy( 
    IBurnCallbacks __RPC_FAR * This,
    /* [in] */ DWORD dwProgressInPercent,
    /* [retval][out] */ BOOL __RPC_FAR *pbRetVal);


void __RPC_STUB IBurnCallbacks_SubtaskProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnCallbacks_AddLogLine_Proxy( 
    IBurnCallbacks __RPC_FAR * This,
    /* [in] */ NERO_TEXT_TYPE type,
    /* [in] */ BSTR bstrLogLine);


void __RPC_STUB IBurnCallbacks_AddLogLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnCallbacks_SetPhase_Proxy( 
    IBurnCallbacks __RPC_FAR * This,
    /* [in] */ BSTR bstrPhase);


void __RPC_STUB IBurnCallbacks_SetPhase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnCallbacks_SetMajorPhase_Proxy( 
    IBurnCallbacks __RPC_FAR * This,
    /* [in] */ NERO_MAJOR_PHASE majorPhase);


void __RPC_STUB IBurnCallbacks_SetMajorPhase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnCallbacks_Aborted_Proxy( 
    IBurnCallbacks __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pbRetVal);


void __RPC_STUB IBurnCallbacks_Aborted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnCallbacks_DisableAbort_Proxy( 
    IBurnCallbacks __RPC_FAR * This,
    /* [in] */ BOOL bAbortEnabled);


void __RPC_STUB IBurnCallbacks_DisableAbort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBurnCallbacks_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_NeroCBUI_0266 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum _tagBURN_PROGRESS_GUI_FLAGS
    {	BPGF_TOTAL_TIME	= 1L << 0,
	BPGF_CURRENT_ACTION	= 1L << 1,
	BPGF_USED_BUFFER	= 1L << 2,
	BPGF_CANCEL_BUTTON	= 1L << 3,
	BPGF_CLOSE_DISCARD_BUTTON	= 1L << 4,
	BPGF_PRINT_BUTTON	= 1L << 6,
	BPGF_SAVE_BUTTON	= 1L << 7
    }	BURN_PROGRESS_GUI_FLAGS;

typedef /* [v1_enum] */ 
enum _tagBURN_PROGRESS_CUSTOM_CONTROL_POSITION
    {	BPCCP_BOTTOM_RIGHT_CORNER	= 0
    }	BURN_PROGRESS_CUSTOM_CONTROL_POSITION;



extern RPC_IF_HANDLE __MIDL_itf_NeroCBUI_0266_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_NeroCBUI_0266_v0_0_s_ifspec;

#ifndef __IBurnProgressDlgCallbacks_INTERFACE_DEFINED__
#define __IBurnProgressDlgCallbacks_INTERFACE_DEFINED__

/* interface IBurnProgressDlgCallbacks */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IBurnProgressDlgCallbacks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ee2ae31b-c11d-40ea-a75b-884837328387")
    IBurnProgressDlgCallbacks : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnCancel( 
            /* [retval][out] */ BOOL __RPC_FAR *pbAllowCancel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnDiscard( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnClose( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBurnProgressDlgCallbacksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBurnProgressDlgCallbacks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBurnProgressDlgCallbacks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBurnProgressDlgCallbacks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnCancel )( 
            IBurnProgressDlgCallbacks __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbAllowCancel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDiscard )( 
            IBurnProgressDlgCallbacks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnClose )( 
            IBurnProgressDlgCallbacks __RPC_FAR * This);
        
        END_INTERFACE
    } IBurnProgressDlgCallbacksVtbl;

    interface IBurnProgressDlgCallbacks
    {
        CONST_VTBL struct IBurnProgressDlgCallbacksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBurnProgressDlgCallbacks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBurnProgressDlgCallbacks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBurnProgressDlgCallbacks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBurnProgressDlgCallbacks_OnCancel(This,pbAllowCancel)	\
    (This)->lpVtbl -> OnCancel(This,pbAllowCancel)

#define IBurnProgressDlgCallbacks_OnDiscard(This)	\
    (This)->lpVtbl -> OnDiscard(This)

#define IBurnProgressDlgCallbacks_OnClose(This)	\
    (This)->lpVtbl -> OnClose(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBurnProgressDlgCallbacks_OnCancel_Proxy( 
    IBurnProgressDlgCallbacks __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pbAllowCancel);


void __RPC_STUB IBurnProgressDlgCallbacks_OnCancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlgCallbacks_OnDiscard_Proxy( 
    IBurnProgressDlgCallbacks __RPC_FAR * This);


void __RPC_STUB IBurnProgressDlgCallbacks_OnDiscard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlgCallbacks_OnClose_Proxy( 
    IBurnProgressDlgCallbacks __RPC_FAR * This);


void __RPC_STUB IBurnProgressDlgCallbacks_OnClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBurnProgressDlgCallbacks_INTERFACE_DEFINED__ */


#ifndef __IBurnProgressDlg_INTERFACE_DEFINED__
#define __IBurnProgressDlg_INTERFACE_DEFINED__

/* interface IBurnProgressDlg */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IBurnProgressDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f9da148d-0052-4b6f-bb4f-c35e1fd4c5a3")
    IBurnProgressDlg : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_GUIFlags( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_CompilationName( 
            /* [in] */ BSTR bstrCompilationName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_CompilationType( 
            /* [in] */ BSTR bstrCompilationType) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_CompilationSize( 
            /* [in] */ BSTR bstrCompilationSize) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_CompilationTime( 
            /* [in] */ BSTR bstrCompilationTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Burn( 
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ NERO_CD_FORMAT cdFormat,
            /* [in] */ const void __RPC_FAR *pWriteCD,
            /* [in] */ IBurnSettings __RPC_FAR *pBurnSettings,
            /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Burn2( 
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ NERO_CD_FORMAT cdFormat,
            /* [in] */ const void __RPC_FAR *pWriteCD,
            /* [in] */ DWORD dwBurnFlags,
            /* [in] */ DWORD dwSpeed,
            /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CanCloseParent( 
            /* [retval][out] */ BOOL __RPC_FAR *pbCanClose) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AllocateProgressBar( 
            /* [in] */ DWORD dwPreProgress,
            /* [in] */ DWORD dwPostProgress) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProgress( 
            /* [in] */ DWORD dwProgressInPercent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddLogLine( 
            /* [in] */ NERO_TEXT_TYPE type,
            /* [in] */ BSTR bstrLogLine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPhase( 
            /* [in] */ BSTR bstrPhase) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBurnProgressDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBurnProgressDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBurnProgressDlg __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GUIFlags )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationName )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationType )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationSize )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationSize);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationTime )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Burn )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ NERO_CD_FORMAT cdFormat,
            /* [in] */ const void __RPC_FAR *pWriteCD,
            /* [in] */ IBurnSettings __RPC_FAR *pBurnSettings,
            /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Burn2 )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ NERO_CD_FORMAT cdFormat,
            /* [in] */ const void __RPC_FAR *pWriteCD,
            /* [in] */ DWORD dwBurnFlags,
            /* [in] */ DWORD dwSpeed,
            /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            IBurnProgressDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanCloseParent )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbCanClose);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateProgressBar )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ DWORD dwPreProgress,
            /* [in] */ DWORD dwPostProgress);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProgress )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ DWORD dwProgressInPercent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddLogLine )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ NERO_TEXT_TYPE type,
            /* [in] */ BSTR bstrLogLine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPhase )( 
            IBurnProgressDlg __RPC_FAR * This,
            /* [in] */ BSTR bstrPhase);
        
        END_INTERFACE
    } IBurnProgressDlgVtbl;

    interface IBurnProgressDlg
    {
        CONST_VTBL struct IBurnProgressDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBurnProgressDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBurnProgressDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBurnProgressDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBurnProgressDlg_put_GUIFlags(This,dwFlags)	\
    (This)->lpVtbl -> put_GUIFlags(This,dwFlags)

#define IBurnProgressDlg_put_CompilationName(This,bstrCompilationName)	\
    (This)->lpVtbl -> put_CompilationName(This,bstrCompilationName)

#define IBurnProgressDlg_put_CompilationType(This,bstrCompilationType)	\
    (This)->lpVtbl -> put_CompilationType(This,bstrCompilationType)

#define IBurnProgressDlg_put_CompilationSize(This,bstrCompilationSize)	\
    (This)->lpVtbl -> put_CompilationSize(This,bstrCompilationSize)

#define IBurnProgressDlg_put_CompilationTime(This,bstrCompilationTime)	\
    (This)->lpVtbl -> put_CompilationTime(This,bstrCompilationTime)

#define IBurnProgressDlg_Burn(This,pDeviceInfo,cdFormat,pWriteCD,pBurnSettings,pBurnCallbacks)	\
    (This)->lpVtbl -> Burn(This,pDeviceInfo,cdFormat,pWriteCD,pBurnSettings,pBurnCallbacks)

#define IBurnProgressDlg_Burn2(This,pDeviceInfo,cdFormat,pWriteCD,dwBurnFlags,dwSpeed,pBurnCallbacks)	\
    (This)->lpVtbl -> Burn2(This,pDeviceInfo,cdFormat,pWriteCD,dwBurnFlags,dwSpeed,pBurnCallbacks)

#define IBurnProgressDlg_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define IBurnProgressDlg_CanCloseParent(This,pbCanClose)	\
    (This)->lpVtbl -> CanCloseParent(This,pbCanClose)

#define IBurnProgressDlg_AllocateProgressBar(This,dwPreProgress,dwPostProgress)	\
    (This)->lpVtbl -> AllocateProgressBar(This,dwPreProgress,dwPostProgress)

#define IBurnProgressDlg_SetProgress(This,dwProgressInPercent)	\
    (This)->lpVtbl -> SetProgress(This,dwProgressInPercent)

#define IBurnProgressDlg_AddLogLine(This,type,bstrLogLine)	\
    (This)->lpVtbl -> AddLogLine(This,type,bstrLogLine)

#define IBurnProgressDlg_SetPhase(This,bstrPhase)	\
    (This)->lpVtbl -> SetPhase(This,bstrPhase)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnProgressDlg_put_GUIFlags_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IBurnProgressDlg_put_GUIFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnProgressDlg_put_CompilationName_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ BSTR bstrCompilationName);


void __RPC_STUB IBurnProgressDlg_put_CompilationName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnProgressDlg_put_CompilationType_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ BSTR bstrCompilationType);


void __RPC_STUB IBurnProgressDlg_put_CompilationType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnProgressDlg_put_CompilationSize_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ BSTR bstrCompilationSize);


void __RPC_STUB IBurnProgressDlg_put_CompilationSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnProgressDlg_put_CompilationTime_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ BSTR bstrCompilationTime);


void __RPC_STUB IBurnProgressDlg_put_CompilationTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlg_Burn_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
    /* [in] */ NERO_CD_FORMAT cdFormat,
    /* [in] */ const void __RPC_FAR *pWriteCD,
    /* [in] */ IBurnSettings __RPC_FAR *pBurnSettings,
    /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks);


void __RPC_STUB IBurnProgressDlg_Burn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlg_Burn2_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
    /* [in] */ NERO_CD_FORMAT cdFormat,
    /* [in] */ const void __RPC_FAR *pWriteCD,
    /* [in] */ DWORD dwBurnFlags,
    /* [in] */ DWORD dwSpeed,
    /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks);


void __RPC_STUB IBurnProgressDlg_Burn2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlg_Cancel_Proxy( 
    IBurnProgressDlg __RPC_FAR * This);


void __RPC_STUB IBurnProgressDlg_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlg_CanCloseParent_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pbCanClose);


void __RPC_STUB IBurnProgressDlg_CanCloseParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlg_AllocateProgressBar_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ DWORD dwPreProgress,
    /* [in] */ DWORD dwPostProgress);


void __RPC_STUB IBurnProgressDlg_AllocateProgressBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlg_SetProgress_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ DWORD dwProgressInPercent);


void __RPC_STUB IBurnProgressDlg_SetProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlg_AddLogLine_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ NERO_TEXT_TYPE type,
    /* [in] */ BSTR bstrLogLine);


void __RPC_STUB IBurnProgressDlg_AddLogLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBurnProgressDlg_SetPhase_Proxy( 
    IBurnProgressDlg __RPC_FAR * This,
    /* [in] */ BSTR bstrPhase);


void __RPC_STUB IBurnProgressDlg_SetPhase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBurnProgressDlg_INTERFACE_DEFINED__ */


#ifndef __IBurnProgressDlg2_INTERFACE_DEFINED__
#define __IBurnProgressDlg2_INTERFACE_DEFINED__

/* interface IBurnProgressDlg2 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IBurnProgressDlg2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2053e9d5-8460-4e52-aba2-832202624365")
    IBurnProgressDlg2 : public IBurnProgressDlg
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_WizardMode( 
            /* [in] */ BOOL bWizardMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBurnProgressDlg2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBurnProgressDlg2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBurnProgressDlg2 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GUIFlags )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationName )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationType )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationSize )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationSize);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationTime )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Burn )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ NERO_CD_FORMAT cdFormat,
            /* [in] */ const void __RPC_FAR *pWriteCD,
            /* [in] */ IBurnSettings __RPC_FAR *pBurnSettings,
            /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Burn2 )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ NERO_CD_FORMAT cdFormat,
            /* [in] */ const void __RPC_FAR *pWriteCD,
            /* [in] */ DWORD dwBurnFlags,
            /* [in] */ DWORD dwSpeed,
            /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            IBurnProgressDlg2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanCloseParent )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbCanClose);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateProgressBar )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ DWORD dwPreProgress,
            /* [in] */ DWORD dwPostProgress);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProgress )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ DWORD dwProgressInPercent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddLogLine )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ NERO_TEXT_TYPE type,
            /* [in] */ BSTR bstrLogLine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPhase )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ BSTR bstrPhase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WizardMode )( 
            IBurnProgressDlg2 __RPC_FAR * This,
            /* [in] */ BOOL bWizardMode);
        
        END_INTERFACE
    } IBurnProgressDlg2Vtbl;

    interface IBurnProgressDlg2
    {
        CONST_VTBL struct IBurnProgressDlg2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBurnProgressDlg2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBurnProgressDlg2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBurnProgressDlg2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBurnProgressDlg2_put_GUIFlags(This,dwFlags)	\
    (This)->lpVtbl -> put_GUIFlags(This,dwFlags)

#define IBurnProgressDlg2_put_CompilationName(This,bstrCompilationName)	\
    (This)->lpVtbl -> put_CompilationName(This,bstrCompilationName)

#define IBurnProgressDlg2_put_CompilationType(This,bstrCompilationType)	\
    (This)->lpVtbl -> put_CompilationType(This,bstrCompilationType)

#define IBurnProgressDlg2_put_CompilationSize(This,bstrCompilationSize)	\
    (This)->lpVtbl -> put_CompilationSize(This,bstrCompilationSize)

#define IBurnProgressDlg2_put_CompilationTime(This,bstrCompilationTime)	\
    (This)->lpVtbl -> put_CompilationTime(This,bstrCompilationTime)

#define IBurnProgressDlg2_Burn(This,pDeviceInfo,cdFormat,pWriteCD,pBurnSettings,pBurnCallbacks)	\
    (This)->lpVtbl -> Burn(This,pDeviceInfo,cdFormat,pWriteCD,pBurnSettings,pBurnCallbacks)

#define IBurnProgressDlg2_Burn2(This,pDeviceInfo,cdFormat,pWriteCD,dwBurnFlags,dwSpeed,pBurnCallbacks)	\
    (This)->lpVtbl -> Burn2(This,pDeviceInfo,cdFormat,pWriteCD,dwBurnFlags,dwSpeed,pBurnCallbacks)

#define IBurnProgressDlg2_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define IBurnProgressDlg2_CanCloseParent(This,pbCanClose)	\
    (This)->lpVtbl -> CanCloseParent(This,pbCanClose)

#define IBurnProgressDlg2_AllocateProgressBar(This,dwPreProgress,dwPostProgress)	\
    (This)->lpVtbl -> AllocateProgressBar(This,dwPreProgress,dwPostProgress)

#define IBurnProgressDlg2_SetProgress(This,dwProgressInPercent)	\
    (This)->lpVtbl -> SetProgress(This,dwProgressInPercent)

#define IBurnProgressDlg2_AddLogLine(This,type,bstrLogLine)	\
    (This)->lpVtbl -> AddLogLine(This,type,bstrLogLine)

#define IBurnProgressDlg2_SetPhase(This,bstrPhase)	\
    (This)->lpVtbl -> SetPhase(This,bstrPhase)


#define IBurnProgressDlg2_put_WizardMode(This,bWizardMode)	\
    (This)->lpVtbl -> put_WizardMode(This,bWizardMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnProgressDlg2_put_WizardMode_Proxy( 
    IBurnProgressDlg2 __RPC_FAR * This,
    /* [in] */ BOOL bWizardMode);


void __RPC_STUB IBurnProgressDlg2_put_WizardMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBurnProgressDlg2_INTERFACE_DEFINED__ */


#ifndef __IExternalChildWindow_INTERFACE_DEFINED__
#define __IExternalChildWindow_INTERFACE_DEFINED__

/* interface IExternalChildWindow */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IExternalChildWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("fda257a8-46ca-452e-9f3c-05798d3382c0")
    IExternalChildWindow : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ HWND hWndParent,
            /* [retval][out] */ HWND __RPC_FAR *phWnd) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MinSize( 
            /* [retval][out] */ SIZE __RPC_FAR *pSize) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MaxSize( 
            /* [retval][out] */ SIZE __RPC_FAR *pSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExternalChildWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExternalChildWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExternalChildWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExternalChildWindow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IExternalChildWindow __RPC_FAR * This,
            /* [in] */ HWND hWndParent,
            /* [retval][out] */ HWND __RPC_FAR *phWnd);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinSize )( 
            IExternalChildWindow __RPC_FAR * This,
            /* [retval][out] */ SIZE __RPC_FAR *pSize);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxSize )( 
            IExternalChildWindow __RPC_FAR * This,
            /* [retval][out] */ SIZE __RPC_FAR *pSize);
        
        END_INTERFACE
    } IExternalChildWindowVtbl;

    interface IExternalChildWindow
    {
        CONST_VTBL struct IExternalChildWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExternalChildWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExternalChildWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExternalChildWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExternalChildWindow_Create(This,hWndParent,phWnd)	\
    (This)->lpVtbl -> Create(This,hWndParent,phWnd)

#define IExternalChildWindow_get_MinSize(This,pSize)	\
    (This)->lpVtbl -> get_MinSize(This,pSize)

#define IExternalChildWindow_get_MaxSize(This,pSize)	\
    (This)->lpVtbl -> get_MaxSize(This,pSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExternalChildWindow_Create_Proxy( 
    IExternalChildWindow __RPC_FAR * This,
    /* [in] */ HWND hWndParent,
    /* [retval][out] */ HWND __RPC_FAR *phWnd);


void __RPC_STUB IExternalChildWindow_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IExternalChildWindow_get_MinSize_Proxy( 
    IExternalChildWindow __RPC_FAR * This,
    /* [retval][out] */ SIZE __RPC_FAR *pSize);


void __RPC_STUB IExternalChildWindow_get_MinSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IExternalChildWindow_get_MaxSize_Proxy( 
    IExternalChildWindow __RPC_FAR * This,
    /* [retval][out] */ SIZE __RPC_FAR *pSize);


void __RPC_STUB IExternalChildWindow_get_MaxSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExternalChildWindow_INTERFACE_DEFINED__ */


#ifndef __IBurnProgressDlg3_INTERFACE_DEFINED__
#define __IBurnProgressDlg3_INTERFACE_DEFINED__

/* interface IBurnProgressDlg3 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IBurnProgressDlg3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4aa37a65-74c2-4da1-b98b-3803c6b9c592")
    IBurnProgressDlg3 : public IBurnProgressDlg2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddCustomControl( 
            /* [in] */ BURN_PROGRESS_CUSTOM_CONTROL_POSITION bpccpWhere,
            /* [in] */ IExternalChildWindow __RPC_FAR *pControl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBurnProgressDlg3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBurnProgressDlg3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBurnProgressDlg3 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GUIFlags )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationName )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationType )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationType);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationSize )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationSize);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompilationTime )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ BSTR bstrCompilationTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Burn )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ NERO_CD_FORMAT cdFormat,
            /* [in] */ const void __RPC_FAR *pWriteCD,
            /* [in] */ IBurnSettings __RPC_FAR *pBurnSettings,
            /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Burn2 )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ const LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ NERO_CD_FORMAT cdFormat,
            /* [in] */ const void __RPC_FAR *pWriteCD,
            /* [in] */ DWORD dwBurnFlags,
            /* [in] */ DWORD dwSpeed,
            /* [in] */ IBurnCallbacks __RPC_FAR *pBurnCallbacks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            IBurnProgressDlg3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanCloseParent )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbCanClose);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateProgressBar )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ DWORD dwPreProgress,
            /* [in] */ DWORD dwPostProgress);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProgress )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ DWORD dwProgressInPercent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddLogLine )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ NERO_TEXT_TYPE type,
            /* [in] */ BSTR bstrLogLine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPhase )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ BSTR bstrPhase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WizardMode )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ BOOL bWizardMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddCustomControl )( 
            IBurnProgressDlg3 __RPC_FAR * This,
            /* [in] */ BURN_PROGRESS_CUSTOM_CONTROL_POSITION bpccpWhere,
            /* [in] */ IExternalChildWindow __RPC_FAR *pControl);
        
        END_INTERFACE
    } IBurnProgressDlg3Vtbl;

    interface IBurnProgressDlg3
    {
        CONST_VTBL struct IBurnProgressDlg3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBurnProgressDlg3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBurnProgressDlg3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBurnProgressDlg3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBurnProgressDlg3_put_GUIFlags(This,dwFlags)	\
    (This)->lpVtbl -> put_GUIFlags(This,dwFlags)

#define IBurnProgressDlg3_put_CompilationName(This,bstrCompilationName)	\
    (This)->lpVtbl -> put_CompilationName(This,bstrCompilationName)

#define IBurnProgressDlg3_put_CompilationType(This,bstrCompilationType)	\
    (This)->lpVtbl -> put_CompilationType(This,bstrCompilationType)

#define IBurnProgressDlg3_put_CompilationSize(This,bstrCompilationSize)	\
    (This)->lpVtbl -> put_CompilationSize(This,bstrCompilationSize)

#define IBurnProgressDlg3_put_CompilationTime(This,bstrCompilationTime)	\
    (This)->lpVtbl -> put_CompilationTime(This,bstrCompilationTime)

#define IBurnProgressDlg3_Burn(This,pDeviceInfo,cdFormat,pWriteCD,pBurnSettings,pBurnCallbacks)	\
    (This)->lpVtbl -> Burn(This,pDeviceInfo,cdFormat,pWriteCD,pBurnSettings,pBurnCallbacks)

#define IBurnProgressDlg3_Burn2(This,pDeviceInfo,cdFormat,pWriteCD,dwBurnFlags,dwSpeed,pBurnCallbacks)	\
    (This)->lpVtbl -> Burn2(This,pDeviceInfo,cdFormat,pWriteCD,dwBurnFlags,dwSpeed,pBurnCallbacks)

#define IBurnProgressDlg3_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define IBurnProgressDlg3_CanCloseParent(This,pbCanClose)	\
    (This)->lpVtbl -> CanCloseParent(This,pbCanClose)

#define IBurnProgressDlg3_AllocateProgressBar(This,dwPreProgress,dwPostProgress)	\
    (This)->lpVtbl -> AllocateProgressBar(This,dwPreProgress,dwPostProgress)

#define IBurnProgressDlg3_SetProgress(This,dwProgressInPercent)	\
    (This)->lpVtbl -> SetProgress(This,dwProgressInPercent)

#define IBurnProgressDlg3_AddLogLine(This,type,bstrLogLine)	\
    (This)->lpVtbl -> AddLogLine(This,type,bstrLogLine)

#define IBurnProgressDlg3_SetPhase(This,bstrPhase)	\
    (This)->lpVtbl -> SetPhase(This,bstrPhase)


#define IBurnProgressDlg3_put_WizardMode(This,bWizardMode)	\
    (This)->lpVtbl -> put_WizardMode(This,bWizardMode)


#define IBurnProgressDlg3_AddCustomControl(This,bpccpWhere,pControl)	\
    (This)->lpVtbl -> AddCustomControl(This,bpccpWhere,pControl)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBurnProgressDlg3_AddCustomControl_Proxy( 
    IBurnProgressDlg3 __RPC_FAR * This,
    /* [in] */ BURN_PROGRESS_CUSTOM_CONTROL_POSITION bpccpWhere,
    /* [in] */ IExternalChildWindow __RPC_FAR *pControl);


void __RPC_STUB IBurnProgressDlg3_AddCustomControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBurnProgressDlg3_INTERFACE_DEFINED__ */


#ifndef __IBurnProgressDlgEx_INTERFACE_DEFINED__
#define __IBurnProgressDlgEx_INTERFACE_DEFINED__

/* interface IBurnProgressDlgEx */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IBurnProgressDlgEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3ef6e092-cb60-4edb-bad2-dbcf097c452a")
    IBurnProgressDlgEx : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_IBurnProgressDlgCallbacks( 
            /* [in] */ IBurnProgressDlgCallbacks __RPC_FAR *pCallbacks) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBurnProgressDlgExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBurnProgressDlgEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBurnProgressDlgEx __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBurnProgressDlgEx __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IBurnProgressDlgCallbacks )( 
            IBurnProgressDlgEx __RPC_FAR * This,
            /* [in] */ IBurnProgressDlgCallbacks __RPC_FAR *pCallbacks);
        
        END_INTERFACE
    } IBurnProgressDlgExVtbl;

    interface IBurnProgressDlgEx
    {
        CONST_VTBL struct IBurnProgressDlgExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBurnProgressDlgEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBurnProgressDlgEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBurnProgressDlgEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBurnProgressDlgEx_put_IBurnProgressDlgCallbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_IBurnProgressDlgCallbacks(This,pCallbacks)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IBurnProgressDlgEx_put_IBurnProgressDlgCallbacks_Proxy( 
    IBurnProgressDlgEx __RPC_FAR * This,
    /* [in] */ IBurnProgressDlgCallbacks __RPC_FAR *pCallbacks);


void __RPC_STUB IBurnProgressDlgEx_put_IBurnProgressDlgCallbacks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBurnProgressDlgEx_INTERFACE_DEFINED__ */


#ifndef __IModalDialog_INTERFACE_DEFINED__
#define __IModalDialog_INTERFACE_DEFINED__

/* interface IModalDialog */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IModalDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d0509114-6204-41f6-a6da-8fd32eabc82f")
    IModalDialog : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DoModal( 
            /* [in] */ HWND hWndParent,
            /* [retval][out] */ int __RPC_FAR *piRetVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModalDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IModalDialog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IModalDialog __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IModalDialog __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoModal )( 
            IModalDialog __RPC_FAR * This,
            /* [in] */ HWND hWndParent,
            /* [retval][out] */ int __RPC_FAR *piRetVal);
        
        END_INTERFACE
    } IModalDialogVtbl;

    interface IModalDialog
    {
        CONST_VTBL struct IModalDialogVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModalDialog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IModalDialog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IModalDialog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IModalDialog_DoModal(This,hWndParent,piRetVal)	\
    (This)->lpVtbl -> DoModal(This,hWndParent,piRetVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IModalDialog_DoModal_Proxy( 
    IModalDialog __RPC_FAR * This,
    /* [in] */ HWND hWndParent,
    /* [retval][out] */ int __RPC_FAR *piRetVal);


void __RPC_STUB IModalDialog_DoModal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModalDialog_INTERFACE_DEFINED__ */


#ifndef __INEROAPI_CDRW_ERASE_MODE_INTERFACE_DEFINED__
#define __INEROAPI_CDRW_ERASE_MODE_INTERFACE_DEFINED__

/* interface INEROAPI_CDRW_ERASE_MODE */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_INEROAPI_CDRW_ERASE_MODE;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("30603428-c6bb-45c1-8b35-a02cda5c7086")
    INEROAPI_CDRW_ERASE_MODE : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_NEROAPI_CDRW_ERASE_MODE( 
            /* [in] */ NEROAPI_CDRW_ERASE_MODE eraseMode) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NEROAPI_CDRW_ERASE_MODE( 
            /* [retval][out] */ NEROAPI_CDRW_ERASE_MODE __RPC_FAR *pEraseMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INEROAPI_CDRW_ERASE_MODEVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INEROAPI_CDRW_ERASE_MODE __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INEROAPI_CDRW_ERASE_MODE __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INEROAPI_CDRW_ERASE_MODE __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NEROAPI_CDRW_ERASE_MODE )( 
            INEROAPI_CDRW_ERASE_MODE __RPC_FAR * This,
            /* [in] */ NEROAPI_CDRW_ERASE_MODE eraseMode);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NEROAPI_CDRW_ERASE_MODE )( 
            INEROAPI_CDRW_ERASE_MODE __RPC_FAR * This,
            /* [retval][out] */ NEROAPI_CDRW_ERASE_MODE __RPC_FAR *pEraseMode);
        
        END_INTERFACE
    } INEROAPI_CDRW_ERASE_MODEVtbl;

    interface INEROAPI_CDRW_ERASE_MODE
    {
        CONST_VTBL struct INEROAPI_CDRW_ERASE_MODEVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INEROAPI_CDRW_ERASE_MODE_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INEROAPI_CDRW_ERASE_MODE_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INEROAPI_CDRW_ERASE_MODE_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INEROAPI_CDRW_ERASE_MODE_put_NEROAPI_CDRW_ERASE_MODE(This,eraseMode)	\
    (This)->lpVtbl -> put_NEROAPI_CDRW_ERASE_MODE(This,eraseMode)

#define INEROAPI_CDRW_ERASE_MODE_get_NEROAPI_CDRW_ERASE_MODE(This,pEraseMode)	\
    (This)->lpVtbl -> get_NEROAPI_CDRW_ERASE_MODE(This,pEraseMode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE INEROAPI_CDRW_ERASE_MODE_put_NEROAPI_CDRW_ERASE_MODE_Proxy( 
    INEROAPI_CDRW_ERASE_MODE __RPC_FAR * This,
    /* [in] */ NEROAPI_CDRW_ERASE_MODE eraseMode);


void __RPC_STUB INEROAPI_CDRW_ERASE_MODE_put_NEROAPI_CDRW_ERASE_MODE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE INEROAPI_CDRW_ERASE_MODE_get_NEROAPI_CDRW_ERASE_MODE_Proxy( 
    INEROAPI_CDRW_ERASE_MODE __RPC_FAR * This,
    /* [retval][out] */ NEROAPI_CDRW_ERASE_MODE __RPC_FAR *pEraseMode);


void __RPC_STUB INEROAPI_CDRW_ERASE_MODE_get_NEROAPI_CDRW_ERASE_MODE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INEROAPI_CDRW_ERASE_MODE_INTERFACE_DEFINED__ */


#ifndef __IEraseDiscDlg_INTERFACE_DEFINED__
#define __IEraseDiscDlg_INTERFACE_DEFINED__

/* interface IEraseDiscDlg */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IEraseDiscDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9a45a9f6-fe69-4fe8-9862-751693dc87df")
    IEraseDiscDlg : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_NERO_DEVICEHANDLE( 
            /* [in] */ NERO_DEVICEHANDLE aDeviceHandle) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ErasingResult( 
            /* [retval][out] */ int __RPC_FAR *piErasingResult) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ErasingResultString( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrErasingResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEraseDiscDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEraseDiscDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEraseDiscDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEraseDiscDlg __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NERO_DEVICEHANDLE )( 
            IEraseDiscDlg __RPC_FAR * This,
            /* [in] */ NERO_DEVICEHANDLE aDeviceHandle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErasingResult )( 
            IEraseDiscDlg __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piErasingResult);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErasingResultString )( 
            IEraseDiscDlg __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrErasingResult);
        
        END_INTERFACE
    } IEraseDiscDlgVtbl;

    interface IEraseDiscDlg
    {
        CONST_VTBL struct IEraseDiscDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEraseDiscDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEraseDiscDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEraseDiscDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEraseDiscDlg_put_NERO_DEVICEHANDLE(This,aDeviceHandle)	\
    (This)->lpVtbl -> put_NERO_DEVICEHANDLE(This,aDeviceHandle)

#define IEraseDiscDlg_get_ErasingResult(This,piErasingResult)	\
    (This)->lpVtbl -> get_ErasingResult(This,piErasingResult)

#define IEraseDiscDlg_get_ErasingResultString(This,pbstrErasingResult)	\
    (This)->lpVtbl -> get_ErasingResultString(This,pbstrErasingResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IEraseDiscDlg_put_NERO_DEVICEHANDLE_Proxy( 
    IEraseDiscDlg __RPC_FAR * This,
    /* [in] */ NERO_DEVICEHANDLE aDeviceHandle);


void __RPC_STUB IEraseDiscDlg_put_NERO_DEVICEHANDLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IEraseDiscDlg_get_ErasingResult_Proxy( 
    IEraseDiscDlg __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piErasingResult);


void __RPC_STUB IEraseDiscDlg_get_ErasingResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IEraseDiscDlg_get_ErasingResultString_Proxy( 
    IEraseDiscDlg __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrErasingResult);


void __RPC_STUB IEraseDiscDlg_get_ErasingResultString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEraseDiscDlg_INTERFACE_DEFINED__ */


#ifndef __IEraseDiscDlg2_INTERFACE_DEFINED__
#define __IEraseDiscDlg2_INTERFACE_DEFINED__

/* interface IEraseDiscDlg2 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IEraseDiscDlg2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b28dc5d4-9593-4179-aaaa-df3c8f28db72")
    IEraseDiscDlg2 : public IEraseDiscDlg
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ErasingFlags( 
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEraseDiscDlg2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEraseDiscDlg2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEraseDiscDlg2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEraseDiscDlg2 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NERO_DEVICEHANDLE )( 
            IEraseDiscDlg2 __RPC_FAR * This,
            /* [in] */ NERO_DEVICEHANDLE aDeviceHandle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErasingResult )( 
            IEraseDiscDlg2 __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piErasingResult);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErasingResultString )( 
            IEraseDiscDlg2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrErasingResult);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErasingFlags )( 
            IEraseDiscDlg2 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IEraseDiscDlg2Vtbl;

    interface IEraseDiscDlg2
    {
        CONST_VTBL struct IEraseDiscDlg2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEraseDiscDlg2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEraseDiscDlg2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEraseDiscDlg2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEraseDiscDlg2_put_NERO_DEVICEHANDLE(This,aDeviceHandle)	\
    (This)->lpVtbl -> put_NERO_DEVICEHANDLE(This,aDeviceHandle)

#define IEraseDiscDlg2_get_ErasingResult(This,piErasingResult)	\
    (This)->lpVtbl -> get_ErasingResult(This,piErasingResult)

#define IEraseDiscDlg2_get_ErasingResultString(This,pbstrErasingResult)	\
    (This)->lpVtbl -> get_ErasingResultString(This,pbstrErasingResult)


#define IEraseDiscDlg2_put_ErasingFlags(This,dwFlags)	\
    (This)->lpVtbl -> put_ErasingFlags(This,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IEraseDiscDlg2_put_ErasingFlags_Proxy( 
    IEraseDiscDlg2 __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEraseDiscDlg2_put_ErasingFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEraseDiscDlg2_INTERFACE_DEFINED__ */


#ifndef __IEraseDiscCallbacks_INTERFACE_DEFINED__
#define __IEraseDiscCallbacks_INTERFACE_DEFINED__

/* interface IEraseDiscCallbacks */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IEraseDiscCallbacks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62b3f282-ad7a-42f7-bdb1-b27772bdb61d")
    IEraseDiscCallbacks : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnEraseDone( 
            /* [in] */ IEraseDiscDlg __RPC_FAR *pEraseDiscDlg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEraseDiscCallbacksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEraseDiscCallbacks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEraseDiscCallbacks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEraseDiscCallbacks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEraseDone )( 
            IEraseDiscCallbacks __RPC_FAR * This,
            /* [in] */ IEraseDiscDlg __RPC_FAR *pEraseDiscDlg);
        
        END_INTERFACE
    } IEraseDiscCallbacksVtbl;

    interface IEraseDiscCallbacks
    {
        CONST_VTBL struct IEraseDiscCallbacksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEraseDiscCallbacks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEraseDiscCallbacks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEraseDiscCallbacks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEraseDiscCallbacks_OnEraseDone(This,pEraseDiscDlg)	\
    (This)->lpVtbl -> OnEraseDone(This,pEraseDiscDlg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEraseDiscCallbacks_OnEraseDone_Proxy( 
    IEraseDiscCallbacks __RPC_FAR * This,
    /* [in] */ IEraseDiscDlg __RPC_FAR *pEraseDiscDlg);


void __RPC_STUB IEraseDiscCallbacks_OnEraseDone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEraseDiscCallbacks_INTERFACE_DEFINED__ */


#ifndef __IEraseDiscDlg3_INTERFACE_DEFINED__
#define __IEraseDiscDlg3_INTERFACE_DEFINED__

/* interface IEraseDiscDlg3 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IEraseDiscDlg3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79b3261b-b57f-493e-a7bd-3325b5f58350")
    IEraseDiscDlg3 : public IEraseDiscDlg2
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Callbacks( 
            /* [in] */ IEraseDiscCallbacks __RPC_FAR *pCallbacks) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEraseDiscDlg3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEraseDiscDlg3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEraseDiscDlg3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEraseDiscDlg3 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NERO_DEVICEHANDLE )( 
            IEraseDiscDlg3 __RPC_FAR * This,
            /* [in] */ NERO_DEVICEHANDLE aDeviceHandle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErasingResult )( 
            IEraseDiscDlg3 __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piErasingResult);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErasingResultString )( 
            IEraseDiscDlg3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrErasingResult);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErasingFlags )( 
            IEraseDiscDlg3 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            IEraseDiscDlg3 __RPC_FAR * This,
            /* [in] */ IEraseDiscCallbacks __RPC_FAR *pCallbacks);
        
        END_INTERFACE
    } IEraseDiscDlg3Vtbl;

    interface IEraseDiscDlg3
    {
        CONST_VTBL struct IEraseDiscDlg3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEraseDiscDlg3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEraseDiscDlg3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEraseDiscDlg3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEraseDiscDlg3_put_NERO_DEVICEHANDLE(This,aDeviceHandle)	\
    (This)->lpVtbl -> put_NERO_DEVICEHANDLE(This,aDeviceHandle)

#define IEraseDiscDlg3_get_ErasingResult(This,piErasingResult)	\
    (This)->lpVtbl -> get_ErasingResult(This,piErasingResult)

#define IEraseDiscDlg3_get_ErasingResultString(This,pbstrErasingResult)	\
    (This)->lpVtbl -> get_ErasingResultString(This,pbstrErasingResult)


#define IEraseDiscDlg3_put_ErasingFlags(This,dwFlags)	\
    (This)->lpVtbl -> put_ErasingFlags(This,dwFlags)


#define IEraseDiscDlg3_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IEraseDiscDlg3_put_Callbacks_Proxy( 
    IEraseDiscDlg3 __RPC_FAR * This,
    /* [in] */ IEraseDiscCallbacks __RPC_FAR *pCallbacks);


void __RPC_STUB IEraseDiscDlg3_put_Callbacks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEraseDiscDlg3_INTERFACE_DEFINED__ */


#ifndef __IEraseDiscDlg4_INTERFACE_DEFINED__
#define __IEraseDiscDlg4_INTERFACE_DEFINED__

/* interface IEraseDiscDlg4 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IEraseDiscDlg4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d658288d-1d49-4eb9-869e-10e5ddd40d16")
    IEraseDiscDlg4 : public IEraseDiscDlg3
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_NeverShowDialogBox( 
            /* [in] */ BOOL bDontShow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEraseDiscDlg4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEraseDiscDlg4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEraseDiscDlg4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEraseDiscDlg4 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NERO_DEVICEHANDLE )( 
            IEraseDiscDlg4 __RPC_FAR * This,
            /* [in] */ NERO_DEVICEHANDLE aDeviceHandle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErasingResult )( 
            IEraseDiscDlg4 __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piErasingResult);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ErasingResultString )( 
            IEraseDiscDlg4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrErasingResult);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ErasingFlags )( 
            IEraseDiscDlg4 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            IEraseDiscDlg4 __RPC_FAR * This,
            /* [in] */ IEraseDiscCallbacks __RPC_FAR *pCallbacks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NeverShowDialogBox )( 
            IEraseDiscDlg4 __RPC_FAR * This,
            /* [in] */ BOOL bDontShow);
        
        END_INTERFACE
    } IEraseDiscDlg4Vtbl;

    interface IEraseDiscDlg4
    {
        CONST_VTBL struct IEraseDiscDlg4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEraseDiscDlg4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEraseDiscDlg4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEraseDiscDlg4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEraseDiscDlg4_put_NERO_DEVICEHANDLE(This,aDeviceHandle)	\
    (This)->lpVtbl -> put_NERO_DEVICEHANDLE(This,aDeviceHandle)

#define IEraseDiscDlg4_get_ErasingResult(This,piErasingResult)	\
    (This)->lpVtbl -> get_ErasingResult(This,piErasingResult)

#define IEraseDiscDlg4_get_ErasingResultString(This,pbstrErasingResult)	\
    (This)->lpVtbl -> get_ErasingResultString(This,pbstrErasingResult)


#define IEraseDiscDlg4_put_ErasingFlags(This,dwFlags)	\
    (This)->lpVtbl -> put_ErasingFlags(This,dwFlags)


#define IEraseDiscDlg4_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)


#define IEraseDiscDlg4_put_NeverShowDialogBox(This,bDontShow)	\
    (This)->lpVtbl -> put_NeverShowDialogBox(This,bDontShow)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IEraseDiscDlg4_put_NeverShowDialogBox_Proxy( 
    IEraseDiscDlg4 __RPC_FAR * This,
    /* [in] */ BOOL bDontShow);


void __RPC_STUB IEraseDiscDlg4_put_NeverShowDialogBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEraseDiscDlg4_INTERFACE_DEFINED__ */


#ifndef __IEraseSettingsDlg_INTERFACE_DEFINED__
#define __IEraseSettingsDlg_INTERFACE_DEFINED__

/* interface IEraseSettingsDlg */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IEraseSettingsDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("cd72cad8-d41a-40b2-9943-01f30b1507cc")
    IEraseSettingsDlg : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ModelessErase( 
            /* [in] */ BOOL bModelessErase) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Callbacks( 
            /* [in] */ IEraseDiscCallbacks __RPC_FAR *pCallbacks) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEraseSettingsDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEraseSettingsDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEraseSettingsDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEraseSettingsDlg __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ModelessErase )( 
            IEraseSettingsDlg __RPC_FAR * This,
            /* [in] */ BOOL bModelessErase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            IEraseSettingsDlg __RPC_FAR * This,
            /* [in] */ IEraseDiscCallbacks __RPC_FAR *pCallbacks);
        
        END_INTERFACE
    } IEraseSettingsDlgVtbl;

    interface IEraseSettingsDlg
    {
        CONST_VTBL struct IEraseSettingsDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEraseSettingsDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEraseSettingsDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEraseSettingsDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEraseSettingsDlg_put_ModelessErase(This,bModelessErase)	\
    (This)->lpVtbl -> put_ModelessErase(This,bModelessErase)

#define IEraseSettingsDlg_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IEraseSettingsDlg_put_ModelessErase_Proxy( 
    IEraseSettingsDlg __RPC_FAR * This,
    /* [in] */ BOOL bModelessErase);


void __RPC_STUB IEraseSettingsDlg_put_ModelessErase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IEraseSettingsDlg_put_Callbacks_Proxy( 
    IEraseSettingsDlg __RPC_FAR * This,
    /* [in] */ IEraseDiscCallbacks __RPC_FAR *pCallbacks);


void __RPC_STUB IEraseSettingsDlg_put_Callbacks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEraseSettingsDlg_INTERFACE_DEFINED__ */


#ifndef __IEraseSettingsDlg2_INTERFACE_DEFINED__
#define __IEraseSettingsDlg2_INTERFACE_DEFINED__

/* interface IEraseSettingsDlg2 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IEraseSettingsDlg2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0040D3ED-84A2-4e56-9539-646BDC57DE4A")
    IEraseSettingsDlg2 : public IEraseSettingsDlg
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ModelessDlgHWND( 
            /* [retval][out] */ HWND __RPC_FAR *phModelessDlgHWND) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEraseSettingsDlg2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEraseSettingsDlg2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEraseSettingsDlg2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEraseSettingsDlg2 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ModelessErase )( 
            IEraseSettingsDlg2 __RPC_FAR * This,
            /* [in] */ BOOL bModelessErase);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            IEraseSettingsDlg2 __RPC_FAR * This,
            /* [in] */ IEraseDiscCallbacks __RPC_FAR *pCallbacks);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModelessDlgHWND )( 
            IEraseSettingsDlg2 __RPC_FAR * This,
            /* [retval][out] */ HWND __RPC_FAR *phModelessDlgHWND);
        
        END_INTERFACE
    } IEraseSettingsDlg2Vtbl;

    interface IEraseSettingsDlg2
    {
        CONST_VTBL struct IEraseSettingsDlg2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEraseSettingsDlg2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEraseSettingsDlg2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEraseSettingsDlg2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEraseSettingsDlg2_put_ModelessErase(This,bModelessErase)	\
    (This)->lpVtbl -> put_ModelessErase(This,bModelessErase)

#define IEraseSettingsDlg2_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)


#define IEraseSettingsDlg2_get_ModelessDlgHWND(This,phModelessDlgHWND)	\
    (This)->lpVtbl -> get_ModelessDlgHWND(This,phModelessDlgHWND)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IEraseSettingsDlg2_get_ModelessDlgHWND_Proxy( 
    IEraseSettingsDlg2 __RPC_FAR * This,
    /* [retval][out] */ HWND __RPC_FAR *phModelessDlgHWND);


void __RPC_STUB IEraseSettingsDlg2_get_ModelessDlgHWND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEraseSettingsDlg2_INTERFACE_DEFINED__ */


#ifndef __IInitSettings_INTERFACE_DEFINED__
#define __IInitSettings_INTERFACE_DEFINED__

/* interface IInitSettings */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IInitSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0f5ebcfd-2d94-4896-8169-088870dfdbaf")
    IInitSettings : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_HMODULE( 
            /* [in] */ HMODULE hNeroAPIModule) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_LanguageCode( 
            /* [in] */ const signed char __RPC_FAR *psLanguageCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInitSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInitSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInitSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInitSettings __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HMODULE )( 
            IInitSettings __RPC_FAR * This,
            /* [in] */ HMODULE hNeroAPIModule);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LanguageCode )( 
            IInitSettings __RPC_FAR * This,
            /* [in] */ const signed char __RPC_FAR *psLanguageCode);
        
        END_INTERFACE
    } IInitSettingsVtbl;

    interface IInitSettings
    {
        CONST_VTBL struct IInitSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInitSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInitSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInitSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInitSettings_put_HMODULE(This,hNeroAPIModule)	\
    (This)->lpVtbl -> put_HMODULE(This,hNeroAPIModule)

#define IInitSettings_put_LanguageCode(This,psLanguageCode)	\
    (This)->lpVtbl -> put_LanguageCode(This,psLanguageCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IInitSettings_put_HMODULE_Proxy( 
    IInitSettings __RPC_FAR * This,
    /* [in] */ HMODULE hNeroAPIModule);


void __RPC_STUB IInitSettings_put_HMODULE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IInitSettings_put_LanguageCode_Proxy( 
    IInitSettings __RPC_FAR * This,
    /* [in] */ const signed char __RPC_FAR *psLanguageCode);


void __RPC_STUB IInitSettings_put_LanguageCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInitSettings_INTERFACE_DEFINED__ */


#ifndef __IInitSettings2_INTERFACE_DEFINED__
#define __IInitSettings2_INTERFACE_DEFINED__

/* interface IInitSettings2 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IInitSettings2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4baf9833-70bb-4523-8349-5209b5644587")
    IInitSettings2 : public IInitSettings
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AppTitle( 
            /* [in] */ const signed char __RPC_FAR *psAppTitle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInitSettings2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInitSettings2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInitSettings2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInitSettings2 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HMODULE )( 
            IInitSettings2 __RPC_FAR * This,
            /* [in] */ HMODULE hNeroAPIModule);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LanguageCode )( 
            IInitSettings2 __RPC_FAR * This,
            /* [in] */ const signed char __RPC_FAR *psLanguageCode);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AppTitle )( 
            IInitSettings2 __RPC_FAR * This,
            /* [in] */ const signed char __RPC_FAR *psAppTitle);
        
        END_INTERFACE
    } IInitSettings2Vtbl;

    interface IInitSettings2
    {
        CONST_VTBL struct IInitSettings2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInitSettings2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInitSettings2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInitSettings2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInitSettings2_put_HMODULE(This,hNeroAPIModule)	\
    (This)->lpVtbl -> put_HMODULE(This,hNeroAPIModule)

#define IInitSettings2_put_LanguageCode(This,psLanguageCode)	\
    (This)->lpVtbl -> put_LanguageCode(This,psLanguageCode)


#define IInitSettings2_put_AppTitle(This,psAppTitle)	\
    (This)->lpVtbl -> put_AppTitle(This,psAppTitle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IInitSettings2_put_AppTitle_Proxy( 
    IInitSettings2 __RPC_FAR * This,
    /* [in] */ const signed char __RPC_FAR *psAppTitle);


void __RPC_STUB IInitSettings2_put_AppTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInitSettings2_INTERFACE_DEFINED__ */


#ifndef __IInitSettings3_INTERFACE_DEFINED__
#define __IInitSettings3_INTERFACE_DEFINED__

/* interface IInitSettings3 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IInitSettings3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9964816b-df5f-44aa-9b87-f0de3f4c57fc")
    IInitSettings3 : public IInitSettings2
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_CompatibilityMgr( 
            /* [in] */ IUnknown __RPC_FAR *pMgr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInitSettings3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInitSettings3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInitSettings3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInitSettings3 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HMODULE )( 
            IInitSettings3 __RPC_FAR * This,
            /* [in] */ HMODULE hNeroAPIModule);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LanguageCode )( 
            IInitSettings3 __RPC_FAR * This,
            /* [in] */ const signed char __RPC_FAR *psLanguageCode);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AppTitle )( 
            IInitSettings3 __RPC_FAR * This,
            /* [in] */ const signed char __RPC_FAR *psAppTitle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CompatibilityMgr )( 
            IInitSettings3 __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pMgr);
        
        END_INTERFACE
    } IInitSettings3Vtbl;

    interface IInitSettings3
    {
        CONST_VTBL struct IInitSettings3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInitSettings3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInitSettings3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInitSettings3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInitSettings3_put_HMODULE(This,hNeroAPIModule)	\
    (This)->lpVtbl -> put_HMODULE(This,hNeroAPIModule)

#define IInitSettings3_put_LanguageCode(This,psLanguageCode)	\
    (This)->lpVtbl -> put_LanguageCode(This,psLanguageCode)


#define IInitSettings3_put_AppTitle(This,psAppTitle)	\
    (This)->lpVtbl -> put_AppTitle(This,psAppTitle)


#define IInitSettings3_put_CompatibilityMgr(This,pMgr)	\
    (This)->lpVtbl -> put_CompatibilityMgr(This,pMgr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IInitSettings3_put_CompatibilityMgr_Proxy( 
    IInitSettings3 __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pMgr);


void __RPC_STUB IInitSettings3_put_CompatibilityMgr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInitSettings3_INTERFACE_DEFINED__ */


#ifndef __IInformation_INTERFACE_DEFINED__
#define __IInformation_INTERFACE_DEFINED__

/* interface IInformation */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IInformation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5db904aa-9c92-494e-897c-5aaa5337cf2d")
    IInformation : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [out] */ WORD __RPC_FAR *pwMajHi,
            /* [out] */ WORD __RPC_FAR *pwMajLo,
            /* [out] */ WORD __RPC_FAR *pwMinHi,
            /* [out] */ WORD __RPC_FAR *pwMinLo) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_InstallFolder( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFolder) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInformationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInformation __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInformation __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInformation __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IInformation __RPC_FAR * This,
            /* [out] */ WORD __RPC_FAR *pwMajHi,
            /* [out] */ WORD __RPC_FAR *pwMajLo,
            /* [out] */ WORD __RPC_FAR *pwMinHi,
            /* [out] */ WORD __RPC_FAR *pwMinLo);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InstallFolder )( 
            IInformation __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFolder);
        
        END_INTERFACE
    } IInformationVtbl;

    interface IInformation
    {
        CONST_VTBL struct IInformationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInformation_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInformation_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInformation_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInformation_get_Version(This,pwMajHi,pwMajLo,pwMinHi,pwMinLo)	\
    (This)->lpVtbl -> get_Version(This,pwMajHi,pwMajLo,pwMinHi,pwMinLo)

#define IInformation_get_InstallFolder(This,pbstrFolder)	\
    (This)->lpVtbl -> get_InstallFolder(This,pbstrFolder)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IInformation_get_Version_Proxy( 
    IInformation __RPC_FAR * This,
    /* [out] */ WORD __RPC_FAR *pwMajHi,
    /* [out] */ WORD __RPC_FAR *pwMajLo,
    /* [out] */ WORD __RPC_FAR *pwMinHi,
    /* [out] */ WORD __RPC_FAR *pwMinLo);


void __RPC_STUB IInformation_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IInformation_get_InstallFolder_Proxy( 
    IInformation __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFolder);


void __RPC_STUB IInformation_get_InstallFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInformation_INTERFACE_DEFINED__ */


#ifndef __IChildWindow_INTERFACE_DEFINED__
#define __IChildWindow_INTERFACE_DEFINED__

/* interface IChildWindow */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IChildWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f714bdc1-aec8-41de-83d2-db9c9437fdb2")
    IChildWindow : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Subclass( 
            /* [in] */ HWND hWnd,
            /* [retval][out] */ BOOL __RPC_FAR *pbRetVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChildWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IChildWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IChildWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IChildWindow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Subclass )( 
            IChildWindow __RPC_FAR * This,
            /* [in] */ HWND hWnd,
            /* [retval][out] */ BOOL __RPC_FAR *pbRetVal);
        
        END_INTERFACE
    } IChildWindowVtbl;

    interface IChildWindow
    {
        CONST_VTBL struct IChildWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChildWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChildWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChildWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChildWindow_Subclass(This,hWnd,pbRetVal)	\
    (This)->lpVtbl -> Subclass(This,hWnd,pbRetVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IChildWindow_Subclass_Proxy( 
    IChildWindow __RPC_FAR * This,
    /* [in] */ HWND hWnd,
    /* [retval][out] */ BOOL __RPC_FAR *pbRetVal);


void __RPC_STUB IChildWindow_Subclass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChildWindow_INTERFACE_DEFINED__ */


#ifndef __IImageInfoDlg_INTERFACE_DEFINED__
#define __IImageInfoDlg_INTERFACE_DEFINED__

/* interface IImageInfoDlg */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IImageInfoDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2302b658-de28-4233-96bd-3bb5fb7b747e")
    IImageInfoDlg : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ImageFilename( 
            /* [in] */ BSTR bstrFilename) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageInfoDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImageInfoDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImageInfoDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImageInfoDlg __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ImageFilename )( 
            IImageInfoDlg __RPC_FAR * This,
            /* [in] */ BSTR bstrFilename);
        
        END_INTERFACE
    } IImageInfoDlgVtbl;

    interface IImageInfoDlg
    {
        CONST_VTBL struct IImageInfoDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageInfoDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImageInfoDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImageInfoDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImageInfoDlg_put_ImageFilename(This,bstrFilename)	\
    (This)->lpVtbl -> put_ImageFilename(This,bstrFilename)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IImageInfoDlg_put_ImageFilename_Proxy( 
    IImageInfoDlg __RPC_FAR * This,
    /* [in] */ BSTR bstrFilename);


void __RPC_STUB IImageInfoDlg_put_ImageFilename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageInfoDlg_INTERFACE_DEFINED__ */


#ifndef __IChooseSessionDlg_INTERFACE_DEFINED__
#define __IChooseSessionDlg_INTERFACE_DEFINED__

/* interface IChooseSessionDlg */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IChooseSessionDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35e68486-0c10-41c5-a52a-55d8c0ba61f2")
    IChooseSessionDlg : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_TrackNumber( 
            /* [retval][out] */ DWORD __RPC_FAR *pdwVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChooseSessionDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IChooseSessionDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IChooseSessionDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IChooseSessionDlg __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TrackNumber )( 
            IChooseSessionDlg __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwVal);
        
        END_INTERFACE
    } IChooseSessionDlgVtbl;

    interface IChooseSessionDlg
    {
        CONST_VTBL struct IChooseSessionDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChooseSessionDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChooseSessionDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChooseSessionDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChooseSessionDlg_get_TrackNumber(This,pdwVal)	\
    (This)->lpVtbl -> get_TrackNumber(This,pdwVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IChooseSessionDlg_get_TrackNumber_Proxy( 
    IChooseSessionDlg __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pdwVal);


void __RPC_STUB IChooseSessionDlg_get_TrackNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChooseSessionDlg_INTERFACE_DEFINED__ */


#ifndef __ISpeedComboboxCallbacks_INTERFACE_DEFINED__
#define __ISpeedComboboxCallbacks_INTERFACE_DEFINED__

/* interface ISpeedComboboxCallbacks */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_ISpeedComboboxCallbacks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("efbe7cff-6878-4dce-b40d-e21c5d7698b6")
    ISpeedComboboxCallbacks : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnContentRefreshed( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpeedComboboxCallbacksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpeedComboboxCallbacks __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpeedComboboxCallbacks __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpeedComboboxCallbacks __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnContentRefreshed )( 
            ISpeedComboboxCallbacks __RPC_FAR * This);
        
        END_INTERFACE
    } ISpeedComboboxCallbacksVtbl;

    interface ISpeedComboboxCallbacks
    {
        CONST_VTBL struct ISpeedComboboxCallbacksVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpeedComboboxCallbacks_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpeedComboboxCallbacks_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpeedComboboxCallbacks_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpeedComboboxCallbacks_OnContentRefreshed(This)	\
    (This)->lpVtbl -> OnContentRefreshed(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISpeedComboboxCallbacks_OnContentRefreshed_Proxy( 
    ISpeedComboboxCallbacks __RPC_FAR * This);


void __RPC_STUB ISpeedComboboxCallbacks_OnContentRefreshed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpeedComboboxCallbacks_INTERFACE_DEFINED__ */


#ifndef __ISpeedCombobox_INTERFACE_DEFINED__
#define __ISpeedCombobox_INTERFACE_DEFINED__

/* interface ISpeedCombobox */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ISpeedCombobox;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4855a95f-969f-49cd-8f5a-ca04e2aa7a62")
    ISpeedCombobox : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Callbacks( 
            /* [in] */ ISpeedComboboxCallbacks __RPC_FAR *pCallbacks) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MediaType( 
            /* [in] */ NERO_MEDIA_TYPE mediaType) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Speed( 
            /* [retval][out] */ DWORD __RPC_FAR *pdwSpeed) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SpeedInKBs( 
            /* [retval][out] */ DWORD __RPC_FAR *pdwSpeedInKBs) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_HideWhenEmpty( 
            /* [in] */ BOOL bHide) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpeedComboboxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpeedCombobox __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpeedCombobox __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpeedCombobox __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            ISpeedCombobox __RPC_FAR * This,
            /* [in] */ ISpeedComboboxCallbacks __RPC_FAR *pCallbacks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MediaType )( 
            ISpeedCombobox __RPC_FAR * This,
            /* [in] */ NERO_MEDIA_TYPE mediaType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Speed )( 
            ISpeedCombobox __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwSpeed);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeedInKBs )( 
            ISpeedCombobox __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwSpeedInKBs);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HideWhenEmpty )( 
            ISpeedCombobox __RPC_FAR * This,
            /* [in] */ BOOL bHide);
        
        END_INTERFACE
    } ISpeedComboboxVtbl;

    interface ISpeedCombobox
    {
        CONST_VTBL struct ISpeedComboboxVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpeedCombobox_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpeedCombobox_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpeedCombobox_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpeedCombobox_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)

#define ISpeedCombobox_put_MediaType(This,mediaType)	\
    (This)->lpVtbl -> put_MediaType(This,mediaType)

#define ISpeedCombobox_get_Speed(This,pdwSpeed)	\
    (This)->lpVtbl -> get_Speed(This,pdwSpeed)

#define ISpeedCombobox_get_SpeedInKBs(This,pdwSpeedInKBs)	\
    (This)->lpVtbl -> get_SpeedInKBs(This,pdwSpeedInKBs)

#define ISpeedCombobox_put_HideWhenEmpty(This,bHide)	\
    (This)->lpVtbl -> put_HideWhenEmpty(This,bHide)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE ISpeedCombobox_put_Callbacks_Proxy( 
    ISpeedCombobox __RPC_FAR * This,
    /* [in] */ ISpeedComboboxCallbacks __RPC_FAR *pCallbacks);


void __RPC_STUB ISpeedCombobox_put_Callbacks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpeedCombobox_put_MediaType_Proxy( 
    ISpeedCombobox __RPC_FAR * This,
    /* [in] */ NERO_MEDIA_TYPE mediaType);


void __RPC_STUB ISpeedCombobox_put_MediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpeedCombobox_get_Speed_Proxy( 
    ISpeedCombobox __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pdwSpeed);


void __RPC_STUB ISpeedCombobox_get_Speed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ISpeedCombobox_get_SpeedInKBs_Proxy( 
    ISpeedCombobox __RPC_FAR * This,
    /* [retval][out] */ DWORD __RPC_FAR *pdwSpeedInKBs);


void __RPC_STUB ISpeedCombobox_get_SpeedInKBs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpeedCombobox_put_HideWhenEmpty_Proxy( 
    ISpeedCombobox __RPC_FAR * This,
    /* [in] */ BOOL bHide);


void __RPC_STUB ISpeedCombobox_put_HideWhenEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpeedCombobox_INTERFACE_DEFINED__ */


#ifndef __ISpeedCombobox2_INTERFACE_DEFINED__
#define __ISpeedCombobox2_INTERFACE_DEFINED__

/* interface ISpeedCombobox2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ISpeedCombobox2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6c373d24-7575-4507-972c-1814914570c9")
    ISpeedCombobox2 : public ISpeedCombobox
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SpeedInKbps( 
            /* [in] */ DWORD dwSpeedInKbps) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SpeedInX( 
            /* [in] */ DWORD dwSpeedInX) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpeedCombobox2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpeedCombobox2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpeedCombobox2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpeedCombobox2 __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Callbacks )( 
            ISpeedCombobox2 __RPC_FAR * This,
            /* [in] */ ISpeedComboboxCallbacks __RPC_FAR *pCallbacks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MediaType )( 
            ISpeedCombobox2 __RPC_FAR * This,
            /* [in] */ NERO_MEDIA_TYPE mediaType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Speed )( 
            ISpeedCombobox2 __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwSpeed);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeedInKBs )( 
            ISpeedCombobox2 __RPC_FAR * This,
            /* [retval][out] */ DWORD __RPC_FAR *pdwSpeedInKBs);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HideWhenEmpty )( 
            ISpeedCombobox2 __RPC_FAR * This,
            /* [in] */ BOOL bHide);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SpeedInKbps )( 
            ISpeedCombobox2 __RPC_FAR * This,
            /* [in] */ DWORD dwSpeedInKbps);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SpeedInX )( 
            ISpeedCombobox2 __RPC_FAR * This,
            /* [in] */ DWORD dwSpeedInX);
        
        END_INTERFACE
    } ISpeedCombobox2Vtbl;

    interface ISpeedCombobox2
    {
        CONST_VTBL struct ISpeedCombobox2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpeedCombobox2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpeedCombobox2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpeedCombobox2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpeedCombobox2_put_Callbacks(This,pCallbacks)	\
    (This)->lpVtbl -> put_Callbacks(This,pCallbacks)

#define ISpeedCombobox2_put_MediaType(This,mediaType)	\
    (This)->lpVtbl -> put_MediaType(This,mediaType)

#define ISpeedCombobox2_get_Speed(This,pdwSpeed)	\
    (This)->lpVtbl -> get_Speed(This,pdwSpeed)

#define ISpeedCombobox2_get_SpeedInKBs(This,pdwSpeedInKBs)	\
    (This)->lpVtbl -> get_SpeedInKBs(This,pdwSpeedInKBs)

#define ISpeedCombobox2_put_HideWhenEmpty(This,bHide)	\
    (This)->lpVtbl -> put_HideWhenEmpty(This,bHide)


#define ISpeedCombobox2_put_SpeedInKbps(This,dwSpeedInKbps)	\
    (This)->lpVtbl -> put_SpeedInKbps(This,dwSpeedInKbps)

#define ISpeedCombobox2_put_SpeedInX(This,dwSpeedInX)	\
    (This)->lpVtbl -> put_SpeedInX(This,dwSpeedInX)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE ISpeedCombobox2_put_SpeedInKbps_Proxy( 
    ISpeedCombobox2 __RPC_FAR * This,
    /* [in] */ DWORD dwSpeedInKbps);


void __RPC_STUB ISpeedCombobox2_put_SpeedInKbps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ISpeedCombobox2_put_SpeedInX_Proxy( 
    ISpeedCombobox2 __RPC_FAR * This,
    /* [in] */ DWORD dwSpeedInX);


void __RPC_STUB ISpeedCombobox2_put_SpeedInX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpeedCombobox2_INTERFACE_DEFINED__ */


#ifndef __IWaitForMediaDlg_INTERFACE_DEFINED__
#define __IWaitForMediaDlg_INTERFACE_DEFINED__

/* interface IWaitForMediaDlg */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IWaitForMediaDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ed8b6cb0-5ab6-4db4-9d61-5dcf28f73d05")
    IWaitForMediaDlg : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE WaitForMedia( 
            /* [in] */ HWND hWndParent,
            /* [in] */ NERO_DEVICEHANDLE aDeviceHandle,
            /* [in] */ NERO_MEDIA_SET nms,
            /* [in] */ DWORD dwBurnFlags,
            /* [in] */ void __RPC_FAR *pCDStamp,
            /* [retval][out] */ BOOL __RPC_FAR *pbAbort) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWaitForMediaDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWaitForMediaDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWaitForMediaDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWaitForMediaDlg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForMedia )( 
            IWaitForMediaDlg __RPC_FAR * This,
            /* [in] */ HWND hWndParent,
            /* [in] */ NERO_DEVICEHANDLE aDeviceHandle,
            /* [in] */ NERO_MEDIA_SET nms,
            /* [in] */ DWORD dwBurnFlags,
            /* [in] */ void __RPC_FAR *pCDStamp,
            /* [retval][out] */ BOOL __RPC_FAR *pbAbort);
        
        END_INTERFACE
    } IWaitForMediaDlgVtbl;

    interface IWaitForMediaDlg
    {
        CONST_VTBL struct IWaitForMediaDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWaitForMediaDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWaitForMediaDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWaitForMediaDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWaitForMediaDlg_WaitForMedia(This,hWndParent,aDeviceHandle,nms,dwBurnFlags,pCDStamp,pbAbort)	\
    (This)->lpVtbl -> WaitForMedia(This,hWndParent,aDeviceHandle,nms,dwBurnFlags,pCDStamp,pbAbort)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWaitForMediaDlg_WaitForMedia_Proxy( 
    IWaitForMediaDlg __RPC_FAR * This,
    /* [in] */ HWND hWndParent,
    /* [in] */ NERO_DEVICEHANDLE aDeviceHandle,
    /* [in] */ NERO_MEDIA_SET nms,
    /* [in] */ DWORD dwBurnFlags,
    /* [in] */ void __RPC_FAR *pCDStamp,
    /* [retval][out] */ BOOL __RPC_FAR *pbAbort);


void __RPC_STUB IWaitForMediaDlg_WaitForMedia_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWaitForMediaDlg_INTERFACE_DEFINED__ */


#ifndef __IUserDlgHandler_INTERFACE_DEFINED__
#define __IUserDlgHandler_INTERFACE_DEFINED__

/* interface IUserDlgHandler */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IUserDlgHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("911fb1f9-6576-4947-bf24-476babe78016")
    IUserDlgHandler : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ParentHWND( 
            /* [in] */ HWND hWndParent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleUserDlg( 
            /* [in] */ NeroUserDlgInOut type,
            /* [in] */ void __RPC_FAR *data,
            /* [retval][out] */ NeroUserDlgInOut __RPC_FAR *pRetVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Aborted( 
            /* [retval][out] */ BOOL __RPC_FAR *pbAborted) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Aborted( 
            /* [in] */ BOOL bAborted) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUserDlgHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUserDlgHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUserDlgHandler __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUserDlgHandler __RPC_FAR * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ParentHWND )( 
            IUserDlgHandler __RPC_FAR * This,
            /* [in] */ HWND hWndParent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleUserDlg )( 
            IUserDlgHandler __RPC_FAR * This,
            /* [in] */ NeroUserDlgInOut type,
            /* [in] */ void __RPC_FAR *data,
            /* [retval][out] */ NeroUserDlgInOut __RPC_FAR *pRetVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Aborted )( 
            IUserDlgHandler __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbAborted);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Aborted )( 
            IUserDlgHandler __RPC_FAR * This,
            /* [in] */ BOOL bAborted);
        
        END_INTERFACE
    } IUserDlgHandlerVtbl;

    interface IUserDlgHandler
    {
        CONST_VTBL struct IUserDlgHandlerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUserDlgHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUserDlgHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUserDlgHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUserDlgHandler_put_ParentHWND(This,hWndParent)	\
    (This)->lpVtbl -> put_ParentHWND(This,hWndParent)

#define IUserDlgHandler_HandleUserDlg(This,type,data,pRetVal)	\
    (This)->lpVtbl -> HandleUserDlg(This,type,data,pRetVal)

#define IUserDlgHandler_get_Aborted(This,pbAborted)	\
    (This)->lpVtbl -> get_Aborted(This,pbAborted)

#define IUserDlgHandler_put_Aborted(This,bAborted)	\
    (This)->lpVtbl -> put_Aborted(This,bAborted)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IUserDlgHandler_put_ParentHWND_Proxy( 
    IUserDlgHandler __RPC_FAR * This,
    /* [in] */ HWND hWndParent);


void __RPC_STUB IUserDlgHandler_put_ParentHWND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUserDlgHandler_HandleUserDlg_Proxy( 
    IUserDlgHandler __RPC_FAR * This,
    /* [in] */ NeroUserDlgInOut type,
    /* [in] */ void __RPC_FAR *data,
    /* [retval][out] */ NeroUserDlgInOut __RPC_FAR *pRetVal);


void __RPC_STUB IUserDlgHandler_HandleUserDlg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IUserDlgHandler_get_Aborted_Proxy( 
    IUserDlgHandler __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pbAborted);


void __RPC_STUB IUserDlgHandler_get_Aborted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IUserDlgHandler_put_Aborted_Proxy( 
    IUserDlgHandler __RPC_FAR * This,
    /* [in] */ BOOL bAborted);


void __RPC_STUB IUserDlgHandler_put_Aborted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUserDlgHandler_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_NeroCBUI_0293 */
/* [local] */ 

#ifdef __AFX_H__
typedef AFX_OLDPROPSHEETPAGE * LPAFX_OLDPROPSHEETPAGE;
#else
typedef long LPAFX_OLDPROPSHEETPAGE;
#endif
#if 0
typedef long LPAFX_OLDPROPSHEETPAGE;

typedef long LPCAFX_OLDPROPSHEETPAGE;

#endif


extern RPC_IF_HANDLE __MIDL_itf_NeroCBUI_0293_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_NeroCBUI_0293_v0_0_s_ifspec;

#ifndef __IMfcPropertyPage_INTERFACE_DEFINED__
#define __IMfcPropertyPage_INTERFACE_DEFINED__

/* interface IMfcPropertyPage */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IMfcPropertyPage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("25398f04-eb36-4cd3-921e-af1aac1a3e61")
    IMfcPropertyPage : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AFX_OLDPROPSHEETPAGE( 
            /* [retval][out] */ LPAFX_OLDPROPSHEETPAGE __RPC_FAR *ppPSP) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMfcPropertyPageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMfcPropertyPage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMfcPropertyPage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMfcPropertyPage __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AFX_OLDPROPSHEETPAGE )( 
            IMfcPropertyPage __RPC_FAR * This,
            /* [retval][out] */ LPAFX_OLDPROPSHEETPAGE __RPC_FAR *ppPSP);
        
        END_INTERFACE
    } IMfcPropertyPageVtbl;

    interface IMfcPropertyPage
    {
        CONST_VTBL struct IMfcPropertyPageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMfcPropertyPage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMfcPropertyPage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMfcPropertyPage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMfcPropertyPage_get_AFX_OLDPROPSHEETPAGE(This,ppPSP)	\
    (This)->lpVtbl -> get_AFX_OLDPROPSHEETPAGE(This,ppPSP)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IMfcPropertyPage_get_AFX_OLDPROPSHEETPAGE_Proxy( 
    IMfcPropertyPage __RPC_FAR * This,
    /* [retval][out] */ LPAFX_OLDPROPSHEETPAGE __RPC_FAR *ppPSP);


void __RPC_STUB IMfcPropertyPage_get_AFX_OLDPROPSHEETPAGE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMfcPropertyPage_INTERFACE_DEFINED__ */


#ifndef __IPrivateDeviceInfos_INTERFACE_DEFINED__
#define __IPrivateDeviceInfos_INTERFACE_DEFINED__

/* interface IPrivateDeviceInfos */
/* [hidden][unique][uuid][object] */ 


EXTERN_C const IID IID_IPrivateDeviceInfos;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a8a66560-7a62-444d-b5e3-629dd8865c80")
    IPrivateDeviceInfos : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Private_NewDeviceInfos( 
            /* [in] */ LPNERO_SCSI_DEVICE_INFOS pDeviceInfos) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Private_DeviceInfoInUseChange( 
            /* [in] */ LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ BOOL bInUse) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Private_DeviceInfoDiscChange( 
            /* [in] */ LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ BOOL bInserted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Private_DisplayWaitCursor( 
            /* [in] */ BOOL bDisplayIt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPrivateDeviceInfosVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPrivateDeviceInfos __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPrivateDeviceInfos __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPrivateDeviceInfos __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Private_NewDeviceInfos )( 
            IPrivateDeviceInfos __RPC_FAR * This,
            /* [in] */ LPNERO_SCSI_DEVICE_INFOS pDeviceInfos);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Private_DeviceInfoInUseChange )( 
            IPrivateDeviceInfos __RPC_FAR * This,
            /* [in] */ LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ BOOL bInUse);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Private_DeviceInfoDiscChange )( 
            IPrivateDeviceInfos __RPC_FAR * This,
            /* [in] */ LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
            /* [in] */ BOOL bInserted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Private_DisplayWaitCursor )( 
            IPrivateDeviceInfos __RPC_FAR * This,
            /* [in] */ BOOL bDisplayIt);
        
        END_INTERFACE
    } IPrivateDeviceInfosVtbl;

    interface IPrivateDeviceInfos
    {
        CONST_VTBL struct IPrivateDeviceInfosVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrivateDeviceInfos_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPrivateDeviceInfos_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPrivateDeviceInfos_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPrivateDeviceInfos_Private_NewDeviceInfos(This,pDeviceInfos)	\
    (This)->lpVtbl -> Private_NewDeviceInfos(This,pDeviceInfos)

#define IPrivateDeviceInfos_Private_DeviceInfoInUseChange(This,pDeviceInfo,bInUse)	\
    (This)->lpVtbl -> Private_DeviceInfoInUseChange(This,pDeviceInfo,bInUse)

#define IPrivateDeviceInfos_Private_DeviceInfoDiscChange(This,pDeviceInfo,bInserted)	\
    (This)->lpVtbl -> Private_DeviceInfoDiscChange(This,pDeviceInfo,bInserted)

#define IPrivateDeviceInfos_Private_DisplayWaitCursor(This,bDisplayIt)	\
    (This)->lpVtbl -> Private_DisplayWaitCursor(This,bDisplayIt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPrivateDeviceInfos_Private_NewDeviceInfos_Proxy( 
    IPrivateDeviceInfos __RPC_FAR * This,
    /* [in] */ LPNERO_SCSI_DEVICE_INFOS pDeviceInfos);


void __RPC_STUB IPrivateDeviceInfos_Private_NewDeviceInfos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPrivateDeviceInfos_Private_DeviceInfoInUseChange_Proxy( 
    IPrivateDeviceInfos __RPC_FAR * This,
    /* [in] */ LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
    /* [in] */ BOOL bInUse);


void __RPC_STUB IPrivateDeviceInfos_Private_DeviceInfoInUseChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPrivateDeviceInfos_Private_DeviceInfoDiscChange_Proxy( 
    IPrivateDeviceInfos __RPC_FAR * This,
    /* [in] */ LPNERO_SCSI_DEVICE_INFO pDeviceInfo,
    /* [in] */ BOOL bInserted);


void __RPC_STUB IPrivateDeviceInfos_Private_DeviceInfoDiscChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPrivateDeviceInfos_Private_DisplayWaitCursor_Proxy( 
    IPrivateDeviceInfos __RPC_FAR * This,
    /* [in] */ BOOL bDisplayIt);


void __RPC_STUB IPrivateDeviceInfos_Private_DisplayWaitCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPrivateDeviceInfos_INTERFACE_DEFINED__ */


#ifndef __IPrivateImageInfoDlg_INTERFACE_DEFINED__
#define __IPrivateImageInfoDlg_INTERFACE_DEFINED__

/* interface IPrivateImageInfoDlg */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IPrivateImageInfoDlg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("671fd79b-c0af-4bb3-9738-e229871732f9")
    IPrivateImageInfoDlg : public IUnknown
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Private_ImageFilename( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPrivateImageInfoDlgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPrivateImageInfoDlg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPrivateImageInfoDlg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPrivateImageInfoDlg __RPC_FAR * This);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Private_ImageFilename )( 
            IPrivateImageInfoDlg __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename);
        
        END_INTERFACE
    } IPrivateImageInfoDlgVtbl;

    interface IPrivateImageInfoDlg
    {
        CONST_VTBL struct IPrivateImageInfoDlgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrivateImageInfoDlg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPrivateImageInfoDlg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPrivateImageInfoDlg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPrivateImageInfoDlg_get_Private_ImageFilename(This,pbstrFilename)	\
    (This)->lpVtbl -> get_Private_ImageFilename(This,pbstrFilename)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IPrivateImageInfoDlg_get_Private_ImageFilename_Proxy( 
    IPrivateImageInfoDlg __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename);


void __RPC_STUB IPrivateImageInfoDlg_get_Private_ImageFilename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPrivateImageInfoDlg_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
