// 题目：523. 连续的子数组和（Continuous Subarray Sum）
// 思路：前缀和取模 k，同一余数在距离大于 1 处再次出现，说明中间这段子数组的和是 k 的倍数。
// 时间复杂度：O(n)，遍历一次并用哈希表 O(1) 查询；空间复杂度：O(k)，最多存 k 个不同余数。
class Solution {  // LeetCode 约定的题解类
public:  // 公有方法区
    bool checkSubarraySum(vector<int>& nums, int k) {  // nums：非负整数数组；k：除数；返回是否存在长度至少为 2、和是 k 倍数的连续子数组
        unordered_map<int, int> d{{0, -1}};  // 哈希表记录「前缀和余数 → 最早出现下标」；哨兵 {0, -1} 让从首元素开始的子数组也能算出长度
        int s = 0;  // s 保存当前前缀和对 k 取模的余数
        for (int i = 0; i < nums.size(); ++i) {  // 逐元素扫描整个数组
            s = (s + nums[i]) % k;  // 累加当前元素后立刻取模，避免数值溢出，并让余数落在 [0, k) 内
            if (!d.contains(s)) {  // 该余数是第一次出现
                d[s] = i;  // 记录余数对应的下标，保留最早出现的位置
            } else if (i - d[s] > 1) {  // 该余数出现过，且两次出现之间至少有 2 个元素
                return true;  // 找到长度 >= 2 且元素和为 k 倍数的子数组
            }  // if-else 结束
        }  // for 结束
        return false;  // 遍历完也没找到符合条件的子数组
    }  // 方法结束
};  // 类定义结束