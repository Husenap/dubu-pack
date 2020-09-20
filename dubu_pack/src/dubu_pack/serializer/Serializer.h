#pragma once

#include <cstdint>

namespace dubu_pack::serializer {

class Endian {
private:
	Endian()                       = delete;
	static constexpr uint32_t data = 0x01020304;
	static constexpr uint8_t magic = (const uint8_t)data;

public:
	static constexpr bool little = magic == 0x04;
	static constexpr bool big    = magic == 0x01;
};

template <typename T>
inline void FlipEndian(T& u) {
	union {
		T u;
		unsigned char u8[sizeof(T)];
	} source, dest;

	source.u = u;

	for (std::size_t k = 0; k < sizeof(T); ++k) {
		dest.u8[k] = source.u8[sizeof(T) - k - 1];
	}

	u = dest.u;
}

inline void Seek(std::ofstream& stream, std::streampos position) {
	stream.seekp(position);
}
inline void Seek(std::ifstream& stream, std::streampos position) {
	stream.seekg(position);
}

template <typename T>
inline T Read(std::ifstream& stream) {
	T data;
	stream.read((char*)&data, sizeof(T));
	if (Endian::big) {
		FlipEndian(data);
	}
	return data;
}

template <typename T>
inline std::streampos Write(std::ofstream& stream, T data) {
	auto position = stream.tellp();
	if (Endian::big) {
		FlipEndian(data);
	}
	stream.write((char*)&data, sizeof(T));
	return position;
}

template<>
inline std::string Read<std::string>(std::ifstream& stream) {
	std::string data;
	auto size = Read<uint32_t>(stream);
	data.resize(size);
	stream.read(&data[0], size);
	return data;
}

template<>
inline std::streampos Write<std::string>(std::ofstream& stream, std::string data) {
	auto position = stream.tellp();
	Write<uint32_t>(stream, data.size());
	stream.write(&data[0], data.size());
	return position;
}

}  // namespace dubu_pack::serializer