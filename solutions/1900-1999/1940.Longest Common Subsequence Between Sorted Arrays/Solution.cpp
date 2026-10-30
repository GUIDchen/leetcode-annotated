// 题目：1940. 排序数组之间的最长公共子序列（Longest Common Subsequence Between Sorted Arrays）
// 思路：每个数组内部元素互不相同，所以「出现在所有数组中」等价于「出现次数等于数组个数」，用计数数组统计每个值的出现次数，再按值升序输出。
// 时间复杂度：O(S + 101)，S 是所有数组的元素总数；空间复杂度：O(101) = O(1)，只用了常数大小的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> longestCommonSubsequence(vector<vector<int>>& arrays) {  // arrays：若干升序数组，求它们共有的元素
        int cnt[101]{};  // cnt[x] 记录数值 x 一共出现在多少个数组里；{} 让全部元素初值为 0
        for (const auto& row : arrays) {  // 逐个数组（逐行）统计
            for (int x : row) {  // 遍历当前数组中的每个元素
                ++cnt[x];  // 该值的出现次数加一
            }
        }
        vector<int> ans;  // 答案数组，按数值升序存放公共元素
        for (int i = 0; i < 101; ++i) {  // 题目给定数值范围是 1..100，这里顺带扫到 0，不影响结果
            if (cnt[i] == arrays.size()) {  // 出现次数等于数组个数 ⇒ 每个数组都含该值 ⇒ 它是公共元素
                ans.push_back(i);  // 加入答案，天然保持升序
            }
        }
        return ans;  // 返回按值升序排列的公共元素序列
    }
};
