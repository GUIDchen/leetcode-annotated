// 题目：162. 寻找峰值（Find Peak Element）
// 核心思路：比较 nums[mid] 与 nums[mid+1] 判断上坡还是下坡，二分把区间收缩到必然包含峰值的半边，最终锁定唯一峰值。
// 时间复杂度：O(log n)，每轮区间减半；空间复杂度：O(1)，只用常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findPeakElement(vector<int>& nums) {  // nums：相邻元素互不相同的数组，两端视为 -∞，因此必有峰值
        int left = 0, right = nums.size() - 1;  // 二分区间 [left, right]，初始覆盖整个数组
        while (left < right) {  // 区间只剩一个下标时，该位置就是峰值，结束循环
            int mid = left + right >> 1;  // 取中点；+ 的优先级高于 >>，等价于 (left + right) / 2 且不会溢出
            if (nums[mid] > nums[mid + 1]) {  // nums[mid] 大于右邻居：处于下坡，峰值必在 mid 或其左侧
                right = mid;  // 保留 mid，因为它本身可能就是峰值
            } else {  // 否则处于上坡，峰值必在 mid 右侧
                left = mid + 1;  // 丢弃 mid：它比右邻居小，不可能是峰值
            }
        }  // 收缩到唯一的峰值下标并返回
        return left;
    }
};