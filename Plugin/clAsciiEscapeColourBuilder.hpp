#ifndef CLASCIIESCAPECOLOURBUILDER_HPP
#define CLASCIIESCAPECOLOURBUILDER_HPP

#include "codelite_exports.h"
#include <unordered_map>
#include <wx/string.h>

enum class eAsciiColours : int {
    RED,
    YELLOW,
    GREEN,
    GRAY,
    NORMAL_TEXT,
};

enum class eAsciiTheme : int {
    DARK,
    LIGHT,
};

// provide hash for eAsciiColours
namespace std
{
template <> struct hash<eAsciiColours> {
    std::size_t operator()(eAsciiColours i) const { return hash<int>{}((int)i); }
};
} // namespace std

class WXDLLIMPEXP_SDK clAsciiEscapeColourBuilder
{
private:
    wxString& m_string;
    typedef std::unordered_map<eAsciiColours, int> ColoursTable_t;
    ColoursTable_t m_lightThemeColours;
    ColoursTable_t m_darkThemeColours;
    ColoursTable_t* m_activeColours = nullptr;

public:
    clAsciiEscapeColourBuilder(wxString& string);
    ~clAsciiEscapeColourBuilder();

    clAsciiEscapeColourBuilder& SetTheme(eAsciiTheme theme);
    clAsciiEscapeColourBuilder& Add(const wxString& text, int textColour, bool bold = false);
    clAsciiEscapeColourBuilder& Add(const wxString& text, eAsciiColours textColour, bool bold = false);
};

#endif // CLASCIIESCAPECOLOURBUILDER_HPP
