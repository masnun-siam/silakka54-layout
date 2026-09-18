# Silakka54 — personal layout

**[Open the layout reference](docs/index.html)** — every layer drawn, with the reasoning.

QWERTY on a 54-key column-staggered split. Thirty-six keys carry the whole
system; the outer columns and number row are a safety net. Arrows live on
`h j k l`, so one motion serves Vim, the browser, the pager and the pointer.

| Path | What it is |
|---|---|
| `vial/siam-silakka54.vil` | The layout. Vial → File → Load saved layout. Carries all seven layers, eleven combos, two macros, and the QMK Settings. |
| `kanata/silakka54-travel.kbd` | The same layout on every *other* keyboard — home-row mods plus NAV/SYM/NUM. Time on a laptop reinforces the muscle memory instead of eroding it. |
| `kanata/dev.kanata.kanata.plist` | LaunchDaemon so kanata starts at boot. |
| `docs/index.html` | Every layer drawn, plus the reasoning and the trade-offs. Open it in a browser. |

## Applying

Vial: load the `.vil`. It sets the Tap-Hold panel too — nothing to click after.

kanata, for every other keyboard:

```sh
brew install kanata
kanata -c kanata/silakka54-travel.kbd --check     # validate before installing
sudo mkdir -p /etc/kanata && sudo cp kanata/silakka54-travel.kbd /etc/kanata/
sudo cp kanata/dev.kanata.kanata.plist /Library/LaunchDaemons/
sudo chown root:wheel /Library/LaunchDaemons/dev.kanata.kanata.plist
sudo launchctl bootstrap system /Library/LaunchDaemons/dev.kanata.kanata.plist
```

`sudo launchctl kickstart -k system/dev.kanata.kanata` reloads after a config
edit; `bootout` uninstalls. Logs at `/var/log/kanata.log`.

**Escape hatch:** hold **LeftCtrl + Space + Escape** (physical keys, before
remapping) to kill kanata if the config ever misbehaves.

## kanata

`Space` holds NAV, `Tab` holds SYM, `Caps` holds NUM — and `Caps` taps as
Escape, which is more than it did before. Home-row mods are the same CAGS
order as the board.

`defhands` + `tap-hold-opposite-hand` is kanata's equivalent of Chordal Hold:
a modifier engages only when the other key is on the other hand, so `df` and
`jk` type as letters. This is the one thing Karabiner could not do, and the
reason this config replaces it.

Two things it does **not** free you from:

- **Karabiner's DriverKit driver stays.** kanata grabs the keyboard through
  `Karabiner-DriverKit-VirtualHIDDevice`. The Karabiner-Elements *app* is gone;
  the driver is the pipe kanata writes through. kanata `v1.12.0` (installed here)
  pairs with driver **`v6.2.0`**; `v1.13.0+` needs **`v8.0.0`**. Upgrade both
  together or kanata loops on `connect_failed asio.system:2`.
- **Root.** The virtual HID daemon's IPC lives under a root-only path, so the
  daemon runs as root.

The device exclude list names kanata's own virtual keyboard **including its
version number**. Re-check it with `kanata --list` after any driver update — a
stale string there silently reopens a feedback loop.

## Key facts

- Board is **MX hotswap, 5-pin** — switches change by hand, no soldering.
- Firmware is **vial-qmk**, keyboard `silakka54`, keymap `vial`. RP2040, UF2.
- `VIAL_KEYBOARD_UID` in the `.vil` matches stock vial-qmk, so it loads clean.
- Right-hand rows are stored **reversed** in the `.vil` (outer column first).
  Worth knowing before hand-editing the JSON.

## Settings that are load-bearing

Chordal Hold **on** and Flow Tap **150** are what make home-row mods survivable
on QWERTY. Without them, `df` and `dt` misfire constantly. Tapping term is
**250 ms**. Quick Tap Term is **120** so holding Backspace still repeats — at 0 it cannot.

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
