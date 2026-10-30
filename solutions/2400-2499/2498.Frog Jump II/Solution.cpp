// 题目：2498. 青蛙过河 II（Frog Jump II）
// 思路：去程与回程共用第 0、1 块石头之间的那一段，其余石头只能隔一个跳，所以答案就是所有「隔一块的差」与首段差的最大值。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxJump(vector<int>& stones) {  // stones 是升序的石头位置，返回来回过河所需的最小「最大跳跃长度」
        int ans = stones[1] - stones[0];  // 第 0、1 块石头之间的差必须被跨越一次，先作为答案初值
        for (int i = 2; i < stones.size(); ++i) ans = max(ans, stones[i] - stones[i - 2]);  // 中间的石头在去程或回程中被占用，只能隔一块跳，取 stones[i]-stones[i-2] 的最大值
        return ans;  // 最大值即为所需的最小最大跳跃长度
    }
};  // 类定义结束