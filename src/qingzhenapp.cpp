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
	return wxApp::OnExit();
////@end QingzhenApp cleanup
}

