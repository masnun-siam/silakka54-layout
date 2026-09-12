# Silakka54 — personal layout

QWERTY on a 54-key column-staggered split. Thirty-six keys carry the whole
system; the outer columns and number row are a safety net. Arrows live on
`h j k l`, so one motion serves Vim, the browser, the pager and the pointer.

| Path | What it is |
|---|---|
| `vial/siam-silakka54.vil` | The layout. Vial → File → Load saved layout. Carries all seven layers, eight combos, and the QMK Settings. |
| `firmware/tuning.c` | Optional. Per-finger tapping terms and thumb-exempt Chordal Hold. Needs a QMK rebuild; header explains when it is worth it. |
| `karabiner/hyper.json` | Hyper + hjkl for spaces, Hyper + letter to launch apps. |
| `karabiner/travel.json` | Home-row mods and the NAV layer on a laptop keyboard, so time away from the board reinforces rather than erodes. |
| `docs/layout-reference.html` | Every layer drawn, plus the reasoning and the trade-offs. |

## Applying

Vial: load the `.vil`. It sets the Tap-Hold panel too — nothing to click after.

Karabiner: copy both JSON files into
`~/.config/karabiner/assets/complex_modifications/`, then enable the rules
under Complex Modifications.

## Key facts

- Board is **MX hotswap, 5-pin** — switches change by hand, no soldering.
- Firmware is **vial-qmk**, keyboard `silakka54`, keymap `vial`. RP2040, UF2.
- `VIAL_KEYBOARD_UID` in the `.vil` matches stock vial-qmk, so it loads clean.
- Right-hand rows are stored **reversed** in the `.vil` (outer column first).
  Worth knowing before hand-editing the JSON.

## Settings that are load-bearing

Chordal Hold **on** and Flow Tap **150** are what make home-row mods survivable
on QWERTY. Without them, `df` and `dt` misfire constantly. Quick Tap Term is
**120** so holding Backspace still repeats — at 0 it cannot.
