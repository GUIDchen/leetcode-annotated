// 题目：4038. 计算单个区间中出现的整数数量 / Count Integers Appearing in a Single Block
// 核心思路：只在每个连续块的首个位置计数，得到每个值落在多少个块中，最后统计块数为 1 的值的个数
// 复杂度：时间复杂度 O(n + V)，空间复杂度 O(V)（V 为数值范围）
class Solution {  // 定义 LeetCode 题解类
public:  // 公有接口
    int countSpecialIntegers(vector<int>& nums) {  // 统计只在单个连续块中出现过的整数个数
        int cnt[101]{};  // cnt[x] 记录 x 出现的连续块个数（题目保证取值不超过 100）
        for (int i = 0; i < nums.size(); ++i) {  // 遍历整个数组
            if (i == 0 || nums[i] != nums[i - 1]) {  // 与前一元素不同说明进入了一个新块
                ++cnt[nums[i]];  // 该值所属的块个数加一
            }  // 结束新块判断
        }  // 结束遍历
        return count(begin(cnt), end(cnt), 1);  // 块个数恰好为 1 的值就是答案，统计这样的值有多少个
    }  // 结束方法
};  // 结束类定义
