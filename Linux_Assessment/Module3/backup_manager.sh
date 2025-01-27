#!/bin/bash
# Module 3 Assessment Solutions 

# Command-line arguments and quoting
if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <source_directory> <backup_directory> <file_extension>"
  exit 1
fi

SOURCE_DIR="$1"
BACKUP_DIR="$2"
FILE_EXT="$3"

# Checking and creating the backup directory
if [ ! -d "$BACKUP_DIR" ]; then
  mkdir -p "$BACKUP_DIR" || { echo "Failed to create backup directory."; exit 1; }
fi

# Globbing and Array Operations - Finding the files matching the extension
FILES=("$SOURCE_DIR"/*"$FILE_EXT")

# Checking if source directory contains files with the given extension
if [ ! -e "${FILES[0]}" ]; then
  echo "No files with extension '$FILE_EXT' found in '$SOURCE_DIR'."
  exit 1
fi

# Initializing BACKUP_COUNT
export BACKUP_COUNT=0
TOTAL_SIZE=0

# Displaying files to be backed up
echo "Files to be backed up:"
for FILE in "${FILES[@]}"; do
  SIZE=$(stat -c%s "$FILE")
  TIMESTAMP=$(date -r "$FILE" +"%Y-%m-%d %H:%M:%S") # last modification time
  echo "  $(basename "$FILE") - $SIZE bytes - Last Modified: $TIMESTAMP"
done

# Backup process
for FILE in "${FILES[@]}"; do
  FILENAME=$(basename "$FILE")
  DEST_FILE="$BACKUP_DIR/$FILENAME"

  # Overwriting only if source file is newer
  if [ -e "$DEST_FILE" ]; then
    if [ "$FILE" -nt "$DEST_FILE" ]; then
      cp "$FILE" "$DEST_FILE"
    fi
  else
    cp "$FILE" "$DEST_FILE"
  fi

  # Incrementing backup count and calculating total size
  ((BACKUP_COUNT++))
  TOTAL_SIZE=$((TOTAL_SIZE + $(stat -c%s "$FILE")))
done

# Output Report file generation
REPORT="$BACKUP_DIR/backup_report.log"
echo "Backup Summary:" > "$REPORT"
echo "Total files processed: $BACKUP_COUNT" >> "$REPORT"
echo "Total size of files backed up: $TOTAL_SIZE bytes" >> "$REPORT"
echo "Backup directory: $BACKUP_DIR" >> "$REPORT"
echo >> "$REPORT"


echo "File Details:" >> "$REPORT"
for FILE in "${FILES[@]}"; do
  SIZE=$(stat -c%s "$FILE")
  TIMESTAMP=$(date -r "$FILE" +"%Y-%m-%d %H:%M:%S") 
  
  echo "$(basename "$FILE") - $SIZE bytes - Last Modified: $TIMESTAMP" >> "$REPORT"
done

# Displaying report
cat "$REPORT"

exit 0

