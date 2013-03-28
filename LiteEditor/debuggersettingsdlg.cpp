//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : debuggersettingsdlg.cpp
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
#include "debuggersettingsdlg.h"
#include "windowattrmanager.h"
#include "debugger_predefined_types_page.h"
#include "editor_config.h"
#include "debuggermanager.h"
#include "macros.h"
#include "manager.h"
#include "globals.h"
#include "dbgcommanddlg.h"
#include "debuggerconfigtool.h"

///////////////////////////////////////////////////
// Misc Page
///////////////////////////////////////////////////

DebuggerPageMisc::DebuggerPageMisc(wxWindow* parent, const wxString &title)
    : DbgPageMiscBase(parent)
    , m_title(title)
{
    DebuggerInformation info;
    if(DebuggerMgr::Get().GetDebuggerInformation(title, info)) {
        m_checkBoxEnableLog->SetValue(info.enableDebugLog);
        m_checkShowTerminal->SetValue(info.showTerminal);
        m_checkUseRelativePaths->SetValue(info.useRelativeFilePaths);
        m_maxFramesSpinCtrl->SetValue(info.maxCallStackFrames);
#ifdef __WXMSW__
        m_checkBoxDebugAssert->SetValue(info.debugAsserts);
#endif
        m_textCtrlCygwinPathCommand->SetValue(info.cygwinPathCommand);
    }

#ifndef __WXMSW__
    m_checkBoxDebugAssert->SetValue(false);
    m_checkBoxDebugAssert->Enable(false);
    m_textCtrlCygwinPathCommand->Enable(false);
    m_staticText5->Enable(false);
#endif
}

DebuggerPageMisc::~DebuggerPageMisc()
{
}

void DebuggerPageMisc::OnDebugAssert(wxCommandEvent& event)
{
}

void DebuggerPageMisc::OnWindowsUI(wxUpdateUIEvent& event)
{
}

///////////////////////////////////////////////////
// Startup Commands Page
///////////////////////////////////////////////////

DebuggerPageStartupCmds::DebuggerPageStartupCmds(wxWindow* parent, const wxString& title)
    : DbgPageStartupCmdsBase(parent)
    , m_title(title)
{
    DebuggerInformation info;
    if(DebuggerMgr::Get().GetDebuggerInformation(title, info)) {
        m_textCtrlStartupCommands->SetValue(info.startupCommands);
    }
}

DebuggerPageStartupCmds::~DebuggerPageStartupCmds()
{
}

///////////////////////////////////////////////////
// General Page
///////////////////////////////////////////////////

DebuggerPage::DebuggerPage(wxWindow *parent, wxString title)
    : DbgPageGeneralBase(parent)
    , m_title(title)
{
    DebuggerInformation info;
    if(DebuggerMgr::Get().GetDebuggerInformation(m_title, info)) {
        m_textCtrDbgPath->SetValue(info.path);
        m_checkBoxEnablePendingBreakpoints->SetValue(info.enablePendingBreakpoints);
        m_checkBreakAtWinMain->SetValue(info.breakAtWinMain);
        m_catchThrow->SetValue(info.catchThrow);
        m_spinCtrlNumElements->SetValue(info.maxDisplayStringSize);
        m_showTooltipsRequiresControl->SetValue(info.showTooltipsOnlyWithControlKeyIsDown);
        m_checkBoxAutoExpand->SetValue(info.autoExpandTipItems);
        m_checkBoxExpandLocals->SetValue(info.resolveLocals);
        m_checkBoxSetBreakpointsAfterMain->SetValue(info.applyBreakpointsAfterProgramStarted);
        m_raiseOnBpHit->SetValue(info.whenBreakpointHitRaiseCodelite);
        m_checkBoxCharArrAsPtr->SetValue(info.charArrAsPtr);
    }
}

DebuggerPage::~DebuggerPage()
{
}

