// 题目：2771. 构造最长非递减子数组（Longest Non-decreasing Subarray From Two Arrays）
// 思路：线性 DP。f 表示以 i 结尾、第 i 位选 nums1[i] 的最长非递减长度，g 表示第 i 位选 nums2[i] 的最长长度，按相邻两位的四种选法转移。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只有常数个状态变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 是两个长度相同的备选数组
        int n = nums1.size();  // 数组长度，两数组等长
        int f = 1, g = 1;  // 初始状态：只含第 0 个元素时，选 nums1[0] 或 nums2[0] 的长度都是 1
        int ans = 1;  // 答案至少为 1，单个元素本身就是非递减的
        for (int i = 1; i < n; ++i) {  // 从下标 1 开始逐个向右扩展子数组
            int ff = 1, gg = 1;  // 本层的新状态，先按“只含当前元素”初始化
            if (nums1[i] >= nums1[i - 1]) {  // 情况一：当前位与前一位都选 nums1，且值不下降
                ff = max(ff, f + 1);  // 可以接在 f 后面，长度加一
            }
            if (nums1[i] >= nums2[i - 1]) {  // 情况二：当前位选 nums1、前一位选 nums2，且值不下降
                ff = max(ff, g + 1);  // 可以接在 g 后面，长度加一
            }
            if (nums2[i] >= nums1[i - 1]) {  // 情况三：当前位选 nums2、前一位选 nums1，且值不下降
                gg = max(gg, f + 1);  // 可以接在 f 后面，长度加一
            }
            if (nums2[i] >= nums2[i - 1]) {  // 情况四：当前位与前一位都选 nums2，且值不下降
                gg = max(gg, g + 1);  // 可以接在 g 后面，长度加一
            }
            f = ff;  // 滚动更新：用本层结果覆盖旧状态 f
            g = gg;  // 滚动更新：用本层结果覆盖旧状态 g
            ans = max(ans, max(f, g));  // 两种结尾方式中的较大者参与更新全局答案
        }
        return ans;  // 返回最长非递减子数组的长度
    }
};