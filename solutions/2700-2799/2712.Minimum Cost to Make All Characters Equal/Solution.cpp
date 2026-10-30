// 题目：2712. 使所有字符相等的最小成本（Minimum Cost to Make All Characters Equal）
// 思路：只在相邻字符不同的位置动手；此处要么翻转前 i 个字符（成本 i），要么翻转后 n-i 个（成本 n-i），取较小者累加。
// 时间复杂度：O(n)，一次线性遍历；空间复杂度：O(1)，只用到若干个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumCost(string s) {  // s：只含 '0' 和 '1' 的字符串，返回使其全部相等的最小成本
        long long ans = 0;  // ans：累计的最小总成本，可能超过 32 位所以用 long long
        int n = s.size();  // n：字符串长度，循环与代价计算都要用
        for (int i = 1; i < n; ++i) {  // 从左到右检查每一对相邻字符
            if (s[i] != s[i - 1]) {  // 相邻字符不同，说明这条缝隙必须被某次翻转跨过
                ans += min(i, n - i);  // 翻前 i 个字符花 i，翻后 n-i 个花 n-i，取更便宜的一侧
            }
        }
        return ans;  // 返回累加得到的最小总成本
    }
};