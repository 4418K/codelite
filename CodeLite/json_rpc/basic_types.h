#ifndef JSONRPC_BASICTYPES_H
#define JSONRPC_BASICTYPES_H

#include "codelite_exports.h"
#include "json_node.h"
#include "JSONObject.h"
#include <wx/sharedptr.h>

namespace json_rpc
{
//===----------------------------------------------------------------------------------
// TextDocumentIdentifier
//===----------------------------------------------------------------------------------
class WXDLLIMPEXP_CL TextDocumentIdentifier : public Serializable
{
    wxFileName m_filename;

public:
    virtual JSONElement ToJSON(const wxString& name) const;
    virtual void FromJSON(const JSONElement& json);

    TextDocumentIdentifier() {}
    TextDocumentIdentifier(const wxFileName& filename)
        : m_filename(filename)
    {
    }
    virtual ~TextDocumentIdentifier() {}
    TextDocumentIdentifier& SetFilename(const wxFileName& filename)
    {
        this->m_filename = filename;
        return *this;
    }
    const wxFileName& GetFilename() const { return m_filename; }
};

//===----------------------------------------------------------------------------------
// Position
//===----------------------------------------------------------------------------------
class WXDLLIMPEXP_CL Position : public Serializable
{
    int m_line;
    int m_character;

public:
    virtual void FromJSON(const JSONElement& json);
    virtual JSONElement ToJSON(const wxString& name) const;

    Position(int line, int col)
        : m_line(line)
        , m_character(col)
    {
    }
    Position() {}
    virtual ~Position() {}
    Position& SetCharacter(int character)
    {
        this->m_character = character;
        return *this;
    }
    Position& SetLine(int line)
    {
        this->m_line = line;
        return *this;
    }
    int GetCharacter() const { return m_character; }
    int GetLine() const { return m_line; }
};

//===----------------------------------------------------------------------------------
// TextDocumentItem
//===----------------------------------------------------------------------------------
class WXDLLIMPEXP_CL TextDocumentItem : public Serializable
{
    wxFileName m_uri;
    wxString m_languageId;
    wxString m_text;
    int m_version = 1;

public:
    virtual void FromJSON(const JSONElement& json);
    virtual JSONElement ToJSON(const wxString& name) const;

    TextDocumentItem(const wxFileName& uri, const wxString& langId, const wxString& text, int version = 1)
        : m_uri(uri)
        , m_languageId(langId)
        , m_text(text)
        , m_version(version)
    {
    }
    TextDocumentItem() {}
    virtual ~TextDocumentItem() {}
    TextDocumentItem& SetLanguageId(const wxString& languageId)
    {
        this->m_languageId = languageId;
        return *this;
    }
    TextDocumentItem& SetText(const wxString& text)
    {
        this->m_text = text;
        return *this;
    }
    TextDocumentItem& SetUri(const wxFileName& uri)
    {
        this->m_uri = uri;
        return *this;
    }
    TextDocumentItem& SetVersion(int version)
    {
        this->m_version = version;
        return *this;
    }
    const wxString& GetLanguageId() const { return m_languageId; }
    const wxString& GetText() const { return m_text; }
    const wxFileName& GetUri() const { return m_uri; }
    int GetVersion() const { return m_version; }
};

};     // namespace json_rpc
#endif // JSONRPC_BASICTYPES_H