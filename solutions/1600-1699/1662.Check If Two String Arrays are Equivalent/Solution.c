// 题目：1662. 检查两个字符串数组是否相等（Check If Two String Arrays are Equivalent）
// 思路：把两个数组都看成字符流，用两对指针同步逐字符比较，单词读完就跳到下一个单词。
// 时间复杂度：O(L)，L 为拼接后字符串长度；空间复杂度：O(1)，只用了四个下标变量。
bool arrayStringsAreEqual(char** word1, int word1Size, char** word2, int word2Size) {  // word1/word2 是字符串数组，两个 Size 是各自单词个数；相等返回 true
    int i = 0;  // word1 中当前正在比较的单词下标
    int j = 0;  // word2 中当前正在比较的单词下标
    int x = 0;  // word1[i] 这个单词内部当前字符的下标
    int y = 0;  // word2[j] 这个单词内部当前字符的下标
    while (i < word1Size && j < word2Size) {  // 两个数组都还没读完，就继续同步比较
        if (word1[i][x++] != word2[j][y++]) {  // 先取当前字符再把下标后移，逐字符比较；不等则直接判定不相等
            return 0;  // 发现不同字符，返回 false（用 0 表示）
        }  // 字符不等分支结束
    // 比较完一个字符后，检查各自单词是否读完，读完就切到下一个单词继续
        if (word1[i][x] == '\0') {  // word1 当前单词已经读到结尾 '\0'
            x = 0;  // 字符下标归零，准备读下一个单词
            i++;  // 换到 word1 的下一个单词
        }  // word1 换词分支结束
        if (word2[j][y] == '\0') {  // word2 当前单词已经读到结尾 '\0'
            y = 0;  // 字符下标归零，准备读下一个单词
            j++;  // 换到 word2 的下一个单词
        }  // word2 换词分支结束
    }  // 主循环结束
    return i == word1Size && j == word2Size;  // 两边必须同时读完才相等：都到达单词数末尾
}  // 函数结束