# elfetch

`elfetch` is a small command-line utility that displays a quick summary of an ELF file's header—like `neofetch`, but for ELF files.

It checks the ELF magic bytes and prints the target path, byte order, architecture, file type, and OS/ABI alongside a small piece of ASCII art.

## Requirements

- A C++17-compatible compiler (for example, `g++`)
- Linux or another environment that provides `unistd.h` and `write(2)`

## Build

From the repository directory, compile the program with:

```sh
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o elfetch
```

## Usage

Pass the path to an ELF file as the first argument:

```sh
./elfetch /bin/ls
```

The output includes fields like:

- **Target** — the path you supplied
- **Endian** — little- or big-endian encoding
- **Arch** — a recognized machine architecture, when available
- **Type** — such as relocatable, executable, shared object, or core file
- **OS/ABI** — a recognized ABI identifier, when available
- **Format** — the program's current ELF header status label

If the file does not have the ELF magic bytes, `elfetch` prints an error and exits with a non-zero status. Run it without a file argument and it exits with a non-zero status.

## Notes

This is an early, minimal ELF-header inspector. It reads a fixed-size header and currently interprets its fields using an ELF64 header layout; it is not a complete ELF validator or a general-purpose binary analysis tool. Architecture and OS/ABI names not covered by its lookup tables are reported as reserved or unknown.

## ELF header reference

The header fields and identification bytes are described in the [System V ABI: ELF Header](https://refspecs.linuxfoundation.org/elf/gabi4+/ch4.eheader.html).

## License

This project is licensed under the GNU Affero General Public License v3.0. See [LICENSE](LICENSE) for details.
