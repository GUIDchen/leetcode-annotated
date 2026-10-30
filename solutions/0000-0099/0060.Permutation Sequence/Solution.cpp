// 题目：60. 排列序列（Permutation Sequence）
// 思路：按位确定答案，第 i 位确定时块大小为 (n-i-1)!；用 k 与块大小的比较跳过整块，最终定位到目标排列。
// 时间复杂度：O(n^2)，外层 n 位、内层最多扫 n 个候选数；空间复杂度：O(n)，vis 与结果串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string getPermutation(int n, int k) {  // n：数字个数（1..n），k：第 k 个排列（1 起计）
        string ans;  // 逐位拼接答案
        bitset<10> vis;  // 标记 1..n 中哪些数字已被使用；n <= 9，用 bitset 很省空间
        for (int i = 0; i < n; ++i) {  // 依次确定答案的第 i 位
            int fact = 1;  // 计算固定前 i 位后，剩余位置的排列数 (n-i-1)!
            for (int j = 1; j < n - i; ++j) fact *= j;  // 连乘 1..n-i-1 得到块大小
            for (int j = 1; j <= n; ++j) {  // 从小到大枚举这一位可以放的数字
                if (vis[j]) continue;  // 已被前面用掉的数字不能再用
                if (k > fact)  // 当前数字开头的排列整整有 fact 个，k 更大说明不在这一块
                    k -= fact;  // 跳过这一整块，在后面的块里继续找
                else {  // k 落在「以 j 打头」的这一块内
                    ans += to_string(j);  // 该块的第一位就是 j，确定这一位
                    vis[j] = 1;  // 记录 j 已使用
                    break;  // 这一位已定，去做下一位
                }
            }
        }
        return ans;  // 每一位都确定后得到第 k 个排列
    }
};
