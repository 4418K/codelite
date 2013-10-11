//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : compiler_pages.h
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

//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef COMPILER_PAGE_BASE_CLASSES_H
#define COMPILER_PAGE_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>

class CompilerPatternsBase : public wxPanel
{
protected:
    wxStaticText* m_staticText161;
    wxListCtrl* m_listErrPatterns;
    wxButton* m_btnAddErrPattern;
    wxButton* m_btnDelErrPattern;
    wxButton* m_btnUpdateErrPattern;
    wxStaticLine* m_staticline5;
    wxStaticText* m_staticText17;
    wxListCtrl* m_listWarnPatterns;
    wxButton* m_btnAddWarnPattern;
    wxButton* m_btnDelWarnPattern;
    wxButton* m_btnUpdateWarnPattern;

protected:
    virtual void OnErrItemActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnBtnAddErrPattern(wxCommandEvent& event) { event.Skip(); }
    virtual void OnBtnDelErrPattern(wxCommandEvent& event) { event.Skip(); }
    virtual void OnErrorPatternSelectedUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnBtnUpdateErrPattern(wxCommandEvent& event) { event.Skip(); }
    virtual void OnWarnItemActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnBtnAddWarnPattern(wxCommandEvent& event) { event.Skip(); }
    virtual void OnBtnDelWarnPattern(wxCommandEvent& event) { event.Skip(); }
    virtual void OnWarningPatternSelectedUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnBtnUpdateWarnPattern(wxCommandEvent& event) { event.Skip(); }

public:
    CompilerPatternsBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~CompilerPatternsBase();
};


class CompilerToolsBase : public wxPanel
{
protected:
    wxStaticText* m_staticText92;
    wxTextCtrl* m_textCompilerName;
    wxStaticText* m_staticText254;
    wxTextCtrl* m_textCtrlCCompilerName;
    wxStaticText* m_staticText43;
    wxTextCtrl* m_textCtrlAssemblerName;
    wxStaticText* m_staticText116;
    wxTextCtrl* m_textLinkerName;
    wxStaticText* m_staticText128;
    wxTextCtrl* m_textSOLinker;
    wxStaticText* m_staticText1010;
    wxTextCtrl* m_textArchiveTool;
    wxStaticText* m_staticText1412;
    wxTextCtrl* m_textResourceCmp;
    wxStaticText* m_staticText19;
    wxTextCtrl* m_textCtrlMake;
    wxStaticText* m_staticText2014;
    wxTextCtrl* m_textCtrlPathVariable;

protected:

public:
    CompilerToolsBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~CompilerToolsBase();
};


class CompilerSwitchesBase : public wxPanel
{
protected:
    wxStaticText* m_staticText8;
    wxListCtrl* m_listSwitches;

protected:
    virtual void OnItemActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnItemSelected(wxListEvent& event) { event.Skip(); }

public:
    CompilerSwitchesBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(438,428), long style = wxTAB_TRAVERSAL);
    virtual ~CompilerSwitchesBase();
};


class CompilerFileTypesBase : public wxPanel
{
protected:
    wxStaticText* m_staticText23;
    wxListCtrl* m_listCtrlFileTypes;
    wxButton* m_buttonNewFileType;
    wxButton* m_buttonDeleteFileType;

protected:
    virtual void OnFileTypeActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnFileTypeDeSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnFileTypeSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnNewFileType(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDeleteFileType(wxCommandEvent& event) { event.Skip(); }

public:
    CompilerFileTypesBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
    virtual ~CompilerFileTypesBase();
};


class CompilerAdvanceBase : public wxPanel
{
protected:
    wxStaticText* m_staticText18;
    wxStaticText* m_staticText141;
    wxTextCtrl* m_textCtrlGlobalIncludePath;
    wxStaticText* m_staticText16;
    wxTextCtrl* m_textCtrlGlobalLibPath;
    wxStaticText* m_staticText19;
    wxStaticText* m_staticText3;
    wxTextCtrl* m_textObjectExtension;
    wxStaticText* m_staticText24;
    wxTextCtrl* m_textDependExtension;
    wxStaticText* m_staticText25;
    wxTextCtrl* m_textPreprocessExtension;
    wxCheckBox* m_checkBoxGenerateDependenciesFiles;
    wxCheckBox* m_checkBoxObjectNameSameAsFileName;
    wxCheckBox* m_checkBoxReadObjectsFromFile;

protected:

public:
    CompilerAdvanceBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~CompilerAdvanceBase();
};


class CompilerCompilerOptionsBase : public wxPanel
{
protected:
    wxStaticText* m_staticText23;
    wxListCtrl* m_listCompilerOptions;
    wxButton* m_buttonCompilerOption;
    wxButton* m_buttonDeleteCompilerOption;

protected:
    virtual void OnCompilerOptionActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnCompilerOptionDeSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnCompilerOptionSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnNewCompilerOption(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDeleteCompilerOption(wxCommandEvent& event) { event.Skip(); }

public:
    CompilerCompilerOptionsBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
    virtual ~CompilerCompilerOptionsBase();
};


class CompilerLinkerOptionsBase : public wxPanel
{
protected:
    wxStaticText* m_staticText23;
    wxListCtrl* m_listLinkerOptions;
    wxButton* m_buttonLinkerOption;
    wxButton* m_buttonDeleteLinkerOption;

protected:
    virtual void OnLinkerOptionActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnLinkerOptionDeSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnLinkerOptionSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnNewLinkerOption(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDeleteLinkerOption(wxCommandEvent& event) { event.Skip(); }

public:
    CompilerLinkerOptionsBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
    virtual ~CompilerLinkerOptionsBase();
};


class CompilerOptionDlgBase : public wxDialog
{
protected:
    wxStaticText* m_staticText26;
    wxTextCtrl* m_textCtrl18;
    wxStaticText* m_staticText27;
    wxTextCtrl* m_textCtrl19;
    wxStaticLine* m_staticline4;
    wxButton* m_buttonOK;
    wxButton* m_buttonCancel;

protected:

public:
    CompilerOptionDlgBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~CompilerOptionDlgBase();
};


class CompilerPatternDlgBase : public wxDialog
{
protected:
    wxStaticText* m_staticText5;
    wxTextCtrl* m_textPattern;
    wxStaticText* m_staticText6;
    wxTextCtrl* m_textFileIndex;
    wxStaticText* m_staticText7;
    wxTextCtrl* m_textLineNumber;
    wxStaticLine* m_staticline5;
    wxButton* m_buttonOK;
    wxButton* m_buttonCancel;

protected:
    virtual void OnSubmit(wxCommandEvent& event) { event.Skip(); }

public:
    CompilerPatternDlgBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~CompilerPatternDlgBase();
};

#endif
