// 题目：2540. 最小公共值（Minimum Common Value）
// 思路：两数组均升序，用双指针从前往后扫；小的那一侧右移，相等即为最小公共值。
// 时间复杂度：O(m + n)；空间复杂度：O(1)，只用两个下标。
int getCommon(int* nums1, int nums1Size, int* nums2, int nums2Size) {  // nums1、nums2 已升序，返回最小公共值
    int i = 0;  // i 指向 nums1 当前比较位置
    int j = 0;  // j 指向 nums2 当前比较位置
    while (i < nums1Size && j < nums2Size) {  // 两个指针都还没越界时继续
        if (nums1[i] == nums2[j]) {  // 值相等；指针只从小到大推进，所以这就是最小的公共值
            return nums1[i];  // 立即返回该值
        }  // if 结束
        if (nums1[i] < nums2[j]) {  // nums1[i] 偏小，它不可能再和 nums2 后面的元素相等
            i++;  // 跳过 nums1 的当前元素
        } else {  // 否则是 nums2[j] 偏小
            j++;  // 跳过 nums2 的当前元素
        }  // else 结束
    }  // while 结束，说明没有公共值
    return -1;  // 按题目要求返回 -1
}  // 函数结束