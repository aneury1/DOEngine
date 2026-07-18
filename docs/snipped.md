##### Declaration of PTR

```cpp
\b[\w:<>]+\s*\*+\s*\w+\b

\b(?:const\s+)?[\w:<>]+\s*(?:const\s+)?\*+\s*\w+\b
```

#### Delete SDL2 from or Sample how to delete pacman packanges
```
sudo pacman -Rns $(pacman -Qq | grep '^sdl2')
```

##### Delete Doengine

```sh
echo "Searching for DOEngine files under /usr..."

find /usr \
    \( -iname "*doengine*" -o -iname "libDOEngine*" -o -iname "libdoengine*" \) \
    2>/dev/null

echo "Deleting DOEngine files..."

find /usr \
    \( -iname "*doengine*" -o -iname "libDOEngine*" -o -iname "libdoengine*" \) \
    -exec rm -rf {} + \
    2>/dev/null
```