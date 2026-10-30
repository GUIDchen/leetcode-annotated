// 题目：1941. 检查是否所有字符出现次数相同（Check if All Characters Have Equal Number of Occurrences）
// 思路：先用长度 26 的计数数组统计每个小写字母的出现次数，再跳过没出现的字母，检查所有出现过的字母次数是否彼此相等。
// 时间复杂度：O(n + 26)，n 为字符串长度；空间复杂度：O(26) = O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool areOccurrencesEqual(string s) {  // s：待检查的小写字母字符串
        vector<int> cnt(26);  // 26 个桶，分别统计 a..z 的出现次数
        for (char c : s) {  // 遍历字符串中的每个字符
            ++cnt[c - 'a'];  // c - 'a' 把字母映射成 0..25 的下标后计数
        }
        int v = 0;  // v 保存「第一个非零的次数」作为比较基准，0 表示还没遇到过
        for (int x : cnt) {  // 逐个字母检查它的出现次数
            if (x == 0) {  // 次数为 0 说明这个字母没出现过
                continue;  // 跳过它，它不参与「次数是否相同」的比较
            }
            if (v && v != x) {  // 基准已存在且与当前次数不同 ⇒ 各字符出现次数不相同
                return false;  // 立即判定为 false
            }
            v = x;  // 否则把当前次数记为新的基准（首次遇到非零时就是这一步完成赋值）
        }
        return true;  // 所有出现过的字母次数都一样，返回 true
    }
};
