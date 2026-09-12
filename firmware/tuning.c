/* Siam's Silakka54 — optional firmware tuning.
 *
 * YOU PROBABLY DO NOT NEED THIS FILE.
 *
 * siam-silakka54.vil now carries the QMK Settings too, so loading it sets the
 * whole Tap-Hold panel in one go — tapping term 170, permissive hold on,
 * quick tap term 0, Chordal Hold on, Flow Tap 150, combo term 38. Nothing to
 * click afterwards.
 *
 * Flow Tap is why this file is optional. It suppresses holds during a fast
 * typing streak: the same problem per-finger tapping terms solve, approached
 * from time-between-keys rather than which-finger. With Chordal Hold beside
 * it, that covers the ground this file was written for.
 *
 * Build this ONLY if, after living with the layout, one specific finger still
 * misfires and you want to tune that finger alone -- or if Hyper chords on the
 * left hand come out dead (see the note on get_chordal_hold below). Per-key
 * tapping terms are compile-time; no GUI setting can express them.
 *
 * ── If you do build it ───────────────────────────────────────────────────
 *     brew install qmk/qmk/qmk
 *     git clone --depth 1 https://github.com/vial-kb/vial-qmk.git ~/vial-qmk
 *     cd ~/vial-qmk && make git-submodule
 *
 *   Add to keyboards/silakka54/keymaps/vial/config.h:
 *     #define TAPPING_TERM 170
 *     #define TAPPING_TERM_PER_KEY
 *
 *   Append everything below the #include to that keymap's keymap.c (it
 *   already includes QMK_KEYBOARD_H). Its LAYOUT tables are only the
 *   power-on default — Vial overwrites them from the .vil.
 *
 *     cd ~/vial-qmk && make silakka54:vial
 *   Double-tap reset one half, it mounts as RPI-RP2, then:
 *     cp ~/vial-qmk/silakka54_vial.uf2 /Volumes/RPI-RP2/
 *   Repeat for the other half. Flashing clears the keymap, so re-load
 *   siam-silakka54.vil afterwards, not before.
 */
#include QMK_KEYBOARD_H

/* Per-finger terms. A pinky commits to a hold far slower than an index finger,
 * so one global number is always wrong for one end of the hand. */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F): case RSFT_T(KC_J):    return 150;  /* index  — Shift */
        case LGUI_T(KC_D): case RGUI_T(KC_K):    return 160;  /* middle — Cmd   */
        case LALT_T(KC_S): case RALT_T(KC_L):    return 180;  /* ring   — Alt   */
        case LCTL_T(KC_A): case RCTL_T(KC_SCLN): return 220;  /* pinky  — Ctrl  */
        default:                                 return TAPPING_TERM;
    }
}

/* Chordal Hold: a mod-tap only resolves as a hold when the other key is on the
 * opposite half. This is what lets `df`, `dt` and `sd` type as plain letters.
 *
 * Handedness comes straight from the matrix: the Silakka54 keymap stores rows
 * 0-4 as the left half and 5-9 as the right, so the row index IS the hand. */
static inline bool slk_is_left(keypos_t key)  { return key.row < 5; }
static inline bool slk_is_thumb(keypos_t key) { return key.row == 4 || key.row == 9; }

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                      uint16_t other_keycode,    keyrecord_t *other_record) {
    /* Thumbs are exempt. Hyper lives on the left inner thumb and most Hyper
     * chords land on the left hand, so applying the handedness rule here would
     * silently swallow half of them. Thumbs do not misfire the way home-row
     * mods do -- they are never in a typing roll -- so there is nothing to
     * protect against. This is the standard '*' wildcard from QMK's
     * chordal_hold_layout idiom, expressed in code. */
    if (slk_is_thumb(tap_hold_record->event.key)) return true;

    return slk_is_left(tap_hold_record->event.key)
        != slk_is_left(other_record->event.key);
}
