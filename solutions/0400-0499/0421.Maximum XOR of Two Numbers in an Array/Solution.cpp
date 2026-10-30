// 题目：421. 数组中两个数的最大异或值（Maximum XOR of Two Numbers in an Array）
// 思路：把所有数按二进制位从高到低插入 0/1 字典树；查询时贪心地优先走「相反位」分支，使高位尽量为 1，从而得到最大异或值。
// 时间复杂度：O(n * 31)，每个数插入与查询各 31 步；空间复杂度：O(n * 31)，字典树节点数。
class Trie {  // 二进制字典树（Trie）：每个节点最多两个子节点，分别对应下一位是 0 还是 1
public:  // 对外可见
    Trie* children[2];  // 两个子指针：children[0] 表示下一位为 0 的分支，children[1] 表示下一位为 1 的分支

    Trie()  // 构造函数：把两个子指针初始化为空
        : children{nullptr, nullptr} {}  // 用初始化列表把 children 数组填成两个 nullptr

    void insert(int x) {  // 把数字 x 的二进制位从高到低插入字典树
        Trie* node = this;  // node 从根节点开始向下走
        for (int i = 30; ~i; --i) {  // 从第 30 位枚举到第 0 位（数值 < 2^31，第 31 位符号位不用管）
            int v = x >> i & 1;  // 取出 x 的第 i 位（0 或 1）
            if (!node->children[v]) {  // 该位对应的分支还不存在
                node->children[v] = new Trie();  // 新建一个节点挂上去
            }  // if 分支结束
            node = node->children[v];  // 沿该位对应的分支继续向下
        }  // 位循环结束
    }  // insert 方法结束

    int search(int x) {  // 查询 x 与树中已有数字能异或出的最大值
        Trie* node = this;  // 从根节点开始
        int ans = 0;  // ans 累积最优异或结果
        for (int i = 30; ~i; --i) {  // 同样从高位到低位逐位决策
            int v = x >> i & 1;  // 取出 x 的第 i 位
            if (node->children[v ^ 1]) {  // 若存在与当前位相反的子树，异或后这一位就是 1，结果更优
                ans |= 1 << i;  // 把答案的第 i 位置为 1
                node = node->children[v ^ 1];  // 走向相反位分支
            } else {  // 否则只能走相同位的分支，这一位异或结果为 0
                node = node->children[v];  // 走向相同位分支
            }  // if-else 结束
        }  // 位循环结束
        return ans;  // 返回本次查询能得到的最大值
    }  // search 方法结束
};  // Trie 类结束

class Solution {  // 题解类
public:  // 题解方法对外可见
    int findMaximumXOR(vector<int>& nums) {  // nums 是输入数组，返回任取两个数异或能得到的最大值
        Trie* trie = new Trie();  // 建一棵空的字典树
        int ans = 0;  // ans 记录当前最大异或值
        for (int x : nums) {  // 逐个处理数组元素
            trie->insert(x);  // 先把 x 插入树中，保证查询到的都是已经插入过的数
            ans = max(ans, trie->search(x));  // 用 x 在树中查询最优异或值，并更新答案
        }  // 元素循环结束
        return ans;  // 返回最大异或值
    }  // findMaximumXOR 方法结束
};  // Solution 类结束