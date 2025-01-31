#!/bin/bash
#Module 5 Assessment Solutions

# 1. Function for recursive search
search_directory() {
    local dir="$1"
    local keyword="$2"

    
    if [[ ! -d "$dir" ]]; then
        echo "Error: Directory '$dir' not found!" | tee -a errors.log
        exit 1
    fi

    echo "Searching recursively for '$keyword' in directory: $dir"

    
    grep -iRn --include="*" "$keyword" "$dir" 2>/dev/null || echo "No matches found."
}

# 2. Function to search in a file
search_file() {
    local file="$1"
    local keyword="$2"

    
    if [[ ! -f "$file" ]]; then
        echo "Error: File '$file' not found!" | tee -a errors.log
        exit 1
    fi

    echo "Searching for '$keyword' in file: $file"
    
    
    grep -i "$keyword" "$file" || echo "No matches found."
}

# 3. Function to display help menu
display_help() {
    cat <<EOF
Usage: $0 [options]
Options:
  -d <directory>   Search for a keyword recursively in a directory
  -f <file>        Search for a keyword in a specific file
  -k <keyword>     Keyword to search
  --help           Display this help menu

EOF
}

# 4. Command-line argument handling using getops
while getopts ":d:f:k:-:" opt; do
    case $opt in
        d) directory="$OPTARG" ;;
        f) file="$OPTARG" ;;
        k) keyword="$OPTARG" ;;
        -)
            case "$OPTARG" in
                help) display_help; exit 0 ;;
                *) echo "Invalid option: --$OPTARG"; exit 1 ;;
            esac ;;
        \?) echo "Invalid option: -$OPTARG"; exit 1 ;;
    esac
done

# 5. Validating inputs
if [[ -z "$keyword" ]]; then
    echo "Error: Keyword cannot be empty!" | tee -a errors.log
    exit 1
fi

if [[ -n "$directory" ]]; then
    search_directory "$directory" "$keyword"
elif [[ -n "$file" ]]; then
    search_file "$file" "$keyword"
else
    echo "Error: Missing arguments! Use --help for usage." | tee -a errors.log
    exit 1
fi
