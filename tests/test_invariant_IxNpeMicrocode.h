#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* 
 * Simulate the buffer construction logic from IxNpeMicrocode.h
 * The vulnerable code uses sprintf() without bounds checking.
 * We test that a safe replacement (snprintf) properly bounds output.
 *
 * Original patterns:
 *   sprintf(filename, "NPE-%c.%08x", (field[0] & 0xf) + 'A', ...)
 *   sprintf(slnk, "NPE-%c-HSS", (field[0] & 0xf) + 'A')
 *   sprintf(slnk, "NPE-%c", (field[0] & 0xf) + 'A')
 *
 * Security invariant: Buffer reads/writes never exceed the declared buffer length.
 * Any output must be truncated or rejected if it would exceed the buffer size.
 */

/* Canary value to detect buffer overflows */
#define CANARY 0xDEADBEEF
#define SMALL_BUF_SIZE 8   /* intentionally small to test overflow protection */
#define NORMAL_BUF_SIZE 32

typedef struct {
    uint32_t canary_before;
    char buf[SMALL_BUF_SIZE];
    uint32_t canary_after;
} guarded_buffer_t;

/* Safe wrapper using snprintf - the fix for the vulnerability */
static int safe_sprintf_filename(char *buf, size_t buf_size, uint8_t field0, uint32_t version)
{
    return snprintf(buf, buf_size, "NPE-%c.%08x", (field0 & 0xf) + 'A', version);
}

static int safe_sprintf_slnk_hss(char *buf, size_t buf_size, uint8_t field0)
{
    return snprintf(buf, buf_size, "NPE-%c-HSS", (field0 & 0xf) + 'A');
}

static int safe_sprintf_slnk(char *buf, size_t buf_size, uint8_t field0)
{
    return snprintf(buf, buf_size, "NPE-%c", (field0 & 0xf) + 'A');
}

/* Test adversarial field[0] values that could produce unexpected characters */
static const uint8_t adversarial_field0[] = {
    0x00,        /* minimum: 'A' */
    0x0f,        /* maximum valid: 'P' */
    0xff,        /* 0xff & 0xf = 0xf -> 'P' */
    0x7f,        /* 0x7f & 0xf = 0xf -> 'P' */
    0x80,        /* 0x80 & 0xf = 0x0 -> 'A' */
    0xaa,        /* 0xaa & 0xf = 0xa -> 'K' */
    0x10,        /* 0x10 & 0xf = 0x0 -> 'A' */
    0xfe,        /* 0xfe & 0xf = 0xe -> 'O' */
};

/* Adversarial version values for filename format */
static const uint32_t adversarial_versions[] = {
    0x00000000,
    0xffffffff,
    0xdeadbeef,
    0x12345678,
    0x80000000,
    0x7fffffff,
};

START_TEST(test_buffer_bounds_filename)
{
    /* Invariant: snprintf must never write beyond declared buffer size */
    int num_fields = sizeof(adversarial_field0) / sizeof(adversarial_field0[0]);
    int num_versions = sizeof(adversarial_versions) / sizeof(adversarial_versions[0]);

    for (int i = 0; i < num_fields; i++) {
        for (int j = 0; j < num_versions; j++) {
            guarded_buffer_t gbuf;
            gbuf.canary_before = CANARY;
            gbuf.canary_after = CANARY;
            memset(gbuf.buf, 0, SMALL_BUF_SIZE);

            int ret = safe_sprintf_filename(gbuf.buf, SMALL_BUF_SIZE,
                                            adversarial_field0[i],
                                            adversarial_versions[j]);

            /* Canaries must be intact - no overflow occurred */
            ck_assert_msg(gbuf.canary_before == CANARY,
                "Buffer underflow detected: canary_before corrupted for field0=0x%02x version=0x%08x",
                adversarial_field0[i], adversarial_versions[j]);
            ck_assert_msg(gbuf.canary_after == CANARY,
                "Buffer overflow detected: canary_after corrupted for field0=0x%02x version=0x%08x",
                adversarial_field0[i], adversarial_versions[j]);

            /* snprintf must return non-negative */
            ck_assert_msg(ret >= 0,
                "snprintf returned error for field0=0x%02x version=0x%08x",
                adversarial_field0[i], adversarial_versions[j]);

            /* Buffer must be null-terminated within bounds */
            int null_found = 0;
            for (int k = 0; k < SMALL_BUF_SIZE; k++) {
                if (gbuf.buf[k] == '\0') {
                    null_found = 1;
                    break;
                }
            }
            ck_assert_msg(null_found,
                "Buffer not null-terminated within bounds for field0=0x%02x version=0x%08x",
                adversarial_field0[i], adversarial_versions[j]);

            /* Actual string length must be within buffer bounds */
            size_t actual_len = strnlen(gbuf.buf, SMALL_BUF_SIZE);
            ck_assert_msg(actual_len < SMALL_BUF_SIZE,
                "String length %zu exceeds buffer size %d for field0=0x%02x version=0x%08x",
                actual_len, SMALL_BUF_SIZE, adversarial_field0[i], adversarial_versions[j]);
        }
    }
}
END_TEST

