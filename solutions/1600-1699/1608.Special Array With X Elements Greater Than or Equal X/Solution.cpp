// 题目：1608. 特殊数组的特征值（Special Array With X Elements Greater Than or Equal X）
// 思路：答案只能在 1..n 之间，直接枚举 x 并统计 ≥ x 的元素个数，命中即返回。
// 时间复杂度：O(n^2)，枚举 n 个 x、每个扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // 题解类
public:  // 对外接口
    int specialArray(vector<int>& nums) {  // nums 为输入数组
        for (int x = 1; x <= nums.size(); ++x) {  // 特征值 x 只可能落在 1..n 之间，逐个枚举
            int cnt = 0;  // 统计大于等于 x 的元素个数
            for (int v : nums) cnt += v >= x;  // 布尔值参与加法：v >= x 为真时计 1，否则计 0
            if (cnt == x) return x;  // 恰好有 x 个元素 ≥ x，x 就是特征值
        }
        return -1;  // 所有可能的 x 都不满足，返回 -1
    }
};