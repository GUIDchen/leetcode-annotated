// 题目：81. 搜索旋转排序数组 II（Search in Rotated Sorted Array II）
// 思路：带重复元素的旋转数组二分。每次把 nums[mid] 与右端点 nums[r] 比较，确定哪一半有序，再判断 target 是否落在有序的一半里；相等时无法判断，只能右端点左移一格。
// 时间复杂度：最坏 O(n)（大量重复元素时退化为线性），平均 O(log n)；空间复杂度：O(1)，只用了常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool search(vector<int>& nums, int target) {  // nums 是旋转过的非递减数组（可能含重复），要判断 target 是否存在
        int l = 0, r = nums.size() - 1;  // 二分查找的闭区间 [l, r]
        while (l < r) {  // 区间还剩不止一个元素时继续二分，结束时 l == r 为唯一候选位置
            int mid = (l + r) >> 1;  // 取中点，右移一位等价于整除 2 向下取整
            if (nums[mid] > nums[r]) {  // 中点大于右端点，说明左半段 [l, mid] 是递增有序的
                if (nums[l] <= target && target <= nums[mid]) {  // target 落在有序的左半段内
                    r = mid;  // 收缩到左半段 [l, mid]
                } else {  // target 不在有序段内，只能去右半段
                    l = mid + 1;  // 丢弃 mid，收缩到 [mid + 1, r]
                }
            } else if (nums[mid] < nums[r]) {  // 中点小于右端点，说明右半段 [mid, r] 是递增有序的
                if (nums[mid] < target && target <= nums[r]) {  // target 落在有序的右半段内（mid 本身已知不满足）
                    l = mid + 1;  // 收缩到右半段 (mid, r]
                } else {  // target 不在有序段内，只能去左半段
                    r = mid;  // 保留 mid，收缩到 [l, mid]
                }
            } else {  // nums[mid] == nums[r]，重复元素导致无法判断哪一半有序
                --r;  // 只能把右端点左移一格去重，这一步让最坏情况退化为 O(n)
            }
        }
        return nums[l] == target;  // 区间只剩一个元素，判断它是否等于 target
    }
};