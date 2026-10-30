// 题目：1625. 执行操作后字典序最小的字符串（Lexicographically Smallest String After Applying Operations）
// 思路：把字符串当作状态做 BFS，每次扩展「奇数位数字加 a」和「右轮转 b 位」两种操作，用哈希集合去重，过程中取字典序最小者。
// 时间复杂度：O(n·10·n/b) 级别，状态数为轮转次数与数字组合数之积；空间复杂度：O(状态数)，用于哈希集合与队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string findLexSmallestString(string s, int a, int b) {  // s 为初始字符串，a 为加在奇数位上的数字，b 为轮转步长
        queue<string> q{{s}};  // BFS 队列，从初始串出发
        unordered_set<string> vis{{s}};  // 访问集合，记录出现过的串，避免重复搜索
        string ans = s;  // 答案初始化为原串
        int n = s.size();  // 字符串长度，轮转与遍历都要用
        while (!q.empty()) {  // 队列不空就继续扩展状态
            s = q.front();  // 取出队首串作为当前状态
            q.pop();  // 弹出已经取出的串
            ans = min(ans, s);  // 用当前串更新字典序最小的答案
            string t1 = s;  // 第一种操作：复制一份，对奇数位数字加 a
            for (int i = 1; i < n; i += 2) {  // 下标从 1 开始、每次加 2，即遍历所有奇数位
                t1[i] = (t1[i] - '0' + a) % 10 + '0';  // 字符转数字、加 a、对 10 取模，再转回字符
            }  // 奇数位处理结束
            string t2 = s.substr(n - b) + s.substr(0, n - b);  // 第二种操作：把后 b 个字符移到前面，等价于右轮转 b 位
            for (auto& t : {t1, t2}) {  // 依次尝试两种新状态
                if (!vis.count(t)) {  // 该状态此前没出现过才入队，避免重复
                    vis.insert(t);  // 标记为已访问
                    q.emplace(t);  // 新状态入队，等待后续扩展
                }  // if 分支结束
            }  // for 循环结束
        }  // while 循环结束
        return ans;  // 返回搜索过程中得到的最小字典序串
    }  // 方法结束
};  // 类定义结束