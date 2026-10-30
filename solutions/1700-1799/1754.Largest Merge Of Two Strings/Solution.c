// 题目：1754. 构造字典序最大的合并字符串（Largest Merge Of Two Strings）
// 思路：双指针贪心，每步比较两串的剩余后缀，取后缀更大那一侧的首字符；比较过程中跳过相同的公共前缀。
// 时间复杂度：O((m+n)^2)，每次比较最坏要扫过整个公共前缀；空间复杂度：O(m+n)，存放结果字符串。
char* largestMerge(char* word1, char* word2) {  // word1、word2 为待合并的两个字符串
    int m = strlen(word1);  // word1 的长度
    int n = strlen(word2);  // word2 的长度
    int i = 0;  // word1 中下一个待取字符的下标
    int j = 0;  // word2 中下一个待取字符的下标
    char* ans = malloc((m + n + 1) * sizeof(char));  // 结果串：m+n 个字符，外加结尾的 '\0'
    while (i < m && j < n) {  // 两个串都还有字符时，每步按字典序挑更大的一侧
        int k = 0;  // 公共前缀的长度，用来跳过两边相同的字符
        while (word1[i + k] && word2[j + k] && word1[i + k] == word2[j + k]) {  // 一边跳过相同字符，直到遇到 '\0' 或不同字符
            k++;  // 公共前缀又长了一位
        }
        if (word1[i + k] > word2[j + k]) {  // 停下处 word1 的字符更大（'\0' 最小），取 word1 能让字典序更大
            ans[i + j] = word1[i];  // 把 word1 当前字符放到结果的第 i+j 位
            i++;  // word1 的指针后移
        } else {  // 否则 word2 的后缀更大或 word1 已到结尾，应该取 word2
            ans[i + j] = word2[j];  // 把 word2 当前字符放到结果的第 i+j 位
            j++;  // word2 的指针后移
        };  // 原代码此处多写了一个分号，作为空语句原样保留
    }
    while (word1[i]) {  // word2 已经用完，把 word1 剩下的部分整段接到末尾
        ans[i + j] = word1[i];  // 依次搬运 word1 的字符
        i++;  // 指针后移
    }
    while (word2[j]) {  // word1 已经用完，把 word2 剩下的部分整段接到末尾
        ans[i + j] = word2[j];  // 依次搬运 word2 的字符
        j++;  // 指针后移
    }
    ans[m + n] = '\0';  // 在 m+n 处补上字符串结束符
    return ans;  // 返回新分配并填好的合并结果
}