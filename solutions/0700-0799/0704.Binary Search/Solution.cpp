// 题目：704. 二分查找（Binary Search）
// 思路：在闭区间 [l, r] 上二分，每次用 nums[mid] 与 target 比较把区间收缩一半，最后只剩一个候选位置再判定。
// 时间复杂度：O(log n)，每轮区间减半；空间复杂度：O(1)，只用了几个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口：二分查找方法
    int search(vector<int>& nums, int target) {  // nums 是升序数组，target 是要找的目标值，返回下标或 -1
        int l = 0, r = nums.size() - 1;  // 闭区间 [l, r] 表示当前还可能是答案的范围
        while (l < r) {  // 区间没有收缩到单个元素时继续二分
            int mid = (l + r) >> 1;  // 取中点，右移一位等价于除以 2 并向下取整
            if (nums[mid] >= target) {  // 中点值大于等于目标，答案落在左半边（含 mid 本身）
                r = mid;  // 右端点收缩到 mid，把 mid 保留为候选
            } else {  // 否则中点值小于目标
                l = mid + 1;  // 答案只可能在 mid 右侧，所以排除 mid
            }  // if-else 结束
        }  // while 结束，此时 l == r
        return nums[l] == target ? l : -1;  // 唯一剩下的候选等于目标就返回下标，否则说明不存在，返回 -1
    }  // 方法结束
};  // 类定义结束
