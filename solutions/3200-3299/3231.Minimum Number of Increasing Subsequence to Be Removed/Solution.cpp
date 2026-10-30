// 题目：3231. 要删除的递增子序列的最小数量（Minimum Number of Increasing Subsequence to Be Removed）
// 思路：由 Dilworth 定理，覆盖整个数组所需的最少递增子序列数等于最长非递增子序列的长度；用耐心排序维护一条非递增的堆顶序列 g，二分找第一个小于 x 的位置替换或追加。
// 时间复杂度：O(n log n)，每个元素二分一次；空间复杂度：O(n)，最坏情况下 g 存下全部元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums：待删除的数组；返回所需的递增子序列最少数量
        vector<int> g;  // g 维护一条非递增的堆顶序列，它的长度就是答案
        for (int x : nums) {  // 依次把每个元素插入 g
            int l = 0, r = g.size();  // 二分查找的左右边界（半开区间）
            while (l < r) {  // 找第一个满足 g[l] < x 的下标 l
                int mid = (l + r) >> 1;  // 取中点
                if (g[mid] < x) {  // g 是非递增的，条件成立时答案一定在左半区
                    r = mid;  // 收缩右边界
                } else {  // g[mid] >= x，插入点还在右边
                    l = mid + 1;  // 收缩左边界
                }  // 二分结束，l 即插入位置
            }  // 循环结束
            if (l == g.size()) {  // l 越界说明 g 中没有比 x 更小的元素
                g.push_back(x);  // 需要新开一条子序列，把 x 追加到末尾
            } else {  // 否则找到了可替换的位置
                g[l] = x;  // 用更小的 x 替换，让序列更平缓，给后续元素留出空间
            }  // 插入分支结束
        }  // 遍历结束
        return g.size();  // 由 Dilworth 定理，g 的长度就是最少递增子序列数
    }  // 方法结束
};  // 类定义结束