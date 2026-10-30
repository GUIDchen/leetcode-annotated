// 题目：35. 搜索插入位置（Search Insert Position）
// 思路：在有序数组上做左闭右开的二分，区间收缩到 left == right 时，该位置就是第一个 ≥ target 的下标，也就是插入位置。
// 时间复杂度：O(log n)，每次折半；空间复杂度：O(1)，只用三个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int searchInsert(vector<int>& nums, int target) {  // nums 是升序数组，target 是待插入值；返回它应该插入的下标
        int l = 0, r = nums.size();  // 二分区间取左闭右开 [l, r)，初始时 r 取 n，使区间覆盖整个数组
        while (l < r) {  // 区间不为空就继续折半
            int mid = (l + r) >> 1;  // 取中点；右移一位等价于除以 2 并向下取整，比 / 更快且不会溢出
            if (nums[mid] >= target) {  // 中点值 ≥ target 时，答案只可能在左半边（mid 本身也可能是答案）
                r = mid;  // 右边界收缩到 mid，把 mid 保留在候选区间内
            } else {  // 否则 mid 及其左边的元素都 < target，答案一定在右半边
                l = mid + 1;  // 左边界跳到 mid+1，直接排除 mid
            }  // else 分支结束
        }  // while 循环结束，此时 l == r
        return l;  // l 是第一个 ≥ target 的位置，即插入位置
    }  // 方法结束
};  // 类定义结束
