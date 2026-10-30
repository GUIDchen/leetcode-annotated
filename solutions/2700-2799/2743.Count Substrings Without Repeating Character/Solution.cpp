// 题目：2743. 计算没有重复字符的子字符串数量（Count Substrings Without Repeating Character）
// 核心思路：滑动窗口，窗口内始终保持无重复字符，以 i 结尾的合法子串个数正好等于窗口长度 i - j + 1。
// 时间复杂度：O(n)，i 与 j 都只向右移动；空间复杂度：O(1)，固定 26 个字母的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfSpecialSubstrings(string s) {  // s：由小写字母组成的字符串
        int n = s.size();  // 字符串长度
        int cnt[26]{};  // 统计窗口内每个字母出现的次数，花括号把全部元素初始化为 0
        int ans = 0;  // 累计答案：没有重复字符的子串数量
        for (int i = 0, j = 0; i < n; ++i) {  // i 是窗口右端，j 是窗口左端，都从 0 开始
            int k = s[i] - 'a';  // 把当前字符映射到 0~25 的下标
            ++cnt[k];  // 当前字符进入窗口，计数加一
            while (cnt[k] > 1) {  // 当前字符出现重复，需要收缩左端直到不再重复
                --cnt[s[j++] - 'a'];  // 左端字符移出窗口，同时左指针右移
            }
            ans += i - j + 1;  // 以 i 结尾、长度从 1 到 i-j+1 的子串都不含重复字符
        }
        return ans;  // 返回没有重复字符的子串总数
    }
};