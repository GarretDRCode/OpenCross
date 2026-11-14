# Russian_UI — optional OpenCross interface translation

This addon translates **interface labels**, not game scripts, dialogue or item names. It is designed to run beside a Russian text mod such as Cat & Mouse, which supplies the actual game text.

## Install

1. Use the OpenCross executable built from this fork's `ru-battle-results-font-fix` branch (GitHub Actions → `OpenCross Russian UI addon (Windows)` → artifact `OpenCross-RU-UI-Windows`).
2. Place `ui/ru_ui.tsv` in `<Chrono Cross game directory>/mods/Russian_UI/ui/ru_ui.tsv`.
3. In OpenCross, enable the mod `Russian_UI` in the Mods tab and set `ArtMode=modded` under `[Video]` of `opencross.ini`. Restart OpenCross if the mod was just added.
4. Keep `[Game] Language=en` when using the Russian translation of the English game strings.

To disable this addon, disable `Russian_UI` in Mods (or remove its folder), then select an art mode without it. No original translation files are changed.

## Edit or extend translations

The file `ru_ui.tsv` is UTF-8, one exact English source label, a TAB character, then its Russian equivalent per line. Comment lines begin with `#`. Changes are loaded when the overlay is applied, including at startup or after an art/mod change. An exact match is required; any unlisted label is displayed unchanged. The dictionary applies only to English-language interface rendering.

The implementation adds `src/ui/ru_ui.h` and narrowly integrates it with OpenCross UI drawing and setup. It does not translate arbitrary story text, arbitrary item names, or image-baked text.

## Limitations

- This is an initial dictionary of known interface labels. Additional captions, shop messages and uncommon screens still need visual verification.
- Some long translations may need shorter wording or additional width fitting.
- Source code compilation of the fork is required for support; simply copying `ru_ui.tsv` into an unmodified OpenCross install will not work.
