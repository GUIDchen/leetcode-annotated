// 题目：3698. 分割数组得到最小绝对差（Split Array With Minimum Difference）
// 核心思路：先求前缀和；再正序递推 f[i]（前缀 nums[0..i] 是否严格递增）、逆序递推 g[i]（后缀 nums[i..n-1] 是否严格递减）；最后枚举切点 i，在 f[i] 与 g[i+1] 同时成立时用两段前缀和之差更新最小绝对差。
// 复杂度：时间 O(n)，两趟预处理加一趟枚举；空间 O(n)，存前缀和与两个布尔数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long splitArray(vector<int>& nums) {  // 返回把 nums 切成两段后两段和之差的绝对值的最小值
        int n = nums.size();  // 数组长度
        vector<long long> s(n);  // s[i] 表示 nums[0..i] 的区间和，用 long long 防溢出
        s[0] = nums[0];  // 前缀和的起手元素
        vector<bool> f(n, true), g(n, true);  // f[i]：前缀是否严格递增；g[i]：后缀是否严格递减

        for (int i = 1; i < n; ++i) {  // 从左到右递推前缀和与前缀单调性
            s[i] = s[i - 1] + nums[i];  // 累加得到当前位置的前缀和
            f[i] = f[i - 1];  // 先继承前一位的单调性结论
            if (nums[i] <= nums[i - 1]) {  // 出现不严格递增（含相等）就破坏严格递增
                f[i] = false;  // 标记该前缀不再严格递增
            }  // 结束单调性判断
        }  // 结束前缀扫描
        for (int i = n - 2; i >= 0; --i) {  // 从右到左递推后缀单调性
            g[i] = g[i + 1];  // 先继承后一位的单调性结论
            if (nums[i] <= nums[i + 1]) {  // 出现不严格递减（含相等）就破坏严格递减
                g[i] = false;  // 标记该后缀不再严格递减
            }  // 结束单调性判断
        }  // 结束后缀扫描

        const long long inf = LLONG_MAX;  // 用 long long 最大值作为「无解」哨兵
        long long ans = inf;  // ans 记录两段和之差的最小绝对值
        for (int i = 0; i < n - 1; ++i) {  // 枚举切点 i：左段 nums[0..i]，右段 nums[i+1..n-1]
            if (f[i] && g[i + 1]) {  // 左段严格递增且右段严格递减，该切点合法
                long long s1 = s[i];  // 左段区间和
                long long s2 = s[n - 1] - s[i];  // 右段区间和＝总和减去左段和
                ans = min(ans, llabs(s1 - s2));  // 用当前切点的绝对差更新答案
            }  // 结束合法性判断
        }  // 结束切点枚举
        return ans < inf ? ans : -1;  // 没有合法切点返回 -1，否则返回最小绝对差
    }  // 结束 splitArray
};  // 结束题解类
