//
// Created by masa_ on 28.04.2020.
//
#include "../output_c_stream.h"

KNIIT_LIB_NAMESPACE {
    OutputCStream::OutputCStream() {
        stream = nullptr;
    }

    OutputCStream::OutputCStream(OutputCStream&& stream) {
        operator=(std::move(stream));
    }

    OutputCStream::OutputCStream(std::ostream* stream) {
        open(stream);
    }

    OutputCStream& OutputCStream::operator=(OutputCStream&& stream) {
        if (this->stream != nullptr) {
            delete this->stream;
        }

        this->stream = stream.stream;
        stream.stream = nullptr;
        return *this;
    }

    OutputCStream::~OutputCStream() {
        close();
    }

    bool OutputCStream::open(std::ostream* stream) {
        close();
        if (stream != nullptr && stream->good()) {
            this->stream = stream;
            return true;
        }
        return false;
    }

    void OutputCStream::close() {
        if (isOpen()) {
            stream->flush();
            delete stream;
        }
        stream = nullptr;
    }

    bool OutputCStream::isOpen() const {
        return stream != nullptr;
    }

    bool OutputCStream::isClose() const {
        return !isOpen();
    }

    bool OutputCStream::canWrite() const {
        return isOpen() && stream->good();
    }

    uintmax OutputCStream::position() const {
        return stream->tellp();
    }

    void OutputCStream::position(uintmax position) {
        stream->seekp(position);
    }

    bool OutputCStream::write(uint8_t& byte) {
        if (canWrite()) {
            if (stream->opfx()) {
                stream->put(byte);
                stream->osfx();
                return true;
            }
        }

        return false;
    }


    bool OutputCStream::write(uint8_t& byte, uintmax position) {
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

    bool OutputCStream::write(uint8_t* bytes, uintmax length) {
        uintmax prevPosition = this->position();
        for (uintmax i = 0; i < length; i++) {
            if (!write(bytes[i])) {
                this->position(prevPosition);
                return false;
            }
        }

        return true;
    }

    bool OutputCStream::write(uint8_t* obj, uintmax length, uintmax position) {
        return false;
    }
};
