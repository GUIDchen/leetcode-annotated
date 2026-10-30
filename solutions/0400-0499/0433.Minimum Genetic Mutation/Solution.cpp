// 题目：433. 最小基因变化（Minimum Genetic Mutation）
// 思路：把每种基因串视为图的一个顶点，相差恰好一个字符的两串之间有边；用 BFS 按变异次数分层搜索，首次到达 endGene 的层数就是最短次数。
// 时间复杂度：O(n² * 8)，n 为基因库大小，每个出队元素都要扫一遍 bank 并比较 8 个字符；空间复杂度：O(n)，队列与访问集合。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int minMutation(string startGene, string endGene, vector<string>& bank) {  // 返回把 startGene 变成 endGene 的最少变异次数，无法到达时返回 -1
        queue<pair<string, int>> q{{{startGene, 0}}};  // BFS 队列，元素是 (当前基因串, 已经变异的次数)，起点层数为 0
        unordered_set<string> vis = {startGene};  // 访问集合，起点先标记，避免后续重复入队
        while (!q.empty()) {  // 队列非空就继续按层向外扩展
            auto [gene, depth] = q.front();  // C++17 结构化绑定：取出队首的基因串和它所在的层数
            q.pop();  // 弹出队首，注意取出值之后才能 pop
            if (gene == endGene) {  // BFS 第一次到达终点，此时层数一定最小
                return depth;  // 直接返回最小变异次数
            }
            for (const string& next : bank) {  // 枚举基因库中的每个串，看能否从当前串一步变异过去
                int c = 2;  // 从 2 开始递减：每发现一处不同就减 1，减到 0 说明不同字符超过 1 个，非法
                for (int k = 0; k < 8 && c; ++k) {  // 逐位比较 8 个字符；c 已经为 0 时提前结束内层循环
                    c -= gene[k] != next[k];  // 该位不同则 c 减 1，相同则不变（利用 bool 转 int 的技巧）
                }
                if (c && !vis.contains(next)) {  // c 非 0 说明恰好只有一个字符不同，且该串尚未被访问过
                    vis.insert(next);  // 先标记已访问，避免同一串被重复入队
                    q.push({next, depth + 1});  // 把新串按层数 +1 入队
                }
            }
        }
        return -1;  // 队列耗尽仍未到达 endGene，说明不可达
    }
};