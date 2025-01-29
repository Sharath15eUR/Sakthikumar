#!/bin/bash

# Checking if the input file is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

INPUT_FILE="$1"
OUTPUT_FILE="output.txt"

# Ensuring the output file is empty before writing new content
> "$OUTPUT_FILE"

# Reading file line by line and extract required parameters
while IFS= read -r line; do
    if [[ $line == *'"frame.time"'* ]]; then
        frame_time=$(echo "$line" | awk -F': ' '{print $2}' | tr -d '",')
        echo "\"frame.time\": \"$frame_time\"" >> "$OUTPUT_FILE"
    elif [[ $line == *'"wlan.fc.type"'* ]]; then
        fc_type=$(echo "$line" | awk -F': ' '{print $2}' | tr -d '",')
        echo "\"wlan.fc.type\": \"$fc_type\"" >> "$OUTPUT_FILE"
    elif [[ $line == *'"wlan.fc.subtype"'* ]]; then
        fc_subtype=$(echo "$line" | awk -F': ' '{print $2}' | tr -d '",')
        echo "\"wlan.fc.subtype\": \"$fc_subtype\"" >> "$OUTPUT_FILE"
        echo "" >> "$OUTPUT_FILE"  # Add a blank line for separation
    fi
done < "$INPUT_FILE"

echo "Extraction completed. Output saved to $OUTPUT_FILE."
