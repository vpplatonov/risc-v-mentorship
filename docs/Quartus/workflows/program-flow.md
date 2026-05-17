# Program Flow

## Goal

Describe how bitstreams are loaded to target hardware.

## Prerequisites

- Programmer cable connected
- Correct device selected
- Built `.sof` file available

## Steps

```bash
# Example only; replace with your exact programming command flow.
quartus_pgm -l
quartus_pgm -m jtag -o "p;<path/to/output.sof>"
```

## Validation

- Device is detected
- Programming completes successfully
- Target boots expected design

