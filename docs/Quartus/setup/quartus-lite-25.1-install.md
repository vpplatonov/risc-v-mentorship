# Quartus Prime Lite 25.1 Install

## Goal

Track exact installation steps for Quartus Prime Lite 25.1 in the Ubuntu guest.

## Prerequisites

- Ubuntu guest ready
- Installer archive available
- Required system libraries installed

## Install Steps

```bash
# Example only; replace with your real commands.
chmod +x ./QuartusLiteSetup-25.1.run
./QuartusLiteSetup-25.1.run
```

## Post-Install

```bash
# Example only; adjust to your install path.
quartus_sh --version
```

## Validation

- `quartus_sh --version` returns expected version
- GUI launch works if needed
- Project compilation starts without missing dependency errors

## Notes

Record any package dependencies and workarounds.

