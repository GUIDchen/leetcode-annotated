// 题目：1663. 具有给定数值的最小字符串（Smallest String With A Given Numeric Value）
// 思路：先全部填 'a' 保证长度与字典序最小，再从末尾尽量补成 'z'，最后把剩余差值补在一个字符上。
// 时间复杂度：O(n)，最多填 n 个字符；空间复杂度：O(n)，存放结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string getSmallestString(int n, int k) {  // n 是字符串长度；k 是各字符数值（a=1..z=26）之和
        string ans(n, 'a');  // 先放 n 个 'a'，此时数值和为 n，也满足字典序尽量小
        int i = n - 1, d = k - n;  // i 指向最后一个待定位置，d 是还需要补足的数值
        for (; d > 25; d -= 25) {  // d 超过 25 时，说明当前位可以拉满成 'z'（比 'a' 多 25）
            ans[i--] = 'z';  // 把当前位改成 'z' 并把指针左移
        }  // for 循环结束
        ans[i] += d;  // 剩下不足 25 的差值直接加到当前字符上，使总和恰好为 k
        return ans;  // 返回构造出的最小字符串
    }  // 方法结束
};  // 类定义结束