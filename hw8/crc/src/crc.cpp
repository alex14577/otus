#include <crc/crc.h>

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>

using namespace std;
using namespace crc_alg;

size_t Crc32Calculator::GetCrc(const vector<uint8_t>& data)
{
     boost::crc_32_type crc32;
     crc32.process_bytes(reinterpret_cast<const void*>( data.data() ), data.size());
     return crc32.checksum();
}
size_t CrcMd5Calculator::GetCrc(const vector<uint8_t>& data)
{
     boost::uuids::detail::md5 md5;
     md5.process_bytes(reinterpret_cast<const void*>( data.data()), data.size());

     boost::uuids::detail::md5::digest_type digest;
     md5.get_digest(digest);
     
     size_t result = 0;
     for (int i = 0; i < 8; ++i)
     {
          result = (result << 8) | digest[i];
     }
     return result;
}
