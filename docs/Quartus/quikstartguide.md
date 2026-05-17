# Quick Start Guide

Use these 5 steps to make this repository immediately useful for Quartus work on macOS + Parallels + Ubuntu + Rosetta.

## 1) Open the playbook

Read and follow:

- [playbook.md](./playbook.md)

This is the main install + runtime flow.

## 2) Create the Quartus container

From Ubuntu VM terminal:

```bash
cd /path/to/repo/docs/Quartus
./scripts/bash/setup_quartus_container.sh quartus_prime
```

## 3) Install Quartus Lite and verify

Inside container:

```bash
distrobox enter quartus_prime
./qinst-lite-linux-25.1std-1129.run
~/altera_lite/25.1std/quartus/bin/quartus_sh --version
```

## 4) Enable board access and launch

On Ubuntu VM host:

```bash
sudo cp ./config/udev/51-usbblaster.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
```

In container:

```bash
./scripts/bash/start_quartus.sh
```

## 5) Run first build and confirm result

Use:

- [workflows/build-flow.md](./workflows/build-flow.md)
- [workflows/program-flow.md](./workflows/program-flow.md)

Attach build evidence in:

- `./assets/images/`

