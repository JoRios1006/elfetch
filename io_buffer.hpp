#pragma once

#include <cstdio>
#include <cstring>
#include <string_view>
#include <cstdarg>

template <size_t Capacity>
class IOBuffer {
private:
    char buffer[Capacity];
    size_t offset = 0;

public:
    IOBuffer() : offset(0) {}

    // No se permite copiar para evitar duplicar búferes del stack por error
    IOBuffer(const IOBuffer&) = delete;
    IOBuffer& operator=(const IOBuffer&) = delete;

    // Agregar texto plano o string_view
    bool append(std::string_view sv) {
        if (offset + sv.size() > Capacity) {
            return false; // Desbordamiento evitado
        }
        std::memcpy(buffer + offset, sv.data(), sv.size());
        offset += sv.size();
        return true;
    }

    // Estilo printf seguro directamente en el stack
    bool print(const char* format, ...) {
        va_list args;
        va_start(args, format);
        int written = std::vsnprintf(buffer + offset, Capacity - offset, format, args);
        va_end(args);

        if (written < 0 || static_cast<size_t>(written) >= (Capacity - offset)) {
            return false; // No hay espacio suficiente
        }
        offset += static_cast<size_t>(written);
        return true;
    }

    // Escritura masiva final (una sola llamada al sistema)
    void flush(FILE* stream = stdout) {
        if (offset > 0) {
            std::fwrite(buffer, 1, offset, stream);
            std::fflush(stream);
            offset = 0; // Reiniciamos el puntero monotónico (opcional)
        }
    }

    // Consultas útiles
    size_t size() const { return offset; }
    constexpr size_t capacity() const { return Capacity; }
    const char* data() const { return buffer; }
};
