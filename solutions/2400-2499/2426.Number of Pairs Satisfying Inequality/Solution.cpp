// 题目：2426. 满足不等式的数对数目（Number of Pairs Satisfying Inequality）
// 核心思路：把条件变形为 nums1[i]-nums2[i] <= nums1[j]-nums2[j] + diff。令 v = nums1-nums2，按下标顺序扫描，用树状数组维护「已经出现过的 v」，对当前 v 查询有多少个旧值 <= 当前值+diff；所有下标统一 +40000 平移以消除负数。
// 时间复杂度：O(n log C)，C 为值域 1e5；空间复杂度：O(C)，即树状数组的存储开销。
class BinaryIndexedTree {  // 树状数组：支持单点加与前缀和查询，用来统计值域内的元素个数
public:  // 对外接口
    int n;  // 值域上界，也是树状数组的有效下标最大值
    vector<int> c;  // c[i] 存放 i 所管辖区间（i-lowbit(i)+1 到 i）内的计数和

    BinaryIndexedTree(int _n)  // 构造函数，_n 是值域大小
        : n(_n)  // 初始化值域上界
        , c(_n + 1) {}  // 下标从 1 开始，所以容量开到 _n+1，并默认初始化为 0

    void update(int x, int delta) {  // 在下标 x 处把计数增加 delta
        while (x <= n) {  // 只要还没越界，就沿着 lowbit 向上爬
            c[x] += delta;  // 更新当前节点记录的区间和
            x += lowbit(x);  // 跳到下一个覆盖 x 的节点
        }  // 上爬结束
    }  // update 方法结束

    int query(int x) {  // 查询前缀 [1, x] 内的元素总数
        int s = 0;  // 前缀和累加器
        while (x > 0) {  // x 大于 0 时不断剥离最低位的 1
            s += c[x];  // 累加当前节点覆盖的那段区间
            x -= lowbit(x);  // 去掉最低位 1，继续处理剩余前缀
        }
        return s;  // 返回 [1, x] 的计数和
    }  // query 方法结束

    int lowbit(int x) {  // 取出 x 二进制中最低位 1 所代表的数值
        return x & -x;  // 位运算技巧：x 与 -x 相与，恰好只保留最低位的 1
    }  // lowbit 方法结束
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {  // nums1、nums2 是输入数组，diff 是允许的偏差，返回满足不等式的下标对数目
        BinaryIndexedTree* tree = new BinaryIndexedTree(1e5);  // 值域取 1e5，足以容纳平移后的所有 v 值（负数 +40000 后仍在范围内）
        long long ans = 0;  // 答案可能达到 O(n^2)，用 long long 避免溢出
        for (int i = 0; i < nums1.size(); ++i) {  // 按顺序处理每个下标 i，树状数组里只保存下标更小的元素，天然满足 i < j
            int v = nums1[i] - nums2[i];  // 题目条件变形后的值 v_i = nums1[i] - nums2[i]
            ans += tree->query(v + diff + 40000);  // 统计已存入的 v_j 中满足 v_j <= v_i + diff 的个数，+40000 是把负数平移到合法下标
            tree->update(v + 40000, 1);  // 把当前 v_i 计入树状数组，供后续下标查询
        }  // 扫完整个数组
        return ans;  // 返回满足条件的下标对总数
    }  // 方法结束
};  // 类定义结束