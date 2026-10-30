// 3845. 最大子数组异或值 / Maximum Subarray XOR with Bounded Range（困难）
// 核心思路：单调队列维护窗口内极差不超过 k 的左端点区间，再用 0-1 字典树配合异或前缀和查询最大异或。
// 复杂度：时间 O(n log U)（U 为值域 2^15），空间 O(n)。
class Solution {  // 解题类：LeetCode 判题器约定的类名
public:  // 公有接口
    int maxXor(vector<int>& nums, int k) {  // 返回元素极差不超过 k 的连续子数组的最大异或值
        root = new TrieNode();  // 为本次调用重建 0-1 字典树的根节点
        int n = nums.size();  // n 为数组长度
        vector<int> prefix(n + 1);  // prefix[i] 表示 nums 前 i 个元素的异或前缀和
        for (int i = 0; i < n; ++i) {  // 预处理异或前缀和
            prefix[i + 1] = prefix[i] ^ nums[i];  // 递推得到下一个前缀异或值
        }  // 前缀和计算结束
        deque<int> maxq, minq;  // 两个单调队列：分别维护窗口内最大值、最小值的下标
        int left = 0, ans = 0;  // left 为滑动窗口左端，ans 记录最大异或值
        update(prefix[0], 1);  // 先把 prefix[0] 插入字典树
        for (int right = 0; right < n; ++right) {  // right 为滑动窗口右端，逐步向右扩展
            while (!maxq.empty() && nums[maxq.back()] <= nums[right]) {  // 维护递减的最大值队列
                maxq.pop_back();  // 弹出队尾所有不大于当前值的下标
            }  // 最大值队尾维护结束
            while (!minq.empty() && nums[minq.back()] >= nums[right]) {  // 维护递增的最小值队列
                minq.pop_back();  // 弹出队尾所有不小于当前值的下标
            }  // 最小值队尾维护结束
            maxq.push_back(right);  // 当前下标入最大值队列队尾
            minq.push_back(right);  // 当前下标入最小值队列队尾
            while (nums[maxq.front()] - nums[minq.front()] > k) {  // 窗口极差超限：收缩左端点直到满足条件
                if (maxq.front() == left) {  // 队首正是要移出的左端点时同步出队
                    maxq.pop_front();  // 最大值队首出队
                }  // 最大值队首判断结束
                if (minq.front() == left) {  // 最小值队首同样处理
                    minq.pop_front();  // 最小值队首出队
                }  // 最小值队首判断结束
                update(prefix[left], -1);  // 左端点移出窗口，从字典树中删除对应前缀值
                ++left;  // 窗口左端右移一位
            }  // 窗口收缩结束
            ans = max(ans, getMaxXor(prefix[right + 1]));  // 用当前前缀值在树中查询最大异或并更新答案
            update(prefix[right + 1], 1);  // 把当前前缀值插入字典树供后续查询
        }  // 遍历结束
        return ans;  // 返回满足极差限制的最大异或值
    }  // maxXor 方法结束

private:  // 私有成员与辅助函数
    struct TrieNode {  // 0-1 字典树节点定义
        TrieNode* children[2]{};  // 两个子指针分别表示当前位为 0 / 1
        int count = 0;  // count 统计经过该节点的元素个数，用于删除后判断是否存在
    };  // 字典树节点定义结束

    TrieNode* root;  // 字典树根指针

    void update(int value, int delta) {  // 把 value 按位插入（delta=1）或删除（delta=-1）字典树
        TrieNode* cur = root;  // 从根节点开始逐位下行
        for (int bit = 14; bit >= 0; --bit) {  // 从高位第 14 位到第 0 位遍历
            int b = (value >> bit) & 1;  // 取出当前位的比特值
            if (!cur->children[b]) {  // 该分支还不存在
                cur->children[b] = new TrieNode();  // 新建节点挂到该分支上
            }  // 分支创建结束
            cur = cur->children[b];  // 下移到对应子节点
            cur->count += delta;  // 途经节点的计数同步增减
        }  // 逐位插入结束
    }  // update 方法结束

    int getMaxXor(int value) {  // 查询字典树中与 value 异或结果最大的值
        TrieNode* cur = root;  // 从根节点开始贪心下行
        int ans = 0;  // 记录能得到的最大异或值
        for (int bit = 14; bit >= 0; --bit) {  // 从高位到低位逐位决策
            int b = (value >> bit) & 1;  // 取出 value 当前位的比特值
            int opp = 1 - b;  // 取反位，优先走异或结果为 1 的分支
            if (cur->children[opp] && cur->children[opp]->count > 0) {  // 反向分支存在且仍有元素时贪心选取
                ans |= 1 << bit;  // 该位异或结果为 1，计入答案
                cur = cur->children[opp];  // 下移到反向子节点
            } else {  // 否则只能走同向分支
                cur = cur->children[b];  // 下移到同向子节点，该位异或结果为 0
            }  // 分支选择结束
        }  // 逐位决策结束
        return ans;  // 返回最大异或值
    }  // getMaxXor 方法结束
};  // 解题类定义结束
