unit NEROAPIGLUE;

interface
uses NeroAPI,
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}


{$IFNDEF __NEROAPIGLUE__}
{$DEFINE __NEROAPIGLUE__}

{$IFDEF __cplusplus}
{$ENDIF}

{$DEFINE USING_NEROSDK}

{+// }
{/// This function has to be called first. }
{= }

var
  NeroAPIGlueConnect: function(reserved: Pointer): Bool cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 

{+// }
{/// This one cleans up after using the glue code. }
{= }
var
  NeroAPIGlueDone: procedure cdecl  {$IFDEF WIN32} stdcall {$ENDIF}; 


{$IFDEF __cplusplus}
{$ENDIF}


{$ENDIF /* __NEROAPIGLUE__*/}



var
  DLLLoaded: Boolean { is DLL (dynamically) loaded already? }
    {$IFDEF WIN32} = False; {$ENDIF}

implementation

var
  SaveExit: pointer;
  DLLHandle: THandle;
{$IFNDEF MSDOS}
  ErrorMode: Integer;
{$ENDIF}

  procedure NewExit; far;
  begin
    ExitProc := SaveExit;
    FreeLibrary(DLLHandle)
  end {NewExit};

procedure LoadDLL;
begin
  if DLLLoaded then Exit;
{$IFNDEF MSDOS}
  ErrorMode := SetErrorMode($8000{SEM_NoOpenFileErrorBox});
{$ENDIF}
  DLLHandle := LoadLibrary('NEROAPIGLUE.DLL');
  if DLLHandle >= 32 then
  begin
    DLLLoaded := True;
    SaveExit := ExitProc;
    ExitProc := @NewExit;
    @NeroAPIGlueConnect := GetProcAddress(DLLHandle,'NeroAPIGlueConnect');
  {$IFDEF WIN32}
    Assert(@NeroAPIGlueConnect <> nil);
  {$ENDIF}
    @NeroAPIGlueDone := GetProcAddress(DLLHandle,'NeroAPIGlueDone');
  {$IFDEF WIN32}
    Assert(@NeroAPIGlueDone <> nil);
  {$ENDIF}
  end
  else
  begin
    DLLLoaded := False;
    { Error: NEROAPIGLUE.DLL could not be loaded !! }
  end;
{$IFNDEF MSDOS}
  SetErrorMode(ErrorMode)
{$ENDIF}
end {LoadDLL};

begin
  LoadDLL;
end.
