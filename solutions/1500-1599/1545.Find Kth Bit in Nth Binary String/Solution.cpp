// 题目：1545. 找出第 N 个二进制字符串中的第 K 位（Find Kth Bit in Nth Binary String）
// 思路：S_n = S_{n-1} + "1" + reverse(invert(S_{n-1}))，按 k 落在左半、中点还是右半递归定位，落在右半时再取反。
// 时间复杂度：O(n)，每层只递归一次；空间复杂度：O(n)，递归栈深度为 n。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    char findKthBit(int n, int k) {  // n：第 n 个二进制字符串；k：要查询的 1 基下标
        function<int(int, int)> dfs = [&](int n, int k) {  // 递归函数：返回 S_n 第 k 位的值（0 或 1），用 lambda 递归方便捕获外部变量
            if (k == 1) {  // S_n 的第 1 位永远是 0
                return 0;  // 递归出口：直接返回 0
            }
            if ((k & (k - 1)) == 0) {  // k 是 2 的幂时，这个位置正好是每层插在正中间的那个 1
                return 1;  // 直接返回 1
            }
            int m = 1 << n;  // S_n 的长度是 2^n - 1，这里预先算好 2^n
            if (k * 2 < m - 1) {  // k 落在左半部分（长度 2^(n-1)-1），与 S_{n-1} 的第 k 位相同
                return dfs(n - 1, k);  // 递归到上一层查同一位置
            }
            return dfs(n - 1, m - k) ^ 1;  // 落在右半部分：对折回左半后取反，^1 把 0/1 互换
        };  // lambda 定义结束
        return '0' + dfs(n, k);  // 把整数 0/1 加上字符 '0' 转成字符返回
    }
};