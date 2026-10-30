// 题目：242. 有效的字母异位词（Valid Anagram）
// 思路：两个字符串长度必须相同；把两个串都原地排序，再逐字符比较，排序后完全相同即为异位词。
// 时间复杂度：O(n log n)，两次 qsort 主导；空间复杂度：O(1)，只做原地排序，不用额外计数数组。
int cmp(const void* a, const void* b) {  // qsort 用的比较函数：按字符对应的整数值升序
    return *(char*) a - *(char*) b;  // 取出两个字符并返回差值，正数表示 a 应排在 b 之后
}

bool isAnagram(char* s, char* t) {  // 判断 s 与 t 是否互为字母异位词
    int n = strlen(s);  // s 的长度
    int m = strlen(t);  // t 的长度
    if (n != m) {  // 长度不同一定不可能互为异位词
        return 0;  // 直接判否
    }
    qsort(s, n, sizeof(char), cmp);  // 原地把 s 的字符排序
    qsort(t, n, sizeof(char), cmp);  // 原地把 t 的字符排序
    return !strcmp(s, t);  // 排序后两串完全相同即为异位词，取反得到 bool
}  // 函数结束