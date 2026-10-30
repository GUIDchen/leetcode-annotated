// 题目：247. 中心对称数 II（Strobogrammatic Number II）
// 思路：按长度递归构造，长度为 u 的中心对称串由长度为 u-2 的内层串左右各拼一个合法对称数字对得到，u=0/u=1 为递归边界。
// 时间复杂度：O(5^(n/2))，即结果数量的量级；空间复杂度：O(n)，递归深度为 n/2。
class Solution {  // LeetCode 约定的题解类
public:  // 成员函数对外可见
    const vector<pair<char, char>> pairs = {{'1', '1'}, {'8', '8'}, {'6', '9'}, {'9', '6'}};  // 可以放到最外层的对称数字对；'0' 只能出现在内层，所以没有放进这张表

    vector<string> findStrobogrammatic(int n) {  // n：目标位数，返回所有长度为 n 的中心对称数字字符串
        function<vector<string>(int)> dfs = [&](int u) {  // 递归函数 dfs(u)：返回所有长度为 u 的中心对称串；用 function 保存 lambda 以便递归自调用
            if (u == 0) return vector<string>{""};  // 边界：长度 0 返回空串，作为拼接时的内层
            if (u == 1) return vector<string>{"0", "1", "8"};  // 边界：长度 1 只有自己旋转仍不变的 0、1、8
            vector<string> ans;  // 收集长度为 u 的全部结果
            for (auto& v : dfs(u - 2)) {  // 枚举所有长度为 u-2 的内层串
                for (auto& [l, r] : pairs) ans.push_back(l + v + r);  // 内层串左右各拼一个合法数字对（结构化绑定取出左右两个字符）
                if (u != n) ans.push_back('0' + v + '0');  // 非最外层可以补 0；最外层补 0 会产生前导零，所以只有 u != n 时才允许
            }  // 结束内层串枚举
            return ans;  // 返回长度为 u 的全部中心对称串
        };  // lambda 定义结束
        return dfs(n);  // 直接求长度为 n 的结果集
    }  // 结束 findStrobogrammatic 方法
};  // 结束 Solution 类