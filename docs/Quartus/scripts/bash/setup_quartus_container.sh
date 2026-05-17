#!/usr/bin/env bash
set -euo pipefail

CONTAINER_NAME="${1:-quartus_prime}"

echo "[1/3] Creating amd64 distrobox container: ${CONTAINER_NAME}"
distrobox create --name "${CONTAINER_NAME}" --image ubuntu:22.04 --additional-flags "--platform linux/amd64"

echo "[2/3] Installing Quartus runtime dependencies inside container"
distrobox enter "${CONTAINER_NAME}" -- bash -lc '
  sudo apt update
  sudo apt install -y \
    libxext6 libxrender1 libxtst6 libxi6 libfreetype6 libfontconfig1 \
    libncurses5 libtinfo5 libxft2 libxss1 libxaw7 libglib2.0-0 \
    libcanberra-gtk-module libcanberra-gtk3-module tk8.6 libtk8.6 \
    build-essential gcc binutils locales file usbutils
'

echo "[3/3] Container setup complete"
echo "Next: distrobox enter ${CONTAINER_NAME}"

