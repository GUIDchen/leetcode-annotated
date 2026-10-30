// 3904. 最小稳定下标 II（Smallest Stable Index II）
// 思路：预处理每个位置的后缀最小值，再从左往右维护前缀最大值；第一个满足「前缀最大值 - 后缀最小值 <= k」的位置就是最小稳定下标。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int firstStableIndex(vector<int>& nums, int k) {  // nums：输入数组；k：允许的最大差值
        int n = nums.size();  // 数组长度
        vector<int> right(n);  // right[i] 表示 nums[i..n-1] 的最小值
        right[n - 1] = nums[n - 1];  // 最后一个位置的后缀最小值就是它自己

        for (int i = n - 2; i >= 0; --i) {  // 从右往左递推，填出每个位置的后缀最小值
            right[i] = min(right[i + 1], nums[i]);  // 后缀最小值 = min(右侧后缀最小值, 当前元素)
        }  // 后缀最小值预处理结束

        int left = 0;  // left 维护 nums[0..i] 的前缀最大值
        for (int i = 0; i < n; ++i) {  // 从左往右扫描，第一个满足条件的位置就是答案
            left = max(left, nums[i]);  // 更新前缀最大值
            if (left - right[i] <= k) {  // 该位置前缀最大值与后缀最小值之差不超过 k
                return i;  // 下标从小到大扫描，首次命中即最小稳定下标
            }  // 不满足则继续向右找
        }  // 扫描结束
        return -1;  // 没有稳定下标，按题意返回 -1
    }  // 方法结束
};  // 类定义结束
