// 题目：2287. 重排字符形成目标字符串（Rearrange Characters to Make Target String）
// 核心思路：分别统计 s 与 target 中每个字母的个数，每个字母能支撑的份数是 count1[i] / count2[i]，所有字母的份数取最小值就是答案。
// 时间复杂度：O(|s| + |target| + 26)，两次线性扫描加一次字母表枚举；空间复杂度：O(1)，两个长度 26 的计数数组。
#define min(a, b) (((a) < (b)) ? (a) : (b))  // 宏：取两数中的较小值，本题用它更新答案

int rearrangeCharacters(char* s, char* target) {  // s：可重排的源字符串；target：目标字符串；返回最多能拼出几个 target
    int count1[26] = {0};  // 统计 s 中每个小写字母出现次数，全部初始化为 0
    int count2[26] = {0};  // 统计 target 中每个小写字母出现次数，全部初始化为 0
    for (int i = 0; s[i]; i++) {  // 遍历 s，遇到字符串结束符 '\0' 时停止
        count1[s[i] - 'a']++;  // 把字母映射到 0..25 的下标并累加计数
    }  // s 统计完毕
    for (int i = 0; target[i]; i++) {  // 遍历 target，同样以 '\0' 为结束标志
        count2[target[i] - 'a']++;  // 累加该字母在 target 中的需求量
    }  // target 统计完毕
    int ans = INT_MAX;  // 答案取各字母可拼份数的最小值，先置为正无穷大 INT_MAX
    for (int i = 0; i < 26; i++) {  // 枚举 26 个小写字母
        if (count2[i]) {  // 只考虑 target 中真正出现过的字母
            ans = min(ans, count1[i] / count2[i]);  // 该字母最多能支撑几份 target，与当前答案取小
        }  // 判断结束
    }  // 枚举结束
    return ans;  // 返回最多能拼出的份数
}  // 函数结束