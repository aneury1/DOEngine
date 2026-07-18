#!/usr/bin/env bash

echo "Searching for DOEngine installation..."

FILES=$(find /usr \
    \( -iname "*doengine*" -o -iname "libDOEngine*" -o -iname "libdoengine*" \) \
    2>/dev/null)

if [ -z "$FILES" ]; then
    echo "No DOEngine files found."
    exit 0
fi

echo "The following will be removed:"
echo "$FILES"

read -rp "Continue? [y/N] " ans

if [[ "$ans" =~ ^[Yy]$ ]]; then
    echo "$FILES" | while IFS= read -r file; do
        echo "Deleting: $file"
        rm -rf "$file"
    done
    echo "Done."
else
    echo "Aborted."
fi