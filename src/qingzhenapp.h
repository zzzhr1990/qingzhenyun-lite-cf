/////////////////////////////////////////////////////////////////////////////
// Name:        qingzhenapp.h
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     01/09/2018 23:54:00
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _QINGZHENAPP_H_
#define _QINGZHENAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "./frames/mainframe.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * QingzhenApp class declaration
 */

class QingzhenApp: public wxApp
{    
    DECLARE_CLASS( QingzhenApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    QingzhenApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin QingzhenApp event handler declarations

////@end QingzhenApp event handler declarations

////@begin QingzhenApp member function declarations

////@end QingzhenApp member function declarations

////@begin QingzhenApp member variables
////@end QingzhenApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(QingzhenApp)
////@end declare app

#endif
    // _QINGZHENAPP_H_
