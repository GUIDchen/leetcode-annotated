// 题目：315. 计算右侧小于当前元素的个数（Count of Smaller Numbers After Self）
// 思路：把所有值离散化后用树状数组维护出现次数，从右往左扫描，边插入边查询严格小于当前值的个数。
// 时间复杂度：O(n log n)，每次更新与查询都是 O(log n)；空间复杂度：O(n)，离线数组与树状数组。
class BinaryIndexedTree {  // 树状数组（Fenwick 树）：支持单点加、前缀和查询
public:  // 对外可见
    int n;  // 树状数组覆盖的下标范围是 1..n
    vector<int> c;  // c[i] 保存区间 (i - lowbit(i), i] 内的元素和

    BinaryIndexedTree(int _n)  // 构造函数，_n 是离散化后的元素个数
        : n(_n)  // 记录规模
        , c(_n + 1) {}  // 下标从 1 开始，所以数组长度是 n + 1，元素默认初始化为 0

    void update(int x, int delta) {  // 在位置 x 上加上 delta
        while (x <= n) {  // 沿父节点链向上更新，直到超出范围
            c[x] += delta;  // 把增量累加到当前节点
            x += lowbit(x);  // 跳到下一个需要更新的节点
        }
    }

    int query(int x) {  // 求前缀和 1..x
        int s = 0;  // 累加器，保存前缀和
        while (x > 0) {  // 沿前一个块链向下累加
            s += c[x];  // 加上当前块覆盖的区间和
            x -= lowbit(x);  // 跳到左边剩下的区间
        }
        return s;  // 返回前缀和
    }

    int lowbit(int x) {  // 取出 x 二进制最低位的 1
        return x & -x;  // 位运算技巧：x & -x
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countSmaller(vector<int>& nums) {  // nums：待统计的数组
        unordered_set<int> s(nums.begin(), nums.end());  // 去重得到所有出现过的值（排序前先放进集合）
        vector<int> alls(s.begin(), s.end());  // 去重后的值列表
        sort(alls.begin(), alls.end());  // 升序排序，用于离散化
        unordered_map<int, int> m;  // 值 → 离散化后的下标
        int n = alls.size();  // 不同值的个数，也就是树状数组的规模
        for (int i = 0; i < n; ++i) m[alls[i]] = i + 1;  // 建立映射，最小值对应下标 1（树状数组从 1 开始）
        BinaryIndexedTree* tree = new BinaryIndexedTree(n);  // 新建树状数组，规模为不同值的个数
        vector<int> ans(nums.size());  // 存放每个位置的答案，长度与 nums 相同
        for (int i = nums.size() - 1; i >= 0; --i) {  // 从右往左遍历，保证树中只有当前元素右侧的数
            int x = m[nums[i]];  // 当前值离散化后的下标
            tree->update(x, 1);  // 把当前值计入树状数组（出现一次）
            ans[i] = tree->query(x - 1);  // 查询严格小于当前值的元素个数，写入当前位置
        }
        return ans;  // 返回每个位置右侧比它小的元素个数
    }
};