#include "crit_utils.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

#ifdef CUSTOM_MAIN

int main(void) {
	RUN_TEST(get_next_line, real_empty);
	// RUN_TEST(get_next_line, stdin);
	RUN_TEST(get_next_line, basic_no_newline);
	RUN_TEST(get_next_line, basic_no_newline_end);
	RUN_TEST(get_next_line, basic_with_newline_end);
	RUN_TEST(get_next_line, one_newline);
	RUN_TEST(get_next_line, two_newlines);
	RUN_TEST(get_next_line, basic_with_newline);
	return (EXIT_SUCCESS);
}

#endif

Test(get_next_line, basic_no_newline)
{
	int fd = open("test_files/basic_no_newline", O_RDONLY);
	cr_assert_neq(fd, -1);
	cr_assert_str_eq(get_next_line(fd), "foobarbazbee");
	cr_assert_null(get_next_line(fd));
	close(fd);
}

Test(get_next_line, basic_no_newline_end)
{
	int fd = open("test_files/basic_no_newline_end", O_RDONLY);
	cr_assert_neq(fd, -1);
	cr_assert_str_eq(get_next_line(fd), "foobar\n");
	cr_assert_str_eq(get_next_line(fd), "bazbee");
	cr_assert_null(get_next_line(fd));
	close(fd);
}

Test(get_next_line, basic_with_newline_end)
{
	int fd = open("test_files/basic_with_newline_end", O_RDONLY);
	cr_assert_neq(fd, -1);
	// char b[8];
	// b[7] = '\0';
	// cr_assert_eq(read(fd, b, 7), 7);
	// cr_assert_str_eq(b, "foobar\n");
	// cr_assert_eq(read(fd, b, 7), 7);
	// cr_assert_str_eq(b, "bazbee\n");
	// cr_assert_eq(read(fd, b, 7), 0);
	// cr_assert_str_eq(b, "bazbee\n");
	// lseek(fd, 0, SEEK_SET);
	cr_assert_str_eq(get_next_line(fd), "foobar\n");
	cr_assert_str_eq(get_next_line(fd), "bazbee\n");
	cr_assert_null(get_next_line(fd));
	close(fd);
}

Test(get_next_line, one_newline)
{
	int fd = open("test_files/one_newline", O_RDONLY);
	cr_assert_neq(fd, -1);
	char b;
	cr_assert_eq(read(fd, &b, 1), 1);
	cr_assert_eq(read(fd, &b, 1), 0);
	lseek(fd, 0, SEEK_SET);
	cr_assert_str_eq(get_next_line(fd), "\n");
	cr_assert_null(get_next_line(fd));
	close(fd);
}

Test(get_next_line, two_newlines)
{
	int fd = open("test_files/two_newlines", O_RDONLY);
	cr_assert_neq(fd, -1);
	char b;
	cr_assert_eq(read(fd, &b, 1), 1);
	cr_assert_eq(read(fd, &b, 1), 1);
	cr_assert_eq(read(fd, &b, 1), 0);
	lseek(fd, 0, SEEK_SET);
	cr_assert_str_eq(get_next_line(fd), "\n");
	cr_assert_str_eq(get_next_line(fd), "\n");
	cr_assert_null(get_next_line(fd));
	close(fd);
}

Test(get_next_line, binary)
{
	int fd = open("test_files/binary", O_RDONLY);
	cr_assert_neq(fd, -1);
	char *out = get_next_line(fd);
	cr_assert_str_eq(out, "world\0hello\n");
	cr_assert_eq(memcmp(out, "world\0hello\n", 13), 0);
	cr_assert_str_eq(get_next_line(fd), "bye");
	cr_assert_null(get_next_line(fd));
	close(fd);
}

Test(get_next_line, stdin, .disabled = true)
{
	int fd = STDIN_FILENO;
	cr_assert_str_eq(get_next_line(fd), "world\n");
	cr_assert_str_eq(get_next_line(fd), "hello\n");
	cr_assert_null(get_next_line(fd));
	close(fd);
}

Test(get_next_line, real_empty)
{
	int fd = open("test_files/empty", O_RDONLY);
	cr_assert_neq(fd, -1);
	cr_assert_null(get_next_line(fd));
}

Test(get_next_line, basic_with_newline)
{
	int fd = open("test_files/basic_with_newline", O_RDONLY);
	cr_assert_neq(fd, -1);
	cr_assert_str_eq(get_next_line(fd), "foo\n");
	cr_assert_null(get_next_line(fd));
	close(fd);
}


ReportHook(POST_SUITE)(struct criterion_suite_stats *a)
{
	size_t	total_tested = a->tests_crashed + a->tests_failed + a->tests_passed;
	if (total_tested != 0)
		printf("\e[1mFinished Suite \e[33;22m%s\e[39;1m: Tested: \e[34;22m%zu\e[39;1m | Passing: \e[32;22m%zu\e[39;1m | Failing: \e[22m%s%zu\e[39;1m | Crashing: \e[22m%s%zu\e[0m\n", a->suite->name, total_tested, a->tests_passed, a->tests_failed > 0 ? "\e[31m" : "", a->tests_failed, a->tests_crashed > 0 ? "\e[31m" : "", a->tests_crashed);
}

#if __has_feature(address_sanitizer)
#else

ReportHook(POST_FINI)(struct criterion_test_stats *a)
{
	if (a->timed_out)
		return ;
	char *cmd = ft_strjoin(ft_strjoin(
		"leaks --quiet $(pgrep -P ", ft_itoa(getpid())), " | head -1) > /tmp/test_leaks");
	int ret = system(cmd);
	if (ret != EXIT_SUCCESS)
	{
		system("cat /tmp/test_leaks");
		printf("\e[33m%s\e[0;1m::\e[0;33m%s\e[0;1m had a leak\e[0m\n", a->test->category, a->test->name);
	}
}

#endif
