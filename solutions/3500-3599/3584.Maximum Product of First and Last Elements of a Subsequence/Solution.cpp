// 3584. 子序列首尾元素的最大乘积（Maximum Product of First and Last Elements of a Subsequence）
// 核心思路：枚举子序列末端下标，用滑动窗口维护可作首元素区间的最小值与最大值，分别与末端值相乘取最优。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)，其中 n 为数组长度。
class Solution {  // 定义题解类
public:  // 公有接口，判题器从这里调用
    long long maximumProduct(vector<int>& nums, int m) {  // 求长度为 m 的子序列首尾元素的最大乘积
        long long ans = LLONG_MIN;  // 答案初始化为最小 long long
        int mx = INT_MIN;  // 窗口首元素可选值的最大值
        int mi = INT_MAX;  // 窗口首元素可选值的最小值
        for (int i = m - 1; i < nums.size(); ++i) {  // 枚举子序列末端下标 i
            int x = nums[i];  // 当前末端元素
            int y = nums[i - m + 1];  // 当前可入选为子序列首元素的最左位置上的值
            mi = min(mi, y);  // 用新进入候选范围的值更新最小值
            mx = max(mx, y);  // 用新进入候选范围的值更新最大值
            ans = max(ans, max(1LL * x * mi, 1LL * x * mx));  // 末端为正时乘最大值，为负时乘最小值，取更优解
        }  // 结束枚举
        return ans;  // 返回最大乘积
    }  // 结束函数
};  // 结束类定义
