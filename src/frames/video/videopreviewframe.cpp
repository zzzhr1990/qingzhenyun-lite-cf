﻿/////////////////////////////////////////////////////////////////////////////
// Name:        videopreviewframe.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     07/09/2018 14:48:49
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 07/09/2018 14:48:49

// For compilers that support precompilation, includes "wx/wx.h".

////@begin includes
#include <wx/platinfo.h>
////@end includes



#ifdef __WXGTK__
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <wx/gtk/win_gtk.h>
#define GET_XID(window) GDK_WINDOW_XWINDOW(GTK_PIZZA(window->m_wxwindow)->bin_window)
#endif
#include "videopreviewframe.h"
#include "../../model/remote_file_model.h"
#include "../../model/user_model.h"
#include "../../util/common_util.h"
////@begin XPM images
////@end XPM images


/*
 * VideoPreviewFrame type definition
 */

IMPLEMENT_DYNAMIC_CLASS( VideoPreviewFrame, wxDialog )


/*
 * VideoPreviewFrame event table definition
 */

BEGIN_EVENT_TABLE( VideoPreviewFrame, wxDialog )

////@begin VideoPreviewFrame event table entries
////@end VideoPreviewFrame event table entries

END_EVENT_TABLE()


/*
 * VideoPreviewFrame constructors
 */

VideoPreviewFrame::VideoPreviewFrame()
{
    Init();
}

VideoPreviewFrame::VideoPreviewFrame(const utility::string_t& path, wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
	this->path = path;
	this->Bind(wxEVT_THREAD, &VideoPreviewFrame::OnThreadEvent, this);
	//this->Bind(wxEVT_CLOSE_WINDOW, &VideoPreviewFrame::OnCloseWindow, this);
	// bind video...

	/*

	eventManager.onPlaying([&]() {
		//std::cout << media.mrl() << " is playing" << std::endl;
		std::cout << this->mp.media().get()->mrl()<< " is playing" << std::endl;
	});

	//bool expected = true;
	mp.eventManager().onPositionChanged([](float pos) {
		std::cout << "position changed " << pos * 10000 << std::endl;
		//assert(expected);
	});
	 */

	//eventManager.

}

void VideoPreviewFrame::OnThreadEvent(wxThreadEvent &event) {
	// D
	switch (event.GetInt()) {
	case USER_PREVIEW_INFO:
	{
		auto payload = event.GetPayload<ResponseEntity>();
		//RefreshListData(payload);
		if (payload.success) {
			//wxMessageBox(_("Success load preview file."), _("Load Preview Success"));
			
			if (payload.result.has_field(U("preview"))) {
				auto preview = payload.result.at(U("preview")).as_array();
				if (preview.size() > 0) {
					// do preview
					PlayPreview(preview);
				}
				else {
					wxMessageBox(_("Preview file is empty."), _("Load Preview Error"));
					this->Close();
				}
			}
		}
		else {
			wxMessageBox(_("Cannot load preview file."), _("Load Preview Error"));
			this->Close();
		}
		break;
	}
	/*
	case USER_REMOTE_DIRECTORY_CREATE:
	{
		auto & fileModel = RemoteFileModel::Instance();
		fileModel.GetPage(this);
		break;
	}
	*/
	
	default:
		event.Skip();
	}
}

/*
void VideoPreviewFrame::OnCloseWindow(wxCloseEvent & event)
{
	event.Skip();
	if (mp == NULL) {
		return;
	}
	if (mp.isPlaying()) {
		mp.stop();
	}
}
 */

void VideoPreviewFrame::Clean(){
	auto system = wxPlatformInfo::Get().GetOperatingSystemId();
	if(system & wxOS_WINDOWS){
		mp.setHwnd(nullptr);
	}
	if (system & wxOS_MAC) {
		mp.setNsobject(nullptr);
	}
	this->UnloadEvents();
	mp.media().reset();
	// std::cout << "START STOP" << std::endl;
	std::thread([this](){
		this->mp.stop();
	//	std::cout << "STOP - STOP" << std::endl;
	}).detach();
	//mp.stop();
	//std::cout << "END STOP" << std::endl;
    //mp.media().reset();
	//delete playPosEvent;

}

