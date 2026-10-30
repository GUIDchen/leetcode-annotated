// 题目：3991. Sort Array Using Prefix Reversals（3991. 使用前缀反转对数组进行排序）
// 核心思路：把数组状态看作节点做 BFS，每一步可选任意长度 pre[i] 做前缀反转；数组用 8 进制逐位编码（每元素占一位，基 8 足够容纳 n ≤ 8 的取值）作为访问标记，首次到达升序状态时的层数即最少反转次数。
// 复杂度：时间 O(n!·|pre|)，空间 O(n!)（最坏遍历所有排列）。
class Solution {  // 定义题解类
public:  // 公开接口
    int sortArray(vector<int>& nums, vector<int>& pre) {  // 返回用 pre 中的前缀长度把 nums 反转成升序所需的最少操作次数
        int n = nums.size();  // n 为数组长度，元素的取值来自 0..n-1

        int target = 0;  // target 记录升序状态的编码
        for (int i = 0; i < n; i++) {  // 逐位拼接升序下标 0,1,…,n-1
            target = target * 8 + i;  // 编码左移一位（乘 8）后加入当前下标
        }  // 升序目标编码构造完成

        int start = 0;  // start 记录初始数组状态的编码
        for (int x : nums) {  // 逐位拼接初始数组的每个元素
            start = start * 8 + x;  // 编码左移一位后加入当前元素
        }  // 初始状态编码构造完成

        if (start == target) {  // 初始状态已经是升序
            return 0;  // 不需要任何操作
        }  // if 分支结束

        unordered_set<int> vis;  // vis 记录已入过队的编码，避免重复搜索
        vis.insert(start);  // 初始状态标记为已访问

        queue<pair<vector<int>, int>> q;  // 队列元素为 (数组状态, 已用操作次数)，用于 BFS 求最短路
        q.emplace(nums, 0);  // 把初始状态与 0 次操作入队

        while (!q.empty()) {  // 队列非空就继续搜索
            auto [state, dist] = q.front();  // 取出队首的状态与操作次数
            q.pop();  // 队首出队

            int nd = dist + 1;  // 扩展到下一层，操作次数加一

            for (int x : pre) {  // 逐个尝试 pre 中允许的前缀长度
                vector<int> nxt = state;  // 复制当前状态，得到待修改的新状态
                reverse(nxt.begin(), nxt.begin() + x);  // 反转前 x 个元素（一次前缀反转操作）

                int key = 0;  // key 用于给新状态编码
                for (int v : nxt) {  // 逐位拼接新状态
                    key = key * 8 + v;  // 编码左移一位后加入当前元素
                }  // 新状态编码构造完成

                if (key == target) {  // 首次到达升序状态，层数就是最少操作次数
                    return nd;  // 返回这一层对应的操作次数
                }  // if 分支结束

                if (vis.insert(key).second) {  // 该状态从未访问过才入队（insert 返回是否为新插入）
                    q.emplace(move(nxt), nd);  // 用移动语义入队，省去一次数组拷贝
                }  // if 分支结束
            }  // 前缀长度遍历结束
        }  // 当前层搜索结束

        return -1;  // BFS 结束仍未到达升序，说明无法排序
    }  // 方法结束
};  // 类定义结束