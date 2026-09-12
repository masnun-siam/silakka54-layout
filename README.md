# Silakka54 — personal layout

QWERTY on a 54-key column-staggered split. Thirty-six keys carry the whole
system; the outer columns and number row are a safety net. Arrows live on
`h j k l`, so one motion serves Vim, the browser, the pager and the pointer.

| Path | What it is |
|---|---|
| `vial/siam-silakka54.vil` | The layout. Vial → File → Load saved layout. Carries all seven layers, eight combos, and the QMK Settings. |
| `firmware/tuning.c` | **Required if you use Hyper.** Exempts the thumbs from Chordal Hold; without it every left-hand Hyper binding is dead. Also carries per-finger tapping terms, which are the optional part. |
| `karabiner/hyper.json` | Rectangle window management, CleanShot X capture, spaces and displays — all on Hyper. |
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

## Hyper map

Bottom row mirrors the NAV row that sits under `hjkl`, so window halves land
where page-jumps already live. Top row goes one level bigger: displays and
spaces. Left hand is CleanShot X.

| | | | |
|---|---|---|---|
| `Y` prev display | `U` space left | `I` space right | `O` next display |
| `N` left half | `M` bottom half | `,` top half | `.` right half |
| `H` center | `/` maximize | `B` almost max | `V` restore |
| `S` capture area | `R` record | `A` all-in-one | `W` window |
| `F` fullscreen | `T` OCR | `G` scrolling | `D` history |

`firmware/tuning.c` must be flashed for any of the left-hand bindings to fire.
Hyper is a left thumb, so without the thumb exemption Chordal Hold forces it to
resolve as a tap whenever the next key is also on the left.

**Never bind Hyper to `J`, `K`, `L` or `;`.** Those are right-hand mod-taps and
Hyper is a left thumb, so Chordal Hold permits the hold — a slightly long press
sends a modifier instead of the letter. `A S D F` are safe: same hand as the
Hyper thumb, so Chordal Hold forces them to tap. `H` is safe too, it is not a mod.

**Raycast** is not in here on purpose. Set it to `Opt+Space` inside Raycast
itself: right-hand Alt on `L` plus the left Space thumb is bilateral, so it is
one of the most reliable chords on the board. Once Raycast is that close,
per-app Hyper launch keys stop earning their place.
