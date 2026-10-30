// 题目：385. 迷你语法分析器（Mini Parser）
// 思路：递归下降；按深度为 0 的逗号或结尾把内层切成若干段子串递归解析，首字符不是 '[' 时整段就是一个整数。
// 时间复杂度：O(n^2)，每层递归都要扫描并切分字符串；空间复杂度：O(n)，递归栈深度与嵌套层数同阶。
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {  // 题解类
public:  // 对外接口
    NestedInteger deserialize(string s) {  // s 是不含空格的序列化字符串，返回对应的 NestedInteger 结构
        if (s == "" || s == "[]") {  // 空串或空列表，都表示一个不装东西的嵌套列表
            return NestedInteger();  // 默认构造出来的就是空列表
        }
        if (s[0] != '[') {  // 首字符不是 '['，说明整段就是一个整数
            return NestedInteger(stoi(s));  // stoi 把字符串转成整数，再包成单值节点
        }
        NestedInteger ans;  // 当前这一层要构造的嵌套列表
        int depth = 0;  // depth 记录未配对的中括号层数，只有 depth 为 0 处的逗号才是本层的分隔符
        for (int i = 1, j = 1; i < s.size(); ++i) {  // i 从 1 开始跳过开头的 '['，j 记录本层当前子串的起点
            if (depth == 0 && (s[i] == ',' || i == s.size() - 1)) {  // 在本层遇到分隔逗号，或已扫到闭括号前的最后一个字符，说明一段结束
                ans.add(deserialize(s.substr(j, i - j)));  // 切出 [j, i) 这段子串递归解析，并挂到当前列表下
                j = i + 1;  // 下一段的起点跳过这个逗号
            } else if (s[i] == '[') {  // 遇到 '[' 表示进入更深一层
                ++depth;  // 层数加一，此后的逗号属于内层，不能在这里切分
            } else if (s[i] == ']') {  // 遇到 ']' 表示退回上一层
                --depth;  // 层数减一
            }
        }
        return ans;  // 返回这一层解析出的嵌套列表
    }
};