// 题目：816. 模糊坐标（Ambiguous Coordinates）
// 思路：枚举逗号切点把括号内数字分成两段，再枚举每段内部小数点的位置，按无前导零、无多余尾零过滤后拼接。
// 时间复杂度：O(n^3)，n 为字符串长度；空间复杂度：O(n^3)，用于存放结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> ambiguousCoordinates(string s) {  // s 形如 (123)，返回所有可能还原出的坐标字符串
        int n = s.size();  // n 是含左右括号的字符串总长度
        vector<string> ans;  // 答案列表
        auto f = [&](int i, int j) {  // 辅助函数：把 s 的区间 [i, j) 解析成所有合法数字串
            vector<string> res;  // 收集该区间的所有可行写法
            for (int k = 1; k <= j - i; ++k) {  // 枚举小数点位置，k 是整数部分的长度
                string l = s.substr(i, k);  // 左半部分 l 作整数部分
                string r = s.substr(i + k, j - i - k);  // 右半部分 r 作小数部分
                bool ok = (l == "0" || l[0] != '0') && r.back() != '0';  // 合法条件：l 是单个 0 或无前导零，且 r 不能以 0 结尾
                if (ok) {  // 合法才放进结果
                    res.push_back(l + (k < j - i ? "." : "") + r);  // 小数点确实在中间时插入点号，否则保持整数形式
                }  // if 结束
            }  // for 结束
            return res;  // 返回该区间的所有写法
        };  // lambda 结束
        for (int i = 2; i < n - 1; ++i) {  // 枚举逗号位置，i 是左半段的结束下标
            for (auto& x : f(1, i)) {  // 左半段的所有写法 x
                for (auto& y : f(i, n - 1)) {  // 右半段的所有写法 y
                    ans.emplace_back("(" + x + ", " + y + ")");  // 拼成坐标形式 (x, y)
                }  // for 结束
            }  // for 结束
        }  // for 结束
        return ans;  // 返回所有坐标
    }  // 方法结束
};  // 类定义结束