// 题目：1684. 统计一致字符串的数目（Count the Number of Consistent Strings）
// 思路：用长度 26 的标记数组记下 allowed 里出现过哪些字母，再对每个单词逐字符检查，出现未被标记的字母就说明该单词不一致。
// 时间复杂度：O(|allowed| + Σ|word|²)，内层循环条件每轮都会重新调用 strlen；空间复杂度：O(26)，只有常数大小的标记数组。
int countConsistentStrings(char* allowed, char** words, int wordsSize) {  // allowed：允许的字符集合；words：待检查的单词数组；wordsSize：单词个数；返回一致字符串的数目
    int n = strlen(allowed);  // n 是 allowed 的长度
    int make[26] = {0};  // make 标记 allowed 中出现过的字母，下标为字符相对 'a' 的偏移，0 表示不允许
    for (int i = 0; i < n; i++) {  // 遍历 allowed 的每个字符
        make[allowed[i] - 'a'] = 1;  // 把对应字母标记为允许
    }
    int ans = wordsSize;  // ans 先假设所有单词都一致，之后每发现一个不一致的就减一
    for (int i = 0; i < wordsSize; i++) {  // 逐个单词检查
        char* word = words[i];  // 取出当前单词，便于后面复用
        for (int j = 0; j < strlen(word); j++) {  // 逐字符检查该单词
            if (!make[word[j] - 'a']) {  // 该字母不在 allowed 中，说明这个单词不一致
                ans--;  // 一致单词数减一
                break;  // 已经确定不一致，无需再检查后面的字符
            }
        }
    }
    return ans;  // 返回一致字符串的数目
}