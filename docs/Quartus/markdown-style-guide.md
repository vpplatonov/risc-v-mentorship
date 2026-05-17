# Markdown Style Guide

## File Structure Rules

- One topic per file.
- Keep headings shallow: `#`, `##`, `###`.
- Prefer short sections with clear names.
- Use relative links.

## Code Block Rules

Use fenced code blocks with language tags:

```bash
quartus_sh --flow compile top
```

```c
int main(void) { return 0; }
```

## Command Style

- Commands must be copy-paste ready.
- Include expected output only if useful.
- Document prerequisites before command blocks.

## Naming

- Use kebab-case for markdown file names.
- Use lowercase snake_case or kebab-case for script names.

## Recommended Section Template

```md
# Title

## Goal

## Prerequisites

## Steps

## Validation

## Troubleshooting
```

