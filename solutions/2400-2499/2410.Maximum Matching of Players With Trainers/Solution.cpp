// 题目：2410. 运动员和训练师的最大匹配数（Maximum Matching of Players With Trainers）
// 思路：双方都升序排序后双指针贪心，为每个运动员分配当前能力够用的最弱训练师。
// 时间复杂度：O(m log m + n log n)，排序主导；空间复杂度：O(1)，只用了常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {  // players 是运动员能力值，trainers 是训练师能力值
        ranges::sort(players);  // 把运动员能力升序排列，便于从小到大依次匹配
        ranges::sort(trainers);  // 把训练师能力升序排列，让“最勉强够用”的人先被选中
        int m = players.size(), n = trainers.size();  // m、n 分别是运动员与训练师的数量
        for (int i = 0, j = 0; i < m; ++i, ++j) {  // i 指向当前运动员，j 指向当前训练师，匹配成功时两者一起后移
            while (j < n && trainers[j] < players[i]) {  // 当前训练师带不动这名运动员就跳过，找第一个够用的
                ++j;  // 训练师能力不足，换下一个更强的
            }
            if (j == n) {  // 训练师已全部用完，后面的运动员更匹配不上
                return i;  // 此时已成功匹配 i 对，直接返回
            }
        }
        return m;  // 所有运动员都匹配成功，匹配数等于运动员人数
    }
};
