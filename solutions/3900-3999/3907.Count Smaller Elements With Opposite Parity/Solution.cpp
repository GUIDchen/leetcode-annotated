// 3907. 统计具有相反奇偶性的较小元素 🔒（Count Smaller Elements With Opposite Parity）
// 思路：从右往左扫描，用奇偶两棵树状数组分别维护已经出现过的值（离散化后），对每个元素查询另一奇偶树中小于它的元素个数。
// 复杂度：时间复杂度 O(n log n)，空间复杂度 O(n)。
struct BIT {  // 树状数组（下标从 1 开始）
    int n;  // 树状数组的规模
    vector<int> c;  // 树状数组本体
    BIT(int n)  // 构造函数
        : n(n)  // 初始化规模
        , c(n + 1, 0) {}  // 下标从 1 开始，多开一位并清零
    void update(int x, int delta) {  // 单点加 delta
        for (; x <= n; x += x & -x) c[x] += delta;  // lowbit 向上跳到下一个覆盖该点的位置
    }  // update 结束
    int query(int x) {  // 查询前缀和 [1, x]
        int s = 0;  // 累加结果
        for (; x > 0; x -= x & -x) s += c[x];  // lowbit 向下跳到上一个不重叠的区间
        return s;  // 返回前缀和
    }  // query 结束
};  // BIT 结构体结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countSmallerOppositeParity(vector<int>& nums) {  // 对每个元素统计其右侧更小且奇偶性相反的元素个数
        int n = nums.size();  // 数组长度
        vector<int> sorted = nums;  // 复制一份用于离散化
        sort(sorted.begin(), sorted.end());  // 排序
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());  // 去重，得到所有出现过的不同值

        int m = sorted.size();  // 不同值的个数，即树状数组的规模
        BIT* bits[2] = {new BIT(m), new BIT(m)};  // 奇偶各一棵树状数组，bits[0] 存偶数、bits[1] 存奇数
        vector<int> ans(n);  // 答案数组

        for (int i = n - 1; i >= 0; --i) {  // 从右往左扫描，保证树里都是右侧元素
            int x = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin() + 1;  // 离散化到 1 基下标
            ans[i] = bits[nums[i] & 1 ^ 1]->query(x - 1);  // 查询另一奇偶树中严格小于 nums[i] 的元素个数
            bits[nums[i] & 1]->update(x, 1);  // 把当前值插入对应奇偶的树状数组
        }  // 扫描结束
        return ans;  // 返回结果
    }  // 方法结束
};  // 类定义结束
