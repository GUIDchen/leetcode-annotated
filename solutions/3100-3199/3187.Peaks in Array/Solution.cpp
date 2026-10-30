// 题目：3187. 数组中的峰值（Peaks in Array）
// 思路：用树状数组维护每个下标「是否为峰」的 0/1 标记；查询时对区间 [q1+1, q2-1] 求前缀和之差，修改时只重算 idx-1、idx、idx+1 三处标记。
// 时间复杂度：O((n + q) log n)，每次操作都是对数级；空间复杂度：O(n)，树状数组长度为 n+1。
class BinaryIndexedTree {  // 树状数组：单点增减与前缀和查询都是 O(log n)
private:  // 内部数据
    int n;  // 下标上界：有效下标范围是 1..n
    vector<int> c;  // 树状数组本体，c[i] 保存某一段区间的和

public:  // 对外接口
    BinaryIndexedTree(int n)  // 构造函数：n 是允许使用的最大下标
        : n(n)  // 初始化下标上界
        , c(n + 1) {}  // 多开一位，让下标从 1 开始，方便 lowbit 计算

    void update(int x, int delta) {  // 把下标 x 对应的值增加 delta
        for (; x <= n; x += x & -x) {  // 沿 x + lowbit(x) 向上，更新所有覆盖 x 的节点
            c[x] += delta;  // 累加这次增量
        }  // 更新结束
    }  // 更新函数结束

    int query(int x) {  // 求前缀和 c[1] + c[2] + ... + c[x]
        int s = 0;  // 前缀和累加器
        for (; x > 0; x -= x & -x) {  // 沿 x - lowbit(x) 向下拆分区间
            s += c[x];  // 累加当前区间的和
        }  // 前缀和拼装完毕
        return s;  // 返回前缀和
    }  // 查询函数结束
};  // 树状数组类结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {  // nums 是原数组；queries 中 [1,l,r] 表示查询、[2,i,val] 表示修改
        int n = nums.size();  // 数组长度
        BinaryIndexedTree tree(n - 1);  // 用树状数组存每个下标「是否为峰」，峰只可能出现在 1..n-2，上界取 n-1
        auto update = [&](int i, int val) {  // 局部函数：把下标 i 的「是否为峰」加上 val
            if (i <= 0 || i >= n - 1) {  // 首尾元素缺少一侧邻居，不可能是峰
                return;  // 直接返回，不做任何更新
            }  // 边界判断结束
            if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {  // 严格大于左右邻居才是峰
                tree.update(i, val);  // 是峰就给标记加上 val（val 为 -1 时表示撤销）
            }  // 峰判断结束
        };  // 局部函数定义结束
        for (int i = 1; i < n - 1; ++i) {  // 初始化：统计原数组中所有峰
            update(i, 1);  // 每个峰在树状数组上记 1
        }  // 初始化完成
        vector<int> ans;  // 按顺序收集每次查询的答案
        for (auto& q : queries) {  // 依次处理每条操作
            if (q[0] == 1) {  // 类型 1：查询子数组 [q[1], q[2]] 内的峰个数
                int l = q[1] + 1, r = q[2] - 1;  // 子数组内的峰只可能出现在 l+1..r-1，这里换算成闭区间端点
                ans.push_back(l > r ? 0 : tree.query(r) - tree.query(l - 1));  // 长度不足 3 时没有峰，否则用前缀和相减得到区间内峰的个数
            } else {  // 类型 2：单点修改
                int idx = q[1], val = q[2];  // 要修改的下标与新的值
                for (int i = idx - 1; i <= idx + 1; ++i) {  // 只有 idx-1、idx、idx+1 三个位置的峰状态可能改变
                    update(i, -1);  // 先撤销这三处在旧值下的贡献
                }  // 撤销完成
                nums[idx] = val;  // 真正修改数组
                for (int i = idx - 1; i <= idx + 1; ++i) {  // 再按新值重新计算这三处
                    update(i, 1);  // 若新状态下是峰就重新登记
                }  // 重新登记完成
            }  // 操作分支结束
        }  // 所有操作处理完毕
        return ans;  // 按顺序返回所有查询结果
    }  // 方法结束
};