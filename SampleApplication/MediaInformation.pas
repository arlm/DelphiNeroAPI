{******************************************************************************}
{                                                                              }
{ Nero API interface Unit for Object Pascal                                    }
{                                                                              }
{ Portions created by Ahead are Copyright (C) 1995-2003 Ahead Software AG.     }
{ All Rights Reserved.                                                         }
{                                                                              }
{ The original file is: NeroAPI.h/NeroAPIGlue.h, released March 2003. The      }
{ original Pascal code is: NeroAPI.pas, released June 2003. The initial        }
{ developer of the Pascal code is Andreas Hausladen (ahuser@sourceforge.net).  }
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
******************************************************************************}

{******************************************************************************
|* DelphiNeroAPI
|*
|* PURPOSE: Media Information
******************************************************************************}
unit MediaInformation;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, Menus, NeroAPI, ImgList;

type
  TFMediaInfo = class(TForm)
    stMedia: TStaticText;
    lbFreeBlocks: TLabel;
    lbTracks: TLabel;
    lbTrackList: TLabel;
    lbArtist: TLabel;
    lbTitle: TLabel;
    btnClose: TButton;
    tvTracks: TTreeView;
    pbProgress: TProgressBar;
    btnCancel: TButton;
    pmTracks: TPopupMenu;
    miExtractTracktoFile: TMenuItem;
    ilTracks: TImageList;
    sdWAV: TSaveDialog;
    procedure FormShow(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure tvTracksContextPopup(Sender: TObject; MousePos: TPoint;
      var Handled: Boolean);
    procedure miExtractTracktoFileClick(Sender: TObject);
    procedure tvTracksCollapsing(Sender: TObject; Node: TTreeNode;
      var AllowCollapse: Boolean);
    procedure tvTracksExpanded(Sender: TObject; Node: TTreeNode);
  private
    { Private declarations }
  protected
  public
  end;

  function TrackReadProgressCallback(pUserData: Pointer;
    dwProgressInPercent: DWORD): BOOL;

var
  FMediaInfo: TFMediaInfo;

implementation

uses MainForm, StrUtils;

{$R *.dfm}

procedure TFMediaInfo.FormShow(Sender: TObject);
var
  TrackCount: Integer;
  Session, Node: TTreeNode;
begin
  if Assigned(FMainForm.dnapiDevices.SelectedDeviceHandle) then
  begin
    if Assigned(FMainForm.NeroCDInfo) then
    begin
      case(FMainForm.NeroCDInfo.ncdiMediumType) of
        NMT_CD_RECORDABLE: stMedia.Caption := 'Recordable media ';
        NMT_CD_REWRITEABLE: stMedia.Caption := 'Rewriteable media ';
        NMT_CD_ROM: stMedia.Caption := 'Read-only media ';
        NMT_UNKNOWN: stMedia.Caption := 'Unknown media type ';
      end;
      stMedia.Caption := stMedia.Caption + '(' + NeroGetTypeNameOfMedia(NERO_MEDIA_SET(FMainForm.NeroCDInfo.ncdiMediaType)) + ')';

      lbFreeBlocks.Caption := IntToStr(FMainForm.NeroCDInfo.ncdiFreeCapacityInBlocks) + ' Free Blocks (' + FloatToStrF(FMainForm.NeroCDInfo.ncdiFreeCapacityInBlocks * 2352 / 1024 / 1024, ffGeneral, 3, 3) + ' MB)';
      lbFreeBlocks.Visible := FMainForm.NeroCDInfo.ncdiIsWriteable;

      lbArtist.Caption := 'Artist : ' + FMainForm.NeroCDInfo.ncdiArtist;
      lbArtist.Visible := (FMainForm.NeroCDInfo.ncdiArtist <> '');
      lbTitle.Caption := 'Album Title : ' + FMainForm.NeroCDInfo.ncdiTitle;
      lbTitle.Visible := (FMainForm.NeroCDInfo.ncdiTitle <> '');

      if FMainForm.NeroCDInfo.ncdiNumTracks > 1 then
        lbTracks.Caption := IntToStr(FMainForm.NeroCDInfo.ncdiNumTracks) + ' Tracks'
      else
        lbTracks.Caption := IntToStr(FMainForm.NeroCDInfo.ncdiNumTracks) + ' Track';

      lbTracks.Visible := (FMainForm.NeroCDInfo.ncdiNumTracks > 0);

      lbTrackList.Visible := lbTracks.Visible;
      tvTracks.Visible := lbTracks.Visible;

      Session := nil;
      tvTracks.Items.Clear;
      for TrackCount := 0 to FMainForm.NeroCDInfo.ncdiNumTracks - 1 do
      begin
        if (not Assigned(Session)) or (Session.Text <> 'Session #' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiSessionNumber)) then
          Session := tvTracks.items.AddChild(nil, 'Session #' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiSessionNumber));

        Node := tvTracks.Items.AddChild(Session, 'Track #' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackNumber));

        case (FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackType) of
          NTT_DATA:
          begin
            Node.Text := Node.Text + ' [Data Track]';
            Node.ImageIndex := 3;
          end;
          NTT_AUDIO:
          begin
            Node.Text := Node.Text + ' [Audio Track]';
            Node.ImageIndex := 4;
          end;
          NTT_UNKNOWN:
          begin
            Node.Text := Node.Text + ' [Unknown Track]';
            Node.ImageIndex := 5;
          end;
        end;

        Node.Text := Node.Text + ' (start block : ' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackStartBlk) +
          ' end block : '  + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackLengthInBlks + FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackStartBlk) +
          ' [' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackLengthInBlks) + '] = ' + FloatToStrF(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackLengthInBlks * 2352 / 1024 / 1024 , ffGeneral, 3, 3) +  ' MB)';

        if FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiISRC <> '' then
          Node.Text := Node.Text + ' ISRC : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiISRC;
        if FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiArtist <> '' then
          Node.Text := Node.Text + ' Artist : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiArtist;
        if FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTitle <> '' then
          Node.Text := Node.Text + ' Title : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTitle;
      end;
      btnCancel.Tag := 0;
      pbProgress.Visible := False;
      btnCancel.Visible := False;
    end;
  end;
