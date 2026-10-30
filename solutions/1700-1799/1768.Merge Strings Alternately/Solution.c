// 题目：1768. 交替合并字符串（Merge Strings Alternately）
// 思路：双指针从两个字符串头部交替取字符，哪个串还没取完就追加哪个，直到写入总长度 m + n 个字符为止。
// 时间复杂度：O(m + n)，每个字符只写入一次；空间复杂度：O(m + n)，需要新建结果串（额外多 1 字节存结尾的 '\0'）。
char* mergeAlternately(char* word1, char* word2) {  // word1、word2 是待交替合并的两个字符串；返回新建的合并串
    int m = strlen(word1);  // word1 的长度 m
    int n = strlen(word2);  // word2 的长度 n
    char* ans = malloc(sizeof(char) * (n + m + 1));  // 多分配 1 个字节用来存放字符串结尾的 '\0'
    int i = 0;  // i 指向 word1 中下一个待取的字符
    int j = 0;  // j 指向 word2 中下一个待取的字符
    while (i + j != m + n) {  // 已写入的字符总数是 i + j，写满 m + n 个就结束
        if (i < m) {  // word1 还有剩余字符就先取它，保证交替顺序
            ans[i + j] = word1[i];  // 把 word1[i] 写到答案的第 i + j 个位置
            i++;  // word1 的指针后移
        }
        if (j < n) {  // word2 还有剩余字符就紧接着取它
            ans[i + j] = word2[j];  // 把 word2[j] 写到答案的下一个位置，实现交替
            j++;  // word2 的指针后移
        }
    }  // 循环结束，字符已全部写完
    ans[n + m] = '\0';  // 补上字符串结束符，使答案是合法的 C 字符串
    return ans;  // 返回堆上分配的合并串（由判题器负责 free）
}  // 函数结束