// 题目：2425. 所有数对的异或和（Bitwise XOR of All Pairings）
// 核心思路：每个数对取异或后全部再取异或，等价于 nums1 中每个元素重复 |nums2| 次、nums2 中每个元素重复 |nums1| 次；同一个数异或偶数次会自身抵消，因此只在另一个数组长度为奇数时才把它整体异或进来。
// 时间复杂度：O(n + m)，最多各遍历一次；空间复杂度：O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 是两个输入数组，返回所有数对的异或和
        int ans = 0;  // 累加器：异或的单位元是 0，从 0 开始不影响结果
        if (nums2.size() % 2 == 1) {  // nums2 长度为奇数时，nums1 里每个元素才会出现在奇数个数对中
            for (int v : nums1) {  // 遍历 nums1 的每个元素
                ans ^= v;  // 异或累加；同一元素出现偶数次会相互抵消，这正是本题的关键
            }  // 结束对 nums1 的遍历
        }  // 第一种情况处理完毕
        if (nums1.size() % 2 == 1) {  // 同理：nums1 长度为奇数时，nums2 的每个元素才被计入
            for (int v : nums2) {  // 遍历 nums2 的每个元素
                ans ^= v;  // 异或累加到答案
            }  // 结束对 nums2 的遍历
        }  // 第二种情况处理完毕
        return ans;  // 返回所有数对的异或和
    }  // 方法结束
};  // 类定义结束