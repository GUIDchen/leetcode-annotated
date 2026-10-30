// 题目：2099. 找到和最大的长度为 K 的子序列（Find Subsequence of Length K With the Largest Sum）
// 思路：先把所有下标按 nums 的值升序排序，末尾 k 个就是值最大的 k 个下标；再把这 k 个下标按原顺序排列，依次取数即可。
// 时间复杂度：O(n log n)，两次排序；空间复杂度：O(n)，下标数组 idx 与答案数组 ans。
#include <ranges>  // 引入 ranges 算法与视图：ranges::iota / ranges::sort / views::drop 都来自这里

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maxSubsequence(vector<int>& nums, int k) {  // nums：输入数组；k：子序列长度，返回长度为 k 的最大和子序列
        int n = nums.size();  // 记录数组长度，后面多处要用
        vector<int> idx(n);  // 准备保存 0..n-1 这些下标，稍后按对应的值排序
        ranges::iota(idx, 0);  // 用 0,1,2,... 依次填满 idx，此时 idx[i] == i
        ranges::sort(idx, [&](int i, int j) { return nums[i] < nums[j]; });  // 把下标按 nums 的值升序排序：值最大的 k 个下标会排到末尾
        ranges::sort(idx | views::drop(n - k));  // 只对末尾 k 个下标再按下标本身升序排，恢复它们在原数组中的先后顺序
        vector<int> ans(k);  // 答案数组，长度固定为 k
        for (int i = n - k; i < n; ++i) {  // 遍历排好序的那 k 个「最大值所在下标」
            ans[i - (n - k)] = nums[idx[i]];  // 减掉 n-k 的偏移得到答案下标，按原数组顺序取出元素
        }
        return ans;  // 返回长度为 k 的最大和子序列
    }
};