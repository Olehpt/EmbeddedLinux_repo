#
echo "This script is about to format files form  chosen catalog by clang-format-21"
if [ $# != 1 ]; then
        echo "Error: script uses only 1 argument."
        exit 1
fi
CATALOG_PATH=$1

if [ ! -d "$CATALOG_PATH" ]; then
        echo "Error: chosen catalog does not exist."
        exit 1
fi

if [ ! -f "$CATALOG_PATH/.clang-format" ]; then
        echo "Error: failure to find .clang-format file."
        exit 1
fi

find "$CATALOG_PATH" -type f \( -name "*.c" -o -name "*.h" \) |
while read -r file; do
    clang-format-21 -i "$file"
done

echo "Done!"
exit 0
