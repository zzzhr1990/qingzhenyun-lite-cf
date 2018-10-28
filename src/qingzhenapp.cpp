/////////////////////////////////////////////////////////////////////////////
// Name:        qingzhenapp.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     01/09/2018 23:54:00
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "qingzhenapp.h"

////@begin XPM images
////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( QingzhenApp )
////@end implement app


/*
 * QingzhenApp type definition
 */

IMPLEMENT_CLASS( QingzhenApp, wxApp )


/*
 * QingzhenApp event table definition
 */

BEGIN_EVENT_TABLE( QingzhenApp, wxApp )

////@begin QingzhenApp event table entries
////@end QingzhenApp event table entries

END_EVENT_TABLE()


/*
 * Constructor for QingzhenApp
 */

QingzhenApp::QingzhenApp()
{
    Init();
}

#ifdef __WXMAC__

void QingzhenApp::MacOpenFiles(const wxArrayString & fileNames )
{
	// Called when a user drags files over our app
	//mainF->DoOpenFile(fileNames[0], true /* new page */);
	mainWindow->DoOpenFiles(fileNames);
}

#endif // __WXMAC__

/*
 * Member initialisation
 */

void QingzhenApp::Init()
{
////@begin QingzhenApp member initialisation
	
////@end QingzhenApp member initialisation
}

/*
 * Initialisation for QingzhenApp
 */

bool QingzhenApp::OnInit()
{    
////@begin QingzhenApp initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.
	checker = new wxSingleInstanceChecker();
	if (checker->IsAnotherRunning())
	{

		wxMessageBox(_("Another program instance is already running, aborting.\nIf still, restart your computer."),_("Warning"));
		delete checker; // OnExit() won't be called if we return false
		checker = nullptr;
		return false;
	}
	//checker->CreateDefault()
#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	// Load Locate
	auto language = wxLANGUAGE_CHINESE_SIMPLIFIED;
	locale = new wxLocale;
	auto success = locale->Init(language, wxLOCALE_DONT_LOAD_DEFAULT);
	//
	if (success) {
		auto succ = locale->AddCatalog(this->GetAppName());
		if (!succ) {
			delete locale;
			locale = nullptr;
		}
	}


	mainWindow = new MainFrame(nullptr);
	mainWindow->Show(true);
////@end QingzhenApp initialisation

    return true;
}


/*
 * Cleanup for QingzhenApp
 */

int QingzhenApp::OnExit()
{    
////@begin QingzhenApp cleanup

	delete checker;


	delete locale;

	return wxApp::OnExit();
////@end QingzhenApp cleanup
}