START_TEST(test_buffer_bounds_slnk_hss)
{
    /* Invariant: snprintf must never write beyond declared buffer size for HSS link names */
    int num_fields = sizeof(adversarial_field0) / sizeof(adversarial_field0[0]);

    for (int i = 0; i < num_fields; i++) {
        guarded_buffer_t gbuf;
        gbuf.canary_before = CANARY;
        gbuf.canary_after = CANARY;
        memset(gbuf.buf, 0, SMALL_BUF_SIZE);

        int ret = safe_sprintf_slnk_hss(gbuf.buf, SMALL_BUF_SIZE, adversarial_field0[i]);

        ck_assert_msg(gbuf.canary_before == CANARY,
            "Buffer underflow detected in slnk_hss: canary_before corrupted for field0=0x%02x",
            adversarial_field0[i]);
        ck_assert_msg(gbuf.canary_after == CANARY,
            "Buffer overflow detected in slnk_hss: canary_after corrupted for field0=0x%02x",
            adversarial_field0[i]);

        ck_assert_msg(ret >= 0,
            "snprintf returned error for slnk_hss field0=0x%02x", adversarial_field0[i]);

        int null_found = 0;
        for (int k = 0; k < SMALL_BUF_SIZE; k++) {
            if (gbuf.buf[k] == '\0') {
                null_found = 1;
                break;
            }
        }
        ck_assert_msg(null_found,
            "slnk_hss buffer not null-terminated within bounds for field0=0x%02x",
            adversarial_field0[i]);

        size_t actual_len = strnlen(gbuf.buf, SMALL_BUF_SIZE);
        ck_assert_msg(actual_len < SMALL_BUF_SIZE,
            "slnk_hss string length %zu exceeds buffer size %d for field0=0x%02x",
            actual_len, SMALL_BUF_SIZE, adversarial_field0[i]);
    }
}
END_TEST

START_TEST(test_buffer_bounds_slnk)
{
    /* Invariant: snprintf must never write beyond declared buffer size for link names */
    int num_fields = sizeof(adversarial_field0) / sizeof(adversarial_field0[0]);

    for (int i = 0; i < num_fields; i++) {
        guarded_buffer_t gbuf;
        gbuf.canary_before = CANARY;
        gbuf.canary_after = CANARY;
        memset(gbuf.buf, 0, SMALL_BUF_SIZE);

        int ret = safe_sprintf_slnk(gbuf.buf, SMALL_BUF_SIZE, adversarial_field0[i]);

        ck_assert_msg(gbuf.canary_before == CANARY,
            "Buffer underflow detected in slnk: canary_before corrupted for field0=0x%02x",
            adversarial_field0[i]);
        ck_assert_msg(gbuf.canary_after == CANARY,
            "Buffer overflow detected in slnk: canary_after corrupted for field0=0x%02x",
            adversarial_field0[i]);

        ck_assert_msg(ret >= 0,
            "snprintf returned error for slnk field0=0x%02x", adversarial_field0[i]);

        int null_found = 0;
        for (int k = 0; k < SMALL_BUF_SIZE; k++) {
            if (gbuf.buf[k] == '\0') {
                null_found = 1;
                break;
            }
        }
        ck_assert_msg(null_found,
            "slnk buffer not null-terminated within bounds for field0=0x%02x",
            adversarial_field0[i]);

        size_t actual_len = strnlen(gbuf.buf, SMALL_BUF_SIZE);
        ck_assert_msg(actual_len < SMALL_BUF_SIZE,
            "slnk string length %zu exceeds buffer size %d for field0=0x%02x",
            actual_len, SMALL_BUF_SIZE, adversarial_field0[i]);
    }
}
END_TEST

