// 题目：154. 寻找旋转排序数组中的最小值 II（Find Minimum in Rotated Sorted Array II）
// 思路：二分。每轮比较 nums[mid] 与 nums[r]：大于则答案在右半段，小于则答案在 [l, mid]，等值无法区分时让 r-- 丢掉一个重复元素。
// 时间复杂度：平均 O(log n)，最坏 O(n)（元素全部相等时会逐个收缩）；空间复杂度：O(1)，只用了 l、r、mid 三个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMin(vector<int>& nums) {  // nums：旋转后被部分打乱的升序数组，且可能含有重复元素
        int l = 0, r = nums.size() - 1;  // 闭区间 [l, r] 表示当前答案可能存在的范围，l 从左端开始，r 指向最右端
        while (l < r) {  // 区间缩到只剩一个元素时它必是最小值，因此用 l < r 作为继续搜索的条件
            int mid = (l + r) >> 1;  // 取中点下标；(l + r) >> 1 等价于向下取整地除以 2
            if (nums[mid] > nums[r]) {  // 中点值大于右端值：说明 mid 右侧出现过下降，最小值一定在那一边
                l = mid + 1;  // 丢弃含 mid 的左半段，把下界推到 mid + 1
            } else if (nums[mid] == nums[r]) {  // 中点值等于右端值：无法判断最小值在左还是右，但 r 处元素可被 mid 处的等值元素替代
                r--;  // 安全地丢掉一个重复元素，缩小搜索范围而不丢失答案
            } else {  // 中点值小于右端值：[mid, r] 这段是升序的，最小值不会在 mid 右侧
                r = mid;  // 答案可能就是 mid 本身，所以保留 mid，把上界收缩到 mid
            }  // 循环结束，此时 l == r，区间只剩一个元素
        }  // 返回剩下的那个元素，即数组最小值
        return nums[l];  // 题解方法结束
    }  // 题解类定义结束
};
