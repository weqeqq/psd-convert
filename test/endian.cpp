extern "C" {

#include <psd_buffer.h>
#include <psd_endian.h>
}

#include <gtest/gtest.h>

#define BE8 0xFF
#define NUM8 0xFF

#define BE16 0xFF, 0xFF
#define NUM16 0xFFFF

#define BE32 0xFF, 0xFF, 0xFF, 0xFF
#define NUM32 0xFFFFFFFF

TEST(endian, u8_from_bendian)
{
        psd_byte_t *buffer;
        psd_assign_bufferp(buffer, sizeof(psd_u8_t), {BE8});

        ASSERT_TRUE((psd_u8_t)NUM8 == psd_u8_from_bendian(buffer));
}

TEST(endian, u16_from_bendian)
{
        psd_byte_t *buffer;
        psd_assign_bufferp(buffer, sizeof(psd_u16_t), {BE16});

        ASSERT_TRUE((psd_u16_t)NUM16 == psd_u16_from_bendian(buffer));
}

TEST(endian, u32_from_bendian)
{
        psd_byte_t *buffer;
        psd_assign_bufferp(buffer, sizeof(psd_u32_t), {BE32});

        ASSERT_TRUE((psd_u32_t)NUM32 == psd_u32_from_bendian(buffer));
}

TEST(endian, i8_from_bendian)
{
        psd_byte_t *buffer;
        psd_assign_bufferp(buffer, sizeof(psd_i8_t), {BE8});

        ASSERT_TRUE((psd_i8_t)NUM8 == psd_i8_from_bendian(buffer));
}

TEST(endian, i16_from_bendian)
{
        psd_byte_t *buffer;
        psd_assign_bufferp(buffer, sizeof(psd_i16_t), {BE16});

        ASSERT_TRUE((psd_i16_t)NUM16 == psd_i16_from_bendian(buffer));
}

TEST(endian, i32_from_bendian)
{
        psd_byte_t *buffer;
        psd_assign_bufferp(buffer, sizeof(psd_i32_t), {BE32});

        ASSERT_TRUE((psd_i32_t)NUM32 == psd_i32_from_bendian(buffer));
}
