// 题目：2582. 递枕头（Pass the Pillow）
// 思路：逐秒模拟，用 k 表示传递方向，碰到编号 1 或 n 就掉头；总共只会走 time 步。
// 时间复杂度：O(time)，逐秒推进；空间复杂度：O(1)，只用两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int passThePillow(int n, int time) {  // n 个人排成一排，time 秒后返回拿着枕头的人的编号
        int ans = 1, k = 1;  // ans 是当前持有者编号（从 1 开始），k 是传递方向：1 向右、-1 向左
        while (time--) {  // 逐秒模拟传递，time 减到 0 就结束
            ans += k;  // 把枕头传给相邻的人
            if (ans == 1 || ans == n) {  // 走到两端就必须掉头往回走
                k *= -1;  // 方向取反
            }
        }
        return ans;  // 返回 time 秒后持有枕头的人的编号
    }
};