// 题目：1318. 或运算的最小翻转次数（Minimum Flips to Make a OR b Equal to c）
// 思路：逐位独立考虑：c 的该位为 0 时 a、b 该位必须全为 0；为 1 时 a、b 至少一个为 1，缺则翻一次。
// 时间复杂度：O(32)，常数位宽；空间复杂度：O(1)，只用若干标量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minFlips(int a, int b, int c) {  // 统计最少翻转位数，使 a | b == c
        int ans = 0;  // 记录累计的翻转次数
        for (int i = 0; i < 32; ++i) {  // 逐位从低到高检查 32 位（int 的位宽）
            int x = a >> i & 1, y = b >> i & 1, z = c >> i & 1;  // 分别取出 a、b、c 在第 i 位的比特值
            ans += z == 0 ? x + y : (x == 0 && y == 0 ? 1 : 0);  // c 该位为 0：a、b 该位必须为 0，有几个 1 就要翻几次；c 该位为 1：a、b 都为 0 时只需翻一次
        }  // 位检查循环结束
        return ans;  // 返回最少翻转次数
    }  // 方法结束
};  // 类定义结束