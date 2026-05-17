# Known Issues

## Purpose

Track reproducible issues, root causes, and fixes.

## Template

## Issue: <short title>

- Symptom:
- Context:
- Root cause:
- Resolution:
- Verification:

## Issue: Quartus command not found

- Symptom: `quartus_sh: command not found`
- Context: New shell session
- Root cause: PATH not set for Quartus binaries
- Resolution: Export Quartus bin path in shell profile
- Verification: `quartus_sh --version` succeeds

