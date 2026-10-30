// 题目：1540. K 次操作转变字符串（Can Convert String in K Moves）
// 思路：统计每个字符需要的循环位移 d = (t[i] - s[i] + 26) % 26，同一位移 d 的第 c 次出现最晚要排到第 d + 26*(c-1) 次操作，逐项与 k 比较即可。
// 时间复杂度：O(n + |Σ|)，一次扫描加 26 次检查；空间复杂度：O(|Σ|)，计数器只用 26 个格子。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canConvertString(string s, string t, int k) {  // s：原始字符串；t：目标字符串；k：最多允许的操作次数
        if (s.size() != t.size()) {  // 两个串长度不同，无论怎么移位都无法转换
            return false;  // 直接返回 false
        }
        int cnt[26]{};  // cnt[d] 记录「需要位移 d」的字符个数，{} 把 26 个计数器全部初始化为 0
        for (int i = 0; i < s.size(); ++i) {  // 逐位比较两个字符串
            int x = (t[i] - s[i] + 26) % 26;  // 需要向右循环移动的步数，+26 是为了避免负数取模
            ++cnt[x];  // 这个位移的需求数加 1
        }
        for (int i = 1; i < 26; ++i) {  // 位移 0 表示字符本来就相同，不需要任何操作，从 1 开始检查
            if (i + 26 * (cnt[i] - 1) > k) {  // 第 cnt[i] 个需要位移 i 的字符必须排到第 i + 26*(cnt[i]-1) 次操作
                return false;  // 超过 k 次可用操作，说明无法完成转换
            }
        }
        return true;  // 所有位移需求都能安排在 k 次操作之内，转换可行
    }
};