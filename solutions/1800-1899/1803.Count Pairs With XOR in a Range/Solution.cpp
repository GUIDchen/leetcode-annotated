// 题目：1803. 统计异或值在范围内的数对有多少（Count Pairs With XOR in a Range）
// 思路：把「异或值 <= high」的计数减去「异或值 < low」的计数；用 01 字典树按位贪心，统计已插入的数中有多少个与当前数异或后严格小于 limit。
// 时间复杂度：O(n log C)，C 为值域位数（这里 16 位）；空间复杂度：O(n log C)，字典树节点数。
class Trie {  // 01 字典树节点：children[0]/children[1] 指向下一位为 0/1 的子节点
public:  // 节点接口对外可见
    Trie()  // 构造函数：初始化两个子节点为空、子树计数为 0
        : children(2)  // children 大小固定为 2，对应二进制的 0 和 1
        , cnt(0) {}  // cnt 记录经过该节点的数字个数（以该前缀开头的数量）

    void insert(int x) {  // 把数字 x 按二进制从高位到低位插入字典树
        Trie* node = this;  // 从根节点开始向下走
        for (int i = 15; ~i; --i) {  // 从第 15 位扫到第 0 位（题目元素值小于 2^16）
            int v = x >> i & 1;  // 取出 x 的第 i 位，即 0 或 1
            if (!node->children[v]) {  // 该位的子节点还不存在
                node->children[v] = new Trie();  // 新建一个子节点挂上去
            }
            node = node->children[v];  // 走到对应位的子节点
            ++node->cnt;  // 沿途每个节点的计数加一，供 search 统计使用
        }
    }

    int search(int x, int limit) {  // 统计已插入的数 y 中满足 (x ^ y) < limit 的个数
        Trie* node = this;  // 从根节点开始比较
        int ans = 0;  // 累计满足条件的个数
        for (int i = 15; ~i && node; --i) {  // 逐位比较；node 为空说明没有可继续匹配的前缀
            int v = x >> i & 1;  // 取出 x 的第 i 位
            if (limit >> i & 1) {  // limit 这一位是 1：异或位为 0 的分支整棵都满足，异或位为 1 的分支要继续比
                if (node->children[v]) {  // 若 y 的该位与 x 相同，异或结果为 0，整棵子树都小于 limit
                    ans += node->children[v]->cnt;  // 把该子树的数量直接累加进答案
                }
                node = node->children[v ^ 1];  // 再沿异或该位为 1 的分支继续找等于 limit 的可能
            } else {  // limit 这一位是 0：只能走异或位为 0 的分支才不会超过
                node = node->children[v];  // 沿异或位为 0（即与 x 该位相同）的分支继续
            }
        }
        return ans;  // 返回满足条件的数字个数
    }

private:  // 节点内部数据
    vector<Trie*> children;  // 两个子节点指针
    int cnt;  // 经过该节点的数字个数
};

class Solution {  // LeetCode 约定的题解类
public:
    int countPairs(vector<int>& nums, int low, int high) {  // 统计 nums 中满足 low <= (nums[i] ^ nums[j]) <= high 的数对个数
        Trie* tree = new Trie();  // 空的 01 字典树，用来保存已经遍历过的数
        int ans = 0;  // 答案：满足条件的下标对数量
        for (int& x : nums) {  // 逐个把元素作为右端点，统计它与之前元素的异或
            ans += tree->search(x, high + 1) - tree->search(x, low);  // 「异或小于 high+1」的个数减去「异或小于 low」的个数，即落在 [low, high] 内的个数
            tree->insert(x);  // 把当前元素插入字典树，供后面的元素查询
        }
        return ans;  // 返回满足条件的数对总数
    }
};