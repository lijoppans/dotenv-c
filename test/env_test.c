#include <stdio.h>
#include <dotenv.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"

#if defined(_WIN32)
#include <string.h>
#endif

#define assert_var(expected, name) \
    assert(0 == strcmp(expected, getenv(name)))


static void test_no_file(void)
{
    assert(-1 == env_load("no such file", false));
}

static void test_value(void)
{
    assert_var("unit test", "VALUE");
    assert_var(" 300", "SPACE  ");
    assert_var("\"double\"", "DOUBLE_QUOTE");
    assert_var("\'single\'", "SINGLE_QUOTE");
    assert_var("nested unit test value", "NESTED");

    assert_var("base/.test", "TEST_DIR");
    assert_var("mysql:host=localhost;dbname=test_db", "DSN");
    assert(NULL == getenv("EMPTY"));
}

static void test_comment(void)
{
    assert(NULL == getenv("# COMMENTED"));
    assert(NULL == getenv(" #COMMENTED2"));
}

static void test_overwrite(void)
{
    assert(0 == env_load("./test/.test.env", false));
    assert_var("unit test", "VALUE");

    assert(0 == env_load("./test/.test.env", true));
    assert_var("something else", "VALUE");
}

int main(void)
{
    env_load("./.test.env", false);

    assert(0 == env_load("./test", false));
//
//    printf("%s", getenv("TEST_DIR"));
//    exit(0);
    test_no_file();
    test_value();
    test_comment();
    test_overwrite();

    assert(0 == strcmp("unit test", env_get_from_file("./test", "VALUE", NULL)));
    assert(0 == strcmp("default value", env_get_from_file("./test", "VALUE_NOT_EXISTSS", "default value")));

    puts("All tests are fine!");

    return 0;
}
