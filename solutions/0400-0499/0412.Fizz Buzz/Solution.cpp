// 题目：412. Fizz Buzz（Fizz Buzz）
// 思路：从 1 到 n 逐个拼接字符串：3 的倍数加 Fizz、5 的倍数加 Buzz，都没拼上就输出数字本身。
// 时间复杂度：O(n)，每个数只处理一次；空间复杂度：O(n)，答案数组保存 n 个字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> fizzBuzz(int n) {  // n 是上界，返回 1..n 的 Fizz Buzz 结果列表
        vector<string> ans;  // 保存每一轮得到的字符串
        for (int i = 1; i <= n; ++i) {  // 从 1 遍历到 n（闭区间）
            string s = "";  // 本轮的字符串，先置空
            if (i % 3 == 0) {  // 3 的倍数拼接 Fizz
                s += "Fizz";  // 追加 Fizz
            }  // 第一个 if 结束
            if (i % 5 == 0) {  // 5 的倍数拼接 Buzz（与上一个 if 独立，保证 15 的倍数得到 FizzBuzz）
                s += "Buzz";  // 追加 Buzz
            }  // 第二个 if 结束
            if (s.empty()) {  // 两个都没拼上，说明既不是 3 也不是 5 的倍数
                s = to_string(i);  // 用数字本身的十进制表示
            }  // 兜底 if 结束
            ans.push_back(s);  // 把本轮结果追加到答案末尾
        }  // 循环结束
        return ans;  // 返回完整结果
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，此处保持一致）