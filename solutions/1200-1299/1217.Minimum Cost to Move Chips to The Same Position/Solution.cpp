// 题目：1217. 玩筹码（Minimum Cost to Move Chips to The Same Position）
// 思路：移动 2 步代价为 0，所以同奇偶的位置可以免费汇聚；最终只需把数量较少的那一组整体移动 1 步。
// 时间复杂度：O(n)，一次遍历统计；空间复杂度：O(1)，只用两个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCostToMoveChips(vector<int>& position) {  // position：每个筹码所在的位置下标
        int a = 0;  // a：统计奇数位置上筹码的个数
        for (auto& p : position) a += p & 1;  // p & 1 取出奇偶性；移动 2 步免费，所以真正决定代价的只有奇偶
        int b = position.size() - a;  // b：偶数位置上筹码的个数（总数减去奇数个数）
        return min(a, b);  // 保留较多的一组不动，把较少的一组逐个移动 1 步，代价取较小值
    }  // 方法结束
};  // 类定义结束