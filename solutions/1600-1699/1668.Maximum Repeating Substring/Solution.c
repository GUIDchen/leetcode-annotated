// 题目：1668. 最大重复子字符串（Maximum Repeating Substring）
// 思路：枚举 sequence 的每个起点，用递归的 findWord 统计从该起点开始能连续匹配多少个 word，取最大值。
// 时间复杂度：O(n·m·k)，每个起点都要逐字符比较；空间复杂度：O(k)，递归深度等于最大重复次数。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 手写取最大值的宏，避免依赖额外函数

int findWord(int i, char* sequence, char* word) {  // 统计从下标 i 开始能连续重复 word 的次数
    int n = strlen(word);  // 单个 word 的长度
    for (int j = 0; j < n; j++) {  // 逐字符检查接下来这一段是否等于 word
        if (sequence[j + i] != word[j]) {  // 出现不匹配的字符，说明本段无法完整重复
            return 0;  // 本段匹配失败，重复次数记为 0
        }  // if 分支结束
    }  // for 循环结束
    return 1 + findWord(i + n, sequence, word);  // 本段匹配成功，累加 1 并继续统计后面的段
}  // findWord 函数结束

int maxRepeating(char* sequence, char* word) {  // 返回 sequence 中 word 的最大重复次数
    int n = strlen(sequence);  // 主串长度，作为下标上界
    int m = strlen(word);  // 子串长度，每次匹配要跳过这么多字符
    int ans = 0;  // 记录目前找到的最大重复次数
    for (int i = 0; i <= n - m; i++) {  // 枚举所有可能的起始下标 i
        ans = max(ans, findWord(i, sequence, word));  // 用当前起点的统计结果更新答案
    }  // 枚举结束
    return ans;  // 返回最大值
}  // 函数结束