void DebuggerPage::OnBrowse(wxCommandEvent& e)
{
    wxUnusedVar(e);
    wxString newfilepath, filepath(m_textCtrDbgPath->GetValue());
    if ((!filepath.IsEmpty()) && wxFileName::FileExists(filepath)) {
        newfilepath = wxFileSelector(wxT("Select file:"), filepath.c_str());
    } else {
        newfilepath = wxFileSelector(wxT("Select file:"));
    }

    if (!newfilepath.IsEmpty()) {
        m_textCtrDbgPath->SetValue(newfilepath);
    }
}

void DebuggerPage::OnDebugAssert(wxCommandEvent& e)
{
    if ( e.IsChecked() ) {
        m_checkBoxEnablePendingBreakpoints->SetValue(true);
    }
}

void DebuggerPage::OnWindowsUI(wxUpdateUIEvent& event)
{
    // enabloe the Cygwin/MinGW part only when under Windows
    static bool OS_WINDOWS = wxGetOsVersion() & wxOS_WINDOWS ? true : false;
    event.Enable(OS_WINDOWS);
}

///////////////////////////////////////////////////
// PreDefined types Page
///////////////////////////////////////////////////
DbgPagePreDefTypes::DbgPagePreDefTypes(wxWindow* parent)
    : DbgPagePreDefTypesBase(parent)
{
    //add items from the saved items
    DebuggerSettingsPreDefMap data;
    DebuggerConfigTool::Get()->ReadObject(wxT("DebuggerCommands"), &data);

    std::map<wxString, DebuggerPreDefinedTypes>::const_iterator iter = data.GePreDefinedTypesMap().begin();
    for(; iter != data.GePreDefinedTypesMap().end(); iter++) {
        m_notebookPreDefTypes->AddPage(new PreDefinedTypesPage(m_notebookPreDefTypes, iter->second), iter->first, iter->second.IsActive());
    }
}

DbgPagePreDefTypes::~DbgPagePreDefTypes()
{
}

void DbgPagePreDefTypes::Save()
{
    //copy the commands the serialized object m_data
    DebuggerSettingsPreDefMap preDefMap;
    std::map<wxString, DebuggerPreDefinedTypes> typesMap;

    for(size_t i=0; i<m_notebookPreDefTypes->GetPageCount(); i++) {
        PreDefinedTypesPage *page = dynamic_cast<PreDefinedTypesPage*>(m_notebookPreDefTypes->GetPage(i));
        if(page) {
            DebuggerPreDefinedTypes types = page->GetPreDefinedTypes();
            types.SetActive( i == (size_t) m_notebookPreDefTypes->GetSelection() );
            typesMap[types.GetName()] = types;
        }
    }
    preDefMap.SePreDefinedTypesMap(typesMap);

    //save the debugger commands
    DebuggerConfigTool::Get()->WriteObject(wxT("DebuggerCommands"), &preDefMap);
}

void DbgPagePreDefTypes::OnDeleteSet(wxCommandEvent& event)
{
    wxUnusedVar(event);
    int sel = m_notebookPreDefTypes->GetSelection();
    if(sel == wxNOT_FOUND)
        return;

    wxString name = m_notebookPreDefTypes->GetPageText((size_t)sel);
    if(wxMessageBox(wxString::Format(wxT("You are about to delete 'PreDefined Types' set '%s'\nContinue ?"), name.c_str()),
                    wxT("Confirm deleting 'PreDefined Types' set"),
                    wxYES_NO|wxCENTER|wxICON_QUESTION,
                    this) == wxYES) {
        m_notebookPreDefTypes->DeletePage((size_t)sel);
    }
}

void DbgPagePreDefTypes::OnDeleteSetUI(wxUpdateUIEvent& event)
{
    int sel = m_notebookPreDefTypes->GetSelection();
    event.Enable(sel != wxNOT_FOUND && m_notebookPreDefTypes->GetPageText((size_t)sel) != wxT("Default"));
}

