// 题目：1995. 统计特殊四元组（Count Special Quadruplets）
// 思路：n 不超过 50，直接四重循环按 a < b < c < d 枚举所有下标组合，检查 nums[a] + nums[b] + nums[c] == nums[d] 并计数。
// 时间复杂度：O(n^4)；空间复杂度：O(1)，只用了两个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countQuadruplets(vector<int>& nums) {  // nums：输入数组
        int ans = 0, n = nums.size();  // ans 记录答案；n 是数组长度
        for (int a = 0; a < n - 3; ++a)  // a 最小，右边至少还要留 b、c、d 三个位置
            for (int b = a + 1; b < n - 2; ++b)  // b 从 a+1 开始，右边至少还要留 c、d 两个位置
                for (int c = b + 1; c < n - 1; ++c)  // c 从 b+1 开始，右边至少还要留 d
                    for (int d = c + 1; d < n; ++d)  // d 从 c+1 开始，保证四个下标严格递增
                        if (nums[a] + nums[b] + nums[c] == nums[d]) ++ans;  // 满足 nums[a]+nums[b]+nums[c]==nums[d] 时答案加一
        return ans;  // 返回特殊四元组的个数
    }  // 方法结束
};  // 题解类结束