// 题目：2519. 统计 K-Big 索引的数量（Count the Number of K-Big Indices）
// 核心思路：两棵树状数组分别维护「左侧已出现」与「右侧剩余」的元素计数；扫描到 i 时先把它从右侧删掉，再判断两侧严格小于 nums[i] 的个数是否都不少于 k。
// 时间复杂度：O(n log n)，每次更新与查询都是 O(log n)；空间复杂度：O(n)，两棵长度为 n+1 的树状数组。
class BinaryIndexedTree {  // 手写树状数组（Binary Indexed Tree），支持单点加与前缀和查询
public:  // 对外接口
    BinaryIndexedTree(int _n)  // 构造函数：_n 是值域上界（本题取数组长度 n，配合值域 1..n）
        : n(_n)  // 记录上界，供 update 与 query 使用
        , c(_n + 1) {}  // c 是树状数组本体，下标从 1 开始，所以开 _n + 1

    void update(int x, int delta) {  // update：在下标 x 处加上 delta
        while (x <= n) {  // 沿 lowbit 链向上更新所有覆盖 x 的节点
            c[x] += delta;  // 当前节点的计数累加 delta
            x += x & -x;  // x += x & -x 跳到下一个受影响的节点
        }  // 结束 while
    }  // 结束 update

    int query(int x) {  // query：求前缀 [1, x] 的区间和
        int s = 0;  // s 累积答案
        while (x) {  // 沿 lowbit 链向下回退，直到下标归零
            s += c[x];  // 累加当前节点保存的区间和
            x -= x & -x;  // x -= x & -x 跳到前一个前缀块
        }  // 结束 while
        return s;  // 返回前缀和，即不大于 x 的元素个数
    }  // 结束 query

private:  // 私有成员：值域上界与树状数组本体
    int n;  // 值域上界
    vector<int> c;  // 树状数组，c[i] 管理区间 (i - lowbit(i), i]
};  // 结束 BinaryIndexedTree 类

class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int kBigIndices(vector<int>& nums, int k) {  // nums：输入数组；k：两侧都要求的严格小于的元素个数
        int n = nums.size();  // 数组长度，同时作为树状数组的值域上界
        BinaryIndexedTree* tree1 = new BinaryIndexedTree(n);  // tree1 统计当前下标左侧已出现过的元素
        BinaryIndexedTree* tree2 = new BinaryIndexedTree(n);  // tree2 统计当前下标右侧尚未处理的元素
        for (int& v : nums) {  // 先把所有元素都计入 tree2，表示初始时右侧拥有全部元素
            tree2->update(v, 1);  // 每个值出现一次，计数加一
        }  // 结束 for
        int ans = 0;  // ans 记录满足条件的下标个数
        for (int& v : nums) {  // 从左到右依次扫描每个下标
            tree2->update(v, -1);  // 当前元素即将被判定，先从右侧集合中删除它
            ans += tree1->query(v - 1) >= k && tree2->query(v - 1) >= k;  // 左侧与右侧严格小于当前值的个数都不少于 k 时条件成立，布尔值累加即为计数
            tree1->update(v, 1);  // 判定完成后把它加入左侧集合，供后面的下标使用
        }  // 结束 for
        return ans;  // 返回 K-Big 索引的总数
    }  // 结束 kBigIndices
};  // 结束 Solution 类