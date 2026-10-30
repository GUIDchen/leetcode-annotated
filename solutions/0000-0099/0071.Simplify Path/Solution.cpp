// 题目：71. 简化路径（Simplify Path）
// 思路：按 '/' 切分路径，用双端队列当作栈：空串和 "." 直接忽略，".." 弹栈（栈非空时），其余目录名入栈，最后统一拼成以 '/' 开头的规范路径。
// 时间复杂度：O(n)，路径中每个字符只被扫描常数次；空间复杂度：O(n)，栈最多保存全部目录名。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string simplifyPath(string path) {  // path：待简化的绝对路径
        deque<string> stk;  // 用 deque 当栈，保存已经确定的目录名
        stringstream ss(path);  // 把路径包装成流，便于用 getline 按 '/' 拆分
        string t;  // t 用来接住每次切出来的一段
        while (getline(ss, t, '/')) {  // 以 '/' 为分隔符逐段读取；连续斜杠会产生空段
            if (t == "" || t == ".") {  // 空段（多余斜杠）和 "."（当前目录）对结果没有贡献
                continue;  // 直接跳过这一段
            }
            if (t == "..") {  // ".." 表示回到上一级目录
                if (!stk.empty()) {  // 栈为空说明已经在根目录，再往上仍停在根目录
                    stk.pop_back();  // 弹出最后一个目录，相当于返回上一级
                }
            } else {
                stk.push_back(t);  // 普通目录名，压入栈中作为路径的一层
            }
        }
        if (stk.empty()) {  // 所有目录都被消掉，说明最终就是根目录
            return "/";  // 根目录用单个斜杠表示
        }
        string ans;  // 逐段拼接最终的规范路径
        for (auto& s : stk) {  // 按从根到叶的顺序遍历栈中目录
            ans += "/" + s;  // 每个目录前加一个斜杠，保证形如 /a/b/c 且没有多余斜杠
        }
        return ans;  // 返回简化后的路径
    }
};