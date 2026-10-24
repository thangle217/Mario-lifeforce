# 06-Ship

This is a separate copy of sample 05. `main.cpp` calls `CGame::LoadShipGame()`, which starts scene 6 with a black background. The ship uses the four arrow keys. Each direction selects one static sprite; releasing the keys stops movement and shows the left sprite. When two perpendicular keys are held, the ship moves diagonally and the up/down sprite takes priority.

Hold `S` to fire a stream of bullets from the ship's right edge. `OnKeyDown` fires the first bullet immediately; while `S` stays down, `CShipScene::Update()` fires one bullet at most every 60 ms. Each bullet flies horizontally to the right and keeps its spawn height. Releasing `S` stops new bullets; bullets already in flight continue until they leave the screen.

One stationary monster is placed near the right side of the screen. A bullet that overlaps its hitbox removes both the bullet and the monster. The monster sprite uses `textures/life_force_enemy.png`; its rectangle in `ShipScene.cpp` is deliberately `0, 0, 0, 0` for you to fill. The temporary monster hitbox is 24 by 24 pixels in `Enemy.cpp`.

## Enter your sprite coordinates

Edit the four `sprites->Add(...)` calls in `ShipScene.cpp`:

| Sprite ID | Direction |
| --- | --- |
| 60001 | Left |
| 60002 | Right |
| 60003 | Up |
| 60004 | Down |

Each call uses `id, left, top, right, bottom, texture`. Coordinates refer to `textures/life_force.png`, start at the image's upper-left corner, and include the `right` and `bottom` pixel. For example, a 32 by 16 rectangle starting at `(20, 10)` uses `20, 10, 51, 25`. The four calls contain the coordinates you supplied.

The sprite sheet is copied from `05-SceneManager/textures`; the original is untouched. The source image may contain opaque dark tiles around its sprites. If a square is visible around the ship against the black screen, make those tile pixels transparent in the PNG.

## Run

Open `samples.sln`, choose `06-Ship` as the startup project, then build and run. The debugger working directory is set to `$(ProjectDir)` so the texture path resolves. All game configuration for this project is now in C++; its `.txt` data copies have been removed. The original Mario files remain in `05-SceneManager`.

When changing the sprite size, adjust `halfWidth` and `halfHeight` in `Ship.cpp` so the ship stops at the screen edges correctly. Change the texture path in `CGame::LoadShipGame()` and starting position in `CShipScene::Load()` as needed.

The single projectile sprite is registered in `CShipScene::Load()` at pixel rectangle `(299, 13, 301, 17)` of `life_force.png`. Edit that line to use a different projectile image. Adjust `SHOT_INTERVAL_MS` in `ShipScene.cpp` to change the spacing of the bullet stream, and `vx` in `Bullet.cpp` to change projectile speed.