void VideoPreviewFrame::PlayPreview(const web::json::array& array) {
	// create

	int clear = 0;
	utility::string_t t;
	for (const auto& i : array) {
		auto c = i.at(U("clear")).as_integer();
		if (c > clear) {
			t = i.at(U("url")).as_string();
			clear = c;
		}
	}
	if (clear > 0) {
		auto url = t.append(U("?token=")).append(UserModel::Instance().GetToken());
		const std::string& xx = utility::conversions::to_utf8string(url);
		std::cout << xx << std::endl;
		auto system = wxPlatformInfo::Get().GetOperatingSystemId();



		//instance =
		VLC::Media media = VLC::Media(instance, xx, VLC::Media::FromLocation);
		// mp =
		// Under Windows, we use Hwnd to pass windows ids.
		// TODO: Change to DirectX 11 for better performance later.

		if(system & wxOS_WINDOWS){
			mp.setHwnd(playerWidget->GetHandle());
		}
		if (system & wxOS_MAC) {
			mp.setNsobject(playerWidget->GetHandle());
		}
		//CopyTextToClipboard(xx);

		//
		// media.addOption("--freetype-color=16777215");

		//instance.
		mp.setMedia(media);
		mp.play();
	}
	else {
		wxMessageBox(_("No video stream found."), _("Load Preview Error"));
		this->Close();
	}


	

}

void VideoPreviewFrame::SetPath(const utility::string_t& path) {
	this->path = path;
}
void VideoPreviewFrame::GetVideoStream() {
	this->RegisterEvents();
	RemoteFileModel::Instance().GetPreviewInfo(this, path);
}

/*
 * VideoPreviewFrame creator
 */

bool VideoPreviewFrame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin VideoPreviewFrame creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end VideoPreviewFrame creation
    return true;
}


/*
 * VideoPreviewFrame destructor
 */

VideoPreviewFrame::~VideoPreviewFrame()
{
////@begin VideoPreviewFrame destruction
	//delete media;
	//delete player;
	//delete instance;
	//player.med
	//std::cout << "DEL_V_FR" << std::endl;
	//instance = NULL;

	/*
	if(playPosEvent!= nullptr){
		playPosEvent->unregister();
		//delete playPosEvent;
		//playPosEvent = nullptr;
	}
	 */


////@end VideoPreviewFrame destruction
}


/*
 * Member initialisation
 */

void VideoPreviewFrame::Init()
{
////@begin VideoPreviewFrame member initialisation
////@end VideoPreviewFrame member initialisation
}


/*
 * Control creation for VideoPreviewFrame
 */

