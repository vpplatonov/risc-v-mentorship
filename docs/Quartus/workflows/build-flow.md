# Build Flow

## Goal

Describe the repeatable Quartus build process.

## Inputs

- Project directory
- Top-level entity name
- Constraints files

## Steps

```bash
# Example CLI build flow.
quartus_sh --flow compile <top_entity>
```

## SoC / BSP Generation (Cyclone V / HPS)

For recent Quartus releases, `bsp-editor` may not exist as a standalone binary.
Use Platform Designer or `qsys-generate` flow instead.

### Option A: GUI (Platform Designer)

```bash
${QUARTUS_ROOT:-$HOME/altera_lite/25.1std}/quartus/sopc_builder/bin/qsys-edit
```

Then in GUI:

- Open your `.qsys` system
- Use `File -> New BSP...` or `File -> Open BSP...`

### Option B: CLI (automation-friendly)

```bash
${QUARTUS_ROOT:-$HOME/altera_lite/25.1std}/quartus/sopc_builder/bin/qsys-generate --help
```

Use `qsys-generate` with your `.qsys`/BSP configuration in CI or scripted builds.

## Outputs

- Build logs
- Timing reports
- Programming file (`.sof` / `.pof`)

## Validation

- Build exits with code 0
- Timing meets project constraints
- Output artifacts generated in expected location
- For SoC flows, BSP generation command exits with code 0
