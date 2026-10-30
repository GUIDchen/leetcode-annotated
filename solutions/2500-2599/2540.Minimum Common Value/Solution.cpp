// 题目：2540. 最小公共值（Minimum Common Value）
// 思路：双指针利用升序性质，每次让较小的一侧前进，第一次相等即最小公共值。
// 时间复杂度：O(m + n)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getCommon(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 均为升序，返回最小公共值
        int m = nums1.size(), n = nums2.size();  // m、n 分别为两个数组的长度
        for (int i = 0, j = 0; i < m && j < n;) {  // 双指针：i 扫 nums1，j 扫 nums2，自增写在循环体内
            if (nums1[i] == nums2[j]) {  // 两值相等，即为最小公共值
                return nums1[i];  // 直接返回
            }  // if 结束
            if (nums1[i] < nums2[j]) {  // nums1[i] 偏小，只能右移 i 去追
                ++i;  // i 右移一位
            } else {  // 否则 nums2[j] 偏小
                ++j;  // j 右移一位
            }  // else 结束
        }  // while 结束，无公共值
        return -1;  // 返回 -1
    }  // 方法结束
};  // 类定义结束