// 题目：2935. 找出强数对的最大异或值 II（Maximum Strong Pair XOR II）
// 思路：排序后用滑动窗口保证窗口内 max <= 2 * min（于是窗口内任意两数都构成强数对），再用 0/1 字典树在窗口内查与 y 异或最大的值。
// 时间复杂度：O(n log C)，每个数只进出字典树各一次、每次走 21 层；空间复杂度：O(n log C)，字典树结点总量。
class Trie {  // 0/1 字典树：支持插入、删除，以及查询与某数异或的最大值
public:  // 成员对外可见
    Trie* children[2];  // 两个孩子：下标 0 表示该位为 0，下标 1 表示该位为 1
    int cnt;  // 经过当前结点的数字个数，用于支持删除

    Trie()  // 构造函数：初始化两个孩子与计数
        : cnt(0) {  // 计数从 0 开始
        children[0] = nullptr;  // 0 号孩子先置空
        children[1] = nullptr;  // 1 号孩子先置空
    }

    void insert(int x) {  // 把 x 插入字典树
        Trie* node = this;  // 从根结点出发
        for (int i = 20; ~i; --i) {  // 从第 20 位逐位降到第 0 位；~i 在 i 为 -1 时得 0，循环自然结束
            int v = (x >> i) & 1;  // 取出 x 的第 i 位
            if (node->children[v] == nullptr) {  // 该分支还不存在
                node->children[v] = new Trie();  // 新建结点挂到该分支上
            }
            node = node->children[v];  // 沿该分支继续下行
            ++node->cnt;  // 路径上每个结点的计数加一
        }
    }

    int search(int x) {  // 在树中找与 x 异或值最大的数，返回该异或值
        Trie* node = this;  // 从根结点出发
        int ans = 0;  // 累计异或结果
        for (int i = 20; ~i; --i) {  // 从最高位到最低位贪心
            int v = (x >> i) & 1;  // x 的第 i 位
            if (node->children[v ^ 1] != nullptr && node->children[v ^ 1]->cnt > 0) {  // 存在与当前位相反且仍存活的数，就能让这一位异或出 1
                ans |= 1 << i;  // 该位异或结果置 1
                node = node->children[v ^ 1];  // 走相反分支，继续贪心
            } else {  // 否则只能走相同分支
                node = node->children[v];  // 该位异或结果为 0，无需置位
            }
        }
        return ans;  // 返回能得到的最大异或值
    }

    void remove(int x) {  // 把 x 从字典树中删除（即路径计数减一）
        Trie* node = this;  // 从根结点出发
        for (int i = 20; ~i; --i) {  // 沿与插入完全相同的路径下行
            int v = (x >> i) & 1;  // 计算该位走哪个分支
            node = node->children[v];  // 走到对应孩子
            --node->cnt;  // 路径计数减一，计数为 0 即视为该数不存在
        }
    }
};  // 字典树定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumStrongPairXor(vector<int>& nums) {  // nums：输入数组
        sort(nums.begin(), nums.end());  // 升序排序，滑动窗口才能用「最大值 <= 2 * 最小值」判定
        Trie* tree = new Trie();  // 维护当前滑动窗口内所有数字的字典树
        int ans = 0, i = 0;  // ans：最大异或值；i：滑动窗口左端点下标
        for (int y : nums) {  // y 依次作为窗口右端点，同时也是窗口内最大值
            tree->insert(y);  // 右端点数字加入窗口
            while (y > nums[i] * 2) {  // 最大值超过最小值的两倍，左端点数字就与窗口内任何元素都构不成强数对
                tree->remove(nums[i++]);  // 先删除左端点 nums[i]，后置自增让 i 再右移一格
            }
            ans = max(ans, tree->search(y));  // 在窗口内找与 y 异或最大的数并更新答案
        }
        return ans;  // 返回最大异或值
    }
};  // 类定义结束