#!/bin/bash
echo "This script is about to check chosen catalog by clang-format-21 & clang-format-17."
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

RESULT=0

echo "==CLANG-FORMAT-21=="

find "$CATALOG_PATH" -type f \( -name "*.c" -o -name "*.h" \) |
while read -r file; do
	if clang-format-21 --style "file:$CATALOG_PATH/.clang-format" --dry-run --Werror "$file" &> /dev/null; then
		echo "OK: $file"
	else
		echo "NOT OK: $file"
		RESULT=1
	fi
done

echo
echo "==CLANG-FORMAT-17=="

find "$CATALOG_PATH" -type f \( -name "*.c" -o -name "*.h" \) |
while read -r file; do
        if clang-format-17 --style "file:$CATALOG_PATH/.clang-format" --dry-run --Werror "$file" &> /dev/null; then
                echo "OK: $file"
        else
                echo "NOT OK: $file"
		RESULT=1
        fi
done

exit $RESULT

