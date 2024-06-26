#!/bin/bash
#
echo "Checking For SDK..."
TOP=$(cd `dirname "${BASH_SOURCE[0]}"` && pwd)
if [ "${MARVELL_SDK_PATH}" = "" ]; then
	echo "Setting up SDK..."
	MARVELL_SDK_PATH="$(cd "${TOP}/../.." && pwd)"
fi
if [ "${MARVELL_ROOTFS}" = "" ]; then
	source "${MARVELL_SDK_PATH}/setenv.sh" || exit 1
fi
cd "${TOP}"

# rm -r build 2> /dev/null || echo > /dev/null
mkdir build 2> /dev/null || echo > /dev/null
mkdir build/imgui 2> /dev/null || echo > /dev/null

if [ -z "$1" ]
then
  	echo "Building NESalizer... (Release)"
	make || exit 2
else
    	echo "Building NESalizer... (Debug)"
	make CONF=DEBUG || exit 2
fi

echo "Packaging it for Steam-Link...."
export DESTDIR="${PWD}/output/nesalizer-steamlink"

rm output/nesalizer 2> /dev/null || echo > /dev/null
rm output/nesalizer-steamlink/nesalizer 2> /dev/null || echo > /dev/null
cp build/nesalizer output/nesalizer-steamlink
mv build/nesalizer output/
cd output

# Pack it up
name=$(basename ${DESTDIR})
tar zcf $name.tgz $name || exit 3
rm output/nesalizer-steamlink/nesalizer 2> /dev/null || echo > /dev/null
echo "Build Complete! Check in /output/ directory."
