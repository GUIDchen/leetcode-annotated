// 题目：55. 跳跃游戏（Jump Game）
// 思路：贪心。维护当前能到达的最远位置 mx，从左往右扫，只要某个下标超出了 mx 就说明走不到，直接返回 false。
// 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用最远可达位置这一个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canJump(vector<int>& nums) {  // nums 为每格的最大跳跃长度，判断能否从下标 0 跳到最后一个下标
        int mx = 0;  // mx 记录目前能到达的最远下标，初始为 0
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右逐个位置尝试扩展可达范围
            if (mx < i) {  // 当前位置 i 已经超过可达范围，说明这个位置根本到不了
                return false;  // 因此不可能跳到终点，提前返回失败
            }  // if 结束
            mx = max(mx, i + nums[i]);  // 从 i 出发最远能到 i + nums[i]，用它更新可达范围
        }  // for 结束
        return true;  // 全程没有被卡住，说明最后一个下标可达
    }  // canJump 结束
};  // 类定义结束