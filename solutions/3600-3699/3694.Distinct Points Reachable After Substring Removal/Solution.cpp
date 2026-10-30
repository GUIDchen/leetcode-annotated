// 3694. Distinct Points Reachable After Substring Removal（3694. 删除子字符串后不同的终点）
// 核心思路：先求出每走一步后的前缀坐标；删掉长度恰为 k 的子串 [i-k+1, i] 后，终点 = 总位移 - 该子串的位移，把所有结果放进哈希集合去重后计数。
// 复杂度：时间 O(n)，空间 O(n)，n 为字符串长度。
class Solution {  // 定义题解类
public:  // 公有接口
    int distinctPoints(string s, int k) {  // 主函数：返回删除任意一个长度恰为 k 的子串后，可能到达的不同终点个数
        int n = s.size();  // n 为字符串长度
        vector<int> f(n + 1), g(n + 1);  // f[i] / g[i] 记录走完前 i 步后的横、纵坐标
        int x = 0, y = 0;  // 当前坐标为 (x, y)
        for (int i = 1; i <= n; ++i) {  // 逐字符模拟行走
            char c = s[i - 1];  // 取出第 i 个字符（i 从 1 开始）
            if (c == 'U')  // 向上走，纵坐标加一
                ++y;  // 纵坐标 +1
            else if (c == 'D')  // 向下走，纵坐标减一
                --y;  // 纵坐标 -1
            else if (c == 'L')  // 向左走，横坐标减一
                --x;  // 横坐标 -1
            else  // 其余情况（'R'）向右走
                ++x;  // 横坐标 +1
            f[i] = x;  // 记录走完前 i 步后的横坐标
            g[i] = y;  // 记录走完前 i 步后的纵坐标
        }  // 循环结束
        unordered_set<long long> st;  // 用集合对不同终点去重
        for (int i = k; i <= n; ++i) {  // 枚举被删除的长度为 k 的区间右端点 i
            int a = f[n] - (f[i] - f[i - k]);  // 新终点横坐标 = 全程位移 - 被删区间位移
            int b = g[n] - (g[i] - g[i - k]);  // 新终点纵坐标 = 全程位移 - 被删区间位移
            st.insert(1LL * a * n + b);  // 用 a*n+b 把二维坐标压缩成一个整数键存入集合
        }  // 循环结束
        return st.size();  // 集合大小就是不同终点的个数
    }  // 主函数结束
};  // 类定义结束
