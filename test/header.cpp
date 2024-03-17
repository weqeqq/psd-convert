#define PSD_RESULT_MACRO__

extern "C" {

#include <psd_buffer.h>
#include <psd_cursor.h>
#include <psd_header.h>
#include <psd_result.h>
}

static psd_result_t PSD_RESULT__;

#include <gtest/gtest.h>

#define CORRECT_SIGNATURE 0x38, 0x42, 0x50, 0x53
#define INCORRECT_SIGNATURE 0x30, 0x46, 0x51, 0x52

#define VERSION_PSD 0x00, 0x00
#define VERSION_PSB 0x00, 0x01
#define INCORRECT_VERSION 0x00, 0x02

#define CORRECT_CHANNELS 0x00, 0x03
#define INCORRECT_CHANNELS 0x00, 0x40

#define CORRECT_HEIGHT 0x00, 0x00, 0x00, 0x10
#define INCORRECT_HEIGHT 0x00, 0x00, 0x00, 0x00

#define CORRECT_WIDTH 0x00, 0x00, 0x00, 0x10
#define INCORRECT_WIDTH 0x00, 0x00, 0x00, 0x00

#define CORRECT_DEPTH 0x00, 0x8
#define INCORRECT_DEPTH 0x00, 0x00

#define CORRECT_COLOR_MODE 0x00, 0x00
#define INCORRECT_COLOR_MODE 0x00, 0x0A

#define CORRECT_HEADER                                                         \
        CORRECT_SIGNATURE, VERSION_PSD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    \
            CORRECT_CHANNELS, CORRECT_HEIGHT, CORRECT_WIDTH, CORRECT_DEPTH,    \
            CORRECT_COLOR_MODE

#define INCORRECT_HEADER                                                       \
        CORRECT_SIGNATURE, VERSION_PSD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    \
            INCORRECT_CHANNELS, CORRECT_HEIGHT, CORRECT_WIDTH, CORRECT_DEPTH,  \
            CORRECT_COLOR_MODE

#define HEADER_SIZE                                                            \
        (PSD_SIGNATURE_SIZE + PSD_VERSION_SIZE + PSD_RESERVED_SIZE +           \
         PSD_CHANNELS_SIZE + PSD_HEIGHT_SIZE + PSD_WIDTH_SIZE +                \
         PSD_DEPTH_SIZE + PSD_COLOR_MODE_SIZE)

TEST(header, read_correct_signature)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;

        psd_assign_bufferp(buffer, PSD_SIGNATURE_SIZE, {CORRECT_SIGNATURE});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_SIGNATURE_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_signature(cursor);

        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
}

TEST(header, read_incorrect_signature)
{
        psd_byte_t *buffer;
        psd_cursor *cursor;

        psd_assign_bufferp(buffer, PSD_SIGNATURE_SIZE, {INCORRECT_SIGNATURE});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_SIGNATURE_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_signature(cursor);

        psd_cursor_destroy(cursor);

        ASSERT_TRUE(psd_result__.is_error);
}

TEST(header, read_psd_version)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_VERSION_SIZE, {VERSION_PSD});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_VERSION_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_version(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
        ASSERT_TRUE(header.version == PSD);
}

TEST(header, read_psb_version)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_VERSION_SIZE, {VERSION_PSB});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_VERSION_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_version(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
        ASSERT_TRUE(header.version == PSB);
}

TEST(header, read_incorrect_version)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_VERSION_SIZE, {INCORRECT_VERSION});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_VERSION_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_version(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_TRUE(psd_result__.is_error);
}

TEST(header, read_correct_number_of_channels)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_CHANNELS_SIZE, {CORRECT_CHANNELS});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_CHANNELS_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_channels(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
        ASSERT_TRUE(header.channels <= PSD_MAX_CHANNELS);
}

TEST(header, read_incorrect_number_of_channels)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_CHANNELS_SIZE, {INCORRECT_CHANNELS});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_CHANNELS_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_channels(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_TRUE(psd_result__.is_error);
}

TEST(header, read_correct_height)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_HEIGHT_SIZE, {CORRECT_HEIGHT});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_HEIGHT_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_height(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
        ASSERT_TRUE(PSD_HEIGHT_PSD_COND(header.height));
}

TEST(header, read_incorrect_height)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_HEIGHT_SIZE, {INCORRECT_HEIGHT});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_HEIGHT_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_height(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_TRUE(psd_result__.is_error);
}

TEST(header, read_correct_width)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_WIDTH_SIZE, {CORRECT_WIDTH});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_WIDTH_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_width(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
        ASSERT_TRUE(PSD_WIDTH_PSD_COND(header.width));
}

TEST(header, read_incorrect_width)
{
        psd_byte_t *buffer;
        psd_cursor_t *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_WIDTH_SIZE, {INCORRECT_WIDTH});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_WIDTH_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_width(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_TRUE(psd_result__.is_error);
}

TEST(header, read_correct_depth)
{
        psd_byte_t *buffer;
        psd_cursor *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_DEPTH_SIZE, {CORRECT_DEPTH});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_DEPTH_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_depth(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
        ASSERT_TRUE(PSD_DEPTH_COND(header.depth));
}

TEST(header, read_incorrect_depth)
{
        psd_byte_t *buffer;
        psd_cursor *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_DEPTH_SIZE, {INCORRECT_DEPTH});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_DEPTH_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_depth(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_TRUE(psd_result__.is_error);
}

TEST(header, read_correct_color_mode)
{
        psd_byte_t *buffer;
        psd_cursor *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_COLOR_MODE_SIZE, {CORRECT_COLOR_MODE});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_COLOR_MODE_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_color_mode(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
        ASSERT_TRUE(PSD_COLOR_MODE_COND(header.color_mode));
}

TEST(header, read_incorrect_color_mode)
{
        psd_byte_t *buffer;
        psd_cursor *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, PSD_COLOR_MODE_SIZE, {INCORRECT_COLOR_MODE});

        psd_result__ = psd_cursor_from_buffer(buffer, PSD_COLOR_MODE_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_read_color_mode(&header, cursor);

        psd_cursor_destroy(cursor);

        ASSERT_TRUE(psd_result__.is_error);
}

TEST(header, read_correct_header)
{
        psd_byte_t *buffer;
        psd_cursor *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, HEADER_SIZE, {CORRECT_HEADER});

        psd_result__ = psd_cursor_from_buffer(buffer, HEADER_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_header_read(cursor);

        psd_header_destroy((psd_header_t *)psd_result__.pointer);
        psd_cursor_destroy(cursor);

        ASSERT_FALSE(psd_result__.is_error);
}

TEST(header, read_incorrect_header)
{
        psd_byte_t *buffer;
        psd_cursor *cursor;
        psd_header_t header;

        psd_assign_bufferp(buffer, HEADER_SIZE, {INCORRECT_HEADER});

        psd_result__ = psd_cursor_from_buffer(buffer, HEADER_SIZE);
        ASSERT_FALSE(psd_result__.is_error);

        cursor = (psd_cursor_t *)psd_result__.pointer;
        psd_result__ = psd_header_read(cursor);

        psd_cursor_destroy(cursor);

        ASSERT_TRUE(psd_result__.is_error);
}
