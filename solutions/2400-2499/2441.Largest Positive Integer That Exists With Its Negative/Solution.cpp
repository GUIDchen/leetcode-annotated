// 题目：2441. 与对应负数同时存在的最大正整数（Largest Positive Integer That Exists With Its Negative）【简单】
// 思路：把数组放进哈希集合去重，再遍历集合中每个 x，若 -x 也存在于集合里就用 max 更新答案；初值 -1 表示不存在这样的数。
// 时间复杂度：O(n)，建集合与遍历集合各一遍；空间复杂度：O(n)，哈希集合最多存 n 个不同值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMaxK(vector<int>& nums) {  // nums 是输入数组
        unordered_set<int> s(nums.begin(), nums.end());  // 用区间构造一次性把数组转成哈希集合：顺带去重，并把查找降到 O(1)
        int ans = -1;  // 答案初值 -1，题意要求找不到时返回 -1
        for (int x : s) {  // 遍历集合中的每个值（去重后每个数只看一次）
            if (s.count(-x)) {  // 判断相反数 -x 是否也在集合中，即 x 与 -x 同时出现
                ans = max(ans, x);  // 同时出现就取较大者更新答案（负数会自然被淘汰，因为要的是正整数）
            }
        }
        return ans;  // 返回满足条件的最大正整数，没有则仍是 -1
    }
};