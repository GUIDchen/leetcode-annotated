// 题目：33. 搜索旋转排序数组（Search in Rotated Sorted Array）
// 思路：改进的二分查找。每次取中点 mid 后，判断 mid 落在「左半段（升序且含最小值）」还是「右半段」，再根据 target 是否落在该侧的有序区间内，决定收缩左边界还是右边界；循环结束时二分到唯一候选 left，再验证它是否等于 target。
// 时间复杂度：O(log n)，每次折半；空间复杂度：O(1)，只用常数个边界变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int search(vector<int>& nums, int target) {  // nums：旋转后的升序数组；target：要找的值；返回下标或 -1
        int n = nums.size();  // 数组长度
        int left = 0, right = n - 1;  // 二分区间为闭区间 [left, right]
        while (left < right) {  // 区间长度大于 1 时继续二分；退出时 left == right 只剩唯一候选
            int mid = (left + right) >> 1;  // 取中点，右移一位等于除以 2（向下取整）
            if (nums[0] <= nums[mid]) {  // mid 落在左半段：从 nums[0] 到 nums[mid] 是单调递增的
                if (nums[0] <= target && target <= nums[mid])  // target 在这个有序区间内部
                    right = mid;  // 目标只能在左半边，含 mid，收缩右边界
                else  // target 不在这个有序区间内
                    left = mid + 1;  // 排除 mid 及其左侧，去右半边找
            } else {  // mid 落在右半段：从 nums[mid] 到 nums[n-1] 是单调递增的
                if (nums[mid] < target && target <= nums[n - 1])  // target 在右侧有序区间内部（不含 mid）
                    left = mid + 1;  // 排除 mid 及其左侧，去右半边找
                else  // 否则目标只可能在左半边
                    right = mid;  // 收缩右边界，保留 mid 作为候选
            }
        }
        return nums[left] == target ? left : -1;  // 二分收敛后唯一候选若等于目标就返回下标，否则说明不存在
    }
};
