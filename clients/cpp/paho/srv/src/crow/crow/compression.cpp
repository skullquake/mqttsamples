#include"./compression.h"
namespace crow
{
    namespace compression
    {
        std::string compress_string(std::string const & str, algorithm algo)
        {
            std::string compressed_str;
            z_stream stream{};
            // Initialize with the default values
            if (::deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, algo, 8, Z_DEFAULT_STRATEGY) == Z_OK)
            {
                char buffer[8192];

                stream.avail_in = str.size();
                // zlib does not take a const pointer. The data is not altered.
                stream.next_in = const_cast<Bytef *>(reinterpret_cast<const Bytef *>(str.c_str()));

                int code = Z_OK;
                do
                {
                    stream.avail_out = sizeof(buffer);
                    stream.next_out = reinterpret_cast<Bytef *>(&buffer[0]);

                    code = ::deflate(&stream, Z_FINISH);
                    // Successful and non-fatal error code returned by deflate when used with Z_FINISH flush
                    if (code == Z_OK || code == Z_STREAM_END)
                    {
                        std::copy(&buffer[0], &buffer[sizeof(buffer) - stream.avail_out], std::back_inserter(compressed_str));
                    }

                } while (code == Z_OK);

                if (code != Z_STREAM_END)
                    compressed_str.clear();

                ::deflateEnd(&stream);
            }

            return compressed_str;
        }

        std::string decompress_string(std::string const & deflated_string)
        {
            std::string inflated_string;
            Bytef tmp[8192];

            z_stream zstream{};
            zstream.avail_in = deflated_string.size();
            // Nasty const_cast but zlib won't alter its contents
            zstream.next_in = const_cast<Bytef *>(reinterpret_cast<Bytef const *>(deflated_string.c_str()));
            // Initialize with automatic header detection, for gzip support
            if (::inflateInit2(&zstream, MAX_WBITS | 32) == Z_OK)
            {
                do
                {
                    zstream.avail_out = sizeof(tmp);
                    zstream.next_out = &tmp[0];

                    auto ret = ::inflate(&zstream, Z_NO_FLUSH);
                    if (ret == Z_OK || ret == Z_STREAM_END)
                    {
                        std::copy(&tmp[0], &tmp[sizeof(tmp) - zstream.avail_out], std::back_inserter(inflated_string));
                    }
                    else
                    {
                        // Something went wrong with inflate; make sure we return an empty string
                        inflated_string.clear();
                        break;
                    }

                } while (zstream.avail_out == 0);

                // Free zlib's internal memory
                ::inflateEnd(&zstream);
            }

            return inflated_string;
        }
    }
}
