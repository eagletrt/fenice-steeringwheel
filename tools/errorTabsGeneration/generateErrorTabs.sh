#! /usr/bin/sh

if [ ! -d .git ]
then
    echo "[!] Please run this script from the root of the repository"
    exit 1
fi

cd tools/errorTabsGeneration

if [ -d ./newErrors ]
then
    rm -r newErrors
fi
mkdir newErrors

cp SampleErrorEntry.qml newErrors/ErrorEntry.qml

if ! command -v deno &> /dev/null
then
    echo "[!] Deno runtime environment is not installed."
    echo "[!] Please install it to run this script."
    exit 1
fi

echo "Generating error entries using errors.txt..."
deno run --allow-read --allow-write parse.ts errors.txt
echo "Done generating error entries."

cd ../..

if [ -d  ./qml/tabs/errors ]
then
    rm -r qml/tabs/errors
fi
mv tools/errorTabsGeneration/newErrors qml/tabs/errors

./tools/fmt
