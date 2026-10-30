// 题目：1096. 花括号展开 II（Brace Expansion II）
// 思路：递归剥离最内层的一对花括号，把逗号分隔的每个选项分别替换后继续递归，直到没有花括号；用 set 去重并保证字典序。
// 时间复杂度：与展开结果个数 r 及串长 n 相关，约为 O(r · n)；空间复杂度：O(r · n)，保存全部结果与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> braceExpansionII(string expression) {  // expression：形如 {a,b}{c,{d,e}} 的花括号表达式
        dfs(expression);  // 从完整表达式开始递归展开
        return vector<string>(s.begin(), s.end());  // s 是 set，天然去重且有序，直接拷贝成 vector 返回
    }  // 方法结束

private:  // 以下为私有成员与辅助函数
    set<string> s;  // 结果集合：既用于去重，也保证字典序

    void dfs(string exp) {  // 递归处理当前表达式 exp，每次替换掉最内层的一对花括号
        int j = exp.find_first_of('}');  // 找到第一个右花括号，即最内层分支的右端点
        if (j == string::npos) {  // 找不到右花括号，说明已经没有可选分支
            s.insert(exp);  // 整个表达式就是一种展开结果，插入集合并返回
            return;  // 提前返回，结束本次递归
        }  // if 结束
        int i = exp.rfind('{', j);  // 从 j 往左找与它配对的左花括号
        string a = exp.substr(0, i);  // 花括号前面的固定前缀
        string c = exp.substr(j + 1);  // 花括号后面的固定后缀
        stringstream ss(exp.substr(i + 1, j - i - 1));  // 把花括号内部按逗号切开
        string b;  // 存放当前切出的一个选项
        while (getline(ss, b, ',')) {  // 按逗号逐个读取选项
            dfs(a + b + c);  // 拼成「前缀 + 选项 + 后缀」的新表达式继续递归
        }  // while 结束
    }  // dfs 结束
};  // 类定义结束