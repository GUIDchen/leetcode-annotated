// 题目：4. 寻找两个正序数组的中位数（Median of Two Sorted Arrays）
// 思路：把中位数转化为「第 k 小」，每轮比较两数组第 k/2 个元素，一次排除整体更小的那一半，递归缩小 k。
// 时间复杂度：O(log(m + n))，k 每层减半；空间复杂度：O(log(m + n))，递归调用栈的深度。
int findKth(int* nums1, int m, int i, int* nums2, int n, int j, int k) {  // 在 nums1[i..] 与 nums2[j..] 中找第 k 小的数（k 从 1 开始）
    if (i >= m)  // nums1 这一段已取空
        return nums2[j + k - 1];  // 答案只能来自 nums2 的第 k 个元素
    if (j >= n)  // nums2 这一段已取空
        return nums1[i + k - 1];  // 答案只能来自 nums1 的第 k 个元素
    if (k == 1)  // 只需要 1 个元素时
        return nums1[i] < nums2[j] ? nums1[i] : nums2[j];  // 取两个候选头部的较小者

    int p = k / 2;  // 每轮比较的步长，正好是 k 的一半

    int x = (i + p - 1 < m) ? nums1[i + p - 1] : INT_MAX;  // nums1 的第 p 个候选；越界时用 INT_MAX 当哨兵，保证它不会被淘汰别人
    int y = (j + p - 1 < n) ? nums2[j + p - 1] : INT_MAX;  // nums2 的第 p 个候选，越界同样用哨兵

    if (x < y)  // nums1 的前 p 个元素整体更小
        return findKth(nums1, m, i + p, nums2, n, j, k - p);  // 淘汰它们，指针前进 p，k 减去 p 继续找
    else  // 否则 nums2 的前 p 个元素整体更小
        return findKth(nums1, m, i, nums2, n, j + p, k - p);  // 淘汰 nums2 的前 p 个，k 减去 p 继续找
}

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {  // m、n 分别为两有序数组长度，返回合并后的中位数
    int total = m + n;  // 元素总数
    int a = findKth(nums1, m, 0, nums2, n, 0, (total + 1) / 2);  // 左中位数：第 (total+1)/2 小
    int b = findKth(nums1, m, 0, nums2, n, 0, (total + 2) / 2);  // 右中位数；total 为奇数时 a、b 是同一个数
    return (a + b) / 2.0;  // 除以 2.0（而不是 2）得到浮点中位数
}
