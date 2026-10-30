// 题目：702. 搜索长度未知的有序数组（Search in a Sorted Array of Unknown Size 🔒）
// 思路：先以倍增方式把右端点 r 扩大到「取值 >= target」为止，确定答案所在的区间 [r/2, r]，再在这个区间里做标准二分查找。
// 时间复杂度：O(log n)，倍增与二分都是对数级；空间复杂度：O(1)，只用了常数个变量。
/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int search(const ArrayReader& reader, int target) {  // reader 提供按下标取值（越界返回 2^31-1），返回 target 的下标或 -1
        int r = 1;  // 右端点从 1 开始，用倍增的方式向外扩展
        while (reader.get(r) < target) {  // 右端点的值还小于目标，说明答案在更右边
            r <<= 1;  // 左移一位等价于乘 2，把搜索区间右边界翻倍
        }
        int l = r >> 1;  // 上一次的右端点（除以 2）必然是第一个可能的下界
        while (l < r) {  // 在 [l, r] 上做二分查找，区间收敛到单点
            int mid = (l + r) >> 1;  // 取中点，右移一位即向下取整的折半
            if (reader.get(mid) >= target) {  // 中点的值不小于目标，答案在左半边（含 mid）
                r = mid;  // 收缩右边界到 mid
            } else {  // 中点的值小于目标，答案在右半边
                l = mid + 1;  // 收缩左边界到 mid + 1
            }
        }
        return reader.get(l) == target ? l : -1;  // 最终位置的取值等于目标则返回下标，否则说明不存在
    }
};
