// 题目：1415. 长度为 n 的开心字符串中字典序第 k 小的字符串（The k-th Lexicographical String of All Happy Strings of Length n）
// 思路：按 a→c 的字典序回溯构造开心字符串，凑满 k 个就剪枝，最后取第 k 个。
// 时间复杂度：O(3 * 2^(n-1))，方案数按指数增长（找到 k 个即停止）；空间复杂度：O(k * n)，保存结果与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string getHappyString(int n, int k) {  // n 是目标长度，k 是要求的字典序名次，返回第 k 小的开心字符串
        vector<string> ans;  // 按构造顺序（即字典序）收集所有开心字符串
        string s = "";  // 当前正在构造的字符串，相当于回溯路径
        auto dfs = [&](this auto&& dfs) -> void {  // 递归回溯函数，用 C++23 的显式对象参数实现 Lambda 自引用
            if (s.size() == n) {  // 长度已经达到 n，得到一个合法结果
                ans.emplace_back(s);  // 收进结果列表
                return;  // 本分支结束，返回上一层继续
            }  // 结束长度判断
            if (ans.size() >= k) {  // 已经凑够 k 个，后面的分支都不必再搜索（剪枝）
                return;  // 直接返回，省掉无谓的枚举
            }  // 结束剪枝判断
            for (char c = 'a'; c <= 'c'; ++c) {  // 按字典序依次尝试 a、b、c
                if (s.empty() || s.back() != c) {  // 当前为空可以放，或与上一个字符不同（开心字符串要求相邻不同）
                    s.push_back(c);  // 选中字符，压入当前串
                    dfs();  // 递归构造下一位
                    s.pop_back();  // 撤销选择，回溯到上一个状态
                }  // 结束字符合法性判断
            }  // 结束字符枚举循环
        };  // 结束 Lambda 定义
        dfs();  // 从空串开始搜索
        return ans.size() < k ? "" : ans[k - 1];  // 凑不够 k 个返回空串，否则取下标 k-1 的那个
    }  // 结束题解方法
};  // 结束题解类
