//
// Created by masa_ on 28.04.2020.
//
#include "../output_stream.h"

KNIIT_LIB_NAMESPACE {
    OutputStream::OutputStream() {
        stream = nullptr;
    }

    OutputStream::OutputStream(std::ostream* stream) {
        open(stream);
    }

    OutputStream::~OutputStream() {
        close();
    }

    bool OutputStream::open(std::ostream *stream) {
        if (stream != nullptr && stream->good()) {
            this->stream = stream;
            return true;
        }
        return false;
    }

    void OutputStream::close() {
        if (isOpen()) {
            stream->flush();
            delete stream;
        }
        stream = nullptr;
    }

    bool OutputStream::isOpen() {
        return stream != nullptr;
    }

    bool OutputStream::isClose() {
        return !isOpen();
    }

    bool OutputStream::canWrite() {
        return isOpen() && stream->good();
    }

    uintmax OutputStream::position() {
        return stream->tellp();
    }

    void OutputStream::position(uintmax position) {
        stream->seekp(position);
    }

    bool OutputStream::write(uint8_t byte) {
        if (canWrite()) {
            if (stream->opfx()) {
                stream->put(byte);
                stream->osfx();
                return true;
            }
        }

        return false;
    }

    bool OutputStream::write(uint8_t byte, uintmax position) {
        if (canWrite()) {
            uintmax prevPosition = this->position();

            this->position(position);

            if (stream->opfx()) {
                stream->put(byte);
                stream->osfx();
                this->position(prevPosition);

                return true;
            } else {
                this->position(prevPosition);
            }
        }
        return false;
    }

    bool OutputStream::write(uint8_t *bytes, uintmax length, ByteOrder byteOrder) {
        uintmax prevPosition = this->position();
        for (uintmax i = 0; i < length; i++) {
            if (!write(bytes[byteOrder == LITTLE_ENDIAN ? length - i - 1 : i])) {
                this->position(prevPosition);
                return false;
            }
        }

        return true;
    }

    OutputStream::OutputStream(OutputStream&& stream) {
        operator=(std::move(stream));
    }

    OutputStream &OutputStream::operator=(OutputStream&& stream) {
        if (this->stream != nullptr) {
            delete this->stream;
        }

        this->stream = stream.stream;
        stream.stream = nullptr;
        return *this;
    }
};
