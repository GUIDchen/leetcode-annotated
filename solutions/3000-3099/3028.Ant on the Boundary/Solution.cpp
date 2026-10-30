// 题目：3028. 边界上的蚂蚁（Ant on the Boundary）
// 思路：维护前缀和 s 表示蚂蚁当前相对起点的位置，每走一步若 s 回到 0，说明它正好踩在边界上，计数加一。
// 时间复杂度：O(n)，只遍历一次数组；空间复杂度：O(1)，只用了计数器和前缀和两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int returnToBoundaryCount(vector<int>& nums) {  // nums：每一步的位移，正数向右、负数向左
        int ans = 0, s = 0;  // ans：回到边界的次数；s：当前相对起点的位移（前缀和）
        for (int x : nums) {  // 按顺序模拟蚂蚁的每一次移动
            s += x;  // 把这一步的位移累加到当前位置上
            ans += s == 0;  // 位置恰为 0 代表回到边界，比较结果是 0/1，直接累加即可
        }
        return ans;  // 返回整个过程里回到边界的次数
    }
};