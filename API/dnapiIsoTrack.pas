{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ Portions created by Alexandre Rocha Lima e Marcondes are Copyright (C) 2003  }
{ Alexandre Rocha Lima e Marcondes . All Rights Reserved.                      }
{                                                                              }
{ Obtained through: Project Nero API for Delphi                                }
{                                                                              }
{ You may retrieve the latest version of this file at the Nero API for Delphi  }
{ home page, located at http://www.sourceforge.net/projects/delphineroapi      }
{                                                                              }
{ The contents of this file are used with permission, subject to the Mozilla   }
{ Public License Version 1.1 (the "License"); you may not use this file except }
{ in compliance with the License. You may obtain a copy of the License at      }
{ http://www.mozilla.org/MPL/MPL-1.1.html                                      }
{                                                                              }
{ Software distributed under the License is distributed on an "AS IS" basis,   }
{ WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for }
{ the specific language governing rights and limitations under the License.    }
{                                                                              }
{******************************************************************************}

{******************************************************************************
|* History
|*
|* CREATOR: Alexandre Rocha Lima e Marcondes
|*
******************************************************************************}

{******************************************************************************
|* NeroSDK / NeroAPI
|*
|* PURPOSE: Refactory IsoTrack structures and classes
******************************************************************************}
unit dnapiIsoTrack;

interface

uses
  Classes, SysUtils, NeroAPI, NeroIsoTrack;

type
  TdnapiIsoTrackItemList = class;

  TdnapiIsoTrackItem = class
  private
    FNeroIsoItem: PNeroIsoItem;
    FSubDirItems: TdnapiIsoTrackItemList;
    function GetFileName: String;
    function GetIsDirectory: Boolean;
    function GetIsReference: Boolean;
    function GetSourceFilePath: String;
    procedure SetIsDirectory(const Value: Boolean);
    procedure SetIsReference(const Value: Boolean);
    function GetUserData: Pointer;
    procedure SetUserData(const Value: Pointer);
    function GetImportInfo: CImportInfo;
    function GetEntryTime: TDateTime;
    procedure SetEntryTime(const Value: TDateTime);
    function GetNextItem: PNeroIsoItem;
    procedure SetFileName(const Value: String);
    procedure SetNextItem(const Value: PNeroIsoItem);
    procedure SetSubDirItems(const Value: TdnapiIsoTrackItemList);
  protected
    property SubDirItems: TdnapiIsoTrackItemList read FSubDirItems write SetSubDirItems;
    property NextItem: PNeroIsoItem read GetNextItem write SetNextItem;
    property UserData: Pointer read GetUserData write SetUserData default nil;
    property ImportInfo: CImportInfo read GetImportInfo;
  public
    constructor Create; overload;
    constructor Create(NeroIsoItem: PNeroIsoItem); overload;
    constructor Create(SourceFileName: String; ISOFileName: String = ''); overload;
    destructor Destroy; override;

    function Clone: TdnapiIsoTrackItem;
    function SetFile(SourceFileName: String; ISOFileName: String = ''): Boolean;

    property NeroIsoItem: PNeroIsoItem read FNeroIsoItem;
    property IsDirectory: Boolean read GetIsDirectory write SetIsDirectory default False;
    property IsReference: Boolean read GetIsReference write SetIsReference default False;
    property FileName: String read GetFileName write SetFileName;
    property SourceFilePath: String read GetSourceFilePath;
    property EntryTime: TDateTime read GetEntryTime write SetEntryTime;
  end;

  TdnapiIsoTrackItemList = class(TList)
  private
  protected
    function Get(Index: Integer): TdnapiIsoTrackItem;
    procedure Put(Index: Integer; Item: TdnapiIsoTrackItem);
    property List;
    function Last: TdnapiIsoTrackItem;
  public
    destructor Destroy; override;
    function Add(Item: TdnapiIsoTrackItem): Integer; overload;
    function Add(SourceFileName: String; ISOFileName: String = ''): Integer; overload;
    procedure Assign(ListA: TdnapiIsoTrackItemList; AOperator: TListAssignOp = laCopy; ListB: TdnapiIsoTrackItemList = nil);
    procedure Clear; override;
    procedure Exchange(Index1, Index2: Integer);
    function Expand: TdnapiIsoTrackItemList;
    function Extract(Item: TdnapiIsoTrackItem): TdnapiIsoTrackItem;
    function First: TdnapiIsoTrackItem;
    function IndexOf(Item: TdnapiIsoTrackItem): Integer;
    procedure Insert(Index: Integer; Item: TdnapiIsoTrackItem);
    procedure Move(CurIndex, NewIndex: Integer);
    function Remove(Item: TdnapiIsoTrackItem): Integer;
    procedure Pack;
    procedure Sort(Compare: TListSortCompare);

    property Items[Index: Integer]: TdnapiIsoTrackItem read Get write Put; default;
  end;

  TTrackType = (ttJoliet, ttMode2, ttRockRidge, ttISO_FS, ttUDF_FS, ttHFS_FS, ttDVDVideoRealloc, ttUseStruct, ttReserved1, ttUseAllSpace, ttReserved2, ttReserved3, ttReserved4);
  TTrackTypes = set of TTrackType;

  TdnapiIsoTrack = class
  private
    FNeroIsoTrack: CNeroIsoTrack;
    FIsoTrackItemList: TdnapiIsoTrackItemList;
    function GetName: String;
    function GetTrackType: TTrackTypes;
  protected
    function ConvertTrackType(Value: TTrackTypes): Cardinal;
  public
    constructor Create(RootItem: TdnapiIsoTrackItem; TrackName: String = ''; Options: TTrackTypes = [ttISO_FS, ttJoliet]); overload;
    constructor Create(ItemList: TdnapiIsoTrackItemList; TrackName: String = ''; Options: TTrackTypes = [ttISO_FS, ttJoliet]); overload;
    constructor Create(SourceFileName: String; ISOFileName: String = ''; TrackName: String= ''; Options: TTrackTypes = [ttISO_FS, ttJoliet]); overload;
    destructor Destroy; override;

    procedure GetVolumeDescriptor(var systemIdentifier, volumeSet,
      publisher, dataPreparer, application,
      copyright, _abstract, bibliographic: PChar);

    property Name: String read GetName;
    property TrackType: TTrackTypes read GetTrackType;
    property NeroIsoTrack: CNeroIsoTrack read FNeroIsoTrack;
    property IsoTrackItemList: TdnapiIsoTrackItemList read FIsoTrackItemList;
  end;

implementation

uses DateUtils;

{ TdnapiIsoTrackItem }
function TdnapiIsoTrackItem.Clone: TdnapiIsoTrackItem;
begin
  Result := TdnapiIsoTrackItem.Create(NeroCopyIsoItem(FNeroIsoItem));
end;

constructor TdnapiIsoTrackItem.Create;
begin
  inherited Create;

  FNeroIsoItem := NeroCreateIsoItem();
  SetEntryTime(Now);
  FSubDirItems := nil;
end;

constructor TdnapiIsoTrackItem.Create(NeroIsoItem: PNeroIsoItem);
begin
  inherited Create;

  FNeroIsoItem := NeroIsoItem;
  SetEntryTime(Now);
  FSubDirItems := nil;
end;

constructor TdnapiIsoTrackItem.Create(SourceFileName, ISOFileName: String);
begin
  inherited Create;

  FNeroIsoItem := NeroCreateIsoItem();
  FSubDirItems := nil;
  SetFile(SourceFileName, ISOFileName);
end;

destructor TdnapiIsoTrackItem.Destroy;
begin
  FreeAndNil(FSubDirItems);

  NeroFreeIsoItem(FNeroIsoItem);

  inherited;
end;


function TdnapiIsoTrackItem.GetFileName: String;
begin
  Result := FNeroIsoItem.fileName;
end;

function TdnapiIsoTrackItem.GetIsDirectory: Boolean;
begin
  Result := FNeroIsoItem.isDirectory;
end;

function TdnapiIsoTrackItem.GetIsReference: Boolean;
begin
  Result := FNeroIsoItem.isReference;
end;

function TdnapiIsoTrackItem.GetSourceFilePath: String;
begin
  Result := FNeroIsoItem.sourceFilePath;
end;

procedure TdnapiIsoTrackItem.SetIsDirectory(const Value: Boolean);
begin
  FNeroIsoItem.isDirectory := Value;
end;

procedure TdnapiIsoTrackItem.SetIsReference(const Value: Boolean);
begin
  FNeroIsoItem.isReference := Value;
end;

function TdnapiIsoTrackItem.GetUserData: Pointer;
begin
  Result := FNeroIsoItem.userData;
end;

procedure TdnapiIsoTrackItem.SetUserData(const Value: Pointer);
begin
  FNeroIsoItem.userData := Value;
end;

function TdnapiIsoTrackItem.GetImportInfo: CImportInfo;
begin
  Result := FNeroIsoItem.importinfo;
end;

function TdnapiIsoTrackItem.GetEntryTime: TDateTime;
begin
  Result := EncodeDateTime(FNeroIsoItem.entryTime.tm_year,
    FNeroIsoItem.entryTime.tm_mon, FNeroIsoItem.entryTime.tm_mday,
    FNeroIsoItem.entryTime.tm_hour, FNeroIsoItem.entryTime.tm_min,
    FNeroIsoItem.entryTime.tm_sec, 0);
end;

procedure TdnapiIsoTrackItem.SetEntryTime(const Value: TDateTime);
var
  tm_year, tm_mon, tm_mday, tm_hour, tm_min, tm_sec, tm_msec: WORD;
begin
  DecodeDateTime(Value, tm_year, tm_mon, tm_mday, tm_hour, tm_min, tm_sec, tm_msec);

  FNeroIsoItem.entryTime.tm_year := tm_year;
  FNeroIsoItem.entryTime.tm_mon := tm_mon;
  FNeroIsoItem.entryTime.tm_wday := DayOfTheWeek(Value);
  FNeroIsoItem.entryTime.tm_mday := DayOfTheMonth(Value);
  FNeroIsoItem.entryTime.tm_yday := DayOfTheYear(Value);
  FNeroIsoItem.entryTime.tm_isdst := WORD(False);
  FNeroIsoItem.entryTime.tm_hour := tm_hour;
  FNeroIsoItem.entryTime.tm_min := tm_min;
  FNeroIsoItem.entryTime.tm_sec := tm_min;
end;

function TdnapiIsoTrackItem.GetNextItem: PNeroIsoItem;
begin
  Result := FNeroIsoItem.nextItem;
end;

function TdnapiIsoTrackItem.SetFile(SourceFileName, ISOFileName: String): Boolean;
var
  sr: TSearchRec;
begin
  if DirectoryExists(SourceFileName) then
  begin
    SetIsDirectory(True);

    if FindFirst(IncludeTrailingPathDelimiter(SourceFileName) + '*.*', faAnyFile + faHidden + faArchive + faReadOnly + faSysFile + faDirectory, sr) = 0 then
    begin
      FreeAndNil(FSubDirItems);

      FSubDirItems.Create;

      repeat
        FSubDirItems.Add(TdnapiIsoTrackItem.Create(sr.Name));
      until FindNext(sr) <> 0;

      FindClose(sr);

      FNeroIsoItem.subDirFirstItem := FSubDirItems.First.FNeroIsoItem;
    end;

    SetIsDirectory(True);
    Result := True;
  end
  else
  begin
    if FileExists(SourceFileName) then
    begin
      StrPCopy(FNeroIsoItem.sourceFilePath, SourceFileName);
      FNeroIsoItem.sourceFilePath[SizeOf(FNeroIsoItem.sourceFilePath) - 1] := #00;

      if FileName = '' then
      begin
        StrPCopy(FNeroIsoItem.fileName, ExtractFileName(SourceFileName));
        FNeroIsoItem.fileName[SizeOf(FNeroIsoItem.fileName) - 1] := #00;
      end
      else
      begin
        StrPCopy(FNeroIsoItem.fileName, ISOFileName);
        FNeroIsoItem.fileName[SizeOf(FNeroIsoItem.fileName) - 1] := #00;
      end;

      SetEntryTime(FileDateToDateTime(FileAge(SourceFileName)));

      FNeroIsoItem.itemSize := SizeOf(FNeroIsoItem);

      if Assigned(FSubDirItems) then
        FreeAndNil(FSubDirItems);

      SetIsDirectory(False);
      Result := True;
    end
    else
    begin
      StrPCopy(FNeroIsoItem.sourceFilePath, '');
      FNeroIsoItem.sourceFilePath[SizeOf(FNeroIsoItem.sourceFilePath) - 1] := #00;

      StrPCopy(FNeroIsoItem.fileName, '');
      FNeroIsoItem.fileName[SizeOf(FNeroIsoItem.fileName) - 1] := #00;

      SetEntryTime(Now);

      FNeroIsoItem.itemSize := SizeOf(FNeroIsoItem);

      if Assigned(FSubDirItems) then
        FreeAndNil(FSubDirItems);

      SetIsDirectory(False);
      Result := False;
    end;
  end;
end;

procedure TdnapiIsoTrackItem.SetFileName(const Value: String);
begin
  StrPCopy(FNeroIsoItem.fileName, Value);
  FNeroIsoItem.fileName[SizeOf(FNeroIsoItem.fileName) - 1] := #00;

  FNeroIsoItem.itemSize := SizeOf(FNeroIsoItem);
end;

procedure TdnapiIsoTrackItem.SetNextItem(const Value: PNeroIsoItem);
begin
  FNeroIsoItem.nextItem := Value;
end;

procedure TdnapiIsoTrackItem.SetSubDirItems(
  const Value: TdnapiIsoTrackItemList);
begin
  if Assigned(FSubDirItems) then
    FreeAndNil(FSubDirItems);

  if GetIsDirectory then
  begin
    FSubDirItems := Value;

    FNeroIsoItem.subDirFirstItem := FSubDirItems.First.FNeroIsoItem;
  end;
end;

{ TdnapiIsoTrackItemList }

function TdnapiIsoTrackItemList.Add(Item: TdnapiIsoTrackItem): Integer;
begin
  Result := inherited Add(Item.FNeroIsoItem);

  if Result > 0 then
    Items[Result - 1].NextItem := Items[Result].FNeroIsoItem;
end;

function TdnapiIsoTrackItemList.Add(SourceFileName,
  ISOFileName: String): Integer;
begin
  Result := Add(TdnapiIsoTrackItem.Create(SourceFileName, ISOFileName));
end;

procedure TdnapiIsoTrackItemList.Assign(ListA: TdnapiIsoTrackItemList;
  AOperator: TListAssignOp; ListB: TdnapiIsoTrackItemList);
begin
  inherited Assign(ListA, AOperator, ListB);
end;

procedure TdnapiIsoTrackItemList.Clear;
var
  Counter: Integer;
begin
  Pack;
  for Counter := 0 to Count - 1 do
  begin
    Items[Counter].Free;
    Items[Counter] := nil;
  end;

  inherited Clear;
end;

destructor TdnapiIsoTrackItemList.Destroy;
begin
  Clear;

  inherited Destroy;
end;

procedure TdnapiIsoTrackItemList.Exchange(Index1, Index2: Integer);
begin
  inherited Exchange(Index1, Index2);

  if Index1 > 0 then
    Items[Index1 - 1].NextItem := Items[Index2].FNeroIsoItem;

  Items[Index1].NextItem := Items[Index2 + 1].FNeroIsoItem;

  if Index2 > 0 then
    Items[Index2 - 1].NextItem := Items[Index1].FNeroIsoItem;

  Items[Index2].NextItem := Items[Index1 + 1].FNeroIsoItem;
end;

function TdnapiIsoTrackItemList.Expand: TdnapiIsoTrackItemList;
begin
  Result := TdnapiIsoTrackItemList(inherited Expand);
end;

function TdnapiIsoTrackItemList.Extract(
  Item: TdnapiIsoTrackItem): TdnapiIsoTrackItem;
begin
  if IndexOf(Item) > 0 then
    Items[IndexOf(Item) - 1].NextItem := Item.NextItem;

  Item.NextItem := nil;

  Result := inherited Extract(Item);
end;

function TdnapiIsoTrackItemList.First: TdnapiIsoTrackItem;
begin
  Result := TdnapiIsoTrackItem.Create(inherited First);
end;

function TdnapiIsoTrackItemList.Get(Index: Integer): TdnapiIsoTrackItem;
begin
  Result := TdnapiIsoTrackItem.Create(inherited Get(Index));
end;

function TdnapiIsoTrackItemList.IndexOf(Item: TdnapiIsoTrackItem): Integer;
begin
  Result := inherited IndexOf(Item.FNeroIsoItem);
end;

procedure TdnapiIsoTrackItemList.Insert(Index: Integer;
  Item: TdnapiIsoTrackItem);
begin
  inherited Insert(Index, Item.FNeroIsoItem);

  if Index > 0 then
  begin
    Items[Index - 1].NextItem := Items[Index].FNeroIsoItem;

    if Index < Count - 1 then
      Items[Index].NextItem := Items[Index + 1].FNeroIsoItem
    else
      Items[Index].NextItem := nil;
  end;
end;

function TdnapiIsoTrackItemList.Last: TdnapiIsoTrackItem;
begin
  Result := TdnapiIsoTrackItem.Create(inherited Last);
end;

procedure TdnapiIsoTrackItemList.Move(CurIndex, NewIndex: Integer);
begin
  inherited Move(CurIndex, NewIndex);

  if CurIndex > 0 then
    Items[CurIndex - 1].NextItem := Items[CurIndex + 1].FNeroIsoItem;

  if NewIndex > 0 then
    Items[NewIndex - 1].NextItem := Items[CurIndex].FNeroIsoItem;

  if NewIndex < Count - 1 then
  begin
    Items[NewIndex].NextItem := Items[NewIndex + 1].FNeroIsoItem;
  end
  else
    Items[NewIndex].NextItem := nil;
end;

procedure TdnapiIsoTrackItemList.Pack;
var
  Counter: Integer;
begin
  inherited Pack;

  if Count > 1 then
  begin
    for Counter := 0 to Count - 2 do
      Items[Counter].NextItem := Items[Counter + 1].FNeroIsoItem;

    Items[Count - 1].NextItem := nil;
  end
  else
    Items[0].NextItem := nil;
end;

procedure TdnapiIsoTrackItemList.Put(Index: Integer;
  Item: TdnapiIsoTrackItem);
begin
  inherited Put(Index, Item.FNeroIsoItem);
end;

function TdnapiIsoTrackItemList.Remove(Item: TdnapiIsoTrackItem): Integer;
begin
  Result := inherited Remove(Item.FNeroIsoItem);

  if Result > 0 then
    Items[Result - 1].NextItem := Items[Result].FNeroIsoItem;
end;

procedure TdnapiIsoTrackItemList.Sort(Compare: TListSortCompare);
begin
  inherited Sort(Compare);

  Pack;
end;

{ TdnapiIsoTrack }

function TdnapiIsoTrack.ConvertTrackType(Value: TTrackTypes): Cardinal;
begin
  Result := 0;

  if ttJoliet in Value then
      Result := Result + NCITEF_USE_JOLIET;
  if ttMode2 in Value then
      Result := Result + NCITEF_USE_MODE2;
  if ttRockRidge in Value then
      Result := Result + NCITEF_USE_ROCKRIDGE;
  if ttDVDVideoRealloc in Value then
      Result := Result + NCITEF_DVDVIDEO_REALLOC;
  if ttUseStruct in Value then
      Result := Result + NCITEF_USE_STRUCT;
  if ttUseAllSpace in Value then
      Result := Result + NCITEF_USE_ALLSPACE;
  if ttISO_FS in Value then
      Result := Result + NCITEF_CREATE_ISO_FS;
  if ttUDF_FS in Value then
      Result := Result + NCITEF_CREATE_UDF_FS;
  if ttHFS_FS in Value then
      Result := Result + NCITEF_CREATE_HFS_FS;
  if ttReserved1 in Value then
      Result := Result + NCITEF_RESERVED1;
  if ttReserved2 in Value then
      Result := Result + NCITEF_RESERVED2;
  if ttReserved3 in Value then
      Result := Result + NCITEF_RESERVED3;
  if ttReserved4 in Value then
      Result := Result + NCITEF_RESERVED4;
end;

constructor TdnapiIsoTrack.Create(ItemList: TdnapiIsoTrackItemList; TrackName: String; Options: TTrackTypes);
begin
  inherited Create;

  FIsoTrackItemList := ItemList;

  FNeroIsoTrack := NeroCreateIsoTrackEx(FIsoTrackItemList.First.FNeroIsoItem, PAnsiChar(TrackName), ConvertTrackType(Options));
end;

constructor TdnapiIsoTrack.Create(SourceFileName, ISOFileName: String; TrackName: String; Options: TTrackTypes);
begin
  inherited Create;

  FIsoTrackItemList := TdnapiIsoTrackItemList.Create;
  FIsoTrackItemList.Add(SourceFileName, ISOFileName);

  FNeroIsoTrack := NeroCreateIsoTrackEx(FIsoTrackItemList.First.FNeroIsoItem, PAnsiChar(TrackName), ConvertTrackType(Options));
end;

constructor TdnapiIsoTrack.Create(RootItem: TdnapiIsoTrackItem; TrackName: String; Options: TTrackTypes);
begin
  inherited Create;

  FIsoTrackItemList := TdnapiIsoTrackItemList.Create;
  FIsoTrackItemList.Add(RootItem);

  FNeroIsoTrack := NeroCreateIsoTrackEx(FIsoTrackItemList.First.FNeroIsoItem, PAnsiChar(TrackName), ConvertTrackType(Options));
end;

destructor TdnapiIsoTrack.Destroy;
begin
  NeroFreeIsoTrack(FNeroIsoTrack);
  FreeAndNil(FIsoTrackItemList);

  inherited;
end;

function TdnapiIsoTrack.GetName: String;
begin
  Result := FNeroIsoTrack.GetName;
end;

function TdnapiIsoTrack.GetTrackType: TTrackTypes;
begin
  Result := [];

  if FNeroIsoTrack.BurnOptions = NCITEF_USE_JOLIET then
      Result := Result + [ttJoliet];
  if FNeroIsoTrack.BurnOptions = NCITEF_USE_MODE2 then
      Result := Result + [ttMode2];
  if FNeroIsoTrack.BurnOptions = NCITEF_USE_ROCKRIDGE then
      Result := Result + [ttRockRidge];
  if FNeroIsoTrack.BurnOptions = NCITEF_DVDVIDEO_REALLOC then
      Result := Result + [ttDVDVideoRealloc];
  if FNeroIsoTrack.BurnOptions = NCITEF_USE_STRUCT then
      Result := Result + [ttUseStruct];
  if FNeroIsoTrack.BurnOptions = NCITEF_USE_ALLSPACE then
      Result := Result + [ttUseAllSpace];
  if FNeroIsoTrack.BurnOptions = NCITEF_CREATE_ISO_FS then
      Result := Result + [ttISO_FS];
  if FNeroIsoTrack.BurnOptions = NCITEF_CREATE_UDF_FS then
      Result := Result + [ttUDF_FS];
  if FNeroIsoTrack.BurnOptions = NCITEF_CREATE_HFS_FS then
      Result := Result + [ttHFS_FS];
  if FNeroIsoTrack.BurnOptions = NCITEF_RESERVED1 then
      Result := Result + [ttReserved1];
  if FNeroIsoTrack.BurnOptions = NCITEF_RESERVED2 then
      Result := Result + [ttReserved2];
  if FNeroIsoTrack.BurnOptions = NCITEF_RESERVED3 then
      Result := Result + [ttReserved3];
  if FNeroIsoTrack.BurnOptions = NCITEF_RESERVED4 then
      Result := Result + [ttReserved4];
end;

procedure TdnapiIsoTrack.GetVolumeDescriptor(var systemIdentifier,
  volumeSet, publisher, dataPreparer, application, copyright, _abstract,
  bibliographic: PChar);
begin
  FNeroIsoTrack.GetVolumeDescriptor(systemIdentifier, volumeSet, publisher, dataPreparer, application, copyright, _abstract, bibliographic);
end;

end.
