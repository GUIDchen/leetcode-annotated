// 题目：2036. 最大交替子数组和（Maximum Alternating Subarray Sum）
// 思路：动态规划。设 f 为「以当前元素结尾且当前元素取正号」的最大交替和，g 为「以当前元素结尾且当前元素取负号」的最大交替和；转移为 f = max(g, 0) + x、g = f_old - x，答案取所有 f、g 的最大值。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只需常数个状态变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumAlternatingSubarraySum(vector<int>& nums) {  // nums 是输入数组，返回任意子数组的最大交替和
        using ll = long long;  // 用短别名简化后面 long long 的书写
        const ll inf = 1LL << 60;  // 用一个足够小的数表示「负无穷」，作为不可能状态的哨兵
        ll ans = -inf, f = -inf, g = -inf;  // ans 记录全局最优；f/g 是两种结尾状态的 DP 值，初始都不可达
        for (int x : nums) {  // 遍历数组中的每个元素
            ll ff = max(g, 0LL) + x;  // 新状态：当前元素取正号；g 为负时不如从当前元素重新开始，所以和 0 取 max
            g = f - x;  // 新状态：当前元素取负号，必须接在「取正号」的状态后面（用旧 f 值）
            f = ff;  // 把刚算出的 ff 写回 f，保证 g 用的是上一轮的 f
            ans = max({ans, f, g});  // 答案可能停在任一符号的位置，所以 f、g 一起比较
        }  // 结束遍历
        return ans;  // 返回最大交替子数组和
    }  // 结束 maximumAlternatingSubarraySum
};  // 结束 Solution 类