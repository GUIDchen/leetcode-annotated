// 题目：153. 寻找旋转排序数组中的最小值（Find Minimum in Rotated Sorted Array）
// 思路：二分——把 nums[mid] 与数组末尾比较，比末尾大说明 mid 落在前面那段升序里，最小值在右半段，否则在左半段（含 mid）。
// 时间复杂度：O(log n)，每次区间减半；空间复杂度：O(1)，只用左右边界与 mid。
class Solution {  // 题目要求的题解类
public:  // 对外提供 findMin 方法
    int findMin(vector<int>& nums) {  // nums 是旋转过的升序数组，返回其中的最小值
        int l = 0, r = nums.size() - 1;  // 二分区间 [l, r]，答案一定落在里面
        while (l < r) {  // 区间收缩到只剩一个元素时结束
            int mid = (l + r) >> 1;  // 取中点，右移一位等价于除以 2
            if (nums[mid] > nums.back()) {  // 中点比末尾大，说明它在旋转点左侧的升序段里
                l = mid + 1;  // 最小值一定在右半段，mid 可以排除
            } else {  // 否则中点在右半段（不大于末尾）
                r = mid;  // 最小值可能是 mid 自己，区间右端收到 mid
            }
        }  // 区间只剩一个元素
        return nums[l];  // 这个元素就是最小值
    }  // findMin 方法结束
};  // Solution 类定义结束
