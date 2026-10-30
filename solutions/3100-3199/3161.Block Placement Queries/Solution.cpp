// 题目：3161. 物块放置查询（Block Placement Queries）
// 核心思路：倒序处理操作，把「放置障碍」化为「删除障碍」；有序集合维护障碍坐标，树状数组维护各障碍右端的最大可用区间长度，询问时比较左侧最大区间与 prev..x 这段是否够长。
// 时间复杂度：O((n+m)log m)，树状数组与有序集合操作均为对数级；空间复杂度：O(m)，树状数组大小由坐标上界决定。
class BinaryIndexedTree {  // 树状数组类：支持单点取 max 更新与前缀最大值查询
private:  // 以下为内部实现细节
    int n;  // 坐标上界（树状数组下标最大值）
    vector<int> c;  // c[i] 保存区间 (i-lowbit(i), i] 内的最大值

public:  // 以下为对外接口
    BinaryIndexedTree(int n) {  // 构造函数，n 为坐标上界
        this->n = n;  // 记下上界，update 的循环条件要用
        c.resize(n + 1);  // 开 n+1 个桶，下标从 1 开始使用
    }  // 构造函数结束

    void update(int x, int v) {  // 在位置 x 上用 v 更新最大值
        while (x <= n) {  // 沿 lowbit 向上，覆盖所有包含 x 的区间
            c[x] = max(c[x], v);  // 区间内取较大值，等价于单点赋 max
            x += x & -x;  // x + lowbit(x) 即父节点下标，继续向上跳
        }  // while 循环结束
    }  // update 结束

    int query(int x) {  // 查询前缀 [1, x] 上的最大值
        int mx = 0;  // 区间长度都非负，用 0 作初值即可
        while (x > 0) {  // 沿 lowbit 向下把前缀拆成若干块
            mx = max(mx, c[x]);  // 用当前块的答案更新结果
            x -= x & -x;  // 跳到前一块
        }  // while 循环结束
        return mx;  // 返回前缀最大值
    }  // query 结束
};  // 树状数组类结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> getResults(vector<vector<int>>& queries) {  // queries：操作序列，q[0]=1 放置障碍，q[0]=2 询问能否放下长 q[2] 的物块
        int m = 0;  // 所有操作中出现过的最大坐标
        for (auto& q : queries) {  // 第一遍扫描：求坐标上界，用来定树状数组大小
            m = max(m, q[1]);  // q[1] 是障碍位置或询问位置
        }  // for 循环结束
        set<int> ts{0, m + 1};  // 障碍坐标集合；哨兵 0 与 m+1 让每段区间都有左右两个端点
        for (auto& q : queries) {  // 第二遍扫描：把所有放置过的障碍一次性插入集合
            if (q[0] == 1) {  // 类型 1 才是放置障碍
                ts.insert(q[1]);  // 记录障碍坐标（重复插入自动去重）
            }  // if 结束
        }  // for 循环结束
        BinaryIndexedTree tree(m + 1);  // 以坐标上界建树状数组
        int pre = 0;  // 上一个障碍的位置，初始为哨兵 0
        for (int x : ts) {  // 按坐标从小到大遍历所有障碍端点
            if (x) {  // 跳过第一个哨兵 0：它没有左侧区间
                tree.update(x, x - pre);  // 位置 x 左侧（含 x）的可用区间长度是 x-pre，挂到右端点 x 上
            }  // if 结束
            pre = x;  // 当前障碍成为下一个端点的前驱
        }  // for 循环结束
        vector<bool> ans;  // 倒序处理时先把答案暂存，最后统一翻转
        for (int i = queries.size() - 1; i >= 0; --i) {  // 倒序撤销操作：从全部障碍就位的最终状态往回退
            int x = queries[i][1];  // 当前操作涉及的坐标
            if (queries[i][0] == 1) {  // 倒序遇到放置操作，等价于把该障碍删除
                auto it = ts.find(x);  // 在集合中定位要删除的障碍
                tree.update(*next(it), *next(it) - *prev(it));  // 删除后左右两段合并，右邻障碍的左端区间变长，更新它的最大值
                ts.erase(it);  // 真正从集合中移除
            } else {  // 否则是类型 2 的询问
                auto it = prev(ts.upper_bound(x));  // 找 x 左侧最近的障碍（哨兵 0 保证一定存在）
                ans.push_back(tree.query(*it) >= queries[i][2] || x - *it >= queries[i][2]);  // 左侧已有够长的区间，或 prev..x 这一段本身够长，都说明放得下
            }  // if/else 结束
        }  // 倒序遍历结束
        reverse(ans.begin(), ans.end());  // 答案是逆序收集的，翻转回正序
        return ans;  // 返回每个询问的结果
    }  // 方法结束
};  // 类定义结束
