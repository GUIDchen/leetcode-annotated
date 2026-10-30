// 题目：2185. 统计包含给定前缀的字符串（Counting Words With a Given Prefix）
// 思路：先求出前缀长度 n，再逐个单词用 strncmp 只比较前 n 个字符，相等就说明该单词以 pref 开头，累加计数。
// 时间复杂度：O(m·n)，m 为单词个数、n 为前缀长度；空间复杂度：O(1)，只用了常数个变量。
int prefixCount(char** words, int wordsSize, char* pref) {  // words：字符串数组；wordsSize：单词个数；pref：待匹配前缀
    int ans = 0;  // 计数器：统计以 pref 开头的单词数量
    int n = strlen(pref);  // 前缀长度，后续只比较每个单词的前 n 个字符
    for (int i = 0; i < wordsSize; i++) {  // 逐个单词扫描
        if (strncmp(words[i], pref, n) == 0) {  // 只比较前 n 个字符：相等说明该单词以 pref 开头
            ans++;  // 命中一个，计数加一
        }  // if 结束
    }  // 循环结束
    return ans;  // 返回满足条件的单词总数
}  // 函数结束