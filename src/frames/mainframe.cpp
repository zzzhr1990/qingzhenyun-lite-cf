/////////////////////////////////////////////////////////////////////////////
// Name:        mainframe.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     01/09/2018 23:54:25
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
#include "./notebook/mainnotebook.h"
////@end includes

#include "mainframe.h"

////@begin XPM images
#include "../resources/if_cloud_main.xpm"
#include "../resources/user.xpm"
#include "../resources/settings.xpm"
////@end XPM images


/*
 * MainFrame type definition
 */

IMPLEMENT_CLASS( MainFrame, wxFrame )


/*
 * MainFrame event table definition
 */

BEGIN_EVENT_TABLE( MainFrame, wxFrame )

////@begin MainFrame event table entries
////@end MainFrame event table entries

END_EVENT_TABLE()


/*
 * MainFrame constructors
 */

MainFrame::MainFrame()
{
    Init();
}

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * MainFrame creator
 */

bool MainFrame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin MainFrame creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    SetIcon(GetIconResource(wxT("if_cloud_main.xpm")));
    Centre();
////@end MainFrame creation
    return true;
}


/*
 * MainFrame destructor
 */

MainFrame::~MainFrame()
{
////@begin MainFrame destruction
////@end MainFrame destruction
}


/*
 * Member initialisation
 */

void MainFrame::Init()
{
////@begin MainFrame member initialisation
////@end MainFrame member initialisation
}


/*
 * Control creation for MainFrame
 */

void MainFrame::CreateControls()
{    
////@begin MainFrame content construction
    MainFrame* itemFrame1 = this;

    wxMenuBar* menuBar = new wxMenuBar;
    wxMenu* itemMenu2 = new wxMenu;
    itemMenu2->Append(wxID_ANY, _("Login/Change User"), wxEmptyString, wxITEM_NORMAL);
    menuBar->Append(itemMenu2, _("User"));
    itemFrame1->SetMenuBar(menuBar);

    wxToolBar* itemToolBar4 = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_TOOLBAR );
    wxBitmap itemtool5Bitmap(itemFrame1->GetBitmapResource(wxT("user.xpm")));
    wxBitmap itemtool5BitmapDisabled;
    itemToolBar4->AddTool(ID_USER_TOOL, wxEmptyString, itemtool5Bitmap, itemtool5BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    itemToolBar4->AddSeparator();
    wxBitmap itemtool8Bitmap(itemFrame1->GetBitmapResource(wxT("settings.xpm")));
    wxBitmap itemtool8BitmapDisabled;
    itemToolBar4->AddTool(ID_SETTING_TOOL, wxEmptyString, itemtool8Bitmap, itemtool8BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    itemToolBar4->Realize();
    itemFrame1->SetToolBar(itemToolBar4);

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxVERTICAL);
    itemFrame1->SetSizer(itemBoxSizer14);

    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer14->Add(itemBoxSizer15, 1, wxGROW, 5);

    MainNotebook* itemNotebook1 = new MainNotebook( itemFrame1, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
    itemBoxSizer15->Add(itemNotebook1, 1, wxGROW, 5);

    wxStatusBar* itemStatusBar17 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar17->SetFieldsCount(3);
    itemStatusBar17->SetStatusText(_("Field One"), 0);
    itemStatusBar17->SetStatusText(_("Field Two"), 1);
    itemStatusBar17->SetStatusText(_("Sync"), 2);
    int itemStatusBar17Widths[3];
    itemStatusBar17Widths[0] = 200;
    itemStatusBar17Widths[1] = -1;
    itemStatusBar17Widths[2] = 200;
    itemStatusBar17->SetStatusWidths(3, itemStatusBar17Widths);
    itemFrame1->SetStatusBar(itemStatusBar17);

////@end MainFrame content construction
}


/*
 * Should we show tooltips?
 */

bool MainFrame::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MainFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MainFrame bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("user.xpm"))
    {
        wxBitmap bitmap(user_xpm);
        return bitmap;
    }
    else if (name == wxT("settings.xpm"))
    {
        wxBitmap bitmap(settings_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end MainFrame bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MainFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MainFrame icon retrieval
    wxUnusedVar(name);
    if (name == wxT("if_cloud_main.xpm"))
    {
        wxIcon icon(if_cloud_xpm);
        return icon;
    }
    return wxNullIcon;
////@end MainFrame icon retrieval
}
