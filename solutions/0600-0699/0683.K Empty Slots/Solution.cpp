// 题目：683. K 个关闭的灯泡（K Empty Slots）
// 思路：按天依次点亮灯泡，用树状数组统计区间内已亮灯泡数；每点亮位置 x，只检查左右各 k+1 处是否已亮且二者中间没有别的亮灯。
// 时间复杂度：O(n log n)，每天一次树状数组更新与常数次前缀查询；空间复杂度：O(n)，树状数组与 vis 数组各占 O(n)。
class BinaryIndexedTree {  // 树状数组：支持单点加与前缀和查询
public:  // 对外提供的接口
    int n;  // 下标上界（1..n）
    vector<int> c;  // 树状数组本体，c[i] 覆盖一段区间的和

    BinaryIndexedTree(int _n)  // 构造函数：_n 是下标上界
        : n(_n)  // 记录下标上界
        , c(_n + 1) {}  // 下标从 1 开始使用，所以开 n+1 个位置

    void update(int x, int delta) {  // 在位置 x 上加上 delta
        for (; x <= n; x += x & -x) {  // x & -x 取出最低位的 1，沿树向上跳
            c[x] += delta;  // 把增量累加到覆盖 x 的每个节点
        }
    }

    int query(int x) {  // 查询位置 1..x 的前缀和
        int s = 0;  // 累加结果
        for (; x; x -= x & -x) {  // 每次去掉最低位的 1，沿树向下跳
            s += c[x];  // 累加当前节点覆盖的区间和
        }
        return s;  // 返回 1..x 的累加和
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    int kEmptySlots(vector<int>& bulbs, int k) {  // bulbs[i] 是第 i+1 天点亮的灯泡位置；k 是要求中间隔开的空位数
        int n = bulbs.size();  // 灯泡总数
        BinaryIndexedTree* tree = new BinaryIndexedTree(n);  // 动态创建树状数组，用来统计已点亮的灯泡数量
        bool vis[n + 1];  // 标记数组：vis[i] 表示位置 i 的灯泡是否已点亮
        memset(vis, false, sizeof(vis));  // 全部初始化为未点亮
        for (int i = 1; i <= n; ++i) {  // 按天数依次点亮灯泡
            int x = bulbs[i - 1];  // 今天点亮的位置
            tree->update(x, 1);  // 在树状数组中给位置 x 加 1，表示这里亮了
            vis[x] = true;  // 标记该位置已点亮
            int y = x - k - 1;  // 左侧可能的另一个亮灯位置：与 x 恰好隔 k 个空位
            if (y > 0 && vis[y] && tree->query(x - 1) - tree->query(y) == 0) {  // 左侧已亮，且 (y, x) 之间没有任何亮灯
                return i;  // 第 i 天首次出现符合条件的情况
            }
            y = x + k + 1;  // 右侧可能的另一个亮灯位置
            if (y <= n && vis[y] && tree->query(y - 1) - tree->query(x) == 0) {  // 右侧已亮，且 (x, y) 之间没有任何亮灯
                return i;  // 第 i 天首次出现符合条件的情况
            }
        }
        return -1;  // 直到最后一天都没有出现两个亮灯之间恰好隔 k 个空位
    }
};