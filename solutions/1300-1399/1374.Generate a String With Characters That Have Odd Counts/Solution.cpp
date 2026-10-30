// 题目：1374. 生成每种字符都是奇数个的字符串（Generate a String With Characters That Have Odd Counts）
// 思路：先铺满 n 个 'a'；若 n 为偶数，把第一个字符换成 'b'，于是 'a' 有 n-1 个、'b' 有 1 个，两者都是奇数个。
// 时间复杂度：O(n)，需要构造长度为 n 的字符串；空间复杂度：O(n)，返回的字符串本身占 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string generateTheString(int n) {  // n 为字符串长度，返回每种字符出现次数都为奇数的字符串
        string ans(n, 'a');  // 先造 n 个 'a'，n 为奇数时已经满足要求
        if (n % 2 == 0) {  // n 为偶数时 'a' 的个数是偶数，需要调整
            ans[0] = 'b';  // 把首字符换成 'b'：'a' 剩 n-1（奇数）个，'b' 恰好 1 个
        }  // 偶数分支结束
        return ans;  // 返回构造好的字符串，两种字符的个数都是奇数
    }  // 方法结束
};  // 类定义结束