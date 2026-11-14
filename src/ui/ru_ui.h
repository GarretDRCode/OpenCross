#pragma once
// Optional UI-label dictionary supplied by a mod at ui/ru_ui.tsv.
// This translates exact interface labels only; story text and item names are left alone.
// The language is still English for the RDE text tables (e.g. a Russian mod replacing EN).
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "import/text.h"
#include "vfs/vfs.h"

namespace oc::ui::ru_ui {

inline std::unordered_map<std::string, std::string>& entries() {
  static std::unordered_map<std::string, std::string> dictionary;
  return dictionary;
}

inline void load(const vfs::Vfs& files) {
  auto& dictionary = entries();
  dictionary.clear();
  const auto bytes = files.read("ui/ru_ui.tsv");
  if (!bytes) return;
  const std::string content(reinterpret_cast<const char*>(bytes->data()), bytes->size());
  std::istringstream stream(content);
  std::string line;
  while (std::getline(stream, line)) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
    if (line.empty() || line.front() == '#') continue;
    const size_t tab = line.find('\t');
    if (tab == std::string::npos || tab == 0 || tab == line.size() - 1) continue;
    dictionary.insert_or_assign(line.substr(0, tab), line.substr(tab + 1));
  }
}

inline std::string_view utf8(std::string_view label, import::Lang lang) {
  if (lang != import::Lang::En) return label;
  const auto& dictionary = entries();
  const auto found = dictionary.find(std::string(label));
  return found == dictionary.end() ? label : std::string_view(found->second);
}

inline const char* cstr(const char* label, import::Lang lang) {
  if (lang != import::Lang::En) return label;
  const auto& dictionary = entries();
  const auto found = dictionary.find(label);
  return found == dictionary.end() ? label : found->second.c_str();
}

inline std::u32string u32(std::u32string_view label, import::Lang lang) {
  if (lang != import::Lang::En || entries().empty()) return std::u32string(label);
  const std::string source = import::u32_to_utf8(label);
  const std::string_view translated = utf8(source, lang);
  return import::utf8_to_u32(translated);
}

}  // namespace oc::ui::ru_ui
