//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2013 by Eran Ifrah
// file name            : cl_sftp.h
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

#ifndef CLSCP_H
#define CLSCP_H

#include "cl_ssh.h"
#include "cl_exception.h"
#include <wx/filename.h>
#include "codelite_exports.h"
#include "cl_sftp_attribute.h"

// We do it this way to avoid exposing the include to <libssh/sftp.h> to files including this header
struct sftp_session_struct;
typedef struct sftp_session_struct* SFTPSession_t;


class WXDLLIMPEXP_CL clSFTP
{
    clSSH::Ptr_t  m_ssh;
    SFTPSession_t m_sftp;
    bool          m_connected;
    wxString      m_currentFolder;
    wxString      m_account;

public:
    typedef wxSharedPtr<clSFTP> Ptr_t;
    enum {
        SFTP_BROWSE_FILES   = 0x00000001,
        SFTP_BROWSE_FOLDERS = 0x00000002,
    };

public:
    clSFTP(clSSH::Ptr_t ssh);
    virtual ~clSFTP();

    bool IsConnected() const {
        return m_connected;
    }

    void SetAccount(const wxString& account) {
        this->m_account = account;
    }
    const wxString& GetAccount() const {
        return m_account;
    }
    /**
     * @brief intialize the scp over ssh
     */
    void Initialize() throw (clException);

    /**
     * @brief close the scp channel
     */
    void Close();

    /**
     * @brief write the content of local file into a remote file
     * @param localFile the local file
     * @param remotePath the remote path (abs path)
     */
    void Write(const wxFileName& localFile, const wxString &remotePath) throw (clException);

    /**
     * @brief write the content of 'fileContent' into the remote file represented by remotePath
     */
    void Write(const wxString &fileContent, const wxString &remotePath) throw (clException);
    
    /**
     * @brief read remote file and return its content
     * @return the file content.
     */
    wxString Read(const wxString &remotePath) throw (clException);
    /**
     * @brief list the content of a folder
     * @param folder
     * @param foldersOnly
     * @param filter filter out files that do not match the filter
     * @throw clException incase an error occured
     */
    SFTPAttribute::List_t List(const wxString &folder, size_t flags, const wxString &filter = "") throw (clException);

    /**
     * @brief cd up and list the content of the directory
     * @return
     */
    SFTPAttribute::List_t CdUp(size_t flags, const wxString &filter) throw (clException);

    /**
     * @brief return the current folder
     */
    const wxString& GetCurrentFolder() const {
        return m_currentFolder;
    }
};

#endif // CLSCP_H
