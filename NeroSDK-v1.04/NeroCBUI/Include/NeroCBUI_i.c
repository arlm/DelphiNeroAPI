/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 13 09:09:00 2004
 */
/* Compiler settings for S:\NeroSDK\Sources\NeroCBUI\Src\NeroCBUI.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_NEROCBUILib = {0xb3267063,0x8ab4,0x464d,{0xa1,0x3c,0x15,0x17,0xbd,0x6d,0xc6,0xf4}};


const CLSID CLSID_InitSettings = {0x9871f8af,0x152a,0x4651,{0x83,0x4c,0xcd,0xc5,0xfe,0x61,0xc1,0x4c}};


const CLSID CLSID_BurnSettings = {0xec39bf14,0xca12,0x46cd,{0x8e,0xa2,0xb4,0x8d,0x5a,0x44,0x35,0x0a}};


const CLSID CLSID_RecorderCombobox = {0xf495ebbe,0xa068,0x41fb,{0x89,0xb6,0xc6,0x05,0xd2,0x0a,0x2d,0xf3}};


const CLSID CLSID_BurnSettingsDlg = {0xe6028af3,0xee0a,0x4e49,{0xa0,0x43,0xc4,0x44,0x37,0x68,0x0a,0xd8}};


const CLSID CLSID_BurnSettingsDlgParam = {0x0b1511cd,0x37ee,0x4f0a,{0x96,0x47,0xcb,0x27,0x85,0xb6,0x8a,0x29}};


const CLSID CLSID_BurnProgressDlg = {0xa861a366,0x0c7a,0x484b,{0x91,0x16,0xf3,0x66,0xbf,0x0f,0xa2,0x3f}};


const CLSID CLSID_ChooseRecorderDlg = {0x0edcdb7d,0xcd9e,0x44e6,{0x9e,0x9a,0xad,0xba,0xa8,0x55,0x40,0xe8}};


const CLSID CLSID_EraseSettingsDlg = {0x1c613f47,0x70c5,0x4551,{0xa2,0x64,0xf7,0x25,0x41,0x39,0x85,0x4c}};


const CLSID CLSID_EraseDiscDlg = {0x7b9717b1,0x2d9b,0x4d14,{0xb2,0xda,0xd4,0xbf,0x5a,0x28,0xc6,0xaf}};


const CLSID CLSID_DiscInfoDlg = {0xf1f2ece6,0x0289,0x4992,{0xa5,0x36,0xf8,0x2d,0xfc,0x6f,0x6d,0x6e}};


const CLSID CLSID_ImageInfoDlg = {0x940f79d9,0x2062,0x41b7,{0xa2,0x2f,0x9e,0x99,0xff,0xdd,0x1b,0x85}};


const CLSID CLSID_ImageInfoDlgParam = {0x712a2867,0x02b2,0x402b,{0x8f,0x8d,0x74,0x43,0x74,0x94,0xdc,0xfb}};


const CLSID CLSID_ChooseSessionDlg = {0xe5b2709a,0x0e6b,0x45d3,{0x83,0xc8,0xef,0x90,0xc2,0xed,0x53,0x40}};


const CLSID CLSID_SpeedCombobox = {0x612fbd09,0xaad2,0x4f1c,{0xba,0x97,0xf5,0x66,0x58,0xb1,0x16,0x1b}};


const CLSID CLSID_WaitForMediaDlg = {0x9e42f1b8,0xde23,0x4af5,{0xa7,0x9a,0x09,0x76,0xe9,0xec,0x57,0x81}};


const CLSID CLSID_UserDlgHandler = {0xbc91ed21,0xe702,0x44e5,{0xaa,0x88,0x9f,0x2f,0x70,0xe9,0x86,0xc6}};


const IID IID_IModelessDialog = {0x98654976,0x9086,0x4817,{0x84,0x1c,0xb7,0x5b,0x0a,0xc0,0xaa,0xa6}};


const IID IID_INERO_SCSI_DEVICE_INFO = {0x8268ed13,0x82f5,0x4dcc,{0xbb,0x13,0x95,0xb5,0xc7,0xa6,0x45,0x90}};


const IID IID_IRecorderComboboxCallbacks = {0x3bd2799a,0xb364,0x405a,{0xa6,0x3b,0x10,0x4d,0x7f,0xbf,0xeb,0x8a}};


const IID IID_IRecorderCombobox = {0xc76f66ef,0xb4d7,0x496b,{0x9a,0xb7,0x40,0x9a,0x96,0x5d,0x9c,0x43}};


const IID IID_IRecorderCombobox2 = {0xde6f71ce,0x1faf,0x405c,{0x8e,0x8e,0x0a,0x32,0xdc,0x02,0x3b,0x59}};


const IID IID_IRecorderCombobox3 = {0x40a779dc,0x9ddc,0x4d02,{0xbf,0x07,0x71,0x7f,0x41,0x9c,0x00,0xaa}};


const IID IID_IBurnSettings = {0x29c0c344,0x4c3c,0x4d4c,{0xbd,0x49,0x62,0x2c,0xcf,0xbd,0x2c,0x2e}};


const IID IID_IBurnSettingsDlg = {0x0e17506d,0xef14,0x4f3f,{0x92,0xbc,0xd3,0xae,0x07,0x39,0xd0,0x79}};


const IID IID_IBurnCallbacks = {0x01e72686,0x14ec,0x4a44,{0xbe,0x83,0x6c,0x1c,0xf9,0xbf,0xa2,0xc0}};


const IID IID_IBurnProgressDlgCallbacks = {0xee2ae31b,0xc11d,0x40ea,{0xa7,0x5b,0x88,0x48,0x37,0x32,0x83,0x87}};


const IID IID_IBurnProgressDlg = {0xf9da148d,0x0052,0x4b6f,{0xbb,0x4f,0xc3,0x5e,0x1f,0xd4,0xc5,0xa3}};


const IID IID_IBurnProgressDlg2 = {0x2053e9d5,0x8460,0x4e52,{0xab,0xa2,0x83,0x22,0x02,0x62,0x43,0x65}};


const IID IID_IExternalChildWindow = {0xfda257a8,0x46ca,0x452e,{0x9f,0x3c,0x05,0x79,0x8d,0x33,0x82,0xc0}};


const IID IID_IBurnProgressDlg3 = {0x4aa37a65,0x74c2,0x4da1,{0xb9,0x8b,0x38,0x03,0xc6,0xb9,0xc5,0x92}};


const IID IID_IBurnProgressDlgEx = {0x3ef6e092,0xcb60,0x4edb,{0xba,0xd2,0xdb,0xcf,0x09,0x7c,0x45,0x2a}};


const IID IID_IModalDialog = {0xd0509114,0x6204,0x41f6,{0xa6,0xda,0x8f,0xd3,0x2e,0xab,0xc8,0x2f}};


const IID IID_INEROAPI_CDRW_ERASE_MODE = {0x30603428,0xc6bb,0x45c1,{0x8b,0x35,0xa0,0x2c,0xda,0x5c,0x70,0x86}};


const IID IID_IEraseDiscDlg = {0x9a45a9f6,0xfe69,0x4fe8,{0x98,0x62,0x75,0x16,0x93,0xdc,0x87,0xdf}};


const IID IID_IEraseDiscDlg2 = {0xb28dc5d4,0x9593,0x4179,{0xaa,0xaa,0xdf,0x3c,0x8f,0x28,0xdb,0x72}};


const IID IID_IEraseDiscCallbacks = {0x62b3f282,0xad7a,0x42f7,{0xbd,0xb1,0xb2,0x77,0x72,0xbd,0xb6,0x1d}};


const IID IID_IEraseDiscDlg3 = {0x79b3261b,0xb57f,0x493e,{0xa7,0xbd,0x33,0x25,0xb5,0xf5,0x83,0x50}};


const IID IID_IEraseDiscDlg4 = {0xd658288d,0x1d49,0x4eb9,{0x86,0x9e,0x10,0xe5,0xdd,0xd4,0x0d,0x16}};


const IID IID_IEraseSettingsDlg = {0xcd72cad8,0xd41a,0x40b2,{0x99,0x43,0x01,0xf3,0x0b,0x15,0x07,0xcc}};


const IID IID_IEraseSettingsDlg2 = {0x0040D3ED,0x84A2,0x4e56,{0x95,0x39,0x64,0x6B,0xDC,0x57,0xDE,0x4A}};


const IID IID_IInitSettings = {0x0f5ebcfd,0x2d94,0x4896,{0x81,0x69,0x08,0x88,0x70,0xdf,0xdb,0xaf}};


const IID IID_IInitSettings2 = {0x4baf9833,0x70bb,0x4523,{0x83,0x49,0x52,0x09,0xb5,0x64,0x45,0x87}};


const IID IID_IInitSettings3 = {0x9964816b,0xdf5f,0x44aa,{0x9b,0x87,0xf0,0xde,0x3f,0x4c,0x57,0xfc}};


const IID IID_IInformation = {0x5db904aa,0x9c92,0x494e,{0x89,0x7c,0x5a,0xaa,0x53,0x37,0xcf,0x2d}};


const IID IID_IChildWindow = {0xf714bdc1,0xaec8,0x41de,{0x83,0xd2,0xdb,0x9c,0x94,0x37,0xfd,0xb2}};


const IID IID_IImageInfoDlg = {0x2302b658,0xde28,0x4233,{0x96,0xbd,0x3b,0xb5,0xfb,0x7b,0x74,0x7e}};


const IID IID_IChooseSessionDlg = {0x35e68486,0x0c10,0x41c5,{0xa5,0x2a,0x55,0xd8,0xc0,0xba,0x61,0xf2}};


const IID IID_ISpeedComboboxCallbacks = {0xefbe7cff,0x6878,0x4dce,{0xb4,0x0d,0xe2,0x1c,0x5d,0x76,0x98,0xb6}};


const IID IID_ISpeedCombobox = {0x4855a95f,0x969f,0x49cd,{0x8f,0x5a,0xca,0x04,0xe2,0xaa,0x7a,0x62}};


const IID IID_ISpeedCombobox2 = {0x6c373d24,0x7575,0x4507,{0x97,0x2c,0x18,0x14,0x91,0x45,0x70,0xc9}};


const IID IID_IWaitForMediaDlg = {0xed8b6cb0,0x5ab6,0x4db4,{0x9d,0x61,0x5d,0xcf,0x28,0xf7,0x3d,0x05}};


const IID IID_IUserDlgHandler = {0x911fb1f9,0x6576,0x4947,{0xbf,0x24,0x47,0x6b,0xab,0xe7,0x80,0x16}};


const IID IID_IMfcPropertyPage = {0x25398f04,0xeb36,0x4cd3,{0x92,0x1e,0xaf,0x1a,0xac,0x1a,0x3e,0x61}};


const IID IID_IPrivateDeviceInfos = {0xa8a66560,0x7a62,0x444d,{0xb5,0xe3,0x62,0x9d,0xd8,0x86,0x5c,0x80}};


const IID IID_IPrivateImageInfoDlg = {0x671fd79b,0xc0af,0x4bb3,{0x97,0x38,0xe2,0x29,0x87,0x17,0x32,0xf9}};


#ifdef __cplusplus
}
#endif

