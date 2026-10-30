// 题目：2279. 装满石头的背包的最大数量（Maximum Bags With Full Capacity of Rocks）
// 思路：算出每个背包的缺口 capacity[i] - rocks[i]，升序排序后用额外石头从缺口最小的开始填，能填几个就是几个。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，在原数组上原地修改。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {  // capacity 为各背包容量，rocks 为现有石头，additionalRocks 为可额外分配的石头总数
        int n = rocks.size();  // 背包数量
        for (int i = 0; i < n; ++i) {  // 遍历每个背包
            capacity[i] -= rocks[i];  // 原地把容量改写成「还差多少块石头才装满」
        }
        ranges::sort(capacity);  // 按缺口升序排序：缺口小的背包更容易被装满，优先选择最划算
        for (int i = 0; i < n; ++i) {  // 依次尝试装满排序后的背包
            additionalRocks -= capacity[i];  // 用额外石头填上当前背包的缺口
            if (additionalRocks < 0) {  // 石头不够，说明第 i 个背包（从 0 计数）装不满
                return i;  // 前 i 个背包已经装满，答案是 i
            }
        }
        return n;  // 石头足够，n 个背包全部装满
    }
};
