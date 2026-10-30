// 题目：4015. 树的加权和（Weighted Sum of a Tree）
// 思路：按 parent 数组建出父→子的邻接表，用 BFS 逐层遍历（根为第 1 层，层号即深度 d）；遍历时先按 nums[i]*(1-d) 累加，BFS 结束后把层数 d（恰好等于树高 h）乘上节点值总和一次性补回，等价于每个节点乘上 (h-d+1)。
// 时间复杂度：O(n)，每个节点入队出队各一次；空间复杂度：O(n)，邻接表与分层队列各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long weightedSum(vector<int>& parent, vector<int>& nums) {  // parent：父节点数组（parent[0] = -1，树以 0 为根）；nums：节点值；返回按 nums[i]*(h-d+1) 求得的加权和
        int n = nums.size();  // 节点总数 n，编号为 0..n-1

        vector<vector<int>> g(n);  // 邻接表 g：只保存父节点指向子节点的边，供自上而下分层遍历使用

        for (int i = 1; i < n; i++) {  // 从 1 号节点开始建边（parent[0] = -1 不参与）
            g[parent[i]].push_back(i);  // 把子节点 i 挂到它的父节点 parent[i] 的孩子列表里
        }  // 建边结束

        long long ans = 0;  // ans 累计加权和，用 long long 防止溢出

        vector<int> q = {0};  // BFS 队列，根节点 0 入队，作为第 1 层

        int d = 0;  // d 记录当前层号；根节点深度为 1，所以处理第 d 层时 d 正好等于深度

        while (!q.empty()) {  // 逐层向外扩展，直到队列为空（整棵树遍历完）
            d++;  // 进入新的一层，层号（即深度）加一

            vector<int> nq;  // 存放下一层的全部节点

            for (int i : q) {  // 遍历当前层的每个节点
                ans += 1LL * nums[i] * (1 - d);  // 先记 nums[i]*(1-d)，相当于预扣 d*nums[i]，留到最后用 h*sum 统一补回
                for (int son : g[i]) {  // 枚举当前节点的所有子节点
                    nq.push_back(son);  // 子节点进入下一层的队列
                }  // 子节点枚举结束
            }  // 本层处理完毕

            q = move(nq);  // 队列整体切换到下一层（move 避免拷贝开销）
        }  // BFS 结束，此时 d 恰好等于树高 h（最大深度）

        long long sum = 0;  // sum 保存所有节点值之和
        for (int x : nums) {  // 遍历全部节点求和
            sum += x;  // 累加节点值
        }  // 求和结束

        ans += 1LL * d * sum;  // 补上 d*sum = h*sum，与前面的 -d*nums[i] 抵消后，每个节点最终乘上 (h-d+1)

        return ans;  // 返回加权和
    }  // 方法结束
};  // 类定义结束