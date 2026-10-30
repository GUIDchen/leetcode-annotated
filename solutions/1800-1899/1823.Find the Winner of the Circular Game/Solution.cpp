// 题目：1823. 找出游戏的获胜者（Find the Winner of the Circular Game）
// 核心思路：约瑟夫环递推，记 f(n,k) 为 n 人时的获胜者在 0-based 编号下的位置，删去第 k 人后重新编号得 f(n,k)=(f(n-1,k)+k)%n，最后把 0 映射为 n。
// 时间复杂度：O(n)，递归深度为 n；空间复杂度：O(n)，递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findTheWinner(int n, int k) {  // n 个人围成一圈，每数到第 k 个人出局
        if (n == 1) return 1;  // 只剩 1 个人时，获胜者就是唯一的编号 1
        int ans = (findTheWinner(n - 1, k) + k) % n;  // 递推：n-1 人的答案整体后移 k 位，再对 n 取模得到 0-based 位置
        return ans == 0 ? n : ans;  // 0-based 位置 0 对应真实编号 n，其余位置加 1 即 ans 本身
    }
};  // 类定义结束