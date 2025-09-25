#!/bin/sh

PROBLEM=$1
EXTENSION="c"

while [ $# -gt 0 ]; do
  case $1 in
    -e|--extension)
      EXTENSION="$2"
      shift
      shift
      ;;
    *)
      shift
      ;;
  esac
done

if [ -z $PROBLEM ]; then
  echo "Choose a problem to run:"
  FILE=$(gum choose $(ls . | grep -E '[0-9]+'))
else
  FILE=$PROBLEM
fi

case $EXTENSION in
  "c")
    gcc -Wall -Wextra -o "dist/$FILE" "$FILE/$FILE.c" -lm;;
  "cc")
    g++ -Wall -Wextra -o "dist/$FILE" "$FILE/$FILE.cc" -lm;;
esac

if [ $? -ne 0 ]; then
  gum log --time="TimeOnly" --structured --level error "Compilation failed for $FILE.$EXTENSION"
  exit 1
else
  gum style \
    --foreground 212 --border-foreground 212 --border double \
    --align center --width 40 \
    'Compiled successfully! 🎉' "Running $FILE.$EXTENSION"
  dist/$FILE
fi

