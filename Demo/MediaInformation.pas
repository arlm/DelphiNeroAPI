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
{ Alexandre Rocha Lima e Marcondes . All Rights Reserved.                                      }
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
|* PROGRAM: NeroAPITest.cpp and NeroAPITest.h
|*
|* PURPOSE: Media Information
******************************************************************************}
unit MediaInformation;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls;

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
    procedure FormShow(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FMediaInfo: TFMediaInfo;

implementation

uses MainForm, NeroAPI;

{$R *.dfm}

procedure TFMediaInfo.FormShow(Sender: TObject);
var
  TrackCount: Integer;
  TrackDescription: String;
  Session: TTreeNode;
begin
  if Assigned(FMainForm.NeroDeviceHandle) then
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

      lbFreeBlocks.Caption := IntToStr(FMainForm.NeroCDInfo.ncdiFreeCapacityInBlocks) + ' Free Blocks';
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
        if (not Assigned(Session)) or (Session.Text <> 'session #' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiSessionNumber)) then
          Session := tvTracks.items.AddChild(nil, 'session #' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiSessionNumber));

        TrackDescription := 'Track #' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackNumber);

        case (FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackType) of
          NTT_AUDIO: TrackDescription := TrackDescription + ' [Audio Track]';
          NTT_DATA: TrackDescription := TrackDescription + ' [Data Track]';
          NTT_UNKNOWN: TrackDescription := TrackDescription + ' [Unknown Track]';
        end;

        TrackDescription := TrackDescription + ' (start block : ' + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackStartBlk) +
          ' end block : '  + IntToStr(FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackLengthInBlks + FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTrackStartBlk) +
          ' )';

        if FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiISRC <> '' then
          TrackDescription := TrackDescription + ' ISRC : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiISRC;
        if FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiArtist <> '' then
          TrackDescription := TrackDescription + ' Artist : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiArtist;
        if FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTitle <> '' then
          TrackDescription := TrackDescription + ' Title : ' + FMainForm.NeroCDInfo.ncdiTrackInfos[TrackCount].ntiTitle;

        tvTracks.Items.AddChild(Session, TrackDescription);
      end;
    end;
  end;
end;

procedure TFMediaInfo.btnCloseClick(Sender: TObject);
begin
  Close;
end;

end.
