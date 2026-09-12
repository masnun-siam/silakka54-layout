# Silakka54 — personal layout

**[Open the layout reference](docs/index.html)** — every layer drawn, with the reasoning.

QWERTY on a 54-key column-staggered split. Thirty-six keys carry the whole
system; the outer columns and number row are a safety net. Arrows live on
`h j k l`, so one motion serves Vim, the browser, the pager and the pointer.

| Path | What it is |
|---|---|
| `vial/siam-silakka54.vil` | The layout. Vial → File → Load saved layout. Carries all seven layers, eight combos, and the QMK Settings. |
| `karabiner/travel.json` | Home-row mods and the NAV layer on a laptop keyboard, so time away from the board reinforces rather than erodes. |
| `docs/index.html` | Every layer drawn, plus the reasoning and the trade-offs. Open it in a browser. |

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

## Hyper

The left inner thumb taps Tab and holds Hyper (⌘⌃⌥⇧). Nothing listens to it
yet — bind it in whichever app you prefer.

One behaviour to know: Chordal Hold forces a same-hand chord to tap when the
second key lands inside the tapping term. Hyper is a left thumb, so a *fast*
Hyper + left-hand-letter roll can come out as Tab plus that letter. Holding
Hyper deliberately is enough to avoid it — Chordal Hold has no effect once the
tapping term has passed. If fast same-hand chords ever matter, a `get_chordal_hold()`
that exempts the thumb rows fixes it; see `git log` for the version that had one.

Avoid `Hyper + J K L ;` regardless — those are right-hand mod-taps, so an
opposite-hand hold is permitted and a long press sends a modifier, not a letter.
