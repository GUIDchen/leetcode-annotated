// 题目：1707. 与数组中元素的最大异或值（Maximum XOR With an Element From Array）
// 思路：把询问按阈值 m 升序处理，同时把 nums 升序后用「只增不减」的指针依次插入 01 字典树；每次查询在树上从高位贪心走相反位，即得所有不超过 m 的元素中的最大异或值。
// 时间复杂度：O((n + q) × 31)，排序另有 O(n log n + q log q)；空间复杂度：O(n × 31)，字典树节点数。
class Trie {  // 01 字典树：每个节点最多两个孩子，对应当前二进制位的 0 或 1
private:  // 孩子数组对外隐藏，只能通过 insert/search 访问
    Trie* children[2];  // 两个子节点指针：children[0] 表示下一位是 0，children[1] 表示下一位是 1

public:  // 公开接口开始
    Trie()  // 构造函数：新节点的两个孩子先置空
        : children{nullptr, nullptr} {}  // 用初始化列表把两个孩子指针都设为 nullptr

    void insert(int x) {  // 把整数 x 的 31 个二进制位（第 30 位到第 0 位）插入字典树
        Trie* node = this;  // 从当前节点（根）开始向下走
        for (int i = 30; ~i; --i) {  // 从高位到低位枚举；~i 为真等价于 i >= 0，所以循环到第 0 位后停止
            int v = (x >> i) & 1;  // 取出 x 的第 i 位，结果只能是 0 或 1
            if (!node->children[v]) {  // 该位的分支还不存在
                node->children[v] = new Trie();  // 为该位新建一个节点挂上去
            }  // 节点创建完成
            node = node->children[v];  // 沿该位对应的分支继续下移
        }  // 插入结束
    }  // 空行：分隔插入与查询方法

    int search(int x) {  // 从根节点开始按位匹配
        Trie* node = this;  // 累积最大异或结果的各个二进制位
        int ans = 0;  // 从高位到低位贪心：高位能取 1 就优先取 1
        for (int i = 30; ~i; --i) {  // x 当前位的值
            int v = (x >> i) & 1;  // 存在与 x 该位相反的节点，异或后这一位为 1，是最优选择
            if (node->children[v ^ 1]) {  // 把结果的第 i 位置 1
                ans |= 1 << i;  // 走相反的那条分支
                node = node->children[v ^ 1];  // 否则尝试走与 x 相同的分支，该位异或结果为 0
            } else if (node->children[v]) {  // 沿相同分支继续下移
                node = node->children[v];  // 两个孩子都不存在，说明树是空的或已走到死路
            } else {  // 没有可用元素，按题意返回 -1
                return -1;  // 分支判断结束
            }  // 查询结束
        }  // 返回最大异或值
        return ans;  // 方法结束
    }  // Trie 类定义结束
};  // 空行：分隔字典树与题解类

class Solution {  // 题解方法对外可见
public:  // nums：候选数组；queries 每项是 [x, m]，表示只能在不超过 m 的元素中选
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {  // 升序排序，便于按阈值 m 从小到大逐步插入
        sort(nums.begin(), nums.end());  // 询问总个数
        int n = queries.size();  // 询问下标数组，用来按阈值排序后仍能回填原顺序的答案
        vector<int> idx(n);  // 把 idx 依次填成 0, 1, 2, ..., n-1
        iota(idx.begin(), idx.end(), 0);  // 按各自询问的 m 升序排列下标，使阈值单调推进
        sort(idx.begin(), idx.end(), [&](int i, int j) { return queries[i][1] < queries[j][1]; });  // 答案数组，按原始询问顺序存放
        vector<int> ans(n);  // 空的 01 字典树，只保存满足 nums[j] <= 当前 m 的元素
        Trie trie;  // 指向 nums 中下一个待插入元素，全程只增不减
        int j = 0;  // 按 m 从小到大的顺序处理每个询问
        for (int i : idx) {  // x 是参与异或的元素，m 是允许使用的元素上界
            int x = queries[i][0], m = queries[i][1];  // 把所有不超过 m 的 nums 元素一次性插入字典树
            while (j < nums.size() && nums[j] <= m) {  // 插入后指针前移，保证每个元素只插入一次
                trie.insert(nums[j++]);  // 询问处理完毕时，树中正好是全部合法元素
            }  // 在树上贪心求出与 x 异或最大的值，写到原询问下标处
            ans[i] = trie.search(x);  // 本轮询问处理结束
        }  // 按原顺序返回所有询问的答案
        return ans;  // 方法结束
    }  // 类定义结束
};  // 文件结束