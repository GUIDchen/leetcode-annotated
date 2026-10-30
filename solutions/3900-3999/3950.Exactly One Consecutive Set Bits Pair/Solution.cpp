// 题目：3950. 恰好一对连续置位（Exactly One Consecutive Set Bits Pair）
// 思路：从最低位往高位逐位扫描，用 pre 记住上一位；若相邻两位同时为 1 就计数，出现第二次即失败，最后要求至少出现一次。
// 复杂度：时间 O(log n)（二进制位数），空间 O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool consecutiveSetBits(int n) {  // n：待检查的正整数，判断它的二进制里是否恰好有一对相邻的 1
        bool vis = false;  // vis 记录是否已经出现过一次「相邻两位都是 1」
        for (int pre = 0; n > 0; n >>= 1) {  // pre 保存上一位的值；从最低位往高位扫描，每次右移一位
            int cur = n & 1;  // cur 是当前最低位的值（0 或 1）
            if (pre == cur && cur == 1) {  // 上一位与当前位都是 1，说明出现了一对相邻的置位
                if (vis) {  // 之前已经出现过一对，说明不止一对
                    return false;  // 直接返回 false
                }
                vis = true;  // 标记已经出现过一对
            }
            pre = cur;  // 当前位成为下一轮的上一位
        }
        return vis;  // 返回 vis：为 true 表示恰好一对，false 表示一对都没有
    }
};