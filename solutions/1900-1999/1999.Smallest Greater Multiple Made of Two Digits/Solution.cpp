// 题目：1999. 最小的仅由两个数组成的倍数（Smallest Greater Multiple Made of Two Digits）
// 思路：以 0 为起点做 BFS，逐步在末尾拼接 digit1 或 digit2，按数值递增顺序找到第一个大于 k 且能被 k 整除的数。
// 时间复杂度：O(k)，至多搜索到 INT_MAX 附近的位数级别；空间复杂度：O(k)，队列中待扩展的候选数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findInteger(int k, int digit1, int digit2) {  // k：除数；digit1、digit2：允许使用的两个数字
        if (digit1 == 0 && digit2 == 0) {
            return -1;  // 只能用数字 0 时只能构造出 0，不存在大于 k 的正倍数
        }
        if (digit1 > digit2) {
            swap(digit1, digit2);  // 保证 digit1 较小，让 BFS 扩展顺序固定，便于分析
        }
        queue<long long> q{{0}};  // BFS 队列，从数值 0 开始；用 long long 防止拼接时溢出
        while (1) {  // 一直搜索，直到找到答案或确认无解
            long long x = q.front();  // 取值最小的候选数
            q.pop();  // 弹出队首
            if (x > INT_MAX) {
                return -1;  // 已超出 32 位有符号整数范围，题目范围外不可能再有解
            }
            if (x > k && x % k == 0) {
                return x;  // 第一个满足「大于 k 且是 k 的倍数」的数就是答案，BFS 保证数值递增
            }
            q.emplace(x * 10 + digit1);  // 在末尾拼接较小数字，形成下一层候选
            if (digit1 != digit2) {
                q.emplace(x * 10 + digit2);  // 两个数字不同才拼接第二个，避免重复入队
            }
        }
    }
};