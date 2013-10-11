//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : sftp.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef __SFTP__
#define __SFTP__

#include "plugin.h"
#include "sftp_workspace_settings.h"
#include "cl_command_event.h"
#include "macros.h"

class SFTPStatusPage;
class SFTPTreeView;

class SFTP : public IPlugin
{
    wxFileName            m_workspaceFile;
    SFTPWorkspaceSettings m_workspaceSettings;
    SFTPStatusPage*       m_outputPane;
    SFTPTreeView*         m_treeView;
    wxStringMap_t         m_remoteFiles;
    
public:
    SFTP(IManager *manager);
    ~SFTP();

protected:
    void OnSettings(wxCommandEvent &e);
    void OnSetupWorkspaceMirroring(wxCommandEvent &e);
    void OnDisableWorkspaceMirroring(wxCommandEvent &e);
    void OnDisableWorkspaceMirroringUI(wxUpdateUIEvent &e);
    void OnWorkspaceOpened(wxCommandEvent &e);
    void OnWorkspaceClosed(wxCommandEvent &e);
    void OnFileSaved(wxCommandEvent &e);
    
    bool IsWorkspaceOpened() const {
        return m_workspaceFile.IsOk();
    }
    
    // API calls
    void OnSaveFile(clCommandEvent &e);
    
public:
    //--------------------------------------------
    //Abstract methods
    //--------------------------------------------
    virtual clToolBar *CreateToolBar(wxWindow *parent);
    virtual void CreatePluginMenu(wxMenu *pluginsMenu);
    virtual void HookPopupMenu(wxMenu *menu, MenuType type);
    virtual void UnHookPopupMenu(wxMenu *menu, MenuType type);
    virtual void UnPlug();
    
    // Callbacks
    void OnFileWriteOK(const wxString &message);
    void OnFileWriteError(const wxString &errorMessage);
};

#endif //SFTP
