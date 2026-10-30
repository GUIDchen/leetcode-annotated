// 题目：15. 三数之和（3Sum）
// 思路：排序后固定第一个数 i，用左右双指针夹逼找剩余两数；nums[i] > 0 时提前结束，靠相邻比较跳过重复解。
// 时间复杂度：O(n^2)，外层枚举 + 内层双指针；空间复杂度：O(1)，除返回值外只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> threeSum(vector<int>& nums) {  // nums 是输入数组
        sort(nums.begin(), nums.end());  // 先排序，才能用双指针并方便去重
        vector<vector<int>> ans;  // 收集所有不重复的三元组
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n - 2 && nums[i] <= 0; ++i) {  // 枚举第一个数；它大于 0 时后面不可能再凑成 0 和
            if (i && nums[i] == nums[i - 1]) {  // 与上一个数相同
                continue;  // 跳过，避免产生重复三元组
            }
            int j = i + 1, k = n - 1;  // 左右指针指向 i 右侧区间的最小值和最大值
            while (j < k) {  // 两指针未相遇就继续
                int x = nums[i] + nums[j] + nums[k];  // 当前三数之和
                if (x < 0) {  // 和偏小
                    ++j;  // 左指针右移取更大的值
                } else if (x > 0) {  // 和偏大
                    --k;  // 右指针左移取更小的值
                } else {  // 恰好为 0
                    ans.push_back({nums[i], nums[j++], nums[k--]});  // 记录三元组，同时把两指针各向内移一步
                    while (j < k && nums[j] == nums[j - 1]) {  // 跳过左指针处重复的值
                        ++j;
                    }
                    while (j < k && nums[k] == nums[k + 1]) {  // 跳过右指针处重复的值
                        --k;
                    }
                }
            }
        }
        return ans;  // 返回所有不重复的三元组
    }
};
