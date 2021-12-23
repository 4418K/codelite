#include "clThemeUpdater.h"

#include "clSystemSettings.h"
#include "codelite_events.h"
#include "event_notifier.h"
#include "file_logger.h"
#include "globals.h"

#include <algorithm>

clThemeUpdater::clThemeUpdater()
{
    EventNotifier::Get()->Bind(wxEVT_CMD_COLOURS_FONTS_UPDATED, &clThemeUpdater::OnColoursAndFontsChanged, this);
}

clThemeUpdater::~clThemeUpdater()
{
    EventNotifier::Get()->Unbind(wxEVT_CMD_COLOURS_FONTS_UPDATED, &clThemeUpdater::OnColoursAndFontsChanged, this);
}

clThemeUpdater& clThemeUpdater::Get()
{
    static clThemeUpdater updater;
    return updater;
}

void clThemeUpdater::OnColoursAndFontsChanged(clCommandEvent& e)
{
    e.Skip();
    CallAfter(&clThemeUpdater::UpdateGlobalColours);
}

void clThemeUpdater::UpdateGlobalColours()
{
#if 0
    std::for_each(m_windows.begin(), m_windows.end(), [&](wxWindow* win) {
        win->SetBackgroundColour(clSystemSettings::GetDefaultPanelColour());
        win->SetForegroundColour(clSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
        win->Refresh();
    });
#endif
}

void clThemeUpdater::RegisterWindow(wxWindow* win)
{
    if(!win) {
        clWARNING() << "clThemeUpdater::RegisterWindow(): Registering nullptr window!" << clEndl;
        return;
    }

    if(m_windows.count(win)) {
        clWARNING() << "clThemeUpdater::RegisterWindow(): Registering the same window twice. ignored" << clEndl;
        return;
    }

    // we want to know when this window is destroyed so we could remove it
#ifdef __WXMSW__
    win->Bind(wxEVT_DESTROY, &clThemeUpdater::OnWindowDestroyed, this);
    win->SetBackgroundColour(clSystemSettings::GetDefaultPanelColour());
    win->SetForegroundColour(clSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
#endif
    m_windows.insert(win);
}

void clThemeUpdater::UnRegisterWindow(wxWindow* win)
{
    if(m_windows.count(win)) {
        // disconnect the destory event
#ifdef __WXMSW__
        win->Unbind(wxEVT_DESTROY, &clThemeUpdater::OnWindowDestroyed, this);
#endif
        m_windows.erase(win);
    }
}

void clThemeUpdater::OnWindowDestroyed(wxWindowDestroyEvent& event)
{
    event.Skip();
    auto iter = m_windows.find(event.GetWindow());
    if(iter != m_windows.end()) {
        m_windows.erase(iter);
    }
}
