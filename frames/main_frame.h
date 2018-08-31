#pragma once
#ifndef FUCK_MAIN_FRAME_H
#define FUCK_MAIN_FRAME_H

#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/notebook.h"
#include "wx/dataview.h"
#endif

class MainFrame : public wxFrame
{
public:
	// ctor(s)
	MainFrame(const wxString& title, int w, int h);
	void OnQuit(wxCommandEvent & WXUNUSED);
	void OnAbout(wxCommandEvent & WXUNUSED);
	void OnWindowCreate(wxIdleEvent & WXUNUSED);
	void OnClose(wxCloseEvent & event);
private:
	wxDECLARE_EVENT_TABLE();

	wxMenu *fileMenu = nullptr;
	wxMenu *helpMenu = nullptr;
	// LoginFrame *loginFrame = nullptr;
};
#endif //FUCK_MAIN_FRAME_H