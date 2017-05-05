//#include "BoostSerializable.h"
//
//template <class T>
//void BoostSerializable::serialize_save(const T& obj, std::string& outString)
//{
//	stringstream binaryOut;
//	boost::archive::binary_oarchive outArchive(binaryOut);
//	outArchive << obj;
//
//	outString = binaryOut.str();
//}
//
//template <class T>
//void BoostSerializable::serialize_load(T& dataOut, const void* data, const size_t dataSize)
//{
//	const char* dataPtr = reinterpret_cast<const char*>(data);
//	std::string dataString(dataPtr, dataPtr + dataSize);
//	std::stringstream dataStream(dataString);
//	boost::archive::binary_iarchive binArchive(dataStream);
//	binArchive >> dataOut;
//}