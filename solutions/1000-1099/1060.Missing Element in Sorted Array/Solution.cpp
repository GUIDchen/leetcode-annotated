// 题目：1060. 有序数组中的缺失元素（Missing Element in Sorted Array）
// 思路：missing(i) = nums[i] - nums[0] - i 表示前 i 个元素之间缺失的个数，它随 i 单调不减，于是可二分查找第 k 个缺失值所在的区间。
// 时间复杂度：O(log n)，二分查找；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int missingElement(vector<int>& nums, int k) {  // nums 严格递增，返回第 k 个缺失的正整数
        auto missing = [&](int i) {  // 局部 lambda：计算 nums[0..i] 之间缺失的数字个数
            return nums[i] - nums[0] - i;  // 数值跨度减去已有元素个数，即为缺失个数
        };  // lambda 定义结束
        int n = nums.size();  // 数组长度
        if (k > missing(n - 1)) {  // 第 k 个缺失元素在整个数组之后
            return nums[n - 1] + k - missing(n - 1);  // 从最后一个元素继续往后数出答案
        }  // 越界判断结束
        int l = 0, r = n - 1;  // 二分查找：寻找第一个 missing(i) >= k 的位置
        while (l < r) {  // 区间收缩到单点
            int mid = (l + r) >> 1;  // 取中点，>> 1 等价于除以 2 向下取整
            if (missing(mid) >= k) {  // 第 k 个缺失元素在 mid 或更左侧
                r = mid;  // 收缩右边界
            } else {  // 第 k 个缺失元素在 mid 右侧
                l = mid + 1;  // 收缩左边界
            }  // 分支结束
        }  // 循环结束时 l 是第一个缺失个数 >= k 的下标
        return nums[l - 1] + k - missing(l - 1);  // 从 l-1 这个已知元素开始向后数出答案
    }  // 方法结束
};  // 类定义结束