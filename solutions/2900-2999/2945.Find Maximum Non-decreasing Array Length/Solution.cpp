// 题目：2945. 找到最大非递减数组的长度（Find Maximum Non-decreasing Array Length）
// 思路：DP + 前缀和 + 二分。f[i] 是前 i 个元素能合并出的最大段数，pre[i] 记录取到该段数时最后一段的前驱位置；再用 lower_bound 求出哪些后继位置可以把 i 当作前驱，并用「前缀取最大」把前驱信息向后传播。
// 时间复杂度：O(n log n)，每轮一次二分；空间复杂度：O(n)，存放前缀和与两个 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMaximumLength(vector<int>& nums) {  // nums 是待合并的数组，返回合并后非递减数组的最大长度
        int n = nums.size();  // 数组长度
        int f[n + 1];  // f[i]：把前 i 个元素合并成非递减序列时能得到的最大段数
        int pre[n + 2];  // pre[i]：f[i] 取到最优时最后一段的前驱位置；多留一格保证 j == n+1 时不越界
        long long s[n + 1];  // 前缀和：s[i] 表示前 i 个元素之和，用 long long 防止累加溢出
        for (int i = 0; i < n; ++i) {  // 逐项累加，构造前缀和数组
            s[i + 1] = s[i] + nums[i];  // s[i+1] = 前 i 项之和 + 第 i 个元素
        }
        memset(f, 0, sizeof(f));  // f 全部初始化为 0
        memset(pre, 0, sizeof(pre));  // pre 全部初始化为 0
        for (int i = 1; i <= n; ++i) {  // 按前缀长度从小到大递推
            pre[i] = max(pre[i], pre[i - 1]);  // 前缀最大值传播：保证 pre[i] 指向最靠后、仍然可用的前驱
            f[i] = f[pre[i]] + 1;  // 在最优前驱的基础上再切出一段，段数加一
            int j = lower_bound(s, s + n + 1, s[i] * 2 - s[pre[i]]) - s;  // 找出第一个前缀和 >= 2*s[i]-s[pre[i]] 的位置 j：从 j 起，下一段的和不小于当前段
            pre[j] = i;  // 把 i 登记为 j 的前驱候选，交由下一轮的 pre 前缀最大化生效
        }
        return f[n];  // 前 n 个元素的最大段数即答案
    }
};