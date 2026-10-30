// 题目：3365. 重排子字符串以形成目标字符串（Rearrange K Substrings to Form Target String）
// 思路：把 s 与 t 各切成 k 段等长子串，用哈希表做「s 段 +1、t 段 -1」的计数差分，计数全为 0 即说明可以重排成功。
// 时间复杂度：O(n) 期望，切段与哈希计数的总代价为线性；空间复杂度：O(k)，最多保存 k 个不同子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPossibleToRearrange(string s, string t, int k) {  // s：原串；t：目标串；k：要求切成的段数
        unordered_map<string, int> cnt;  // 哈希表：键是子串，值是「s 中出现次数 - t 中出现次数」
        int n = s.size();  // 字符串长度
        int m = n / k;  // 每段的长度，题目保证 n 能被 k 整除
        for (int i = 0; i < n; i += m) {  // 按固定长度 m 顺序切段，共 k 段
            cnt[s.substr(i, m)]++;  // s 的第 i 段出现次数 +1
            cnt[t.substr(i, m)]--;  // t 的第 i 段出现次数 -1，两边抵消后只需检查差值是否为 0
        }  // 切段结束
        for (auto& [_, v] : cnt) {  // 遍历哈希表中所有子串的计数差
            if (v) {  // 差值非 0 说明这段子串在两边数量不匹配
                return false;  // 无法通过重排得到目标串
            }  // 结束条件判断
        }  // 遍历结束
        return true;  // 所有段的计数都抵消了，说明可以重排成 t
    }  // 方法结束
};  // 类定义结束
