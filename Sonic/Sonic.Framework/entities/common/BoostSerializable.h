#ifndef BOOST_SERIALIZABLE_H
#define BOOST_SERIALIZABLE_H

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class BoostSerializable
{
public:
	template <class T>
	static void serialize_save(const T& obj, std::string& outString);

	template <class T>
	static void serialize_load(T& dataOut, const void* data, const size_t dataSize);
};

#endif // !BOOST_SERIALIZABLE_H

template <class T>
inline void BoostSerializable::serialize_save(const T& obj, std::string& outString)
{
	stringstream binaryOut;
	boost::archive::binary_oarchive outArchive(binaryOut);
	outArchive << obj;

	outString = binaryOut.str();
}

template <class T>
inline void BoostSerializable::serialize_load(T& dataOut, const void* data, const size_t dataSize)
{
	const char* dataPtr = reinterpret_cast<const char*>(data);
	std::string dataString(dataPtr, dataPtr + dataSize);
	std::stringstream dataStream(dataString);
	boost::archive::binary_iarchive binArchive(dataStream);
	binArchive >> dataOut;
}
