extern noinline unsigned long __crypto_memneq(const void *a, const void *b, size_t size);
static inline int crypto_memneq(const void *a, const void *b, size_t size)
{
	return __crypto_memneq(a, b, size) != 0UL ? 1 : 0;
}
