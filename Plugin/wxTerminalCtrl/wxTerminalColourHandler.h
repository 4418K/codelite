#ifndef WXTERMINALCOLOURHANDLER_H
#define WXTERMINALCOLOURHANDLER_H

#include "clAnsiEscapeCodeHandler.hpp"

#include <map>
#include <unordered_map>
#include <vector>
#include <wx/textctrl.h>

class TextView;
class wxTerminalCtrl;
class wxTerminalColourHandler : public wxEvtHandler
{
    TextView* m_ctrl = nullptr;
    wxSTCStyleProvider* m_style_provider = nullptr;
    wxTextAttr m_defaultAttr;
    wxString m_title;

protected:
    void SetCaretEnd();

public:
    wxTerminalColourHandler();
    ~wxTerminalColourHandler();

    void Append(const wxString& buffer, wxString* window_title);
    void SetCtrl(TextView* ctrl);
    void SetDefaultStyle(const wxTextAttr& attr);
    void Clear();
};

#endif // WXTERMINALCOLOURHANDLER_H
