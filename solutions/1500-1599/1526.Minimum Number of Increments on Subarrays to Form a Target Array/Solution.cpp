// 题目：1526. 形成目标数组的子数组最少增加次数（Minimum Number of Increments on Subarrays to Form a Target Array）
// 核心思路：把 target 看成一层层叠起来的「山」；答案 = target[0] + Σ max(0, target[i] - target[i-1])，即每处上升都要新开一批操作。
// 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minNumberOperations(vector<int>& target) {  // target：目标数组，返回最少操作次数
        int f = target[0];  // f 累计操作次数，第一列需要的 target[0] 次先算进来
        for (int i = 1; i < target.size(); ++i) {  // 从第二个元素开始比较相邻高度
            if (target[i] > target[i - 1]) {  // 高度上升
                f += target[i] - target[i - 1];  // 上升多少，就需要在这部分新开多少次操作
            }  // if 结束
        }  // 循环结束
        return f;  // 返回总操作次数
    }  // 方法结束
};  // 类定义结束