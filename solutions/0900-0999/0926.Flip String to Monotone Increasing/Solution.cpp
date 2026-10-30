// 题目：926. 将字符串翻转到单调递增（Flip String to Monotone Increasing）
// 思路：枚举分界点 i，让前缀全为 0、后缀全为 1；代价 = 前缀中 1 的个数 + 后缀中 0 的个数，用 0 的总数和前缀 0 的计数 O(1) 求出。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minFlipsMonoIncr(string s) {  // s：只含 '0' 和 '1' 的字符串
        int tot = count(s.begin(), s.end(), '0');  // 统计整个串中 '0' 的总数，用来快速算出后缀 0 的个数
        int ans = tot, cur = 0;  // ans 先设为「全部翻成 1」的代价；cur 记录当前前缀中 '0' 的个数
        for (int i = 1; i <= s.size(); ++i) {  // 枚举分界点 i：前 i 个字符全变 0，后面全变 1（i 从 1 开始）
            cur += s[i - 1] == '0';  // 把 s[i-1] 纳入前缀，若它是 '0' 则前缀 0 的计数加一
            ans = min(ans, i - cur + tot - cur);  // 代价 = 前缀 1 的个数 (i-cur) + 后缀 0 的个数 (tot-cur)
        }  // for 结束
        return ans;  // 返回所有分界点中的最小代价
    }  // 方法结束
};  // 类定义结束