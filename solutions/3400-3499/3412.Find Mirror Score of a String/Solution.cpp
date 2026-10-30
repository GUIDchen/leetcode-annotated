// 3412. 计算字符串的镜像分数 / Find Mirror Score of a String
// 核心思路：用哈希表为每个字符维护未配对下标栈，遇到其镜像字符就弹出最近下标并累加距离。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution {  // 题解类定义
public:  // 公有接口
    long long calculateScore(string s) {  // 计算字符串的镜像分数
        unordered_map<char, vector<int>> d;  // 记录每个字符尚未配对的下标栈
        int n = s.length();  // 字符串长度
        long long ans = 0;  // 累加答案
        for (int i = 0; i < n; ++i) {  // 从左到右扫描每个字符
            char x = s[i];  // 当前字符
            char y = 'a' + 'z' - x;  // 镜像字符：a<->z, b<->y ...
            if (d.contains(y)) {  // 存在可配对的镜像字符
                vector<int>& ls = d[y];  // 取出该镜像字符的下标栈
                int j = ls.back();  // 最近的一个未配对下标
                ls.pop_back();  // 弹出该下标（每个下标只能用一次）
                if (ls.empty()) {  // 该字符的栈已空
                    d.erase(y);  // 从哈希表中删除空栈
                }  // 结束清理分支
                ans += i - j;  // 累加距离 i-j 作为分数
            } else {  // 否则没有可配对的镜像字符
                d[x].push_back(i);  // 把当前下标压入自己的栈
            }  // 结束分支
        }  // 结束扫描
        return ans;  // 返回总分
    }  // 结束 calculateScore
};  // 结束题解类
