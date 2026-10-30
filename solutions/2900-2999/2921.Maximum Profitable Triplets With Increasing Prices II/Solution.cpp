// 题目：2921. 价格递增的最大利润三元组 II（Maximum Profitable Triplets With Increasing Prices II）
// 思路：对每个中间位置 i，用树状数组分别预处理左侧价格更小、右侧价格更大的最大利润，再枚举 i 取三段利润之和的最大值。
// 时间复杂度：O(n log m)，两次扫描各一次查询与更新；空间复杂度：O(n + m)，两个树状数组与两个辅助数组。
class BinaryIndexedTree {  // 树状数组（BIT）：维护前缀最大值，支持单点更新与前缀查询
private:  // 内部实现细节不对外暴露
    int n;  // 下标上限
    vector<int> c;  // 树状数组本体，c[i] 存一段区间的最大值

public:  // 对外提供的构造与操作
    BinaryIndexedTree(int n) {  // 构造函数：n 取价格最大值 + 1
        this->n = n;  // 保存下标上限
        c.resize(n + 1, 0);  // 树状数组从下标 1 开始，初始化全 0
    }  // 构造函数结束

    void update(int x, int v) {  // 把位置 x 的贡献更新为 max(原值, v)
        while (x <= n) {  // 沿 x 的父链向上跳
            c[x] = max(c[x], v);  // 每个覆盖 x 的区间都取最大值
            x += x & -x;  // lowbit 跳到下一个覆盖位置
        }  // update 结束
    }
  // 查询区间 [1, x] 内的最大值
    int query(int x) {  // 价格带来的利润均为正，0 可作为空集答案
        int mx = 0;  // 不断去掉最低位的 1 向前缀收缩
        while (x > 0) {  // 用 c[x] 覆盖的区间更新答案
            mx = max(mx, c[x]);  // lowbit 跳到前一个区间
            x -= x & -x;  // 返回前缀最大值
        }  // query 结束
        return mx;  // 树状数组类定义结束
    }
};  // LeetCode 约定的题解类
  // 题解方法对外可见
class Solution {  // prices：价格；profits：对应利润；找 i<j<k 且价格递增的最优三元组
public:  // 商品个数
    int maxProfit(vector<int>& prices, vector<int>& profits) {  // left[i]：i 左边价格严格更小的商品中的最大利润
        int n = prices.size();  // right[i]：i 右边价格严格更大的商品中的最大利润
        vector<int> left(n, 0);  // 价格最大值，用来确定树状数组的大小
        vector<int> right(n, 0);  // 从左往右扫：按价格维护前缀最大利润
        int m = *max_element(prices.begin(), prices.end());  // 从右往左扫：把价格映射后再维护前缀最大利润
        BinaryIndexedTree tree1(m + 1);  // 第一遍：从左到右
        BinaryIndexedTree tree2(m + 1);  // 当前价格
        for (int i = 0; i < n; ++i) {  // 查询价格严格小于 x 的已出现商品的最大利润
            int x = prices[i];  // 把当前商品按价格插入树状数组
            left[i] = tree1.query(x - 1);  // 第一遍扫描结束
            tree1.update(x, profits[i]);  // 第二遍：从右到左
        }  // 反向映射价格，使「价格更大」变成「映射值更小」
        for (int i = n - 1; i >= 0; --i) {  // 查询右侧价格严格更大的商品的最大利润
            int x = m + 1 - prices[i];  // 把当前商品按映射价格插入
            right[i] = tree2.query(x - 1);  // 第二遍扫描结束
            tree2.update(x, profits[i]);  // 无解时返回 -1
        }  // 枚举中间元素 i
        int ans = -1;  // 左右都必须存在可行商品
        for (int i = 0; i < n; ++i) {  // 更新三元组总利润
            if (left[i] > 0 && right[i] > 0) {  // 判断结束
                ans = max(ans, left[i] + profits[i] + right[i]);  // 枚举结束
            }  // 返回最大总利润
        }  // maxProfit 结束
        return ans;  // 类定义结束
    }
};