void DbgPagePreDefTypes::OnNewSet(wxCommandEvent& event)
{
    NewPreDefinedSetDlg dlg(this);
    dlg.GetCheckBoxMakeActive()->SetValue(false);

    wxArrayString copyFromArr;
    // Make sure that a set with this name does not already exists
    copyFromArr.Add(wxT("None"));
    for(size_t i=0; i<m_notebookPreDefTypes->GetPageCount(); i++) {
        copyFromArr.Add(m_notebookPreDefTypes->GetPageText((size_t)i));
    }
    dlg.GetChoiceCopyFrom()->Append(copyFromArr);
    dlg.GetChoiceCopyFrom()->SetSelection(0);
    dlg.GetNameTextctl()->SetFocus();

    if(dlg.ShowModal() == wxID_OK) {
        wxString newName = dlg.GetNameTextctl()->GetValue();
        newName.Trim().Trim(false);
        if(newName.IsEmpty())
            return;

        // Make sure that a set with this name does not already exists
        for(size_t i=0; i<m_notebookPreDefTypes->GetPageCount(); i++) {
            if(m_notebookPreDefTypes->GetPageText((size_t)i) == newName) {
                wxMessageBox(wxT("A set with this name already exist"), wxT("Name Already Exists"), wxICON_WARNING|wxOK|wxCENTER);
                return;
            }
        }

        DebuggerPreDefinedTypes initialValues;
        wxString copyFrom = dlg.GetChoiceCopyFrom()->GetStringSelection();
        if(copyFrom != wxT("None")) {
            for(size_t i=0; i<m_notebookPreDefTypes->GetPageCount(); i++) {
                PreDefinedTypesPage *page = dynamic_cast<PreDefinedTypesPage*>(m_notebookPreDefTypes->GetPage(i));
                if(page && m_notebookPreDefTypes->GetPageText(i) == copyFrom) {
                    initialValues = page->GetPreDefinedTypes();
                    break;
                }
            }
        }

        initialValues.SetName( newName );
        m_notebookPreDefTypes->AddPage(new PreDefinedTypesPage(m_notebookPreDefTypes, initialValues), 
                                       initialValues.GetName(), 
                                       dlg.GetCheckBoxMakeActive()->IsChecked());

    }
}

///////////////////////////////////////////////////
// Container dialog Page
///////////////////////////////////////////////////
DebuggerSettingsDlg::DebuggerSettingsDlg( wxWindow* parent )
    :DebuggerSettingsBaseDlg( parent )
{
    //fill the notebook with the available debuggers
    Initialize();
    ConnectButton(m_buttonOK, DebuggerSettingsDlg::OnOk);

    // center the dialog
    Centre();

    WindowAttrManager::Load(this, wxT("DbgSettingsDlg"), NULL);
    GetSizer()->Fit(this);
}

void DebuggerSettingsDlg::Initialize()
{
    MSWSetNativeTheme(m_treebook2->GetTreeCtrl());

    DebuggerMgr &mgr = DebuggerMgr::Get();
    wxArrayString debuggers = mgr.GetAvailableDebuggers();
    for (size_t i=0; i<debuggers.GetCount(); i++) {

        //create page per-debugger
        m_treebook2->AddPage(0, debuggers.Item(i), false);

        // for each debugger, add page
        m_treebook2->AddSubPage(new DebuggerPage           (m_treebook2, debuggers.Item(i)), wxT("General"),          true);
        m_treebook2->AddSubPage(new DebuggerPageMisc       (m_treebook2, debuggers.Item(i)), wxT("Misc"),             false);
        m_treebook2->AddSubPage(new DebuggerPageStartupCmds(m_treebook2, debuggers.Item(i)), wxT("Startup Commands"), false);
    }

    m_treebook2->AddPage(new DbgPagePreDefTypes(m_treebook2), wxT("Pre Defined Types"), false);
}

