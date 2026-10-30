// 题目：2612. 最少翻转操作数（Minimum Reverse Operations）
// 思路：BFS 求最少翻转次数；翻转只会在同奇偶的下标之间跳，用两个有序集合保存未访问下标，按可达区间批量取出并删除。
// 时间复杂度：O(n log n)，每个下标只被取出删除一次；空间复杂度：O(n)，答案数组与两个有序集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {  // n：数组长度；p：初始 1 的下标；banned：禁止出现的下标；k：翻转区间长度
        vector<int> ans(n, -1);  // ans：答案，-1 表示无法到达
        ans[p] = 0;  // 起点 p 需要 0 次操作
        set<int> ts[2];  // 按下标奇偶分成两个有序集合，保存「尚未确定答案」的下标
        for (int i = 0; i < n; ++i) {  // 把所有可用下标按奇偶入集合
            ts[i % 2].insert(i);  // i 按奇偶放进对应集合
        }  // 集合初始化完成
        ts[p % 2].erase(p);  // 起点已经确定答案，从集合中删除
        for (int i : banned) {  // 处理被禁止的下标
            ts[i % 2].erase(i);  // 禁止的下标永远不可达，直接删除
        }  // 禁止表处理完毕
        ts[0].insert(n);  // 放一个哨兵 n，避免 lower_bound 越界
        ts[1].insert(n);  // 两个集合都要放哨兵
        queue<int> q{{p}};  // BFS 队列，从起点 p 开始
        while (!q.empty()) {  // 队列非空就继续扩展
            int i = q.front();  // 取队首下标
            q.pop();  // 弹出队首
            int mi = max(i - k + 1, k - i - 1);  // k 长翻转后能到达的最小下标
            int mx = min(i + k - 1, n * 2 - k - i - 1);  // k 长翻转后能到达的最大下标
            auto& s = ts[mi % 2];  // 翻转不改变下标奇偶性，取对应奇偶的集合
            auto it = s.lower_bound(mi);  // 从 >= mi 的第一个未访问下标开始
            while (*it <= mx) {  // 区间内（<= mx）的下标都能一步到达
                int j = *it;  // 取出该下标
                ans[j] = ans[i] + 1;  // BFS 层数 + 1 就是最少操作次数
                q.push(j);  // 新下标入队，继续扩展
                it = s.erase(it);  // 删除已访问的下标，同时把迭代器移到下一个
            }  // 区间处理完毕
        }  // BFS 结束
        return ans;  // 返回每个下标的最少操作次数
    }  // 方法结束
};  // 类定义结束