// 题目：1561. 你可以获得的最大硬币数目（Maximum Number of Coins You Can Get）
// 思路：升序排序后，最小的三分之一给对手；剩下部分每三堆一组（小给对手、中给自己、大给朋友），自己取每组的中位数。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，除原地排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxCoins(vector<int>& piles) {  // piles：每堆硬币数
        ranges::sort(piles);  // C++20 ranges 版排序：按硬币数升序排列
        int ans = 0;  // 自己最终能拿到的硬币总数
        for (int i = piles.size() / 3; i < piles.size(); i += 2) {  // 最小的三分之一让给对手；此后每两堆取下标较小者即该组的中位数
            ans += piles[i];  // 累加自己拿到的一堆
        }  // 循环体结束
        return ans;  // 返回最大收益
    }  // 方法结束
};  // 类定义结束
