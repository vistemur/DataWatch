# DataWatch 

local console databese for overwatch players and teams

## Trailer

https://github.com/user-attachments/assets/31a84bc0-707f-47a1-b5b2-41670658469b

## Compile & run ⚙️ 🔨

use Makefile to compile

```console
make
```

and then run

```console
./DataWatch
```

## Usage 🎨

Main menu

```console
enter option:
1 - print all teams
2 - add team
3 - delete team
4 - choose team
5 - exit
option:
```

enter number from 1 to 5 to select

add team example

```console
option: 2

enter team's name: easy win
add leader...
leader nickname: nagibator
leader current rating = 3500
leader max rating = 4000
leader role (1 - healer, 2 - dps, 3 - tank, 4 - flex): 3
add player? (1 - yes, 2 - no)
1
player 1 nickname: loshara
player 1 current rating = 1000
player 1 max rating = 1200
player 1 role (1 - healer, 2 - dps, 3 - tank, 4 - flex): 2
add another player? (1 - yes, 2 - no)
1
player 2 nickname: noCheats
player 2 current rating = 1500
player 2 max rating = 3500
player 2 role (1 - healer, 2 - dps, 3 - tank, 4 - flex): 4
add another player? (1 - yes, 2 - no)
1
player 3 nickname: 2
player 3 current rating = 0
player 3 max rating = 0
player 3 role (1 - healer, 2 - dps, 3 - tank, 4 - flex): 1
add another player? (1 - yes, 2 - no)
2
```

print will be:

```console
option: 1

Team name: easy win
Team rating: 1500
Team id: 0
+----------------+------+------+------+
|    nickname    | max  | cur  | role |
+----------------+------+------+------+
| nagibator      | 4000 | 3500 | tank |
+----------------+------+------+------+
| noCheats       | 3500 | 1500 | flex |
+----------------+------+------+------+
| loshara        | 1200 | 1000 | dps  |
+----------------+------+------+------+
| 2              |    0 |    0 | heal |
+----------------+------+------+------+
```

configure team (delete player example)

```console
option: 4

enter choose option:
1 - choose with id
2 - choose with name
option: 1
enter team id: 0

Team name: easy win
Team rating: 1500
Team id: 0
+----------------+------+------+------+
|    nickname    | max  | cur  | role |
+----------------+------+------+------+
| nagibator      | 4000 | 3500 | tank |
+----------------+------+------+------+
| noCheats       | 3500 | 1500 | flex |
+----------------+------+------+------+
| loshara        | 1200 | 1000 | dps  |
+----------------+------+------+------+
| 2              |    0 |    0 | heal |
+----------------+------+------+------+

enter choose option:
1 - print team
2 - add player
3 - delete player
4 - make new leader
5 - change team name
6 - choose player
7 - back
option: 3

Team name: easy win
Team rating: 1500
Team id: 0
+----------------+------+------+------+
|    nickname    | max  | cur  | role |
+----------------+------+------+------+
| nagibator      | 4000 | 3500 | tank |
+----------------+------+------+------+
| noCheats       | 3500 | 1500 | flex |
+----------------+------+------+------+
| loshara        | 1200 | 1000 | dps  |
+----------------+------+------+------+
| 2              |    0 |    0 | heal |
+----------------+------+------+------+

enter choose option:
1 - delete player with id
2 - delete player with nickname
3 - back
option: 1

nagibator                      - 0
noCheats                       - 1
loshara                        - 2
2                              - 3

enter player id: 3

2 has been deleted

Team name: easy win
Team rating: 1500
Team id: 0
+----------------+------+------+------+
|    nickname    | max  | cur  | role |
+----------------+------+------+------+
| nagibator      | 4000 | 3500 | tank |
+----------------+------+------+------+
| noCheats       | 3500 | 1500 | flex |
+----------------+------+------+------+
| loshara        | 1200 | 1000 | dps  |
+----------------+------+------+------+
```
