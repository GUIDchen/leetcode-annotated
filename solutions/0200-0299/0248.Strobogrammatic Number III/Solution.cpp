// 题目：248. 中心对称数 III（Strobogrammatic Number III）
// 思路：先按位数递归构造出所有中心对称数（与 247 相同的构造），再转成整数与 [low, high] 比较计数。
// 时间复杂度：O((b-a+1)·5^(n/2))，b/a 为 high/low 的位数；空间复杂度：O(n)，递归栈深度与生成结果的开销。
using ll = long long;  // 给 long long 起别名 ll，便于处理超过 int 范围的大数

class Solution {  // LeetCode 约定的题解类
public:  // 成员函数对外可见
    const vector<pair<char, char>> pairs = {{'1', '1'}, {'8', '8'}, {'6', '9'}, {'9', '6'}};  // 可以放到外层的对称数字对；'0' 只能出现在内层

    int strobogrammaticInRange(string low, string high) {  // 统计数值落在闭区间 [low, high] 内的中心对称数个数
        int n;  // 当前正在生成的中心对称数位数，供 dfs 捕获读取以判断是否为最外层
        function<vector<string>(int)> dfs = [&](int u) {  // dfs(u)：返回所有长度为 u 的中心对称串；用 function 支持递归自调用
            if (u == 0) return vector<string>{""};  // 边界：长度 0 返回空串，作为拼接的内层
            if (u == 1) return vector<string>{"0", "1", "8"};  // 边界：长度 1 只有 0、1、8
            vector<string> ans;  // 收集长度为 u 的结果
            for (auto& v : dfs(u - 2)) {  // 枚举内层串
                for (auto& [l, r] : pairs) ans.push_back(l + v + r);  // 左右各拼一个对称数字对
                if (u != n) ans.push_back('0' + v + '0');  // 非最外层才允许补 0，避免前导零
            }  // 结束内层枚举
            return ans;  // 返回当前位数的全部结果
        };  // lambda 定义结束

        int a = low.size(), b = high.size();  // 取出边界数字的位数，只需生成位数在 [a, b] 之间的数
        int ans = 0;  // 答案计数器
        ll l = stoll(low), r = stoll(high);  // 把字符串边界转成 64 位整数，便于做区间比较
        for (n = a; n <= b; ++n) {  // 按位数从 a 到 b 依次生成；同时把 n 写回外层变量，让 dfs 能判断最外层
            for (auto& s : dfs(n)) {  // 遍历该位数下的所有中心对称串
                ll v = stoll(s);  // 转成数值再比较（long long 可容纳题目范围内的位数）
                if (l <= v && v <= r) {  // 落在闭区间内才计数
                    ++ans;  // 计数加一
                }  // 结束区间判断
            }  // 结束该位数的结果遍历
        }  // 结束位数循环
        return ans;  // 返回区间内的中心对称数个数
    }  // 结束 strobogrammaticInRange 方法
};  // 结束 Solution 类