#ifndef CRIT_UTILS_H
# define CRIT_UTILS_H

# include <criterion/criterion.h>
# ifdef CUSTOM_MAIN
#  define RUN_TEST(suite, name) void suite##_##name(void);suite##_##name()
#  undef Test
#  define Test(suite, name, ...) void suite##_##name(void)
# endif

#define HEAP2STACK(str, prefix)													\
size_t str##len = ft_strlen(str) + 1;											\
char prefix##_##str[str##len];													\
memmove(prefix##_##str, str, str##len);											\
free(str)

# define cr_assert_str_escaped_eq(str1_, str2_)									\
{																				\
	char *str1 = ft_str_replace(str1_, "\n", "\\n");							\
	char *str2 = ft_str_replace(str2_, "\n", "\\n");							\
	HEAP2STACK(str1, new);														\
	HEAP2STACK(str2, new);														\
	cr_assert_str_eq(new_str1, new_str2);										\
}

# define cr_expect_str_escaped_eq(str1_, str2_)									\
{																				\
	char *str1 = ft_str_replace(str1_, "\n", "\\n");							\
	char *str2 = ft_str_replace(str2_, "\n", "\\n");							\
	HEAP2STACK(str1, new);														\
	HEAP2STACK(str2, new);														\
	cr_expect_str_eq(new_str1, new_str2);										\
}

# define cr_assert_int_eq(int1, int2, ...)										\
{																				\
	char *str1 = ft_itoa(int1);													\
	char *str2 = ft_itoa(int2);													\
	HEAP2STACK(str1, new);														\
	HEAP2STACK(str2, new);														\
	cr_assert_str_eq(new_str1, new_str2, __VA_ARGS__);							\
}

# define cr_expect_int_eq(int1, int2, ...)										\
{																				\
	char *str1 = ft_itoa(int1);													\
	char *str2 = ft_itoa(int2);													\
	HEAP2STACK(str1, new);														\
	HEAP2STACK(str2, new);														\
	cr_expect_str_eq(new_str1, new_str2, __VA_ARGS__);							\
}


#endif
