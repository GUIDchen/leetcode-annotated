// 3400. 右移后的最大匹配索引数 / Maximum Number of Matching Indices After Right Shifts
// 核心思路：枚举全部 n 种右移量 k，逐位比较 nums1[(i + k) % n] 与 nums2[i]，统计匹配数并取最大值
// 复杂度：时间 O(n^2)，空间 O(1)
class Solution {  // 定义题目解答类
public:
    int maximumMatchingIndices(vector<int>& nums1, vector<int>& nums2) {  // 方法入口：nums1 循环右移，nums2 固定，求最多匹配位数
        int n = nums1.size();  // 数组长度，也是右移的周期
        int ans = 0;  // 记录最大匹配数
        for (int k = 0; k < n; ++k) {  // 枚举右移量 k
            int t = 0;  // 当前右移量下的匹配数
            for (int i = 0; i < n; ++i) {  // 逐位比较
                if (nums1[(i + k) % n] == nums2[i]) {  // nums1 循环右移 k 位后第 i 位的元素与 nums2[i] 相等
                    ++t;  // 匹配数加一
                }
            }
            ans = max(ans, t);  // 更新全局最大值
        }
        return ans;  // 返回最多匹配的索引个数
    }
};