void VideoPreviewFrame::CreateControls()
{    
////@begin VideoPreviewFrame content construction
    // Generated by DialogBlocks, 08/09/2018 00:01:21 (unregistered)

    VideoPreviewFrame* itemDialog1 = this;

	mainBoxSizer = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(mainBoxSizer);

    // wxMediaCtrl* itemMediaCtrl1 = new wxMediaCtrl( itemDialog1, ID_MEDIACTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 100), wxNO_BORDER );
	/*
	
	playerWidget = new wxWindow(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxNO_BORDER);
	playerWidget->SetBackgroundColour(wxColour(wxT("black")));
	
	*/
	wxPanel* itemPanel1 = new wxPanel(itemDialog1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL);
	itemPanel1->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
	itemPanel1->SetName(wxT("playerPanel"));
	itemPanel1->SetBackgroundColour(wxColour(wxT("black")));
	mainBoxSizer->Add(itemPanel1, 1, wxGROW, 5);

	wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	//itemBoxSizer3->SetBackgroundColour(wxColour(wxT("black")));
	itemPanel1->SetSizer(itemBoxSizer3);
	playerWidget = new wxWindow(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxNO_BORDER);
	playerWidget->SetBackgroundColour(wxColour(wxT("black")));
	playerWidget->Disable();
	//wxMediaCtrl* itemMediaCtrl4 = new wxMediaCtrl(itemPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(100, 100), wxNO_BORDER);
	itemBoxSizer3->Add(playerWidget, 1, wxGROW, 5);
	
    //mainBoxSizer->Add(playerWidget, 1, wxGROW, 5);

	controllBarSizer = new wxBoxSizer(wxHORIZONTAL);
    mainBoxSizer->Add(controllBarSizer, 0, wxGROW, 5);

    playBtn = new wxButton( itemDialog1, wxID_ANY, _("PLAY"), wxDefaultPosition, wxDefaultSize, 0 );
    controllBarSizer->Add(playBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    playingTime = new wxStaticText( itemDialog1, wxID_STATIC, _("00:00"), wxDefaultPosition, wxSize(60, -1), wxALIGN_CENTRE );
    controllBarSizer->Add(playingTime, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    progressSlider = new wxSlider( itemDialog1, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
    controllBarSizer->Add(progressSlider, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    totalTimeText = new wxStaticText( itemDialog1, wxID_STATIC, _("00:00"), wxDefaultPosition, wxSize(60, -1), wxALIGN_CENTRE );
    controllBarSizer->Add(totalTimeText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("vol"), wxDefaultPosition, wxDefaultSize, 0 );
    controllBarSizer->Add(itemStaticText6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    volSlider = new wxSlider( itemDialog1, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
    controllBarSizer->Add(volSlider, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	progressSlider->Bind(wxEVT_SCROLL_THUMBTRACK, &VideoPreviewFrame::OnBeginSeek,this);
	progressSlider->Bind(wxEVT_SCROLL_THUMBRELEASE, &VideoPreviewFrame::OnEndSeek,this);
	progressSlider->Bind(wxEVT_SCROLL_PAGEUP, &VideoPreviewFrame::OnSliderScrollPageUp, this);
	progressSlider->Bind(wxEVT_SCROLL_PAGEDOWN, &VideoPreviewFrame::OnSliderScrollPageDown, this);

	volSlider->Bind(wxEVT_SCROLL_THUMBTRACK, &VideoPreviewFrame::OnBeginVol,this);
	volSlider->Bind(wxEVT_SCROLL_THUMBRELEASE, &VideoPreviewFrame::OnEndVol,this);
	//libvlc_event_attach(vlcEventManager, libvlc_MediaPlayerEndReached, ::OnEndReached_VLC, NULL);
	//libvlc_event_attach(vlcEventManager, libvlc_MediaPlayerPositionChanged, ::OnPositionChanged_VLC, NULL);
	//libvlc_event_attach(vlcEventManager, libvlc_Me, ::OnPositionChanged_VLC, NULL);
    playBtn->Bind(wxEVT_BUTTON, &VideoPreviewFrame::OnPlayBtnClick, this);
    playerWidget->Bind(wxEVT_LEFT_DCLICK, &VideoPreviewFrame::OnPlayerDClick, this);
	playerWidget->Bind(wxEVT_LEFT_UP, &VideoPreviewFrame::OnPlayerClick, this);
    /*
    
	auto bx = ([&](wxCommandEvent e){
		std::cout << "xxx" << std::endl;
	});
    playerWidget->Bind(wxEVT_COMMAND_LEFT_CLICK,bx);
     */
	InitVLC();
//	this->instance.addIntf("hotkeys,none");
    //auto eventManager = mp.eventManager();


////@end VideoPreviewFrame content construction
}

//void VideoPreviewFrame::OnPositionChanged_VLC(const libvlc_event_t *event, void *data) {
	//wxCommandEvent evt(vlcEVT_POS, wxID_ANY);
	//mainWindow->GetEventHandler()->AddPendingEvent(evt);
	//event.
//}

//void VideoPreviewFrame::OnEndReached_VLC(const libvlc_event_t *event, void *data) {
	//wxCommandEvent evt(vlcEVT_END, wxID_ANY);
	//mainWindow->GetEventHandler()->AddPendingEvent(evt);
//}

void VideoPreviewFrame::InitVLC() {
#ifdef __WXGTK__
	libvlc_media_player_set_xwindow(media_player, GET_XID(this->playerWidget));
#else
	//libvlc_media_player_set_hwnd(mediaPlayer, this->playerWidget->GetHandle());
	//libvlc
	//libvlc_media_player_set_w
#endif
	mp.setMouseInput(false);
}

/*
 * Should we show tooltips?
 */

void VideoPreviewFrame::OnBeginSeek(wxScrollEvent& WXUNUSED(event))
{
	beginSeek = true;
}

void VideoPreviewFrame::OnEndSeek(wxScrollEvent& WXUNUSED(event))
{
    /*
    if( m_mediactrl->Seek(
            m_slider->GetValue() * 1000
    ) == wxInvalidOffset )
        wxMessageBox(wxT("Couldn't seek in movie!"));
        */
	StartSeek();
}

void VideoPreviewFrame::StartSeek() {
	if (mp.isSeekable()) {
		//this->totalTime * 1000 / 2;
		mp.setPosition(0.01f * progressSlider->GetValue());
		//std::cout << progressSlider->GetValue() << std::endl;
		this->currentPercent = -1;
	}
	beginSeek = false;
}

bool VideoPreviewFrame::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap VideoPreviewFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin VideoPreviewFrame bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end VideoPreviewFrame bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon VideoPreviewFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin VideoPreviewFrame icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end VideoPreviewFrame icon retrieval
}

void VideoPreviewFrame::OnSliderScrollPageUp(wxScrollEvent & event)
{
	StartSeek();
}

void VideoPreviewFrame::OnSliderScrollPageDown(wxScrollEvent & event)
{
	StartSeek();
}

void VideoPreviewFrame::RegisterEvents() {
	playPosEvent = mp.eventManager().onPositionChanged([&](float pos) {
		int newPos = static_cast<int>(pos * 100);
		if(newPos != this->currentPercent){
			this->progressSlider->SetValue(newPos);//currentPercent
			this->currentPercent = newPos;
		}
	});

	timeEvent = mp.eventManager().onTimeChanged([&](int64_t pos){
		int newTime = static_cast<int>(pos / 1000);
		if(newTime != this->currentTime){

			if(!this->beginSeek){
				this->currentTime = newTime;
				int nMinutes = newTime / 60;
				int nSeconds =  newTime % 60;
				this->playingTime->SetLabel(wxString::Format(wxT("%02i:%02i"), nMinutes, nSeconds));
			}

		}
	});

    playingEvent = mp.eventManager().onPlaying([&]{
        this->playBtn->SetLabel(_("PAUSE"));
	});

    pauseEvent = mp.eventManager().onPaused([&]{
        this->playBtn->SetLabel(_("PLAY"));
    });

	bufferEvent = mp.eventManager().onBuffering([&](int64_t status){
		//std::cout << "Buffering:" << status << std::endl;

		if(status == 100){
		    if(mp.state() == libvlc_Playing){
                this->playBtn->SetLabel(_("PAUSE"));
		    }else{
                this->playBtn->SetLabel(_("PLAY"));
		    }

		}else{
            this->playBtn->SetLabel(wxString::Format(wxT("%s(%d)"),_("BUF"), static_cast<int>(status)));
		}
	});

	lengthEvent = mp.eventManager().onLengthChanged([&](int64_t time){

		int newTime = static_cast<int>(time / 1000);
		this->totalTime = newTime;
		int nMinutes = newTime / 60;
		int nSeconds =  newTime % 60;
		this->totalTimeText->SetLabel(wxString::Format(wxT("%02i:%02i"), nMinutes, nSeconds));
	});



    volEvent = mp.eventManager().onAudioVolume([&](float vol){
	    //std::cout << vol << std::endl;
		volSlider->SetValue(static_cast<int>(vol * 100));
		std::cout << "Vol Change" << vol << std::endl;
	});

	endEvent = mp.eventManager().onEndReached([&]() {
		//std::cout << vol << std::endl;
		/*
		*/
		
		if (mp.isSeekable()) {
			mp.setPosition(0.1f);
		}
		if (mp.canPause()) {
			mp.pause();
		}
		
		//mp.setPosition(0.1f);
		//mp.stop();
		//mp.setPosition(0);
		//mp.play();
	});


    /*
    mp.eventManager().onVout([](int newCount){
    	std::cout << "Vout:" << newCount << std::endl;
    });

    mp.eventManager().onCorked([](){
		std::cout << "Chork:" << std::endl;
    });

	mp.eventManager().onUncorked([](){
		std::cout << "UnChork:" << std::endl;
	});



	//mp.eventManager().onScrambledChanged()
	 */
	//mp.tit

}

void VideoPreviewFrame::UnloadEvents() {
	if(playPosEvent != nullptr){
		playPosEvent->unregister();
		// playPosEvent = nullptr;
		//playPosEvent = nullptr;
	}
	if(bufferEvent != nullptr){
		bufferEvent->unregister();
		// delete bufferEvent;
	}
	if(timeEvent != nullptr){
		timeEvent->unregister();
		// delete timeEvent;
	}
	if(lengthEvent != nullptr){
		lengthEvent->unregister();
		// delete lengthEvent;
	}
	if(playingEvent != nullptr){
        playingEvent->unregister();
	}
    if(pauseEvent != nullptr){
        pauseEvent->unregister();
    }
    if(volEvent != nullptr){
        volEvent->unregister();
    }
	if (endEvent != nullptr) {
		endEvent->unregister();
	}
	

}

void VideoPreviewFrame::OnEndVol(wxScrollEvent &) {
	beginSeek = false;
	mp.setVolume(volSlider->GetValue());
}

void VideoPreviewFrame::OnBeginVol(wxScrollEvent &) {
	beginSeek = true;
}

void VideoPreviewFrame::OnPlayBtnClick(wxCommandEvent &) {
    CheckPauseBtnClick();
}

void VideoPreviewFrame::OnPlayerDClick(wxMouseEvent &) {
	/*
	
	bool succ = mp.addSlave(VLC::MediaSlave::Type::Subtitle,"https://www.6pan.cn/test.srt",
							true);
	std::cout << "Adding subtitle " << succ << std::endl;
	//mp.setMedia(*mp.media());

	//mp.

    std::cout << "Should Full Screen:sp:" << mp.spu() << " count" << mp.spuCount() << " DESC:" << mp.spuDescription().size() << std::endl;
    if(mp.spuCount() > 0){
    	for(unsigned long i = 0; i < mp.spuCount();i++){
    		//mp.setSpu(i);
			auto desc = mp.spuDescription().at(i);
			std::cout << "SUB: " << desc.name() << std::endl;
			mp.setSpu(desc.id());
    	}
    }
	*/

    //mp.setTeletext(libvlc_teletext_key_red);
    /*
	mp.setMarqueeString(libvlc_marquee_Text,"Ppppdedepd杀不杀epdepdpedpedpedpepdede");
	mp.setMarqueeInt(libvlc_marquee_Size,72);
	mp.setMarqueeInt(libvlc_marquee_Timeout,2000);
	mp.setMarqueeInt(libvlc_marquee_Enable,1);
     */

    //mp.spuDescription().
	//controllBarSizer->Hide(this);
}

void VideoPreviewFrame::OnPlayerClick(wxMouseEvent &) {
    CheckPauseBtnClick();
}

void VideoPreviewFrame::CheckPauseBtnClick() {
    const auto& state = mp.state();
    if(state == libvlc_Playing || state == libvlc_Buffering){
        //this->playBtn->SetLabel(_("PAUSE"));
        if(mp.canPause()){
            mp.pause();
        }
    }else{
        //this->playBtn->SetLabel(_("PLAY"));
        mp.play();
    }
}
