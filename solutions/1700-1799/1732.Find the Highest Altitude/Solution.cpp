// 题目：1732. 找到最高海拔（Find the Highest Altitude）
// 思路：把高差数组当作前缀和，遍历时累加出当前海拔，并不断更新最大值（起点海拔 0 也算）。
// 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用两个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largestAltitude(vector<int>& gain) {  // gain 是相邻两点的海拔差数组
        int ans = 0, h = 0;  // ans 记录最高海拔，h 是当前海拔（起点按 0 计）
        for (int v : gain) h += v, ans = max(ans, h);  // 逗号表达式：先累加当前海拔，再用它更新答案
        return ans;  // 返回出现过的最高海拔
    }  // 方法结束
};  // 类结束