START_TEST(test_output_length_predictability)
{
    /* Invariant: output length must be predictable and bounded for all valid inputs */
    /* "NPE-%c.%08x" -> exactly 14 chars + null = 15 bytes minimum buffer needed */
    /* "NPE-%c-HSS"   -> exactly 9 chars + null = 10 bytes minimum buffer needed */
    /* "NPE-%c"       -> exactly 5 chars + null = 6 bytes minimum buffer needed */

    char buf[NORMAL_BUF_SIZE];
    int num_fields = sizeof(adversarial_field0) / sizeof(adversarial_field0[0]);
    int num_versions = sizeof(adversarial_versions) / sizeof(adversarial_versions[0]);

    for (int i = 0; i < num_fields; i++) {
        uint8_t f = adversarial_field0[i];
        char expected_char = (char)((f & 0xf) + 'A');

        /* Test slnk format: "NPE-%c" */
        memset(buf, 0xAA, NORMAL_BUF_SIZE);
        int ret = safe_sprintf_slnk(buf, NORMAL_BUF_SIZE, f);
        ck_assert_msg(ret == 5,
            "slnk format produced unexpected length %d (expected 5) for field0=0x%02x", ret, f);
        ck_assert_msg(buf[4] == expected_char,
            "slnk format produced wrong char '%c' (expected '%c') for field0=0x%02x",
            buf[4], expected_char, f);
        ck_assert_msg(buf[5] == '\0',
            "slnk format not null-terminated at position 5 for field0=0x%02x", f);

        /* Test slnk_hss format: "NPE-%c-HSS" */
        memset(buf, 0xAA, NORMAL_BUF_SIZE);
        ret = safe_sprintf_slnk_hss(buf, NORMAL_BUF_SIZE, f);
        ck_assert_msg(ret == 9,
            "slnk_hss format produced unexpected length %d (expected 9) for field0=0x%02x", ret, f);
        ck_assert_msg(buf[4] == expected_char,
            "slnk_hss format produced wrong char '%c' (expected '%c') for field0=0x%02x",
            buf[4], expected_char, f);
        ck_assert_msg(buf[9] == '\0',
            "slnk_hss format not null-terminated at position 9 for field0=0x%02x", f);

        /* Test filename format: "NPE-%c.%08x" */
        for (int j = 0; j < num_versions; j++) {
            memset(buf, 0xAA, NORMAL_BUF_SIZE);
            ret = safe_sprintf_filename(buf, NORMAL_BUF_SIZE, f, adversarial_versions[j]);
            ck_assert_msg(ret == 14,
                "filename format produced unexpected length %d (expected 14) for field0=0x%02x version=0x%08x",
                ret, f, adversarial_versions[j]);
            ck_assert_msg(buf[4] == expected_char,
                "filename format produced wrong char '%c' (expected '%c') for field0=0x%02x",
                buf[4], expected_char, f);
            ck_assert_msg(buf[14] == '\0',
                "filename format not null-terminated at position 14 for field0=0x%02x version=0x%08x",
                f, adversarial_versions[j]);
        }
    }
}
END_TEST

START_TEST(test_truncation_on_tiny_buffer)
{
    /* Invariant: even with a 1-byte buffer, snprintf must not overflow */
    const size_t tiny_sizes[] = {0, 1, 2, 3, 4, 5};
    int num_sizes = sizeof(tiny_sizes) / sizeof(tiny_sizes[0]);
    int num_fields = sizeof(adversarial_field0) / sizeof(adversarial_field0[0]);

    for (int s = 0; s < num_sizes; s++) {
        size_t buf_size = tiny_sizes[s];
        /* Allocate with extra space and canaries */
        char *buf = NULL;
        uint32_t canary_after = CANARY;

        if (buf_size > 0) {
            buf = (char *)malloc(buf_size + sizeof(uint32_t));
            ck_assert_ptr_nonnull