end;

procedure TFMediaInfo.btnCloseClick(Sender: TObject);
begin
  Close;
end;

procedure TFMediaInfo.btnCancelClick(Sender: TObject);
begin
  btnCancel.Tag  := 666;
end;

function TrackReadProgressCallback(pUserData: Pointer;
  dwProgressInPercent: DWORD): BOOL;
begin
	FMediaInfo.Caption := 'Track extraction in progress (' + FormatFloat('000 ', dwProgressInPercent) + '%)';
  FMediaInfo.pbProgress.StepBy(dwProgressInPercent);
  Application.ProcessMessages;

	Result := (FMediaInfo.btnCancel.Tag = 666);
end;

procedure TFMediaInfo.tvTracksContextPopup(Sender: TObject;
  MousePos: TPoint; var Handled: Boolean);
begin
  miExtractTracktoFile.Enabled := (LeftStr(tvTracks.GetNodeAt(MousePos.X, MousePos.Y).Text, 7) <> 'session');
end;

procedure TFMediaInfo.miExtractTracktoFileClick(Sender: TObject);
var
  NeroCallBack: PNeroCallBack;
  Exchange: PNeroDataExchange;
  Track: Integer;
  Buffer: String;
begin
  if tvTracks.Selected.ImageIndex = 4 then
  begin
    NeroCallBack := AllocMem(SizeOf(TNeroCallBack));
    NeroCallback.ncCallbackFunction := @TrackReadProgressCallback;
    NeroCallBack.ncUserData := FMainForm.dnapiSettings.NeroSettings;

    Buffer := LeftStr(tvTracks.Selected.Text, 9);
    Buffer := RightStr(Buffer, Length(Buffer) - LastDelimiter('#', Buffer));
    Track := Cardinal(StrToInt(Trim(Buffer)));

    Exchange := AllocMem(SizeOf(TNeroDataExchange));
    Exchange.ndeType := NERO_ET_FILE;

    sdWAV.Title := 'Extract Track #' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiTrackNumber);
    if FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiISRC <> '' then
      sdWAV.Title := sdWAV.Title + ' ISRC : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiISRC;
    if FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiArtist <> '' then
      sdWAV.Title := sdWAV.Title + ' Artist : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiArtist;
    if FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiTitle <> '' then
      sdWAV.Title := sdWAV.Title + ' Title : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiTitle;

    if not sdWAV.Execute then
    begin
      NeroFreeMem(NeroCallBack);
      NeroFreeMem(Exchange);
      exit;
    end;

    if FileExists(sdWAV.FileName) then
      DeleteFile(sdWAV.FileName);

    StrCopy(Exchange.ndeData.ndeFileName, PChar(sdWAV.FileName));
    Exchange.ndeData.ndeFileName[Length(sdWAV.FileName)] := #0;

    btnClose.Visible := False;
    btnCancel.Visible := True;
    pbProgress.Visible := True;
    pbProgress.Position := 0;
    pbProgress.Max := FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiTrackLengthInBlks;

    NeroDAE(FMainForm.dnapiDevices.SelectedDeviceHandle, FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiTrackStartBlk,
      FMainForm.NeroCDInfo.ncdiTrackInfos[Track].ntiTrackLengthInBlks, Exchange,
      FMainForm.dnapiDevices.SelectedDevice.nsdiReadSpeeds.nsiSupportedSpeedsKBs[FMainForm.dnapiDevices.SelectedDevice.nsdiReadSpeeds.nsiNumSupportedSpeeds - 1],
      NeroCallBack);

    NeroFreeMem(NeroCallBack);
    NeroFreeMem(Exchange);
  end;
end;

procedure TFMediaInfo.tvTracksCollapsing(Sender: TObject; Node: TTreeNode;
  var AllowCollapse: Boolean);
begin
  if (LeftStr(Node.Text, 7) = 'Session') then
    Node.ImageIndex := 1;
end;

procedure TFMediaInfo.tvTracksExpanded(Sender: TObject; Node: TTreeNode);
begin
  if (LeftStr(Node.Text, 7) = 'Session') then
    Node.ImageIndex := 2;
end;

end.
