#pragma once

#include <kodi/gui/Window.h>
#include <kodi/gui/ListItem.h>
#include <map>
#include <string>
#include <vector>

// Modal dialog: lists every backend provider with logo, name, country/state
// and a checkbox. The user toggles providers and confirms with "Apply".
//
// Skin file: resources/skins/Default/720p/DialogProviderSelect.xml
class ATTR_DLL_LOCAL CProviderSelectDialog : public kodi::gui::CWindow {
public:
  struct Entry {
    std::string name;      // backend key (used for API calls)
    std::string label;     // display name
    std::string country;
    std::string logo;      // URL or local path
    std::string state;     // idle | warming | ready | error | ""
    bool enabled = true;
  };

  explicit CProviderSelectDialog(std::vector<Entry> entries);

  // Shows the dialog modally. Returns true only if the user pressed "Apply".
  bool Run();

  // provider name -> desired enabled state (all providers, not just changed)
  std::map<std::string, bool> Result() const;

  // Control IDs - must match DialogProviderSelect.xml
  static constexpr int ID_LIST = 50;
  static constexpr int ID_TITLE = 10;
  static constexpr int ID_COUNTER = 11;
  static constexpr int ID_BTN_ALL = 201;
  static constexpr int ID_BTN_NONE = 202;
  static constexpr int ID_BTN_APPLY = 203;
  static constexpr int ID_BTN_CANCEL = 204;

protected:
  bool OnInit() override;
  bool OnClick(int controlId) override;
  bool OnAction(ADDON_ACTION actionId) override;

private:
  void FillList();
  void SetAll(bool enabled);
  void Toggle(int position);
  void UpdateCounter();

  std::vector<Entry> m_entries;
  // list position -> index into m_entries (list is shown sorted by label)
  std::vector<size_t> m_order;
  bool m_applied = false;
};
