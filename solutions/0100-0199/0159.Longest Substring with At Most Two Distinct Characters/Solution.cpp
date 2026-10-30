// 题目：159. 至多包含两个不同字符的最长子串（Longest Substring with At Most Two Distinct Characters）
// 思路：滑动窗口（双指针）。右指针逐个扩窗并计数，字符种类超过 2 时左指针收缩，每次收缩后更新答案。
// 时间复杂度：O(n)，i、j 都只单调右移；空间复杂度：O(1)，哈希表最多存 3 个不同字符的计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lengthOfLongestSubstringTwoDistinct(string s) {  // s：输入字符串；返回至多含两种字符的最长子串长度
        unordered_map<char, int> cnt;  // 窗口内每种字符出现的次数，键是字符、值是次数
        int n = s.size();  // 字符串长度，避免循环里反复调用 size()
        int ans = 0;  // 记录历史最大窗口长度
        for (int i = 0, j = 0; i < n; ++i) {  // i 是右边界（扩张），j 是左边界（收缩），两者都从 0 出发
            cnt[s[i]]++;  // 把新字符计入窗口
            while (cnt.size() > 2) {  // 字符种类超过 2 时窗口不合法，需要收缩左边界
                cnt[s[j]]--;  // 把左边界的字符计数减一
                if (cnt[s[j]] == 0) {  // 该字符在窗口内已经消失
                    cnt.erase(s[j]);  // 从哈希表中删除它，保证 cnt.size() 反映的是窗口内的真实种类数
                }  // 删除操作结束
                ++j;  // 左边界右移一位，继续尝试收缩
            }  // 收缩结束，此时窗口内至多两种字符
            ans = max(ans, i - j + 1);  // 用当前合法窗口长度 i-j+1 更新答案
        }  // 外层循环结束
        return ans;  // 返回记录到的最大长度
    }  // 题解方法结束
};  // 题解类定义结束