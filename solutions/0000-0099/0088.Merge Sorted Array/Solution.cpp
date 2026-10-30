// 题目：88. 合并两个有序数组（Merge Sorted Array）
// 思路：从后往前双指针归并。nums1 尾部有 n 个空位，先把较大的元素放到 nums1 末尾，避免覆盖尚未比较的小元素。
// 时间复杂度：O(m + n)，每个元素最多被放一次；空间复杂度：O(1)，只用了三个下标变量。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {  // nums1 前 m 个有效、后面 n 个空位；把 nums2 的 n 个元素并入
        for (int i = m - 1, j = n - 1, k = m + n - 1; ~j; --k) {  // i/j 分别指向两数组有效末尾，k 指向写入位置；~j 等价于 j != -1，即 nums2 还没放完
            nums1[k] = i >= 0 && nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];  // 取两者中较大者放到 k：nums1 空了就直接取 nums2（j 递减），相等时也优先取 nums2
        }
    }
};