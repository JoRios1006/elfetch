# elfetch

`elfetch` is a lightweight command-line utility inspired by `neofetch`, but focused on ELF binaries.

It reads the ELF header of a target file and prints a compact, human-readable summary including the path, byte order, architecture, file type, ABI, and a small ASCII preview.

## Features

- Validates the ELF magic bytes before parsing
- Reads key fields from an ELF64 header
- Prints a neofetch-like summary with ASCII art
- Reports architecture and OS/ABI labels when recognized
- Exits with a non-zero status for missing arguments or invalid ELF input

## Requirements

- A C++17-compatible compiler, such as `g++`
- A Unix-like environment providing `unistd.h` and `write(2)`

## Build

From the project root, compile it with:

```sh
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o elfetch
```

## Usage

Run it with the path to an ELF file:

```sh
./elfetch ./elfetch
```

Example output:

```text
\     /\     /   Target:  ./elfetch
 \. .'--`. .'    Endian:  little endian
  \\|X X |//     Arch:    AMD x86-64 architecture
   \|┌──┐|/      Type:    EXEC (Ejecutable)
    |└──┘|       OS/ABI:  Linux
     ----        Format:  ELF64 Header OK
```

If the file is not a valid ELF binary, the program prints an error and exits with status 1.

## Notes

This project is intentionally small and focused: it reads a fixed ELF64 header and interprets the most common metadata fields. It is not a full ELF parser or validator for every possible ELF variant.

The header layout is based on the System V ABI ELF header specification:

- https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html

## License

This project is licensed under the GNU Affero General Public License v3.0. See [LICENSE](LICENSE) for details.
