// 题目：3861. 容量最小的箱子（Minimum Capacity Box）
// 思路：一次遍历，在所有容量不小于 itemSize 的箱子中取容量最小者；容量相同时保留更小的下标。
// 时间复杂度：O(n)，n 为箱子数量；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumIndex(vector<int>& capacity, int itemSize) {  // capacity：每个箱子的容量；itemSize：物品大小
        int ans = -1;  // 记录答案下标，-1 表示暂时没有可选的箱子
        for (int i = 0; i < capacity.size(); ++i) {  // 从左到右遍历箱子
            int x = capacity[i];  // 当前箱子的容量
            if (x >= itemSize && (ans == -1 || x < capacity[ans])) {  // 能装下物品，且容量严格更小才替换（相等时保留更小的下标）
                ans = i;  // 更新为更优的箱子下标
            }
        }
        return ans;  // 返回结果，没有合适箱子时仍是 -1
    }
};
