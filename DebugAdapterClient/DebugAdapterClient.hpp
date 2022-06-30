//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 Eran Ifrah
// file name            : LLDBPlugin.h
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

#ifndef __LLDBDebugger__
#define __LLDBDebugger__

#include "BreakpointsHelper.hpp"
#include "DAPBreakpointsView.h"
#include "DAPTextView.h"
#include "DebugSession.hpp"
#include "RunInTerminalHelper.hpp"
#include "SessionBreakpoints.hpp"
#include "asyncprocess.h"
#include "clDapSettingsStore.hpp"
#include "clModuleLogger.hpp"
#include "cl_command_event.h"
#include "dap/Client.hpp"
#include "plugin.h"
#include "ssh_account_info.h"

#include <vector>
#include <wx/stc/stc.h>

class DAPMainView;
class IProcess;

class DebugAdapterClient : public IPlugin
{
    dap::Client m_client;
    wxString m_defaultPerspective;
    DebugSession m_session;
    clDapSettingsStore m_dap_store;
    IProcess* m_dap_server = nullptr;
    RunInTerminalHelper m_terminal_helper;
    wxFileName m_breakpointsFile;
    BreakpointsHelper* m_breakpointsHelper = nullptr;
    SessionBreakpoints m_sessionBreakpoints;

    /// ------------------------------------
    /// UI elements
    /// ------------------------------------
    DAPMainView* m_threadsView = nullptr;
    DAPBreakpointsView* m_breakpointsView = nullptr;
    DAPTextView* m_textView = nullptr;

    bool m_raisOnBpHit;
    bool m_isPerspectiveLoaded;
    bool m_showThreadNames;
    bool m_showFileNamesOnly;

    friend class LLDBTooltip;

private:
    void DestroyUI();
    void InitializeUI();
    void LoadPerspective();
    void ShowPane(const wxString& paneName, bool show);
    void ClearDebuggerMarker();
    void DoCleanup();
    void StartAndConnectToDapServer(const DapEntry& dap_server, const wxString& exepath, const wxString& args,
                                    const wxString& working_directory, const clEnvList_t& env);
    bool LaunchProcess(const DapEntry& dap_entry);
    void RefreshBreakpointsView();

    /// stop the dap server if it is running and send DEBUG_STOP event
    void StopProcess();
    void RestoreUI();

    /// Place breakpoint markers for a given editor
    void RefreshBreakpointsMarkersForEditor(IEditor* editor);
    wxString NormaliseReceivedPath(const wxString& path) const;
    void RegisterDebuggers();
    /**
     * @brief return true of the debugger identified by "name"
     * is owned by this plugin
     */
    bool IsDebuggerOwnedByPlugin(const wxString& name) const;

public:
    DebugAdapterClient(IManager* manager);
    ~DebugAdapterClient();

    IManager* GetManager() { return m_mgr; }

    /**
     * @brief Should thread name column be shown in thread pane?
     */
    bool ShowThreadNames() const;

    /**
     * @brief Maybe convert a path to filename only for display.
     */
    wxString GetFilenameForDisplay(const wxString& fileName) const;

protected:
    // Other codelite events
    void OnWorkspaceLoaded(clWorkspaceEvent& event);
    void OnWorkspaceClosed(clWorkspaceEvent& event);
    void OnSettings(wxCommandEvent& event);
    void OnInitDone(wxCommandEvent& event);
    void OnFileLoaded(clCommandEvent& event);

    // UI debugger events
    void OnDebugStart(clDebugEvent& event);
    void OnDebugContinue(clDebugEvent& event);
    void OnDebugNext(clDebugEvent& event);
    void OnDebugStop(clDebugEvent& event);
    void OnDebugIsRunning(clDebugEvent& event);
    void OnDebugCanInteract(clDebugEvent& event);
    void OnDebugStepIn(clDebugEvent& event);
    void OnDebugStepOut(clDebugEvent& event);
    void OnToggleInterrupt(clDebugEvent& event);
    void OnDebugTooltip(clDebugEvent& event);
    void OnDebugQuickDebug(clDebugEvent& event);
    void OnDebugCoreFile(clDebugEvent& event);
    void OnDebugAttachToProcess(clDebugEvent& event);
    void OnDebugDeleteAllBreakpoints(clDebugEvent& event);
    void OnDebugEnableAllBreakpoints(clDebugEvent& event);
    void OnDebugDisableAllBreakpoints(clDebugEvent& event);
    void OnDebugNextInst(clDebugEvent& event);
    void OnDebugVOID(clDebugEvent& event);
    void OnDebugShowCursor(clDebugEvent& event);

    void OnBuildStarting(clBuildEvent& event);
    void OnRunToCursor(wxCommandEvent& event);
    void OnJumpToCursor(wxCommandEvent& event);

    void OnAddWatch(wxCommandEvent& event);
    void OnProcessOutput(clProcessEvent& event);
    void OnProcessTerminated(clProcessEvent& event);

    // DAP events
    void OnDapExited(DAPEvent& event);
    void OnDapLaunchResponse(DAPEvent& event);
    void OnDapInitializedEvent(DAPEvent& event);
    void OnDapInitializeResponse(DAPEvent& event);
    void OnDapStoppedEvent(DAPEvent& event);
    void OnDapThreadsResponse(DAPEvent& event);
    void OnDapStackTraceResponse(DAPEvent& event);
    void OnDapSetFunctionBreakpointResponse(DAPEvent& event);
    void OnDapSetSourceBreakpointResponse(DAPEvent& event);
    void OnDapBreakpointEvent(DAPEvent& event);
    void OnDapRunInTerminal(DAPEvent& event);
    void OnDapLog(DAPEvent& event);
    void OnDapScopesResponse(DAPEvent& event);
    void OnDapVariablesResponse(DAPEvent& event);

public:
    //--------------------------------------------
    // Abstract methods
    //--------------------------------------------
    void CreateToolBar(clToolBar* toolbar) override;
    void CreatePluginMenu(wxMenu* pluginsMenu) override;
    void HookPopupMenu(wxMenu* menu, MenuType type) override;
    void UnPlug() override;

    // expose these API calls to the views can use it
    dap::Client& GetClient() { return m_client; }
    void LoadFile(const dap::Source& sourceId, int line_number);
};

#endif // LLDBDebuggerPlugin
