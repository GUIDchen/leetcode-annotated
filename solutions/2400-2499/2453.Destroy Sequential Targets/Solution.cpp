// 题目：2453. 摧毁一系列目标（Destroy Sequential Targets）
// 思路：能被同一轮摧毁的目标，其值对 space 取模的余数相同；先用哈希表统计每个余数类的目标个数，再按原数组顺序挑出所在类最大（同大小取值更小者）的目标。
// 时间复杂度：O(n)，对数组做两遍线性扫描；空间复杂度：O(n)，哈希表最多保存 n 个不同的余数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int destroyTargets(vector<int>& nums, int space) {  // nums：目标值数组；space：每轮推进的距离
        unordered_map<int, int> cnt;  // 哈希表：键为对 space 取模的余数，值为该余数类中目标的个数
        for (int v : nums) ++cnt[v % space];  // 第一遍：统计每个余数类各有多少个目标
        int ans = 0, mx = 0;  // ans 记录答案值，mx 记录当前最优余数类的大小
        for (int v : nums) {  // 第二遍：在原数组中挑选最合适的起始目标
            int t = cnt[v % space];  // 以当前目标为起点时，同一轮能摧毁的目标总数
            if (t > mx || (t == mx && v < ans)) {  // 数量更多，或数量相同但值更小（题目要求取最小值）
                ans = v;  // 更新答案
                mx = t;  // 更新当前最优数量
            }
        }
        return ans;  // 返回摧毁目标数最多时可选的最小起始目标值
    }
};