// 题目：666. 路径总和 IV（Path Sum IV）
// 思路：把三位数 num 拆成「深度 num/10、层内位置、节点值 num%10」存进哈希表，再从根编码 11 开始 DFS，遇叶子累加整条路径和。
// 时间复杂度：O(n)，每个出现的节点访问一次；空间复杂度：O(n)，哈希表存所有节点。
class Solution {  // LeetCode 约定的题解类
public:  // 公有接口
    int ans;  // 所有叶子节点路径和的总和
    unordered_map<int, int> mp;  // 键为节点编码（深度 * 10 + 层内位置），值为节点数值

    int pathSum(vector<int>& nums) {  // nums 中每个三位数编码一个节点：百位是深度，十位是该层位置，个位是节点值
        ans = 0;  // 重置答案，避免同一个对象被多次调用时残留旧数据
        mp.clear();  // 清空哈希表，防止上一次调用遗留
        for (int num : nums) mp[num / 10] = num % 10;  // num/10 得到「深度 + 位置」的编码，num%10 是节点值
        dfs(11, 0);  // 根节点编码固定为 11（第 1 层第 1 个），从它开始 DFS，初始路径和为 0
        return ans;  // 返回累加好的结果
    }  // 结束 pathSum

    void dfs(int node, int t) {  // node：当前节点编码；t：从根走到当前节点（不含当前）的路径和
        if (!mp.count(node)) return;  // 该编码不存在说明这个位置没有节点，直接返回
        t += mp[node];  // 把当前节点值累加进路径和
        int d = node / 10, p = node % 10;  // 拆出当前深度 d 与该层位置 p
        int l = (d + 1) * 10 + (p * 2) - 1;  // 下一层左孩子的编码：深度加 1，位置 = 2p - 1
        int r = l + 1;  // 右孩子位置紧挨着左孩子
        if (!mp.count(l) && !mp.count(r)) {  // 左右孩子都不存在，说明当前是叶子节点
            ans += t;  // 叶子：把整条路径的和累加到答案
            return;  // 叶子没有孩子，返回
        }
        dfs(l, t);  // 继续往左子树走，带上已累计的路径和
        dfs(r, t);  // 继续往右子树走，带上已累计的路径和
    }  // 结束 dfs
};