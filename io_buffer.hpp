#pragma once

#include <cstdio>
#include <cstring>
#include <string_view>
#include <cstdarg>
#include <charconv> // Para std::to_chars (C++17)
#include <type_traits>
#include <unistd.h> // Para la syscall write

template <size_t Capacity>
class IOBuffer {
private:
    char buffer[Capacity];
    size_t offset = 0;

public:
    IOBuffer() : offset(0) {}

    IOBuffer(const IOBuffer&) = delete;
    IOBuffer& operator=(const IOBuffer&) = delete;

    // 1. Append para texto o string_view
    bool append(std::string_view sv) {
        if (offset + sv.size() > Capacity) {
            return false;
        }
        std::memcpy(buffer + offset, sv.data(), sv.size());
        offset += sv.size();
        return true;
    }

    // Sobrecarga cómoda para cadenas estilo C tradicional (const char*)
    bool append(const char* str) {
        return append(std::string_view(str));
    }

    // 2. Append polimórfico para NÚMEROS ENTEROS (int, long, uint32_t, etc.)
    template <typename T>
    std::enable_if_t<std::is_integral_v<T>, bool> append(T value) {
        // Escribe el número directamente en el espacio libre del búfer del stack
        auto [ptr, ec] = std::to_chars(buffer + offset, buffer + Capacity, value);
        
        if (ec != std::errc()) {
            return false; // Error: No hay suficiente espacio en el búfer
        }
        
        // Actualizamos el offset midiendo cuántos caracteres escribió to_chars
        offset = ptr - buffer;
        return true;
    }

    // 3. Append polimórfico para NÚMEROS FLOTANTES (float, double)
    template <typename T>
    std::enable_if_t<std::is_floating_point_v<T>, bool> append(T value) {
        auto [ptr, ec] = std::to_chars(buffer + offset, buffer + Capacity, value);
        if (ec != std::errc()) {
            return false;
        }
        offset = ptr - buffer;
        return true;
    }

    // Estilo printf tradicional (opcional, por si lo sigues queriendo)
    bool print(const char* format, ...) {
        va_list args;
        va_start(args, format);
        int written = std::vsnprintf(buffer + offset, Capacity - offset, format, args);
        va_end(args);

        if (written < 0 || static_cast<size_t>(written) >= (Capacity - offset)) {
            return false;
        }
        offset += static_cast<size_t>(written);
        return true;
    }

    // Escritura masiva final
    void flush(int fd = STDOUT_FILENO) {
        if (offset > 0) {
            // Llamada al sistema pura y dura, sin que glibc meta las manos
            ::write(fd, buffer, offset);
            offset = 0;
        }
    }

    size_t size() const { return offset; }
    constexpr size_t capacity() const { return Capacity; }
    const char* data() const { return buffer; }
};
