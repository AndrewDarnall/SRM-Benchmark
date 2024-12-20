#!/bin/bash

# Directory containing the files
DIR="./images"

# Initialize iteration number
ITER=1

# Loop through all files in the directory
for FILE in "$DIR"/*; do
    # Skip if it's not a regular file
    if [[ ! -f "$FILE" ]]; then
        continue
    fi

    # Get file extension
    EXT="${FILE##*.}"

    # Generate new filename with iteration number and extension
    NEW_NAME="seg_img_${ITER}.${EXT}"

    # Rename the file
    mv "$FILE" "$DIR/$NEW_NAME"

    # Increment the iteration number
    ((ITER++))
done

echo "Renaming completed!"
