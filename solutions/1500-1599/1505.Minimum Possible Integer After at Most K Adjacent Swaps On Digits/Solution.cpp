// 题目：1505. 最多 K 次交换相邻数位后得到的最小整数（Minimum Possible Integer After at Most K Adjacent Swaps On Digits）
// 思路：从左到右逐位贪心，10 个队列记录每个数字的原始位置，树状数组统计已固定数字带来的位移，选出能负担得起的最小数字。
// 时间复杂度：O(10 * n log n)，每位最多试 10 个数字、每次一次树状数组查询；空间复杂度：O(n)，树状数组与队列。
class BinaryIndexedTree {  // 树状数组：单点加 + 前缀和查询，用来统计哪些原始位置已经被取走
public:  // 对外可见
    int n;  // 下标范围 1..n
    vector<int> c;  // 树状数组本体，1-based

    BinaryIndexedTree(int _n)  // 构造函数：规模上限为 _n
        : n(_n)  // 保存规模
        , c(_n + 1) {}  // 数组开 n+1 个位置并清零

    void update(int x, int delta) {  // 在位置 x 上累加 delta
        while (x <= n) {  // 沿父结点方向向上更新
            c[x] += delta;  // 累加增量
            x += lowbit(x);  // 跳到下一个受影响的结点
        }
    }

    int query(int x) {  // 求前缀和 1..x
        int s = 0;  // 累加结果
        while (x > 0) {  // 沿 lowbit 方向把区间逐个拆开
            s += c[x];  // 累加当前结点负责的区间
            x -= lowbit(x);  // 跳到前一个区间
        }
        return s;  // 返回前缀和
    }

    int lowbit(int x) {  // 取 x 的最低位 1 所代表的数值
        return x & -x;  // 位运算技巧：x 与 -x 相与只保留最低位的 1
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    string minInteger(string num, int k) {  // num：数字字符串；k：最多允许的相邻交换次数；返回能得到的最小整数（字符串形式）
        vector<queue<int>> pos(10);  // pos[d] 存放数字 d 出现的全部原始下标（1-based），按先后顺序入队
        int n = num.size();  // 数的长度
        for (int i = 0; i < n; ++i) pos[num[i] - '0'].push(i + 1);  // 统计每个数字出现的位置，下标统一转成 1-based 以配合树状数组
        BinaryIndexedTree* tree = new BinaryIndexedTree(n);  // 树状数组标记哪些原始位置已经被取走
        string ans = "";  // 逐位构造的答案
        for (int i = 1; i <= n; ++i) {  // 依次确定答案的第 i 位（1-based）
            for (int v = 0; v < 10; ++v) {  // 贪心：从小到大尝试放哪个数字
                auto& q = pos[v];  // 该数字还未使用的原始位置队列
                if (!q.empty()) {  // 该数字还有剩余可用位置
                    int j = q.front();  // 取它最靠前的一个位置
                    int dist = tree->query(n) - tree->query(j) + j - i;  // 估算交换次数：基准距离 j - i，再加上已取走元素（原本位于 j 右侧）带来的额外位移
                    if (dist <= k) {  // 剩余交换次数够把它移到第 i 位
                        k -= dist;  // 扣掉本次交换消耗的次数
                        q.pop();  // 该位置已被使用，出队
                        ans += (v + '0');  // 把数字字符接到答案末尾
                        tree->update(j, 1);  // 标记该位置已取走，供后续位修正位移
                        break;  // 当前位已确定，跳出尝试循环
                    }
                }
            }
        }
        return ans;  // 返回最小整数
    }
};