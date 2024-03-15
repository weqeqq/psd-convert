extern "C" {

#include <psd_buffer.h>
#include <psd_conversion.h>
#include <psd_header.h>
#include <psd_types.h>
}

#include <gtest/gtest.h>

using namespace std;

TEST(conversion, bytep_to_bytepp)
{
        const psd_size_t WIDTH = 3, HEIGHT = 6, CHANNELS = 1;

        psd_byte_t *bufferp, **buferpp, **expected;
        psd_header_t header;
        psd_byte_t **bufferpp;
        int buffereq;

        psd_assign_bufferp(bufferp, HEIGHT * WIDTH,
                           {1, 0, 0,   //
                            0, 1, 0,   //
                            0, 0, 1,   //
                            1, 0, 0,   //
                            0, 1, 0,   //
                            0, 0, 1}); //

        psd_assign_bufferpp(expected, HEIGHT, WIDTH,
                            {1, 0, 0,   //
                             0, 1, 0,   //
                             0, 0, 1,   //
                             1, 0, 0,   //
                             0, 1, 0,   //
                             0, 0, 1}); //

        header.width = WIDTH;
        header.height = HEIGHT;
        header.channels = CHANNELS;

        bufferpp = bytep_to_bytepp_with_free(&header, bufferp);

        buffereq = 1;
        for (psd_size_t i = 0; i < HEIGHT; ++i) {
                if (memcmp(bufferpp[i], expected[i], WIDTH)) {
                        buffereq = 0;
                        break;
                }
        }

        for (psd_size_t i = 0; i < HEIGHT; ++i) {
                free(bufferpp[i]);
                free(expected[i]);
        }

        free(bufferpp);
        free(expected);

        ASSERT_TRUE(buffereq);
}

TEST(conversion, bytepp_to_bytep)
{
        const psd_size_t WIDTH = 3, HEIGHT = 6, CHANNELS = 1;

        psd_byte_t *bufferp, **bufferpp, *expected;
        psd_header_t header;
        int buffereq;

        psd_assign_bufferpp(bufferpp, HEIGHT, WIDTH,
                            {1, 0, 0,   //
                             0, 1, 0,   //
                             0, 0, 1,   //
                             1, 0, 0,   //
                             0, 1, 0,   //
                             0, 0, 1}); //

        psd_assign_bufferp(expected, HEIGHT * WIDTH,
                           {1, 0, 0,   //
                            0, 1, 0,   //
                            0, 0, 1,   //
                            1, 0, 0,   //
                            0, 1, 0,   //
                            0, 0, 1}); //

        header.width = WIDTH;
        header.height = HEIGHT;
        header.channels = CHANNELS;

        bufferp = bytepp_to_bytep_with_free(&header, bufferpp);

        buffereq = 1;
        for (psd_size_t i = 0; i < HEIGHT; ++i) {
                if (memcmp(bufferp, expected, WIDTH)) {
                        buffereq = 0;
                        break;
                }
        }

        free(bufferp);
        free(expected);

        ASSERT_TRUE(buffereq);
}