void DebuggerSettingsDlg::OnOk(wxCommandEvent &e)
{
    wxUnusedVar(e);
    //go over the debuggers and set the debugger path
    for (size_t i=0; i<(size_t) m_treebook2->GetPageCount(); i++) {
        wxWindow *win = m_treebook2->GetPage(i);
        if( !win )
            continue;

        DebuggerPage *page =  dynamic_cast<DebuggerPage*>(win);
        if(page) {
            //find the debugger
            DebuggerInformation info;
            DebuggerMgr::Get().GetDebuggerInformation(page->m_title, info);

            //populate the information and save it
            info.enablePendingBreakpoints             = page->m_checkBoxEnablePendingBreakpoints->GetValue();
            info.path                                 = page->m_textCtrDbgPath->GetValue();
            info.name                                 = page->m_title;
            info.breakAtWinMain                       = page->m_checkBreakAtWinMain->IsChecked();
            info.consoleCommand                       = EditorConfigST::Get()->GetOptions()->GetProgramConsoleCommand();
            info.catchThrow                           = page->m_catchThrow->IsChecked();
            info.showTooltipsOnlyWithControlKeyIsDown = page->m_showTooltipsRequiresControl->IsChecked();
            info.maxDisplayStringSize                 = page->m_spinCtrlNumElements->GetValue();
            info.resolveLocals                        = page->m_checkBoxExpandLocals->IsChecked();
            info.autoExpandTipItems                   = page->m_checkBoxAutoExpand->IsChecked();
            info.applyBreakpointsAfterProgramStarted  = page->m_checkBoxSetBreakpointsAfterMain->IsChecked();
            info.whenBreakpointHitRaiseCodelite       = page->m_raiseOnBpHit->IsChecked();
            info.charArrAsPtr                         = page->m_checkBoxCharArrAsPtr->IsChecked();
            DebuggerMgr::Get().SetDebuggerInformation(page->m_title, info);

        }

        DebuggerPageMisc *miscPage =  dynamic_cast<DebuggerPageMisc*>(win);
        if(miscPage) {
            //find the debugger
            DebuggerInformation info;
            DebuggerMgr::Get().GetDebuggerInformation(miscPage->m_title, info);

            //populate the information and save it
            info.enableDebugLog                      = miscPage->m_checkBoxEnableLog->GetValue();
            info.showTerminal                        = miscPage->m_checkShowTerminal->IsChecked();
            info.useRelativeFilePaths                = miscPage->m_checkUseRelativePaths->IsChecked();
            info.maxCallStackFrames                  = miscPage->m_maxFramesSpinCtrl->GetValue();
#ifdef __WXMSW__
            info.debugAsserts                        = miscPage->m_checkBoxDebugAssert->IsChecked();
#endif
            info.cygwinPathCommand                   = miscPage->m_textCtrlCygwinPathCommand->GetValue();
            DebuggerMgr::Get().SetDebuggerInformation(miscPage->m_title, info);
        }

        DebuggerPageStartupCmds *suCmds =  dynamic_cast<DebuggerPageStartupCmds*>(win);
        if(suCmds) {
            //find the debugger
            DebuggerInformation info;
            DebuggerMgr::Get().GetDebuggerInformation(suCmds->m_title, info);
            info.startupCommands = suCmds->m_textCtrlStartupCommands->GetValue();
            DebuggerMgr::Get().SetDebuggerInformation(suCmds->m_title, info);
        }

        DbgPagePreDefTypes *pd = dynamic_cast<DbgPagePreDefTypes*>( win );
        if(pd) {
            pd->Save();
        }
    }

    EndModal(wxID_OK);
}

void DebuggerSettingsDlg::OnButtonCancel(wxCommandEvent &e)
{
    wxUnusedVar(e);
    EndModal(wxID_CANCEL);
}

DebuggerSettingsDlg::~DebuggerSettingsDlg()
{
    WindowAttrManager::Save(this, wxT("DbgSettingsDlg"), NULL);
}
