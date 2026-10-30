// 题目：3800. 使二进制字符串相等的最小成本（Minimum Cost to Make Two Binary Strings Equal）
// 思路：先统计 s 与 t 不同位置上「s 为 0」与「s 为 1」的数量，再枚举三种操作组合（全翻转 / 交换+翻转 / 交叉+交换+翻转）取最小值。
// 时间复杂度：O(n)，一趟扫描统计差异；空间复杂度：O(1)，只用了常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost) {  // s、t 是等长二进制串，flip/swap/cross 分别是三种操作的成本
        long long diff[2] = {0, 0};  // diff[0]、diff[1]：s 为 0 / 1 而 t 不同的位置数量
        int n = s.size();  // 串长
        for (int i = 0; i < n; i++) {  // 逐位比较两串
            if (s[i] != t[i]) {  // 该位不同
                diff[s[i] - '0']++;  // 按 s 上的字符（'0' 或 '1'）分类计数
            }  // 结束 if (s[i] != t[i])
        }  // 结束 for (int i = 0; i < n; i++)

        long long ans = (diff[0] + diff[1]) * flipCost;  // 方案一：所有不同的位都逐个翻转

        long long mx = max(diff[0], diff[1]);  // 两类不匹配数量的较大者
        long long mn = min(diff[0], diff[1]);  // 两类不匹配数量的较小者
        ans = min(ans, mn * 1LL * swapCost + (mx - mn) * flipCost);  // 方案二：先两两交换 min 对，剩下 (mx-mn) 位单独翻转

        long long avg = (mx + mn) / 2;  // 方案三的折中点：用交叉操作把两类数量拧成一样
        ans = min(ans, (avg - mn) * crossCost + avg * swapCost + (mx + mn - avg * 2) * flipCost);  // 方案三：交叉操作 + 剩余两两交换 + 可能的单点翻转，取最小值

        return ans;  // 三种方案的最小值即为答案
    }  // 结束 long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost)
};  // 结束 class Solution
