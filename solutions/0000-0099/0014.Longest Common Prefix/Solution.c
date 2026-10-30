// 题目：14. 最长公共前缀（Longest Common Prefix）
// 思路：以第 0 个字符串为基准，按列（第 i 个字符）与其他串逐位比较，一旦某串在该列不同或已结束，就把基准串在第 i 位截断。
// 时间复杂度：O(n·L)，n 是字符串个数、L 是最长公共前缀长度；空间复杂度：O(1)，直接在原串上原地截断。
char* longestCommonPrefix(char** strs, int strsSize) {  // strs 是字符串数组，strsSize 是元素个数
    for (int i = 0; strs[0][i]; i++) {  // 逐个检查基准串的字符，遇到 '\0' 说明已到串尾就停
        for (int j = 1; j < strsSize; j++) {  // 拿其余每个字符串在同一列与基准串比较
            if (strs[j][i] != strs[0][i]) {  // 该串这一列不同（若该串已结束则取到 '\0'，同样不相等）
                strs[0][i] = '\0';  // 直接在第 i 位写入结束符，原地把基准串截断成公共前缀
                return strs[0];  // 返回截断后的基准串
            }
        }
    }
    return strs[0];  // 所有列都比过且未出现差异，基准串本身就是最长公共前缀
}
