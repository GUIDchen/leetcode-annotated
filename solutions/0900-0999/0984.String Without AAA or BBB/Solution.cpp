// 题目：984. 不含 AAA 或 BBB 的字符串（String Without AAA or BBB）
// 思路：贪心，字母多的一方每次输出两个自己夹一个对方，数量相同时输出 "ab"，这样任何时刻都不会出现三个连续相同字母。
// 时间复杂度：O(a+b)，与结果字符串长度成正比；空间复杂度：O(a+b)，存放结果字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string strWithout3a3b(int a, int b) {  // a、b 分别是字母 'a' 与 'b' 的剩余个数
        string ans;  // 结果字符串缓冲区
        while (a && b) {  // 两种字母都还有剩余时成对处理
            if (a > b) {  // a 比 b 多
                ans += "aab";  // 先放两个 a 再夹一个 b，保证不出现 aaa
                a -= 2;  // 用掉两个 a
                b -= 1;  // 用掉一个 b
            } else if (a < b) {  // b 比 a 多
                ans += "bba";  // 对称处理：先放两个 b 再夹一个 a
                a -= 1;  // 用掉一个 a
                b -= 2;  // 用掉两个 b
            } else {  // a 与 b 一样多
                ans += "ab";  // 各放一个即可，交替出现不会违规
                --a;  // 用掉一个 a
                --b;  // 用掉一个 b
            }  // if-else 链结束
        }  // 循环结束，此时至少有一种字母用完
        if (a) ans += string(a, 'a');  // 只剩 a 时最多剩两个，直接补齐
        if (b) ans += string(b, 'b');  // 只剩 b 时最多剩两个，直接补齐
        return ans;  // 返回构造好的字符串
    }  // 方法结束
};  // 类定义结束