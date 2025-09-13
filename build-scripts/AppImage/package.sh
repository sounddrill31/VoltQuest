#!/bin/sh

set -eux

# Based on https://github.com/pkgforge-dev/transmission-qt-AppImage/blob/main/transmission-qt-appimage.sh

rm -rf AppDir
rm -rf *.AppImage*

ARCH="$(uname -m)"
URUNTIME="https://raw.githubusercontent.com/pkgforge-dev/Anylinux-AppImages/refs/heads/main/useful-tools/uruntime2appimage.sh"
SHARUN="https://raw.githubusercontent.com/pkgforge-dev/Anylinux-AppImages/refs/heads/main/useful-tools/quick-sharun.sh"

VERSION="main" # set to branch for now, TODO: get from git tags later or use versioning
echo "$VERSION" > ~/version

export ADD_HOOKS="self-updater.bg.hook"
# The arch package does not have icon lol
export ICON="https://raw.githubusercontent.com/transmission/transmission/refs/heads/main/icons/hicolor_apps_scalable_transmission.svg" # TODO: Change to actual voltquest icon
export DESKTOP="./build-scripts/AppImage/voltquest.desktop"
export UPINFO="gh-releases-zsync|${GITHUB_REPOSITORY%/*}|${GITHUB_REPOSITORY#*/}|latest|*$ARCH.AppImage.zsync"
export OUTNAME=VoltQuest-"$VERSION"-anylinux-"$ARCH".AppImage

# Deploy dependencies
wget --retry-connrefused --tries=30 "$SHARUN" -O ./quick-sharun
chmod +x ./quick-sharun
./quick-sharun ./build/voltquest

# MAKE APPIMAGE WITH URUNTIME
wget --retry-connrefused --tries=30 "$URUNTIME" -O ./uruntime2appimage
chmod +x ./uruntime2appimage
./uruntime2appimage

echo "All Done!"