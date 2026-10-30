// 题目：2321. 拼接数组的最大分数（Maximum Score Of Spliced Array）
// 核心思路：一次拼接等价于「用 nums2 的一段换掉 nums1 的同段」，答案 = sum(nums2) + 差值数组 nums1-nums2 的最大子段和，两个方向各算一次取较大值。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用到常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两个等长的输入数组
        int s1 = 0, s2 = 0, n = nums1.size();  // s1、s2 分别记录两数组的总和；n 是数组长度
        for (int i = 0; i < n; ++i) {  // 一次遍历同时求两个数组的元素和
            s1 += nums1[i];  // 累加 nums1 的第 i 个元素
            s2 += nums2[i];  // 累加 nums2 的第 i 个元素
        }  // 结束求和循环
        return max(s2 + f(nums1, nums2), s1 + f(nums2, nums1));  // 两种替换方向（用 nums2 的段换 nums1 的段 / 反之）各算一次，取较大值
    }

    int f(vector<int>& nums1, vector<int>& nums2) {  // 辅助函数：求差值数组 nums1-nums2 的最大子段和
        int t = nums1[0] - nums2[0];  // t：以当前位置结尾的最大子段和
        int mx = t;  // mx：全局最大子段和
        for (int i = 1; i < nums1.size(); ++i) {  // 从下标 1 开始线性递推（Kadane 算法）
            int v = nums1[i] - nums2[i];  // 当前位置的差值
            if (t > 0)  // 前面的子段和为正，接上当前差值更划算
                t += v;  // 延长子段
            else  // 否则（前面子段和非正）
                t = v;  // 丢弃之前的子段，从当前位置重新开始
            mx = max(mx, t);  // 更新全局最大子段和
        }  // 结束递推循环
        return mx;  // 返回最大子段和
    }
};