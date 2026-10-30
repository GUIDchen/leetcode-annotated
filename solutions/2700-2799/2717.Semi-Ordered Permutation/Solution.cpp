// 题目：2717. 半有序排列（Semi-Ordered Permutation）
// 思路：只需把 1 挪到开头、n 挪到末尾；代价是 1 左侧元素个数加上 n 右侧元素个数，若两者交叉则交换时能省一步。
// 时间复杂度：O(n)，两次线性查找；空间复杂度：O(1)，只用了几个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int semiOrderedPermutation(vector<int>& nums) {  // nums：1 到 n 的排列，返回变成半有序排列的最少操作次数
        int n = nums.size();  // n 既是长度也是排列中的最大值
        int i = find(nums.begin(), nums.end(), 1) - nums.begin();  // 找到 1 所在的下标 i
        int j = find(nums.begin(), nums.end(), n) - nums.begin();  // 找到最大值 n 所在的下标 j
        int k = i < j ? 1 : 2;  // 若 1 在 n 左边，两者交换时会相遇，可少用 1 步；否则少用 2 步
        return i + n - j - k;  // i 个元素要挪到 1 右边，(n-1-j) 个要挪到 n 左边，再减去相遇省下的 k
    }
};