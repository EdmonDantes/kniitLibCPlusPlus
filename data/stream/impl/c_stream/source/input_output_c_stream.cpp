/*
 *      Copyright (c). 2020. Loginov Ilya Vladislavovoich. All rights reserved.
 *      You must get permission for all action with this code or part of code from email dantes2104@gmail.com
 */
#include "../input_output_c_stream.h"
#include "../../../../../core/exception.h"

KNIIT_LIB_NAMESPACE {

	void InputOutputCStream::init(std::iostream* stream) {
		if (stream->good()) {
			stream->seekg(0);
			stream->seekp(0);
		}

		this->stream = stream;
	}

	InputOutputCStream::InputOutputCStream() {
	}

	InputOutputCStream::InputOutputCStream(InputOutputCStream&& stream) {
		operator=(std::move(stream));
	}

	InputOutputCStream::InputOutputCStream(std::iostream* stream) {
		init(stream);
	}

	InputOutputCStream::~InputOutputCStream() {
		close();
	}

	void InputOutputCStream::close() {
		if (stream != nullptr) {
			if (stream->good()) {
				stream->flush();
			}

			delete stream;
		}

		stream = nullptr;
	}

	InputOutputCStream& InputOutputCStream::operator=(InputOutputCStream&& stream) {
		close();
		init(stream.stream);
		stream.stream = nullptr;
		return *this;
	}

	bool InputOutputCStream::open(std::iostream* stream) {
		close();
		init(stream);
		return true;
	}

	bool InputOutputCStream::isOpen() const {
		return stream != nullptr && stream->good();
	}

	bool InputOutputCStream::isClose() const {
		return !isOpen();
	}

	uintmax InputOutputCStream::position() const {
		uintmax readPosition = stream->tellg();
		uintmax writePosition = stream->tellp();

		if (readPosition != writePosition) {
			throw createException2("InputOutputCStream", "Wrong read and write positions");
		}

		return readPosition;
	}

	void InputOutputCStream::position(uintmax position) {
		stream->seekp(position);
		stream->seekg(position);
	}

	bool InputOutputCStream::canRead() const {
		return isOpen();
	}

	uint8_t InputOutputCStream::read() {
		if (!canRead()) {
			throw createException2("InputOutputCStream", "Can not read byte");
		}

		return stream->get();
	}

	uint8_t InputOutputCStream::read(uintmax position) {
		uintmax startPosition = this->position();
		this->position(position);

		uint8_t result = read();

		this->position(startPosition);
		return result;
	}

	void InputOutputCStream::read(uint8_t* pointer, uintmax length) {
		for (int i = 0; i < length; i++) {
			pointer[i] = read();
		}
	}

	void InputOutputCStream::read(uint8_t* pointer, uintmax length, uintmax position) {
		uintmax startPosition = this->position();

		this->position(position);
		read(pointer, length);
		this->position(startPosition);
	}

	bool InputOutputCStream::canWrite() const {
		return isOpen();
	}

	bool InputOutputCStream::write(uint8_t& obj) {
		if (canWrite()) {
			if (stream->opfx()) {
				stream->put(obj);
				stream->osfx();
				return true;
			}
		}

		return false;
	}

	bool InputOutputCStream::write(uint8_t& obj, uintmax position) {
		uintmax startPosition = this->position();

		this->position(position);
		bool result = write(obj);
		this->position(startPosition);
		return result;
	}

	bool InputOutputCStream::write(uint8_t* obj, uintmax length) {
		uintmax startPosition = position();

		for (int i = 0; i < length; i++) {
			if (!write(obj[i])) {
				this->position(startPosition);
				return false;
			}
		}

		return true;
	}

	bool InputOutputCStream::write(uint8_t* obj, uintmax length, uintmax position) {
		uintmax startPosition = this->position();

		this->position(position);
		bool result = write(obj, length);
		this->position(startPosition);

		return result;
	}

};
