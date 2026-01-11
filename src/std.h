size_t strlen(const char s[]) {
    const char *p = s;
    while (*p)
        p++;
    return (size_t)(p - s);
}
