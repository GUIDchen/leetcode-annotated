// 题目：2216. 美化数组的最少删除数（Minimum Deletions to Make Array Beautiful）
// 思路：贪心。从左往右配对：相邻相等就删掉左边一个（计数 +1，只前进一步）；相邻不等就保留这对（前进两步）。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDeletion(vector<int>& nums) {  // nums 是输入数组，返回值是最少删除次数
        int n = nums.size();  // 原数组长度
        int ans = 0;  // 已删除的元素个数
        for (int i = 0; i < n - 1; ++i) {  // i 指向当前待配对的下标，必须留出 i + 1 这个位置
            if (nums[i] == nums[i + 1]) {  // 这一对相等，会违反“相邻且偶数下标不相等”的规则
                ++ans;  // 删掉 nums[i]，删除数加一
            } else {  // 这一对可以保留
                ++i;  // 跳过 nums[i + 1]，下一轮从更后面的位置继续配对
            }
        }
        ans += (n - ans) % 2;  // 剩余长度为奇数时必须再删一个，保证最终数组长度为偶数
        return ans;  // 返回最少删除次数
    }
};