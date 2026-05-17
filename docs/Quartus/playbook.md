# Playbook: Install Quartus Prime Lite 25.1 on macOS (Apple Silicon)

## 1. Host Prerequisites (macOS)

1. Install Parallels Desktop (Pro/Business if Rosetta passthrough is required).
2. Create Ubuntu VM (22.04 or 24.04 ARM64).
3. In VM settings, enable:
   - `Use Rosetta to run x86-64 binaries`
4. Allocate practical resources:
   - CPU/RAM according to your project size
   - Disk >= 200 GB for Quartus projects (more if combined toolchains)

Optional check on macOS host:

```bash
arch -x86_64 zsh
```

If shell starts without error, Rosetta is available.

## 2. Ubuntu VM Baseline

Install required platform packages:

```bash
sudo apt update
sudo apt install -y binfmt-support linux-modules-extra-$(uname -r) cloud-guest-utils docker.io distrobox
```

If Rosetta mount is not auto-registered:

```bash
sudo mkdir -p /media/rosetta
sudo mount -t virtiofs rosetta /media/rosetta
sudo /usr/sbin/update-binfmts --install rosetta /media/rosetta/rosetta --magic "\x7fELF\x02\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x3e\x00" --mask "\xff\xff\xff\xff\xff\xfe\xfe\x00\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xff\xff\xff" --credentials yes --fix-binary yes
sudo update-binfmts --enable rosetta
ls /proc/sys/fs/binfmt_misc/
```

## 3. Create Quartus Distrobox (amd64 userspace)

Use the helper script:

```bash
./scripts/bash/setup_quartus_container.sh quartus_prime
```

This creates `ubuntu:22.04` amd64 container and installs key runtime dependencies.

## 4. Install Quartus Lite 25.1

Inside container:

```bash
distrobox enter quartus_prime
./qinst-lite-linux-25.1std-1129.run
```

Validate:

```bash
~/altera_lite/25.1std/quartus/bin/quartus_sh --version
```

## 5. USB-Blaster Access (Ubuntu VM host, not inside container)

Install udev rules file:

```bash
sudo cp ./config/udev/51-usbblaster.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
```

In Parallels, attach USB-Blaster device to Ubuntu VM.

## 6. Optional Stability Fixes for Rosetta

If Quartus crashes with AVX/SQLite-related faults:

1. Build bridge library from `scripts/c/altr_sqlite_bridge.c`:

```bash
./scripts/bash/build_sqlite_bridge.sh ~/altera_lite/25.1std/quartus/linux64
```

2. Launch Quartus via:

```bash
./scripts/bash/start_quartus.sh
```

This script applies Java/X11/MKL guardrails and starts `jtagd`.

## 7. JTAG Validation

Inside container:

```bash
~/altera_lite/25.1std/quartus/bin/jtagconfig
```

If no hardware appears, restart daemon:

```bash
~/altera_lite/25.1std/quartus/bin/jtagd
~/altera_lite/25.1std/quartus/bin/jtagconfig
```

## 8. Daily Workflow

1. Start Ubuntu VM.
2. Enter container: `distrobox enter quartus_prime`.
3. Start Quartus: `./scripts/bash/start_quartus.sh`.
4. Build/program using CLI or GUI.

## 9. Notes

- Keep project files outside transient paths.
- If VM disk was expanded in Parallels and Ubuntu still shows old size:
  - `sudo growpart /dev/sda 2`
  - `sudo resize2fs /dev/sda2`

