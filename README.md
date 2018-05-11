# Keyer7

Ever since I first saw the
[microwriter](https://en.wikipedia.org/wiki/Microwriter), I have been
fascinated by chorded keyboards: single handed keyboards with a handful
(literally) of keys where instead of pressing one key at a time, you press
a "chord" (several keys) to select each letter.

Now that low cost Bluetooth LE devices like the [Adafruit
NRF52](https://www.adafruit.com/product/3406) are cheap and
easy to program, there really was no excuse not to build one.

## Keymap

The keymap is based on the ["modified NASA" keymap](https://chorder.cs.vassar.edu/doku.php?id=spiffchorder:modified_nasa:chart_alphanumeric_keys) as described in the following tables.

### Alphabet

| Keys | Thumb |       |
| ---- | ----- | ----- |
| -RMI | -C-   |  a    |
| P--I | ---   |  b    |
| --M- | -C-   |  c    |
| --MI | ---   |  d    |
| -RMI | ---   |  e    |
| P--- | -C-   |  f    |
| -R-- | -C-   |  g    |
| -RM- | ---   |  h    |
| ---I | ---   |  i    |
| -R-I | -C-   |  j    |
| -R-I | ---   |  k    |
| ---I | -C-   |  l    |
| --MI | -C-   |  m    |
| PRM- | -C-   |  n    |
| PRMI | -C-   |  o    |
| -RM- | -C-   |  p    |
| PR-I | -C-   |  q    |
| --M- | ---   |  r    |
| PRM- | ---   |  s    |
| PRMI | ---   |  t    |
| PR-- | ---   |  u    |
| PR-- | -C-   |  v    |
| P--- | ---   |  w    |
| P--I | -C-   |  x    |
| -R-- | ---   |  y    |
| PR-I | ---   |  z    |
| ---- | -C-   |  spc  |

### With N key

| Keys | Thumb |        |   |
| ---- | ----- | ------ | - |
| PR-- | N--   | ;      | : |
| --M- | N--   | ,      | < |
| -RM- | N--   | .      | > |
| -RMI | N--   | '      | " |
| -R-- | N--   | esc    |   |
| PRM- | N--   | alt    |   |
| PR-I | N--   | ctrl   |   |
| P--- | N--   | fnc    |   |
| PRMI | N--   | numl   |   |
| P--I | N--   | ins    |   |
| ---- | NCF   | qwerty |   |
| ---- | N-F   | dvorak |   |

### With N-prefix

| Keys | Thumb |   | F  | hint |
| ---- | ----- | - | -- | ---- |
| ---- | -C-   | 1 | !  |      |
| ---I | ---   | 2 | @  |      |
| --M- | ---   | 3 | #  |      |
| -R-- | ---   | 4 | $  |      |
| P--- | ---   | 5 | %  |      |
| ---I | -C-   | 6 | ^  |      |
| --M- | -C-   | 7 | *  |      |
| -R-- | -C-   | 8 | *  |      |
| P--- | -C-   | 9 | (  |      |
| PRMI | -C-   | 0 | )  |      |
| -RMI | -C-   | + |    | a    |
| P--I | ---   | \ | \| | b    |
| --MI | ---   | / | ?  | d    |
| -RMI | ---   | = | +  | e    |
| -R-I | ---   | $ |    | k    |
| --MI | -C-   | * |    | m    |
| PRM- | -C-   | [ | {  | n    |
| PR-- | -C-   | ] | }  | v    |
| -RM- | -C-   | % |    | p    |
| PR-I | -C-   | ? |    | q    |
| PRM- | ---   | - | _  | s    |
| P--I | -C-   | & |    | x    |
| PR-I | ---   | ` | ~  | z    |

### With F key

| Keys | Thumb |      | F>CF    |
| ---- | ----- | ---- | ------- |
| PRMI | NC-   | kpl  |         |
| P--- | --F   | ret  | kp ret  |
| ---- | --F   | lshf | kp +    |
| PRMI | --F   | caps | kp ins  |
| -R-I | --F   | tab  | kp -    |
| --M- | --F   | bksp | kp beg  |
| -RM- | --F   | del  | kp del  |
| P-MI | --F   | sclk | kp /    |
| P-M- | --F   | ptsc | kp *    |
| -R-- | --F   | rght | kp rght |
| PR-- | --F   | down | kp down |
| PRM- | --F   | pgdn | kp pgdn |
| ---I | --F   | left | kp left |
| --MI | --F   | up   | kp up   |
| -RMI | --F   | pgup | kp pgup |
| PR-I | --F   | home | kp home |
| P--I | --F   | end  | kp end  |
| ---- | N-F   | brk  |         |
| ---- | NCF   | rst  |         |

